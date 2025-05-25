#include "sysNew.h"

#include "MemStat.h"
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
 * Size:	0000F0
 */
DEFINE_PRINT(nullptr);

/*
 * --INFO--
 * Address:	80047004
 * Size:	000164
 */
void* System::alloc(u32 size)
{
	void* result = nullptr;
	if (size & 0x3) {
		size = (size + 3) & ~0x3;
	}

	if (gsys->mActiveHeapIdx >= 0) {
		AyuHeap* heap = &gsys->mHeaps[gsys->mActiveHeapIdx];
		result        = heap->push(size);
		if (!result) {
			PRINT("new[] %d failed in heap '%s'", gsys->mActiveHeapIdx, size);
		}

		if (size == 0 || gsys->mForceTogglePrint) {
			u32 print          = !!gsys->mTogglePrint;
			gsys->mTogglePrint = 1;
			gsys->mTogglePrint = print;
		}

		MemInfo* info = gsys->mCurrMemInfo;
		while (info) {
			info->mMemorySize += size;
			info = static_cast<MemInfo*>(info->mParent);
		}

		if ((u32)result & 0x3) {
			PRINT("idek man", (u32)result);
		}

		int length = size / 4;
		for (int i = 0; i < length; i++) {
			((u32*)result)[i] = 0;
		}
	}

	return result;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000044
 */
void* operator new(u32, int)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80047168
 * Size:	000044
 */
void* operator new[](u32 size, int alignment)
{
	// this is what this SHOULD be, but it's doing the subtraction in a weird order
	return (void*)(ALIGN_NEXT((u32)System::alloc(size + alignment), alignment));
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x20(r1)
	  stw       r31, 0x1C(r1)
	  addi      r31, r4, 0
	  add       r3, r3, r31
	  bl        -0x17C
	  subi      r0, r31, 0x1
	  add       r3, r31, r3
	  not       r4, r0
	  subi      r0, r3, 0x1
	  and       r3, r4, r0
	  lwz       r0, 0x24(r1)
	  lwz       r31, 0x1C(r1)
	  addi      r1, r1, 0x20
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800471AC
 * Size:	000004
 */
void operator delete(void*)
{
}

/*
 * --INFO--
 * Address:	800471B0
 * Size:	000004
 */
void operator delete[](void*)
{
}
