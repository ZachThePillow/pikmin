#ifndef _PELLET_H
#define _PELLET_H

#include "types.h"
#include "DualCreature.h"
#include "CreatureProp.h"
#include "ObjectMgr.h"
#include "PelletAnimator.h"
#include "StateMachine.h"
#include "EffectMgr.h"
#include "Shape.h"

struct PaniAnimKeyEvent;
struct PaniMotionTable;
struct PelletShapeObject;
struct PelletStateMachine;
struct PelletView;
struct Shape;
struct RippleEffect;
struct Suckable;

/**
 * @brief TODO
 */
struct NumberPel {
	int mPelletColor; // _00
	int mPelletType;  // _04
	u32 mPelletID;    // _08
};

extern NumberPel numberPellets[13];

/**
 * @brief TODO
 */
enum PelletType {
	// Easier to label this separate, these will also have PelletColor as -1
	PELTYPE_Corpse = 0,

	// Blue, Red, Yellow pellets
	PELTYPE_Blue   = 0,
	PELTYPE_Red    = 1,
	PELTYPE_Yellow = 2,

	// Ship parts
	PELTYPE_UfoPart = 3,
};

/**
 * @brief TODO
 */
enum NumPelletType {
	NUMPEL_NULL         = -1,
	NUMPEL_OnePellet    = 0,
	NUMPEL_FivePellet   = 1,
	NUMPEL_TenPellet    = 2,
	NUMPEL_TwentyPellet = 3,
};

/**
 * @brief TODO
 */
enum PelletColor {
	PELCOLOR_NULL = -1,

	PELCOLOR_Blue   = 0,
	PELCOLOR_Red    = 1,
	PELCOLOR_Yellow = 2,

	PELCOLOR_MIN  = PELCOLOR_Blue,
	PELCOLOUR_MAX = PELCOLOR_Yellow,

	PELCOLOUR_COUNT,
};

/**
 * @brief Offset for pellet sound IDs associated with animations.
 *
 * @note Used with PaniAnimKeyEvent passing of sound IDs.
 * @note Add 0xBE to this to get SoundID offset.
 */
enum PelletAnimSoundID {
	PELSOUND_NONE     = -1,
	PELSOUND_Other    = 0,
	PELSOUND_Engine   = 1,
	PELSOUND_Gear     = 2,
	PELSOUND_Rader    = 3,
	PELSOUND_Spring   = 4,
	PELSOUND_Battery  = 5,
	PELSOUND_Zenmai   = 6,
	PELSOUND_MoneyBox = 7,
};

/**
 * @brief Index for bounce sounds used by Pellet.
 *
 * @note See bounceSounds table in pelletMgr.cpp
 */
enum PelletBounceSoundID {
	PELBOUNCE_NONE            = -1,
	PELBOUNCE_NormalPellet    = 0,
	PELBOUNCE_NormalUfoPart   = 1,
	PELBOUNCE_SpringUfoPart   = 2,
	PELBOUNCE_MoneyBoxUfoPart = 3,
	// everything else is unused, though bounceSounds has more entries
};

/**
 * @brief TODO
 */
enum PelletMgrMovieFlags {
	PELMOVIE_Unk1 = 1 << 0, // 0x1
	PELMOVIE_Unk2 = 1 << 1, // 0x2
	PELMOVIE_Unk3 = 1 << 2, // 0x4
	PELMOVIE_Unk4 = 1 << 3, // 0x8
};

/**
 * @brief TODO
 *
 * @note Size: 0x58.
 */
struct PelletProp : public CreatureProp {
	PelletProp() { mCreatureProps.mFriction(0.1f); }

	// _54     = VTBL
	// _00-_58 = CreatureProp
};

/**
 * @brief TODO
 */
struct PelletShapeObject {
	PelletShapeObject(char*, Shape*, char*, char*, int);

	bool isMotionFlag(u8 flag) { return mMotionFlag & flag; }
	void setMotionFlag(u8 flag) { mMotionFlag |= flag; }

	Shape* mShape;          // _00
	AnimMgr* mAnimMgr;      // _04
	AnimContext mAnimatorA; // _08
	AnimContext mAnimatorB; // _18
	u8 mMotionFlag;         // _28
};

/**
 * @brief TODO
 *
 * @note Size: 0x138.
 */
struct PelletConfig : public Parameters, public CoreNode {
	PelletConfig();

	// _04     = VTBL
	// _00-_04 = Parameters
	// _04-_18 = CoreNode
	Parm<String> mPelletName;         // _18, x99
	ID32 mModelId;                    // _2C
	ID32 _38;                         // _38
	ID32 mPelletId;                   // _44
	Parm<int> mPelletType;            // _50, p00
	Parm<int> mPelletColor;           // _60, p09
	Parm<int> mCarryMinPikis;         // _70, p01
	Parm<int> mCarryMaxPikis;         // _80, p02
	Parm<int> mUseDynamicMotion;      // _90, p03 - maybe model rotation when sucking into onyon?
	Parm<f32> _A0;                    // _A0, p04 - dynParm1?
	Parm<f32> _B0;                    // _B0, p05 - dynParm2?
	Parm<int> _C0;                    // _C0, p08 - dynCollNums?
	Parm<int> mMatchingOnyonSeeds;    // _D0, p06 - null produces fireworks
	Parm<int> mNonMatchingOnyonSeeds; // _E0, p07 - null produces fireworks
	Parm<f32> mPelletScale;           // _F0, p10
	Parm<f32> mCarryInfoHeight;       // _100, p11
	Parm<int> mAnimSoundID;           // _110, p12 - see PelletAnimSoundID enum
	Parm<int> mBounceSoundID;         // _120, p13
	int mUfoPartIndex;                // _130

	// this has to be down here or the second VTBL spawns at 0x18 (should spawn at 0x134)

	virtual void read(RandomAccessStream&); // _18 (weak)
};

/**
 * @brief TODO
 *
 * @note Size: 0x5BC.
 */
struct Pellet : public DualCreature, public PaniAnimKeyListener {
	Pellet();

	virtual void init(Vector3f&);                        // _28
	virtual void startAI(int);                           // _34
	virtual f32 getiMass();                              // _38
	virtual f32 getSize();                               // _3C
	virtual f32 getCylinderHeight();                     // _44
	virtual void doSave(RandomAccessStream&);            // _50
	virtual void doLoad(RandomAccessStream&);            // _54
	virtual Vector3f getCentre();                        // _58
	virtual bool isVisible();                            // _74
	virtual bool isAtari();                              // _84
	virtual bool isAlive();                              // _88
	virtual bool ignoreAtari(Creature*);                 // _98
	virtual bool isFree();                               // _9C
	virtual bool stimulate(Interaction&);                // _A0
	virtual void collisionCallback(struct CollEvent&);   // _A8
	virtual void bounceCallback();                       // _AC
	virtual void startWaterEffect();                     // _CC
	virtual void finishWaterEffect();                    // _D0
	virtual void update();                               // _E0
	virtual void postUpdate(int, f32);                   // _E4
	virtual void refresh(Graphics&);                     // _EC
	virtual void doAnimation();                          // _108
	virtual void doKill();                               // _10C
	virtual void doRender(Graphics&, Matrix4f&);         // _118
	virtual void doCreateColls(Graphics&);               // _11C
	virtual void animationKeyUpdated(PaniAnimKeyEvent&); // _12C (weak)

	int getState();
	void setTrySound(bool);
	void startPick();
	void finishPick();
	void startGoal();
	void doCarry(Creature*, Vector3f&, u16);
	f32 getBottomRadius();
	bool startStickTeki(Creature*, f32);
	void endStickTeki(Creature*);
	bool winnable(int);
	bool stickSlot(int);
	void stickOffSlot(int);
	int getMinFreeSlotIndex();
	int getNearestFreeSlotIndex(Vector3f&);
	int getRandomFreeSlotIndex();
	Vector3f getSlotLocalPos(int, f32);
	Vector3f getSlotGlobalPos(int, f32);
	void setSlotFlag(int);
	void resetSlotFlag(int);
	bool isSlotFlag(int);
	void initPellet(PelletShapeObject*, PelletConfig*);
	void startCarryMotion(f32);
	void finishMotion();

	// unused/inlined:
	void initSlotFlags();
	void initPellet(PelletView*, PelletConfig*);
	void stopMotion();
	void startAppear();

	static bool isUfoPartsID(u32);

	AState<Pellet>* getCurrState() { return mCurrentState; }
	void setCurrState(AState<Pellet>* state) { mCurrentState = state; }

	void setMotionFlag(u8 flag) { mMotionFlag |= flag; }
	bool isMotionFlag(u8 flag) { return mMotionFlag & flag; }

	// this is just bool in the DLL, but seems to need to be BOOL/int to match initPellet
	BOOL isUfoParts()
	{
		if (mConfig) {
			return (mConfig->mPelletType() == PELTYPE_UfoPart);
		}
		return false;
	}

	bool isSlotFree(int slot) { return !isSlotFlag(slot); } // yeah actually.

	// DLL inlines to do:
	int getNearestFreeSlotIndex();

	// _00       = VTBL1
	// _440      = VTBL2
	// _00-_440  = DualCreature
	// _440-_444 = PaniAnimKeyListener
	Vector3f mSpawnPosition;              // _444
	bool mUseSpawnPosition;               // _450
	bool mIsPlayTrySound;                 // _451
	u8 mMotionFlag;                       // _452
	RippleEffect* mRippleEffect;          // _454
	Suckable* mTargetGoal;                // _458
	CollPart* mStuckMouthPart;            // _45C
	f32 mStuckAngle;                      // _460
	Vector3f mLastPosition;               // _464
	PelletStateMachine* mStateMachine;    // _470
	AState<Pellet>* mCurrentState;        // _474
	Creature* mPikiCarrier;               // _478
	Vector3f mCarryDirection;             // _47C
	u16 mCarrierCount;                    // _488
	f32 mTransitionTimer;                 // _48C
	u16 mCarryState;                      // _490
	Vector3f mCurrentPelletPosition;      // _494
	u16 _4A0;                             // _4A0
	f32 mCurrentPelletHeight;             // _4A4
	void* mPelletView;                    // _4A8, both PelletView* and Creature* - see Pellet::getBottomRadius
	PelletAnimator mAnimator;             // _4AC
	PelletShapeObject* mShapeObject;      // _554
	u8 _558[0x4];                         // _558, unknown
	PelletConfig* mConfig;                // _55C
	f32 mMotionSpeed;                     // _560
	int mSlotFlags[3];                    // _564
	u16 mCarrierCounter;                  // _570
	CollInfo* mPelletCollInfo;            // _574
	SearchData mSearchData[4];            // _578
	ShapeDynMaterials mShapeDynMaterials; // _5A8
	bool mIsAlive;                        // _5B8
	bool mIsAIActive;                     // _5B9, name is a guess
};

/**
 * @brief TODO
 *
 * @note Size: 0x204.
 */
struct PelletMgr : public MonoObjectMgr {

	/**
	 * @brief TODO
	 */
	struct UseNode : public CoreNode {
		UseNode() { initCore("useNode"); }

		// _00     = VTBL
		// _00-_14 = CoreNode
		u32 mPelletID; // _14
	};

	PelletMgr(MapMgr*);

	virtual ~PelletMgr() { }                // _48 (weak)
	virtual void refresh(Graphics&);        // _58
	virtual Creature* createObject();       // _80
	virtual void read(RandomAccessStream&); // _84 (weak)

	bool decomposeNumberPellet(u32, int&, int&);
	void registerUfoParts();
	Pellet* newNumberPellet(int, int);
	Pellet* newPellet(u32, PelletView*);
	PelletShapeObject* getShapeObject(u32);
	void addUseList(u32);
	void initShapeInfos();
	int getConfigIndex(u32);
	PelletConfig* getConfigFromIdx(int);
	PelletConfig* getConfig(u32);
	void readConfigs(RandomAccessStream&);
	void readAnimInfos(RandomAccessStream&);
	void initTekiNakaParts();
	void createShapeObjects();
	void refresh2d(Graphics&);

	// unused/inlined:
	bool useShape(u32);
	ID32 getConfigIdAt(int);

	bool isMovieFlag(u16 flag) { return mMovieFlags & flag; }
	void setMovieFlags(u16 flag) { mMovieFlags = flag; }

	static int getUfoIndexFromID(u32 ufoID);
	static u32 getUfoIDFromIndex(int);

	// DLL inlines to make:
	int getNumConfigs();

	void writeAnimInfos(RandomAccessStream&);
	void writeConfigs(RandomAccessStream&);

	// _00     = VTBL 1
	// _08     = VTBL 2
	// _00-_3C = MonoObjectMgr
	UseNode mUseList;                 // _3C
	int mConfigNum;                   // _54
	PelletConfig mConfigList;         // _58
	int mAnimInfoNum;                 // _190
	PelletAnimInfo mAnimInfoList;     // _194
	PelletProp* mPelletProps;         // _1F4
	PaniMotionTable* mUfoMotionTable; // _1F8
	int mReadStage;                   // _1FC, 0:read in configs, 1:read in animinfos
	u16 mMovieFlags;                  // _200, see PelletMgrMovieFlags enum
};

extern PelletMgr* pelletMgr;
extern bool SmartTurnOver;

#endif
