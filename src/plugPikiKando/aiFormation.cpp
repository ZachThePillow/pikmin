#include "PikiAI.h"
#include "FormationMgr.h"
#include "Navi.h"
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
DEFINE_PRINT("aiFormation")

/*
 * --INFO--
 * Address:	800B98D8
 * Size:	00032C
 */
void ActFormation::animationKeyUpdated(PaniAnimKeyEvent& event)
{
	switch (event.mEventType) {
	case KEY_Action0:
		mPiki->mVelocity.set(0.0f, 0.0f, 0.0f);
		mPiki->mTargetVelocity.set(0.0f, 0.0f, 0.0f);
		break;

	case KEY_Finished:
		if (mIsIdling || mHasStartedIdleAnim) {
			if (mHasStartedIdleAnim) {
				mIdleTimer          = (15.0f * gsys->getRand(1.0f)) + 15.0f;
				mHasStartedIdleAnim = 0;
			}
			mPiki->startMotion(PaniMotionInfo(PIKIANIM_Wait, this), PaniMotionInfo(PIKIANIM_Wait));
			break;
		}

		if (mIsTripping == 0) {
			mPiki->startMotion(PaniMotionInfo(PIKIANIM_Korobu, this), PaniMotionInfo(PIKIANIM_Korobu));
			Vector3f dir(sinf(mPiki->mFaceDirection), 0.0f, cosf(mPiki->mFaceDirection));
			f32 speed              = mPiki->mVelocity.length();
			mPiki->mVelocity       = speed * dir;
			mPiki->mTargetVelocity = speed * dir;
			mIdleTimer             = gsys->getRand(1.0f) + 0.8f;
			mIsTripping            = 1;
			break;
		}

		if (mIsTripping == 1) {
			mIsOnFloorTripped = 0;
			mPiki->startMotion(PaniMotionInfo(PIKIANIM_Run), PaniMotionInfo(PIKIANIM_Run));
			break;
		}

		if (mHasStartedRunAnim) {
			mHasStartedRunAnim = 0;
			if (mDistanceToTarget > 5.0f) {
				mPiki->startMotion(PaniMotionInfo(PIKIANIM_Run), PaniMotionInfo(PIKIANIM_Run));
			}
		}

		break;
	}
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0xF0(r1)
	  stfd      f31, 0xE8(r1)
	  stfd      f30, 0xE0(r1)
	  stfd      f29, 0xD8(r1)
	  stw       r31, 0xD4(r1)
	  addi      r31, r3, 0
	  stw       r30, 0xD0(r1)
	  stw       r29, 0xCC(r1)
	  lwz       r0, 0x0(r4)
	  cmpwi     r0, 0x1
	  beq-      .loc_0x44
	  bge-      .loc_0x304
	  cmpwi     r0, 0
	  bge-      .loc_0x80
	  b         .loc_0x304

	.loc_0x44:
	  lwz       r3, 0xC(r31)
	  lfs       f0, -0x4918(r13)
	  stfsu     f0, 0x70(r3)
	  lfs       f0, -0x4914(r13)
	  stfs      f0, 0x4(r3)
	  lfs       f0, -0x4910(r13)
	  stfs      f0, 0x8(r3)
	  lwz       r3, 0xC(r31)
	  lfs       f0, -0x490C(r13)
	  stfsu     f0, 0xA4(r3)
	  lfs       f0, -0x4908(r13)
	  stfs      f0, 0x4(r3)
	  lfs       f0, -0x4904(r13)
	  stfs      f0, 0x8(r3)
	  b         .loc_0x304

	.loc_0x80:
	  lbz       r0, 0x29(r31)
	  cmplwi    r0, 0
	  bne-      .loc_0x98
	  lbz       r0, 0x2A(r31)
	  cmplwi    r0, 0
	  beq-      .loc_0x130

	.loc_0x98:
	  lbz       r0, 0x2A(r31)
	  cmplwi    r0, 0
	  beq-      .loc_0xEC
	  bl        0x15E6F4
	  xoris     r0, r3, 0x8000
	  lfd       f4, -0x6D50(r2)
	  stw       r0, 0xC4(r1)
	  lis       r3, 0x4330
	  lfs       f2, -0x6D64(r2)
	  li        r0, 0
	  stw       r3, 0xC0(r1)
	  lfs       f0, -0x6D68(r2)
	  lfd       f3, 0xC0(r1)
	  lfs       f1, -0x6D60(r2)
	  fsubs     f3, f3, f4
	  fdivs     f2, f3, f2
	  fmuls     f0, f0, f2
	  fmuls     f0, f1, f0
	  fadds     f0, f1, f0
	  stfs      f0, 0x1C(r31)
	  stb       r0, 0x2A(r31)

	.loc_0xEC:
	  cmplwi    r31, 0
	  addi      r29, r31, 0
	  beq-      .loc_0xFC
	  addi      r29, r29, 0x14

	.loc_0xFC:
	  addi      r3, r1, 0x9C
	  li        r4, 0x3
	  bl        0x6557C
	  addi      r30, r3, 0
	  addi      r5, r29, 0
	  addi      r3, r1, 0xA4
	  li        r4, 0x3
	  bl        0x6559C
	  mr        r4, r3
	  lwz       r3, 0xC(r31)
	  mr        r5, r30
	  bl        0x10FD8
	  b         .loc_0x304

	.loc_0x130:
	  lwz       r0, 0x30(r31)
	  cmpwi     r0, 0
	  bne-      .loc_0x274
	  cmplwi    r31, 0
	  addi      r29, r31, 0
	  beq-      .loc_0x14C
	  addi      r29, r29, 0x14

	.loc_0x14C:
	  addi      r3, r1, 0x8C
	  li        r4, 0x14
	  bl        0x6552C
	  addi      r30, r3, 0
	  addi      r5, r29, 0
	  addi      r3, r1, 0x94
	  li        r4, 0x14
	  bl        0x6554C
	  mr        r4, r3
	  lwz       r3, 0xC(r31)
	  mr        r5, r30
	  bl        0x10F88
	  lwz       r3, 0xC(r31)
	  lfs       f1, 0xA0(r3)
	  bl        0x1620F8
	  lwz       r3, 0xC(r31)
	  fmr       f30, f1
	  lfs       f1, 0xA0(r3)
	  bl        0x16227C
	  lwz       r3, 0xC(r31)
	  fmr       f31, f1
	  lfsu      f1, 0x70(r3)
	  lfs       f29, -0x4900(r13)
	  lfs       f0, 0x4(r3)
	  fmuls     f1, f1, f1
	  lfs       f2, 0x8(r3)
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xABE5C
	  fmuls     f2, f31, f1
	  fmuls     f3, f29, f1
	  fmuls     f1, f30, f1
	  stfs      f2, 0x48(r1)
	  lfs       f0, 0x48(r1)
	  stfs      f0, 0x80(r1)
	  stfs      f3, 0x84(r1)
	  stfs      f1, 0x88(r1)
	  lwz       r4, 0xC(r31)
	  lwz       r3, 0x80(r1)
	  lwz       r0, 0x84(r1)
	  stw       r3, 0x70(r4)
	  stw       r0, 0x74(r4)
	  lwz       r0, 0x88(r1)
	  stw       r0, 0x78(r4)
	  stfs      f2, 0x74(r1)
	  stfs      f3, 0x78(r1)
	  stfs      f1, 0x7C(r1)
	  lwz       r4, 0xC(r31)
	  lwz       r3, 0x74(r1)
	  lwz       r0, 0x78(r1)
	  stw       r3, 0xA4(r4)
	  stw       r0, 0xA8(r4)
	  lwz       r0, 0x7C(r1)
	  stw       r0, 0xAC(r4)
	  bl        0x15E56C
	  xoris     r0, r3, 0x8000
	  lfd       f4, -0x6D50(r2)
	  stw       r0, 0xC4(r1)
	  lis       r3, 0x4330
	  lfs       f2, -0x6D64(r2)
	  li        r0, 0x1
	  stw       r3, 0xC0(r1)
	  lfs       f1, -0x6D68(r2)
	  lfd       f3, 0xC0(r1)
	  lfs       f0, -0x6D5C(r2)
	  fsubs     f3, f3, f4
	  fdivs     f2, f3, f2
	  fmuls     f1, f1, f2
	  fadds     f0, f0, f1
	  stfs      f0, 0x1C(r31)
	  stw       r0, 0x30(r31)
	  b         .loc_0x304

	.loc_0x274:
	  cmpwi     r0, 0x1
	  bne-      .loc_0x2B4
	  li        r0, 0
	  stb       r0, 0x2B(r31)
	  addi      r3, r1, 0x64
	  li        r4, 0
	  bl        0x653F4
	  addi      r30, r3, 0
	  addi      r3, r1, 0x6C
	  li        r4, 0
	  bl        0x653E4
	  mr        r4, r3
	  lwz       r3, 0xC(r31)
	  mr        r5, r30
	  bl        0x10E54
	  b         .loc_0x304

	.loc_0x2B4:
	  lbz       r0, 0x2C(r31)
	  cmplwi    r0, 0
	  beq-      .loc_0x304
	  li        r0, 0
	  stb       r0, 0x2C(r31)
	  lfs       f1, 0x24(r31)
	  lfs       f0, -0x6D58(r2)
	  fcmpo     cr0, f1, f0
	  ble-      .loc_0x304
	  addi      r3, r1, 0x54
	  li        r4, 0
	  bl        0x653A0
	  addi      r30, r3, 0
	  addi      r3, r1, 0x5C
	  li        r4, 0
	  bl        0x65390
	  mr        r4, r3
	  lwz       r3, 0xC(r31)
	  mr        r5, r30
	  bl        0x10E00

	.loc_0x304:
	  lwz       r0, 0xF4(r1)
	  lfd       f31, 0xE8(r1)
	  lfd       f30, 0xE0(r1)
	  lfd       f29, 0xD8(r1)
	  lwz       r31, 0xD4(r1)
	  lwz       r30, 0xD0(r1)
	  lwz       r29, 0xCC(r1)
	  addi      r1, r1, 0xF0
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800B9C04
 * Size:	00005C
 */
ActFormation::ActFormation(Piki* piki)
    : Action(piki, true)
{
	mFormMgr = nullptr;
}

/*
 * --INFO--
 * Address:	800B9C60
 * Size:	000148
 */
void ActFormation::getFormPoint()
{
	mPiki->mFormPoint = mFormMgr->getFormPoint(mPiki);
	PRINT("piki %x got formPt %x owner is %x\n", mPiki, mPiki->mFormPoint, mPiki->mFormPoint->getOwner());

	Iterator iter(mFormMgr);
	CI_LOOP(iter)
	{
		Creature* member = *iter;
		if (member->mFormPoint == mPiki->mFormPoint && mPiki != member) {
			PRINT("########################################\n");
			PRINT(" creature %x and piki %x share same formPoint %x\n", member, mPiki, member->mFormPoint);
			PRINT(" owner is %x\n", member->mFormPoint->getOwner());
			while (true) {
				// bad code gets locked in the INFINITE WHILE LOOP
				;
			}
		}
	}
	mUseLastFormationPosition = 0;
}

/*
 * --INFO--
 * Address:	800B9DA8
 * Size:	0000F4
 */
void ActFormation::init(Creature* target)
{
	if (mPiki->isKinoko()) {
		ERROR("formation kinoko!");
	}

	mInFormation = 1;

	if (target->mObjType != OBJTYPE_Navi) {
		PRINT("target is not navi (%d)\n", target->mObjType);
	}

	Navi* navi                = static_cast<Navi*>(target);
	mFormMgr                  = navi->mFormMgr;
	mUseLastFormationPosition = 1;
	mIdleTimer                = (2.0f * gsys->getRand(1.0f)) + 4.0f;
	mPiki->startMotion(PaniMotionInfo(PIKIANIM_Run), PaniMotionInfo(PIKIANIM_Run));
	mPiki->unsetPastel();
	mIsIdling           = 0;
	mHasStartedIdleAnim = 0;
	mIsOnFloorTripped   = 0;
	mIsTripping         = 0;
}

/*
 * --INFO--
 * Address:	800B9E9C
 * Size:	00004C
 */
void ActFormation::cleanup()
{
	if (mFormMgr) {
		mFormMgr->exit(mPiki);
		mPiki->mFormPoint = nullptr;
		mFormMgr          = nullptr;
	}
}

/*
 * --INFO--
 * Address:	800B9EE8
 * Size:	0006A4
 */
int ActFormation::exec()
{
	if (mIsOnFloorTripped) {
		mIdleTimer -= gsys->getFrameTime();
		if (mIdleTimer < 0.0f) {
			mPiki->mPikiAnimMgr.finishMotion(this);
		}

		return ACTOUT_Continue;
	}

	Vector3f pos;
	if (mUseLastFormationPosition) {
		pos = mFormMgr->getLastCentre();
	} else {
		pos = mPiki->mFormPoint->getPos();
	}

	Vector3f directionToTarget = pos - mPiki->mPosition;
	f32 distanceToTarget       = directionToTarget.length();
	mDistanceToTarget          = distanceToTarget;
	mPiki->mTargetVelocity.set(0.0f, 0.0f, 0.0f);

	if (mUseLastFormationPosition && distanceToTarget < 100.0f) {
		getFormPoint();
	} else if (!mUseLastFormationPosition && distanceToTarget < 6.0f) {
		mInFormation = false;
		mPiki->mFaceDirection += 2.5f * (angDist(mPiki->mNavi->mFaceDirection, mPiki->mFaceDirection) * gsys->getFrameTime());

		if (!mIsIdling) {
			mPiki->mPikiAnimMgr.finishMotion(this);
			mIsIdling           = 1;
			mIdleTimer          = (15.0f * gsys->getRand(1.0f)) + 15.0f;
			mHasStartedIdleAnim = 0;
		} else {
			mIdleTimer -= gsys->getFrameTime();
			if (mIdleTimer < 0.0f && !mHasStartedIdleAnim) {
				// this is set up for far more flexibility than it ended up having wtf
				int baseIdx[1]    = { PIKIANIM_Wait };
				f32 v             = 1.0f;
				int randOffsetIdx = int(v * gsys->getRand(1.0f));
				if (randOffsetIdx >= 1) {
					randOffsetIdx = 0;
				}
				mPiki->startMotion(PaniMotionInfo(baseIdx[randOffsetIdx], this), PaniMotionInfo(baseIdx[randOffsetIdx]));
				mHasStartedIdleAnim = 1;
			}
		}

		return ACTOUT_Continue;
	}

	if (!mIsIdling && !mIsOnFloorTripped && gsys->getRand(1.0f) > 0.99f && gsys->getRand(1.0f) > 0.99f
	    && mPiki->mVelocity.length() > mPiki->getSpeed(0.5f)) {
		mPiki->mPikiAnimMgr.finishMotion(this);
		mIsTripping       = 0;
		mIsOnFloorTripped = 1;
		return ACTOUT_Continue;
	}

	if (mIsIdling) {
		mIsIdling          = 0;
		mHasStartedRunAnim = 0;
		mPiki->startMotion(PaniMotionInfo(PIKIANIM_Run), PaniMotionInfo(PIKIANIM_Run));
	}

	Vector3f zeroVector(0.0f, 0.0f, 0.0f);
	Vector3f normalisedDirection = pos - mPiki->mPosition;
	normalisedDirection.normalise();

	Vector3f perpDirection(-normalisedDirection.z, 0.0f, normalisedDirection.x);
	bool shouldApplyDrag = false;

	Vector3f flatDirection = pos - mPiki->mPosition;
	flatDirection.y        = 0.0f;
	f32 flatDistance       = flatDirection.length();
	if (flatDistance > 0.0f) {
		flatDirection = (1.0f / flatDistance) * flatDirection;
	} else {
		f32 randAngle = 2.0f * (PI * gsys->getRand(1.0f));
		flatDirection.set(cosf(randAngle), 0.0f, sinf(randAngle));
	}

	f32 speedMultiplier = 0.0f;
	if (flatDistance > 30.0f) {
		speedMultiplier = (flatDistance - 30.0f) / 10.0f;
		if (speedMultiplier > 1.0f) {
			speedMultiplier = 1.0f;
		}
	}

	mPiki->setSpeed(speedMultiplier, flatDirection);
	f32 dragFactor = 1.0f;
	if (shouldApplyDrag) {
		mPiki->mTargetVelocity = (1.0f - dragFactor) * mPiki->mTargetVelocity + dragFactor * zeroVector;
	}

	return ACTOUT_Continue;
}
