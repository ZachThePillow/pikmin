#include "PikiAI.h"
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
DEFINE_PRINT("aiRandomBoid") // ... no you're not

/*
 * --INFO--
 * Address:	800B5688
 * Size:	00006C
 */
ActChase::ActChase(Piki* piki)
    : Action(piki, true)
{
	mTarget.reset();
}

/*
 * --INFO--
 * Address:	800B56F4
 * Size:	000004
 */
void ActChase::Initialiser::initialise(Action*)
{
}

/*
 * --INFO--
 * Address:	800B56F8
 * Size:	0000D4
 */
void ActChase::init(Creature* target)
{
	mChaseTimer = randFloat(2.0f) + 4.0f;
	mTarget.set(target);
	mActor->startMotion(PaniMotionInfo(PIKIANIM_Run), PaniMotionInfo(PIKIANIM_Run));
}

/*
 * --INFO--
 * Address:	800B57CC
 * Size:	000040
 */
void ActChase::cleanup()
{
	Creature* target = mTarget.getPtr();
	mTarget.reset();
}

/*
 * --INFO--
 * Address:	800B580C
 * Size:	00023C
 */
int ActChase::exec()
{
	u32 badCompiler[2];
	Creature* target = mTarget.getPtr();
	if (!target->isVisible()) {
		return ACTOUT_Fail;
	}

	mChaseTimer -= gsys->getFrameTime();

	if (!mActor->_500.isNull() && mActor->_500.getPtr() == mTarget.getPtr()) {
		return ACTOUT_Success;
	}

	if (mChaseTimer < 0.0f) {
		return ACTOUT_Fail;
	}

	mActor->mTargetVelocity.set(0.0f, 0.0f, 0.0f);

	Vector3f chaseDir = target->mPosition - mActor->mPosition;
	chaseDir.y        = 0.0f;
	f32 chaseDist     = chaseDir.length();
	if (chaseDist > 0.0f) {
		chaseDir = (1.0f / chaseDist) * chaseDir;
	} else {
		f32 randAngle = 2.0f * (randFloat(PI));
		chaseDir.set(cosf(randAngle), 0.0f, sinf(randAngle));
	}

	mActor->setSpeed(1.0f, chaseDir);
	return ACTOUT_Continue;
}
