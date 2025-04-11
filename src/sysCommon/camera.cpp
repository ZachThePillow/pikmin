#include "Camera.h"
#include "Texture.h"
#include "Graphics.h"
#include "Geometry.h"
#include "sysNew.h"
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
 * Size:	0000F0
 */
DEFINE_PRINT(nullptr)

/*
 * --INFO--
 * Address:	........
 * Size:	0000C4
 */
void CullFrustum::vectorToWorldPlane(Vector3f& vec, CullingPlane& worldPlane)
{
	projectVector(vec, worldPlane.mPlane.mNormal);
	worldPlane.mPlane.mOffset = worldPlane.mPlane.mNormal.dot(mPosition);
}

/*
 * --INFO--
 * Address:	80041584
 * Size:	00006C
 */
bool CullFrustum::isPointVisible(Vector3f& point, f32 cutoff)
{
	for (int i = 0; i < mActivePlaneCount; i++) {
		Plane* plane = &mPlanePointers[i]->mPlane;
		if (point.x * plane->mNormal.x + point.y * plane->mNormal.y + point.z * plane->mNormal.z - plane->mOffset < -cutoff) {
			return false;
		}
	}

	return true;
}

/*
 * --INFO--
 * Address:	800415F0
 * Size:	000FBC
 */
void CullFrustum::draw(Graphics& gfx)
{
	gfx._324              = 0;
	bool prevLightSetting = gfx.setLighting(false, nullptr);
	gfx.useMatrix(gfx.mCamera->mLookAtMtx, 0);
	gfx.useTexture(nullptr, 0);
	gfx.setColour(Colour(255, 255, 255, 255), true);
	gfx.setAuxColour(Colour(255, 255, 255, 255));
	gfx.drawLine(mPosition, mFocus);

	f32 targetDist = mPosition.distance(mFocus);
	f32 tanTheta   = sinf(PI * (mFov / 2) / 180.0f) * targetDist / cosf(PI * (mFov / 2) / 180.0f);

	f32 divTanTheta = tanTheta / mAspectRatio;
	f32 roundedTan  = divTanTheta * mAspectRatio;

	Vector3f vec1(-roundedTan, tanTheta, 0.0f);
	Vector3f vec2(roundedTan, tanTheta, 0.0f);
	Vector3f vec3(roundedTan, -tanTheta, 0.0f);
	Vector3f vec4(-roundedTan, -tanTheta, 0.0f);

	Vector3f targ1(vec1.dot(mViewXAxis) + mFocus.x, vec1.dot(mViewYAxis) + mFocus.y, vec1.dot(mViewZAxis) + mFocus.z);
	Vector3f targ2(vec2.dot(mViewXAxis) + mFocus.x, vec2.dot(mViewYAxis) + mFocus.y, vec2.dot(mViewZAxis) + mFocus.z);
	Vector3f targ3(vec3.dot(mViewXAxis) + mFocus.x, vec3.dot(mViewYAxis) + mFocus.y, vec3.dot(mViewZAxis) + mFocus.z);
	Vector3f targ4(vec4.dot(mViewXAxis) + mFocus.x, vec4.dot(mViewYAxis) + mFocus.y, vec4.dot(mViewZAxis) + mFocus.z);

	Vector3f dir;
	dir.sub2(mFocus, mPosition);
	dir.normalise();
	dir.multiply(mNear);
	dir.add(mPosition);

	f32 invDist = mNear / mFocus.distance(mPosition);
	f32 divDist = divTanTheta * invDist;
	f32 tanDist = tanTheta * invDist;

	Vector3f vec5(-divDist, tanDist, 0.0f);
	Vector3f vec6(divDist, tanDist, 0.0f);
	Vector3f vec7(divDist, -tanDist, 0.0f);
	Vector3f vec8(-divDist, -tanDist, 0.0f);

	Vector3f dir1(vec5.dot(mViewXAxis) + dir.x, vec5.dot(mViewYAxis) + dir.y, vec5.dot(mViewZAxis) + dir.z);
	Vector3f dir2(vec6.dot(mViewXAxis) + dir.x, vec6.dot(mViewYAxis) + dir.y, vec6.dot(mViewZAxis) + dir.z);
	Vector3f dir3(vec7.dot(mViewXAxis) + dir.x, vec7.dot(mViewYAxis) + dir.y, vec7.dot(mViewZAxis) + dir.z);
	Vector3f dir4(vec8.dot(mViewXAxis) + dir.x, vec8.dot(mViewYAxis) + dir.y, vec8.dot(mViewZAxis) + dir.z);

	Vector3f odir;
	odir.sub2(mFocus, mPosition);
	odir.normalise();
	odir.multiply(mFar);
	odir.add(mPosition);

	f32 oinvDist = mFar / mFocus.distance(mPosition);
	f32 odivDist = roundedTan * invDist;
	f32 otanDist = tanTheta * invDist;

	Vector3f vec9(-odivDist, otanDist, 0.0f);
	Vector3f vec10(odivDist, otanDist, 0.0f);
	Vector3f vec11(odivDist, -otanDist, 0.0f);
	Vector3f vec12(-odivDist, -otanDist, 0.0f);

	Vector3f odir1(vec9.dot(mViewXAxis) + odir.x, vec9.dot(mViewYAxis) + odir.y, vec9.dot(mViewZAxis) + odir.z);
	Vector3f odir2(vec10.dot(mViewXAxis) + odir.x, vec10.dot(mViewYAxis) + odir.y, vec10.dot(mViewZAxis) + odir.z);
	Vector3f odir3(vec11.dot(mViewXAxis) + odir.x, vec11.dot(mViewYAxis) + odir.y, vec11.dot(mViewZAxis) + odir.z);
	Vector3f odir4(vec12.dot(mViewXAxis) + odir.x, vec12.dot(mViewYAxis) + odir.y, vec12.dot(mViewZAxis) + odir.z);

	gfx.setColour(Colour(32, 255, 32, 128), true);
	gfx.drawLine(dir1, dir2);
	gfx.drawLine(dir2, dir3);
	gfx.drawLine(dir3, dir4);
	gfx.drawLine(dir4, dir1);

	gfx.drawLine(dir1, targ1);
	gfx.drawLine(dir2, targ2);
	gfx.drawLine(dir3, targ3);
	gfx.drawLine(dir4, targ4);

	gfx.drawLine(targ1, targ2);
	gfx.drawLine(targ2, targ3);
	gfx.drawLine(targ3, targ4);
	gfx.drawLine(targ4, targ1);

	gfx.setColour(Colour(255, 32, 32, 128), true);
	gfx.drawLine(odir1, odir2);
	gfx.drawLine(odir2, odir3);
	gfx.drawLine(odir3, odir4);
	gfx.drawLine(odir4, odir1);

	gfx.drawLine(odir1, targ1);
	gfx.drawLine(odir2, targ2);
	gfx.drawLine(odir3, targ3);
	gfx.drawLine(odir4, targ4);

	gfx.setColour(Colour(255, 0, 0, 16), true);
	Vector3f vec3Block1[4];
	Vector2f vec2Block1[4];
	vec2Block1[0].set(0.0f, 0.0f);
	vec2Block1[1].set(0.0f, 0.0f);
	vec2Block1[2].set(0.0f, 0.0f);
	vec2Block1[3].set(0.0f, 0.0f);

	vec3Block1[0] = dir2;
	vec3Block1[1] = dir1;
	vec3Block1[2] = odir1;
	vec3Block1[3] = odir2;
	gfx.drawOneTri(vec3Block1, nullptr, vec2Block1, 4);

	gfx.setColour(Colour(255, 0, 32, 16), true);
	vec3Block1[0] = dir3;
	vec3Block1[1] = dir2;
	vec3Block1[2] = odir2;
	vec3Block1[3] = odir3;
	gfx.drawOneTri(vec3Block1, nullptr, vec2Block1, 4);

	gfx.setColour(Colour(255, 0, 0, 16), true);
	vec3Block1[0] = dir4;
	vec3Block1[1] = dir3;
	vec3Block1[2] = odir3;
	vec3Block1[3] = odir4;
	gfx.drawOneTri(vec3Block1, nullptr, vec2Block1, 4);

	gfx.setColour(Colour(255, 0, 32, 16), true);
	vec3Block1[0] = dir1;
	vec3Block1[1] = dir4;
	vec3Block1[2] = odir4;
	vec3Block1[3] = odir1;
	gfx.drawOneTri(vec3Block1, nullptr, vec2Block1, 4);

	gfx.setLighting(prevLightSetting, nullptr);

	/*
	.loc_0x0:
	  mflr      r0
	  li        r5, 0
	  stw       r0, 0x4(r1)
	  li        r0, 0
	  stwu      r1, -0x430(r1)
	  stfd      f31, 0x428(r1)
	  stfd      f30, 0x420(r1)
	  stfd      f29, 0x418(r1)
	  stfd      f28, 0x410(r1)
	  stfd      f27, 0x408(r1)
	  stfd      f26, 0x400(r1)
	  stmw      r26, 0x3E8(r1)
	  addi      r26, r4, 0
	  addi      r31, r3, 0
	  mr        r3, r26
	  stw       r0, 0x324(r4)
	  li        r4, 0
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0x30(r12)
	  mtlr      r12
	  blrl
	  mr        r0, r3
	  lwz       r4, 0x2E4(r26)
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  mr        r27, r0
	  addi      r4, r4, 0x1E0
	  lwz       r12, 0x74(r12)
	  li        r5, 0
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  li        r4, 0
	  li        r5, 0
	  lwz       r12, 0xCC(r12)
	  mtlr      r12
	  blrl
	  li        r28, 0xFF
	  stb       r28, 0x258(r1)
	  addi      r4, r1, 0x258
	  addi      r3, r26, 0
	  stb       r28, 0x259(r1)
	  li        r5, 0x1
	  stb       r28, 0x25A(r1)
	  stb       r28, 0x25B(r1)
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0xA8(r12)
	  mtlr      r12
	  blrl
	  stb       r28, 0x254(r1)
	  addi      r4, r1, 0x254
	  addi      r3, r26, 0
	  stb       r28, 0x255(r1)
	  stb       r28, 0x256(r1)
	  stb       r28, 0x257(r1)
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0xAC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r31, 0x164
	  addi      r5, r31, 0x170
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, -0x7BF8(r2)
	  stfs      f0, 0x1D8(r1)
	  stfs      f0, 0x1D4(r1)
	  stfs      f0, 0x1D0(r1)
	  lfs       f1, 0x170(r31)
	  lfs       f0, 0x164(r31)
	  lfs       f4, 0x178(r31)
	  fsubs     f0, f1, f0
	  lfs       f3, 0x16C(r31)
	  lfs       f2, 0x174(r31)
	  lfs       f1, 0x168(r31)
	  fsubs     f3, f4, f3
	  stfs      f0, 0x1AC(r1)
	  fsubs     f1, f2, f1
	  lfs       f0, 0x1AC(r1)
	  stfs      f0, 0x1D0(r1)
	  stfs      f1, 0x1D4(r1)
	  stfs      f3, 0x1D8(r1)
	  lfs       f1, 0x1D0(r1)
	  lfs       f0, 0x1D4(r1)
	  lfs       f2, 0x1D8(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0x33B24
	  lfs       f2, 0x1CC(r31)
	  fmr       f27, f1
	  lfs       f0, -0x7BF0(r2)
	  lfs       f3, -0x7BF4(r2)
	  fmuls     f1, f2, f0
	  lfs       f0, -0x7BEC(r2)
	  fmuls     f1, f3, f1
	  fdivs     f1, f1, f0
	  bl        0x1DA3CC
	  lfs       f2, 0x1CC(r31)
	  fmr       f26, f1
	  lfs       f0, -0x7BF0(r2)
	  lfs       f3, -0x7BF4(r2)
	  fmuls     f1, f2, f0
	  lfs       f0, -0x7BEC(r2)
	  fmuls     f1, f3, f1
	  fdivs     f1, f1, f0
	  bl        0x1DA53C
	  fmuls     f1, f27, f1
	  lfs       f6, 0x1C4(r31)
	  lfs       f4, 0x17C(r31)
	  lfs       f0, 0x180(r31)
	  fdivs     f31, f1, f26
	  lfs       f2, 0x18C(r31)
	  lfs       f5, 0x198(r31)
	  lfs       f9, 0x188(r31)
	  lfs       f28, -0x7924(r13)
	  fdivs     f26, f31, f6
	  lfs       f3, 0x184(r31)
	  lfs       f10, 0x190(r31)
	  lfs       f27, 0x19C(r31)
	  lfs       f13, 0x194(r31)
	  fmuls     f30, f26, f6
	  lfs       f7, 0x170(r31)
	  fmuls     f1, f31, f0
	  lfs       f11, 0x174(r31)
	  fmuls     f8, f31, f2
	  fneg      f2, f30
	  lfs       f0, 0x178(r31)
	  fmuls     f6, f28, f3
	  lfs       f3, -0x7920(r13)
	  fmuls     f12, f31, f5
	  fmuls     f5, f2, f4
	  lfs       f4, -0x791C(r13)
	  fmuls     f9, f2, f9
	  fmuls     f13, f2, f13
	  fadds     f1, f5, f1
	  fmuls     f10, f28, f10
	  fadds     f5, f9, f8
	  fadds     f1, f6, f1
	  fmuls     f8, f28, f27
	  fadds     f6, f13, f12
	  fadds     f5, f10, f5
	  fadds     f1, f7, f1
	  fadds     f6, f8, f6
	  fadds     f5, f11, f5
	  stfs      f1, 0x3A8(r1)
	  fneg      f1, f31
	  fadds     f0, f0, f6
	  stfs      f5, 0x3AC(r1)
	  stfs      f0, 0x3B0(r1)
	  lfs       f5, 0x17C(r31)
	  lfs       f0, 0x180(r31)
	  lfs       f8, 0x188(r31)
	  fmuls     f5, f30, f5
	  fmuls     f0, f31, f0
	  lfs       f7, 0x18C(r31)
	  lfs       f6, 0x184(r31)
	  lfs       f11, 0x194(r31)
	  lfs       f10, 0x198(r31)
	  lfs       f9, 0x190(r31)
	  fmuls     f8, f30, f8
	  fmuls     f7, f31, f7
	  lfs       f12, 0x19C(r31)
	  fmuls     f6, f3, f6
	  fadds     f0, f5, f0
	  fmuls     f11, f30, f11
	  fmuls     f10, f31, f10
	  lfs       f5, 0x170(r31)
	  fadds     f0, f6, f0
	  fmuls     f9, f3, f9
	  fadds     f6, f8, f7
	  fmuls     f12, f3, f12
	  lfs       f7, 0x174(r31)
	  fadds     f8, f11, f10
	  fadds     f3, f9, f6
	  fadds     f0, f5, f0
	  lfs       f6, 0x178(r31)
	  fadds     f5, f12, f8
	  fadds     f3, f7, f3
	  stfs      f0, 0x39C(r1)
	  fadds     f0, f6, f5
	  stfs      f3, 0x3A0(r1)
	  stfs      f0, 0x3A4(r1)
	  lfs       f0, 0x194(r31)
	  lfs       f5, 0x198(r31)
	  lfs       f3, 0x188(r31)
	  fmuls     f8, f30, f0
	  lfs       f0, 0x18C(r31)
	  fmuls     f7, f1, f5
	  lfs       f9, 0x19C(r31)
	  lfs       f5, 0x190(r31)
	  fmuls     f3, f30, f3
	  lfs       f10, 0x178(r31)
	  fmuls     f0, f1, f0
	  lfs       f6, 0x174(r31)
	  fmuls     f9, f4, f9
	  fadds     f7, f8, f7
	  fmuls     f5, f4, f5
	  fadds     f0, f3, f0
	  fadds     f3, f9, f7
	  fadds     f0, f5, f0
	  fadds     f8, f10, f3
	  fadds     f7, f6, f0
	  lfs       f3, 0x17C(r31)
	  lfs       f0, 0x180(r31)
	  fmuls     f3, f30, f3
	  lfs       f5, 0x184(r31)
	  fmuls     f0, f1, f0
	  lfs       f6, 0x170(r31)
	  fmuls     f4, f4, f5
	  fadds     f3, f3, f0
	  lfs       f0, -0x7918(r13)
	  fadds     f3, f4, f3
	  fadds     f3, f6, f3
	  stfs      f3, 0x390(r1)
	  stfs      f7, 0x394(r1)
	  stfs      f8, 0x398(r1)
	  lfs       f4, 0x17C(r31)
	  lfs       f3, 0x180(r31)
	  lfs       f7, 0x188(r31)
	  fmuls     f4, f2, f4
	  fmuls     f3, f1, f3
	  lfs       f6, 0x18C(r31)
	  lfs       f5, 0x184(r31)
	  lfs       f10, 0x194(r31)
	  lfs       f9, 0x198(r31)
	  lfs       f8, 0x190(r31)
	  fmuls     f7, f2, f7
	  fmuls     f6, f1, f6
	  lfs       f11, 0x19C(r31)
	  fmuls     f5, f0, f5
	  fadds     f3, f4, f3
	  fmuls     f10, f2, f10
	  fmuls     f9, f1, f9
	  lfs       f2, 0x170(r31)
	  fadds     f1, f5, f3
	  fmuls     f4, f0, f8
	  fadds     f3, f7, f6
	  fmuls     f7, f0, f11
	  lfs       f5, 0x174(r31)
	  fadds     f6, f10, f9
	  fadds     f3, f4, f3
	  fadds     f0, f2, f1
	  lfs       f2, 0x178(r31)
	  fadds     f1, f7, f6
	  fadds     f3, f5, f3
	  stfs      f0, 0x384(r1)
	  fadds     f0, f2, f1
	  stfs      f3, 0x388(r1)
	  stfs      f0, 0x38C(r1)
	  lfs       f3, 0x170(r31)
	  lfs       f2, 0x164(r31)
	  lfs       f1, 0x174(r31)
	  lfs       f0, 0x168(r31)
	  fsubs     f29, f3, f2
	  lfs       f2, 0x178(r31)
	  fsubs     f28, f1, f0
	  lfs       f0, 0x16C(r31)
	  fmuls     f1, f29, f29
	  fsubs     f27, f2, f0
	  fmuls     f0, f28, f28
	  fmuls     f2, f27, f27
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0x33DE4
	  lfs       f0, -0x7BF8(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x450
	  fdivs     f29, f29, f1
	  fdivs     f28, f28, f1
	  fdivs     f27, f27, f1

	.loc_0x450:
	  lfs       f1, 0x1D0(r31)
	  lfs       f5, 0x164(r31)
	  lfs       f4, 0x168(r31)
	  fmuls     f29, f29, f1
	  lfs       f3, 0x16C(r31)
	  fmuls     f28, f28, f1
	  lfs       f0, -0x7BF8(r2)
	  fmuls     f27, f27, f1
	  stfs      f0, 0x1C8(r1)
	  fadds     f29, f29, f5
	  fadds     f28, f28, f4
	  stfs      f0, 0x1C4(r1)
	  fadds     f27, f27, f3
	  stfs      f0, 0x1C0(r1)
	  lfs       f0, 0x170(r31)
	  lfs       f2, 0x178(r31)
	  lfs       f1, 0x174(r31)
	  fsubs     f0, f5, f0
	  fsubs     f2, f3, f2
	  fsubs     f1, f4, f1
	  stfs      f0, 0x198(r1)
	  lfs       f0, 0x198(r1)
	  stfs      f0, 0x1C0(r1)
	  stfs      f1, 0x1C4(r1)
	  stfs      f2, 0x1C8(r1)
	  lfs       f1, 0x1C0(r1)
	  lfs       f0, 0x1C4(r1)
	  lfs       f2, 0x1C8(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0x33E84
	  lfs       f0, 0x1D0(r31)
	  lfs       f3, 0x17C(r31)
	  fdivs     f1, f0, f1
	  lfs       f2, 0x180(r31)
	  lfs       f10, 0x188(r31)
	  lfs       f7, 0x18C(r31)
	  lfs       f0, -0x7914(r13)
	  fmuls     f4, f26, f1
	  lfs       f8, 0x184(r31)
	  fmuls     f5, f31, f1
	  lfs       f12, 0x198(r31)
	  lfs       f11, 0x190(r31)
	  fneg      f1, f4
	  lfs       f13, 0x194(r31)
	  fmuls     f6, f5, f2
	  lfs       f26, 0x19C(r31)
	  fmuls     f9, f5, f7
	  fmuls     f7, f1, f3
	  lfs       f2, -0x7910(r13)
	  fmuls     f10, f1, f10
	  lfs       f3, -0x790C(r13)
	  fmuls     f8, f0, f8
	  fadds     f6, f7, f6
	  fmuls     f13, f1, f13
	  fmuls     f12, f5, f12
	  fadds     f6, f8, f6
	  fmuls     f8, f0, f11
	  fadds     f7, f10, f9
	  fadds     f6, f29, f6
	  fmuls     f10, f0, f26
	  fadds     f9, f13, f12
	  fadds     f7, f8, f7
	  stfs      f6, 0x33C(r1)
	  fneg      f0, f5
	  fadds     f6, f10, f9
	  fadds     f7, f28, f7
	  fadds     f6, f27, f6
	  stfs      f7, 0x340(r1)
	  stfs      f6, 0x344(r1)
	  lfs       f7, 0x17C(r31)
	  lfs       f6, 0x180(r31)
	  lfs       f10, 0x188(r31)
	  fmuls     f7, f4, f7
	  fmuls     f6, f5, f6
	  lfs       f9, 0x18C(r31)
	  lfs       f8, 0x184(r31)
	  lfs       f13, 0x194(r31)
	  lfs       f12, 0x198(r31)
	  lfs       f11, 0x190(r31)
	  fmuls     f10, f4, f10
	  fmuls     f9, f5, f9
	  lfs       f26, 0x19C(r31)
	  fmuls     f8, f2, f8
	  fadds     f6, f7, f6
	  fmuls     f13, f4, f13
	  fmuls     f12, f5, f12
	  fadds     f5, f8, f6
	  fmuls     f7, f2, f11
	  fadds     f6, f10, f9
	  fadds     f5, f29, f5
	  fmuls     f9, f2, f26
	  fadds     f8, f13, f12
	  fadds     f2, f7, f6
	  stfs      f5, 0x330(r1)
	  fadds     f5, f9, f8
	  fadds     f2, f28, f2
	  fadds     f5, f27, f5
	  stfs      f2, 0x334(r1)
	  stfs      f5, 0x338(r1)
	  lfs       f5, 0x17C(r31)
	  lfs       f2, 0x180(r31)
	  lfs       f10, 0x194(r31)
	  fmuls     f5, f4, f5
	  fmuls     f2, f0, f2
	  lfs       f9, 0x198(r31)
	  lfs       f8, 0x188(r31)
	  lfs       f7, 0x18C(r31)
	  lfs       f6, 0x184(r31)
	  lfs       f12, 0x19C(r31)
	  fmuls     f11, f4, f10
	  fmuls     f10, f0, f9
	  lfs       f9, 0x190(r31)
	  fmuls     f8, f4, f8
	  fmuls     f7, f0, f7
	  fmuls     f4, f3, f6
	  fadds     f2, f5, f2
	  fmuls     f6, f3, f12
	  fadds     f5, f11, f10
	  fadds     f2, f4, f2
	  fmuls     f4, f3, f9
	  fadds     f3, f8, f7
	  fadds     f5, f6, f5
	  fadds     f2, f29, f2
	  fadds     f3, f4, f3
	  fadds     f4, f27, f5
	  stfs      f2, 0x324(r1)
	  fadds     f2, f28, f3
	  stfs      f2, 0x328(r1)
	  lfs       f11, -0x7908(r13)
	  stfs      f4, 0x32C(r1)
	  lfs       f3, 0x17C(r31)
	  lfs       f2, 0x180(r31)
	  lfs       f6, 0x188(r31)
	  fmuls     f3, f1, f3
	  fmuls     f2, f0, f2
	  lfs       f5, 0x18C(r31)
	  lfs       f4, 0x184(r31)
	  lfs       f9, 0x194(r31)
	  lfs       f8, 0x198(r31)
	  lfs       f7, 0x190(r31)
	  fmuls     f6, f1, f6
	  fmuls     f5, f0, f5
	  lfs       f10, 0x19C(r31)
	  fmuls     f4, f11, f4
	  fadds     f2, f3, f2
	  fmuls     f9, f1, f9
	  fmuls     f3, f0, f8
	  fadds     f0, f4, f2
	  fmuls     f2, f11, f7
	  fadds     f1, f6, f5
	  fadds     f0, f29, f0
	  fmuls     f4, f11, f10
	  fadds     f3, f9, f3
	  fadds     f1, f2, f1
	  stfs      f0, 0x318(r1)
	  fadds     f0, f4, f3
	  fadds     f1, f28, f1
	  fadds     f0, f27, f0
	  stfs      f1, 0x31C(r1)
	  stfs      f0, 0x320(r1)
	  lfs       f3, 0x170(r31)
	  lfs       f2, 0x164(r31)
	  lfs       f1, 0x174(r31)
	  lfs       f0, 0x168(r31)
	  fsubs     f27, f3, f2
	  lfs       f2, 0x178(r31)
	  fsubs     f28, f1, f0
	  lfs       f0, 0x16C(r31)
	  fmuls     f1, f27, f27
	  fsubs     f29, f2, f0
	  fmuls     f0, f28, f28
	  fmuls     f2, f29, f29
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0x340C8
	  lfs       f0, -0x7BF8(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x734
	  fdivs     f27, f27, f1
	  fdivs     f28, f28, f1
	  fdivs     f29, f29, f1

	.loc_0x734:
	  lfs       f1, 0x1D4(r31)
	  lfs       f5, 0x164(r31)
	  lfs       f4, 0x168(r31)
	  fmuls     f27, f27, f1
	  lfs       f3, 0x16C(r31)
	  fmuls     f28, f28, f1
	  lfs       f0, -0x7BF8(r2)
	  fmuls     f29, f29, f1
	  stfs      f0, 0x1B8(r1)
	  fadds     f27, f27, f5
	  fadds     f28, f28, f4
	  stfs      f0, 0x1B4(r1)
	  fadds     f29, f29, f3
	  stfs      f0, 0x1B0(r1)
	  lfs       f0, 0x170(r31)
	  lfs       f2, 0x178(r31)
	  lfs       f1, 0x174(r31)
	  fsubs     f0, f5, f0
	  fsubs     f2, f3, f2
	  fsubs     f1, f4, f1
	  stfs      f0, 0x184(r1)
	  lfs       f0, 0x184(r1)
	  stfs      f0, 0x1B0(r1)
	  stfs      f1, 0x1B4(r1)
	  stfs      f2, 0x1B8(r1)
	  lfs       f1, 0x1B0(r1)
	  lfs       f0, 0x1B4(r1)
	  lfs       f2, 0x1B8(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0x34168
	  lfs       f0, 0x1D4(r31)
	  lfs       f2, 0x17C(r31)
	  fdivs     f1, f0, f1
	  lfs       f0, 0x180(r31)
	  lfs       f8, 0x188(r31)
	  lfs       f3, 0x18C(r31)
	  lfs       f13, -0x7904(r13)
	  fmuls     f30, f30, f1
	  lfs       f6, 0x184(r31)
	  fmuls     f4, f31, f1
	  lfs       f10, 0x198(r31)
	  lfs       f9, 0x190(r31)
	  fneg      f1, f30
	  lfs       f11, 0x194(r31)
	  fmuls     f0, f4, f0
	  lfs       f12, 0x19C(r31)
	  fmuls     f7, f4, f3
	  fmuls     f5, f1, f2
	  lfs       f2, -0x7900(r13)
	  fmuls     f8, f1, f8
	  lfs       f3, -0x78FC(r13)
	  fmuls     f6, f13, f6
	  fadds     f0, f5, f0
	  fmuls     f11, f1, f11
	  fmuls     f10, f4, f10
	  fadds     f0, f6, f0
	  fmuls     f6, f13, f9
	  fadds     f5, f8, f7
	  fadds     f0, f27, f0
	  fmuls     f8, f13, f12
	  fadds     f7, f11, f10
	  fadds     f5, f6, f5
	  stfs      f0, 0x2D0(r1)
	  fneg      f0, f4
	  fadds     f6, f8, f7
	  fadds     f5, f28, f5
	  fadds     f6, f29, f6
	  stfs      f5, 0x2D4(r1)
	  stfs      f6, 0x2D8(r1)
	  lfs       f6, 0x17C(r31)
	  lfs       f5, 0x180(r31)
	  lfs       f9, 0x188(r31)
	  fmuls     f6, f30, f6
	  fmuls     f5, f4, f5
	  lfs       f8, 0x18C(r31)
	  lfs       f7, 0x184(r31)
	  lfs       f12, 0x194(r31)
	  lfs       f11, 0x198(r31)
	  lfs       f10, 0x190(r31)
	  fmuls     f9, f30, f9
	  fmuls     f8, f4, f8
	  lfs       f13, 0x19C(r31)
	  fmuls     f7, f2, f7
	  fadds     f5, f6, f5
	  fmuls     f12, f30, f12
	  fmuls     f11, f4, f11
	  fadds     f4, f7, f5
	  fmuls     f6, f2, f10
	  fadds     f5, f9, f8
	  fadds     f4, f27, f4
	  fmuls     f8, f2, f13
	  fadds     f7, f12, f11
	  fadds     f2, f6, f5
	  stfs      f4, 0x2C4(r1)
	  fadds     f4, f8, f7
	  fadds     f2, f28, f2
	  fadds     f4, f29, f4
	  stfs      f2, 0x2C8(r1)
	  stfs      f4, 0x2CC(r1)
	  lfs       f4, 0x17C(r31)
	  lfs       f2, 0x180(r31)
	  lfs       f9, 0x194(r31)
	  fmuls     f4, f30, f4
	  fmuls     f2, f0, f2
	  lfs       f8, 0x198(r31)
	  lfs       f7, 0x188(r31)
	  lfs       f6, 0x18C(r31)
	  lfs       f5, 0x184(r31)
	  lfs       f11, 0x19C(r31)
	  fmuls     f10, f30, f9
	  fmuls     f9, f0, f8
	  lfs       f8, 0x190(r31)
	  fmuls     f7, f30, f7
	  fmuls     f6, f0, f6
	  fmuls     f5, f3, f5
	  fadds     f2, f4, f2
	  fmuls     f11, f3, f11
	  fadds     f9, f10, f9
	  fadds     f2, f5, f2
	  fmuls     f4, f3, f8
	  fadds     f3, f7, f6
	  fadds     f5, f11, f9
	  fadds     f2, f27, f2
	  fadds     f3, f4, f3
	  fadds     f4, f29, f5
	  stfs      f2, 0x2B8(r1)
	  fadds     f2, f28, f3
	  stfs      f2, 0x2BC(r1)
	  li        r28, 0x20
	  lfs       f11, -0x78F8(r13)
	  li        r29, 0xFF
	  stfs      f4, 0x2C0(r1)
	  li        r30, 0x80
	  lfs       f3, 0x17C(r31)
	  addi      r4, r1, 0x1F0
	  lfs       f2, 0x180(r31)
	  mr        r3, r26
	  fmuls     f3, f1, f3
	  fmuls     f2, f0, f2
	  lfs       f4, 0x184(r31)
	  lfs       f6, 0x188(r31)
	  li        r5, 0x1
	  lfs       f5, 0x18C(r31)
	  lfs       f9, 0x194(r31)
	  fmuls     f4, f11, f4
	  fadds     f2, f3, f2
	  lfs       f8, 0x198(r31)
	  fmuls     f6, f1, f6
	  fmuls     f5, f0, f5
	  fmuls     f9, f1, f9
	  fmuls     f3, f0, f8
	  lfs       f7, 0x190(r31)
	  fadds     f0, f4, f2
	  lfs       f10, 0x19C(r31)
	  fmuls     f2, f11, f7
	  fadds     f1, f6, f5
	  stb       r28, 0x1F0(r1)
	  fadds     f0, f27, f0
	  stb       r29, 0x1F1(r1)
	  fadds     f1, f2, f1
	  stb       r28, 0x1F2(r1)
	  fmuls     f4, f11, f10
	  fadds     f3, f9, f3
	  stfs      f0, 0x2AC(r1)
	  fadds     f1, f28, f1
	  fadds     f0, f4, f3
	  stb       r30, 0x1F3(r1)
	  stfs      f1, 0x2B0(r1)
	  fadds     f0, f29, f0
	  stfs      f0, 0x2B4(r1)
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0xA8(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x33C
	  addi      r5, r1, 0x330
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x330
	  addi      r5, r1, 0x324
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x324
	  addi      r5, r1, 0x318
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x318
	  addi      r5, r1, 0x33C
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x33C
	  addi      r5, r1, 0x3A8
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x330
	  addi      r5, r1, 0x39C
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x324
	  addi      r5, r1, 0x390
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x318
	  addi      r5, r1, 0x384
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x3A8
	  addi      r5, r1, 0x39C
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x39C
	  addi      r5, r1, 0x390
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x390
	  addi      r5, r1, 0x384
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x384
	  addi      r5, r1, 0x3A8
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  stb       r29, 0x1EC(r1)
	  addi      r4, r1, 0x1EC
	  addi      r3, r26, 0
	  stb       r28, 0x1ED(r1)
	  li        r5, 0x1
	  stb       r28, 0x1EE(r1)
	  stb       r30, 0x1EF(r1)
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0xA8(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x2D0
	  addi      r5, r1, 0x2C4
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x2C4
	  addi      r5, r1, 0x2B8
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x2B8
	  addi      r5, r1, 0x2AC
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x2AC
	  addi      r5, r1, 0x2D0
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x2D0
	  addi      r5, r1, 0x3A8
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x2C4
	  addi      r5, r1, 0x39C
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x2B8
	  addi      r5, r1, 0x390
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r1, 0x2AC
	  addi      r5, r1, 0x384
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  stb       r29, 0x1E8(r1)
	  li        r30, 0
	  li        r31, 0x10
	  stb       r30, 0x1E9(r1)
	  addi      r4, r1, 0x1E8
	  addi      r3, r26, 0
	  stb       r30, 0x1EA(r1)
	  li        r5, 0x1
	  stb       r31, 0x1EB(r1)
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0xA8(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, -0x7BF8(r2)
	  mr        r3, r26
	  lwz       r11, 0x330(r1)
	  addi      r4, r1, 0x27C
	  stfs      f0, 0x284(r1)
	  lwz       r10, 0x334(r1)
	  addi      r6, r1, 0x25C
	  stfs      f0, 0x280(r1)
	  li        r5, 0
	  lwz       r9, 0x338(r1)
	  stfs      f0, 0x27C(r1)
	  li        r7, 0x4
	  lwz       r8, 0x33C(r1)
	  stfs      f0, 0x290(r1)
	  lwz       r0, 0x340(r1)
	  stfs      f0, 0x28C(r1)
	  stfs      f0, 0x288(r1)
	  stfs      f0, 0x29C(r1)
	  stfs      f0, 0x298(r1)
	  stfs      f0, 0x25C(r1)
	  stfs      f0, 0x294(r1)
	  stfs      f0, 0x260(r1)
	  stfs      f0, 0x2A8(r1)
	  stfs      f0, 0x264(r1)
	  stfs      f0, 0x2A4(r1)
	  stfs      f0, 0x268(r1)
	  stfs      f0, 0x2A0(r1)
	  stfs      f0, 0x26C(r1)
	  stfs      f0, 0x270(r1)
	  stw       r11, 0x27C(r1)
	  stfs      f0, 0x274(r1)
	  stw       r10, 0x280(r1)
	  stfs      f0, 0x278(r1)
	  stw       r9, 0x284(r1)
	  stw       r8, 0x288(r1)
	  stw       r0, 0x28C(r1)
	  lwz       r0, 0x344(r1)
	  stw       r0, 0x290(r1)
	  lwz       r8, 0x2D0(r1)
	  lwz       r0, 0x2D4(r1)
	  stw       r8, 0x294(r1)
	  stw       r0, 0x298(r1)
	  lwz       r0, 0x2D8(r1)
	  stw       r0, 0x29C(r1)
	  lwz       r8, 0x2C4(r1)
	  lwz       r0, 0x2C8(r1)
	  stw       r8, 0x2A0(r1)
	  stw       r0, 0x2A4(r1)
	  lwz       r0, 0x2CC(r1)
	  stw       r0, 0x2A8(r1)
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0xA0(r12)
	  mtlr      r12
	  blrl
	  stb       r29, 0x1E4(r1)
	  addi      r4, r1, 0x1E4
	  addi      r3, r26, 0
	  stb       r30, 0x1E5(r1)
	  li        r5, 0x1
	  stb       r28, 0x1E6(r1)
	  stb       r31, 0x1E7(r1)
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0xA8(r12)
	  mtlr      r12
	  blrl
	  lwz       r0, 0x324(r1)
	  mr        r3, r26
	  lwz       r5, 0x328(r1)
	  addi      r4, r1, 0x27C
	  stw       r0, 0x27C(r1)
	  lwz       r0, 0x32C(r1)
	  addi      r6, r1, 0x25C
	  stw       r5, 0x280(r1)
	  li        r5, 0
	  lwz       r8, 0x330(r1)
	  stw       r0, 0x284(r1)
	  li        r7, 0x4
	  lwz       r0, 0x334(r1)
	  stw       r8, 0x288(r1)
	  stw       r0, 0x28C(r1)
	  lwz       r0, 0x338(r1)
	  stw       r0, 0x290(r1)
	  lwz       r8, 0x2C4(r1)
	  lwz       r0, 0x2C8(r1)
	  stw       r8, 0x294(r1)
	  stw       r0, 0x298(r1)
	  lwz       r0, 0x2CC(r1)
	  stw       r0, 0x29C(r1)
	  lwz       r8, 0x2B8(r1)
	  lwz       r0, 0x2BC(r1)
	  stw       r8, 0x2A0(r1)
	  stw       r0, 0x2A4(r1)
	  lwz       r0, 0x2C0(r1)
	  stw       r0, 0x2A8(r1)
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0xA0(r12)
	  mtlr      r12
	  blrl
	  stb       r29, 0x1E0(r1)
	  addi      r4, r1, 0x1E0
	  addi      r3, r26, 0
	  stb       r30, 0x1E1(r1)
	  li        r5, 0x1
	  stb       r30, 0x1E2(r1)
	  stb       r31, 0x1E3(r1)
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0xA8(r12)
	  mtlr      r12
	  blrl
	  lwz       r0, 0x318(r1)
	  mr        r3, r26
	  lwz       r5, 0x31C(r1)
	  addi      r4, r1, 0x27C
	  stw       r0, 0x27C(r1)
	  lwz       r0, 0x320(r1)
	  addi      r6, r1, 0x25C
	  stw       r5, 0x280(r1)
	  li        r5, 0
	  lwz       r8, 0x324(r1)
	  stw       r0, 0x284(r1)
	  li        r7, 0x4
	  lwz       r0, 0x328(r1)
	  stw       r8, 0x288(r1)
	  stw       r0, 0x28C(r1)
	  lwz       r0, 0x32C(r1)
	  stw       r0, 0x290(r1)
	  lwz       r8, 0x2B8(r1)
	  lwz       r0, 0x2BC(r1)
	  stw       r8, 0x294(r1)
	  stw       r0, 0x298(r1)
	  lwz       r0, 0x2C0(r1)
	  stw       r0, 0x29C(r1)
	  lwz       r8, 0x2AC(r1)
	  lwz       r0, 0x2B0(r1)
	  stw       r8, 0x2A0(r1)
	  stw       r0, 0x2A4(r1)
	  lwz       r0, 0x2B4(r1)
	  stw       r0, 0x2A8(r1)
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0xA0(r12)
	  mtlr      r12
	  blrl
	  stb       r29, 0x1DC(r1)
	  addi      r4, r1, 0x1DC
	  addi      r3, r26, 0
	  stb       r30, 0x1DD(r1)
	  li        r5, 0x1
	  stb       r28, 0x1DE(r1)
	  stb       r31, 0x1DF(r1)
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0xA8(r12)
	  mtlr      r12
	  blrl
	  lwz       r0, 0x33C(r1)
	  mr        r3, r26
	  lwz       r5, 0x340(r1)
	  addi      r4, r1, 0x27C
	  stw       r0, 0x27C(r1)
	  lwz       r0, 0x344(r1)
	  addi      r6, r1, 0x25C
	  stw       r5, 0x280(r1)
	  li        r5, 0
	  lwz       r8, 0x318(r1)
	  stw       r0, 0x284(r1)
	  li        r7, 0x4
	  lwz       r0, 0x31C(r1)
	  stw       r8, 0x288(r1)
	  stw       r0, 0x28C(r1)
	  lwz       r0, 0x320(r1)
	  stw       r0, 0x290(r1)
	  lwz       r8, 0x2AC(r1)
	  lwz       r0, 0x2B0(r1)
	  stw       r8, 0x294(r1)
	  stw       r0, 0x298(r1)
	  lwz       r0, 0x2B4(r1)
	  stw       r0, 0x29C(r1)
	  lwz       r8, 0x2D0(r1)
	  lwz       r0, 0x2D4(r1)
	  stw       r8, 0x2A0(r1)
	  stw       r0, 0x2A4(r1)
	  lwz       r0, 0x2D8(r1)
	  stw       r0, 0x2A8(r1)
	  lwz       r12, 0x3B4(r26)
	  lwz       r12, 0xA0(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r26
	  lwz       r12, 0x3B4(r26)
	  addi      r4, r27, 0
	  li        r5, 0
	  lwz       r12, 0x30(r12)
	  mtlr      r12
	  blrl
	  lmw       r26, 0x3E8(r1)
	  lwz       r0, 0x434(r1)
	  lfd       f31, 0x428(r1)
	  lfd       f30, 0x420(r1)
	  lfd       f29, 0x418(r1)
	  lfd       f28, 0x410(r1)
	  lfd       f27, 0x408(r1)
	  lfd       f26, 0x400(r1)
	  addi      r1, r1, 0x430
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800425AC
 * Size:	00046C
 */
void CullFrustum::updateViewPlanes(f32 leftScale, f32 rightScale, f32 bottomScale, f32 topScale)
{
	u32 badCompiler[4];

	CullingPlane* planes = &mCullPlanes[mViewPlaneIdx];
	Vector3f vec;
	vec.x = mWidth / absF(leftScale);
	vec.y = 0.0f;
	vec.z = mDepth;
	vec.normalise();
	vectorToWorldPlane(vec, planes[0]);
	planes[0].CheckMinMaxDir();
	planes[0]._28 = 1;

	vec.x = -mWidth / absF(rightScale);
	vec.y = 0.0f;
	vec.z = mDepth;
	vec.normalise();
	vectorToWorldPlane(vec, planes[1]);
	planes[1].CheckMinMaxDir();
	planes[1]._28 = 1;

	vec.x = 0.0f;
	vec.y = absF(bottomScale) * -mWidth;
	vec.z = mDepth;
	vec.normalise();
	vectorToWorldPlane(vec, planes[2]);
	planes[2].CheckMinMaxDir();
	planes[2]._28 = 1;

	vec.x = 0.0f;
	vec.y = absF(topScale) * mWidth;
	vec.z = mDepth;
	vec.normalise();
	vectorToWorldPlane(vec, planes[3]);
	planes[3].CheckMinMaxDir();
	planes[3]._28 = 1;

	mTotalPlaneCount = &planes[4] - mCullPlanes;
}

/*
 * --INFO--
 * Address:	80042A18
 * Size:	00023C
 */
void CullFrustum::createViewPlanes()
{
	CullingPlane* planes = mCullPlanes;
	Vector3f vec;
	mTotalPlaneCount = 0;
	mDepth           = sinf(PI * (0.5f * mFov) / 180.0f);
	mWidth           = cosf(PI * (0.5f * mFov) / 180.0f);
	vectorToWorldPlane(Vector3f(0.0f, 0.0f, 1.0f), planes[0]);
	planes[0].mPlane.mOffset += mNear;
	planes[0].CheckMinMaxDir();
	planes[0]._28 = 1;

	vectorToWorldPlane(Vector3f(0.0f, 0.0f, -1.0f), planes[1]);
	planes[1].mPlane.mOffset -= 2600.0f;
	planes[1].CheckMinMaxDir();
	planes[1]._28 = 1;

	mViewPlaneIdx = &planes[2] - mCullPlanes;

	FORCE_DONT_INLINE;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000BC
 */
void CullFrustum::additionalPlanes(CullFrustum*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000058
 */
void CullFrustum::createVecs()
{
	// col1 = x axis after transforming
	mViewXAxis.x = mLookAtMtx.mMtx[0][0];
	mViewXAxis.y = mLookAtMtx.mMtx[1][0];
	mViewXAxis.z = -mLookAtMtx.mMtx[2][0];

	// col2 = y axis after transforming
	mViewYAxis.x = mLookAtMtx.mMtx[0][1];
	mViewYAxis.y = mLookAtMtx.mMtx[1][1];
	mViewYAxis.z = -mLookAtMtx.mMtx[2][1];

	// col3 = z axis after transforming
	mViewZAxis.x = mLookAtMtx.mMtx[0][2];
	mViewZAxis.y = mLookAtMtx.mMtx[1][2];
	mViewZAxis.z = -mLookAtMtx.mMtx[2][2];
}

/*
 * --INFO--
 * Address:	........
 * Size:	000058
 */
void CullFrustum::createInvVecs()
{
	mInvXAxis.x = mLookAtMtx.mMtx[0][0];
	mInvXAxis.y = mLookAtMtx.mMtx[0][1];
	mInvXAxis.z = mLookAtMtx.mMtx[0][2];

	mInvYAxis.x = mLookAtMtx.mMtx[1][0];
	mInvYAxis.y = mLookAtMtx.mMtx[1][1];
	mInvYAxis.z = mLookAtMtx.mMtx[1][2];

	mInvZAxis.x = -mLookAtMtx.mMtx[2][0];
	mInvZAxis.y = -mLookAtMtx.mMtx[2][1];
	mInvZAxis.z = -mLookAtMtx.mMtx[2][2];
}

/*
 * --INFO--
 * Address:	80042C54
 * Size:	000150
 */
void CullFrustum::update(f32 aspectRatio, f32 fov, f32 near, f32 far)
{
	mAspectRatio   = aspectRatio;
	mVerticalScale = 1.0f;
	mFov           = fov;
	mNear          = near;
	mFar           = far;

	createVecs();
	createInvVecs();
	createViewPlanes();
	updateViewPlanes(mAspectRatio, -mAspectRatio, -mVerticalScale, mVerticalScale);

	for (int i = 0; i < mTotalPlaneCount; i++) {
		mPlanePointers[i] = &mCullPlanes[i];
	}

	mActivePlaneCount = mTotalPlaneCount;
	mBoundOffset.set(0.0f, 0.0f, 0.0f);
}

/*
 * --INFO--
 * Address:	80042DA4
 * Size:	000268
 */
void CullFrustum::calcVectors(Vector3f& eyePos, Vector3f& targetPos)
{
	u32 badCompiler[4];

	mPosition = eyePos;
	mFocus    = targetPos;

	// make sure eye pos and target pos aren't exactly the same, since we need a direction to point the camera
	if (mPosition.x == mFocus.x && mPosition.z == mFocus.z) {
		mFocus.z += 0.0001f;
	}

	// construct target view direction
	mViewZAxis.x = mPosition.x - mFocus.x;
	mViewZAxis.y = mPosition.y - mFocus.y;
	mViewZAxis.z = mPosition.z - mFocus.z;
	mViewZAxis.normalise();

	// construct perpendicular direction manually
	mViewXAxis.set(mViewZAxis.z, 0.0f, -mViewZAxis.x);
	mViewXAxis.normalise();

	// calculate vertical direction by crossing z and x
	mViewYAxis = mViewZAxis;
	mViewYAxis.CP(mViewXAxis);
	mViewYAxis.normalise();

	// construct lookat matrices
	mLookAtMtx.makeLookat(mPosition, mViewXAxis, mViewYAxis, mViewZAxis);
	mLookAtMtx.inverse(&mInverseLookAtMtx);

	update(1.0f, mFov, mNear, mFar);
}

/*
 * --INFO--
 * Address:	8004300C
 * Size:	00003C
 */
void CullFrustum::calcLookAt(Vector3f& p1, Vector3f& p2, Vector3f* p3)
{
	mLookAtMtx.makeLookat(p1, p2, p3);
	mLookAtMtx.inverse(&mInverseLookAtMtx);
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void CullFrustum::calcLookFrom(Vector3f&, Vector3f&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00015C
 */
void Camera::camReflect(Camera&, Plane&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80043048
 * Size:	00017C
 */
f32 Camera::projectWorldPoint(Graphics& gfx, Vector3f& point)
{
	f32 dist = mProjectionMatrix.mMtx[3][0] * point.x + mProjectionMatrix.mMtx[3][1] * point.y + mProjectionMatrix.mMtx[3][2] * point.z
	         + mProjectionMatrix.mMtx[3][3];
	if (dist <= 0.0f) {
		return dist;
	}

	point.multMatrix(mProjectionMatrix);
	f32 norm = 1.0f / dist;
	point.x *= norm;
	point.y *= norm;
	point.z *= norm;

	point.x *= gfx.mScreenWidth / 2.0f;
	point.y *= -(gfx.mScreenHeight / 2.0f);

	point.x += gfx.mScreenWidth / 2.0f;
	point.y += gfx.mScreenHeight / 2.0f;

	return point.z;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000170
 */
f32 Camera::projectCamPoint(Vector3f&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800431C4
 * Size:	000150
 */
Camera::Camera()
{
	mRotation.set(0.0f, 4.363323f, 0.0f);
	_32C.set(0.0f, 0.0f, 0.0f);
	mAspectRatio = 1.0f;
	mBlur        = 110.0f;
}

/*
 * --INFO--
 * Address:	80043314
 * Size:	0000D0
 */
void LightCamera::initLightmap(int size, int texFmt)
{
	mLightMap                = new Texture();
	f32 sizeFactor           = 1.0f / f32(size);
	mLightMap->mWidthFactor  = sizeFactor;
	mLightMap->mHeightFactor = sizeFactor;
	mLightMap->mTexFlags     = (Texture::TEX_CLAMP_S | Texture::TEX_Unk2 | Texture::TEX_CLAMP_T);
	mLightMap->createBuffer(size, size, texFmt, nullptr);
	gsys->addTexture(mLightMap, "internalLightmap");
}

/*
 * --INFO--
 * Address:	800433E4
 * Size:	000508
 */
void LightCamera::calcProjection(Graphics& gfx, bool p2, Node* p3)
{
	f32 targetDist = mPosition.distance(mFocus);
	f32 tanTheta   = sinf(PI * mFov / 180.0f) / cosf(PI * mFov / 180.0f);
	mFrustumRange  = tanTheta * targetDist;
	mFrustumSize   = mFrustumRange;

	Vector3f vec(mFrustumSize * (1.0f / tanTheta), mFrustumRange * (1.0f / tanTheta), 1.0f);
	Vector3f dir;
	dir.sub2(mPosition, mFocus);

	mProjectionX = dir.length() / vec.x;
	mProjectionY = dir.length() / vec.y;

	mProjectionScale.set(0.5f * mProjectionX, 0.5f * mProjectionY, 1.0f);

	if (mLightMap && p3) {
		mProjectionX = 0.5f * (mProjectionX - 1.0f);
		mProjectionY = 0.5f * (mProjectionY - 1.0f);

		f32 width  = 2.0f * mLightMap->mWidth;
		f32 height = 2.0f * mLightMap->mHeight;
		gfx.setPerspective(mPerspectiveMatrix.mMtx, mFov, mAspectRatio, 30.0f, mFar, 1.0f);

		gfx.setViewport(RectArea(-(width * mProjectionX), -(height * mProjectionY), width + (int(width * mProjectionX)),
		                         height + (int(height * mProjectionY))));

		Camera* cam = gfx.mCamera;
		gfx.setClearColour(Colour(0, 0, 0, 0));
		gfx.clearBuffer(3, 0);

		gfx.setScissor(RectArea(4, 4, int(width) - 4, int(height) - 4));
		gfx.setFog(false);
		gfx.setLighting(false, nullptr);
		gfx.setCamera(cam);
		gfx.useTexture(nullptr, 0);
		p3->draw(gfx);

		mLightMap->grabBuffer(mLightMap->mWidth, mLightMap->mHeight, true, true);
		gfx.setCamera(cam);
	}
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x150(r1)
	  stfd      f31, 0x148(r1)
	  stfd      f30, 0x140(r1)
	  stw       r31, 0x13C(r1)
	  mr        r31, r6
	  stw       r30, 0x138(r1)
	  addi      r30, r4, 0
	  stw       r29, 0x134(r1)
	  addi      r29, r3, 0
	  stw       r28, 0x130(r1)
	  lfs       f0, -0x7BF8(r2)
	  stfs      f0, 0x7C(r1)
	  stfs      f0, 0x78(r1)
	  stfs      f0, 0x74(r1)
	  lfs       f1, 0x170(r3)
	  lfs       f0, 0x164(r3)
	  lfs       f4, 0x178(r3)
	  fsubs     f0, f1, f0
	  lfs       f3, 0x16C(r3)
	  lfs       f2, 0x174(r3)
	  lfs       f1, 0x168(r3)
	  fsubs     f3, f4, f3
	  stfs      f0, 0x68(r1)
	  fsubs     f1, f2, f1
	  lfs       f0, 0x68(r1)
	  stfs      f0, 0x74(r1)
	  stfs      f1, 0x78(r1)
	  stfs      f3, 0x7C(r1)
	  lfs       f1, 0x74(r1)
	  lfs       f0, 0x78(r1)
	  lfs       f2, 0x7C(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0x3583C
	  lfs       f2, -0x7BF4(r2)
	  fmr       f31, f1
	  lfs       f1, 0x1CC(r29)
	  lfs       f0, -0x7BEC(r2)
	  fmuls     f1, f2, f1
	  fdivs     f1, f1, f0
	  bl        0x1D86BC
	  lfs       f2, -0x7BF4(r2)
	  fmr       f30, f1
	  lfs       f1, 0x1CC(r29)
	  lfs       f0, -0x7BEC(r2)
	  fmuls     f1, f2, f1
	  fdivs     f1, f1, f0
	  bl        0x1D8834
	  fdivs     f1, f1, f30
	  fmuls     f0, f1, f31
	  stfs      f0, 0x354(r29)
	  lfs       f0, 0x354(r29)
	  stfs      f0, 0x350(r29)
	  lfs       f0, -0x7BD4(r2)
	  lfs       f3, 0x168(r29)
	  fdivs     f7, f0, f1
	  lfs       f2, 0x174(r29)
	  lfs       f1, 0x164(r29)
	  lfs       f0, 0x170(r29)
	  lfs       f6, 0x354(r29)
	  fsubs     f4, f3, f2
	  lfs       f2, -0x7BF8(r2)
	  fsubs     f3, f1, f0
	  lfs       f1, 0x16C(r29)
	  lfs       f0, 0x178(r29)
	  fsubs     f0, f1, f0
	  lfs       f5, 0x350(r29)
	  fmuls     f1, f4, f4
	  fmuls     f3, f3, f3
	  fmuls     f4, f0, f0
	  fmuls     f0, f6, f7
	  fadds     f1, f3, f1
	  fmuls     f6, f5, f7
	  fadds     f1, f4, f1
	  fcmpo     cr0, f1, f2
	  ble-      .loc_0x1A0
	  fsqrte    f3, f1
	  lfd       f5, -0x7BE8(r2)
	  lfd       f4, -0x7BE0(r2)
	  fmul      f2, f3, f3
	  fmul      f3, f5, f3
	  fmul      f2, f1, f2
	  fsub      f2, f4, f2
	  fmul      f3, f3, f2
	  fmul      f2, f3, f3
	  fmul      f3, f5, f3
	  fmul      f2, f1, f2
	  fsub      f2, f4, f2
	  fmul      f3, f3, f2
	  fmul      f2, f3, f3
	  fmul      f3, f5, f3
	  fmul      f2, f1, f2
	  fsub      f2, f4, f2
	  fmul      f2, f3, f2
	  fmul      f2, f1, f2
	  frsp      f2, f2
	  stfs      f2, 0x64(r1)
	  lfs       f2, 0x64(r1)
	  b         .loc_0x1A4

	.loc_0x1A0:
	  fmr       f2, f1

	.loc_0x1A4:
	  fdivs     f2, f2, f6
	  stfs      f2, 0x348(r29)
	  lfs       f2, -0x7BF8(r2)
	  fcmpo     cr0, f1, f2
	  ble-      .loc_0x210
	  fsqrte    f3, f1
	  lfd       f5, -0x7BE8(r2)
	  lfd       f4, -0x7BE0(r2)
	  fmul      f2, f3, f3
	  fmul      f3, f5, f3
	  fmul      f2, f1, f2
	  fsub      f2, f4, f2
	  fmul      f3, f3, f2
	  fmul      f2, f3, f3
	  fmul      f3, f5, f3
	  fmul      f2, f1, f2
	  fsub      f2, f4, f2
	  fmul      f3, f3, f2
	  fmul      f2, f3, f3
	  fmul      f3, f5, f3
	  fmul      f2, f1, f2
	  fsub      f2, f4, f2
	  fmul      f2, f3, f2
	  fmul      f1, f1, f2
	  frsp      f1, f1
	  stfs      f1, 0x60(r1)
	  lfs       f1, 0x60(r1)

	.loc_0x210:
	  fdivs     f0, f1, f0
	  stfs      f0, 0x34C(r29)
	  lfs       f2, -0x7BF0(r2)
	  lfs       f0, 0x348(r29)
	  lfs       f1, 0x34C(r29)
	  fmuls     f0, f2, f0
	  fmuls     f1, f2, f1
	  stfs      f0, 0x35C(r29)
	  stfs      f1, 0x360(r29)
	  lfs       f0, -0x78B4(r13)
	  stfs      f0, 0x364(r29)
	  lwz       r0, 0x358(r29)
	  cmplwi    r0, 0
	  beq-      .loc_0x4E0
	  cmplwi    r31, 0
	  beq-      .loc_0x4E0
	  lfs       f5, -0x7BD4(r2)
	  lis       r28, 0x4330
	  lfs       f0, 0x348(r29)
	  mr        r3, r30
	  addi      r4, r29, 0x260
	  fsubs     f0, f0, f5
	  fmuls     f0, f2, f0
	  stfs      f0, 0x348(r29)
	  lfs       f0, 0x34C(r29)
	  fsubs     f0, f0, f5
	  fmuls     f0, f2, f0
	  stfs      f0, 0x34C(r29)
	  lwz       r6, 0x358(r29)
	  lwz       r12, 0x3B4(r30)
	  lhz       r5, 0x8(r6)
	  lhz       r0, 0xA(r6)
	  stw       r5, 0x12C(r1)
	  lwz       r12, 0x3C(r12)
	  stw       r0, 0x124(r1)
	  lfd       f2, -0x7BA8(r2)
	  mtlr      r12
	  stw       r28, 0x128(r1)
	  lfs       f6, -0x7BB4(r2)
	  stw       r28, 0x120(r1)
	  lfd       f1, 0x128(r1)
	  lfd       f0, 0x120(r1)
	  fsubs     f4, f1, f2
	  lfs       f1, 0x1CC(r29)
	  fsubs     f0, f0, f2
	  lfs       f2, 0x1C4(r29)
	  lfs       f3, -0x7BB0(r2)
	  fmuls     f31, f6, f4
	  lfs       f4, 0x1D4(r29)
	  fmuls     f30, f6, f0
	  blrl
	  lfs       f1, 0x348(r29)
	  addi      r4, r1, 0x94
	  lfs       f0, 0x34C(r29)
	  mr        r3, r30
	  fmuls     f1, f31, f1
	  fmuls     f3, f30, f0
	  lfd       f4, -0x7BC8(r2)
	  fctiwz    f0, f1
	  fctiwz    f2, f3
	  fneg      f1, f1
	  stfd      f0, 0x100(r1)
	  fneg      f0, f3
	  stfd      f2, 0x118(r1)
	  fctiwz    f1, f1
	  lwz       r0, 0x104(r1)
	  fctiwz    f0, f0
	  lwz       r5, 0x11C(r1)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0xFC(r1)
	  xoris     r0, r5, 0x8000
	  stw       r0, 0x114(r1)
	  stw       r28, 0xF8(r1)
	  stw       r28, 0x110(r1)
	  lfd       f2, 0xF8(r1)
	  stfd      f1, 0xE8(r1)
	  lfd       f3, 0x110(r1)
	  fsubs     f2, f2, f4
	  stfd      f0, 0xE0(r1)
	  fsubs     f1, f3, f4
	  lwz       r5, 0xEC(r1)
	  fadds     f0, f31, f2
	  lwz       r0, 0xE4(r1)
	  fadds     f1, f30, f1
	  fctiwz    f0, f0
	  stw       r5, 0x94(r1)
	  fctiwz    f1, f1
	  stw       r0, 0x98(r1)
	  stfd      f0, 0xF0(r1)
	  stfd      f1, 0x108(r1)
	  lwz       r5, 0xF4(r1)
	  lwz       r0, 0x10C(r1)
	  stw       r5, 0x9C(r1)
	  stw       r0, 0xA0(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x48(r12)
	  mtlr      r12
	  blrl
	  lwz       r28, 0x2E4(r30)
	  li        r0, 0
	  addi      r4, r1, 0x90
	  stb       r0, 0x90(r1)
	  mr        r3, r30
	  stb       r0, 0x91(r1)
	  stb       r0, 0x92(r1)
	  stb       r0, 0x93(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0xB4(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r30
	  lwz       r12, 0x3B4(r30)
	  li        r4, 0x3
	  li        r5, 0
	  lwz       r12, 0x38(r12)
	  mtlr      r12
	  blrl
	  fctiwz    f1, f31
	  li        r0, 0x4
	  fctiwz    f0, f30
	  stw       r0, 0x80(r1)
	  addi      r4, r1, 0x80
	  stfd      f1, 0xD8(r1)
	  mr        r3, r30
	  stfd      f0, 0xD0(r1)
	  lwz       r6, 0xDC(r1)
	  stw       r0, 0x84(r1)
	  lwz       r5, 0xD4(r1)
	  subi      r6, r6, 0x4
	  stw       r6, 0x88(r1)
	  subi      r0, r5, 0x4
	  stw       r0, 0x8C(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x50(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r30
	  lwz       r12, 0x3B4(r30)
	  li        r4, 0
	  lwz       r12, 0xB8(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r30
	  lwz       r12, 0x3B4(r30)
	  li        r4, 0
	  li        r5, 0
	  lwz       r12, 0x30(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r30
	  lwz       r12, 0x3B4(r30)
	  mr        r4, r29
	  lwz       r12, 0x6C(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r30
	  lwz       r12, 0x3B4(r30)
	  li        r4, 0
	  li        r5, 0
	  lwz       r12, 0xCC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r31
	  lwz       r12, 0x0(r31)
	  mr        r4, r30
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  lwz       r3, 0x358(r29)
	  li        r6, 0x1
	  li        r7, 0x1
	  lhz       r4, 0x8(r3)
	  lhz       r5, 0xA(r3)
	  bl        0xDA0
	  mr        r3, r30
	  lwz       r12, 0x3B4(r30)
	  mr        r4, r28
	  lwz       r12, 0x6C(r12)
	  mtlr      r12
	  blrl

	.loc_0x4E0:
	  lwz       r0, 0x154(r1)
	  lfd       f31, 0x148(r1)
	  lfd       f30, 0x140(r1)
	  lwz       r31, 0x13C(r1)
	  lwz       r30, 0x138(r1)
	  lwz       r29, 0x134(r1)
	  lwz       r28, 0x130(r1)
	  addi      r1, r1, 0x150
	  mtlr      r0
	  blr
	*/
}
