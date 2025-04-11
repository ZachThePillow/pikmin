#include "TAI/Action.h"
#include "teki.h"
#include "sysNew.h"
#include "DebugLog.h"

/*
 * --INFO--
 * Address:	........
 * Size:	000098
 */
DEFINE_ERROR()

/*
 * --INFO--
 * Address:	........
 * Size:	0000F0
 */
DEFINE_PRINT("tai");

/*
 * --INFO--
 * Address:	80126E04
 * Size:	00005C
 */
TaiSerialAction::TaiSerialAction(int nextState, int count)
    : TaiAction(nextState)
    , mCount(count)
{
	mActionQueue = new TaiAction*[mCount];
}

/*
 * --INFO--
 * Address:	80126E60
 * Size:	000044
 */
void TaiSerialAction::start(Teki& teki)
{
	teki.mCurrentQueueId = 0;
	mActionQueue[teki.mCurrentQueueId]->start(teki);
}

/*
 * --INFO--
 * Address:	80126EA8
 * Size:	000080
 */
void TaiSerialAction::finish(Teki& teki)
{
	for (int i = 0; i < mCount; i++) {
		TaiAction* action = mActionQueue[i];
		action->finish(teki);
	}
}

/*
 * --INFO--
 * Address:	80126F2C
 * Size:	0000A8
 */
bool TaiSerialAction::act(Teki& teki)
{
	if (mActionQueue[teki.mCurrentQueueId]->act(teki)) {
		if (teki.mCurrentQueueId == mCount - 1) {
			return true;
		}
		teki.mCurrentQueueId++;
		mActionQueue[teki.mCurrentQueueId]->start(teki);
	}

	return false;
}

/*
 * --INFO--
 * Address:	80126FDC
 * Size:	0000B4
 */
bool TaiSerialAction::actByEvent(TekiEvent& event)
{
	Teki* teki = event.mTeki;
	if (mActionQueue[teki->mCurrentQueueId]->actByEvent(event)) {
		if (teki->mCurrentQueueId == mCount - 1) {
			return true;
		}
		teki->mCurrentQueueId++;
		mActionQueue[teki->mCurrentQueueId]->start(*event.mTeki);
	}

	return false;
}

/*
 * --INFO--
 * Address:	80127098
 * Size:	00004C
 */
TaiState::TaiState(int count)
    : mCount(count)
{
	mActions = new TaiAction*[mCount];
}

/*
 * --INFO--
 * Address:	801270E4
 * Size:	000080
 */
void TaiState::start(Teki& teki)
{
	for (int i = 0; i < mCount; i++) {
		TaiAction* action = mActions[i];
		action->start(teki);
	}
}

/*
 * --INFO--
 * Address:	80127164
 * Size:	000080
 */
void TaiState::finish(Teki& teki)
{
	for (int i = 0; i < mCount; i++) {
		TaiAction* action = mActions[i];
		action->finish(teki);
	}
}

/*
 * --INFO--
 * Address:	801271E4
 * Size:	0000EC
 */
bool TaiState::act(Teki& teki)
{
	Teki* pTeki = &teki;
	for (int i = 0; i < mCount; i++) {
		TaiAction* action = mActions[i];
		if (action->act(teki) && action->hasNextState()) {
			PRINT("transit:%08x:i:%d:%d->%d(%d),t:%d,m:%d\n", (u32)pTeki, i, teki.mStateID, action->mNextState, teki.mReturnStateID,
			      teki.mTekiType, teki.mTekiAnimator->getCurrentMotionIndex());

			volatile int& stateID = teki.mStateID;
			int startVal          = teki.mStateID;
			if (action->mNextState == -2) {
				stateID = teki.mReturnStateID;
			} else {
				stateID = action->mNextState;
			}
			teki.mReturnStateID = startVal;
			return true;
		}
	}

	return false;
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x38(r1)
	  stw       r31, 0x34(r1)
	  li        r31, 0
	  stw       r30, 0x30(r1)
	  stw       r29, 0x2C(r1)
	  stw       r28, 0x28(r1)
	  addi      r28, r3, 0
	  stw       r4, 0xC(r1)
	  lwz       r30, 0xC(r1)
	  stw       r31, 0x20(r1)
	  b         .loc_0xB8

	.loc_0x34:
	  lwz       r3, 0x8(r28)
	  mr        r4, r30
	  lwzx      r29, r3, r31
	  mr        r3, r29
	  lwz       r12, 0x4(r29)
	  lwz       r12, 0x10(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0xA8
	  mr        r3, r29
	  lwz       r12, 0x4(r29)
	  lwz       r12, 0x18(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0xA8
	  lwz       r0, 0x0(r29)
	  addi      r3, r30, 0x324
	  lwz       r4, 0x324(r30)
	  cmpwi     r0, -0x2
	  bne-      .loc_0x98
	  lwz       r0, 0x330(r30)
	  stw       r0, 0x0(r3)
	  b         .loc_0x9C

	.loc_0x98:
	  stw       r0, 0x0(r3)

	.loc_0x9C:
	  stw       r4, 0x330(r30)
	  li        r3, 0x1
	  b         .loc_0xCC

	.loc_0xA8:
	  lwz       r3, 0x20(r1)
	  addi      r31, r31, 0x4
	  addi      r0, r3, 0x1
	  stw       r0, 0x20(r1)

	.loc_0xB8:
	  lwz       r3, 0x20(r1)
	  lwz       r0, 0x4(r28)
	  cmpw      r3, r0
	  blt+      .loc_0x34
	  li        r3, 0

	.loc_0xCC:
	  lwz       r0, 0x3C(r1)
	  lwz       r31, 0x34(r1)
	  lwz       r30, 0x30(r1)
	  lwz       r29, 0x2C(r1)
	  lwz       r28, 0x28(r1)
	  addi      r1, r1, 0x38
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	801272F0
 * Size:	0000F4
 */
bool TaiState::eventPerformed(TekiEvent& event)
{
	// NON-MATCHING
	for (int i = 0; i < mCount; i++) {
		TaiAction* action = mActions[i];
		if (action->actByEvent(event) && action->hasNextState()) {
			PRINT("eventPerformed:%08x:i:%d:%d->%d(%d),t:%d,m:%d\n", event.mTeki, i, event.mTeki->mStateID, action->mNextState,
			      event.mTeki->mReturnStateID, event.mTeki->mTekiType, event.mTeki->mTekiAnimator->getCurrentMotionIndex());

			int startVal          = event.mTeki->mStateID;
			volatile int& stateID = event.mTeki->mStateID;
			int nextState         = action->mNextState;
			if (nextState == -2) {
				stateID = event.mTeki->mReturnStateID;
			} else {
				stateID = nextState;
			}
			event.mTeki->mReturnStateID = startVal;
			return true;
		}
	}

	return false;
}

/*
 * --INFO--
 * Address:	801273E4
 * Size:	000064
 */
TaiStrategy::TaiStrategy(int stateCount, int stateID)
{
	init(stateCount, stateID);
}

/*
 * --INFO--
 * Address:	80127448
 * Size:	00004C
 */
void TaiStrategy::init(int stateCount, int stateID)
{
	mStateCount = stateCount;
	mStateList  = new TaiState*[mStateCount];
	mStateID    = stateID;
}

/*
 * --INFO--
 * Address:	80127494
 * Size:	000014
 */
void TaiStrategy::start(Teki& teki)
{
	teki.mStateID      = mStateID;
	teki.mIsStateReady = true;
}

/*
 * --INFO--
 * Address:	801274A8
 * Size:	0000CC
 */
void TaiStrategy::act(Teki& teki)
{
	if (teki.mIsStateReady) {
		mStateList[teki.mStateID]->start(teki);
		teki.mIsStateReady = false;
	}

	int stateID = teki.mStateID;
	if (mStateList[teki.mStateID]->act(teki)) {
		mStateList[stateID]->finish(teki);
		teki.mIsStateReady = true;
	}
}

/*
 * --INFO--
 * Address:	80127574
 * Size:	000090
 */
void TaiStrategy::eventPerformed(TekiEvent& event)
{
	Teki* teki  = event.mTeki;
	int stateID = teki->mStateID;
	if (mStateList[teki->mStateID]->eventPerformed(event)) {
		mStateList[stateID]->finish(*teki);
		teki->mIsStateReady = true;
	}
}
