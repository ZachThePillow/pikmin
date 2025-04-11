#ifndef _TAI_AJUDGE_H
#define _TAI_AJUDGE_H

#include "types.h"
#include "TAI/Action.h"
#include "teki.h"

/**
 * @brief TODO
 */
struct TAIAsearchWorkObject : public TaiAction {
	inline TAIAsearchWorkObject() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual void start(Teki&); // _08
	virtual bool act(Teki&);   // _10

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAjudgeLife : public TaiAction {
	TAIAjudgeLife(int nextState)
	    : TaiAction(nextState)
	{
	}

	virtual f32 getLifePercentThreshold(Teki&) = 0; // _1C

	f32 getLifePercent(Teki& teki) { return teki.mHealth / teki.getParameterF(TPF_Life); }

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAlessLife : public TAIAjudgeLife {
	TAIAlessLife(int nextState)
	    : TAIAjudgeLife(nextState)
	{
	}

	virtual bool act(Teki&);                        // _10
	virtual f32 getLifePercentThreshold(Teki&) = 0; // _1C

	// _04     = VTBL
	// _00-_08 = TAIAjudgeLife?
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAmoreLife : public TAIAjudgeLife {
	TAIAmoreLife(int nextState)
	    : TAIAjudgeLife(nextState)
	{
	}

	virtual bool act(Teki&);                        // _10
	virtual f32 getLifePercentThreshold(Teki&) = 0; // _1C

	// _04     = VTBL
	// _00-_08 = TAIAjudgeLife?
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAjudgeOptionalRange : public TaiAction {
	inline TAIAjudgeOptionalRange() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki&);                   // _10
	virtual bool setTargetPosition(Teki&) = 0; // _1C
	virtual f32 getOptionalRange(Teki&)   = 0; // _20
	virtual bool judgement(Teki&)         = 0; // _24

	bool setTargetPositionCreature(Teki&);

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAinsideOptionalRange : public TAIAjudgeOptionalRange {
	inline TAIAinsideOptionalRange() // TODO: this is a guess
	{
	}

	virtual bool setTargetPosition(Teki&) = 0; // _1C
	virtual f32 getOptionalRange(Teki&)   = 0; // _20
	virtual bool judgement(Teki&);             // _24

	// _04     = VTBL
	// _00-_08 = TAIAjudgeOptionalRange?
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAoutsideOptionalRange : public TAIAjudgeOptionalRange {
	inline TAIAoutsideOptionalRange() // TODO: this is a guess
	{
	}

	virtual bool setTargetPosition(Teki&) = 0; // _1C
	virtual f32 getOptionalRange(Teki&)   = 0; // _20
	virtual bool judgement(Teki&);             // _24

	// _04     = VTBL
	// _00-_08 = TAIAjudgeOptionalRange?
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAcheckInsideRangePiki : public TaiAction {
	TAIAcheckInsideRangePiki(int nextState, int pikiMax, f32 range)
	    : TaiAction(nextState)
	{
		mPikiMax = pikiMax;
		mRange   = range;
	}

	virtual bool act(Teki&);                           // _10
	virtual int getPikiMax(Teki&) { return mPikiMax; } // _1C
	virtual f32 getRange(Teki&) { return mRange; }     // _20

	// _04     = VTBL
	// _00-_08 = TaiAction
	int mPikiMax; // _08
	f32 mRange;   // _0C
};

/**
 * @brief TODO
 */
struct TAIAinsideTerritoryRangeNavi : public TaiAction {
	inline TAIAinsideTerritoryRangeNavi() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki&); // _10

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAoutsideTerritoryRangeNavi : public TaiAction {
	inline TAIAoutsideTerritoryRangeNavi() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki&); // _10

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAvisibleNavi : public TaiAction {
	inline TAIAvisibleNavi() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki&); // _10

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAvisiblePiki : public TaiAction {
	TAIAvisiblePiki(int nextState)
	    : TaiAction(nextState)
	{
	}

	virtual bool act(Teki&); // _10

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAattackableTarget : public TaiAction {
	inline TAIAattackableTarget() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki&);   // _10
	virtual bool judge(Teki&); // _1C

	bool checkAngle(Teki&);

	// unused/inlined:
	bool checkDist(Teki&);

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAunvisibleTarget : public TaiAction {
	inline TAIAunvisibleTarget() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki&); // _10

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAstickingPiki : public TaiAction {
	inline TAIAstickingPiki() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual void start(Teki&) { }                              // _08
	virtual bool act(Teki&);                                   // _10
	virtual int getPikiNum(Teki&) { return mStickingPikiNum; } // _1C

	// _04     = VTBL
	// _00-_08 = TaiAction
	int mStickingPikiNum; // _08
};

/**
 * @brief TODO
 */
struct TAIAdistanceTarget : public TaiAction {
	TAIAdistanceTarget() // this never gets called, so who knows
	    : TaiAction(TAI_NO_TRANSIT)
	{
	}

	virtual void start(Teki&); // _08
	virtual bool act(Teki&);   // _10

	// _04     = VTBL
	// _00-_08 = TaiAction
	f32 _08;       // _08
	f32 mDistance; // _0C
};

/**
 * @brief TODO
 */
struct TAIAcheckTurnAngle : public TaiAction {
	TAIAcheckTurnAngle(int nextState, f32 p2, bool p3)
	    : TaiAction(nextState)
	{
		_08 = p2;
		_0C = p3;
	}

	virtual void start(Teki&); // _08
	virtual bool act(Teki&);   // _10

	// _04     = VTBL
	// _00-_08 = TaiAction
	f32 _08;  // _08
	bool _0C; // _0C
};

/**
 * @brief TODO
 */
struct TAIAoutsideTerritory : public TaiAction {
	inline TAIAoutsideTerritory() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki&); // _10

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAattackableAngleTarget : public TAIAattackableTarget {
	inline TAIAattackableAngleTarget() // TODO: this is a guess
	{
	}

	virtual bool judge(Teki&); // _1C

	// _04     = VTBL
	// _00-_08 = TAIAattackableTarget?
	// TODO: members
};

#endif
