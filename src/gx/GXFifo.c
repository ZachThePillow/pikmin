#include "Dolphin/gx.h"
#include "Dolphin/os.h"

static OSThread* __GXCurrentThread;
static GXBool CPGPLinked;
static BOOL GXOverflowSuspendInProgress;
static GXBreakPtCallback BreakPointCB;
static u32 __GXOverflowCount;
#if DEBUG
static int IsWGPipeRedirected;
#endif

struct __GXFifoObj* CPUFifo;
struct __GXFifoObj* GPFifo;
void* __GXCurrentBP;

#if DEBUG
static char __data_0[] = "[GXOverflowHandler]";
#endif

/*
 * --INFO--
 * Address:	........
 * Size:	000050
 */
static void GXOverflowHandler(s16 interrupt, OSContext* context)
{
#if DEBUG
	if (__gxVerif->verifyLevel > 1) {
		OSReport(__data_0);
	}
#endif
	ASSERTLINE(0x15A, !GXOverflowSuspendInProgress);

	__GXOverflowCount++;
	__GXWriteFifoIntEnable(0, 1);
	__GXWriteFifoIntReset(1, 0);
	GXOverflowSuspendInProgress = TRUE;

#if DEBUG
	if (__gxVerif->verifyLevel > 1) {
		OSReport("[GXOverflowHandler Sleeping]");
	}
#endif
	OSSuspendThread(__GXCurrentThread);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000044
 */
static void GXUnderflowHandler(s16 interrupt, OSContext* context)
{
#if DEBUG
	if (__gxVerif->verifyLevel > 1) {
		OSReport("[GXUnderflowHandler]");
	}
#endif
	ASSERTLINE(0x184, GXOverflowSuspendInProgress);

	OSResumeThread(__GXCurrentThread);
	GXOverflowSuspendInProgress = FALSE;
	__GXWriteFifoIntReset(1U, 1U);
	__GXWriteFifoIntEnable(1U, 0U);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000080
 */
static void GXBreakPointHandler(s16 interrupt, OSContext* context)
{
	OSContext exceptionContext;

	gx->cpEnable = gx->cpEnable & 0xFFFFFFDF;
	__cpReg[1]   = gx->cpEnable;
	if (BreakPointCB != NULL) {
		OSClearContext(&exceptionContext);
		OSSetCurrentContext(&exceptionContext);
		BreakPointCB();
		OSClearContext(&exceptionContext);
		OSSetCurrentContext(context);
	}
}

/*
 * --INFO--
 * Address:	8020EB40
 * Size:	00013C
 */
static void GXCPInterruptHandler(s16 interrupt, OSContext* context)
{
	gx->cpStatus = __cpReg[0];
	if (GET_REG_FIELD(gx->cpEnable, 1, 3) && GET_REG_FIELD(gx->cpStatus, 1, 1)) {
		GXUnderflowHandler(interrupt, context);
	}
	if (GET_REG_FIELD(gx->cpEnable, 1, 2) && GET_REG_FIELD(gx->cpStatus, 1, 0)) {
		GXOverflowHandler(interrupt, context);
	}
	if (GET_REG_FIELD(gx->cpEnable, 1, 5) && GET_REG_FIELD(gx->cpStatus, 1, 4)) {
		GXBreakPointHandler(interrupt, context);
	}
}

/*
 * --INFO--
 * Address:	8020EC7C
 * Size:	00006C
 */
void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size)
{
	struct _GXFifoObjPriv* realFifo = (struct _GXFifoObjPriv*)fifo;

	ASSERTMSGLINE(0x1FF, realFifo != CPUFifo, "GXInitFifoBase: fifo is attached to CPU");
	ASSERTMSGLINE(0x201, realFifo != GPFifo, "GXInitFifoBase: fifo is attached to GP");
	ASSERTMSGLINE(0x203, ((u32)base & 0x1F) == 0, "GXInitFifoBase: base must be 32B aligned");
	ASSERTMSGLINE(0x205, base != NULL, "GXInitFifoBase: base pointer is NULL");
	ASSERTMSGLINE(0x207, (size & 0x1F) == 0, "GXInitFifoBase: size must be 32B aligned");
	ASSERTMSGLINE(0x209, size >= 0x10000, "GXInitFifoBase: fifo is not large enough");

	realFifo->base       = base;
	realFifo->end        = (u8*)base + size - 4;
	realFifo->size       = size;
	realFifo->rwDistance = 0;
	GXInitFifoLimits(fifo, size - 0x4000, (size >> 1) & ~0x1F);
	GXInitFifoPtrs(fifo, base, base);
}

/*
 * --INFO--
 * Address:	8020ECE8
 * Size:	000070
 */
void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr)
{
	struct __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;
	BOOL enabled;

	ASSERTMSGLINE(0x231, realFifo != CPUFifo, "GXInitFifoPtrs: fifo is attached to CPU");
	ASSERTMSGLINE(0x233, realFifo != GPFifo, "GXInitFifoPtrs: fifo is attached to GP");
	ASSERTMSGLINE(0x235, ((u32)readPtr & 0x1F) == 0, "GXInitFifoPtrs: readPtr not 32B aligned");
	ASSERTMSGLINE(0x237, ((u32)writePtr & 0x1F) == 0, "GXInitFifoPtrs: writePtr not 32B aligned");
	ASSERTMSGLINE(0x23A, realFifo->base <= readPtr && readPtr < realFifo->top, "GXInitFifoPtrs: readPtr not in fifo range");
	ASSERTMSGLINE(0x23D, realFifo->base <= writePtr && writePtr < realFifo->top, "GXInitFifoPtrs: writePtr not in fifo range");

	enabled         = OSDisableInterrupts();
	realFifo->rdPtr = readPtr;
	realFifo->wrPtr = writePtr;
	realFifo->count = (u8*)writePtr - (u8*)readPtr;
	if (realFifo->count < 0) {
		realFifo->count += realFifo->size;
	}
	OSRestoreInterrupts(enabled);
}

/*
 * --INFO--
 * Address:	8020ED58
 * Size:	00000C
 */
void GXInitFifoLimits(GXFifoObj* fifo, u32 hiWatermark, u32 loWatermark)
{
	struct __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;

	ASSERTMSGLINE(0x262, realFifo != GPFifo, "GXInitFifoLimits: fifo is attached to GP");
	ASSERTMSGLINE(0x264, (hiWatermark & 0x1F) == 0, "GXInitFifoLimits: hiWatermark not 32B aligned");
	ASSERTMSGLINE(0x266, (loWatermark & 0x1F) == 0, "GXInitFifoLimits: loWatermark not 32B aligned");
	ASSERTMSGLINE(0x268, hiWatermark < realFifo->top - realFifo->base, "GXInitFifoLimits: hiWatermark too large");
	ASSERTMSGLINE(0x26A, loWatermark < hiWatermark, "GXInitFifoLimits: hiWatermark below lo watermark");

	realFifo->hiWatermark = hiWatermark;
	realFifo->loWatermark = loWatermark;
}

/*
 * --INFO--
 * Address:	8020ED64
 * Size:	000110
 */
void GXSetCPUFifo(GXFifoObj* fifo)
{
	struct __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;
	BOOL enabled                 = OSDisableInterrupts();

	CPUFifo = realFifo;
	if (CPUFifo == GPFifo) {
		u32 reg = 0;

		__piReg[3] = (u32)realFifo->base & 0x3FFFFFFF;
		__piReg[4] = (u32)realFifo->top & 0x3FFFFFFF;
		SET_REG_FIELD(0x294, reg, 21, 5, ((u32)realFifo->wrPtr & 0x3FFFFFFF) >> 5);
		SET_REG_FIELD(0x295, reg, 1, 26, 0);
		__piReg[5] = reg;
		CPGPLinked = GX_TRUE;
		__GXWriteFifoIntReset(1, 1);
		__GXWriteFifoIntEnable(1, 0);
		__GXFifoLink(1);
	} else {
		u32 reg;

		if (CPGPLinked) {
			__GXFifoLink(0);
			CPGPLinked = GX_FALSE;
		}
		__GXWriteFifoIntEnable(0, 0);
		reg        = 0;
		__piReg[3] = (u32)realFifo->base & 0x3FFFFFFF;
		__piReg[4] = (u32)realFifo->top & 0x3FFFFFFF;
		SET_REG_FIELD(0x2B7, reg, 21, 5, ((u32)realFifo->wrPtr & 0x3FFFFFFF) >> 5);
		SET_REG_FIELD(0x2B8, reg, 1, 26, 0);
		__piReg[5] = reg;
	}

	__sync();

	OSRestoreInterrupts(enabled);
}

/*
 * --INFO--
 * Address:	8020EE74
 * Size:	000178
 */
void GXSetGPFifo(GXFifoObj* fifo)
{
	struct __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;
	BOOL enabled                 = OSDisableInterrupts();

	__GXFifoReadDisable();
	__GXWriteFifoIntEnable(0, 0);
	GPFifo = realFifo;

	__cpReg[16] = (u32)realFifo->base & 0xFFFF;
	__cpReg[18] = (u32)realFifo->top & 0xFFFF;
	__cpReg[24] = realFifo->count & 0xFFFF;
	__cpReg[26] = (u32)realFifo->wrPtr & 0xFFFF;
	__cpReg[28] = (u32)realFifo->rdPtr & 0xFFFF;
	__cpReg[20] = (u32)realFifo->hiWatermark & 0xFFFF;
	__cpReg[22] = (u32)realFifo->loWatermark & 0xFFFF;
	__cpReg[17] = ((u32)realFifo->base & 0x3FFFFFFF) >> 16;
	__cpReg[19] = ((u32)realFifo->top & 0x3FFFFFFF) >> 16;
	__cpReg[25] = realFifo->count >> 16;
	__cpReg[27] = ((u32)realFifo->wrPtr & 0x3FFFFFFF) >> 16;
	__cpReg[29] = ((u32)realFifo->rdPtr & 0x3FFFFFFF) >> 16;
	__cpReg[21] = (u32)realFifo->hiWatermark >> 16;
	__cpReg[23] = (u32)realFifo->loWatermark >> 16;

	__sync();

	if (CPUFifo == GPFifo) {
		CPGPLinked = GX_TRUE;
		__GXWriteFifoIntEnable(1, 0);
		__GXFifoLink(1);
	} else {
		CPGPLinked = GX_FALSE;
		__GXWriteFifoIntEnable(0, 0);
		__GXFifoLink(0);
	}
	__GXWriteFifoIntReset(1, 1);
	__GXFifoReadEnable();
	OSRestoreInterrupts(enabled);
}

/*
 * --INFO--
 * Address:	8020EFEC
 * Size:	000020
 */
void GXSaveCPUFifo(GXFifoObj* fifo)
{
	struct __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;
	ASSERTMSGLINE(0x321, realFifo == CPUFifo, "GXSaveCPUFifo: fifo is not attached to CPU");
	__GXSaveCPUFifoAux(realFifo);
}

#define SOME_MACRO1(fifo)                       \
	do {                                        \
		u32 temp = __cpReg[29] << 16;           \
		temp |= __cpReg[28];                    \
		fifo->rdPtr = OSPhysicalToCached(temp); \
	} while (0)

#define SOME_MACRO2(fifo)             \
	do {                              \
		u32 temp = __cpReg[25] << 16; \
		temp |= __cpReg[24];          \
		fifo->count = temp;           \
	} while (0)

/*
 * --INFO--
 * Address:	8020F00C
 * Size:	0000DC
 */
void __GXSaveCPUFifoAux(struct __GXFifoObj* realFifo)
{
	BOOL enabled = OSDisableInterrupts();

	GXFlush();
	realFifo->base  = OSPhysicalToCached(__piReg[3]);
	realFifo->top   = OSPhysicalToCached(__piReg[4]);
	realFifo->wrPtr = OSPhysicalToCached(__piReg[5] & 0xFBFFFFFF);
	if (CPGPLinked) {
		SOME_MACRO1(realFifo);
		SOME_MACRO2(realFifo);
	} else {
		realFifo->count = (u8*)realFifo->wrPtr - (u8*)realFifo->rdPtr;
		if (realFifo->count < 0)
			realFifo->count += realFifo->size;
	}
	OSRestoreInterrupts(enabled);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
void GXSaveGPFifo(GXFifoObj* fifo)
{
	struct __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;
	unsigned long cpStatus;
	unsigned char readIdle;
	unsigned long temp;

	ASSERTMSGLINE(0x36A, realFifo == GPFifo, "GXSaveGPFifo: fifo is not attached to GP");
	cpStatus = __cpReg[0];
	readIdle = GET_REG_FIELD(cpStatus, 1, 2);
	ASSERTMSGLINE(0x371, readIdle, "GXSaveGPFifo: GP is not idle");

	SOME_MACRO1(realFifo);
	SOME_MACRO2(realFifo);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000064
 */
void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle, GXBool* cmdIdle, GXBool* brkpt)
{
	gx->cpStatus = __cpReg[0];
	*overhi      = GET_REG_FIELD(gx->cpStatus, 1, 0);
	*underlow    = (int)GET_REG_FIELD(gx->cpStatus, 1, 1);
	*readIdle    = (int)GET_REG_FIELD(gx->cpStatus, 1, 2);
	*cmdIdle     = (int)GET_REG_FIELD(gx->cpStatus, 1, 3);
	*brkpt       = (int)GET_REG_FIELD(gx->cpStatus, 1, 4);
}
/*
 * --INFO--
 * Address:	........
 * Size:	000110
 */
void GXGetFifoStatus(GXFifoObj* fifo, GXBool* overhi, GXBool* underflow, u32* fifoCount, GXBool* cpuWrite, GXBool* gpRead, GXBool* fifowrap)
{
	struct __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;

	*underflow = GX_FALSE;
	*overhi    = GX_FALSE;
	*fifoCount = 0;
	*fifowrap  = GX_FALSE;
	if (realFifo == GPFifo) {
		SOME_MACRO1(realFifo);
		SOME_MACRO2(realFifo);
	}
	if (realFifo == CPUFifo) {
		__GXSaveCPUFifoAux(realFifo);
		*fifowrap = (int)GET_REG_FIELD(__piReg[5], 1, 26);
	}
	*overhi    = (realFifo->count > realFifo->hiWatermark);
	*underflow = (realFifo->count < realFifo->loWatermark);
	*fifoCount = (realFifo->count);
	*cpuWrite  = (CPUFifo == realFifo);
	*gpRead    = (GPFifo == realFifo);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000098
 */
void GXGetFifoPtrs(GXFifoObj* fifo, void** readPtr, void** writePtr)
{
	struct __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;

	ASSERTMSGLINE(0x3F2, realFifo == CPUFifo || realFifo == GPFifo, "GXGetFifoPtrs: fifo is not CPU or GP fifo");
	if (realFifo == CPUFifo) {
		realFifo->wrPtr = OSPhysicalToCached(__piReg[5] & 0xFBFFFFFF);
	}
	if (realFifo == GPFifo) {
		SOME_MACRO1(realFifo);
		SOME_MACRO2(realFifo);
	} else {
		realFifo->count = (u8*)realFifo->wrPtr - (u8*)realFifo->rdPtr;
		if (realFifo->count < 0) {
			realFifo->count += realFifo->size;
		}
	}
	*readPtr  = realFifo->rdPtr;
	*writePtr = realFifo->wrPtr;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
void* GXGetFifoBase(GXFifoObj* fifo)
{
	struct __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;

	return realFifo->base;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
u32 GXGetFifoSize(GXFifoObj* fifo)
{
	struct __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;

	return realFifo->size;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000014
 */
void GXGetFifoLimits(GXFifoObj* fifo, u32* hi, u32* lo)
{
	struct __GXFifoObj* realFifo = (struct __GXFifoObj*)fifo;

	*hi = realFifo->hiWatermark;
	*lo = realFifo->loWatermark;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000044
 */
GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb)
{
	GXBreakPtCallback oldcb = BreakPointCB;
	BOOL enabled            = OSDisableInterrupts();

	BreakPointCB = cb;
	OSRestoreInterrupts(enabled);
	return oldcb;
}

void* __GXCurrentBP;

/*
 * --INFO--
 * Address:	........
 * Size:	000098
 */
void GXEnableBreakPt(void* break_pt)
{
	BOOL enabled = OSDisableInterrupts();

	__GXFifoReadDisable();
	ASSERTMSGLINE(0x44A, (u8*)break_pt >= GPFifo->base && (u8*)break_pt <= GPFifo->top,
	              "GXEnableBreakPt: Break point value not in fifo range");
	__cpReg[30]   = (u32)break_pt;
	__cpReg[31]   = ((u32)break_pt >> 16) & 0x3FFF;
	gx->cpEnable  = (gx->cpEnable & 0xFFFFFFFD) | 2;
	gx->cpEnable  = (gx->cpEnable & 0xFFFFFFDF) | 0x20;
	__cpReg[1]    = gx->cpEnable;
	__GXCurrentBP = break_pt;
	__GXFifoReadEnable();
	OSRestoreInterrupts(enabled);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000064
 */
void GXDisableBreakPt(void)
{
	BOOL enabled = OSDisableInterrupts();

	gx->cpEnable  = gx->cpEnable & 0xFFFFFFFD;
	gx->cpEnable  = gx->cpEnable & 0xFFFFFFDF;
	__cpReg[1]    = gx->cpEnable;
	__GXCurrentBP = NULL;
	OSRestoreInterrupts(enabled);
}

/*
 * --INFO--
 * Address:	8020F0E8
 * Size:	000044
 */
void __GXFifoInit(void)
{
	__OSSetInterruptHandler(0x11, GXCPInterruptHandler);
	__OSUnmaskInterrupts(0x4000);
	__GXCurrentThread           = OSGetCurrentThread();
	GXOverflowSuspendInProgress = FALSE;
}

/*
 * --INFO--
 * Address:	8020F12C
 * Size:	000028
 */
void __GXFifoReadEnable(void)
{
	SET_REG_FIELD(0, gx->cpEnable, 1, 0, 1);
	__cpReg[1] = gx->cpEnable;
}

/*
 * --INFO--
 * Address:	8020F154
 * Size:	000024
 */
void __GXFifoReadDisable(void)
{
	SET_REG_FIELD(0, gx->cpEnable, 1, 0, 0);
	__cpReg[1] = gx->cpEnable;
}

/*
 * --INFO--
 * Address:	8020F178
 * Size:	000044
 */
void __GXFifoLink(u8 en)
{
	SET_REG_FIELD(0x4B0, gx->cpEnable, 1, 4, (en != 0) ? 1 : 0);
	__cpReg[1] = gx->cpEnable;
}

/*
 * --INFO--
 * Address:	8020F1BC
 * Size:	00004C
 */
void __GXWriteFifoIntEnable(u8 hiWatermarkEn, u8 loWatermarkEn)
{
	SET_REG_FIELD(0x4C6, gx->cpEnable, 1, 2, hiWatermarkEn);
	SET_REG_FIELD(0x4C7, gx->cpEnable, 1, 3, loWatermarkEn);
	__cpReg[1] = gx->cpEnable;
}

/*
 * --INFO--
 * Address:	8020F208
 * Size:	00004C
 */
void __GXWriteFifoIntReset(u8 hiWatermarkClr, u8 loWatermarkClr)
{
	SET_REG_FIELD(0x4DE, gx->cpClr, 1, 0, hiWatermarkClr);
	SET_REG_FIELD(0x4DF, gx->cpClr, 1, 1, loWatermarkClr);
	__cpReg[2] = gx->cpClr;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
void __GXInsaneWatermark(void)
{
	struct __GXFifoObj* realFifo = GPFifo;

	realFifo->hiWatermark = realFifo->loWatermark + 512;
	__cpReg[20]           = (realFifo->hiWatermark & 0x3FFFFFFF) & 0xFFFF;
	__cpReg[21]           = (realFifo->hiWatermark & 0x3FFFFFFF) >> 16;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000FC
 */
void __GXCleanGPFifo(void)
{
	GXFifoObj dummyFifo;
	GXFifoObj* gpFifo  = GXGetGPFifo();
	GXFifoObj* cpuFifo = GXGetCPUFifo();
	void* base         = GXGetFifoBase(gpFifo);

	dummyFifo = *gpFifo;
	GXInitFifoPtrs(&dummyFifo, base, base);
	GXSetGPFifo(&dummyFifo);
	if (cpuFifo == gpFifo) {
		GXSetCPUFifo(&dummyFifo);
	}
	GXInitFifoPtrs(gpFifo, base, base);
	GXSetGPFifo(gpFifo);
	if (cpuFifo == gpFifo) {
		GXSetCPUFifo(cpuFifo);
	}
}

/*
 * --INFO--
 * Address:	8020F254
 * Size:	00004C
 */
OSThread* GXSetCurrentGXThread(void)
{
	BOOL enabled;
	struct OSThread* prev;

	enabled = OSDisableInterrupts();
	prev    = __GXCurrentThread;
	ASSERTMSGLINE(0x532, !GXOverflowSuspendInProgress, "GXSetCurrentGXThread: Two threads cannot generate GX commands at the same time!");
	__GXCurrentThread = OSGetCurrentThread();
	OSRestoreInterrupts(enabled);
	return prev;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
OSThread* GXGetCurrentGXThread(void)
{
	return __GXCurrentThread;
}

/*
 * --INFO--
 * Address:	8020F2A0
 * Size:	000008
 */
GXFifoObj* GXGetCPUFifo(void)
{
	return (GXFifoObj*)CPUFifo;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
GXFifoObj* GXGetGPFifo(void)
{
	return (GXFifoObj*)GPFifo;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
u32 GXGetOverflowCount(void)
{
	return __GXOverflowCount;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000010
 */
u32 GXResetOverflowCount(void)
{
	u32 oldcount;

	oldcount          = __GXOverflowCount;
	__GXOverflowCount = 0;
	return oldcount;
}

#define SET_REG_FIELD2(line, reg, mask, val)                                                     \
	do {                                                                                         \
		ASSERTMSGLINE(line, ((val) & ~(mask)) == 0, "GX Internal: Register field out of range"); \
		(reg) = ((u32)(reg) & ~(mask)) | ((u32)(val));                                           \
	} while (0)

/*
 * --INFO--
 * Address:	........
 * Size:	000104
 */
volatile void* GXRedirectWriteGatherPipe(void* ptr)
{
	u32 reg      = 0;
	BOOL enabled = OSDisableInterrupts();

	CHECK_GXBEGIN(0x5A6, "GXRedirectWriteGatherPipe");
	ASSERTLINE(0x5A7, OFFSET(ptr, 32) == 0);
	ASSERTLINE(0x5A9, !IsWGPipeRedirected);
#if DEBUG
	IsWGPipeRedirected = TRUE;
#endif

	GXFlush();
	while (PPCMfwpar() & 1) { }
	PPCMtwpar((u32)OSUncachedToPhysical((void*)GXFIFO_ADDR));
	if (CPGPLinked) {
		__GXFifoLink(0);
		__GXWriteFifoIntEnable(0, 0);
	}
	CPUFifo->wrPtr = OSPhysicalToCached(__piReg[5] & 0xFBFFFFFF);
	__piReg[3]     = 0;
	__piReg[4]     = 0x04000000;
	SET_REG_FIELD(0x5C8, reg, 21, 5, ((u32)ptr & 0x3FFFFFFF) >> 5);
	/*if (((u32)ptr >> 5) & 0x1E00000)
	    OSPanic(__FILE__, 0x5FB, "GX Internal: Register field out of range");
	//SET_REG_FIELD(0x5C8, reg, 25, 5, ((u32)ptr & 0x3FFFFFFF) >> 5);*/
	// reg = (reg & ~0x3FFFFE0) | ((u32)ptr & 0x3FFFFFE0);
	reg &= 0xFBFFFFFF;
	__piReg[5] = reg;
	__sync();
	OSRestoreInterrupts(enabled);
	return (volatile void*)GXFIFO_ADDR;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0001B4
 */
void GXRestoreWriteGatherPipe(void)
{
	u32 reg = 0;  // r31
	u32 i;        // r29
	BOOL enabled; // r28

	ASSERTLINE(0x5E1, IsWGPipeRedirected);
#if DEBUG
	IsWGPipeRedirected = FALSE;
#endif
	enabled = OSDisableInterrupts();
	for (i = 0; i < 31; i++) {
		GXWGFifo.u8 = 0;
	}
	PPCSync();
	while (PPCMfwpar() & 1) { }
	PPCMtwpar((u32)OSUncachedToPhysical((void*)GXFIFO_ADDR));
	__piReg[3] = (u32)CPUFifo->base & 0x3FFFFFFF;
	__piReg[4] = (u32)CPUFifo->top & 0x3FFFFFFF;
	SET_REG_FIELD(0x5FB, reg, 21, 5, ((u32)CPUFifo->wrPtr & 0x3FFFFFFF) >> 5);
	/*if ((((u32)CPUFifo->wrPtr & 0x3FFFFFFF) >> 5) & 0x7E00000)
	    OSPanic(__FILE__, 0x5FB, "GX Internal: Register field out of range");
	reg = (reg & ~0x3FFFFE0) | (((u32)CPUFifo->wrPtr & 0x3FFFFFFF) & ~0x1F);*/
	// SET_REG_FIELD(0x5FB, reg, 25, 5, ((u32)CPUFifo->wrPtr & 0x3FFFFFFF) >> 5);
	reg &= 0xFBFFFFFF;
	__piReg[5] = reg;
	if (CPGPLinked) {
		__GXWriteFifoIntReset(1, 1);
		__GXWriteFifoIntEnable(1, 0);
		__GXFifoLink(1);
	}
	__sync();
	OSRestoreInterrupts(enabled);
}
