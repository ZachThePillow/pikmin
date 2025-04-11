#include "Graphics.h"
#include "Dolphin/os.h"
#include "Shape.h"
#include "sysNew.h"
#include "DebugLog.h"

/*
 * --INFO--
 * Address:	........
 * Size:	00009C
 */
DEFINE_ERROR()

/*
 * --INFO--
 * Address:	........
 * Size:	0000F4
 */
DEFINE_PRINT("DGXGraphics")

DGXGraphics* gfx;

GXRenderModeObj progressiveRenderMode = { VI_TVMODE_NTSC_PROG, 640, 480, 480, 40, 0, 640, 480, VI_XFBMODE_SF };
GXRenderModeObj localNtsc480IntDf     = { VI_TVMODE_NTSC_INT, 640, 480, 480, 40, 0, 640, 480, VI_XFBMODE_SF };

GXRenderModeObj* sScreenMode[2] = { &localNtsc480IntDf, &progressiveRenderMode };

static int sFirstFrame      = 4;
static int kDefaultFifoSize = 0x60000;
static int kTempFifoSize    = 0x10000;
static int kDefaultDLSize   = 0x20000;
static bool sendMtxIndx     = true;
static bool sendTxUVIndx    = true;

u32 sFrameSize;
int frameNum;
int oldCull;
int oldVerts;
int oldNorms;
int oldCols;

int oldTexs[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
GXColor GColors[3];

/*
 * --INFO--
 * Address:	800474B8
 * Size:	0002F8
 */
DGXGraphics::DGXGraphics(bool flag)
{
	_3BC = new (0x20) u8[kDefaultFifoSize];
	_3C0 = new (0x20) u8[kTempFifoSize];
	_3C4 = new (0x20) u8[kDefaultDLSize];
	_3B8 = GXInit(_3BC, kDefaultFifoSize);

	if (flag) {
		_00 = 1;
	} else {
		_00 = 0;
	}

	mScreenWidth  = sScreenMode[_00]->fbWidth;
	mScreenHeight = sScreenMode[_00]->efbHeight;
	GXSetDispCopySrc(0, 0, sScreenMode[_00]->fbWidth, sScreenMode[_00]->efbHeight);
	GXSetDispCopyDst(sScreenMode[_00]->fbWidth, sScreenMode[_00]->xfbHeight);
	GXSetDispCopyYScale((f32)sScreenMode[_00]->xfbHeight / (f32)sScreenMode[_00]->efbHeight);
	GXSetCopyFilter(sScreenMode[_00]->aa, sScreenMode[_00]->sample_pattern, GX_TRUE, sScreenMode[_00]->vfilter);

	if (sScreenMode[_00]->aa) {
		GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
	} else {
		GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
	}

	VIInit();
	videoReset();

	sFrameSize = (sScreenMode[_00]->fbWidth + 0xf & 0xfff0) * sScreenMode[_00]->xfbHeight * 2;

	int backup = gsys->getHeap(gsys->mActiveHeapIdx)->mAllocType;
	gsys->getHeap(gsys->mActiveHeapIdx)->setAllocType(2);

	_610      = new (0x20) u8[sFrameSize];
	u16* test = (u16*)_610;
	for (int i = 0; i < sFrameSize / 2; i++) {
		test[i] = 0x1080;
	}

	DCFlushRange(_610, sFrameSize);
	gsys->getHeap(gsys->mActiveHeapIdx)->mAllocType = backup;
	VISetBlack(TRUE);
	VISetNextFrameBuffer(_610);
	VIFlush();
	VIWaitForRetrace();
	setupRender();
	gfx  = this;
	_614 = 0;
	_618 = VIGetRetraceCount();
	_61C = gsys->mFrameRate;
	_620 = VISetPostRetraceCallback(retraceProc);
	OSInitMessageQueue(&_624, &_644, 1);

	f32 badcompiler[2];
}

/*
 * --INFO--
 * Address:	800477B0
 * Size:	000094
 */
void DGXGraphics::setVerticalFilter(u8* vf)
{
	sScreenMode[_00]->vfilter[0] = vf[0];
	sScreenMode[_00]->vfilter[1] = vf[1];
	sScreenMode[_00]->vfilter[2] = vf[2];
	sScreenMode[_00]->vfilter[3] = vf[3];
	sScreenMode[_00]->vfilter[4] = vf[4];
	sScreenMode[_00]->vfilter[5] = vf[5];
	sScreenMode[_00]->vfilter[6] = vf[6];
}

/*
 * --INFO--
 * Address:	80047844
 * Size:	000094
 */
void DGXGraphics::getVerticalFilter(u8* vf)
{
	vf[0] = sScreenMode[_00]->vfilter[0];
	vf[1] = sScreenMode[_00]->vfilter[1];
	vf[2] = sScreenMode[_00]->vfilter[2];
	vf[3] = sScreenMode[_00]->vfilter[3];
	vf[4] = sScreenMode[_00]->vfilter[4];
	vf[5] = sScreenMode[_00]->vfilter[5];
	vf[6] = sScreenMode[_00]->vfilter[6];
}

/*
 * --INFO--
 * Address:	800478D8
 * Size:	000074
 */
void DGXGraphics::videoReset()
{
	static int videoModeAsIs = -1;

	if (videoModeAsIs != _00) {
		videoModeAsIs = _00;
		sFirstFrame   = 2;
		VIConfigure(sScreenMode[_00]);
		VIFlush();
		VIWaitForRetrace();
		VIWaitForRetrace();
	}
}

/*
 * --INFO--
 * Address:	8004794C
 * Size:	000040
 */
void DGXGraphics::resetCopyFilter()
{
	GXSetCopyFilter(sScreenMode[_00]->aa, sScreenMode[_00]->sample_pattern, GX_TRUE, sScreenMode[_00]->vfilter);
}

/*
 * --INFO--
 * Address:	8004798C
 * Size:	000040
 */
void DGXGraphics::setupRender()
{
	_618 = VIGetRetraceCount();
	_3C8 = _3C4;
	_3CC = kDefaultDLSize;
}

/*
 * --INFO--
 * Address:	800479CC
 * Size:	000008
 */
u8* DGXGraphics::getDListPtr()
{
	return _3C8;
}

/*
 * --INFO--
 * Address:	800479D4
 * Size:	000008
 */
u32 DGXGraphics::getDListRemainSize()
{
	return _3CC;
}

/*
 * --INFO--
 * Address:	800479DC
 * Size:	00001C
 */
void DGXGraphics::useDList(u32 num)
{
	_3CC -= num;
	_3C8 += num;
}

/*
 * --INFO--
 * Address:	800479F8
 * Size:	0004C8
 */
u32 DGXGraphics::compileMaterial(Material* mat)
{
	if (!(mat->mFlags & 1)) {
		return 0;
	}

	gsys->_26C;
	u8* dl               = gsys->mGfx->getDListPtr();
	mat->mDisplayListPtr = dl;
	GXBeginDisplayList(dl, getDListRemainSize());

	if (mat->mPeInfo._00 & 1) {
		u32 data = mat->mPeInfo.mBlendModeFlags;
		GXSetBlendMode((GXBlendMode)(data & 0xf), (GXBlendFactor)(data >> 4 & 0xf), (GXBlendFactor)(data >> 8 & 0xf),
		               (GXLogicOp)(data >> 12 & 0xf));

		u32 data2 = mat->mPeInfo.mAlphaCompareFlags;
		GXSetAlphaCompare((GXCompare)(data2 & 0xf), (GXBlendFactor)(data2 >> 4 & 0xf), (GXAlphaOp)(data2 >> 16 & 0xf),
		                  (GXCompare)(data2 >> 20 & 0xf), (GXAlphaOp)(data2 >> 24 & 0xf));

		data2 = mat->mPeInfo.mDepthTestFlags;
		GXSetZMode(bool(data2 & 1), (GXCompare)(data2 >> 8), bool(data2 & 2));
	} else if (mat->mPeInfo._00 & 0x8000) {
		GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVSRCCOL, GX_LO_CLEAR);
		GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
	} else if (mat->mPeInfo._00 & 0x100) {
		GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_COPY);
		GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	} else if (mat->mPeInfo._00 & 0x200) {
		GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_COPY);
		GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_AND, GX_LEQUAL, 255);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	} else if (mat->mPeInfo._00 & 0x400) {
		GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
		GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
	}

	GXSetTevKColor(GX_KCOLOR0, *(GXColor*)((GXColor*)mat->mTevInfo + 27)); // this probably isnt right
	GXSetTevKColor(GX_KCOLOR1, *(GXColor*)((GXColor*)mat->mTevInfo + 28));
	GXSetTevKColor(GX_KCOLOR2, *(GXColor*)((GXColor*)mat->mTevInfo + 29));
	GXSetTevKColor(GX_KCOLOR3, *(GXColor*)((GXColor*)mat->mTevInfo + 30));
	for (int i = 0; i < mat->mTevInfo->mTevColRegs[0]._00.r; i++) { }
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x38(r1)

	  blrl
	  mr        r28, r3
	  stw       r28, 0x98(r31)
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0x18(r12)
	  mtlr      r12
	  blrl
	  addi      r4, r3, 0
	  addi      r3, r28, 0
	  bl        0x1CC684
	  lwz       r0, 0x58(r31)
	  rlwinm.   r0,r0,0,31,31
	  beq-      .loc_0xE0
	  lwz       r0, 0x64(r31)
	  rlwinm    r3,r0,0,28,31
	  rlwinm    r4,r0,28,28,31
	  rlwinm    r5,r0,24,28,31
	  rlwinm    r6,r0,20,28,31
	  bl        0x1CC1C4
	  lwz       r0, 0x5C(r31)
	  rlwinm    r3,r0,0,28,31
	  rlwinm    r4,r0,28,24,31
	  rlwinm    r5,r0,16,28,31
	  rlwinm    r6,r0,12,28,31
	  rlwinm    r7,r0,8,24,31
	  bl        0x1CBC4C
	  lwz       r6, 0x60(r31)
	  rlwinm    r0,r6,0,31,31
	  neg       r4, r0
	  subic     r3, r4, 0x1
	  rlwinm    r0,r6,0,30,30
	  subfe     r3, r3, r4
	  neg       r5, r0
	  subic     r0, r5, 0x1
	  rlwinm    r4,r6,24,24,31
	  subfe     r5, r0, r5
	  bl        0x1CC300
	  b         .loc_0x200

	.loc_0xE0:
	  lwz       r3, 0x18(r31)
	  rlwinm.   r0,r3,0,16,16
	  beq-      .loc_0x12C
	  li        r3, 0x1
	  li        r4, 0
	  li        r5, 0x3
	  li        r6, 0
	  bl        0x1CC158
	  li        r3, 0x7
	  li        r4, 0
	  li        r5, 0x1
	  li        r6, 0x7
	  li        r7, 0
	  bl        0x1CBBE4
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0
	  bl        0x1CC2B4
	  b         .loc_0x200

	.loc_0x12C:
	  rlwinm.   r0,r3,0,23,23
	  beq-      .loc_0x174
	  li        r3, 0
	  li        r4, 0x1
	  li        r5, 0
	  li        r6, 0x3
	  bl        0x1CC110
	  li        r3, 0x7
	  li        r4, 0
	  li        r5, 0x1
	  li        r6, 0x7
	  li        r7, 0
	  bl        0x1CBB9C
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0x1
	  bl        0x1CC26C
	  b         .loc_0x200

	.loc_0x174:
	  rlwinm.   r0,r3,0,22,22
	  beq-      .loc_0x1BC
	  li        r3, 0
	  li        r4, 0x1
	  li        r5, 0
	  li        r6, 0x3
	  bl        0x1CC0C8
	  li        r3, 0x6
	  li        r4, 0x80
	  li        r5, 0
	  li        r6, 0x3
	  li        r7, 0xFF
	  bl        0x1CBB54
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0x1
	  bl        0x1CC224
	  b         .loc_0x200

	.loc_0x1BC:
	  rlwinm.   r0,r3,0,21,21
	  beq-      .loc_0x200
	  li        r3, 0x1
	  li        r4, 0x4
	  li        r5, 0x5
	  li        r6, 0x3
	  bl        0x1CC080
	  li        r3, 0x7
	  li        r4, 0
	  li        r5, 0x1
	  li        r6, 0x7
	  li        r7, 0
	  bl        0x1CBB0C
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0
	  bl        0x1CC1DC

	.loc_0x200:
	  lwz       r3, 0x90(r31)
	  addi      r4, r1, 0x1C
	  lwz       r0, 0x6C(r3)
	  li        r3, 0
	  stw       r0, 0x1C(r1)
	  bl        0x1CB8A0
	  lwz       r3, 0x90(r31)
	  addi      r4, r1, 0x18
	  lwz       r0, 0x70(r3)
	  li        r3, 0x1
	  stw       r0, 0x18(r1)
	  bl        0x1CB888
	  lwz       r3, 0x90(r31)
	  addi      r4, r1, 0x14
	  lwz       r0, 0x74(r3)
	  li        r3, 0x2
	  stw       r0, 0x14(r1)
	  bl        0x1CB870
	  lwz       r3, 0x90(r31)
	  addi      r4, r1, 0x10
	  lwz       r0, 0x78(r3)
	  li        r3, 0x3
	  stw       r0, 0x10(r1)
	  bl        0x1CB858
	  li        r29, 0
	  li        r28, 0
	  b         .loc_0x2E4

	.loc_0x26C:
	  lwz       r0, 0x80(r3)
	  addi      r3, r29, 0
	  add       r30, r0, r28
	  lbz       r4, 0x6(r30)
	  lbz       r5, 0x7(r30)
	  lbz       r6, 0x8(r30)
	  lbz       r7, 0x9(r30)
	  bl        0x1CB4C0
	  lbz       r4, 0xA(r30)
	  mr        r3, r29
	  lbz       r5, 0xB(r30)
	  lbz       r6, 0xC(r30)
	  lbz       r7, 0xD(r30)
	  lbz       r8, 0xE(r30)
	  bl        0x1CB5A8
	  lbz       r4, 0x12(r30)
	  mr        r3, r29
	  lbz       r5, 0x13(r30)
	  lbz       r6, 0x14(r30)
	  lbz       r7, 0x15(r30)
	  bl        0x1CB50C
	  lbz       r4, 0x16(r30)
	  mr        r3, r29
	  lbz       r5, 0x17(r30)
	  lbz       r6, 0x18(r30)
	  lbz       r7, 0x19(r30)
	  lbz       r8, 0x1A(r30)
	  bl        0x1CB634
	  addi      r28, r28, 0x1E
	  addi      r29, r29, 0x1

	.loc_0x2E4:
	  lwz       r3, 0x90(r31)
	  lwz       r0, 0x7C(r3)
	  cmplw     r29, r0
	  blt+      .loc_0x26C
	  lwz       r0, 0x4C(r31)
	  addi      r30, r31, 0x4C
	  rlwinm    r0,r0,0,31,31
	  neg       r3, r0
	  subic     r0, r3, 0x1
	  subfe     r3, r0, r3
	  addic.    r0, r31, 0x4C
	  beq-      .loc_0x3F4
	  lwz       r0, 0x0(r30)
	  rlwinm    r3,r0,0,31,31
	  neg       r5, r3
	  subic     r4, r5, 0x1
	  subfe     r6, r4, r5
	  rlwinm    r3,r0,0,29,29
	  neg       r5, r3
	  subic     r4, r5, 0x1
	  subfe     r7, r4, r5
	  rlwinm    r3,r0,0,22,22
	  neg       r5, r3
	  subic     r4, r5, 0x1
	  rlwinm    r3,r0,0,21,21
	  subfe     r10, r4, r5
	  neg       r5, r3
	  subic     r4, r5, 0x1
	  subfe     r9, r4, r5
	  rlwinm    r3,r0,0,20,20
	  neg       r5, r3
	  rlwinm    r8,r7,0,24,31
	  addi      r26, r8, 0
	  subic     r4, r5, 0x1
	  rlwinm    r11,r6,0,24,31
	  subfe     r6, r4, r5
	  rlwinm    r3,r0,0,19,19
	  neg       r5, r3
	  subic     r4, r5, 0x1
	  subfe     r7, r4, r5
	  rlwinm.   r3,r11,0,24,31
	  addi      r4, r11, 0
	  rlwinm    r8,r0,29,30,31
	  rlwinm    r27,r0,27,30,31
	  rlwinm    r5,r10,0,24,31
	  rlwinm    r28,r9,0,24,31
	  rlwinm    r6,r6,0,24,31
	  rlwinm    r29,r7,0,24,31
	  bne-      .loc_0x3B0
	  li        r9, 0x2
	  b         .loc_0x3B4

	.loc_0x3B0:
	  li        r9, 0x1

	.loc_0x3B4:
	  li        r3, 0
	  li        r7, 0x3
	  bl        0x1CA16C
	  rlwinm.   r0,r26,0,24,31
	  bne-      .loc_0x3D0
	  li        r9, 0x2
	  b         .loc_0x3D4

	.loc_0x3D0:
	  li        r9, 0x1

	.loc_0x3D4:
	  addi      r4, r26, 0
	  addi      r5, r28, 0
	  addi      r6, r29, 0
	  addi      r8, r27, 0
	  li        r3, 0x2
	  li        r7, 0x3
	  bl        0x1CA13C
	  b         .loc_0x424

	.loc_0x3F4:
	  rlwinm.   r0,r3,0,24,31
	  addi      r4, r3, 0
	  bne-      .loc_0x408
	  li        r9, 0x2
	  b         .loc_0x40C

	.loc_0x408:
	  li        r9, 0x1

	.loc_0x40C:
	  li        r3, 0x4
	  li        r5, 0
	  li        r6, 0
	  li        r7, 0x3
	  li        r8, 0x2
	  bl        0x1CA108

	.loc_0x424:
	  cmplwi    r30, 0
	  li        r26, 0x1
	  beq-      .loc_0x484
	  lwz       r3, 0x0(r30)
	  rlwinm.   r0,r3,0,30,30
	  beq-      .loc_0x484
	  rlwinm    r8,r3,25,30,31
	  li        r3, 0x1
	  li        r4, 0x1
	  li        r5, 0
	  li        r6, 0
	  li        r7, 0x80
	  li        r9, 0
	  bl        0x1CA0D0
	  li        r3, 0x3
	  li        r4, 0
	  li        r5, 0
	  li        r6, 0
	  li        r7, 0x80
	  li        r8, 0x2
	  li        r9, 0x2
	  bl        0x1CA0B0
	  li        r26, 0x2
	  b         .loc_0x4A4

	.loc_0x484:
	  li        r3, 0x5
	  li        r4, 0
	  li        r5, 0
	  li        r6, 0
	  li        r7, 0
	  li        r8, 0
	  li        r9, 0x2
	  bl        0x1CA088

	.loc_0x4A4:
	  stw       r26, 0x50(r31)
	  bl        0x1CC310
	  stw       r3, 0x94(r31)
	  lwz       r3, 0x94(r31)

	.loc_0x4B4:
	  lmw       r26, 0x20(r1)
	  lwz       r0, 0x3C(r1)
	  addi      r1, r1, 0x38
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80047EC0
 * Size:	0001AC
 */
void DGXGraphics::initRender(int a1, int a2)
{
	frameNum++;
	Graphics::initRender(a1, a2);
	mLightIntensity = 1.0f;
	oldCull         = 0;
	GXSetCullMode(GX_CULL_BACK);
	GXSetCoPlanar(GX_FALSE);
	GXSetColorUpdate(GX_TRUE);
	GXSetDither(GX_FALSE);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
	GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	mDepthMode = 1;
	GXSetZCompLoc(GX_FALSE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
	mLineWidth = 1.0f;
	GXSetLineWidth(mLineWidth * 6.0f, GX_TO_ZERO);
	GXSetPointSize(24, GX_TO_ZERO);
	_324 = 0;
	_3D4 = 0;
	_334 = 0;
	useTexture(nullptr, 0);
	setMatHandler(nullptr);
	mRenderState      = 0x700;
	_3D8              = 0;
	_3DC              = 30;
	oldVerts          = 0;
	oldCols           = 0;
	oldNorms          = 0;
	oldTexs[0]        = 0;
	oldTexs[1]        = 0;
	oldTexs[2]        = 0;
	oldTexs[3]        = 0;
	oldTexs[4]        = 0;
	oldTexs[5]        = 0;
	oldTexs[6]        = 0;
	oldTexs[7]        = 0;
	mActiveTexture[0] = nullptr;
	mActiveTexture[1] = nullptr;
	mActiveTexture[2] = nullptr;
	mActiveTexture[3] = nullptr;
	mActiveTexture[4] = nullptr;
	mActiveTexture[5] = nullptr;
	mActiveTexture[6] = nullptr;
	mActiveTexture[7] = nullptr;
	_380              = 0;
	gsys->resetLFlares();
}

/*
 * --INFO--
 * Address:	8004806C
 * Size:	000038
 */
void DGXGraphics::beginRender()
{
	gsys->_26C; // volatile ints are very cool
	gsys->_26C = 1;
	GXInvalidateTexAll();
	GXInvalidateVtxCache();
}

/*
 * --INFO--
 * Address:	........
 * Size:	000084
 */
void DGXGraphics::GXReInit()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800480A4
 * Size:	000030
 */
void DGXGraphics::doneRender()
{
	GXFlush();
	GXDrawDone();
	gsys->_26C = 0;
}

/*
 * --INFO--
 * Address:	800480D4
 * Size:	0000C4
 */
void DGXGraphics::waitRetrace()
{
	waitPostRetrace();
	if (sFirstFrame) {
		sFirstFrame--;
		if (sFirstFrame == 0) {
			sFirstFrame = 0;
		}
	}
	VIFlush();
	VIWaitForRetrace();
	GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

	// this mess is probably an inline
	bool test = true;
	if (!gsys->_268 && !gsys->getPending()) {
		test = false;
	}
	bool set = test ? false : true;
	GXCopyDisp(_610, set);

	_618 = VIGetRetraceCount();
	_61C = gsys->mFrameRate;
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x18(r1)
	  stw       r31, 0x14(r1)
	  mr        r31, r3
	  bl        .loc_0xC4
	  lwz       r3, -0x7768(r13)
	  cmpwi     r3, 0
	  beq-      .loc_0x40
	  subi      r0, r3, 0x1
	  stw       r0, -0x7768(r13)
	  lwz       r0, -0x7768(r13)
	  cmpwi     r0, 0
	  bne-      .loc_0x40
	  li        r0, 0
	  stw       r0, -0x7768(r13)

	.loc_0x40:
	  bl        0x1BB7A8
	  bl        0x1BAC40
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0x1
	  bl        0x1CBCA8
	  lwz       r4, 0x2DEC(r13)
	  li        r3, 0x1
	  lwz       r0, 0x268(r4)
	  cmplwi    r0, 0
	  bne-      .loc_0x7C
	  lbz       r0, 0x0(r4)
	  cmplwi    r0, 0
	  bne-      .loc_0x7C
	  li        r3, 0

	.loc_0x7C:
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x8C
	  li        r0, 0
	  b         .loc_0x90

	.loc_0x8C:
	  li        r0, 0x1

	.loc_0x90:
	  mr        r4, r0
	  lwz       r3, 0x610(r31)
	  bl        0x1C94D8
	  bl        0x1BB950
	  stw       r3, 0x618(r31)
	  lwz       r3, 0x2DEC(r13)
	  lwz       r0, 0x14(r3)
	  stw       r0, 0x61C(r31)
	  lwz       r0, 0x1C(r1)
	  lwz       r31, 0x14(r1)
	  addi      r1, r1, 0x18
	  mtlr      r0
	  blr

	.loc_0xC4:
	*/
}

/*
 * --INFO--
 * Address:	80048198
 * Size:	000070
 */
void DGXGraphics::waitPostRetrace()
{
	BOOL interrupt = OSDisableInterrupts();

	int a = _61C - (VIGetRetraceCount() - _618) - 1;
	if (a > 0) {
		_614 = a;
		OSReceiveMessage(&_624, nullptr, 1);
	}

	OSRestoreInterrupts(interrupt);
}

/*
 * --INFO--
 * Address:	80048208
 * Size:	000084
 */
void DGXGraphics::retraceProc(u32)
{
	gsys->nudgeDvdThread();
	if (gsys->_260) {
		gsys->nudgeLoading();
		return;
	}

	gsys->_2A0++;
	if (gfx->_614 != 0 && --gfx->_614 == 0) {
		OSSendMessage(&gfx->_624, (OSMessage)'DONE', 0);
	}
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x8(r1)
	  lwz       r3, 0x2DEC(r13)
	  bl        -0x15B0
	  lwz       r3, 0x2DEC(r13)
	  lwz       r0, 0x260(r3)
	  cmplwi    r0, 0
	  beq-      .loc_0x2C
	  bl        -0x1C44
	  b         .loc_0x74

	.loc_0x2C:
	  lwz       r4, 0x2A0(r3)
	  addi      r0, r4, 0x1
	  stw       r0, 0x2A0(r3)
	  lwz       r3, 0x2E34(r13)
	  addi      r4, r3, 0x614
	  lwz       r0, 0x614(r3)
	  cmplwi    r0, 0
	  beq-      .loc_0x74
	  lwz       r3, 0x0(r4)
	  subic.    r0, r3, 0x1
	  stw       r0, 0x0(r4)
	  bne-      .loc_0x74
	  lwz       r5, 0x2E34(r13)
	  lis       r3, 0x444F
	  addi      r4, r3, 0x4E45
	  addi      r3, r5, 0x624
	  li        r5, 0
	  bl        0x1B159C

	.loc_0x74:
	  lwz       r0, 0xC(r1)
	  addi      r1, r1, 0x8
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004828C
 * Size:	000008
 */
void DGXGraphics::setCamera(Camera* a1)
{
	mCamera = a1;
}

/*
 * --INFO--
 * Address:	80048294
 * Size:	00002C
 */
void DGXGraphics::calcViewMatrix(Matrix4f& mtx1, Matrix4f& mtx2)
{
	mMatrix = &mtx1;
	mCamera->mLookAtMtx.multiplyTo(mtx1, mtx2);
}

/*
 * --INFO--
 * Address:	800482C0
 * Size:	000050
 */
f32 DGXGraphics::setLineWidth(f32 width)
{
	f32 old    = mLineWidth;
	mLineWidth = width;
	GXSetLineWidth(mLineWidth * 6.0f, GX_TO_ZERO);
	return old;
}

/*
 * --INFO--
 * Address:	80048310
 * Size:	00005C
 */
u8 DGXGraphics::setDepth(bool depth)
{
	u8 old     = mDepthMode;
	mDepthMode = depth;
	if (!depth) {
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
	} else {
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	}
	return old;
}

/*
 * --INFO--
 * Address:	8004836C
 * Size:	000078
 */
int DGXGraphics::setCullFront(int cull)
{
	mCullMode = cull;
	if (oldCull != mCullMode) {
		if (mCullMode == 1) {
			GXSetCullMode(GX_CULL_FRONT);
		} else if (mCullMode == 0) {
			GXSetCullMode(GX_CULL_BACK);
		} else {
			GXSetCullMode(GX_CULL_NONE);
		}
	}
	oldCull = mCullMode;
	return oldCull;
}

/*
 * --INFO--
 * Address:	800483E4
 * Size:	0000A0
 */
void DGXGraphics::setAmbient()
{
	GColors[1].r = mAmbientFogColour.r;
	GColors[1].g = mAmbientFogColour.g;
	GColors[1].b = mAmbientFogColour.b;
	GColors[1].a = f32(mAmbientFogColour.a) * mLightIntensity;

	GXSetChanAmbColor(GX_COLOR0A0, GColors[1]);
	GXSetChanMatColor(GX_COLOR1A1, GColors[0]);
}

/*
 * --INFO--
 * Address:	80048484
 * Size:	0001D0
 */
bool DGXGraphics::setLighting(bool, PVWLightingInfo*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x38(r1)
	  stmw      r25, 0x1C(r1)
	  mr.       r29, r5
	  addi      r28, r3, 0
	  lbz       r31, 0x320(r3)
	  stb       r4, 0x320(r3)
	  beq-      .loc_0x104
	  lwz       r0, 0x0(r29)
	  rlwinm    r3,r0,0,31,31
	  neg       r5, r3
	  subic     r4, r5, 0x1
	  subfe     r6, r4, r5
	  rlwinm    r3,r0,0,29,29
	  neg       r5, r3
	  subic     r4, r5, 0x1
	  subfe     r7, r4, r5
	  rlwinm    r3,r0,0,22,22
	  neg       r5, r3
	  subic     r4, r5, 0x1
	  rlwinm    r3,r0,0,21,21
	  subfe     r10, r4, r5
	  neg       r5, r3
	  subic     r4, r5, 0x1
	  subfe     r9, r4, r5
	  rlwinm    r3,r0,0,20,20
	  neg       r5, r3
	  rlwinm    r8,r7,0,24,31
	  addi      r30, r8, 0
	  subic     r4, r5, 0x1
	  rlwinm    r11,r6,0,24,31
	  subfe     r6, r4, r5
	  rlwinm    r3,r0,0,19,19
	  neg       r5, r3
	  subic     r4, r5, 0x1
	  subfe     r7, r4, r5
	  rlwinm.   r3,r11,0,24,31
	  addi      r4, r11, 0
	  rlwinm    r8,r0,29,30,31
	  rlwinm    r25,r0,27,30,31
	  rlwinm    r5,r10,0,24,31
	  rlwinm    r26,r9,0,24,31
	  rlwinm    r6,r6,0,24,31
	  rlwinm    r27,r7,0,24,31
	  bne-      .loc_0xC0
	  li        r9, 0x2
	  b         .loc_0xC4

	.loc_0xC0:
	  li        r9, 0x1

	.loc_0xC4:
	  lwz       r7, 0x378(r28)
	  li        r3, 0
	  bl        0x1C99D0
	  rlwinm.   r0,r30,0,24,31
	  bne-      .loc_0xE0
	  li        r9, 0x2
	  b         .loc_0xE4

	.loc_0xE0:
	  li        r9, 0x1

	.loc_0xE4:
	  lwz       r7, 0x378(r28)
	  addi      r4, r30, 0
	  addi      r5, r26, 0
	  addi      r6, r27, 0
	  addi      r8, r25, 0
	  li        r3, 0x2
	  bl        0x1C99A0
	  b         .loc_0x130

	.loc_0x104:
	  rlwinm.   r0,r4,0,24,31
	  bne-      .loc_0x114
	  li        r9, 0x2
	  b         .loc_0x118

	.loc_0x114:
	  li        r9, 0x1

	.loc_0x118:
	  lwz       r7, 0x378(r28)
	  li        r3, 0x4
	  li        r5, 0
	  li        r6, 0
	  li        r8, 0x2
	  bl        0x1C9970

	.loc_0x130:
	  cmplwi    r29, 0
	  li        r25, 0x1
	  beq-      .loc_0x190
	  lwz       r3, 0x0(r29)
	  rlwinm.   r0,r3,0,30,30
	  beq-      .loc_0x190
	  rlwinm    r8,r3,25,30,31
	  li        r3, 0x1
	  li        r4, 0x1
	  li        r5, 0
	  li        r6, 0
	  li        r7, 0x80
	  li        r9, 0
	  bl        0x1C9938
	  li        r3, 0x3
	  li        r4, 0
	  li        r5, 0
	  li        r6, 0
	  li        r7, 0x80
	  li        r8, 0x2
	  li        r9, 0x2
	  bl        0x1C9918
	  li        r25, 0x2
	  b         .loc_0x1B0

	.loc_0x190:
	  li        r3, 0x5
	  li        r4, 0
	  li        r5, 0
	  li        r6, 0
	  li        r7, 0
	  li        r8, 0
	  li        r9, 0x2
	  bl        0x1C98F0

	.loc_0x1B0:
	  rlwinm    r3,r25,0,24,31
	  bl        0x1C989C
	  mr        r3, r31
	  lmw       r25, 0x1C(r1)
	  lwz       r0, 0x3C(r1)
	  addi      r1, r1, 0x38
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80048654
 * Size:	000344
 */
void DGXGraphics::setLight(Light*, int)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x70(r1)
	  stw       r31, 0x6C(r1)
	  stw       r30, 0x68(r1)
	  addi      r30, r5, 0
	  rlwinm    r5,r5,6,0,25
	  stw       r29, 0x64(r1)
	  addi      r31, r5, 0x410
	  addi      r29, r4, 0
	  stw       r28, 0x60(r1)
	  addi      r28, r3, 0
	  add       r31, r28, r31
	  lwz       r7, 0x2DEC(r13)
	  mr        r3, r31
	  lwz       r6, 0x1C4(r7)
	  addi      r0, r6, 0x1
	  stw       r0, 0x1C4(r7)
	  lfs       f1, 0x38(r4)
	  lfs       f2, 0x3C(r4)
	  lfs       f3, 0x40(r4)
	  lfs       f4, 0x2C(r4)
	  lfs       f5, 0x30(r4)
	  lfs       f6, 0x34(r4)
	  bl        0x1C92C8
	  lfs       f0, 0x54(r29)
	  addi      r3, r1, 0x40
	  stfs      f0, 0x40(r1)
	  lfs       f0, 0x58(r29)
	  stfs      f0, 0x44(r1)
	  lfs       f0, 0x5C(r29)
	  stfs      f0, 0x48(r1)
	  lwz       r4, 0x2E4(r28)
	  addi      r4, r4, 0x1E0
	  bl        -0x10F90
	  lfs       f1, 0x40(r1)
	  mr        r3, r31
	  lfs       f2, 0x44(r1)
	  lfs       f3, 0x48(r1)
	  bl        0x1C92A8
	  lfs       f0, -0x7B58(r2)
	  stfs      f0, 0x3C(r1)
	  stfs      f0, 0x38(r1)
	  stfs      f0, 0x34(r1)
	  lwz       r0, 0x14(r29)
	  rlwinm    r0,r0,0,24,31
	  cmpwi     r0, 0x3
	  bne-      .loc_0x154
	  lwz       r3, 0x60(r29)
	  lwz       r0, 0x64(r29)
	  stw       r3, 0x34(r1)
	  stw       r0, 0x38(r1)
	  lwz       r0, 0x68(r29)
	  stw       r0, 0x3C(r1)
	  lfs       f1, 0x34(r1)
	  lfs       f0, 0x38(r1)
	  lfs       f2, 0x3C(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0x3AB0C
	  lfs       f0, -0x7B58(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x12C
	  lfs       f0, 0x34(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x34(r1)
	  lfs       f0, 0x38(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x38(r1)
	  lfs       f0, 0x3C(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x3C(r1)

	.loc_0x12C:
	  lwz       r4, 0x2E4(r28)
	  addi      r3, r1, 0x34
	  addi      r4, r4, 0x1E0
	  bl        -0x11180
	  lfs       f1, 0x34(r1)
	  mr        r3, r31
	  lfs       f2, 0x38(r1)
	  lfs       f3, 0x3C(r1)
	  bl        0x1C9208
	  b         .loc_0x1EC

	.loc_0x154:
	  cmpwi     r0, 0x1
	  bne-      .loc_0x1EC
	  lwz       r3, 0x54(r29)
	  lwz       r0, 0x58(r29)
	  stw       r3, 0x34(r1)
	  stw       r0, 0x38(r1)
	  lwz       r0, 0x5C(r29)
	  stw       r0, 0x3C(r1)
	  lfs       f1, 0x34(r1)
	  lfs       f0, 0x38(r1)
	  lfs       f2, 0x3C(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0x3ABA8
	  lfs       f0, -0x7B58(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x1C8
	  lfs       f0, 0x34(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x34(r1)
	  lfs       f0, 0x38(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x38(r1)
	  lfs       f0, 0x3C(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x3C(r1)

	.loc_0x1C8:
	  lwz       r4, 0x2E4(r28)
	  addi      r3, r1, 0x34
	  addi      r4, r4, 0x1E0
	  bl        -0x1121C
	  lfs       f1, 0x34(r1)
	  mr        r3, r31
	  lfs       f2, 0x38(r1)
	  lfs       f3, 0x3C(r1)
	  bl        0x1C916C

	.loc_0x1EC:
	  lbz       r0, 0x6C(r29)
	  cmpwi     r30, 0x7
	  stb       r0, 0x30(r1)
	  lbz       r0, 0x6D(r29)
	  stb       r0, 0x31(r1)
	  lbz       r0, 0x6E(r29)
	  stb       r0, 0x32(r1)
	  lbz       r0, 0x6F(r29)
	  stb       r0, 0x33(r1)
	  bne-      .loc_0x2CC
	  lwz       r3, 0x60(r29)
	  lwz       r0, 0x64(r29)
	  stw       r3, 0x34(r1)
	  stw       r0, 0x38(r1)
	  lwz       r0, 0x68(r29)
	  stw       r0, 0x3C(r1)
	  lfs       f1, 0x34(r1)
	  lfs       f0, 0x38(r1)
	  lfs       f2, 0x3C(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0x3AC60
	  lfs       f0, -0x7B58(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x280
	  lfs       f0, 0x34(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x34(r1)
	  lfs       f0, 0x38(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x38(r1)
	  lfs       f0, 0x3C(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x3C(r1)

	.loc_0x280:
	  lwz       r4, 0x2E4(r28)
	  addi      r3, r1, 0x34
	  addi      r4, r4, 0x1E0
	  bl        -0x112D4
	  lfs       f1, 0x34(r1)
	  mr        r3, r31
	  lfs       f2, 0x38(r1)
	  lfs       f3, 0x3C(r1)
	  bl        0x1C90D0
	  lfs       f2, 0x370(r28)
	  mr        r3, r31
	  lfs       f0, -0x7B54(r2)
	  lfs       f1, -0x7B58(r2)
	  fmuls     f4, f2, f0
	  lfs       f3, -0x7B60(r2)
	  fmr       f2, f1
	  fmr       f5, f1
	  fsubs     f6, f3, f4
	  bl        0x1C9060

	.loc_0x2CC:
	  lbz       r3, 0x33(r1)
	  lis       r0, 0x4330
	  lfd       f2, -0x7B68(r2)
	  addi      r4, r1, 0x2C
	  stw       r3, 0x5C(r1)
	  lfs       f0, 0x374(r28)
	  mr        r3, r31
	  stw       r0, 0x58(r1)
	  lfd       f1, 0x58(r1)
	  fsubs     f1, f1, f2
	  fmuls     f0, f1, f0
	  fctiwz    f0, f0
	  stfd      f0, 0x50(r1)
	  lwz       r0, 0x54(r1)
	  stb       r0, 0x33(r1)
	  lwz       r0, 0x30(r1)
	  stw       r0, 0x2C(r1)
	  bl        0x1C9134
	  li        r0, 0x1
	  addi      r3, r31, 0
	  slw       r4, r0, r30
	  bl        0x1C914C
	  lwz       r0, 0x74(r1)
	  lwz       r31, 0x6C(r1)
	  lwz       r30, 0x68(r1)
	  lwz       r29, 0x64(r1)
	  lwz       r28, 0x60(r1)
	  addi      r1, r1, 0x70
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80048998
 * Size:	000098
 */
void DGXGraphics::setPerspective(Mtx mtx, f32 a1, f32 a2, f32 a3, f32 a4, f32 a5)
{
	MTXPerspective(mtx, a1, a2, a3, a4);
	GXSetProjection(mtx, GX_PERSPECTIVE);
	f32 a     = 1.0f / (a4 - a3);
	mtx[2][2] = a * -(a4 + a3);
	mtx[2][3] = a * -(a4 * 2.0f * a3);
	GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
}

/*
 * --INFO--
 * Address:	80048A30
 * Size:	00019C
 */
void DGXGraphics::setOrthogonal(Mtx mtx, RectArea& bounds)
{
	MTXOrtho(mtx, bounds.mMinY, bounds.mMaxY, bounds.mMinX, bounds.mMaxX, 0.0f, -1.0f);
	GXSetProjection(mtx, GX_ORTHOGRAPHIC);
	GXLoadPosMtxImm(Matrix4f::ident.mMtx, 0);
	GXSetCurrentMtx(0);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 1, GX_DF_NONE, GX_AF_NONE);
	GXSetNumChans(1);
	GXSetZMode(GX_FALSE, GX_LEQUAL, GX_TRUE);
	setScissor(bounds);
	setViewport(bounds);
	GXSetNumTexGens(1);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3X4, GX_TG_TEX0, 0x3c, 0, 0x7d);
	useTexture(nullptr, 0);
	setFog(false);
}

/*
 * --INFO--
 * Address:	80048BCC
 * Size:	00003C
 */
void DGXGraphics::setScissor(RectArea& bounds)
{
	GXSetScissor(bounds.mMinX, bounds.mMinY, bounds.mMaxX - bounds.mMinX, bounds.mMaxY - bounds.mMinY);
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x8(r1)
	  lwz       r3, 0x0(r4)
	  lwz       r0, 0x8(r4)
	  lwz       r7, 0x4(r4)
	  lwz       r6, 0xC(r4)
	  sub       r5, r0, r3
	  addi      r4, r7, 0
	  sub       r6, r6, r7
	  bl        0x1CBADC
	  lwz       r0, 0xC(r1)
	  addi      r1, r1, 0x8
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80048C08
 * Size:	000098
 */
void DGXGraphics::setViewport(RectArea& bounds)
{
	GXSetViewport(bounds.mMinX, bounds.mMinY, bounds.mMaxX - bounds.mMinX, bounds.mMaxY - bounds.mMinY, 0.0f, 1.0f);

	/*
	.loc_0x0:
	  mflr      r0
	  lis       r6, 0x4330
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x30(r1)
	  lwz       r7, 0x4(r4)
	  lwz       r0, 0xC(r4)
	  xoris     r5, r7, 0x8000
	  lwz       r8, 0x0(r4)
	  lwz       r3, 0x8(r4)
	  sub       r4, r0, r7
	  xoris     r0, r8, 0x8000
	  stw       r5, 0x24(r1)
	  sub       r3, r3, r8
	  stw       r0, 0x2C(r1)
	  xoris     r3, r3, 0x8000
	  xoris     r0, r4, 0x8000
	  lfd       f4, -0x7B48(r2)
	  stw       r3, 0x1C(r1)
	  lfs       f5, -0x7B58(r2)
	  stw       r0, 0x14(r1)
	  lfs       f6, -0x7B60(r2)
	  stw       r6, 0x20(r1)
	  stw       r6, 0x28(r1)
	  lfd       f0, 0x20(r1)
	  stw       r6, 0x18(r1)
	  lfd       f1, 0x28(r1)
	  fsubs     f2, f0, f4
	  stw       r6, 0x10(r1)
	  lfd       f3, 0x18(r1)
	  fsubs     f1, f1, f4
	  lfd       f0, 0x10(r1)
	  fsubs     f3, f3, f4
	  fsubs     f4, f0, f4
	  bl        0x1CBA20
	  lwz       r0, 0x34(r1)
	  addi      r1, r1, 0x30
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80048CA0
 * Size:	000030
 */
void DGXGraphics::setViewportOffset(RectArea& bounds)
{
	GXSetScissorBoxOffset(-bounds.mMinX, -bounds.mMinY);
}

/*
 * --INFO--
 * Address:	80048CD0
 * Size:	000004
 */
void DGXGraphics::initReflectTex(bool)
{
}

/*
 * --INFO--
 * Address:	80048CD4
 * Size:	0000D0
 */
void DGXGraphics::initProjTex(bool set, LightCamera* cam)
{
	f32 badcompiler[0x3c];
	if (set) {
		MTXLightPerspective(_3E0.mMtx, cam->mFov, cam->mAspectRatio, cam->mProjectionScale.x, -cam->mProjectionScale.y, 0.5f, 0.5f);
		Matrix4f mtx;
		PSMTXConcat(_3E0.mMtx, cam->mLookAtMtx.mMtx, _3E0.mMtx);
		PSMTXConcat(_3E0.mMtx, Matrix4f::ident.mMtx, mtx.mMtx);
		GXLoadTexMtxImm(mtx.mMtx, 30, GX_MTX3x4);
		GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_POS, 30, GX_FALSE, 125);
	} else {
		GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3X4, GX_TG_TEX0, 60, GX_FALSE, 125);
	}

	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  rlwinm.   r0,r4,0,24,31
	  stwu      r1, -0x150(r1)
	  stw       r31, 0x14C(r1)
	  addi      r31, r5, 0
	  stw       r30, 0x148(r1)
	  addi      r30, r3, 0
	  beq-      .loc_0x9C
	  lfs       f0, 0x360(r31)
	  addi      r3, r30, 0x3E0
	  lfs       f5, -0x7B54(r2)
	  fneg      f4, f0
	  lfs       f1, 0x1CC(r31)
	  fmr       f6, f5
	  lfs       f2, 0x1C4(r31)
	  lfs       f3, 0x35C(r31)
	  bl        0x1B513C
	  addi      r3, r30, 0x3E0
	  addi      r4, r31, 0x1E0
	  addi      r5, r3, 0
	  bl        0x1B4E98
	  lis       r3, 0x803A
	  subi      r4, r3, 0x77C0
	  addi      r3, r30, 0x3E0
	  addi      r5, r1, 0x14
	  bl        0x1B4E84
	  addi      r3, r1, 0x14
	  li        r4, 0x1E
	  li        r5, 0
	  bl        0x1CB7C0
	  li        r3, 0
	  li        r4, 0
	  li        r5, 0
	  li        r6, 0x1E
	  li        r7, 0
	  li        r8, 0x7D
	  bl        0x1C76F0
	  b         .loc_0xB8

	.loc_0x9C:
	  li        r3, 0
	  li        r4, 0x1
	  li        r5, 0x4
	  li        r6, 0x3C
	  li        r7, 0
	  li        r8, 0x7D
	  bl        0x1C76D0

	.loc_0xB8:
	  lwz       r0, 0x154(r1)
	  lwz       r31, 0x14C(r1)
	  lwz       r30, 0x148(r1)
	  addi      r1, r1, 0x150
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80048DA4
 * Size:	000168
 */
void DGXGraphics::useMatrixQuick(Matrix4f&, int)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x150(r1)
	  stw       r31, 0x14C(r1)
	  mulli     r31, r5, 0x3
	  stw       r30, 0x148(r1)
	  addi      r30, r4, 0
	  stw       r29, 0x144(r1)
	  addi      r29, r3, 0
	  addi      r4, r31, 0
	  stw       r30, 0xC(r3)
	  addi      r3, r30, 0
	  bl        0x1CB680
	  lwz       r4, 0x380(r29)
	  cmplwi    r4, 0
	  beq-      .loc_0x8C
	  lfs       f1, 0x0(r4)
	  addi      r3, r1, 0x110
	  lfs       f2, 0x4(r4)
	  lfs       f3, 0x8(r4)
	  bl        0x1B5028
	  addi      r3, r30, 0
	  addi      r4, r1, 0x80
	  bl        0x1B4EDC
	  addi      r3, r1, 0x80
	  addi      r4, r1, 0xE0
	  bl        0x1B4E80
	  addi      r3, r1, 0xE0
	  addi      r4, r1, 0x110
	  addi      r5, r1, 0xB0
	  bl        0x1B4DA4
	  addi      r3, r1, 0xB0
	  addi      r4, r31, 0
	  bl        0x1CB668
	  b         .loc_0x98

	.loc_0x8C:
	  addi      r3, r30, 0
	  addi      r4, r31, 0
	  bl        0x1CB658

	.loc_0x98:
	  lwz       r0, 0x338(r29)
	  cmplwi    r0, 0
	  beq-      .loc_0xCC
	  lis       r3, 0x803A
	  subi      r4, r3, 0x77C0
	  addi      r3, r29, 0x3E0
	  addi      r5, r1, 0x50
	  bl        0x1B4D68
	  addi      r3, r1, 0x50
	  li        r4, 0x1E
	  li        r5, 0
	  bl        0x1CB6A4
	  b         .loc_0x14C

	.loc_0xCC:
	  lwz       r0, 0x324(r29)
	  cmpwi     r0, 0
	  beq-      .loc_0x14C
	  mr        r3, r30
	  bl        0x1B5224
	  lfs       f2, -0x7B54(r2)
	  addi      r3, r1, 0x20
	  lfs       f0, 0x0(r30)
	  li        r5, 0x1
	  fdivs     f1, f2, f1
	  fmuls     f0, f1, f0
	  stfs      f0, 0x20(r1)
	  lfs       f0, 0x4(r30)
	  fmuls     f0, f1, f0
	  stfs      f0, 0x24(r1)
	  lfs       f0, 0x8(r30)
	  fmuls     f0, f1, f0
	  stfs      f0, 0x28(r1)
	  stfs      f2, 0x2C(r1)
	  lfs       f0, 0x10(r30)
	  fmuls     f0, f1, f0
	  stfs      f0, 0x30(r1)
	  lfs       f0, 0x14(r30)
	  fmuls     f0, f1, f0
	  stfs      f0, 0x34(r1)
	  lfs       f0, 0x18(r30)
	  fmuls     f0, f1, f0
	  stfs      f0, 0x38(r1)
	  stfs      f2, 0x3C(r1)
	  lwz       r0, 0x3DC(r29)
	  add       r4, r0, r31
	  bl        0x1CB620

	.loc_0x14C:
	  lwz       r0, 0x154(r1)
	  lwz       r31, 0x14C(r1)
	  lwz       r30, 0x148(r1)
	  lwz       r29, 0x144(r1)
	  addi      r1, r1, 0x150
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80048F0C
 * Size:	000054
 */
void DGXGraphics::useMatrix(Matrix4f& mtx, int a)
{
	useMatrixQuick(mtx, a);
	_3D8 = a * 3;
	GXSetCurrentMtx(_3D8);
}

/*
 * --INFO--
 * Address:	80048F60
 * Size:	0000F8
 */
void DGXGraphics::useTexture(Texture* texture, int id)
{
	_324 = 0;
	if (!texture || texture != mActiveTexture[id]) {
		if (texture) {
			texture->makeResident();
			GXLoadTexObj(texture->mTexObj, (GXTexMapID)id);
			GXSetNumTexGens(1);
			GXSetNumTevStages(1);
			GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
			GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		} else {
			GXSetNumTexGens(0);
			GXSetNumTevStages(1);
			GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
			GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
		}
		mActiveTexture[id] = texture;
	}
}

/*
 * --INFO--
 * Address:	80049058
 * Size:	000148
 */
void DGXGraphics::setMatMatrices(Material*, int)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x38(r1)
	  stmw      r25, 0x1C(r1)
	  mr        r26, r4
	  addi      r25, r3, 0
	  addi      r27, r5, 0
	  lwz       r0, 0x80(r4)
	  cmplwi    r0, 0
	  beq-      .loc_0x30
	  li        r0, 0x1
	  b         .loc_0x34

	.loc_0x30:
	  li        r0, 0

	.loc_0x34:
	  rlwinm    r0,r0,0,24,31
	  stw       r0, 0x324(r25)
	  lwz       r0, 0x78(r26)
	  rlwinm    r3,r0,0,24,31
	  bl        0x1C768C
	  li        r31, 0
	  addi      r30, r31, 0
	  li        r29, 0x1E
	  li        r28, 0
	  b         .loc_0x128

	.loc_0x5C:
	  lwz       r0, 0x88(r26)
	  add       r3, r0, r31
	  lbz       r0, 0x3(r3)
	  cmplwi    r0, 0xA
	  beq-      .loc_0x78
	  mr        r6, r29
	  b         .loc_0x7C

	.loc_0x78:
	  li        r6, 0x3C

	.loc_0x7C:
	  lbz       r5, 0x2(r3)
	  li        r7, 0
	  lbz       r4, 0x1(r3)
	  li        r8, 0x7D
	  lbz       r3, 0x0(r3)
	  bl        0x1C7370
	  lwz       r3, 0x88(r26)
	  addi      r0, r31, 0x1
	  lbzx      r0, r3, r0
	  cmplwi    r0, 0x1
	  bne-      .loc_0x120
	  lwz       r0, 0x84(r26)
	  add       r3, r0, r30
	  lbz       r0, 0x14(r3)
	  cmpwi     r0, 0xFF
	  beq-      .loc_0x11C
	  cmpwi     r0, 0xA
	  beq-      .loc_0xCC
	  mr        r0, r29
	  b         .loc_0xD0

	.loc_0xCC:
	  li        r0, 0x3C

	.loc_0xD0:
	  mr        r4, r0
	  addi      r3, r3, 0x5C
	  li        r5, 0x1
	  bl        0x1CB3D8
	  lwz       r0, 0x324(r25)
	  cmpwi     r0, 0
	  beq-      .loc_0x118
	  lwz       r3, 0x88(r26)
	  addi      r0, r31, 0x2
	  lbzx      r0, r3, r0
	  cmplwi    r0, 0x1
	  bne-      .loc_0x118
	  stw       r29, 0x3DC(r25)
	  lwz       r0, 0x80(r26)
	  mullw     r0, r0, r27
	  mulli     r0, r0, 0x3
	  add       r29, r29, r0
	  b         .loc_0x11C

	.loc_0x118:
	  addi      r29, r29, 0x3

	.loc_0x11C:
	  addi      r30, r30, 0x9C

	.loc_0x120:
	  addi      r31, r31, 0x4
	  addi      r28, r28, 0x1

	.loc_0x128:
	  lwz       r0, 0x78(r26)
	  cmplw     r28, r0
	  blt+      .loc_0x5C
	  lmw       r25, 0x1C(r1)
	  lwz       r0, 0x3C(r1)
	  addi      r1, r1, 0x38
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800491A0
 * Size:	000864
 */
void DGXGraphics::setMaterial(Material*, bool)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x98(r1)
	  stmw      r27, 0x84(r1)
	  mr.       r31, r4
	  addi      r30, r3, 0
	  beq-      .loc_0x7C8
	  lwz       r4, 0x2DEC(r13)
	  lwz       r3, 0x1A8(r4)
	  addi      r0, r3, 0x1
	  stw       r0, 0x1A8(r4)
	  lwz       r4, 0x18(r31)
	  rlwinm.   r0,r4,0,31,31
	  beq-      .loc_0x4DC
	  lwz       r3, 0x98(r31)
	  cmplwi    r3, 0
	  beq-      .loc_0x5C
	  lwz       r4, 0x94(r31)
	  bl        0x1CB09C
	  lwz       r0, 0x50(r31)
	  rlwinm    r3,r0,0,24,31
	  bl        0x1C8CE0
	  b         .loc_0x318

	.loc_0x5C:
	  lwz       r0, 0x58(r31)
	  rlwinm.   r0,r0,0,31,31
	  beq-      .loc_0xCC
	  lwz       r0, 0x64(r31)
	  rlwinm    r3,r0,0,28,31
	  rlwinm    r4,r0,28,28,31
	  rlwinm    r5,r0,24,28,31
	  rlwinm    r6,r0,20,28,31
	  bl        0x1CAA30
	  lwz       r0, 0x5C(r31)
	  rlwinm    r3,r0,0,28,31
	  rlwinm    r4,r0,28,24,31
	  rlwinm    r5,r0,16,28,31
	  rlwinm    r6,r0,12,28,31
	  rlwinm    r7,r0,8,24,31
	  bl        0x1CA4B8
	  lwz       r6, 0x60(r31)
	  rlwinm    r0,r6,0,31,31
	  neg       r4, r0
	  subic     r3, r4, 0x1
	  rlwinm    r0,r6,0,30,30
	  subfe     r3, r3, r4
	  neg       r5, r0
	  subic     r0, r5, 0x1
	  rlwinm    r4,r6,24,24,31
	  subfe     r5, r0, r5
	  bl        0x1CAB6C
	  b         .loc_0x1E8

	.loc_0xCC:
	  rlwinm.   r0,r4,0,16,16
	  beq-      .loc_0x114
	  li        r3, 0x1
	  li        r4, 0
	  li        r5, 0x3
	  li        r6, 0
	  bl        0x1CA9C8
	  li        r3, 0x7
	  li        r4, 0
	  li        r5, 0x1
	  li        r6, 0x7
	  li        r7, 0
	  bl        0x1CA454
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0
	  bl        0x1CAB24
	  b         .loc_0x1E8

	.loc_0x114:
	  rlwinm.   r0,r4,0,23,23
	  beq-      .loc_0x15C
	  li        r3, 0
	  li        r4, 0x1
	  li        r5, 0
	  li        r6, 0x3
	  bl        0x1CA980
	  li        r3, 0x7
	  li        r4, 0
	  li        r5, 0x1
	  li        r6, 0x7
	  li        r7, 0
	  bl        0x1CA40C
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0x1
	  bl        0x1CAADC
	  b         .loc_0x1E8

	.loc_0x15C:
	  rlwinm.   r0,r4,0,22,22
	  beq-      .loc_0x1A4
	  li        r3, 0
	  li        r4, 0x1
	  li        r5, 0
	  li        r6, 0x3
	  bl        0x1CA938
	  li        r3, 0x6
	  li        r4, 0x80
	  li        r5, 0
	  li        r6, 0x3
	  li        r7, 0xFF
	  bl        0x1CA3C4
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0x1
	  bl        0x1CAA94
	  b         .loc_0x1E8

	.loc_0x1A4:
	  rlwinm.   r0,r4,0,21,21
	  beq-      .loc_0x1E8
	  li        r3, 0x1
	  li        r4, 0x4
	  li        r5, 0x5
	  li        r6, 0x3
	  bl        0x1CA8F0
	  li        r3, 0x7
	  li        r4, 0
	  li        r5, 0x1
	  li        r6, 0x7
	  li        r7, 0
	  bl        0x1CA37C
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0
	  bl        0x1CAA4C

	.loc_0x1E8:
	  lwz       r3, 0x90(r31)
	  addi      r4, r1, 0x64
	  lwz       r0, 0x6C(r3)
	  li        r3, 0
	  stw       r0, 0x64(r1)
	  bl        0x1CA110
	  lwz       r3, 0x90(r31)
	  addi      r4, r1, 0x60
	  lwz       r0, 0x70(r3)
	  li        r3, 0x1
	  stw       r0, 0x60(r1)
	  bl        0x1CA0F8
	  lwz       r3, 0x90(r31)
	  addi      r4, r1, 0x5C
	  lwz       r0, 0x74(r3)
	  li        r3, 0x2
	  stw       r0, 0x5C(r1)
	  bl        0x1CA0E0
	  lwz       r3, 0x90(r31)
	  addi      r4, r1, 0x58
	  lwz       r0, 0x78(r3)
	  li        r3, 0x3
	  stw       r0, 0x58(r1)
	  bl        0x1CA0C8
	  li        r28, 0
	  li        r29, 0
	  b         .loc_0x2CC

	.loc_0x254:
	  lwz       r0, 0x80(r3)
	  addi      r3, r28, 0
	  add       r27, r0, r29
	  lbz       r4, 0x6(r27)
	  lbz       r5, 0x7(r27)
	  lbz       r6, 0x8(r27)
	  lbz       r7, 0x9(r27)
	  bl        0x1C9D30
	  lbz       r4, 0xA(r27)
	  mr        r3, r28
	  lbz       r5, 0xB(r27)
	  lbz       r6, 0xC(r27)
	  lbz       r7, 0xD(r27)
	  lbz       r8, 0xE(r27)
	  bl        0x1C9E18
	  lbz       r4, 0x12(r27)
	  mr        r3, r28
	  lbz       r5, 0x13(r27)
	  lbz       r6, 0x14(r27)
	  lbz       r7, 0x15(r27)
	  bl        0x1C9D7C
	  lbz       r4, 0x16(r27)
	  mr        r3, r28
	  lbz       r5, 0x17(r27)
	  lbz       r6, 0x18(r27)
	  lbz       r7, 0x19(r27)
	  lbz       r8, 0x1A(r27)
	  bl        0x1C9EA4
	  addi      r29, r29, 0x1E
	  addi      r28, r28, 0x1

	.loc_0x2CC:
	  lwz       r3, 0x90(r31)
	  lwz       r0, 0x7C(r3)
	  cmplw     r28, r0
	  blt+      .loc_0x254
	  lwz       r6, 0x2DEC(r13)
	  addi      r3, r30, 0
	  addi      r5, r31, 0x4C
	  lwz       r4, 0x1C0(r6)
	  addi      r0, r4, 0x1
	  stw       r0, 0x1C0(r6)
	  lwz       r0, 0x4C(r31)
	  lwz       r12, 0x3B4(r30)
	  rlwinm    r0,r0,0,31,31
	  lwz       r12, 0x30(r12)
	  neg       r4, r0
	  subic     r0, r4, 0x1
	  mtlr      r12
	  subfe     r4, r0, r4
	  blrl

	.loc_0x318:
	  addi      r28, r30, 0
	  li        r27, 0
	  li        r29, 0
	  b         .loc_0x374

	.loc_0x328:
	  lwz       r4, 0x84(r31)
	  addi      r3, r29, 0x8
	  lwz       r0, 0x2E8(r28)
	  lwzx      r3, r4, r3
	  cmplw     r3, r0
	  beq-      .loc_0x368
	  stw       r3, 0x2E8(r28)
	  lwz       r3, 0x2E8(r28)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x10(r12)
	  mtlr      r12
	  blrl
	  lwz       r3, 0x2E8(r28)
	  mr        r4, r27
	  lwz       r3, 0x24(r3)
	  bl        0x1C9260

	.loc_0x368:
	  addi      r29, r29, 0x9C
	  addi      r28, r28, 0x4
	  addi      r27, r27, 0x1

	.loc_0x374:
	  lwz       r0, 0x74(r31)
	  cmplw     r27, r0
	  blt+      .loc_0x328
	  lwz       r6, 0x90(r31)
	  addi      r4, r1, 0x50
	  li        r3, 0x1
	  lwz       r5, 0x0(r6)
	  lwz       r0, 0x4(r6)
	  stw       r5, 0x50(r1)
	  stw       r0, 0x54(r1)
	  bl        0x1C9EFC
	  lwz       r6, 0x90(r31)
	  addi      r4, r1, 0x48
	  li        r3, 0x2
	  lwz       r5, 0x24(r6)
	  lwz       r0, 0x28(r6)
	  stw       r5, 0x48(r1)
	  stw       r0, 0x4C(r1)
	  bl        0x1C9EDC
	  lwz       r6, 0x90(r31)
	  addi      r4, r1, 0x40
	  li        r3, 0x3
	  lwz       r5, 0x48(r6)
	  lwz       r0, 0x4C(r6)
	  stw       r5, 0x40(r1)
	  stw       r0, 0x44(r1)
	  bl        0x1C9EBC
	  lwz       r3, 0x90(r31)
	  lwz       r0, 0x7C(r3)
	  rlwinm    r3,r0,0,24,31
	  bl        0x1CA3D8
	  li        r27, 0
	  li        r28, 0
	  b         .loc_0x438

	.loc_0x3FC:
	  lwz       r0, 0x80(r3)
	  addi      r3, r27, 0
	  add       r29, r0, r28
	  lbz       r4, 0x1(r29)
	  lbz       r5, 0x2(r29)
	  lbz       r6, 0x3(r29)
	  bl        0x1CA210
	  mr        r3, r27
	  lbz       r4, 0x4(r29)
	  bl        0x1C9F60
	  mr        r3, r27
	  lbz       r4, 0x5(r29)
	  bl        0x1C9FC0
	  addi      r28, r28, 0x1E
	  addi      r27, r27, 0x1

	.loc_0x438:
	  lwz       r3, 0x90(r31)
	  lwz       r0, 0x7C(r3)
	  cmplw     r27, r0
	  blt+      .loc_0x3FC
	  lbz       r3, 0x2F(r31)
	  lis       r0, 0x4330
	  lfd       f1, -0x7B68(r2)
	  addi      r4, r1, 0x3C
	  stw       r3, 0x7C(r1)
	  lfs       f2, 0x374(r30)
	  li        r3, 0x4
	  stw       r0, 0x78(r1)
	  lbz       r6, 0x2E(r31)
	  lfd       f0, 0x78(r1)
	  lbz       r5, 0x2D(r31)
	  fsubs     f0, f0, f1
	  lbz       r0, 0x2C(r31)
	  stb       r0, 0x6C(r1)
	  fmuls     f0, f2, f0
	  stb       r5, 0x6D(r1)
	  fctiwz    f0, f0
	  stb       r6, 0x6E(r1)
	  stfd      f0, 0x70(r1)
	  lwz       r0, 0x74(r1)
	  stb       r0, 0x6F(r1)
	  lwz       r0, 0x6C(r1)
	  stw       r0, 0x3C(r1)
	  bl        0x1C8728
	  lwz       r0, 0x7C(r31)
	  cmplwi    r0, 0
	  beq-      .loc_0x4C0
	  addi      r0, r31, 0x68
	  stw       r0, 0x380(r30)
	  b         .loc_0x4C8

	.loc_0x4C0:
	  li        r0, 0
	  stw       r0, 0x380(r30)

	.loc_0x4C8:
	  lwz       r5, 0x328(r30)
	  addi      r3, r30, 0
	  addi      r4, r31, 0
	  bl        -0x61C
	  b         .loc_0x850

	.loc_0x4DC:
	  li        r0, 0
	  stw       r0, 0x380(r30)
	  lwz       r3, 0x18(r31)
	  rlwinm.   r0,r3,0,16,16
	  beq-      .loc_0x530
	  li        r3, 0x1
	  li        r4, 0
	  li        r5, 0x3
	  li        r6, 0
	  bl        0x1CA5AC
	  li        r3, 0x7
	  li        r4, 0
	  li        r5, 0x1
	  li        r6, 0x7
	  li        r7, 0
	  bl        0x1CA038
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0
	  bl        0x1CA708
	  b         .loc_0x604

	.loc_0x530:
	  rlwinm.   r0,r3,0,23,23
	  beq-      .loc_0x578
	  li        r3, 0
	  li        r4, 0x1
	  li        r5, 0
	  li        r6, 0x3
	  bl        0x1CA564
	  li        r3, 0x7
	  li        r4, 0
	  li        r5, 0x1
	  li        r6, 0x7
	  li        r7, 0
	  bl        0x1C9FF0
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0x1
	  bl        0x1CA6C0
	  b         .loc_0x604

	.loc_0x578:
	  rlwinm.   r0,r3,0,22,22
	  beq-      .loc_0x5C0
	  li        r3, 0
	  li        r4, 0x1
	  li        r5, 0
	  li        r6, 0x3
	  bl        0x1CA51C
	  li        r3, 0x6
	  li        r4, 0x80
	  li        r5, 0
	  li        r6, 0x3
	  li        r7, 0xFF
	  bl        0x1C9FA8
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0x1
	  bl        0x1CA678
	  b         .loc_0x604

	.loc_0x5C0:
	  rlwinm.   r0,r3,0,21,21
	  beq-      .loc_0x604
	  li        r3, 0x1
	  li        r4, 0x4
	  li        r5, 0x5
	  li        r6, 0x3
	  bl        0x1CA4D4
	  li        r3, 0x7
	  li        r4, 0
	  li        r5, 0x1
	  li        r6, 0x7
	  li        r7, 0
	  bl        0x1C9F60
	  li        r3, 0x1
	  li        r4, 0x3
	  li        r5, 0
	  bl        0x1CA630

	.loc_0x604:
	  mr        r3, r30
	  lwz       r4, 0x24(r31)
	  lwz       r12, 0x3B4(r30)
	  li        r5, 0
	  lwz       r12, 0xCC(r12)
	  mtlr      r12
	  blrl
	  lbz       r3, 0x2F(r31)
	  lis       r0, 0x4330
	  lfd       f1, -0x7B68(r2)
	  addi      r4, r1, 0x38
	  stw       r3, 0x74(r1)
	  lfs       f2, 0x374(r30)
	  li        r3, 0x4
	  stw       r0, 0x70(r1)
	  lbz       r6, 0x2E(r31)
	  lfd       f0, 0x70(r1)
	  lbz       r5, 0x2D(r31)
	  fsubs     f0, f0, f1
	  lbz       r0, 0x2C(r31)
	  stb       r0, 0x68(r1)
	  fmuls     f0, f2, f0
	  stb       r5, 0x69(r1)
	  fctiwz    f0, f0
	  stb       r6, 0x6A(r1)
	  stfd      f0, 0x78(r1)
	  lwz       r0, 0x7C(r1)
	  stb       r0, 0x6B(r1)
	  lwz       r0, 0x68(r1)
	  stw       r0, 0x38(r1)
	  bl        0x1C8550
	  lwz       r0, 0x338(r30)
	  cmplwi    r0, 0
	  bne-      .loc_0x850
	  lwz       r4, 0x28(r31)
	  cmplwi    r4, 0
	  beq-      .loc_0x7C8
	  lbz       r0, 0x3D4(r30)
	  cmplwi    r0, 0
	  bne-      .loc_0x7BC
	  lwz       r12, 0x3B4(r30)
	  mr        r3, r30
	  li        r5, 0x1
	  lwz       r12, 0xCC(r12)
	  mtlr      r12
	  blrl
	  lwz       r0, 0x24(r31)
	  cmplwi    r0, 0
	  beq-      .loc_0x6DC
	  li        r3, 0x2
	  bl        0x1C6EBC
	  li        r3, 0x2
	  bl        0x1CA0F0
	  b         .loc_0x6EC

	.loc_0x6DC:
	  li        r3, 0x1
	  bl        0x1C6EA8
	  li        r3, 0x1
	  bl        0x1CA0DC

	.loc_0x6EC:
	  lwz       r5, 0x3D8(r30)
	  li        r3, 0x1
	  li        r4, 0x1
	  addi      r6, r5, 0x1E
	  li        r5, 0x1
	  li        r7, 0
	  li        r8, 0x7D
	  bl        0x1C6BB0
	  li        r3, 0x1
	  li        r4, 0x1
	  li        r5, 0x1
	  li        r6, 0xFF
	  bl        0x1C9F08
	  lwz       r0, 0x24(r31)
	  cmplwi    r0, 0
	  beq-      .loc_0x74C
	  li        r3, 0
	  li        r4, 0
	  bl        0x1C96C8
	  li        r3, 0
	  li        r4, 0
	  li        r5, 0
	  li        r6, 0x4
	  bl        0x1C9EDC

	.loc_0x74C:
	  li        r3, 0x1
	  li        r4, 0
	  li        r5, 0xC
	  li        r6, 0x8
	  li        r7, 0xF
	  bl        0x1C9840
	  li        r3, 0x1
	  li        r4, 0
	  li        r5, 0
	  li        r6, 0
	  li        r7, 0x1
	  li        r8, 0
	  bl        0x1C9928
	  li        r3, 0x1
	  li        r4, 0x7
	  li        r5, 0
	  li        r6, 0x4
	  li        r7, 0x7
	  bl        0x1C988C
	  li        r3, 0x1
	  li        r4, 0
	  li        r5, 0
	  li        r6, 0
	  li        r7, 0x1
	  li        r8, 0
	  bl        0x1C99B4
	  li        r0, 0x1
	  stb       r0, 0x3D4(r30)

	.loc_0x7BC:
	  li        r0, 0x1
	  stw       r0, 0x324(r30)
	  b         .loc_0x850

	.loc_0x7C8:
	  li        r31, 0
	  stw       r31, 0x380(r30)
	  lbz       r0, 0x3D4(r30)
	  cmplwi    r0, 0
	  beq-      .loc_0x81C
	  li        r3, 0x1
	  li        r4, 0x4
	  bl        0x1C9618
	  li        r3, 0x1
	  li        r4, 0x1
	  li        r5, 0x5
	  li        r6, 0x3C
	  li        r7, 0
	  li        r8, 0x7D
	  bl        0x1C6AB8
	  li        r3, 0x1
	  li        r4, 0xFF
	  li        r5, 0xFF
	  li        r6, 0xFF
	  bl        0x1C9E10
	  stb       r31, 0x3D4(r30)

	.loc_0x81C:
	  li        r3, 0x1
	  bl        0x1C9FA4
	  li        r3, 0
	  li        r4, 0x1
	  li        r5, 0x4
	  li        r6, 0x3C
	  li        r7, 0
	  li        r8, 0x7D
	  bl        0x1C6A7C
	  li        r0, 0
	  stw       r0, 0x2E20(r13)
	  li        r3, 0x2
	  bl        0x1C745C

	.loc_0x850:
	  lmw       r27, 0x84(r1)
	  lwz       r0, 0x9C(r1)
	  addi      r1, r1, 0x98
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80049A04
 * Size:	0001D4
 */
void DGXGraphics::initMesh(Shape*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  lis       r5, 0x802A
	  stw       r0, 0x4(r1)
	  li        r0, 0
	  stwu      r1, -0x30(r1)
	  stmw      r27, 0x1C(r1)
	  addi      r30, r3, 0
	  addi      r31, r4, 0
	  li        r3, 0
	  stw       r0, 0x2E24(r13)
	  addi      r0, r5, 0x5A7C
	  mr        r4, r0
	  bl        0x1C6570
	  lis       r3, 0x802A
	  addi      r3, r3, 0x59C4
	  bl        0x1C5CF8
	  lwz       r3, 0x23C(r31)
	  cmplwi    r3, 0
	  beq-      .loc_0x74
	  lwz       r0, 0x13C(r31)
	  rlwinm.   r0,r0,0,31,31
	  beq-      .loc_0x64
	  lwz       r0, 0x238(r31)
	  mulli     r4, r0, 0xC
	  bl        0x1AD1B8

	.loc_0x64:
	  lwz       r4, 0x23C(r31)
	  li        r3, 0x9
	  li        r5, 0xC
	  bl        0x1C6948

	.loc_0x74:
	  lwz       r3, 0x290(r31)
	  cmplwi    r3, 0
	  beq-      .loc_0xA8
	  lwz       r0, 0x13C(r31)
	  rlwinm.   r0,r0,0,30,30
	  beq-      .loc_0x98
	  lwz       r0, 0x28C(r31)
	  mulli     r4, r0, 0xC
	  bl        0x1AD184

	.loc_0x98:
	  lwz       r4, 0x290(r31)
	  li        r3, 0xA
	  li        r5, 0xC
	  bl        0x1C6914

	.loc_0xA8:
	  lwz       r3, 0x298(r31)
	  cmplwi    r3, 0
	  beq-      .loc_0xCC
	  lwz       r0, 0x13C(r31)
	  rlwinm.   r0,r0,0,29,29
	  beq-      .loc_0xCC
	  lwz       r0, 0x294(r31)
	  mulli     r4, r0, 0x24
	  bl        0x1AD150

	.loc_0xCC:
	  addi      r28, r31, 0
	  li        r27, 0
	  li        r29, 0x1
	  b         .loc_0x120

	.loc_0xDC:
	  lwz       r3, 0x26C(r28)
	  cmplwi    r3, 0
	  beq-      .loc_0x118
	  addi      r0, r27, 0x5
	  lwz       r4, 0x13C(r31)
	  slw       r0, r29, r0
	  and.      r0, r4, r0
	  beq-      .loc_0x108
	  lwz       r0, 0x24C(r28)
	  rlwinm    r4,r0,3,0,28
	  bl        0x1AD114

	.loc_0x108:
	  lwz       r4, 0x26C(r28)
	  addi      r3, r27, 0xD
	  li        r5, 0x8
	  bl        0x1C68A4

	.loc_0x118:
	  addi      r28, r28, 0x4
	  addi      r27, r27, 0x1

	.loc_0x120:
	  lwz       r0, 0x248(r31)
	  cmpw      r27, r0
	  blt+      .loc_0xDC
	  lwz       r3, 0x244(r31)
	  cmplwi    r3, 0
	  beq-      .loc_0x160
	  lwz       r0, 0x13C(r31)
	  rlwinm.   r0,r0,0,27,27
	  beq-      .loc_0x150
	  lwz       r0, 0x238(r31)
	  rlwinm    r4,r0,2,0,29
	  bl        0x1AD0CC

	.loc_0x150:
	  lwz       r4, 0x244(r31)
	  li        r3, 0xB
	  li        r5, 0x4
	  bl        0x1C685C

	.loc_0x160:
	  li        r4, 0
	  stw       r4, 0x13C(r31)
	  li        r0, 0x1
	  subi      r3, r13, 0x7754
	  stb       r4, 0x2E38(r13)
	  stb       r0, -0x7758(r13)
	  stb       r4, 0x2E39(r13)
	  stb       r4, 0x2E3A(r13)
	  stb       r0, -0x7754(r13)
	  stb       r4, 0x1(r3)
	  stb       r4, 0x2(r3)
	  stb       r4, 0x3(r3)
	  stb       r4, 0x4(r3)
	  stb       r4, 0x5(r3)
	  stb       r4, 0x6(r3)
	  stb       r4, 0x7(r3)
	  stw       r4, 0x2E8(r30)
	  stw       r4, 0x2EC(r30)
	  stw       r4, 0x2F0(r30)
	  stw       r4, 0x2F4(r30)
	  stw       r4, 0x2F8(r30)
	  stw       r4, 0x2FC(r30)
	  stw       r4, 0x300(r30)
	  stw       r4, 0x304(r30)
	  lwz       r0, 0x34(r1)
	  lmw       r27, 0x1C(r1)
	  addi      r1, r1, 0x30
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80049BD8
 * Size:	000260
 */
void DGXGraphics::setupVtxDesc(Shape*, Material*, Mesh*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x28(r1)
	  stw       r31, 0x24(r1)
	  mr        r31, r6
	  stw       r30, 0x20(r1)
	  stw       r29, 0x1C(r1)
	  addi      r29, r3, 0
	  stw       r28, 0x18(r1)
	  addi      r28, r4, 0
	  lwz       r0, 0x2C(r6)
	  rlwinm.   r0,r0,0,31,31
	  beq-      .loc_0x58
	  lbz       r0, -0x7758(r13)
	  cmplwi    r0, 0
	  bne-      .loc_0x78
	  li        r3, 0
	  li        r4, 0x1
	  bl        0x1C57E0
	  li        r0, 0x1
	  stb       r0, -0x7758(r13)
	  b         .loc_0x78

	.loc_0x58:
	  lbz       r0, -0x7758(r13)
	  cmplwi    r0, 0
	  beq-      .loc_0x78
	  li        r3, 0
	  li        r4, 0
	  bl        0x1C57BC
	  li        r0, 0
	  stb       r0, -0x7758(r13)

	.loc_0x78:
	  lwz       r0, 0x2C(r31)
	  rlwinm.   r0,r0,0,30,30
	  beq-      .loc_0xA8
	  lbz       r0, 0x2E38(r13)
	  cmplwi    r0, 0
	  bne-      .loc_0xC8
	  li        r3, 0x2
	  li        r4, 0x1
	  bl        0x1C5790
	  li        r0, 0x1
	  stb       r0, 0x2E38(r13)
	  b         .loc_0xC8

	.loc_0xA8:
	  lbz       r0, 0x2E38(r13)
	  cmplwi    r0, 0
	  beq-      .loc_0xC8
	  li        r3, 0x2
	  li        r4, 0
	  bl        0x1C576C
	  li        r0, 0
	  stb       r0, 0x2E38(r13)

	.loc_0xC8:
	  lwz       r0, 0x380(r29)
	  cmplwi    r0, 0
	  beq-      .loc_0x12C
	  lbz       r0, 0x2E3A(r13)
	  cmplwi    r0, 0
	  bne-      .loc_0x180
	  lwz       r4, 0x298(r28)
	  li        r3, 0x19
	  li        r5, 0x24
	  bl        0x1C66F8
	  li        r3, 0
	  li        r4, 0x19
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C5F6C
	  li        r3, 0xA
	  li        r4, 0
	  bl        0x1C5718
	  li        r3, 0x19
	  li        r4, 0x3
	  bl        0x1C570C
	  li        r0, 0x1
	  stb       r0, 0x2E3A(r13)
	  b         .loc_0x180

	.loc_0x12C:
	  lbz       r0, 0x2E3A(r13)
	  cmplwi    r0, 0
	  beq-      .loc_0x180
	  lwz       r4, 0x290(r28)
	  li        r3, 0xA
	  li        r5, 0xC
	  bl        0x1C66A0
	  li        r3, 0
	  li        r4, 0xA
	  li        r5, 0
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C5F14
	  li        r3, 0xA
	  li        r4, 0x3
	  bl        0x1C56C0
	  li        r3, 0x19
	  li        r4, 0
	  bl        0x1C56B4
	  li        r0, 0
	  stb       r0, 0x2E3A(r13)

	.loc_0x180:
	  li        r28, 0
	  subi      r29, r13, 0x7754

	.loc_0x188:
	  addi      r0, r28, 0x3
	  lwz       r3, 0x2C(r31)
	  li        r30, 0x1
	  slw       r0, r30, r0
	  and.      r0, r3, r0
	  beq-      .loc_0x1C0
	  lbz       r0, 0x0(r29)
	  cmplwi    r0, 0
	  bne-      .loc_0x1E0
	  addi      r3, r28, 0xD
	  li        r4, 0x3
	  bl        0x1C5674
	  stb       r30, 0x0(r29)
	  b         .loc_0x1E0

	.loc_0x1C0:
	  lbz       r0, 0x0(r29)
	  cmplwi    r0, 0
	  beq-      .loc_0x1E0
	  addi      r3, r28, 0xD
	  li        r4, 0
	  bl        0x1C5654
	  li        r0, 0
	  stb       r0, 0x0(r29)

	.loc_0x1E0:
	  addi      r28, r28, 0x1
	  cmpwi     r28, 0x8
	  addi      r29, r29, 0x1
	  blt+      .loc_0x188
	  lwz       r0, 0x2C(r31)
	  rlwinm.   r0,r0,0,29,29
	  beq-      .loc_0x220
	  lbz       r0, 0x2E39(r13)
	  cmplwi    r0, 0
	  bne-      .loc_0x240
	  li        r3, 0xB
	  li        r4, 0x3
	  bl        0x1C5618
	  li        r0, 0x1
	  stb       r0, 0x2E39(r13)
	  b         .loc_0x240

	.loc_0x220:
	  lbz       r0, 0x2E39(r13)
	  cmplwi    r0, 0
	  beq-      .loc_0x240
	  li        r3, 0xB
	  li        r4, 0
	  bl        0x1C55F4
	  li        r0, 0
	  stb       r0, 0x2E39(r13)

	.loc_0x240:
	  lwz       r0, 0x2C(r1)
	  lwz       r31, 0x24(r1)
	  lwz       r30, 0x20(r1)
	  lwz       r29, 0x1C(r1)
	  lwz       r28, 0x18(r1)
	  addi      r1, r1, 0x28
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80049E38
 * Size:	000244
 */
void DGXGraphics::drawSingleMatpoly(Shape*, Joint::MatPoly*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x40(r1)
	  stmw      r23, 0x1C(r1)
	  addi      r23, r3, 0
	  mr        r24, r4
	  lwz       r6, 0x20(r5)
	  lwz       r0, 0x1C(r5)
	  mulli     r3, r6, 0x30
	  lwz       r5, 0x54(r4)
	  lwz       r4, 0x44(r4)
	  add       r5, r5, r3
	  lwz       r3, 0x28(r5)
	  mulli     r0, r0, 0x9C
	  cmplwi    r3, 0
	  addi      r29, r5, 0
	  add       r25, r4, r0
	  beq-      .loc_0x230
	  lwz       r4, 0x18(r25)
	  rlwinm.   r0,r4,0,15,15
	  beq-      .loc_0x58
	  b         .loc_0x230

	.loc_0x58:
	  lwz       r0, 0x20(r3)
	  cntlzw    r0, r0
	  rlwinm.   r0,r0,27,31,31
	  bne-      .loc_0x230
	  lwz       r0, 0x4(r23)
	  and.      r0, r4, r0
	  beq-      .loc_0x230
	  lwz       r0, 0x1C(r29)
	  addi      r3, r23, 0
	  addi      r4, r25, 0
	  stw       r0, 0x328(r23)
	  lwz       r12, 0x3B4(r23)
	  lwz       r12, 0xC8(r12)
	  mtlr      r12
	  blrl
	  addi      r3, r23, 0
	  addi      r4, r24, 0
	  addi      r5, r25, 0
	  addi      r6, r29, 0
	  bl        -0x304
	  li        r28, 0
	  li        r30, 0
	  b         .loc_0x224

	.loc_0xB4:
	  lwz       r0, 0x24(r29)
	  li        r26, 0
	  li        r31, 0
	  add       r27, r0, r30
	  b         .loc_0x194

	.loc_0xC8:
	  lwz       r3, 0x4(r27)
	  lwzx      r0, r3, r31
	  cmpwi     r0, -0x1
	  beq-      .loc_0x18C
	  lwz       r3, 0x18(r24)
	  rlwinm    r4,r0,3,0,28
	  lwz       r5, 0x3C(r24)
	  lwz       r0, 0x0(r3)
	  add       r5, r5, r4
	  cmplwi    r0, 0
	  beq-      .loc_0x160
	  lbz       r0, 0x0(r5)
	  cmplwi    r0, 0
	  beq-      .loc_0x12C
	  mr        r3, r24
	  lwz       r4, 0x4(r5)
	  bl        -0x14F58
	  lwz       r12, 0x3B4(r23)
	  addi      r4, r3, 0
	  addi      r3, r23, 0
	  lwz       r12, 0xF4(r12)
	  mr        r5, r26
	  mtlr      r12
	  blrl
	  b         .loc_0x18C

	.loc_0x12C:
	  lwz       r4, 0x58(r24)
	  mr        r3, r24
	  lwz       r0, 0x4(r5)
	  add       r4, r4, r0
	  bl        -0x14F8C
	  lwz       r12, 0x3B4(r23)
	  addi      r4, r3, 0
	  addi      r3, r23, 0
	  lwz       r12, 0xF4(r12)
	  mr        r5, r26
	  mtlr      r12
	  blrl
	  b         .loc_0x18C

	.loc_0x160:
	  mr        r3, r23
	  lwz       r0, 0x4(r5)
	  lwz       r12, 0x3B4(r23)
	  addi      r5, r26, 0
	  mulli     r4, r0, 0x11C
	  lwz       r0, 0x5C(r24)
	  lwz       r12, 0xF4(r12)
	  addi      r4, r4, 0x48
	  mtlr      r12
	  add       r4, r0, r4
	  blrl

	.loc_0x18C:
	  addi      r31, r31, 0x4
	  addi      r26, r26, 0x1

	.loc_0x194:
	  lwz       r0, 0x0(r27)
	  cmpw      r26, r0
	  blt+      .loc_0xC8
	  li        r26, 0
	  li        r31, 0
	  b         .loc_0x210

	.loc_0x1AC:
	  mr        r3, r23
	  lwz       r0, 0xC(r27)
	  lwz       r12, 0x3B4(r23)
	  add       r25, r0, r31
	  lwz       r0, 0x334(r23)
	  lwz       r4, 0x14(r25)
	  lwz       r12, 0x58(r12)
	  rlwinm    r4,r4,0,30,31
	  mtlr      r12
	  xor       r4, r4, r0
	  blrl
	  lwz       r4, 0x2DEC(r13)
	  lwz       r0, 0x28(r25)
	  lwz       r3, 0x1A4(r4)
	  add       r0, r3, r0
	  stw       r0, 0x1A4(r4)
	  lwz       r4, 0x2DEC(r13)
	  lwz       r3, 0x1AC(r4)
	  addi      r0, r3, 0x1
	  stw       r0, 0x1AC(r4)
	  lwz       r3, 0x1C(r25)
	  lwz       r4, 0x18(r25)
	  bl        0x1CA248
	  addi      r31, r31, 0x74
	  addi      r26, r26, 0x1

	.loc_0x210:
	  lwz       r0, 0x8(r27)
	  cmpw      r26, r0
	  blt+      .loc_0x1AC
	  addi      r30, r30, 0x10
	  addi      r28, r28, 0x1

	.loc_0x224:
	  lwz       r0, 0x20(r29)
	  cmpw      r28, r0
	  blt+      .loc_0xB4

	.loc_0x230:
	  lmw       r23, 0x1C(r1)
	  lwz       r0, 0x44(r1)
	  addi      r1, r1, 0x40
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004A07C
 * Size:	0000B0
 */
void DGXGraphics::drawMeshes(Camera&, Shape* shape)
{
	initMesh(shape);
	for (int i = shape->mTotalMatpolyCount - 1; i >= 0; i--) {
		drawSingleMatpoly(shape, shape->mMatpolyList[i]);
	}
	useMaterial(nullptr);
}

/*
 * --INFO--
 * Address:	8004A12C
 * Size:	00009C
 */
void DGXGraphics::setColour(Colour& color, bool set)
{
	mPrimaryColour = color;
	if (set) {
		mAuxiliaryColour = color;
	}

	GXColor color2;
	color2.r = mPrimaryColour.r;
	color2.g = mPrimaryColour.g;
	color2.b = mPrimaryColour.b;
	color2.a = mPrimaryColour.a;

	color2.a *= mLightIntensity;
	GXSetChanMatColor(GX_COLOR0A0, color2);
}

/*
 * --INFO--
 * Address:	8004A1C8
 * Size:	00000C
 */
void DGXGraphics::setAuxColour(Colour& color)
{
	mAuxiliaryColour = color;
}

/*
 * --INFO--
 * Address:	8004A1D4
 * Size:	000060
 */
void DGXGraphics::setPrimEnv(Colour* col1, Colour* col2)
{
	if (col1) {
		GXSetTevColor(GX_TEVREG0, *(GXColor*)col1);
	}
	if (col2) {
		GXSetTevColor(GX_TEVREG1, *(GXColor*)col2);
	}
}

/*
 * --INFO--
 * Address:	8004A234
 * Size:	00000C
 */
void DGXGraphics::setClearColour(Colour& color)
{
	mBufferClearColour = color;
}

/*
 * --INFO--
 * Address:	8004A240
 * Size:	000034
 */
void DGXGraphics::clearBuffer(int, bool)
{
	GXSetCopyClear(*(GXColor*)&mBufferClearColour, 0xffffff);
}

/*
 * --INFO--
 * Address:	8004A274
 * Size:	0000B4
 */
void DGXGraphics::setFog(bool set)
{
	if (set) {
		if (mCamera->mNear < mCamera->mFar) {
			GXSetFog(GX_FOG_LINEAR, mFogStart, mFogEnd, mCamera->mNear, mCamera->mFar, *(GXColor*)&mFogColour);
		} else {
			OSReport("%s:%d Warning: cam->vNear >= cam->vFar\n", "dgxGraphics.cpp", 1683);
		}
	} else {
		GXColor col = { 0, 0, 0, 0 };
		GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, col);
	}
	/*
	.loc_0x0:
	  mflr      r0
	  addi      r6, r3, 0
	  stw       r0, 0x4(r1)
	  rlwinm.   r0,r4,0,24,31
	  stwu      r1, -0x20(r1)
	  beq-      .loc_0x78
	  lwz       r3, 0x2E4(r6)
	  lfs       f1, 0x1D0(r3)
	  lfs       f0, 0x1D4(r3)
	  fcmpo     cr0, f1, f0
	  bge-      .loc_0x58
	  lwz       r0, 0x364(r6)
	  addi      r4, r1, 0x1C
	  li        r3, 0x2
	  stw       r0, 0x1C(r1)
	  lwz       r5, 0x2E4(r6)
	  lfs       f1, 0x358(r6)
	  lfs       f2, 0x35C(r6)
	  lfs       f3, 0x1D0(r5)
	  lfs       f4, 0x1D4(r5)
	  bl        0x1C96D4
	  b         .loc_0xA4

	.loc_0x58:
	  lis       r3, 0x802A
	  crclr     6, 0x6
	  lis       r4, 0x802A
	  addi      r3, r3, 0x5B2C
	  addi      r4, r4, 0x56E8
	  li        r5, 0x693
	  bl        0x1AD5AC
	  b         .loc_0xA4

	.loc_0x78:
	  lwz       r0, -0x7B40(r2)
	  addi      r4, r1, 0x18
	  lfs       f1, -0x7B58(r2)
	  li        r3, 0
	  stw       r0, 0x14(r1)
	  fmr       f2, f1
	  lwz       r0, 0x14(r1)
	  fmr       f3, f1
	  fmr       f4, f1
	  stw       r0, 0x18(r1)
	  bl        0x1C9684

	.loc_0xA4:
	  lwz       r0, 0x24(r1)
	  addi      r1, r1, 0x20
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004A328
 * Size:	000040
 */
void DGXGraphics::setFog(bool set, Colour& color, f32 density, f32 start, f32 end)
{
	mFogColour  = color;
	mFogStart   = start;
	mFogEnd     = end;
	mFogDensity = density;
	setFog(set);
}

/*
 * --INFO--
 * Address:	8004A368
 * Size:	000164
 */
void DGXGraphics::setBlendMode(u8 blend, u8 zmode, u8 flag3)
{
	GXSetBlendMode(GX_BM_BLEND, (GXBlendFactor)(blend & 0xf), (GXBlendFactor)(blend >> 4), GX_LO_SET);

	GXSetZMode((GXBool)((zmode & 8) >> 3), (GXCompare)(zmode & 7), (GXBool)(zmode >> 4));

	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);

	switch (flag3) {
	case 0:
		GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ONE, GX_CC_TEXC, GX_CC_ZERO);
		break;
	case 1:
		GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXC, GX_CC_ZERO);
		break;
	case 2:
		GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C2, GX_CC_C0, GX_CC_TEXC, GX_CC_ZERO);
		break;
	case 3:
		GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_C2);
		break;
	case 4:
		GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
		break;
	}
}

/*
 * --INFO--
 * Address:	8004A4CC
 * Size:	000438
 */
int DGXGraphics::setCBlending(int mode)
{
	int old    = mBlendMode;
	mBlendMode = mode;
	GXSetNumTexGens(1);
	GXSetNumTevStages(1);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);

	switch (mode) {
	case 0:
		GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
		break;
	case 1:
		GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_SET);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
		break;
	case 2:
		GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVSRCCOL, GX_LO_CLEAR);
		GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
		break;
	case 3:
		GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_SET);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
		break;
	case 4:
		GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_SET);
		GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
		break;
	case 5:
		GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
		GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_AND, GX_LEQUAL, 0xff);
		break;
	case 6:
		GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
		GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
		GXSetNumTexGens(2);
		GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
		GXSetNumTevStages(4);

		GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
		GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
		GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

		GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
		GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
		GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
		GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

		GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
		GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
		GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_APREV, GX_CA_ZERO);
		GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

		GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
		GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
		GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_A0, GX_CA_APREV, GX_CA_ZERO);
		GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

		GXSetAlphaCompare(GX_GEQUAL, 0, GX_AOP_AND, GX_LESS, 0xff);
	}
	return old;
}

/*
 * --INFO--
 * Address:	8004A904
 * Size:	0000B8
 */
bool DGXGraphics::initParticle(bool a)
{
	if (!mActiveTexture[0]) {
		return false;
	}

	GXClearVtxDesc();

	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_POS_XYZ, GX_F32, 0);
	if (a) {
		GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_POS_XYZ, GX_RGBA8, 0);
	}
	return true;
}

/*
 * --INFO--
 * Address:	8004A9BC
 * Size:	000328
 */
void DGXGraphics::drawRotParticle(Camera&, Vector3f&, u16, f32)
{
	/*
	.loc_0x0:
	  mflr      r0
	  rlwinm    r3,r6,0,16,31
	  stw       r0, 0x4(r1)
	  addis     r7, r3, 0x1
	  addi      r6, r3, 0x2000
	  stwu      r1, -0x158(r1)
	  subi      r9, r7, 0x2000
	  subi      r0, r7, 0x6000
	  stfd      f31, 0x150(r1)
	  addi      r3, r3, 0x6000
	  rlwinm    r9,r9,30,18,29
	  stfd      f30, 0x148(r1)
	  rlwinm    r6,r6,30,18,29
	  rlwinm    r0,r0,30,18,29
	  stfd      f29, 0x140(r1)
	  stfd      f28, 0x138(r1)
	  stfd      f27, 0x130(r1)
	  stfd      f26, 0x128(r1)
	  stfd      f25, 0x120(r1)
	  stfd      f24, 0x118(r1)
	  stfd      f23, 0x110(r1)
	  stfd      f22, 0x108(r1)
	  stfd      f21, 0x100(r1)
	  stfd      f20, 0xF8(r1)
	  stfd      f19, 0xF0(r1)
	  stfd      f18, 0xE8(r1)
	  stfd      f17, 0xE0(r1)
	  stfd      f16, 0xD8(r1)
	  stw       r31, 0xD4(r1)
	  addi      r31, r5, 0
	  stw       r30, 0xD0(r1)
	  addi      r30, r4, 0
	  lwz       r10, 0x2DEC(r13)
	  lwz       r8, 0x1A4(r10)
	  addi      r7, r8, 0x2
	  stw       r7, 0x1A4(r10)
	  lis       r8, 0x8039
	  lis       r7, 0x8039
	  addi      r8, r8, 0x4840
	  lfs       f23, -0x774C(r13)
	  addi      r5, r7, 0x840
	  lfs       f22, -0x7748(r13)
	  rlwinm    r7,r3,30,18,29
	  lfs       f21, -0x7744(r13)
	  add       r4, r8, r9
	  lfs       f20, -0x7740(r13)
	  lfs       f8, 0x0(r4)
	  add       r3, r5, r9
	  lfs       f7, 0x0(r3)
	  add       r4, r8, r6
	  lfs       f6, 0x0(r4)
	  add       r3, r5, r6
	  fmuls     f30, f1, f8
	  lfs       f5, 0x0(r3)
	  add       r4, r8, r7
	  lfs       f4, 0x0(r4)
	  add       r3, r5, r7
	  lfs       f3, 0x0(r3)
	  add       r3, r5, r0
	  lfs       f0, 0x0(r3)
	  add       r4, r8, r0
	  lfs       f2, 0x0(r4)
	  fmuls     f31, f1, f7
	  li        r3, 0x80
	  fmuls     f28, f1, f6
	  li        r4, 0
	  fmuls     f29, f1, f5
	  fmuls     f26, f1, f4
	  li        r5, 0x4
	  fmuls     f27, f1, f3
	  fmuls     f24, f1, f2
	  fmuls     f25, f1, f0
	  bl        0x1C60F8
	  lfs       f3, 0x17C(r30)
	  lis       r3, 0xCC01
	  lfs       f2, 0x180(r30)
	  lfs       f8, 0x188(r30)
	  fmuls     f5, f31, f3
	  lfs       f6, 0x18C(r30)
	  fmuls     f1, f30, f2
	  lfs       f19, 0x194(r30)
	  lfs       f12, 0x198(r30)
	  lfs       f9, 0x190(r30)
	  fmuls     f7, f31, f8
	  lfs       f18, 0x19C(r30)
	  fmuls     f0, f30, f6
	  lfs       f4, 0x184(r30)
	  fadds     f1, f5, f1
	  fmuls     f17, f23, f4
	  lfs       f5, 0x0(r31)
	  fmuls     f13, f31, f19
	  lfs       f10, 0x4(r31)
	  fmuls     f11, f30, f12
	  fadds     f31, f17, f1
	  lfs       f30, 0x8(r31)
	  fmuls     f16, f23, f9
	  lfs       f1, -0x7B58(r2)
	  fadds     f17, f7, f0
	  fadds     f7, f5, f31
	  lfs       f0, -0x7B60(r2)
	  fmuls     f31, f23, f18
	  fadds     f23, f13, f11
	  fadds     f13, f16, f17
	  fmuls     f11, f29, f3
	  stfs      f7, -0x8000(r3)
	  fadds     f16, f31, f23
	  fmuls     f7, f28, f2
	  fadds     f13, f10, f13
	  fmuls     f31, f29, f8
	  fmuls     f23, f28, f6
	  fadds     f16, f30, f16
	  stfs      f13, -0x8000(r3)
	  fmuls     f13, f22, f4
	  fadds     f7, f11, f7
	  stfs      f16, -0x8000(r3)
	  fmuls     f29, f29, f19
	  fmuls     f28, f28, f12
	  stfs      f1, -0x8000(r3)
	  fadds     f7, f13, f7
	  fmuls     f13, f22, f9
	  fadds     f11, f31, f23
	  fmuls     f23, f22, f18
	  stfs      f1, -0x8000(r3)
	  fadds     f22, f29, f28
	  fadds     f11, f13, f11
	  fadds     f7, f5, f7
	  fadds     f23, f23, f22
	  fmuls     f22, f27, f19
	  fmuls     f13, f26, f12
	  stfs      f7, -0x8000(r3)
	  fadds     f16, f10, f11
	  fmuls     f11, f27, f8
	  fmuls     f7, f26, f6
	  fadds     f17, f30, f23
	  stfs      f16, -0x8000(r3)
	  fmuls     f23, f21, f18
	  fadds     f22, f22, f13
	  stfs      f17, -0x8000(r3)
	  fmuls     f13, f21, f9
	  fadds     f7, f11, f7
	  stfs      f0, -0x8000(r3)
	  fadds     f11, f23, f22
	  stfs      f1, -0x8000(r3)
	  fadds     f7, f13, f7
	  fadds     f11, f30, f11
	  fadds     f7, f10, f7
	  fmuls     f22, f27, f3
	  fmuls     f13, f26, f2
	  fmuls     f21, f21, f4
	  fmuls     f3, f25, f3
	  fadds     f13, f22, f13
	  fmuls     f2, f24, f2
	  fmuls     f8, f25, f8
	  fadds     f13, f21, f13
	  fmuls     f6, f24, f6
	  fmuls     f4, f20, f4
	  fadds     f21, f5, f13
	  fadds     f2, f3, f2
	  fmuls     f13, f25, f19
	  stfs      f21, -0x8000(r3)
	  fmuls     f12, f24, f12
	  fadds     f2, f4, f2
	  stfs      f7, -0x8000(r3)
	  fmuls     f4, f20, f9
	  fadds     f3, f8, f6
	  stfs      f11, -0x8000(r3)
	  fmuls     f7, f20, f18
	  fadds     f6, f13, f12
	  stfs      f0, -0x8000(r3)
	  fadds     f3, f4, f3
	  fadds     f4, f7, f6
	  stfs      f0, -0x8000(r3)
	  fadds     f2, f5, f2
	  fadds     f3, f10, f3
	  fadds     f4, f30, f4
	  stfs      f2, -0x8000(r3)
	  stfs      f3, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stfs      f0, -0x8000(r3)
	  lwz       r0, 0x15C(r1)
	  lfd       f31, 0x150(r1)
	  lfd       f30, 0x148(r1)
	  lfd       f29, 0x140(r1)
	  lfd       f28, 0x138(r1)
	  lfd       f27, 0x130(r1)
	  lfd       f26, 0x128(r1)
	  lfd       f25, 0x120(r1)
	  lfd       f24, 0x118(r1)
	  lfd       f23, 0x110(r1)
	  lfd       f22, 0x108(r1)
	  lfd       f21, 0x100(r1)
	  lfd       f20, 0xF8(r1)
	  lfd       f19, 0xF0(r1)
	  lfd       f18, 0xE8(r1)
	  lfd       f17, 0xE0(r1)
	  lfd       f16, 0xD8(r1)
	  lwz       r31, 0xD4(r1)
	  lwz       r30, 0xD0(r1)
	  addi      r1, r1, 0x158
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004ACE4
 * Size:	00027C
 */
void DGXGraphics::drawParticle(Camera&, Vector3f&, f32)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x140(r1)
	  stfd      f31, 0x138(r1)
	  stfd      f30, 0x130(r1)
	  stfd      f29, 0x128(r1)
	  stfd      f28, 0x120(r1)
	  stfd      f27, 0x118(r1)
	  stfd      f26, 0x110(r1)
	  fmr       f26, f1
	  stfd      f25, 0x108(r1)
	  fneg      f27, f26
	  stfd      f24, 0x100(r1)
	  stfd      f23, 0xF8(r1)
	  stfd      f22, 0xF0(r1)
	  stfd      f21, 0xE8(r1)
	  stfd      f20, 0xE0(r1)
	  stfd      f19, 0xD8(r1)
	  stfd      f18, 0xD0(r1)
	  stfd      f17, 0xC8(r1)
	  stw       r31, 0xC4(r1)
	  stw       r30, 0xC0(r1)
	  mr        r30, r5
	  li        r5, 0x4
	  stw       r29, 0xBC(r1)
	  mr        r29, r4
	  lwz       r6, 0x2DEC(r13)
	  lwz       r4, 0x1A4(r6)
	  addi      r0, r4, 0x2
	  stw       r0, 0x1A4(r6)
	  li        r4, 0
	  lwz       r31, 0x318(r3)
	  li        r3, 0x80
	  lfs       f31, -0x773C(r13)
	  lfs       f30, -0x7738(r13)
	  lfs       f29, -0x7734(r13)
	  lfs       f28, -0x7730(r13)
	  bl        0x1C5E5C
	  lfs       f2, 0x17C(r29)
	  lis       r3, 0xCC01
	  lfs       f18, 0x180(r29)
	  lfs       f21, 0x188(r29)
	  fmuls     f5, f27, f2
	  lfs       f6, 0x184(r29)
	  fmuls     f19, f26, f18
	  lfs       f0, 0x18C(r29)
	  lfs       f10, 0x190(r29)
	  lfs       f17, 0x194(r29)
	  fmuls     f9, f27, f21
	  lfs       f24, 0x19C(r29)
	  fmuls     f8, f26, f0
	  lfs       f13, 0x198(r29)
	  fmuls     f3, f31, f6
	  fadds     f1, f5, f19
	  lfs       f7, 0x0(r30)
	  fmuls     f25, f27, f17
	  lfs       f11, 0x4(r30)
	  fmuls     f12, f26, f13
	  fadds     f1, f3, f1
	  lfs       f23, 0x8(r30)
	  fmuls     f22, f26, f2
	  lfs       f4, -0x7B58(r2)
	  fadds     f20, f7, f1
	  fmuls     f2, f26, f21
	  lfs       f1, -0x7B60(r2)
	  fmuls     f3, f26, f17
	  fmuls     f26, f31, f10
	  fadds     f21, f9, f8
	  fmuls     f17, f31, f24
	  stfs      f20, -0x8000(r3)
	  fadds     f31, f25, f12
	  fadds     f20, f26, f21
	  fmuls     f21, f30, f6
	  fmuls     f26, f27, f18
	  fadds     f18, f17, f31
	  fmuls     f31, f27, f0
	  fadds     f17, f11, f20
	  fmuls     f0, f27, f13
	  fadds     f13, f22, f19
	  fadds     f18, f23, f18
	  stfs      f17, -0x8000(r3)
	  fmuls     f20, f30, f10
	  fadds     f27, f2, f8
	  stfs      f18, -0x8000(r3)
	  fadds     f8, f21, f13
	  stw       r31, -0x8000(r3)
	  fadds     f13, f20, f27
	  fmuls     f20, f30, f24
	  fadds     f12, f3, f12
	  stfs      f4, -0x8000(r3)
	  fadds     f8, f7, f8
	  fadds     f17, f11, f13
	  stfs      f4, -0x8000(r3)
	  fadds     f13, f20, f12
	  stfs      f8, -0x8000(r3)
	  fmuls     f12, f29, f6
	  fadds     f8, f22, f26
	  fadds     f18, f23, f13
	  stfs      f17, -0x8000(r3)
	  fmuls     f27, f29, f10
	  fadds     f13, f2, f31
	  stfs      f18, -0x8000(r3)
	  fadds     f2, f12, f8
	  stw       r31, -0x8000(r3)
	  fadds     f8, f27, f13
	  fmuls     f12, f29, f24
	  fadds     f3, f3, f0
	  stfs      f1, -0x8000(r3)
	  fadds     f2, f7, f2
	  fadds     f13, f11, f8
	  stfs      f4, -0x8000(r3)
	  fadds     f8, f12, f3
	  stfs      f2, -0x8000(r3)
	  fmuls     f3, f28, f6
	  fadds     f2, f5, f26
	  fadds     f8, f23, f8
	  stfs      f13, -0x8000(r3)
	  fmuls     f6, f28, f10
	  fadds     f5, f9, f31
	  stfs      f8, -0x8000(r3)
	  fadds     f2, f3, f2
	  stw       r31, -0x8000(r3)
	  fadds     f3, f6, f5
	  fmuls     f6, f28, f24
	  fadds     f5, f25, f0
	  stfs      f1, -0x8000(r3)
	  fadds     f0, f7, f2
	  fadds     f3, f11, f3
	  stfs      f1, -0x8000(r3)
	  fadds     f2, f6, f5
	  stfs      f0, -0x8000(r3)
	  fadds     f0, f23, f2
	  stfs      f3, -0x8000(r3)
	  stfs      f0, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  lwz       r0, 0x144(r1)
	  lfd       f31, 0x138(r1)
	  lfd       f30, 0x130(r1)
	  lfd       f29, 0x128(r1)
	  lfd       f28, 0x120(r1)
	  lfd       f27, 0x118(r1)
	  lfd       f26, 0x110(r1)
	  lfd       f25, 0x108(r1)
	  lfd       f24, 0x100(r1)
	  lfd       f23, 0xF8(r1)
	  lfd       f22, 0xF0(r1)
	  lfd       f21, 0xE8(r1)
	  lfd       f20, 0xE0(r1)
	  lfd       f19, 0xD8(r1)
	  lfd       f18, 0xD0(r1)
	  lfd       f17, 0xC8(r1)
	  lwz       r31, 0xC4(r1)
	  lwz       r30, 0xC0(r1)
	  lwz       r29, 0xBC(r1)
	  addi      r1, r1, 0x140
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004AF60
 * Size:	000128
 */
void DGXGraphics::drawCamParticle(Camera&, Vector3f&, Vector2f&, Vector2f&, Vector2f&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  li        r4, 0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x108(r1)
	  stfd      f31, 0x100(r1)
	  stfd      f30, 0xF8(r1)
	  stfd      f29, 0xF0(r1)
	  stfd      f28, 0xE8(r1)
	  stfd      f27, 0xE0(r1)
	  stw       r31, 0xDC(r1)
	  stw       r30, 0xD8(r1)
	  addi      r30, r8, 0
	  stw       r29, 0xD4(r1)
	  addi      r29, r7, 0
	  lwz       r9, 0x2DEC(r13)
	  lwz       r7, 0x1A4(r9)
	  addi      r0, r7, 0x2
	  stw       r0, 0x1A4(r9)
	  lfs       f5, 0x4(r6)
	  lfs       f3, 0x0(r6)
	  fneg      f0, f5
	  lfs       f4, 0x4(r5)
	  lfs       f2, 0x0(r5)
	  fneg      f1, f3
	  lfs       f30, 0x8(r5)
	  lwz       r31, 0x318(r3)
	  fadds     f31, f5, f4
	  fadds     f27, f1, f2
	  li        r3, 0x80
	  fadds     f29, f3, f2
	  fadds     f28, f0, f4
	  li        r5, 0x4
	  bl        0x1C5BF4
	  lis       r3, 0xCC01
	  stfs      f27, -0x8000(r3)
	  stfs      f31, -0x8000(r3)
	  stfs      f30, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lfs       f2, 0x4(r29)
	  lfs       f1, 0x0(r29)
	  stfs      f1, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stfs      f29, -0x8000(r3)
	  stfs      f31, -0x8000(r3)
	  stfs      f30, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lfs       f0, 0x0(r30)
	  stfs      f0, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stfs      f29, -0x8000(r3)
	  stfs      f28, -0x8000(r3)
	  stfs      f30, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lfs       f2, 0x4(r30)
	  stfs      f0, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stfs      f27, -0x8000(r3)
	  stfs      f28, -0x8000(r3)
	  stfs      f30, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  lwz       r0, 0x10C(r1)
	  lfd       f31, 0x100(r1)
	  lfd       f30, 0xF8(r1)
	  lfd       f29, 0xF0(r1)
	  lfd       f28, 0xE8(r1)
	  lfd       f27, 0xE0(r1)
	  lwz       r31, 0xDC(r1)
	  lwz       r30, 0xD8(r1)
	  lwz       r29, 0xD4(r1)
	  addi      r1, r1, 0x108
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004B088
 * Size:	0000F4
 */
void DGXGraphics::drawLine(Vector3f&, Vector3f&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x30(r1)
	  stw       r31, 0x2C(r1)
	  mr        r31, r3
	  stw       r30, 0x28(r1)
	  addi      r30, r5, 0
	  li        r5, 0
	  stw       r29, 0x24(r1)
	  addi      r29, r4, 0
	  li        r4, 0
	  lwz       r12, 0x3B4(r31)
	  lwz       r12, 0xCC(r12)
	  mtlr      r12
	  blrl
	  bl        0x1C4B38
	  li        r3, 0x9
	  li        r4, 0x1
	  bl        0x1C4330
	  li        r3, 0xB
	  li        r4, 0x1
	  bl        0x1C4324
	  li        r3, 0
	  li        r4, 0x9
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C4B54
	  li        r3, 0
	  li        r4, 0xB
	  li        r5, 0x1
	  li        r6, 0x5
	  li        r7, 0
	  bl        0x1C4B3C
	  lwz       r31, 0x318(r31)
	  li        r3, 0xA8
	  li        r4, 0
	  li        r5, 0x2
	  bl        0x1C5AB4
	  lfs       f2, 0x8(r29)
	  lis       r3, 0xCC01
	  lfs       f1, 0x4(r29)
	  lfs       f0, 0x0(r29)
	  stfs      f0, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lfs       f2, 0x8(r30)
	  lfs       f1, 0x4(r30)
	  lfs       f0, 0x0(r30)
	  stfs      f0, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lwz       r0, 0x34(r1)
	  lwz       r31, 0x2C(r1)
	  lwz       r30, 0x28(r1)
	  lwz       r29, 0x24(r1)
	  addi      r1, r1, 0x30
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004B17C
 * Size:	000224
 */
void DGXGraphics::drawPoints(Vector3f*, int)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x30(r1)
	  stw       r31, 0x2C(r1)
	  mr        r31, r3
	  stw       r30, 0x28(r1)
	  addi      r30, r5, 0
	  li        r5, 0
	  stw       r29, 0x24(r1)
	  addi      r29, r4, 0
	  li        r4, 0
	  lwz       r12, 0x3B4(r31)
	  lwz       r12, 0xCC(r12)
	  mtlr      r12
	  blrl
	  bl        0x1C4A44
	  li        r3, 0x9
	  li        r4, 0x1
	  bl        0x1C423C
	  li        r3, 0xB
	  li        r4, 0x1
	  bl        0x1C4230
	  li        r3, 0
	  li        r4, 0x9
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C4A60
	  li        r3, 0
	  li        r4, 0xB
	  li        r5, 0x1
	  li        r6, 0x5
	  li        r7, 0
	  bl        0x1C4A48
	  lwz       r31, 0x318(r31)
	  rlwinm    r5,r30,0,16,31
	  li        r3, 0xB8
	  li        r4, 0
	  bl        0x1C59C0
	  cmpwi     r30, 0
	  li        r5, 0
	  ble-      .loc_0x208
	  cmpwi     r30, 0x8
	  subi      r3, r30, 0x8
	  ble-      .loc_0x1FC
	  addi      r0, r3, 0x7
	  rlwinm    r0,r0,29,3,31
	  cmpwi     r3, 0
	  mtctr     r0
	  addi      r4, r29, 0
	  lis       r3, 0xCC01
	  ble-      .loc_0x1FC

	.loc_0xD0:
	  lfs       f2, 0x8(r4)
	  addi      r5, r5, 0x8
	  lfs       f1, 0x4(r4)
	  lfs       f0, 0x0(r4)
	  stfs      f0, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lfs       f1, 0x14(r4)
	  lfs       f2, 0x10(r4)
	  lfs       f0, 0xC(r4)
	  stfs      f0, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lfs       f1, 0x20(r4)
	  lfs       f2, 0x1C(r4)
	  lfs       f0, 0x18(r4)
	  stfs      f0, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lfs       f1, 0x2C(r4)
	  lfs       f2, 0x28(r4)
	  lfs       f0, 0x24(r4)
	  stfs      f0, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lfs       f1, 0x38(r4)
	  lfs       f2, 0x34(r4)
	  lfs       f0, 0x30(r4)
	  stfs      f0, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lfs       f1, 0x44(r4)
	  lfs       f2, 0x40(r4)
	  lfs       f0, 0x3C(r4)
	  stfs      f0, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lfs       f1, 0x50(r4)
	  lfs       f2, 0x4C(r4)
	  lfs       f0, 0x48(r4)
	  stfs      f0, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lfs       f1, 0x5C(r4)
	  lfs       f2, 0x58(r4)
	  lfs       f0, 0x54(r4)
	  addi      r4, r4, 0x60
	  stfs      f0, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  bdnz+     .loc_0xD0
	  b         .loc_0x1FC

	.loc_0x1C0:
	  sub       r0, r30, r5
	  cmpw      r5, r30
	  mtctr     r0
	  lis       r3, 0xCC01
	  bge-      .loc_0x208

	.loc_0x1D4:
	  lfs       f1, 0x8(r4)
	  lfs       f2, 0x4(r4)
	  lfs       f0, 0x0(r4)
	  addi      r4, r4, 0xC
	  stfs      f0, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  bdnz+     .loc_0x1D4
	  b         .loc_0x208

	.loc_0x1FC:
	  mulli     r0, r5, 0xC
	  add       r4, r29, r0
	  b         .loc_0x1C0

	.loc_0x208:
	  lwz       r0, 0x34(r1)
	  lwz       r31, 0x2C(r1)
	  lwz       r30, 0x28(r1)
	  lwz       r29, 0x24(r1)
	  addi      r1, r1, 0x30
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004B3A0
 * Size:	0003D8
 */
void DGXGraphics::drawOneTri(Vector3f*, Vector3f*, Vector2f*, int)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x40(r1)
	  stmw      r27, 0x2C(r1)
	  addi      r31, r3, 0
	  addi      r27, r4, 0
	  addi      r28, r5, 0
	  addi      r29, r6, 0
	  mr        r30, r7
	  lwz       r8, 0x2DEC(r13)
	  lwz       r3, 0x1A4(r8)
	  addi      r0, r3, 0x1
	  stw       r0, 0x1A4(r8)
	  bl        0x1C4828
	  li        r3, 0x9
	  li        r4, 0x1
	  bl        0x1C4020
	  cmplwi    r28, 0
	  beq-      .loc_0x5C
	  li        r3, 0xA
	  li        r4, 0x1
	  bl        0x1C400C
	  b         .loc_0x68

	.loc_0x5C:
	  li        r3, 0xB
	  li        r4, 0x1
	  bl        0x1C3FFC

	.loc_0x68:
	  li        r3, 0xD
	  li        r4, 0x1
	  bl        0x1C3FF0
	  li        r3, 0
	  li        r4, 0x9
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C4820
	  cmplwi    r28, 0
	  beq-      .loc_0xB0
	  li        r3, 0
	  li        r4, 0xA
	  li        r5, 0
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C4800
	  b         .loc_0xC8

	.loc_0xB0:
	  li        r3, 0
	  li        r4, 0xB
	  li        r5, 0x1
	  li        r6, 0x5
	  li        r7, 0
	  bl        0x1C47E4

	.loc_0xC8:
	  li        r3, 0
	  li        r4, 0xD
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C47CC
	  lwz       r31, 0x318(r31)
	  rlwinm    r5,r30,0,16,31
	  li        r3, 0xA0
	  li        r4, 0
	  bl        0x1C5744
	  cmplwi    r28, 0
	  addi      r5, r27, 0
	  addi      r6, r28, 0
	  addi      r7, r29, 0
	  lis       r4, 0xCC01
	  beq-      .loc_0x2A0
	  cmpwi     r30, 0
	  addi      r3, r30, 0
	  ble-      .loc_0x3C4
	  rlwinm.   r0,r3,30,2,31
	  mtctr     r0
	  beq-      .loc_0x248

	.loc_0x124:
	  lfs       f2, 0x8(r5)
	  lfs       f1, 0x4(r5)
	  lfs       f0, 0x0(r5)
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  lfs       f2, 0x8(r6)
	  lfs       f1, 0x4(r6)
	  lfs       f0, 0x0(r6)
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  lfs       f1, 0x4(r7)
	  lfs       f0, 0x0(r7)
	  addi      r7, r7, 0x8
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  lfs       f2, 0x14(r5)
	  lfs       f1, 0x10(r5)
	  lfs       f0, 0xC(r5)
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  lfs       f2, 0x14(r6)
	  lfs       f1, 0x10(r6)
	  lfs       f0, 0xC(r6)
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  lfs       f1, 0x4(r7)
	  lfs       f0, 0x0(r7)
	  addi      r7, r7, 0x8
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  lfs       f2, 0x20(r5)
	  lfs       f1, 0x1C(r5)
	  lfs       f0, 0x18(r5)
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  lfs       f2, 0x20(r6)
	  lfs       f1, 0x1C(r6)
	  lfs       f0, 0x18(r6)
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  lfs       f1, 0x4(r7)
	  lfs       f0, 0x0(r7)
	  addi      r7, r7, 0x8
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  lfs       f2, 0x2C(r5)
	  lfs       f1, 0x28(r5)
	  lfs       f0, 0x24(r5)
	  addi      r5, r5, 0x30
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  lfs       f2, 0x2C(r6)
	  lfs       f1, 0x28(r6)
	  lfs       f0, 0x24(r6)
	  addi      r6, r6, 0x30
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  lfs       f1, 0x4(r7)
	  lfs       f0, 0x0(r7)
	  addi      r7, r7, 0x8
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  bdnz+     .loc_0x124
	  andi.     r3, r3, 0x3
	  beq-      .loc_0x3C4

	.loc_0x248:
	  mtctr     r3

	.loc_0x24C:
	  lfs       f2, 0x8(r5)
	  lfs       f1, 0x4(r5)
	  lfs       f0, 0x0(r5)
	  addi      r5, r5, 0xC
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  lfs       f2, 0x8(r6)
	  lfs       f1, 0x4(r6)
	  lfs       f0, 0x0(r6)
	  addi      r6, r6, 0xC
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  lfs       f1, 0x4(r7)
	  lfs       f0, 0x0(r7)
	  addi      r7, r7, 0x8
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  bdnz+     .loc_0x24C
	  b         .loc_0x3C4

	.loc_0x2A0:
	  cmpwi     r30, 0
	  addi      r3, r30, 0
	  ble-      .loc_0x3C4
	  rlwinm.   r0,r3,30,2,31
	  mtctr     r0
	  beq-      .loc_0x388

	.loc_0x2B8:
	  lfs       f2, 0x8(r5)
	  lfs       f1, 0x4(r5)
	  lfs       f0, 0x0(r5)
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  stw       r31, -0x8000(r4)
	  lfs       f1, 0x4(r7)
	  lfs       f0, 0x0(r7)
	  addi      r7, r7, 0x8
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  lfs       f2, 0x14(r5)
	  lfs       f1, 0x10(r5)
	  lfs       f0, 0xC(r5)
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  stw       r31, -0x8000(r4)
	  lfs       f1, 0x4(r7)
	  lfs       f0, 0x0(r7)
	  addi      r7, r7, 0x8
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  lfs       f2, 0x20(r5)
	  lfs       f1, 0x1C(r5)
	  lfs       f0, 0x18(r5)
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  stw       r31, -0x8000(r4)
	  lfs       f1, 0x4(r7)
	  lfs       f0, 0x0(r7)
	  addi      r7, r7, 0x8
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  lfs       f2, 0x2C(r5)
	  lfs       f1, 0x28(r5)
	  lfs       f0, 0x24(r5)
	  addi      r5, r5, 0x30
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  stw       r31, -0x8000(r4)
	  lfs       f1, 0x4(r7)
	  lfs       f0, 0x0(r7)
	  addi      r7, r7, 0x8
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  bdnz+     .loc_0x2B8
	  andi.     r3, r3, 0x3
	  beq-      .loc_0x3C4

	.loc_0x388:
	  mtctr     r3

	.loc_0x38C:
	  lfs       f2, 0x8(r5)
	  lfs       f1, 0x4(r5)
	  lfs       f0, 0x0(r5)
	  addi      r5, r5, 0xC
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  stw       r31, -0x8000(r4)
	  lfs       f1, 0x4(r7)
	  lfs       f0, 0x0(r7)
	  addi      r7, r7, 0x8
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  bdnz+     .loc_0x38C

	.loc_0x3C4:
	  lmw       r27, 0x2C(r1)
	  lwz       r0, 0x44(r1)
	  addi      r1, r1, 0x40
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004B778
 * Size:	00021C
 */
void DGXGraphics::blatRectangle(RectArea&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x80(r1)
	  stw       r31, 0x7C(r1)
	  stw       r30, 0x78(r1)
	  addi      r30, r3, 0
	  stw       r29, 0x74(r1)
	  addi      r29, r4, 0
	  bl        0x1C4464
	  li        r3, 0x9
	  li        r4, 0x1
	  bl        0x1C3C5C
	  li        r3, 0xB
	  li        r4, 0x1
	  bl        0x1C3C50
	  li        r3, 0xD
	  li        r4, 0x1
	  bl        0x1C3C44
	  li        r3, 0xE
	  li        r4, 0x1
	  bl        0x1C3C38
	  li        r3, 0
	  li        r4, 0x9
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C4468
	  li        r3, 0
	  li        r4, 0xB
	  li        r5, 0x1
	  li        r6, 0x5
	  li        r7, 0
	  bl        0x1C4450
	  li        r3, 0
	  li        r4, 0xD
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C4438
	  li        r3, 0
	  li        r4, 0xE
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C4420
	  lwz       r31, 0x318(r30)
	  li        r3, 0x80
	  lwz       r30, 0x31C(r30)
	  li        r4, 0
	  li        r5, 0x4
	  bl        0x1C5394
	  lwz       r0, 0x0(r29)
	  lis       r5, 0x4330
	  lwz       r6, 0x4(r29)
	  lis       r3, 0xCC01
	  xoris     r4, r0, 0x8000
	  stw       r4, 0x64(r1)
	  xoris     r0, r6, 0x8000
	  lfd       f5, -0x7B48(r2)
	  stw       r0, 0x6C(r1)
	  lfs       f4, -0x7B58(r2)
	  stw       r5, 0x60(r1)
	  lfs       f3, -0x7B60(r2)
	  stw       r5, 0x68(r1)
	  lfd       f0, 0x60(r1)
	  lfd       f1, 0x68(r1)
	  fsubs     f0, f0, f5
	  stw       r0, 0x5C(r1)
	  fsubs     f1, f1, f5
	  stw       r5, 0x58(r1)
	  stfs      f0, -0x8000(r3)
	  lfd       f0, 0x58(r1)
	  stfs      f1, -0x8000(r3)
	  fsubs     f1, f0, f5
	  stfs      f4, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  lwz       r0, 0x8(r29)
	  stw       r4, 0x34(r1)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x54(r1)
	  stw       r5, 0x50(r1)
	  lfd       f0, 0x50(r1)
	  stw       r0, 0x44(r1)
	  fsubs     f0, f0, f5
	  stw       r5, 0x40(r1)
	  stfs      f0, -0x8000(r3)
	  lfd       f0, 0x40(r1)
	  stfs      f1, -0x8000(r3)
	  fsubs     f1, f0, f5
	  stfs      f4, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  stfs      f3, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stfs      f3, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  lwz       r0, 0xC(r29)
	  stw       r5, 0x30(r1)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x4C(r1)
	  lfd       f0, 0x30(r1)
	  stw       r5, 0x48(r1)
	  fsubs     f0, f0, f5
	  lfd       f2, 0x48(r1)
	  stfs      f1, -0x8000(r3)
	  fsubs     f1, f2, f5
	  stw       r0, 0x3C(r1)
	  stfs      f1, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stw       r30, -0x8000(r3)
	  stfs      f3, -0x8000(r3)
	  stfs      f3, -0x8000(r3)
	  stw       r5, 0x38(r1)
	  stfs      f3, -0x8000(r3)
	  lfd       f1, 0x38(r1)
	  stfs      f3, -0x8000(r3)
	  fsubs     f1, f1, f5
	  stfs      f0, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stw       r30, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stfs      f3, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stfs      f3, -0x8000(r3)
	  lwz       r0, 0x84(r1)
	  lwz       r31, 0x7C(r1)
	  lwz       r30, 0x78(r1)
	  lwz       r29, 0x74(r1)
	  addi      r1, r1, 0x80
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004B994
 * Size:	0001C8
 */
void DGXGraphics::testRectangle(RectArea&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x70(r1)
	  stw       r31, 0x6C(r1)
	  stw       r30, 0x68(r1)
	  mr        r30, r4
	  lwz       r31, 0x318(r3)
	  bl        0x1C424C
	  li        r3, 0x9
	  li        r4, 0x1
	  bl        0x1C3A44
	  li        r3, 0xB
	  li        r4, 0x1
	  bl        0x1C3A38
	  li        r3, 0xD
	  li        r4, 0x1
	  bl        0x1C3A2C
	  li        r3, 0
	  li        r4, 0x9
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C425C
	  li        r3, 0
	  li        r4, 0xB
	  li        r5, 0x1
	  li        r6, 0x5
	  li        r7, 0
	  bl        0x1C4244
	  li        r3, 0
	  li        r4, 0xD
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C422C
	  li        r3, 0x80
	  li        r4, 0
	  li        r5, 0x4
	  bl        0x1C51A8
	  lwz       r0, 0x0(r30)
	  lis       r5, 0x4330
	  lwz       r6, 0x4(r30)
	  lis       r3, 0xCC01
	  xoris     r4, r0, 0x8000
	  stw       r4, 0x5C(r1)
	  xoris     r0, r6, 0x8000
	  lfd       f5, -0x7B48(r2)
	  stw       r0, 0x64(r1)
	  lfs       f4, -0x7B58(r2)
	  stw       r5, 0x58(r1)
	  lfs       f3, -0x7B60(r2)
	  stw       r5, 0x60(r1)
	  lfd       f0, 0x58(r1)
	  lfd       f1, 0x60(r1)
	  fsubs     f0, f0, f5
	  stw       r0, 0x54(r1)
	  fsubs     f1, f1, f5
	  stw       r5, 0x50(r1)
	  stfs      f0, -0x8000(r3)
	  lfd       f0, 0x50(r1)
	  stfs      f1, -0x8000(r3)
	  fsubs     f1, f0, f5
	  stfs      f4, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  lwz       r0, 0x8(r30)
	  stw       r4, 0x2C(r1)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x4C(r1)
	  stw       r5, 0x48(r1)
	  lfd       f0, 0x48(r1)
	  stw       r0, 0x3C(r1)
	  fsubs     f0, f0, f5
	  stw       r5, 0x38(r1)
	  stfs      f0, -0x8000(r3)
	  lfd       f0, 0x38(r1)
	  stfs      f1, -0x8000(r3)
	  fsubs     f1, f0, f5
	  stfs      f4, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  stfs      f3, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  lwz       r0, 0xC(r30)
	  stw       r5, 0x28(r1)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x44(r1)
	  lfd       f0, 0x28(r1)
	  stw       r5, 0x40(r1)
	  fsubs     f0, f0, f5
	  lfd       f2, 0x40(r1)
	  stfs      f1, -0x8000(r3)
	  fsubs     f1, f2, f5
	  stw       r0, 0x34(r1)
	  stfs      f1, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  stw       r5, 0x30(r1)
	  stfs      f3, -0x8000(r3)
	  lfd       f1, 0x30(r1)
	  stfs      f3, -0x8000(r3)
	  fsubs     f1, f1, f5
	  stfs      f0, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  stfs      f4, -0x8000(r3)
	  stfs      f3, -0x8000(r3)
	  lwz       r0, 0x74(r1)
	  lwz       r31, 0x6C(r1)
	  lwz       r30, 0x68(r1)
	  addi      r1, r1, 0x70
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004BB5C
 * Size:	00046C
 */
void DGXGraphics::drawRectangle(RectArea&, RectArea&, Vector3f*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x78(r1)
	  stmw      r26, 0x60(r1)
	  addi      r26, r3, 0
	  addi      r27, r4, 0
	  addi      r28, r5, 0
	  addi      r29, r6, 0
	  bl        0x1C4080
	  li        r3, 0x9
	  li        r4, 0x1
	  bl        0x1C3878
	  li        r3, 0xB
	  li        r4, 0x1
	  bl        0x1C386C
	  li        r3, 0xD
	  li        r4, 0x1
	  bl        0x1C3860
	  li        r3, 0
	  li        r4, 0x9
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C4090
	  li        r3, 0
	  li        r4, 0xB
	  li        r5, 0x1
	  li        r6, 0x5
	  li        r7, 0
	  bl        0x1C4078
	  li        r3, 0
	  li        r4, 0xD
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C4060
	  li        r3, 0
	  li        r4, 0
	  bl        0x1C73A8
	  li        r3, 0x1
	  li        r4, 0x4
	  li        r5, 0x5
	  li        r6, 0
	  bl        0x1C8044
	  lwz       r31, 0x318(r26)
	  li        r3, 0x80
	  lwz       r30, 0x31C(r26)
	  li        r4, 0
	  li        r5, 0x4
	  bl        0x1C4FB4
	  cmplwi    r29, 0
	  beq-      .loc_0xD8
	  lfs       f2, 0x8(r29)
	  b         .loc_0xDC

	.loc_0xD8:
	  lfs       f2, -0x7B58(r2)

	.loc_0xDC:
	  cmplwi    r29, 0
	  beq-      .loc_0xEC
	  lfs       f3, 0x4(r29)
	  b         .loc_0xF0

	.loc_0xEC:
	  lfs       f3, -0x7B58(r2)

	.loc_0xF0:
	  lwz       r3, 0x4(r27)
	  lis       r0, 0x4330
	  lfd       f1, -0x7B48(r2)
	  cmplwi    r29, 0
	  xoris     r3, r3, 0x8000
	  stw       r3, 0x5C(r1)
	  stw       r0, 0x58(r1)
	  lfd       f0, 0x58(r1)
	  fsubs     f0, f0, f1
	  fadds     f1, f0, f3
	  beq-      .loc_0x124
	  lfs       f3, 0x0(r29)
	  b         .loc_0x128

	.loc_0x124:
	  lfs       f3, -0x7B58(r2)

	.loc_0x128:
	  lwz       r0, 0x0(r27)
	  lis       r5, 0x4330
	  lfd       f4, -0x7B48(r2)
	  lis       r4, 0xCC01
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x5C(r1)
	  cmplwi    r29, 0
	  stw       r5, 0x58(r1)
	  lfd       f0, 0x58(r1)
	  fsubs     f0, f0, f4
	  fadds     f0, f0, f3
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  stw       r31, -0x8000(r4)
	  lwz       r0, 0x0(r28)
	  lwz       r6, 0x2E8(r26)
	  xoris     r0, r0, 0x8000
	  lwz       r3, 0x4(r28)
	  stw       r0, 0x4C(r1)
	  xoris     r0, r3, 0x8000
	  lfs       f0, 0x28(r6)
	  stw       r0, 0x54(r1)
	  lfs       f2, 0x2C(r6)
	  stw       r5, 0x48(r1)
	  stw       r5, 0x50(r1)
	  lfd       f1, 0x48(r1)
	  lfd       f3, 0x50(r1)
	  fsubs     f1, f1, f4
	  fsubs     f3, f3, f4
	  fmuls     f0, f1, f0
	  fmuls     f1, f3, f2
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  beq-      .loc_0x1BC
	  lfs       f2, 0x8(r29)
	  b         .loc_0x1C0

	.loc_0x1BC:
	  lfs       f2, -0x7B58(r2)

	.loc_0x1C0:
	  cmplwi    r29, 0
	  beq-      .loc_0x1D0
	  lfs       f3, 0x4(r29)
	  b         .loc_0x1D4

	.loc_0x1D0:
	  lfs       f3, -0x7B58(r2)

	.loc_0x1D4:
	  lwz       r3, 0x4(r27)
	  lis       r0, 0x4330
	  lfd       f1, -0x7B48(r2)
	  cmplwi    r29, 0
	  xoris     r3, r3, 0x8000
	  stw       r3, 0x4C(r1)
	  stw       r0, 0x48(r1)
	  lfd       f0, 0x48(r1)
	  fsubs     f0, f0, f1
	  fadds     f1, f0, f3
	  beq-      .loc_0x208
	  lfs       f3, 0x0(r29)
	  b         .loc_0x20C

	.loc_0x208:
	  lfs       f3, -0x7B58(r2)

	.loc_0x20C:
	  lwz       r0, 0x8(r27)
	  lis       r5, 0x4330
	  lfd       f4, -0x7B48(r2)
	  lis       r4, 0xCC01
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x4C(r1)
	  cmplwi    r29, 0
	  stw       r5, 0x48(r1)
	  lfd       f0, 0x48(r1)
	  fsubs     f0, f0, f4
	  fadds     f0, f0, f3
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  stw       r31, -0x8000(r4)
	  lwz       r0, 0x8(r28)
	  lwz       r6, 0x2E8(r26)
	  xoris     r0, r0, 0x8000
	  lwz       r3, 0x4(r28)
	  stw       r0, 0x5C(r1)
	  xoris     r0, r3, 0x8000
	  lfs       f0, 0x28(r6)
	  stw       r0, 0x54(r1)
	  lfs       f2, 0x2C(r6)
	  stw       r5, 0x58(r1)
	  stw       r5, 0x50(r1)
	  lfd       f1, 0x58(r1)
	  lfd       f3, 0x50(r1)
	  fsubs     f1, f1, f4
	  fsubs     f3, f3, f4
	  fmuls     f0, f1, f0
	  fmuls     f1, f3, f2
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  beq-      .loc_0x2A0
	  lfs       f2, 0x8(r29)
	  b         .loc_0x2A4

	.loc_0x2A0:
	  lfs       f2, -0x7B58(r2)

	.loc_0x2A4:
	  cmplwi    r29, 0
	  beq-      .loc_0x2B4
	  lfs       f3, 0x4(r29)
	  b         .loc_0x2B8

	.loc_0x2B4:
	  lfs       f3, -0x7B58(r2)

	.loc_0x2B8:
	  lwz       r3, 0xC(r27)
	  lis       r0, 0x4330
	  lfd       f1, -0x7B48(r2)
	  cmplwi    r29, 0
	  xoris     r3, r3, 0x8000
	  stw       r3, 0x4C(r1)
	  stw       r0, 0x48(r1)
	  lfd       f0, 0x48(r1)
	  fsubs     f0, f0, f1
	  fadds     f1, f0, f3
	  beq-      .loc_0x2EC
	  lfs       f3, 0x0(r29)
	  b         .loc_0x2F0

	.loc_0x2EC:
	  lfs       f3, -0x7B58(r2)

	.loc_0x2F0:
	  lwz       r0, 0x8(r27)
	  lis       r5, 0x4330
	  lfd       f4, -0x7B48(r2)
	  lis       r4, 0xCC01
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x4C(r1)
	  cmplwi    r29, 0
	  stw       r5, 0x48(r1)
	  lfd       f0, 0x48(r1)
	  fsubs     f0, f0, f4
	  fadds     f0, f0, f3
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  stw       r30, -0x8000(r4)
	  lwz       r0, 0x8(r28)
	  lwz       r6, 0x2E8(r26)
	  xoris     r0, r0, 0x8000
	  lwz       r3, 0xC(r28)
	  stw       r0, 0x5C(r1)
	  xoris     r0, r3, 0x8000
	  lfs       f0, 0x28(r6)
	  stw       r0, 0x54(r1)
	  lfs       f2, 0x2C(r6)
	  stw       r5, 0x58(r1)
	  stw       r5, 0x50(r1)
	  lfd       f1, 0x58(r1)
	  lfd       f3, 0x50(r1)
	  fsubs     f1, f1, f4
	  fsubs     f3, f3, f4
	  fmuls     f0, f1, f0
	  fmuls     f1, f3, f2
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  beq-      .loc_0x384
	  lfs       f2, 0x8(r29)
	  b         .loc_0x388

	.loc_0x384:
	  lfs       f2, -0x7B58(r2)

	.loc_0x388:
	  cmplwi    r29, 0
	  beq-      .loc_0x398
	  lfs       f3, 0x4(r29)
	  b         .loc_0x39C

	.loc_0x398:
	  lfs       f3, -0x7B58(r2)

	.loc_0x39C:
	  lwz       r3, 0xC(r27)
	  lis       r0, 0x4330
	  lfd       f1, -0x7B48(r2)
	  cmplwi    r29, 0
	  xoris     r3, r3, 0x8000
	  stw       r3, 0x4C(r1)
	  stw       r0, 0x48(r1)
	  lfd       f0, 0x48(r1)
	  fsubs     f0, f0, f1
	  fadds     f1, f0, f3
	  beq-      .loc_0x3D0
	  lfs       f3, 0x0(r29)
	  b         .loc_0x3D4

	.loc_0x3D0:
	  lfs       f3, -0x7B58(r2)

	.loc_0x3D4:
	  lwz       r0, 0x0(r27)
	  lis       r5, 0x4330
	  lfd       f4, -0x7B48(r2)
	  lis       r4, 0xCC01
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x4C(r1)
	  stw       r5, 0x48(r1)
	  lfd       f0, 0x48(r1)
	  fsubs     f0, f0, f4
	  fadds     f0, f0, f3
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  stfs      f2, -0x8000(r4)
	  stw       r30, -0x8000(r4)
	  lwz       r0, 0x0(r28)
	  lwz       r6, 0x2E8(r26)
	  xoris     r0, r0, 0x8000
	  lwz       r3, 0xC(r28)
	  stw       r0, 0x5C(r1)
	  xoris     r0, r3, 0x8000
	  lfs       f0, 0x28(r6)
	  stw       r0, 0x54(r1)
	  lfs       f2, 0x2C(r6)
	  stw       r5, 0x58(r1)
	  stw       r5, 0x50(r1)
	  lfd       f1, 0x58(r1)
	  lfd       f3, 0x50(r1)
	  fsubs     f1, f1, f4
	  fsubs     f3, f3, f4
	  fmuls     f0, f1, f0
	  fmuls     f1, f3, f2
	  stfs      f0, -0x8000(r4)
	  stfs      f1, -0x8000(r4)
	  lwz       r0, 0x7C(r1)
	  lmw       r26, 0x60(r1)
	  addi      r1, r1, 0x78
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004BFC8
 * Size:	0001DC
 */
void DGXGraphics::lineRectangle(RectArea&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x88(r1)
	  stw       r31, 0x84(r1)
	  stw       r30, 0x80(r1)
	  addi      r30, r3, 0
	  stw       r29, 0x7C(r1)
	  addi      r29, r4, 0
	  bl        0x1C3C14
	  li        r3, 0x9
	  li        r4, 0x1
	  bl        0x1C340C
	  li        r3, 0xB
	  li        r4, 0x1
	  bl        0x1C3400
	  li        r3, 0
	  li        r4, 0x9
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C3C30
	  li        r3, 0
	  li        r4, 0xB
	  li        r5, 0x1
	  li        r6, 0x5
	  li        r7, 0
	  bl        0x1C3C18
	  mr        r3, r30
	  lwz       r12, 0x3B4(r30)
	  li        r4, 0
	  li        r5, 0
	  lwz       r12, 0xCC(r12)
	  mtlr      r12
	  blrl
	  lwz       r31, 0x318(r30)
	  li        r3, 0xB0
	  lwz       r30, 0x31C(r30)
	  li        r4, 0
	  li        r5, 0x5
	  bl        0x1C4B70
	  lwz       r0, 0x0(r29)
	  lis       r5, 0x4330
	  lwz       r6, 0x4(r29)
	  lis       r3, 0xCC01
	  xoris     r4, r0, 0x8000
	  stw       r4, 0x6C(r1)
	  xoris     r6, r6, 0x8000
	  lfd       f4, -0x7B48(r2)
	  stw       r6, 0x74(r1)
	  lfs       f3, -0x7B58(r2)
	  stw       r5, 0x68(r1)
	  stw       r5, 0x70(r1)
	  lfd       f0, 0x68(r1)
	  lfd       f1, 0x70(r1)
	  fsubs     f0, f0, f4
	  stw       r6, 0x64(r1)
	  fsubs     f1, f1, f4
	  stw       r5, 0x60(r1)
	  stfs      f0, -0x8000(r3)
	  lfd       f0, 0x60(r1)
	  stfs      f1, -0x8000(r3)
	  fsubs     f1, f0, f4
	  stfs      f3, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lwz       r0, 0x8(r29)
	  stw       r4, 0x3C(r1)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x5C(r1)
	  stw       r5, 0x58(r1)
	  lfd       f0, 0x58(r1)
	  stw       r0, 0x4C(r1)
	  fsubs     f0, f0, f4
	  stw       r5, 0x48(r1)
	  stfs      f0, -0x8000(r3)
	  lfd       f0, 0x48(r1)
	  stfs      f1, -0x8000(r3)
	  fsubs     f1, f0, f4
	  stfs      f3, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lwz       r0, 0xC(r29)
	  stw       r5, 0x38(r1)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x54(r1)
	  lfd       f0, 0x38(r1)
	  stw       r5, 0x50(r1)
	  fsubs     f0, f0, f4
	  lfd       f2, 0x50(r1)
	  stw       r0, 0x44(r1)
	  fsubs     f2, f2, f4
	  stfs      f1, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stw       r5, 0x40(r1)
	  stfs      f3, -0x8000(r3)
	  lfd       f1, 0x40(r1)
	  stw       r30, -0x8000(r3)
	  fsubs     f1, f1, f4
	  stw       r4, 0x2C(r1)
	  stfs      f0, -0x8000(r3)
	  stw       r6, 0x34(r1)
	  stw       r5, 0x28(r1)
	  stfs      f1, -0x8000(r3)
	  lfd       f0, 0x28(r1)
	  stw       r5, 0x30(r1)
	  fsubs     f0, f0, f4
	  stfs      f3, -0x8000(r3)
	  lfd       f1, 0x30(r1)
	  stw       r30, -0x8000(r3)
	  fsubs     f1, f1, f4
	  stfs      f0, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stfs      f3, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lwz       r0, 0x8C(r1)
	  lwz       r31, 0x84(r1)
	  lwz       r30, 0x80(r1)
	  lwz       r29, 0x7C(r1)
	  addi      r1, r1, 0x88
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004C1A4
 * Size:	0001AC
 */
void DGXGraphics::fillRectangle(RectArea&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x70(r1)
	  stw       r31, 0x6C(r1)
	  stw       r30, 0x68(r1)
	  addi      r30, r3, 0
	  stw       r29, 0x64(r1)
	  addi      r29, r4, 0
	  bl        0x1C3A38
	  li        r3, 0x9
	  li        r4, 0x1
	  bl        0x1C3230
	  li        r3, 0xB
	  li        r4, 0x1
	  bl        0x1C3224
	  li        r3, 0
	  li        r4, 0x9
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C3A54
	  li        r3, 0
	  li        r4, 0xB
	  li        r5, 0x1
	  li        r6, 0x5
	  li        r7, 0
	  bl        0x1C3A3C
	  mr        r3, r30
	  lwz       r12, 0x3B4(r30)
	  li        r4, 0
	  li        r5, 0
	  lwz       r12, 0xCC(r12)
	  mtlr      r12
	  blrl
	  lwz       r31, 0x318(r30)
	  li        r3, 0x80
	  lwz       r30, 0x31C(r30)
	  li        r4, 0
	  li        r5, 0x4
	  bl        0x1C4994
	  lwz       r0, 0x0(r29)
	  lis       r5, 0x4330
	  lwz       r6, 0x4(r29)
	  lis       r3, 0xCC01
	  xoris     r4, r0, 0x8000
	  stw       r4, 0x54(r1)
	  xoris     r0, r6, 0x8000
	  lfd       f4, -0x7B48(r2)
	  stw       r0, 0x5C(r1)
	  lfs       f3, -0x7B58(r2)
	  stw       r5, 0x50(r1)
	  stw       r5, 0x58(r1)
	  lfd       f0, 0x50(r1)
	  lfd       f1, 0x58(r1)
	  fsubs     f0, f0, f4
	  stw       r0, 0x4C(r1)
	  fsubs     f1, f1, f4
	  stw       r5, 0x48(r1)
	  stfs      f0, -0x8000(r3)
	  lfd       f0, 0x48(r1)
	  stfs      f1, -0x8000(r3)
	  fsubs     f1, f0, f4
	  stfs      f3, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lwz       r0, 0x8(r29)
	  stw       r4, 0x24(r1)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x44(r1)
	  stw       r5, 0x40(r1)
	  lfd       f0, 0x40(r1)
	  stw       r0, 0x34(r1)
	  fsubs     f0, f0, f4
	  stw       r5, 0x30(r1)
	  stfs      f0, -0x8000(r3)
	  lfd       f0, 0x30(r1)
	  stfs      f1, -0x8000(r3)
	  fsubs     f1, f0, f4
	  stfs      f3, -0x8000(r3)
	  stw       r31, -0x8000(r3)
	  lwz       r0, 0xC(r29)
	  stw       r5, 0x20(r1)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x3C(r1)
	  lfd       f0, 0x20(r1)
	  stw       r5, 0x38(r1)
	  fsubs     f0, f0, f4
	  lfd       f2, 0x38(r1)
	  stw       r0, 0x2C(r1)
	  fsubs     f2, f2, f4
	  stfs      f1, -0x8000(r3)
	  stfs      f2, -0x8000(r3)
	  stw       r5, 0x28(r1)
	  stfs      f3, -0x8000(r3)
	  lfd       f1, 0x28(r1)
	  stw       r30, -0x8000(r3)
	  fsubs     f1, f1, f4
	  stfs      f0, -0x8000(r3)
	  stfs      f1, -0x8000(r3)
	  stfs      f3, -0x8000(r3)
	  stw       r30, -0x8000(r3)
	  lwz       r0, 0x74(r1)
	  lwz       r31, 0x6C(r1)
	  lwz       r30, 0x68(r1)
	  lwz       r29, 0x64(r1)
	  addi      r1, r1, 0x70
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004C350
 * Size:	000404
 */
void DGXGraphics::texturePrintf(Font* font, int x, int y, char* format, ...)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x2B8(r1)
	  stfd      f31, 0x2B0(r1)
	  stfd      f30, 0x2A8(r1)
	  stfd      f29, 0x2A0(r1)
	  stmw      r17, 0x264(r1)
	  bne-      cr1, .loc_0x40
	  stfd      f1, 0x28(r1)
	  stfd      f2, 0x30(r1)
	  stfd      f3, 0x38(r1)
	  stfd      f4, 0x40(r1)
	  stfd      f5, 0x48(r1)
	  stfd      f6, 0x50(r1)
	  stfd      f7, 0x58(r1)
	  stfd      f8, 0x60(r1)

	.loc_0x40:
	  stw       r3, 0x8(r1)
	  addi      r29, r3, 0
	  lis       r0, 0x500
	  stw       r4, 0xC(r1)
	  addi      r30, r4, 0
	  addi      r17, r5, 0
	  stw       r5, 0x10(r1)
	  addi      r31, r6, 0
	  addi      r4, r7, 0
	  stw       r6, 0x14(r1)
	  addi      r3, r1, 0xE0
	  stw       r7, 0x18(r1)
	  stw       r8, 0x1C(r1)
	  stw       r9, 0x20(r1)
	  stw       r10, 0x24(r1)
	  stw       r0, 0xD4(r1)
	  addi      r0, r1, 0x2C0
	  stw       r0, 0xD8(r1)
	  addi      r0, r1, 0x8
	  stw       r0, 0xDC(r1)
	  addi      r0, r1, 0xD4
	  mr        r5, r0
	  bl        0x1CA284
	  li        r3, 0
	  li        r4, 0
	  bl        0x1C6BA8
	  li        r3, 0x1
	  li        r4, 0x4
	  li        r5, 0x5
	  li        r6, 0
	  bl        0x1C7844
	  mr        r3, r29
	  lwz       r4, 0x0(r30)
	  lwz       r12, 0x3B4(r29)
	  li        r5, 0
	  lwz       r12, 0xCC(r12)
	  mtlr      r12
	  blrl
	  lwz       r0, 0x318(r29)
	  addi      r4, r1, 0xC0
	  li        r3, 0
	  stw       r0, 0xC0(r1)
	  bl        0x1C5934
	  bl        0x1C37C0
	  li        r3, 0x9
	  li        r4, 0x1
	  bl        0x1C2FB8
	  li        r3, 0xB
	  li        r4, 0x1
	  bl        0x1C2FAC
	  li        r3, 0xD
	  li        r4, 0x1
	  bl        0x1C2FA0
	  li        r3, 0
	  li        r4, 0x9
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C37D0
	  li        r3, 0
	  li        r4, 0xB
	  li        r5, 0x1
	  li        r6, 0x5
	  li        r7, 0
	  bl        0x1C37B8
	  li        r3, 0
	  li        r4, 0xD
	  li        r5, 0x1
	  li        r6, 0x4
	  li        r7, 0
	  bl        0x1C37A0
	  lfd       f29, -0x7B48(r2)
	  mr        r23, r17
	  lfs       f30, -0x7B58(r2)
	  addi      r22, r1, 0xE0
	  lfs       f31, -0x7B54(r2)
	  xoris     r28, r31, 0x8000
	  lis       r26, 0x4330
	  lis       r27, 0xCC01
	  b         .loc_0x3D8

	.loc_0x180:
	  rlwinm.   r0,r5,0,24,24
	  beq-      .loc_0x1A0
	  lbz       r4, 0x1(r22)
	  addi      r3, r30, 0
	  rlwimi    r4,r5,8,0,23
	  bl        -0x2448C
	  addi      r22, r22, 0x2
	  b         .loc_0x1B0

	.loc_0x1A0:
	  addi      r3, r30, 0
	  addi      r4, r5, 0
	  bl        -0x24544
	  addi      r22, r22, 0x1

	.loc_0x1B0:
	  mulli     r24, r3, 0x1C
	  lwz       r0, 0xC(r30)
	  lwz       r20, 0x318(r29)
	  lwz       r19, 0x31C(r29)
	  add       r6, r0, r24
	  lha       r4, 0xA(r6)
	  addi      r21, r6, 0xC
	  lha       r5, 0x6(r6)
	  li        r3, 0x80
	  lha       r0, 0x4(r6)
	  sub       r17, r23, r4
	  add       r25, r31, r5
	  add       r18, r17, r0
	  li        r4, 0
	  li        r5, 0x4
	  bl        0x1C4698
	  xoris     r7, r17, 0x8000
	  stw       r28, 0x254(r1)
	  xoris     r3, r18, 0x8000
	  stw       r7, 0x25C(r1)
	  stw       r26, 0x258(r1)
	  stw       r26, 0x250(r1)
	  lfd       f1, 0x258(r1)
	  lfd       f0, 0x250(r1)
	  fsubs     f2, f1, f29
	  stw       r3, 0x23C(r1)
	  fsubs     f1, f0, f29
	  stw       r26, 0x238(r1)
	  stfs      f2, -0x8000(r27)
	  lfd       f0, 0x238(r1)
	  stfs      f1, -0x8000(r27)
	  fsubs     f4, f0, f29
	  stfs      f30, -0x8000(r27)
	  stw       r20, -0x8000(r27)
	  lwz       r0, 0x0(r21)
	  lwz       r4, 0x4(r21)
	  xoris     r6, r0, 0x8000
	  lwz       r5, 0x2E8(r29)
	  xoris     r0, r4, 0x8000
	  stw       r6, 0x244(r1)
	  lfs       f0, 0x28(r5)
	  stw       r0, 0x24C(r1)
	  lfs       f1, 0x2C(r5)
	  stw       r26, 0x240(r1)
	  stw       r26, 0x248(r1)
	  lfd       f2, 0x240(r1)
	  lfd       f3, 0x248(r1)
	  fsubs     f2, f2, f29
	  stw       r28, 0x234(r1)
	  fsubs     f5, f3, f29
	  stw       r26, 0x230(r1)
	  fadds     f3, f31, f2
	  fadds     f6, f31, f5
	  lfd       f2, 0x230(r1)
	  stw       r0, 0x22C(r1)
	  fmuls     f5, f3, f0
	  fmuls     f6, f6, f1
	  fsubs     f3, f2, f29
	  stw       r26, 0x228(r1)
	  stfs      f5, -0x8000(r27)
	  lfd       f2, 0x228(r1)
	  stfs      f6, -0x8000(r27)
	  fsubs     f2, f2, f29
	  stfs      f4, -0x8000(r27)
	  stfs      f3, -0x8000(r27)
	  fadds     f2, f31, f2
	  stfs      f30, -0x8000(r27)
	  fmuls     f4, f2, f1
	  stw       r20, -0x8000(r27)
	  lwz       r0, 0x8(r21)
	  xoris     r5, r0, 0x8000
	  stw       r5, 0x224(r1)
	  stw       r26, 0x220(r1)
	  lfd       f2, 0x220(r1)
	  fsubs     f2, f2, f29
	  fadds     f2, f31, f2
	  fmuls     f2, f2, f0
	  stfs      f2, -0x8000(r27)
	  stw       r3, 0x21C(r1)
	  xoris     r4, r25, 0x8000
	  addi      r0, r24, 0x8
	  stw       r26, 0x218(r1)
	  stw       r4, 0x214(r1)
	  lfd       f2, 0x218(r1)
	  stw       r26, 0x210(r1)
	  fsubs     f3, f2, f29
	  lfd       f2, 0x210(r1)
	  stfs      f4, -0x8000(r27)
	  fsubs     f2, f2, f29
	  stfs      f3, -0x8000(r27)
	  stfs      f2, -0x8000(r27)
	  stfs      f30, -0x8000(r27)
	  stw       r19, -0x8000(r27)
	  lwz       r3, 0xC(r21)
	  stw       r5, 0x204(r1)
	  xoris     r3, r3, 0x8000
	  stw       r3, 0x20C(r1)
	  stw       r26, 0x200(r1)
	  stw       r26, 0x208(r1)
	  lfd       f2, 0x200(r1)
	  lfd       f3, 0x208(r1)
	  fsubs     f2, f2, f29
	  stw       r7, 0x1FC(r1)
	  fsubs     f4, f3, f29
	  stw       r26, 0x1F8(r1)
	  fadds     f3, f31, f2
	  fadds     f4, f31, f4
	  stw       r4, 0x1F4(r1)
	  lfd       f2, 0x1F8(r1)
	  stw       r6, 0x1E4(r1)
	  fmuls     f3, f3, f0
	  stw       r26, 0x1F0(r1)
	  fmuls     f6, f4, f1
	  fsubs     f5, f2, f29
	  stw       r3, 0x1EC(r1)
	  lfd       f2, 0x1F0(r1)
	  stw       r26, 0x1E0(r1)
	  fsubs     f4, f2, f29
	  stfs      f3, -0x8000(r27)
	  lfd       f2, 0x1E0(r1)
	  stw       r26, 0x1E8(r1)
	  fsubs     f2, f2, f29
	  stfs      f6, -0x8000(r27)
	  lfd       f3, 0x1E8(r1)
	  stfs      f5, -0x8000(r27)
	  fadds     f2, f31, f2
	  fsubs     f3, f3, f29
	  stfs      f4, -0x8000(r27)
	  fmuls     f0, f2, f0
	  stfs      f30, -0x8000(r27)
	  fadds     f2, f31, f3
	  stw       r19, -0x8000(r27)
	  fmuls     f1, f2, f1
	  stfs      f0, -0x8000(r27)
	  stfs      f1, -0x8000(r27)
	  lwz       r3, 0xC(r30)
	  lhax      r0, r3, r0
	  add       r23, r23, r0

	.loc_0x3D8:
	  lbz       r5, 0x0(r22)
	  cmplwi    r5, 0
	  bne+      .loc_0x180
	  lmw       r17, 0x264(r1)
	  lwz       r0, 0x2BC(r1)
	  lfd       f31, 0x2B0(r1)
	  lfd       f30, 0x2A8(r1)
	  lfd       f29, 0x2A0(r1)
	  addi      r1, r1, 0x2B8
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	0001A0
 */
void DGXGraphics::showCrash(u16, OSContext*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000184
 */
void DGXGraphics::showError(char*, char*, int)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000D0
 */
void DGXGraphics::directDrawChar(int, int, int)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000F8
 */
void DGXGraphics::directDrawChar(RectArea&, RectArea&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0001D8
 */
void DGXGraphics::directPrint(int, int, char*, ...)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000108
 */
void DGXGraphics::directErase(RectArea&, bool)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8004C754
 * Size:	00003C
 */
Shape::Shape()
{
}

/*
 * --INFO--
 * Address:	8004C790
 * Size:	00013C
 */
void Shape::optimize()
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x30(r1)
	  stmw      r25, 0x14(r1)
	  mr        r31, r3
	  lwz       r0, 0x26C(r3)
	  cmplwi    r0, 0
	  bne-      .loc_0x58
	  li        r3, 0x10
	  bl        -0x57B0
	  lis       r4, 0x8003
	  addi      r4, r4, 0x38B4
	  li        r5, 0
	  li        r6, 0x8
	  li        r7, 0x1
	  bl        0x1C845C
	  stw       r3, 0x26C(r31)
	  lfs       f0, -0x7B58(r2)
	  lwz       r3, 0x26C(r31)
	  stfs      f0, 0x0(r3)
	  lwz       r3, 0x26C(r31)
	  stfs      f0, 0x4(r3)

	.loc_0x58:
	  li        r0, 0x17
	  stw       r0, 0x13C(r31)
	  li        r5, 0
	  li        r3, 0x1
	  b         .loc_0x84

	.loc_0x6C:
	  addi      r0, r5, 0x5
	  lwz       r4, 0x13C(r31)
	  slw       r0, r3, r0
	  or        r0, r4, r0
	  stw       r0, 0x13C(r31)
	  addi      r5, r5, 0x1

	.loc_0x84:
	  lwz       r0, 0x248(r31)
	  cmpw      r5, r0
	  blt+      .loc_0x6C
	  lwz       r0, 0x50(r31)
	  cmpwi     r0, 0
	  beq-      .loc_0x128
	  li        r28, 0
	  li        r29, 0
	  b         .loc_0x11C

	.loc_0xA8:
	  li        r27, 0
	  li        r30, 0
	  b         .loc_0x100

	.loc_0xB4:
	  lwz       r3, 0x24(r3)
	  addi      r0, r30, 0xC
	  li        r25, 0
	  lwzx      r26, r3, r0
	  b         .loc_0xDC

	.loc_0xC8:
	  lwz       r3, 0x1C(r26)
	  lwz       r4, 0x18(r26)
	  bl        0x1AA3BC
	  addi      r26, r26, 0x74
	  addi      r25, r25, 0x1

	.loc_0xDC:
	  lwz       r3, 0x54(r31)
	  addi      r0, r3, 0x24
	  lwzx      r3, r29, r0
	  addi      r0, r3, 0x8
	  lwzx      r0, r30, r0
	  cmpw      r25, r0
	  blt+      .loc_0xC8
	  addi      r30, r30, 0x10
	  addi      r27, r27, 0x1

	.loc_0x100:
	  lwz       r0, 0x54(r31)
	  add       r3, r29, r0
	  lwz       r0, 0x20(r3)
	  cmpw      r27, r0
	  blt+      .loc_0xB4
	  addi      r29, r29, 0x30
	  addi      r28, r28, 0x1

	.loc_0x11C:
	  lwz       r0, 0x50(r31)
	  cmpw      r28, r0
	  blt+      .loc_0xA8

	.loc_0x128:
	  lmw       r25, 0x14(r1)
	  lwz       r0, 0x34(r1)
	  addi      r1, r1, 0x30
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8004C8CC
 * Size:	000004
 */
void DGXGraphics::setPointSize(f32)
{
}

/*
 * --INFO--
 * Address:	8004C8D0
 * Size:	000004
 */
void DGXGraphics::setClippingPlane(bool, Plane*)
{
}

/*
 * --INFO--
 * Address:	8004C8D4
 * Size:	000004
 */
void DGXGraphics::drawOutline(Camera&, Shape*)
{
}

/*
 * --INFO--
 * Address:	8004C8D8
 * Size:	000004
 */
void DGXGraphics::drawOneStrip(Vector3f*, Vector3f*, Vector2f*, int)
{
}

/*
 * --INFO--
 * Address:	8004C8DC
 * Size:	00002C
 */
void __sinit_dgxGraphics_cpp(void)
{
	/*
	.loc_0x0:
	  li        r0, 0xFF
	  lis       r3, 0x803A
	  stbu      r0, -0x2BD0(r3)
	  stb       r0, 0x1(r3)
	  stb       r0, 0x2(r3)
	  stb       r0, 0x3(r3)
	  stb       r0, 0x4(r3)
	  stb       r0, 0x5(r3)
	  stb       r0, 0x6(r3)
	  stb       r0, 0x7(r3)
	  blr
	*/
}
