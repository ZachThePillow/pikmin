#ifndef _ROUTE_H
#define _ROUTE_H

#include "types.h"
#include "Vector.h"
#include "Node.h"
#include "Colour.h"

struct Creature;
struct CmdStream;
struct DataMsg;
struct Graphics;
struct MapMgr;
struct Plane;
struct BaseShape;
struct PathFinder;

/**
 * @brief TODO
 */
struct EditNode : public CoreNode {
	virtual void msgCommand(DataMsg&) { }      // _10 (weak)
	virtual void render2d(Graphics&, int&) {}; // _14 (weak)

	// _00     = VTBL
	// _00-_14 = CoreNode
	// TODO: members
};

/**
 * @brief TODO
 */
struct RouteLink : public CoreNode {
	// _00     = VTBL
	// _00-_14 = CoreNode
	u32 mLinkIndex; // _14
};

/**
 * @brief TODO
 */
struct RoutePoint : public CoreNode {
	RoutePoint();

	void loadini(CmdStream*);

	// unused/inlined:
	void refresh(Graphics&);

	// _00     = VTBL
	// _00-_14 = CoreNode
	u32 _14;         // _14
	u32 _18;         // _18
	u32 _1C;         // _1C
	u32 _20;         // _20
	u32 _24;         // _24
	u32 _28;         // _28
	u32 _2C;         // _2C
	u32 _30;         // _30
	u32 _34;         // _34
	u32 _38;         // _38
	RouteLink mLink; // _3C
};

/**
 * @brief TODO
 * @note Size: 0xC0.
 */
struct RouteGroup : public EditNode {
	RouteGroup();

	virtual void render2d(Graphics&, int&); // _14

	void refresh(Graphics&, EditNode*);
	void loadini(CmdStream*);

	// unused/inlined:
	void saveini(char*, RandomAccessStream&);

	// _00     = VTBL
	// _00-_14 = EditNode?
	Colour mColour;          // _14
	char mRouteName[0x40];   // _18
	u32 _58;                 // _58
	char _5C[8];             // _5C
	BaseShape* mParentShape; // _64
	RoutePoint mPoint;       // _68
	u32 _BC;                 // _BC
};

/**
 * @brief TODO
 */
struct WayPoint {
	WayPoint();

	void setFlag(bool);
	void refresh(Graphics&);
	void resetLinkInfos();
	void initLinkInfos();

	// unused/inlined:
	void getLinkIndex(int);

	Vector3f mPosition; // _00, probably
	                    // TODO: members
};

/**
 * @brief TODO
 */
struct RouteMgr : public Node {
	struct Group { };

	RouteMgr();

	virtual void update(); // _10

	PathFinder* getPathFinder(u32);
	void getNumWayPoints(u32);
	void getSafePosition(u32, Vector3f&);
	void findNearestEdge(WayPoint**, WayPoint**, u32, Vector3f&, bool, bool, bool);
	void findNearestEdgeAvoidOff(WayPoint**, WayPoint**, u32, Vector3f&, bool, bool, bool);
	WayPoint* findNearestWayPoint(u32, Vector3f&, bool);
	void findNearestOffWayPoint(u32, Vector3f&, bool);
	void createOffPlane(u32, Plane&, WayPoint*);
	void findNearestWayPointAll(u32, Vector3f&);
	void getWayPoint(u32, int);
	void construct(MapMgr*);
	void initLinks();
	void id2idx(u32);
	void getColinIndex(RouteGroup*, RoutePoint*);
	void refresh(Graphics&);

	// unused/inlined:
	void dump(u32);
	void idx2id(int);

	// _00     = VTBL
	// _00-_20 = Node
	// TODO: members
};

/**
 * @brief TODO
 */
struct PathFinder {
	struct Buffer {
		Buffer();

		u32 _00; // _00
		u8 _04;  // _04
	};

	struct Client {
		// TODO: members
	};

	PathFinder(RouteMgr::Group&);

	void findASync(Buffer*, int, int, bool);
	void checkASync(u32);
	void releaseHandle(u32);
	void updateClient(Client&, int);
	void findSync(WayPoint**, int, int, int, bool);
	void findSync(Buffer*, int, int, bool);
	void getWayPoint(int);
	void selectWay(Buffer&, int, Buffer*, int, bool);
	void findSyncOnyon(Vector3f&, Buffer*, int, int, bool);
	void selectWayOnyon(int, int, Buffer&, int, Buffer*, int, bool);
	void selectSecondBestWayOnyon(Vector3f&, int&, int, Buffer&, int, Buffer*, int, bool);

	// unused/inlined:
	void handle2idx(u32);
	void updateASync();
	void findFirstStepOnyon(int, int, Buffer*);

	// TODO: members
};

/**
 * @brief Mostly stripped struct (and substructs).
 */
struct RouteTracer {
	struct Context {
		struct PointInfo {
			PointInfo();
		};

		void makeContext(RouteTracer*);
		void setTarget(RouteTracer*);
		void recognise(RouteTracer*);
	};

	RouteTracer();

	// unused/inlined:
	void render(Graphics&);
	void noLink();
	void startConsult(Creature*, PathFinder*, PathFinder::Buffer*, int, Vector3f&);
	void updateState();
	void getTarget();

	// TODO: members
};

extern RouteMgr* routeMgr;

#endif
