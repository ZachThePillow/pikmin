#ifndef _CINEMATICPLAYER_H
#define _CINEMATICPLAYER_H

#include "types.h"
#include "CoreNode.h"
#include "Animator.h"
#include "Camera.h"
#include "Light.h"
#include "Dolphin/arith.h"
#include "stl/string.h"
#include "EffectMgr.h"
#include "Shape.h"

struct AgeServer;
struct CmdStream;
struct Graphics;
struct Matrix4f;
struct Vector3f;
struct CinematicPlayer;
struct CineShapeObject;
struct ActorInstance;

/**
 * @brief TODO
 */
struct SceneData : public CoreNode {
	SceneData()
	    : CoreNode("")
	{
		mNumFrames  = 0;
		mNumCameras = 0;
		mNumLights  = 0;
	}

	void parse(CmdStream*);
	void getAnimInfo(CmdStream*);

	// _00     = VTBL
	// _00-_14 = CoreNode
	DataChunk* mCameraAnimations; // _14
	DataChunk* mLightAnimations;  // _18
	CamDataInfo* mCameraData;     // _1C
	LightDataInfo* mLightData;    // _20
	u32 mNumFrames;               // _24
	int mNumCameras;              // _28
	int mNumLights;               // _2C
};

/**
 * @brief TODO
 */
struct ActorInstance : public CoreNode {
	ActorInstance()
	    : CoreNode("")
	{
		_5C        = 0;
		_60        = 0;
		_64        = 0;
		mAnim.mMgr = 0;
		_19E       = 0;
		_19D       = 0;
		_19F       = 0;
		_19C       = 0;
		_6C        = 0;
		_70        = 1;
		_74        = -1;
		_80        = 0.0f;
		_68        = 2;
		_78        = 0;
	}

	void exitInstance();
	void initInstance();
	void checkEventKeys(f32, f32, Vector3f&);
	void refresh(Matrix4f&, Graphics&, f32*);

	// unused/inlined:
	void onceInit();

	// _00     = VTBL
	// _00-_14 = CoreNode
	Animator mAnim;                     // _14
	ShapeDynMaterials mDynMat;          // _48
	Shape* _58;                         // _58
	CineShapeObject* _5C;               // _5C
	CineShapeObject* _60;               // _60
	int _64;                            // _64
	int _68;                            // _68
	int _6C;                            // _6C
	int _70;                            // _70
	int _74;                            // _74
	int _78;                            // _78
	CinematicPlayer* _7C;               // _7C
	f32 _80;                            // _80
	Vector3f _84;                       // _84
	Vector3f _90;                       // _90
	Vector3f _9C[9];                    // _9C
	Vector3f _108[4];                   // _108
	zen::particleGenerator* _138[9];    // _138
	zen::particleGenerator* _15C[4][4]; // _15C
	u8 _19C;                            // _19C
	u8 _19D;                            // _19D
	u8 _19E;                            // _19E
	u8 _19F;                            // _19F
};

/**
 * @brief TODO
 */
struct SceneCut : public CoreNode {
	SceneCut()
	    : CoreNode("")
	{
		mStartFrame = 0;
		mEndFrame   = 0;
		mActor.initCore("");
		mFlags     = 3;
		_20        = 0;
		mSceneData = 0;
		mKey.mNext = &mKey;
		mKey.mPrev = &mKey;
	}

	ActorInstance* addInstance(char*);

	// unused/inlined:
	int countEKeys();

	// _00     = VTBL
	// _00-_14 = CoreNode
	int mFlags;            // _14
	int mStartFrame;       // _18
	int mEndFrame;         // _1C
	int _20;               // _20
	SceneData* mSceneData; // _24
	ActorInstance mActor;  // _28
	AnimKey mKey;          // _1C8
	CinematicPlayer* _1D8; // _1D8
};

/**
 * @brief TODO
 */
struct CineShapeObject : public CoreNode {
	CineShapeObject()
	    : CoreNode("")
	{
		_30 = 0;
		_1C = 0;
		_18 = 0;
	}

	// unused/inlined:
	void init(char*, char*, char*);

	// _00     = VTBL
	// _00-_14 = CoreNode
	Shape* _14;           // _14
	char* _18;            // _18
	char* _1C;            // _1C
	AnimContext mContext; // _20
	AnimMgr* _30;         // _30
};

struct CinematicPlayer {
	CinematicPlayer(char*);

	void init(char*);
	void loadCin(char*);
	SceneData* addScene(SceneData*);
	SceneCut* addCut(int, int, int);
	void addActor(CineShapeObject*);
	void addActor(char*, char*, char*);
	SceneCut* addSceneCut();
	void skipScene(int);
	int update();
	void addLights(Graphics&);
	void refresh(Graphics&);

	// unused/inlined:
	void addScene(char*);

	// DLL inlines
	CineShapeObject* findActor(char* name)
	{
		for (CineShapeObject* actor = (CineShapeObject*)_80.mChild; actor; actor = (CineShapeObject*)actor->mNext) {
			if (!strcmp(actor->mName, name)) {
				return actor;
			}
		}
		return nullptr;
	}

	SceneData* findScene(int id)
	{
		int i = 0;
		for (SceneData* shape = (SceneData*)_4C.mChild; shape; shape = (SceneData*)shape->mNext) {
			if (i == id) {
				return shape;
			}
			i++;
		}
		return nullptr;
	}
	void ageAddActor(AgeServer&);
	void ageAddCut(AgeServer&);
	void ageAddScene(AgeServer&);
	void ageLoad(AgeServer&);
	void ageNew(AgeServer&);
	void agePlayAnim(AgeServer&);
	void ageRefreshSection(AgeServer&);
	void ageSave(AgeServer&);
	void calcMaxFrames()
	{
		mTotalSceneDuration = 0;
		for (CineShapeObject* shape = (CineShapeObject*)mCutList.mChild; shape; shape = (CineShapeObject*)shape->mNext) {
			mTotalSceneDuration += abs(shape->_1C - shape->_18);
		}

		if (mCurrentPlaybackTime >= (f32)mTotalSceneDuration) {
			mCurrentPlaybackTime = (f32)mTotalSceneDuration - 1.0f;
		}
	}
	void genAge(AgeServer&);
	void genSection(AgeServer&);
	void saveCin(char*);
	void truncateName(char*);

	// TODO: members
	u32 mFlags;                 // _00
	int mType;                  // _04
	Matrix4f mMtx;              // _08
	u32 _48;                    // _48
	SceneData _4C;              // _4C
	SceneData* mCurrentScene;   // _7C
	CineShapeObject _80;        // _80
	SceneCut mCutList;          // _B4
	SceneCut* mCurrentCut;      // _290
	SceneCut* mPreviousCut;     // _294
	int mPlaybackMode;          // _298
	f32 mCurrentCutStartTime;   // _29C
	f32 mPlaybackSpeed;         // _2A0
	f32 mCurrentPlaybackTime;   // _2A4
	f32 mCurrentFramePosition;  // _2A8
	f32 mPreviousFramePosition; // _2AC
	int mTotalSceneDuration;    // _2B0
	int mCutTransitionFlag;     // _2B4
	Vector3f mCameraPosition;   // _2B8
	Vector3f mCameraLookAt;     // _2CC
	Vector3f _2D0;              // _2D0
	f32 mCameraTargetFov;       // _2DC
	f32 mCameraBlendRatio;      // _2E0
	bool _2E4;                  // _2E4
	bool mIsPlaying;            // _2E5
};

#endif
