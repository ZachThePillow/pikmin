#ifndef _GAMECORESECTION_H
#define _GAMECORESECTION_H

#include "types.h"
#include "Node.h"
#include "Light.h"

struct Camera;
struct Controller;
struct Creature;
struct Font;
struct MapMgr;
struct Menu;
struct Navi;
struct RectArea;
struct SearchSystem;

namespace zen {
struct DrawGameInfo;
}

/**
 * @brief TODO
 */
enum CorePauseFlags {
	COREPAUSE_Unk1 = 1 << 0, // 0x1
	COREPAUSE_Unk2 = 1 << 1, // 0x2
	COREPAUSE_Unk3 = 1 << 2, // 0x4
	COREPAUSE_Unk4 = 1 << 3, // 0x8
	// ...
	COREPAUSE_Unk16 = 1 << 15, // 0x8000
};

/**
 * @brief TODO
 */
struct GameCoreSection : public Node {
	GameCoreSection(Controller*, MapMgr*, Camera&);

	virtual void update();        // _10
	virtual void draw(Graphics&); // _14

	void updateTextDemo();
	void startMovie(u32, bool);
	void endMovie(int);
	void exitDayEnd();
	void forceDayEnd();
	void clearDeadlyPikmins();
	void enterFreePikmins();
	void cleanupDayEnd();
	void prepareBadEnd();
	void exitStage();
	void initStage();
	void finalSetup();
	void startContainerDemo();
	void startSundownWarn();
	void updateAI();
	void draw1D(Graphics&);
	void draw2D(Graphics&);

	static void startTextDemo(Creature*, int);

	// unused/inlined:
	bool hideTeki();
	bool hideAllPellet();
	bool hidePelletExceptSucked();

	static void finishPause() { pauseFlag = 0; }
	static void startPause(u16 pause) { pauseFlag = pause; }
	static bool inPause() { return pauseFlag & COREPAUSE_Unk16; } // probably?

	static u16 pauseFlag;
	static int textDemoState;
	static u16 textDemoTimer;
	static int textDemoIndex;

	// _00     = VTBL
	// _00-_20 = Node
	Controller* mController;          // _20
	u8 _24[0x4];                      // _24, unknown
	u32 _28;                          // _28, unknown
	u32 _2C;                          // _2C, unknown
	u8 _30;                           // _30
	u8 _31;                           // _31
	u32 _34;                          // _34, unknown
	u8 _38[0x4];                      // _38, unknown
	Menu* mAiPerfDebugMenu;           // _3C, unknown
	u8 _40[0x50 - 0x40];              // _40, unknown
	Shape* _50;                       // _50, unknown
	SearchSystem* _54;                // _54
	Navi* mNavi;                      // _58
	u8 _5C[0x64 - 0x5C];              // _5C, unknown
	MapMgr* mMapMgr;                  // _64
	Texture* mShadowTexture;          // _68
	Font* mBigFont;                   // _6C
	Light _70;                        // _70
	zen::DrawGameInfo* mDrawGameInfo; // _344
};

#endif
