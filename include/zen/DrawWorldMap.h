#ifndef _ZEN_DRAWWORLDMAP_H
#define _ZEN_DRAWWORLDMAP_H

#include "types.h"
#include "P2D/Pane.h"
#include "zen/Number.h"

struct Controller;
struct Graphics;
struct P2DScreen;

namespace {

/**
 * @brief TODO
 */
enum WorldMapName {
	// TODO: this
};

struct WorldMapTitleMgr {
	WorldMapTitleMgr();

	void exitTitle();
	void init(P2DScreen*);
	void init();
	void update();
};

/**
 * @brief TODO
 */
struct WorldMapTitleObj {
	WorldMapTitleObj();

	void update();

	// TODO: members
};

/**
 * @brief TODO
 */
struct DrawWorldMapDateCallBack : public P2DPaneCallBack, public zen::NumberTex {

	virtual bool invoke(P2DPane*); // _08

	void setTex();
};

/**
 * @brief TODO
 */
struct WorldMapCoursePoint {
	WorldMapCoursePoint();

	void setPane(P2DScreen*, u32, u32, u32, P2DScreen*, u32);
	void select();

	// TODO: members
};
} // namespace

namespace zen {

/**
 * @brief TODO
 */
struct DrawWorldMap {

	/**
	 * @brief TODO
	 */
	enum startModeFlag {
		// TODO: this
	};

	/**
	 * @brief TODO
	 */
	enum startPlaceFlag {
		// TODO: this
	};

	DrawWorldMap();

	bool update(Controller*);
	void draw(Graphics&);
	void start(startModeFlag, startPlaceFlag);
	bool modeStart(Controller*);
	bool modeAppear(Controller*);
	bool modeOperation(Controller*);
	bool modeConfirm(Controller*);
	bool modeEnd(Controller*);
	void updateScreens();
	void closeMapInfo();
	void openMapInfo();

	// unused/inlined:
	~DrawWorldMap();
	void setCoursePoint(startPlaceFlag);

	// TODO: members
	int _00;              // _00
	int _04;              // _04
	int _08;              // _08
	u8 _0C[0x368 - 0x0C]; // _0C
};

/**
 * @brief TODO
 */
struct WorldMapConfirmMgr {
	/**
	 * @brief TODO
	 */
	enum statusFlag {
		// TODO: this
	};

	void init(statusFlag);
	bool modeOperation(Controller*);

	// TODO: members
};

/**
 * @brief TODO
 */
struct WorldMapCursorMgr {
	void init();
	void setLandingFlag(bool);
	void initParams();
	void effect();
	void moveOnyon();
	void forceMove();
	bool moveUfo();
	void stayUfo();
	void updateOnyonPos(Vector3f*, Vector3f*, Vector3f*);

	// TODO: members
};

/**
 * @brief TODO
 */
struct WorldMapCursorOnyon {
	WorldMapCursorOnyon();

	void init();
	void update(Vector3f&);

	// TODO: members
};

/**
 * @brief TODO
 */
struct WorldMapMapImageMgr {
	void init();
	void modeOpen();
	void modeClose();

	// TODO: members
};

/**
 * @brief TODO
 */
struct WorldMapPartsInfoMgr {
	void setDisplayParts(int, int);
	void setActiveMapNo(WorldMapName);

	// TODO: members
};

/**
 * @brief TODO
 */
struct WorldMapCoursePointMgr {
	bool modeAppear();
	bool modeOperation(Controller*, bool);

	// TODO: members
};

} // namespace zen

/**
 * @brief TODO
 */
struct WorldMapWipe {
	WorldMapWipe();

	void init(P2DScreen*, u32);
	void move(int, int);
	void moveDefaultPos();
	void set(int, int);
	void setDefault();
	void update(f32, u8);

	// TODO: members
};

/**
 * @brief Entire struct seems to be inline, wtf?
 */
struct WorldMapWipeMgr {
	WorldMapWipeMgr();

	void close(float, int, int);
	void init(P2DScreen*);
	void init();
	BOOL isActive();
	void open(float);
	void set(int, int);
	void setDefault();
	BOOL update();
};

#endif
