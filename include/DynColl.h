#ifndef _DYNCOLL_H
#define _DYNCOLL_H

#include "types.h"
#include "Node.h"
#include "BoundBox.h"

struct Creature;
struct MapAnimShapeObject;
struct CollGroup;
struct MapMgr;
struct Shape;

/**
 * @brief TODO
 */
struct DynCollObject : public Node {
	DynCollObject()
	    : Node("")
	{
		mContactCount = 0;
		_24           = -1;
		mCreature     = nullptr;
	}

	virtual void adjust(Creature*) { }                           // _30
	virtual void applyVelocity(Plane&, Vector3f&, Vector3f&) { } // _34
	virtual void touchCallback(Plane&, Vector3f&, Vector3f&) { } // _38
	virtual Shape* getShape() { return nullptr; }                // _3C

	// _00     = VTBL
	// _00-_20 = Node
	u32 mContactCount;   // _20, unknown
	u32 _24;             // _24, maybe int?
	Creature* mCreature; // _28
};

/**
 * @brief TODO
 *
 * @note Size: 0x140.
 */
struct DynCollShape : public DynCollObject {
	DynCollShape(Shape* shape)
	{
		mShape = shape;
		if (mShape) {
			createDupCollData();
		}

		mScale    = Vector3f(1.0f, 1.0f, 1.0f);
		mPosition = Vector3f(0.0f, 0.0f, 0.0f);
		mRotation = mPosition;
		mTransformMtx.makeIdentity();
	}

	virtual void update();                       // _10
	virtual void adjust(Creature*);              // _30
	virtual Shape* getShape() { return mShape; } // _3C
	virtual void jointVisible(int, int);         // _40
	virtual void refresh(Graphics&);             // _44

	void createDupCollData();
	void updatePos();
	void updateContext();

	// unused/inlined:
	void drawAtari(Graphics&);

	// _00     = VTBL
	// _00-_2C = DynCollObject
	Shape* mShape;             // _2C
	Vector3f* mVertexList;     // _30
	u32 _34;                   // _34
	bool* mProgressStateList;  // _38
	int mColliderCount;        // _3C
	CollGroup** mColliderList; // _40
	BoundBox mBoundingBox;     // _44
	Matrix4f mTransformMtx;    // _5C
	Matrix4f mInverseMatrix;   // _9C
	Matrix4f mWorldMatrix;     // _DC
	Vector3f mScale;           // _11C, these 3 are actually an SRT struct in the DLL
	Vector3f mRotation;        // _128
	Vector3f mPosition;        // _134
};

/**
 * @brief TODO
 *
 * @note Size: 0x144.
 */
struct DynCollObjBody : public DynCollShape {
	DynCollObjBody() // TODO: fix this, it's implicit but required/this is just a guess
	    : DynCollShape(nullptr)
	{
	}

	virtual void update() { }                                 // _10
	virtual void adjust(Creature*) { }                        // _30
	virtual void applyVelocity(Plane&, Vector3f&, Vector3f&); // _34
	virtual void touchCallback(Plane&, Vector3f&, Vector3f&); // _38

	// _00      = VTBL
	// _00-_140 = DynCollShape
	u8 _140[0x4]; // _140, unknown
};

/**
 * @brief TODO
 *
 * @note Size: 0x140.
 */
struct DynBuildShape : public DynCollShape {
	DynBuildShape(Shape* s) // TODO: fix this, it's implicit but required/this is just a guess
	    : DynCollShape(s)
	{
	}

	virtual void update() { }           // _10
	virtual void refresh(Graphics&) { } // _44

	// _00      = VTBL
	// _00-_140 = DynCollShape
};

#endif
