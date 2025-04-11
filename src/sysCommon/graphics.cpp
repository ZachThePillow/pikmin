#include "types.h"
#include "stl/math.h"

#include "Graphics.h"
#include "Colour.h"
#include "Material.h"
#include "Font.h"
#include "Collision.h"
#include "Plane.h"
#include "Texture.h"
#include "Shape.h"
#include "sysNew.h"
#include "PVW.h"
#include "DebugLog.h"
#include "nlib/Math.h"

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
DEFINE_PRINT("Graphics");

/*
 * --INFO--
 * Address:	........
 * Size:	000094
 */
void Colour::write(Stream& s)
{
	r = s.readByte();
	g = s.readByte();
	b = s.readByte();
	a = s.readByte();
}

/*
 * --INFO--
 * Address:	........
 * Size:	000064
 */
void PVWLightingInfo::read(RandomAccessStream& s)
{
	_00 = s.readInt();
	_08 = s.readFloat();
}

/*
 * --INFO--
 * Address:	80025914
 * Size:	000120
 */
void PVWPolygonColourInfo::animate(f32* data, Colour& col)
{
	// If there is no animation loaded, don't do anything
	if (mTotalFrameCount == 0) {
		return;
	}

	if (data) {
		mCurrentFrame = std::fmodf(data[0], mTotalFrameCount);
	} else {
		// If no new data is provided, increment the current frame
		mCurrentFrame += gsys->getFrameTime() * (30.0f * mSpeed);

		// Wrap around if we've reached the end of the animation
		if (mCurrentFrame >= mTotalFrameCount - 1) {
			mCurrentFrame = 0.0f;
		}
	}

	// Animate colour and transparency separately
	mColourInfo.extract(mCurrentFrame, col);
	mAlphaInfo.extract(mCurrentFrame, col);
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A0
 */
f32 subExtract(f32 time, void* source, void* destination)
{
	// TODO
}

/*
 * --INFO--
 * Address:	80025A34
 * Size:	000498
 */
void PVWColourAnimInfo::extract(f32 value, Colour& target)
{
	// If there is no animation data, return without modification
	if (mTotalFrameCount == 0) {
		return;
	}
	/*
	.loc_0x0:
	  stwu      r1, -0x1F8(r1)
	  stfd      f31, 0x1F0(r1)
	  stfd      f30, 0x1E8(r1)
	  stfd      f29, 0x1E0(r1)
	  stfd      f28, 0x1D8(r1)
	  stfd      f27, 0x1D0(r1)
	  stfd      f26, 0x1C8(r1)
	  stfd      f25, 0x1C0(r1)
	  stfd      f24, 0x1B8(r1)
	  stfd      f23, 0x1B0(r1)
	  stfd      f22, 0x1A8(r1)
	  stfd      f21, 0x1A0(r1)
	  stfd      f20, 0x198(r1)
	  stfd      f19, 0x190(r1)
	  stfd      f18, 0x188(r1)
	  stfd      f17, 0x180(r1)
	  lwz       r5, 0x0(r3)
	  cmplwi    r5, 0
	  beq-      .loc_0x454
	  cmplwi    r5, 0x1
	  bne-      .loc_0x7C
	  lwz       r5, 0x4(r3)
	  lbz       r0, 0x4(r5)
	  stb       r0, 0x0(r4)
	  lwz       r5, 0x4(r3)
	  lbz       r0, 0x10(r5)
	  stb       r0, 0x1(r4)
	  lwz       r3, 0x4(r3)
	  lbz       r0, 0x1C(r3)
	  stb       r0, 0x2(r4)
	  b         .loc_0x454

	.loc_0x7C:
	  subic.    r0, r5, 0x1
	  lfd       f2, -0x7DD0(r2)
	  li        r8, 0
	  li        r9, 0
	  mtctr     r0
	  li        r6, 0
	  lis       r5, 0x4330
	  ble-      .loc_0xF8

	.loc_0x9C:
	  lwz       r0, 0x4(r3)
	  add       r7, r0, r6
	  lwz       r0, 0x0(r7)
	  stw       r0, 0x17C(r1)
	  stw       r5, 0x178(r1)
	  lfd       f0, 0x178(r1)
	  fsubs     f0, f0, f2
	  fcmpo     cr0, f0, f1
	  cror      2, 0, 0x2
	  bne-      .loc_0xEC
	  lwz       r0, 0x28(r7)
	  stw       r0, 0x17C(r1)
	  stw       r5, 0x178(r1)
	  lfd       f0, 0x178(r1)
	  fsubs     f0, f0, f2
	  fcmpo     cr0, f0, f1
	  cror      2, 0x1, 0x2
	  bne-      .loc_0xEC
	  mr        r8, r9
	  b         .loc_0xF8

	.loc_0xEC:
	  addi      r6, r6, 0x28
	  addi      r9, r9, 0x1
	  bdnz+     .loc_0x9C

	.loc_0xF8:
	  mulli     r0, r8, 0x28
	  lwz       r3, 0x4(r3)
	  lfd       f13, -0x7DD0(r2)
	  lwzx      r8, r3, r0
	  add       r6, r3, r0
	  lbz       r0, 0x4(r6)
	  lis       r5, 0x4330
	  stw       r8, 0x164(r1)
	  lbz       r3, 0x2C(r6)
	  stw       r0, 0x16C(r1)
	  lwz       r7, 0x28(r6)
	  stw       r5, 0x160(r1)
	  lfs       f0, 0x30(r6)
	  stw       r5, 0x168(r1)
	  lfd       f2, 0x160(r1)
	  lfd       f3, 0x168(r1)
	  fsubs     f2, f2, f13
	  lfs       f5, 0xC(r6)
	  lfs       f4, 0x8(r6)
	  fsubs     f3, f3, f13
	  stw       r7, 0x174(r1)
	  stfs      f2, 0x104(r1)
	  stfs      f3, 0x108(r1)
	  stw       r5, 0x170(r1)
	  stfs      f4, 0x10C(r1)
	  lfd       f2, 0x170(r1)
	  stfs      f5, 0x110(r1)
	  fsubs     f2, f2, f13
	  lfs       f3, 0x104(r1)
	  lfs       f12, -0x7DC8(r2)
	  fsubs     f2, f2, f3
	  stw       r3, 0x17C(r1)
	  lbz       r3, 0x38(r6)
	  fsubs     f20, f1, f3
	  stw       r5, 0x178(r1)
	  fdivs     f8, f12, f2
	  stw       r3, 0x15C(r1)
	  lfd       f3, 0x178(r1)
	  lbz       r0, 0x10(r6)
	  stw       r5, 0x158(r1)
	  fmuls     f2, f20, f20
	  lfs       f10, -0x7DC0(r2)
	  fsubs     f19, f3, f13
	  lfd       f3, 0x158(r1)
	  lfs       f11, -0x7DC4(r2)
	  fmuls     f6, f8, f2
	  stw       r0, 0x154(r1)
	  fsubs     f30, f3, f13
	  lfs       f9, -0x7DBC(r2)
	  stw       r5, 0x150(r1)
	  fmuls     f5, f6, f8
	  lfd       f2, 0x150(r1)
	  fmuls     f4, f11, f6
	  lfs       f7, 0x108(r1)
	  lfs       f17, 0x110(r1)
	  fmuls     f3, f20, f5
	  lfs       f29, 0x3C(r6)
	  fmuls     f21, f10, f5
	  fsubs     f2, f2, f13
	  fmuls     f5, f3, f8
	  fsubs     f8, f3, f4
	  lfs       f4, 0x18(r6)
	  fsubs     f18, f3, f6
	  fmuls     f6, f11, f5
	  fmuls     f5, f9, f5
	  fadds     f8, f20, f8
	  lfs       f3, 0x14(r6)
	  fsubs     f6, f6, f21
	  fadds     f5, f5, f21
	  fmuls     f8, f17, f8
	  fadds     f6, f12, f6
	  fmuls     f17, f0, f18
	  fmuls     f5, f19, f5
	  fmuls     f0, f7, f6
	  fadds     f0, f0, f5
	  fadds     f0, f8, f0
	  fadds     f31, f17, f0
	  stw       r8, 0x14C(r1)
	  stw       r5, 0x148(r1)
	  lfd       f0, 0x148(r1)
	  stw       r8, 0x12C(r1)
	  fsubs     f0, f0, f13
	  stw       r7, 0x144(r1)
	  stfs      f0, 0xE4(r1)
	  stfs      f2, 0xE8(r1)
	  stfs      f3, 0xEC(r1)
	  stfs      f4, 0xF0(r1)
	  lbz       r0, 0x1C(r6)
	  stw       r5, 0x128(r1)
	  lbz       r3, 0x44(r6)
	  stw       r0, 0x134(r1)
	  lfd       f0, 0x128(r1)
	  stw       r5, 0x130(r1)
	  fsubs     f0, f0, f13
	  lfs       f8, 0xE4(r1)
	  lfd       f2, 0x130(r1)
	  lfs       f7, 0xF0(r1)
	  fsubs     f27, f1, f8
	  fsubs     f3, f2, f13
	  stw       r7, 0x124(r1)
	  lfs       f5, 0xE8(r1)
	  fmuls     f2, f27, f27
	  lfs       f26, 0x48(r6)
	  lfs       f6, 0x24(r6)
	  lfs       f4, 0x20(r6)
	  stw       r5, 0x140(r1)
	  stfs      f0, 0xC4(r1)
	  stfs      f3, 0xC8(r1)
	  lfd       f3, 0x140(r1)
	  stw       r5, 0x120(r1)
	  fsubs     f3, f3, f13
	  stfs      f4, 0xCC(r1)
	  lfd       f0, 0x120(r1)
	  stfs      f6, 0xD0(r1)
	  fsubs     f3, f3, f8
	  fsubs     f0, f0, f13
	  lfs       f6, 0xC4(r1)
	  fdivs     f18, f12, f3
	  stw       r3, 0x13C(r1)
	  lfs       f19, -0x7DD4(r2)
	  stw       r5, 0x138(r1)
	  lfd       f3, 0x138(r1)
	  fmuls     f28, f18, f2
	  lfs       f2, 0xD0(r1)
	  fsubs     f4, f0, f6
	  lfs       f0, 0xC8(r1)
	  fsubs     f21, f1, f6
	  fmuls     f17, f28, f18
	  fdivs     f1, f12, f4
	  fmuls     f4, f21, f21
	  fmuls     f8, f27, f17
	  fmuls     f20, f10, f17
	  fmuls     f22, f1, f4
	  fmuls     f17, f8, f18
	  fmuls     f6, f11, f28
	  fmuls     f23, f22, f1
	  fmuls     f4, f11, f17
	  fsubs     f6, f8, f6
	  fmuls     f24, f21, f23
	  fsubs     f4, f4, f20
	  fmuls     f17, f9, f17
	  fmuls     f25, f24, f1
	  fmuls     f18, f11, f22
	  fadds     f1, f17, f20
	  fmuls     f17, f10, f23
	  fmuls     f10, f11, f25
	  fsubs     f20, f24, f18
	  fadds     f4, f12, f4
	  fmuls     f9, f9, f25
	  fsubs     f11, f3, f13
	  fadds     f20, f21, f20
	  fadds     f3, f9, f17
	  fmuls     f9, f5, f4
	  fsubs     f10, f10, f17
	  fmuls     f5, f30, f1
	  fmuls     f1, f11, f3
	  fadds     f4, f12, f10
	  fadds     f6, f27, f6
	  fsubs     f8, f8, f28
	  fmuls     f0, f0, f4
	  fadds     f3, f9, f5
	  fmuls     f4, f7, f6
	  fsubs     f18, f24, f22
	  fadds     f0, f0, f1
	  fmuls     f2, f2, f20
	  fmuls     f5, f29, f8
	  fadds     f3, f4, f3
	  fadds     f0, f2, f0
	  fmuls     f1, f26, f18
	  fcmpo     cr0, f31, f19
	  fadds     f2, f5, f3
	  fadds     f1, f1, f0
	  bge-      .loc_0x3B4
	  li        r0, 0
	  b         .loc_0x3D8

	.loc_0x3B4:
	  lfs       f0, -0x7DB8(r2)
	  fcmpo     cr0, f31, f0
	  ble-      .loc_0x3C8
	  li        r0, 0xFF
	  b         .loc_0x3D8

	.loc_0x3C8:
	  fctiwz    f0, f31
	  stfd      f0, 0x120(r1)
	  lwz       r0, 0x124(r1)
	  rlwinm    r0,r0,0,24,31

	.loc_0x3D8:
	  stb       r0, 0x0(r4)
	  lfs       f0, -0x7DD4(r2)
	  fcmpo     cr0, f2, f0
	  bge-      .loc_0x3F0
	  li        r0, 0
	  b         .loc_0x414

	.loc_0x3F0:
	  lfs       f0, -0x7DB8(r2)
	  fcmpo     cr0, f2, f0
	  ble-      .loc_0x404
	  li        r0, 0xFF
	  b         .loc_0x414

	.loc_0x404:
	  fctiwz    f0, f2
	  stfd      f0, 0x120(r1)
	  lwz       r0, 0x124(r1)
	  rlwinm    r0,r0,0,24,31

	.loc_0x414:
	  stb       r0, 0x1(r4)
	  lfs       f0, -0x7DD4(r2)
	  fcmpo     cr0, f1, f0
	  bge-      .loc_0x42C
	  li        r0, 0
	  b         .loc_0x450

	.loc_0x42C:
	  lfs       f0, -0x7DB8(r2)
	  fcmpo     cr0, f1, f0
	  ble-      .loc_0x440
	  li        r0, 0xFF
	  b         .loc_0x450

	.loc_0x440:
	  fctiwz    f0, f1
	  stfd      f0, 0x120(r1)
	  lwz       r0, 0x124(r1)
	  rlwinm    r0,r0,0,24,31

	.loc_0x450:
	  stb       r0, 0x2(r4)

	.loc_0x454:
	  lfd       f31, 0x1F0(r1)
	  lfd       f30, 0x1E8(r1)
	  lfd       f29, 0x1E0(r1)
	  lfd       f28, 0x1D8(r1)
	  lfd       f27, 0x1D0(r1)
	  lfd       f26, 0x1C8(r1)
	  lfd       f25, 0x1C0(r1)
	  lfd       f24, 0x1B8(r1)
	  lfd       f23, 0x1B0(r1)
	  lfd       f22, 0x1A8(r1)
	  lfd       f21, 0x1A0(r1)
	  lfd       f20, 0x198(r1)
	  lfd       f19, 0x190(r1)
	  lfd       f18, 0x188(r1)
	  lfd       f17, 0x180(r1)
	  addi      r1, r1, 0x1F8
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80025ECC
 * Size:	0001F8
 */
void PVWAlphaAnimInfo::extract(f32, Colour&)
{
	/*
	.loc_0x0:
	  stwu      r1, -0xA0(r1)
	  stfd      f31, 0x98(r1)
	  stfd      f30, 0x90(r1)
	  lwz       r5, 0x0(r3)
	  cmplwi    r5, 0
	  beq-      .loc_0x1E8
	  cmplwi    r5, 0x1
	  bne-      .loc_0x30
	  lwz       r3, 0x4(r3)
	  lbz       r0, 0x4(r3)
	  stb       r0, 0x3(r4)
	  b         .loc_0x1E8

	.loc_0x30:
	  subic.    r0, r5, 0x1
	  lfd       f2, -0x7DD0(r2)
	  li        r8, 0
	  li        r9, 0
	  mtctr     r0
	  li        r6, 0
	  lis       r5, 0x4330
	  ble-      .loc_0xAC

	.loc_0x50:
	  lwz       r0, 0x4(r3)
	  add       r7, r0, r6
	  lwz       r0, 0x0(r7)
	  stw       r0, 0x8C(r1)
	  stw       r5, 0x88(r1)
	  lfd       f0, 0x88(r1)
	  fsubs     f0, f0, f2
	  fcmpo     cr0, f0, f1
	  cror      2, 0, 0x2
	  bne-      .loc_0xA0
	  lwz       r0, 0x10(r7)
	  stw       r0, 0x8C(r1)
	  stw       r5, 0x88(r1)
	  lfd       f0, 0x88(r1)
	  fsubs     f0, f0, f2
	  fcmpo     cr0, f0, f1
	  cror      2, 0x1, 0x2
	  bne-      .loc_0xA0
	  mr        r8, r9
	  b         .loc_0xAC

	.loc_0xA0:
	  addi      r6, r6, 0x10
	  addi      r9, r9, 0x1
	  bdnz+     .loc_0x50

	.loc_0xAC:
	  lwz       r6, 0x4(r3)
	  rlwinm    r5,r8,4,0,27
	  lis       r3, 0x4330
	  lfd       f7, -0x7DD0(r2)
	  lwzx      r0, r6, r5
	  add       r6, r6, r5
	  stw       r0, 0x74(r1)
	  lbz       r0, 0x4(r6)
	  stw       r3, 0x70(r1)
	  lbz       r5, 0x14(r6)
	  stw       r0, 0x7C(r1)
	  lfd       f0, 0x70(r1)
	  stw       r3, 0x78(r1)
	  lwz       r0, 0x10(r6)
	  fsubs     f0, f0, f7
	  lfd       f2, 0x78(r1)
	  lfs       f10, 0x18(r6)
	  stw       r0, 0x84(r1)
	  fsubs     f2, f2, f7
	  lfs       f4, 0xC(r6)
	  lfs       f3, 0x8(r6)
	  stw       r3, 0x80(r1)
	  stfs      f0, 0x58(r1)
	  lfd       f0, 0x80(r1)
	  stfs      f2, 0x5C(r1)
	  fsubs     f0, f0, f7
	  stfs      f3, 0x60(r1)
	  stfs      f4, 0x64(r1)
	  lfs       f2, 0x58(r1)
	  lfs       f8, -0x7DC8(r2)
	  fsubs     f0, f0, f2
	  stw       r5, 0x8C(r1)
	  fsubs     f31, f1, f2
	  lfs       f2, -0x7DC0(r2)
	  stw       r3, 0x88(r1)
	  fdivs     f13, f8, f0
	  lfd       f0, 0x88(r1)
	  lfs       f5, -0x7DC4(r2)
	  lfs       f1, -0x7DBC(r2)
	  lfs       f3, 0x5C(r1)
	  fmuls     f4, f31, f31
	  lfs       f6, 0x64(r1)
	  fsubs     f9, f0, f7
	  lfs       f0, -0x7DD4(r2)
	  fmuls     f12, f13, f4
	  fmuls     f11, f12, f13
	  fmuls     f4, f5, f12
	  fmuls     f7, f31, f11
	  fmuls     f30, f2, f11
	  fmuls     f11, f7, f13
	  fsubs     f4, f7, f4
	  fsubs     f7, f7, f12
	  fmuls     f2, f5, f11
	  fmuls     f1, f1, f11
	  fadds     f4, f31, f4
	  fsubs     f2, f2, f30
	  fadds     f1, f1, f30
	  fmuls     f4, f6, f4
	  fadds     f2, f8, f2
	  fmuls     f1, f9, f1
	  fmuls     f5, f10, f7
	  fmuls     f2, f3, f2
	  fadds     f1, f2, f1
	  fadds     f1, f4, f1
	  fadds     f1, f5, f1
	  fcmpo     cr0, f1, f0
	  bge-      .loc_0x1C0
	  li        r0, 0
	  b         .loc_0x1E4

	.loc_0x1C0:
	  lfs       f0, -0x7DB8(r2)
	  fcmpo     cr0, f1, f0
	  ble-      .loc_0x1D4
	  li        r0, 0xFF
	  b         .loc_0x1E4

	.loc_0x1D4:
	  fctiwz    f0, f1
	  stfd      f0, 0x70(r1)
	  lwz       r0, 0x74(r1)
	  rlwinm    r0,r0,0,24,31

	.loc_0x1E4:
	  stb       r0, 0x3(r4)

	.loc_0x1E8:
	  lfd       f31, 0x98(r1)
	  lfd       f30, 0x90(r1)
	  addi      r1, r1, 0xA0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800260C4
 * Size:	0004A0
 */
void PVWColourShortAnimInfo::extract(f32, ShortColour&)
{
	/*
	.loc_0x0:
	  stwu      r1, -0x1D8(r1)
	  stfd      f31, 0x1D0(r1)
	  stfd      f30, 0x1C8(r1)
	  stfd      f29, 0x1C0(r1)
	  stfd      f28, 0x1B8(r1)
	  stfd      f27, 0x1B0(r1)
	  stfd      f26, 0x1A8(r1)
	  stfd      f25, 0x1A0(r1)
	  stfd      f24, 0x198(r1)
	  stfd      f23, 0x190(r1)
	  stfd      f22, 0x188(r1)
	  stfd      f21, 0x180(r1)
	  lwz       r5, 0x0(r3)
	  cmplwi    r5, 0
	  beq-      .loc_0x46C
	  cmplwi    r5, 0x1
	  bne-      .loc_0x6C
	  lwz       r5, 0x4(r3)
	  lha       r0, 0x4(r5)
	  sth       r0, 0x0(r4)
	  lwz       r5, 0x4(r3)
	  lha       r0, 0x10(r5)
	  sth       r0, 0x2(r4)
	  lwz       r3, 0x4(r3)
	  lha       r0, 0x1C(r3)
	  sth       r0, 0x4(r4)
	  b         .loc_0x46C

	.loc_0x6C:
	  subic.    r0, r5, 0x1
	  lfd       f2, -0x7DD0(r2)
	  li        r8, 0
	  li        r9, 0
	  mtctr     r0
	  li        r6, 0
	  lis       r5, 0x4330
	  ble-      .loc_0xE8

	.loc_0x8C:
	  lwz       r0, 0x4(r3)
	  add       r7, r0, r6
	  lwz       r0, 0x0(r7)
	  stw       r0, 0x17C(r1)
	  stw       r5, 0x178(r1)
	  lfd       f0, 0x178(r1)
	  fsubs     f0, f0, f2
	  fcmpo     cr0, f0, f1
	  cror      2, 0, 0x2
	  bne-      .loc_0xDC
	  lwz       r0, 0x28(r7)
	  stw       r0, 0x17C(r1)
	  stw       r5, 0x178(r1)
	  lfd       f0, 0x178(r1)
	  fsubs     f0, f0, f2
	  fcmpo     cr0, f0, f1
	  cror      2, 0x1, 0x2
	  bne-      .loc_0xDC
	  mr        r8, r9
	  b         .loc_0xE8

	.loc_0xDC:
	  addi      r6, r6, 0x28
	  addi      r9, r9, 0x1
	  bdnz+     .loc_0x8C

	.loc_0xE8:
	  mulli     r0, r8, 0x28
	  lwz       r3, 0x4(r3)
	  lfd       f5, -0x7DD0(r2)
	  lfd       f6, -0x7DA8(r2)
	  add       r6, r3, r0
	  lwzx      r8, r3, r0
	  lis       r5, 0x4330
	  lha       r0, 0x4(r6)
	  stw       r8, 0x164(r1)
	  xoris     r0, r0, 0x8000
	  lwz       r7, 0x28(r6)
	  stw       r0, 0x16C(r1)
	  lha       r3, 0x2C(r6)
	  stw       r5, 0x160(r1)
	  xoris     r0, r3, 0x8000
	  lfs       f7, 0x30(r6)
	  stw       r5, 0x168(r1)
	  lfd       f0, 0x160(r1)
	  lfd       f2, 0x168(r1)
	  stw       r7, 0x174(r1)
	  fsubs     f0, f0, f5
	  lfs       f4, 0xC(r6)
	  fsubs     f2, f2, f6
	  lfs       f3, 0x8(r6)
	  stw       r5, 0x170(r1)
	  stfs      f0, 0x104(r1)
	  lfd       f0, 0x170(r1)
	  stfs      f2, 0x108(r1)
	  fsubs     f0, f0, f5
	  stfs      f3, 0x10C(r1)
	  stfs      f4, 0x110(r1)
	  lfs       f2, 0x104(r1)
	  lfs       f4, -0x7DC8(r2)
	  fsubs     f0, f0, f2
	  stw       r0, 0x17C(r1)
	  lha       r3, 0x38(r6)
	  fsubs     f31, f1, f2
	  stw       r5, 0x178(r1)
	  fdivs     f12, f4, f0
	  lfd       f2, 0x178(r1)
	  lha       r0, 0x10(r6)
	  xoris     r3, r3, 0x8000
	  stw       r3, 0x15C(r1)
	  fmuls     f0, f31, f31
	  lfs       f3, -0x7DC4(r2)
	  fsubs     f30, f2, f6
	  xoris     r0, r0, 0x8000
	  lfs       f2, -0x7DC0(r2)
	  fmuls     f27, f12, f0
	  stw       r0, 0x154(r1)
	  lfs       f0, -0x7DBC(r2)
	  stw       r5, 0x158(r1)
	  fmuls     f10, f27, f12
	  fmuls     f9, f3, f27
	  lfd       f8, 0x158(r1)
	  lfs       f13, 0x108(r1)
	  fmuls     f11, f31, f10
	  fmuls     f22, f2, f10
	  lfs       f28, 0x110(r1)
	  fsubs     f8, f8, f6
	  fmuls     f12, f11, f12
	  fsubs     f10, f11, f9
	  fsubs     f29, f11, f27
	  stw       r5, 0x150(r1)
	  fmuls     f11, f3, f12
	  fadds     f27, f31, f10
	  fmuls     f9, f0, f12
	  fsubs     f12, f11, f22
	  lfd       f10, 0x150(r1)
	  fmuls     f27, f28, f27
	  fadds     f11, f9, f22
	  fmuls     f28, f7, f29
	  fadds     f12, f4, f12
	  lfs       f9, 0x3C(r6)
	  fmuls     f11, f30, f11
	  lfs       f29, 0x18(r6)
	  fmuls     f7, f13, f12
	  fsubs     f12, f10, f6
	  lfs       f13, 0x14(r6)
	  fadds     f7, f7, f11
	  fadds     f7, f27, f7
	  fadds     f7, f28, f7
	  stw       r8, 0x14C(r1)
	  stw       r5, 0x148(r1)
	  lfd       f10, 0x148(r1)
	  stw       r7, 0x144(r1)
	  fsubs     f10, f10, f5
	  stw       r8, 0x12C(r1)
	  stfs      f10, 0xE4(r1)
	  stfs      f12, 0xE8(r1)
	  stw       r5, 0x140(r1)
	  stfs      f13, 0xEC(r1)
	  lfd       f10, 0x140(r1)
	  stfs      f29, 0xF0(r1)
	  fsubs     f10, f10, f5
	  lfs       f11, 0xE4(r1)
	  lha       r0, 0x1C(r6)
	  fsubs     f10, f10, f11
	  stw       r7, 0x124(r1)
	  fsubs     f25, f1, f11
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x134(r1)
	  fdivs     f26, f4, f10
	  stw       r5, 0x128(r1)
	  lha       r0, 0x44(r6)
	  stw       r5, 0x130(r1)
	  lfd       f10, 0x128(r1)
	  fmuls     f13, f25, f25
	  lfd       f11, 0x130(r1)
	  fsubs     f12, f10, f5
	  lfs       f28, 0xF0(r1)
	  lfs       f30, 0xE8(r1)
	  fmuls     f31, f26, f13
	  lfs       f10, 0x48(r6)
	  lfs       f22, 0x24(r6)
	  fsubs     f24, f11, f6
	  lfs       f23, 0x20(r6)
	  fmuls     f29, f31, f26
	  stw       r5, 0x120(r1)
	  fmuls     f13, f3, f31
	  xoris     r0, r0, 0x8000
	  stfs      f12, 0xC4(r1)
	  fmuls     f27, f25, f29
	  lfd       f11, 0x120(r1)
	  stfs      f24, 0xC8(r1)
	  fmuls     f21, f2, f29
	  fsubs     f5, f11, f5
	  fmuls     f11, f27, f26
	  stfs      f23, 0xCC(r1)
	  fsubs     f13, f27, f13
	  stfs      f22, 0xD0(r1)
	  fsubs     f27, f27, f31
	  fmuls     f12, f3, f11
	  lfs       f22, 0xC4(r1)
	  fmuls     f11, f0, f11
	  stw       r0, 0x13C(r1)
	  fadds     f29, f25, f13
	  fadds     f13, f11, f21
	  stw       r5, 0x138(r1)
	  fsubs     f11, f5, f22
	  fsubs     f5, f1, f22
	  fsubs     f12, f12, f21
	  fdivs     f1, f4, f11
	  fadds     f31, f4, f12
	  lfd       f12, 0x138(r1)
	  fmuls     f11, f5, f5
	  fmuls     f8, f8, f13
	  fmuls     f31, f30, f31
	  fmuls     f24, f1, f11
	  lfs       f11, 0xD0(r1)
	  fmuls     f13, f28, f29
	  fadds     f8, f31, f8
	  fsubs     f22, f12, f6
	  fmuls     f9, f9, f27
	  fadds     f6, f13, f8
	  lfs       f8, 0xC8(r1)
	  fmuls     f13, f24, f1
	  fadds     f12, f9, f6
	  lfs       f6, -0x7DB4(r2)
	  fmuls     f23, f5, f13
	  fmuls     f21, f2, f13
	  fmuls     f9, f3, f24
	  fmuls     f13, f23, f1
	  fcmpo     cr0, f7, f6
	  fsubs     f2, f23, f9
	  fmuls     f1, f3, f13
	  fmuls     f0, f0, f13
	  fadds     f2, f5, f2
	  fsubs     f1, f1, f21
	  fadds     f0, f0, f21
	  fsubs     f6, f23, f24
	  fadds     f1, f4, f1
	  fmuls     f0, f22, f0
	  fmuls     f2, f11, f2
	  fmuls     f1, f8, f1
	  fmuls     f3, f10, f6
	  fadds     f0, f1, f0
	  fadds     f0, f2, f0
	  fadds     f1, f3, f0
	  bge-      .loc_0x3C0
	  li        r0, -0x3FF
	  b         .loc_0x3E4

	.loc_0x3C0:
	  lfs       f0, -0x7DB0(r2)
	  fcmpo     cr0, f7, f0
	  ble-      .loc_0x3D4
	  li        r0, 0x3FF
	  b         .loc_0x3E4

	.loc_0x3D4:
	  fctiwz    f0, f7
	  stfd      f0, 0x120(r1)
	  lwz       r0, 0x124(r1)
	  extsh     r0, r0

	.loc_0x3E4:
	  extsh     r0, r0
	  sth       r0, 0x0(r4)
	  lfs       f0, -0x7DB4(r2)
	  fcmpo     cr0, f12, f0
	  bge-      .loc_0x400
	  li        r0, -0x3FF
	  b         .loc_0x424

	.loc_0x400:
	  lfs       f0, -0x7DB0(r2)
	  fcmpo     cr0, f12, f0
	  ble-      .loc_0x414
	  li        r0, 0x3FF
	  b         .loc_0x424

	.loc_0x414:
	  fctiwz    f0, f12
	  stfd      f0, 0x120(r1)
	  lwz       r0, 0x124(r1)
	  extsh     r0, r0

	.loc_0x424:
	  extsh     r0, r0
	  sth       r0, 0x2(r4)
	  lfs       f0, -0x7DB4(r2)
	  fcmpo     cr0, f1, f0
	  bge-      .loc_0x440
	  li        r0, -0x3FF
	  b         .loc_0x464

	.loc_0x440:
	  lfs       f0, -0x7DB0(r2)
	  fcmpo     cr0, f1, f0
	  ble-      .loc_0x454
	  li        r0, 0x3FF
	  b         .loc_0x464

	.loc_0x454:
	  fctiwz    f0, f1
	  stfd      f0, 0x120(r1)
	  lwz       r0, 0x124(r1)
	  extsh     r0, r0

	.loc_0x464:
	  extsh     r0, r0
	  sth       r0, 0x4(r4)

	.loc_0x46C:
	  lfd       f31, 0x1D0(r1)
	  lfd       f30, 0x1C8(r1)
	  lfd       f29, 0x1C0(r1)
	  lfd       f28, 0x1B8(r1)
	  lfd       f27, 0x1B0(r1)
	  lfd       f26, 0x1A8(r1)
	  lfd       f25, 0x1A0(r1)
	  lfd       f24, 0x198(r1)
	  lfd       f23, 0x190(r1)
	  lfd       f22, 0x188(r1)
	  lfd       f21, 0x180(r1)
	  addi      r1, r1, 0x1D8
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80026564
 * Size:	000208
 */
void PVWAlphaShortAnimInfo::extract(f32, ShortColour&)
{
	/*
	.loc_0x0:
	  stwu      r1, -0xA0(r1)
	  stfd      f31, 0x98(r1)
	  stfd      f30, 0x90(r1)
	  lwz       r5, 0x0(r3)
	  cmplwi    r5, 0
	  beq-      .loc_0x1F8
	  cmplwi    r5, 0x1
	  bne-      .loc_0x30
	  lwz       r3, 0x4(r3)
	  lha       r0, 0x4(r3)
	  sth       r0, 0x6(r4)
	  b         .loc_0x1F8

	.loc_0x30:
	  subic.    r0, r5, 0x1
	  lfd       f2, -0x7DD0(r2)
	  li        r8, 0
	  li        r9, 0
	  mtctr     r0
	  li        r6, 0
	  lis       r5, 0x4330
	  ble-      .loc_0xAC

	.loc_0x50:
	  lwz       r0, 0x4(r3)
	  add       r7, r0, r6
	  lwz       r0, 0x0(r7)
	  stw       r0, 0x8C(r1)
	  stw       r5, 0x88(r1)
	  lfd       f0, 0x88(r1)
	  fsubs     f0, f0, f2
	  fcmpo     cr0, f0, f1
	  cror      2, 0, 0x2
	  bne-      .loc_0xA0
	  lwz       r0, 0x10(r7)
	  stw       r0, 0x8C(r1)
	  stw       r5, 0x88(r1)
	  lfd       f0, 0x88(r1)
	  fsubs     f0, f0, f2
	  fcmpo     cr0, f0, f1
	  cror      2, 0x1, 0x2
	  bne-      .loc_0xA0
	  mr        r8, r9
	  b         .loc_0xAC

	.loc_0xA0:
	  addi      r6, r6, 0x10
	  addi      r9, r9, 0x1
	  bdnz+     .loc_0x50

	.loc_0xAC:
	  lwz       r3, 0x4(r3)
	  rlwinm    r0,r8,4,0,27
	  lis       r5, 0x4330
	  lfd       f4, -0x7DD0(r2)
	  add       r6, r3, r0
	  lwzx      r0, r3, r0
	  lha       r3, 0x4(r6)
	  stw       r0, 0x74(r1)
	  xoris     r0, r3, 0x8000
	  lha       r3, 0x14(r6)
	  stw       r0, 0x7C(r1)
	  lwz       r0, 0x10(r6)
	  xoris     r3, r3, 0x8000
	  stw       r5, 0x70(r1)
	  lfd       f8, -0x7DA8(r2)
	  stw       r5, 0x78(r1)
	  lfd       f0, 0x70(r1)
	  lfd       f3, 0x78(r1)
	  fsubs     f2, f0, f4
	  stw       r0, 0x84(r1)
	  lfs       f0, 0x18(r6)
	  fsubs     f5, f3, f8
	  stw       r5, 0x80(r1)
	  lfs       f7, 0xC(r6)
	  lfs       f6, 0x8(r6)
	  lfd       f3, 0x80(r1)
	  stfs      f2, 0x58(r1)
	  fsubs     f2, f3, f4
	  stfs      f5, 0x5C(r1)
	  stfs      f6, 0x60(r1)
	  stfs      f7, 0x64(r1)
	  lfs       f3, 0x58(r1)
	  lfs       f9, -0x7DC8(r2)
	  fsubs     f2, f2, f3
	  stw       r3, 0x8C(r1)
	  fsubs     f31, f1, f3
	  lfs       f3, -0x7DC0(r2)
	  stw       r5, 0x88(r1)
	  fdivs     f13, f9, f2
	  lfd       f1, 0x88(r1)
	  lfs       f6, -0x7DC4(r2)
	  lfs       f2, -0x7DBC(r2)
	  lfs       f4, 0x5C(r1)
	  fmuls     f5, f31, f31
	  lfs       f7, 0x64(r1)
	  fsubs     f10, f1, f8
	  lfs       f1, -0x7DD4(r2)
	  fmuls     f12, f13, f5
	  fmuls     f11, f12, f13
	  fmuls     f5, f6, f12
	  fmuls     f8, f31, f11
	  fmuls     f30, f3, f11
	  fmuls     f11, f8, f13
	  fsubs     f5, f8, f5
	  fsubs     f8, f8, f12
	  fmuls     f3, f6, f11
	  fmuls     f2, f2, f11
	  fadds     f5, f31, f5
	  fsubs     f3, f3, f30
	  fadds     f2, f2, f30
	  fmuls     f6, f0, f8
	  fadds     f3, f9, f3
	  fmuls     f2, f10, f2
	  fmuls     f5, f7, f5
	  fmuls     f0, f4, f3
	  fadds     f0, f0, f2
	  fadds     f0, f5, f0
	  fadds     f2, f6, f0
	  fcmpo     cr0, f2, f1
	  bge-      .loc_0x1CC
	  li        r0, 0
	  b         .loc_0x1F0

	.loc_0x1CC:
	  lfs       f0, -0x7DB8(r2)
	  fcmpo     cr0, f2, f0
	  ble-      .loc_0x1E0
	  li        r0, 0xFF
	  b         .loc_0x1F0

	.loc_0x1E0:
	  fctiwz    f0, f2
	  stfd      f0, 0x70(r1)
	  lwz       r0, 0x74(r1)
	  extsh     r0, r0

	.loc_0x1F0:
	  extsh     r0, r0
	  sth       r0, 0x6(r4)

	.loc_0x1F8:
	  lfd       f31, 0x98(r1)
	  lfd       f30, 0x90(r1)
	  addi      r1, r1, 0xA0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8002676C
 * Size:	0003B0
 */
void PVWTexAnimInfo::extract(f32, Vector3f&)
{
	/*
	.loc_0x0:
	  stwu      r1, -0x158(r1)
	  stfd      f31, 0x150(r1)
	  stfd      f30, 0x148(r1)
	  stfd      f29, 0x140(r1)
	  lwz       r7, 0x0(r3)
	  cmplwi    r7, 0
	  beq-      .loc_0x39C
	  cmplwi    r7, 0x1
	  bne-      .loc_0x4C
	  lwz       r5, 0x4(r3)
	  lfs       f0, 0x4(r5)
	  stfs      f0, 0x0(r4)
	  lwz       r5, 0x4(r3)
	  lfs       f0, 0x10(r5)
	  stfs      f0, 0x4(r4)
	  lwz       r3, 0x4(r3)
	  lfs       f0, 0x1C(r3)
	  stfs      f0, 0x8(r4)
	  b         .loc_0x39C

	.loc_0x4C:
	  mulli     r0, r7, 0x28
	  lwz       r8, 0x4(r3)
	  lfd       f2, -0x7DD0(r2)
	  add       r6, r8, r0
	  lwz       r0, -0x28(r6)
	  lis       r5, 0x4330
	  li        r9, 0
	  stw       r0, 0x13C(r1)
	  stw       r5, 0x138(r1)
	  lfd       f0, 0x138(r1)
	  fsubs     f0, f0, f2
	  fcmpo     cr0, f1, f0
	  cror      2, 0x1, 0x2
	  bne-      .loc_0xC0
	  lfs       f0, -0x24(r6)
	  stfs      f0, 0x0(r4)
	  lwz       r0, 0x0(r3)
	  lwz       r5, 0x4(r3)
	  mulli     r0, r0, 0x28
	  add       r5, r5, r0
	  lfs       f0, -0x18(r5)
	  stfs      f0, 0x4(r4)
	  lwz       r0, 0x0(r3)
	  lwz       r3, 0x4(r3)
	  mulli     r0, r0, 0x28
	  add       r3, r3, r0
	  lfs       f0, -0xC(r3)
	  stfs      f0, 0x8(r4)
	  b         .loc_0x39C

	.loc_0xC0:
	  subic.    r0, r7, 0x1
	  li        r10, 0
	  li        r6, 0
	  mtctr     r0
	  ble-      .loc_0x12C

	.loc_0xD4:
	  add       r7, r8, r6
	  lwz       r0, 0x0(r7)
	  stw       r0, 0x13C(r1)
	  stw       r5, 0x138(r1)
	  lfd       f0, 0x138(r1)
	  fsubs     f0, f0, f2
	  fcmpo     cr0, f0, f1
	  cror      2, 0, 0x2
	  bne-      .loc_0x120
	  lwz       r0, 0x28(r7)
	  stw       r0, 0x13C(r1)
	  stw       r5, 0x138(r1)
	  lfd       f0, 0x138(r1)
	  fsubs     f0, f0, f2
	  fcmpo     cr0, f0, f1
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x120
	  mr        r9, r10
	  b         .loc_0x12C

	.loc_0x120:
	  addi      r6, r6, 0x28
	  addi      r10, r10, 0x1
	  bdnz+     .loc_0xD4

	.loc_0x12C:
	  mulli     r9, r9, 0x28
	  lfd       f5, -0x7DD0(r2)
	  lwzx      r0, r8, r9
	  add       r6, r8, r9
	  lwz       r5, 0x28(r6)
	  lis       r7, 0x4330
	  stw       r0, 0x134(r1)
	  lfs       f13, 0x30(r6)
	  stw       r7, 0x130(r1)
	  lfs       f12, 0x2C(r6)
	  lfd       f0, 0x130(r1)
	  stw       r5, 0x13C(r1)
	  fsubs     f0, f0, f5
	  lfs       f4, 0xC(r6)
	  lfs       f3, 0x8(r6)
	  lfs       f2, 0x4(r6)
	  stw       r7, 0x138(r1)
	  stfs      f0, 0x100(r1)
	  lfd       f0, 0x138(r1)
	  stfs      f2, 0x104(r1)
	  fsubs     f0, f0, f5
	  stfs      f3, 0x108(r1)
	  stfs      f4, 0x10C(r1)
	  lfs       f2, 0x100(r1)
	  lfs       f4, -0x7DC8(r2)
	  fsubs     f6, f0, f2
	  lfs       f3, -0x7DC4(r2)
	  fsubs     f30, f1, f2
	  lfs       f2, -0x7DC0(r2)
	  lfs       f0, -0x7DBC(r2)
	  fdivs     f31, f4, f6
	  lfs       f8, 0x104(r1)
	  lfs       f10, 0x10C(r1)
	  fmuls     f6, f30, f30
	  fmuls     f11, f31, f6
	  fmuls     f9, f11, f31
	  fmuls     f6, f3, f11
	  fmuls     f7, f30, f9
	  fmuls     f29, f2, f9
	  fsubs     f9, f7, f6
	  fmuls     f31, f7, f31
	  fsubs     f11, f7, f11
	  fadds     f9, f30, f9
	  fmuls     f7, f3, f31
	  fmuls     f6, f0, f31
	  fmuls     f9, f10, f9
	  fsubs     f7, f7, f29
	  fadds     f6, f6, f29
	  fmuls     f10, f13, f11
	  fadds     f7, f4, f7
	  fmuls     f6, f12, f6
	  fmuls     f7, f8, f7
	  fadds     f6, f7, f6
	  fadds     f6, f9, f6
	  fadds     f6, f10, f6
	  stfs      f6, 0x0(r4)
	  lwz       r5, 0x4(r3)
	  lwzx      r0, r5, r9
	  add       r6, r5, r9
	  lwz       r5, 0x28(r6)
	  stw       r0, 0x124(r1)
	  lfs       f13, 0x3C(r6)
	  stw       r7, 0x120(r1)
	  lfs       f12, 0x38(r6)
	  lfd       f6, 0x120(r1)
	  lfs       f9, 0x18(r6)
	  stw       r5, 0x12C(r1)
	  fsubs     f6, f6, f5
	  lfs       f8, 0x14(r6)
	  lfs       f7, 0x10(r6)
	  stw       r7, 0x128(r1)
	  stfs      f6, 0xE0(r1)
	  lfd       f6, 0x128(r1)
	  stfs      f7, 0xE4(r1)
	  fsubs     f6, f6, f5
	  stfs      f8, 0xE8(r1)
	  stfs      f9, 0xEC(r1)
	  lfs       f7, 0xE0(r1)
	  fsubs     f31, f1, f7
	  fsubs     f7, f6, f7
	  lfs       f8, 0xE4(r1)
	  fmuls     f6, f31, f31
	  lfs       f10, 0xEC(r1)
	  fdivs     f30, f4, f7
	  fmuls     f11, f30, f6
	  fmuls     f9, f11, f30
	  fmuls     f6, f3, f11
	  fmuls     f7, f31, f9
	  fmuls     f29, f2, f9
	  fmuls     f30, f7, f30
	  fsubs     f9, f7, f6
	  fsubs     f11, f7, f11
	  fmuls     f7, f3, f30
	  fmuls     f6, f0, f30
	  fadds     f9, f31, f9
	  fsubs     f7, f7, f29
	  fadds     f6, f6, f29
	  fmuls     f9, f10, f9
	  fadds     f7, f4, f7
	  fmuls     f6, f12, f6
	  fmuls     f10, f13, f11
	  fmuls     f7, f8, f7
	  fadds     f6, f7, f6
	  fadds     f6, f9, f6
	  fadds     f6, f10, f6
	  stfs      f6, 0x4(r4)
	  lwz       r3, 0x4(r3)
	  lwzx      r0, r3, r9
	  add       r5, r3, r9
	  lwz       r3, 0x28(r5)
	  stw       r0, 0x114(r1)
	  lfs       f11, 0x48(r5)
	  stw       r7, 0x110(r1)
	  lfs       f10, 0x44(r5)
	  lfd       f6, 0x110(r1)
	  stw       r3, 0x11C(r1)
	  fsubs     f6, f6, f5
	  lfs       f9, 0x24(r5)
	  lfs       f8, 0x20(r5)
	  lfs       f7, 0x1C(r5)
	  stw       r7, 0x118(r1)
	  stfs      f6, 0xC0(r1)
	  lfd       f6, 0x118(r1)
	  stfs      f7, 0xC4(r1)
	  fsubs     f6, f6, f5
	  stfs      f8, 0xC8(r1)
	  stfs      f9, 0xCC(r1)
	  lfs       f8, 0xC0(r1)
	  lfs       f5, 0xC4(r1)
	  fsubs     f7, f6, f8
	  lfs       f6, 0xCC(r1)
	  fsubs     f13, f1, f8
	  fdivs     f12, f4, f7
	  fmuls     f1, f13, f13
	  fmuls     f9, f12, f1
	  fmuls     f8, f9, f12
	  fmuls     f1, f3, f9
	  fmuls     f7, f13, f8
	  fmuls     f29, f2, f8
	  fmuls     f8, f7, f12
	  fsubs     f2, f7, f1
	  fsubs     f7, f7, f9
	  fmuls     f1, f3, f8
	  fmuls     f0, f0, f8
	  fadds     f2, f13, f2
	  fsubs     f1, f1, f29
	  fadds     f0, f0, f29
	  fmuls     f2, f6, f2
	  fadds     f1, f4, f1
	  fmuls     f0, f10, f0
	  fmuls     f3, f11, f7
	  fmuls     f1, f5, f1
	  fadds     f0, f1, f0
	  fadds     f0, f2, f0
	  fadds     f0, f3, f0
	  stfs      f0, 0x8(r4)

	.loc_0x39C:
	  lfd       f31, 0x150(r1)
	  lfd       f30, 0x148(r1)
	  lfd       f29, 0x140(r1)
	  addi      r1, r1, 0x158
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80026B1C
 * Size:	0002F8
 */
void PVWTextureData::animate(f32*, Matrix4f&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x70(r1)
	  stfd      f31, 0x68(r1)
	  stfd      f30, 0x60(r1)
	  stw       r31, 0x5C(r1)
	  addi      r31, r5, 0
	  stw       r30, 0x58(r1)
	  mr        r30, r3
	  lbz       r0, 0x14(r3)
	  cmplwi    r0, 0xFF
	  beq-      .loc_0x2D8
	  lfs       f1, -0x7E40(r13)
	  lfs       f0, -0x7E3C(r13)
	  stfs      f1, 0x40(r1)
	  stfs      f0, 0x44(r1)
	  lfs       f0, -0x7E38(r13)
	  stfs      f0, 0x48(r1)
	  lfs       f1, -0x7E34(r13)
	  lfs       f0, -0x7E30(r13)
	  stfs      f1, 0x34(r1)
	  stfs      f0, 0x38(r1)
	  lfs       f0, -0x7E2C(r13)
	  stfs      f0, 0x3C(r1)
	  lfs       f1, -0x7E28(r13)
	  lfs       f0, -0x7E24(r13)
	  stfs      f1, 0x28(r1)
	  stfs      f0, 0x2C(r1)
	  lfs       f0, -0x7E20(r13)
	  stfs      f0, 0x30(r1)
	  lwz       r0, 0x38(r30)
	  cmplwi    r0, 0
	  bne-      .loc_0xDC
	  lbz       r0, 0x16(r30)
	  cmplwi    r0, 0
	  bne-      .loc_0x1C4
	  lfs       f0, 0x1C(r30)
	  stfs      f0, 0x40(r1)
	  lfs       f0, 0x20(r30)
	  stfs      f0, 0x44(r1)
	  lfs       f0, -0x7E1C(r13)
	  stfs      f0, 0x48(r1)
	  lfs       f1, -0x7E18(r13)
	  lfs       f0, -0x7E14(r13)
	  stfs      f1, 0x34(r1)
	  stfs      f0, 0x38(r1)
	  lfs       f0, 0x24(r30)
	  stfs      f0, 0x3C(r1)
	  lfs       f0, 0x28(r30)
	  stfs      f0, 0x28(r1)
	  lfs       f0, 0x2C(r30)
	  stfs      f0, 0x2C(r1)
	  lfs       f0, -0x7E10(r13)
	  stfs      f0, 0x30(r1)
	  b         .loc_0x1C4

	.loc_0xDC:
	  cmplwi    r4, 0
	  beq-      .loc_0x130
	  stw       r0, 0x54(r1)
	  lis       r0, 0x4330
	  lfs       f31, 0x0(r4)
	  stw       r0, 0x50(r1)
	  lfd       f1, -0x7DD0(r2)
	  fabs      f2, f31
	  lfd       f0, 0x50(r1)
	  fsubs     f30, f0, f1
	  fabs      f0, f30
	  fcmpo     cr0, f0, f2
	  ble-      .loc_0x114
	  b         .loc_0x128

	.loc_0x114:
	  fdivs     f1, f31, f30
	  bl        0x1EE7C0
	  bl        0x1EE708
	  fmuls     f0, f30, f1
	  fsubs     f31, f31, f0

	.loc_0x128:
	  stfs      f31, 0x58(r30)
	  b         .loc_0x18C

	.loc_0x130:
	  lfs       f1, -0x7DD8(r2)
	  lis       r0, 0x4330
	  lfs       f0, 0x3C(r30)
	  lwz       r3, 0x2DEC(r13)
	  fmuls     f1, f1, f0
	  lfs       f2, 0x58(r30)
	  lfs       f0, 0x28C(r3)
	  fmuls     f0, f1, f0
	  fadds     f0, f2, f0
	  stfs      f0, 0x58(r30)
	  lwz       r3, 0x38(r30)
	  lfd       f1, -0x7DD0(r2)
	  subi      r3, r3, 0x1
	  lfs       f2, 0x58(r30)
	  stw       r3, 0x54(r1)
	  stw       r0, 0x50(r1)
	  lfd       f0, 0x50(r1)
	  fsubs     f0, f0, f1
	  fcmpo     cr0, f2, f0
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x18C
	  lfs       f0, -0x7DD4(r2)
	  stfs      f0, 0x58(r30)

	.loc_0x18C:
	  lfs       f1, 0x58(r30)
	  addi      r3, r30, 0x40
	  addi      r4, r1, 0x40
	  bl        -0x548
	  lfs       f1, 0x58(r30)
	  addi      r3, r30, 0x48
	  addi      r4, r1, 0x34
	  bl        -0x558
	  lfs       f1, 0x58(r30)
	  addi      r3, r30, 0x50
	  addi      r4, r1, 0x28
	  bl        -0x568
	  li        r0, 0
	  stb       r0, 0x16(r30)

	.loc_0x1C4:
	  lbz       r0, 0x16(r30)
	  cmplwi    r0, 0
	  bne-      .loc_0x2D8
	  lfs       f2, -0x7DA0(r2)
	  lfs       f1, 0x3C(r1)
	  lfs       f0, -0x7D9C(r2)
	  fmuls     f1, f2, f1
	  fdivs     f1, f1, f0
	  bl        0x1F4FE8
	  lfs       f2, -0x7DA0(r2)
	  fmr       f31, f1
	  lfs       f1, 0x3C(r1)
	  lfs       f0, -0x7D9C(r2)
	  fmuls     f1, f2, f1
	  fdivs     f1, f1, f0
	  bl        0x1F4E38
	  lfs       f0, 0x40(r1)
	  li        r0, 0x1
	  fmuls     f0, f0, f1
	  stfs      f0, 0x0(r31)
	  lfs       f0, 0x40(r1)
	  fneg      f0, f0
	  fmuls     f0, f0, f31
	  stfs      f0, 0x4(r31)
	  lfs       f5, -0x7DD4(r2)
	  stfs      f5, 0x8(r31)
	  lfs       f0, 0x40(r1)
	  lfs       f6, 0x30(r30)
	  fneg      f3, f0
	  lfs       f2, 0x34(r30)
	  fmuls     f0, f0, f31
	  lfs       f4, 0x28(r1)
	  fmuls     f3, f3, f1
	  fmuls     f0, f2, f0
	  fmuls     f2, f6, f3
	  fadds     f0, f2, f0
	  fadds     f0, f6, f0
	  fadds     f0, f4, f0
	  stfs      f0, 0xC(r31)
	  lfs       f0, 0x44(r1)
	  fmuls     f0, f0, f31
	  stfs      f0, 0x10(r31)
	  lfs       f0, 0x44(r1)
	  fmuls     f0, f0, f1
	  stfs      f0, 0x14(r31)
	  stfs      f5, 0x18(r31)
	  lfs       f0, 0x44(r1)
	  lfs       f6, 0x34(r30)
	  fneg      f2, f0
	  lfs       f3, 0x30(r30)
	  fmuls     f0, f0, f1
	  lfs       f4, 0x2C(r1)
	  fmuls     f1, f2, f31
	  fmuls     f0, f6, f0
	  fmuls     f1, f3, f1
	  fsubs     f0, f1, f0
	  fadds     f0, f6, f0
	  fadds     f0, f4, f0
	  stfs      f0, 0x1C(r31)
	  stfs      f5, 0x20(r31)
	  stfs      f5, 0x24(r31)
	  lfs       f0, -0x7DC8(r2)
	  stfs      f0, 0x28(r31)
	  stfs      f5, 0x2C(r31)
	  stfs      f5, 0x30(r31)
	  stfs      f5, 0x34(r31)
	  stfs      f5, 0x38(r31)
	  stfs      f0, 0x3C(r31)
	  stb       r0, 0x16(r30)

	.loc_0x2D8:
	  lwz       r0, 0x74(r1)
	  lfd       f31, 0x68(r1)
	  lfd       f30, 0x60(r1)
	  lwz       r31, 0x5C(r1)
	  lwz       r30, 0x58(r1)
	  addi      r1, r1, 0x70
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80026E14
 * Size:	0005A4
 */
void PVWTextureData::read(RandomAccessStream& stream)
{
	_00 = stream.readInt();
	_0C = stream.readShort();
	_0E = stream.readShort();
	_10 = stream.readByte();
	_11 = stream.readByte();
	_12 = stream.readByte();
	_13 = stream.readByte();
	_14 = stream.readInt();
	_38 = stream.readInt();
	_3C = stream.readFloat();
	_1C = stream.readFloat();
	_20 = stream.readFloat();
	_24 = stream.readFloat();
	_28 = stream.readFloat();
	_2C = stream.readFloat();
	_30 = stream.readFloat();
	_34 = stream.readFloat();

	// _40.read(stream);
	// _48.read(stream);
	// _50.read(stream);

	// 3 function calls.. hmmm

	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x38(r1)
	  stmw      r27, 0x24(r1)
	  addi      r31, r4, 0
	  addi      r30, r3, 0
	  addi      r3, r31, 0
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x0(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x10(r12)
	  mtlr      r12
	  blrl
	  sth       r3, 0xC(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x10(r12)
	  mtlr      r12
	  blrl
	  sth       r3, 0xE(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x10(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x11(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x12(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x13(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x14(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x38(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x3C(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x1C(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x20(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x24(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x28(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x2C(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x30(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x34(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x40(r30)
	  lwz       r0, 0x40(r30)
	  cmplwi    r0, 0
	  beq-      .loc_0x2F8
	  mulli     r3, r0, 0x28
	  bl        0x20018
	  li        r29, 0
	  stw       r3, 0x44(r30)
	  mr        r27, r29
	  b         .loc_0x2EC

	.loc_0x1EC:
	  mr        r3, r31
	  lwz       r0, 0x44(r30)
	  lwz       r12, 0x4(r31)
	  add       r28, r0, r27
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x0(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x4(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x8(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0xC(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x10(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x14(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x18(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x1C(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x20(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x24(r28)
	  addi      r27, r27, 0x28
	  addi      r29, r29, 0x1

	.loc_0x2EC:
	  lwz       r0, 0x40(r30)
	  cmpw      r29, r0
	  blt+      .loc_0x1EC

	.loc_0x2F8:
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x48(r30)
	  lwz       r0, 0x48(r30)
	  cmplwi    r0, 0
	  beq-      .loc_0x440
	  mulli     r3, r0, 0x28
	  bl        0x1FED0
	  li        r29, 0
	  stw       r3, 0x4C(r30)
	  mr        r27, r29
	  b         .loc_0x434

	.loc_0x334:
	  mr        r3, r31
	  lwz       r0, 0x4C(r30)
	  lwz       r12, 0x4(r31)
	  add       r28, r0, r27
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x0(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x4(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x8(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0xC(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x10(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x14(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x18(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x1C(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x20(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x24(r28)
	  addi      r27, r27, 0x28
	  addi      r29, r29, 0x1

	.loc_0x434:
	  lwz       r0, 0x48(r30)
	  cmpw      r29, r0
	  blt+      .loc_0x334

	.loc_0x440:
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x50(r30)
	  lwz       r0, 0x50(r30)
	  cmplwi    r0, 0
	  beq-      .loc_0x588
	  mulli     r3, r0, 0x28
	  bl        0x1FD88
	  li        r29, 0
	  stw       r3, 0x54(r30)
	  mr        r27, r29
	  b         .loc_0x57C

	.loc_0x47C:
	  mr        r3, r31
	  lwz       r0, 0x54(r30)
	  lwz       r12, 0x4(r31)
	  add       r28, r0, r27
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x0(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x4(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x8(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0xC(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x10(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x14(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x18(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x1C(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x20(r28)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x24(r28)
	  addi      r27, r27, 0x28
	  addi      r29, r29, 0x1

	.loc_0x57C:
	  lwz       r0, 0x50(r30)
	  cmpw      r29, r0
	  blt+      .loc_0x47C

	.loc_0x588:
	  lbz       r0, 0x14(r30)
	  cmplwi    r0, 0xFF
	  lmw       r27, 0x24(r1)
	  lwz       r0, 0x3C(r1)
	  addi      r1, r1, 0x38
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	000094
 */
void PVWTexGenData::read(RandomAccessStream&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800273B8
 * Size:	0001E8
 */
void PVWTextureInfo::read(RandomAccessStream&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x38(r1)
	  stmw      r27, 0x24(r1)
	  addi      r31, r4, 0
	  addi      r30, r3, 0
	  addi      r3, r31, 0
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x14(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x0(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x4(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x8(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x10(r30)
	  lwz       r0, 0x10(r30)
	  cmplwi    r0, 0
	  beq-      .loc_0x130
	  rlwinm    r3,r0,2,0,29
	  bl        0x1FBAC
	  stw       r3, 0x20(r30)
	  li        r27, 0
	  li        r28, 0
	  b         .loc_0x124

	.loc_0xB4:
	  mr        r3, r31
	  lwz       r0, 0x20(r30)
	  lwz       r12, 0x4(r31)
	  add       r29, r0, r28
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x0(r29)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x1(r29)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x2(r29)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x3(r29)
	  addi      r28, r28, 0x4
	  addi      r27, r27, 0x1

	.loc_0x124:
	  lwz       r0, 0x10(r30)
	  cmplw     r27, r0
	  blt+      .loc_0xB4

	.loc_0x130:
	  li        r0, 0
	  stw       r0, 0x18(r30)
	  mr        r3, r31
	  lwz       r12, 0x4(r31)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0xC(r30)
	  lwz       r28, 0xC(r30)
	  cmplwi    r28, 0
	  beq-      .loc_0x1D4
	  mulli     r3, r28, 0x9C
	  addi      r3, r3, 0x8
	  bl        0x1FAE8
	  lis       r4, 0x8002
	  addi      r4, r4, 0x75A0
	  addi      r7, r28, 0
	  li        r5, 0
	  li        r6, 0x9C
	  bl        0x1ED6F4
	  li        r27, 0
	  stw       r3, 0x1C(r30)
	  mulli     r28, r27, 0x9C
	  b         .loc_0x1C8

	.loc_0x190:
	  lwz       r0, 0x1C(r30)
	  addi      r4, r31, 0
	  add       r3, r0, r28
	  bl        -0x740
	  lwz       r3, 0x1C(r30)
	  addi      r0, r28, 0x11
	  lbzx      r0, r3, r0
	  cmplwi    r0, 0x2
	  bne-      .loc_0x1C0
	  lwz       r3, 0x18(r30)
	  addi      r0, r3, 0x1
	  stw       r0, 0x18(r30)

	.loc_0x1C0:
	  addi      r28, r28, 0x9C
	  addi      r27, r27, 0x1

	.loc_0x1C8:
	  lwz       r0, 0xC(r30)
	  cmplw     r27, r0
	  blt+      .loc_0x190

	.loc_0x1D4:
	  lmw       r27, 0x24(r1)
	  lwz       r0, 0x3C(r1)
	  addi      r1, r1, 0x38
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800275A0
 * Size:	000018
 */
PVWTextureData::PVWTextureData()
{
	/*
	.loc_0x0:
	  lfs       f0, -0x7DD4(r2)
	  li        r0, 0
	  stfs      f0, 0x58(r3)
	  stw       r0, 0x8(r3)
	  stb       r0, 0x16(r3)
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800275B8
 * Size:	000120
 */
void PVWTevColReg::animate(f32*, ShortColour&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x48(r1)
	  stfd      f31, 0x40(r1)
	  stfd      f30, 0x38(r1)
	  stw       r31, 0x34(r1)
	  addi      r31, r5, 0
	  stw       r30, 0x30(r1)
	  mr        r30, r3
	  lwz       r0, 0x8(r3)
	  cmplwi    r0, 0
	  beq-      .loc_0x100
	  cmplwi    r4, 0
	  beq-      .loc_0x84
	  stw       r0, 0x2C(r1)
	  lis       r0, 0x4330
	  lfs       f31, 0x0(r4)
	  stw       r0, 0x28(r1)
	  lfd       f1, -0x7DD0(r2)
	  fabs      f2, f31
	  lfd       f0, 0x28(r1)
	  fsubs     f30, f0, f1
	  fabs      f0, f30
	  fcmpo     cr0, f0, f2
	  ble-      .loc_0x68
	  b         .loc_0x7C

	.loc_0x68:
	  fdivs     f1, f31, f30
	  bl        0x1EDDD0
	  bl        0x1EDD18
	  fmuls     f0, f30, f1
	  fsubs     f31, f31, f0

	.loc_0x7C:
	  stfs      f31, 0x20(r30)
	  b         .loc_0xE0

	.loc_0x84:
	  lfs       f1, -0x7DD8(r2)
	  lis       r0, 0x4330
	  lfs       f0, 0xC(r30)
	  lwz       r3, 0x2DEC(r13)
	  fmuls     f1, f1, f0
	  lfs       f2, 0x20(r30)
	  lfs       f0, 0x28C(r3)
	  fmuls     f0, f1, f0
	  fadds     f0, f2, f0
	  stfs      f0, 0x20(r30)
	  lwz       r3, 0x8(r30)
	  lfd       f1, -0x7DD0(r2)
	  subi      r3, r3, 0x1
	  lfs       f2, 0x20(r30)
	  stw       r3, 0x2C(r1)
	  stw       r0, 0x28(r1)
	  lfd       f0, 0x28(r1)
	  fsubs     f0, f0, f1
	  fcmpo     cr0, f2, f0
	  cror      2, 0x1, 0x2
	  bne-      .loc_0xE0
	  lfs       f0, -0x7DD4(r2)
	  stfs      f0, 0x20(r30)

	.loc_0xE0:
	  lfs       f1, 0x20(r30)
	  addi      r4, r31, 0
	  addi      r3, r30, 0x10
	  bl        -0x15E0
	  lfs       f1, 0x20(r30)
	  addi      r4, r31, 0
	  addi      r3, r30, 0x18
	  bl        -0x1150

	.loc_0x100:
	  lwz       r0, 0x4C(r1)
	  lfd       f31, 0x40(r1)
	  lfd       f30, 0x38(r1)
	  lwz       r31, 0x34(r1)
	  lwz       r30, 0x30(r1)
	  addi      r1, r1, 0x48
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800276D8
 * Size:	000054
 */
void Material::attach()
{
	gsys->mGfx->useDList(gsys->mGfx->compileMaterial(this));
}

/*
 * --INFO--
 * Address:	80027738
 * Size:	000238
 */
void Material::read(RandomAccessStream&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x28(r1)
	  stw       r31, 0x24(r1)
	  stw       r30, 0x20(r1)
	  addi      r30, r4, 0
	  stw       r29, 0x1C(r1)
	  addi      r29, r3, 0
	  addi      r3, r30, 0
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x18(r29)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x1C(r29)
	  addi      r3, r30, 0
	  addi      r31, r29, 0x2C
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x0(r31)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x1(r31)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x2(r31)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x3(r31)
	  lwz       r0, 0x18(r29)
	  rlwinm.   r0,r0,0,31,31
	  beq-      .loc_0x21C
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x8C(r29)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x2C(r29)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x2D(r29)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x2E(r29)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x2F(r29)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x30(r29)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x34(r29)
	  addi      r4, r30, 0
	  addi      r3, r29, 0x38
	  bl        0x1E8
	  addi      r3, r29, 0x40
	  addi      r4, r30, 0
	  bl        .loc_0x238
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x4C(r29)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x54(r29)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x58(r29)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x5C(r29)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x60(r29)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x64(r29)
	  addi      r4, r30, 0
	  addi      r3, r29, 0x68
	  bl        -0x598

	.loc_0x21C:
	  lwz       r0, 0x2C(r1)
	  lwz       r31, 0x24(r1)
	  lwz       r30, 0x20(r1)
	  lwz       r29, 0x1C(r1)
	  addi      r1, r1, 0x28
	  mtlr      r0
	  blr

	.loc_0x238:
	*/
}

/*
 * --INFO--
 * Address:	80027970
 * Size:	000120
 */
void PVWAnimInfo1<PVWKeyInfoU8>::read(RandomAccessStream&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x30(r1)
	  stmw      r27, 0x1C(r1)
	  addi      r28, r4, 0
	  addi      r27, r3, 0
	  addi      r3, r28, 0
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x0(r27)
	  lwz       r0, 0x0(r27)
	  cmplwi    r0, 0
	  beq-      .loc_0x10C
	  rlwinm    r3,r0,4,0,27
	  bl        0x1F654
	  stw       r3, 0x4(r27)
	  li        r29, 0
	  li        r30, 0
	  b         .loc_0x100

	.loc_0x54:
	  mr        r3, r28
	  lwz       r0, 0x4(r27)
	  lwz       r12, 0x4(r28)
	  add       r31, r0, r30
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x0(r31)
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x4(r31)
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x8(r31)
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0xC(r31)
	  addi      r30, r30, 0x10
	  addi      r29, r29, 0x1

	.loc_0x100:
	  lwz       r0, 0x0(r27)
	  cmplw     r29, r0
	  blt+      .loc_0x54

	.loc_0x10C:
	  lmw       r27, 0x1C(r1)
	  lwz       r0, 0x34(r1)
	  addi      r1, r1, 0x30
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80027A90
 * Size:	000228
 */
void PVWAnimInfo3<PVWKeyInfoU8>::read(RandomAccessStream&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x30(r1)
	  stmw      r27, 0x1C(r1)
	  addi      r28, r4, 0
	  addi      r27, r3, 0
	  addi      r3, r28, 0
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x0(r27)
	  lwz       r0, 0x0(r27)
	  cmplwi    r0, 0
	  beq-      .loc_0x214
	  mulli     r3, r0, 0x28
	  bl        0x1F534
	  stw       r3, 0x4(r27)
	  li        r29, 0
	  li        r30, 0
	  b         .loc_0x208

	.loc_0x54:
	  mr        r3, r28
	  lwz       r0, 0x4(r27)
	  lwz       r12, 0x4(r28)
	  add       r31, r0, r30
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x0(r31)
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x4(r31)
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x8(r31)
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0xC(r31)
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x10(r31)
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x14(r31)
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x18(r31)
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x1C(r31)
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x20(r31)
	  mr        r3, r28
	  lwz       r12, 0x4(r28)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stfs      f1, 0x24(r31)
	  addi      r30, r30, 0x28
	  addi      r29, r29, 0x1

	.loc_0x208:
	  lwz       r0, 0x0(r27)
	  cmpw      r29, r0
	  blt+      .loc_0x54

	.loc_0x214:
	  lmw       r27, 0x1C(r1)
	  lwz       r0, 0x34(r1)
	  addi      r1, r1, 0x30
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80027CB8
 * Size:	0002D0
 */
void Font::setTexture(Texture* tex, int numRows, int numCols)
{
	mTexture    = tex;
	mChars      = new FontChar[numRows * numCols];
	mCharWidth  = mTexture->mWidth / numRows;
	mCharHeight = mTexture->mHeight / numCols;

	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {
			int charIndex         = i * numRows + j;
			FontChar& currentChar = mChars[charIndex];

			// Find left boundary
			int leftEdge = 0;
			for (int k = 0; k < mCharWidth; k++) {
				int alphaCount = 0;
				for (int m = 0; m < mCharHeight - 1; m++) {
					if (!tex->getAlpha(k + (j * mCharWidth), m + (i * mCharHeight))) {
						alphaCount++;
					}
				}

				if (alphaCount != mCharHeight - 1) {
					break;
				}

				leftEdge = k;
			}

			// Find right boundary
			int rightEdge;
			for (int k = mCharWidth - 1; k >= 0; k--) {
				int alphaCount = 0;
				for (int m = 0; m < mCharHeight - 1; m++) {
					if (!tex->getAlpha(k + (j * mCharWidth), m + (i * mCharHeight))) {
						alphaCount++;
					}
				}

				if (alphaCount != mCharHeight - 1) {
					break;
				}

				rightEdge = k;
			}

			// Find baseline
			int baseline    = -1;
			int baselinePos = mCharWidth;
			for (int k = 0; k < mCharWidth; k++) {
				u8 alpha = tex->getAlpha(k + (j * mCharWidth), ((i * mCharHeight) + mCharHeight) - 1);
				if (baseline < 0) {
					if (!alpha) {
						baseline = k;
					}
				} else if (alpha) {
					baselinePos = k;
					break;
				}
			}

			// This is ridiculous, seriously? why?
			// so much indexing, this isn't even an inline function
			mChars[charIndex].mCharSpacing         = baselinePos - baseline;
			mChars[charIndex].mLeftOffset          = baseline - leftEdge;
			mChars[charIndex]._00                  = leftEdge + mCharWidth * j;
			mChars[charIndex].mWidth               = mCharWidth - leftEdge - rightEdge;
			mChars[charIndex]._02                  = i * mCharHeight;
			mChars[charIndex].mHeight              = mCharHeight - 1;
			mChars[charIndex].mTextureCoords.mMinX = (s16)mChars[charIndex]._00;
			mChars[charIndex].mTextureCoords.mMinY = (s16)mChars[charIndex]._02;
			mChars[charIndex].mTextureCoords.mMaxX = (s16)mChars[charIndex].mWidth + (s16)mChars[charIndex]._00;
			mChars[charIndex].mTextureCoords.mMaxY = (s16)mChars[charIndex]._02 + (s16)mChars[charIndex].mHeight - 1;
		}
	}
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x58(r1)
	  stmw      r19, 0x24(r1)
	  addi      r29, r4, 0
	  addi      r30, r5, 0
	  addi      r31, r6, 0
	  mullw     r19, r30, r31
	  mulli     r5, r19, 0x1C
	  addi      r28, r3, 0
	  stw       r29, 0x0(r3)
	  addi      r3, r5, 0x8
	  bl        0x1F31C
	  lis       r4, 0x8002
	  addi      r4, r4, 0x7F88
	  addi      r7, r19, 0
	  li        r5, 0
	  li        r6, 0x1C
	  bl        0x1ECF28
	  stw       r3, 0xC(r28)
	  li        r25, 0
	  li        r26, 0
	  lwz       r3, 0x0(r28)
	  lhz       r0, 0x8(r3)
	  divw      r0, r0, r30
	  stw       r0, 0x4(r28)
	  lwz       r3, 0x0(r28)
	  lhz       r0, 0xA(r3)
	  divw      r0, r0, r31
	  stw       r0, 0x8(r28)
	  b         .loc_0x2B4

	.loc_0x7C:
	  addi      r27, r26, 0
	  li        r24, 0
	  b         .loc_0x2A8

	.loc_0x88:
	  li        r23, 0
	  li        r22, 0
	  li        r21, 0
	  b         .loc_0xF0

	.loc_0x98:
	  li        r20, 0
	  li        r19, 0
	  b         .loc_0xD0

	.loc_0xA4:
	  lwz       r3, 0x4(r28)
	  mullw     r0, r25, r4
	  mullw     r4, r24, r3
	  addi      r3, r29, 0
	  add       r4, r21, r4
	  add       r5, r19, r0
	  bl        0x1C490
	  rlwinm.   r0,r3,0,24,31
	  bne-      .loc_0xCC
	  addi      r20, r20, 0x1

	.loc_0xCC:
	  addi      r19, r19, 0x1

	.loc_0xD0:
	  lwz       r4, 0x8(r28)
	  subi      r0, r4, 0x1
	  cmpw      r19, r0
	  blt+      .loc_0xA4
	  cmpw      r20, r0
	  bne-      .loc_0xFC
	  addi      r23, r21, 0
	  addi      r21, r21, 0x1

	.loc_0xF0:
	  lwz       r0, 0x4(r28)
	  cmpw      r21, r0
	  blt+      .loc_0x98

	.loc_0xFC:
	  lwz       r3, 0x4(r28)
	  subi      r19, r3, 0x1
	  b         .loc_0x164

	.loc_0x108:
	  li        r20, 0
	  li        r21, 0
	  b         .loc_0x140

	.loc_0x114:
	  lwz       r3, 0x4(r28)
	  mullw     r0, r25, r4
	  mullw     r4, r24, r3
	  addi      r3, r29, 0
	  add       r4, r19, r4
	  add       r5, r21, r0
	  bl        0x1C420
	  rlwinm.   r0,r3,0,24,31
	  bne-      .loc_0x13C
	  addi      r20, r20, 0x1

	.loc_0x13C:
	  addi      r21, r21, 0x1

	.loc_0x140:
	  lwz       r4, 0x8(r28)
	  subi      r0, r4, 0x1
	  cmpw      r21, r0
	  blt+      .loc_0x114
	  cmpw      r20, r0
	  bne-      .loc_0x16C
	  lwz       r0, 0x4(r28)
	  sub       r22, r0, r19
	  subi      r19, r19, 0x1

	.loc_0x164:
	  cmpwi     r19, 0
	  bge+      .loc_0x108

	.loc_0x16C:
	  lwz       r20, 0x4(r28)
	  li        r19, -0x1
	  li        r21, 0
	  b         .loc_0x1C8

	.loc_0x17C:
	  lwz       r3, 0x8(r28)
	  mullw     r4, r24, r0
	  mullw     r0, r25, r3
	  add       r5, r3, r0
	  addi      r3, r29, 0
	  add       r4, r21, r4
	  subi      r5, r5, 0x1
	  bl        0x1C3B4
	  cmpwi     r19, 0
	  bge-      .loc_0x1B4
	  rlwinm.   r0,r3,0,24,31
	  bne-      .loc_0x1C4
	  mr        r19, r21
	  b         .loc_0x1C4

	.loc_0x1B4:
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x1C4
	  mr        r20, r21
	  b         .loc_0x1D4

	.loc_0x1C4:
	  addi      r21, r21, 0x1

	.loc_0x1C8:
	  lwz       r0, 0x4(r28)
	  cmpw      r21, r0
	  blt+      .loc_0x17C

	.loc_0x1D4:
	  lwz       r3, 0xC(r28)
	  sub       r4, r20, r19
	  addi      r0, r27, 0x8
	  sthx      r4, r3, r0
	  sub       r6, r19, r23
	  addi      r0, r27, 0xA
	  lwz       r5, 0xC(r28)
	  addi      r4, r27, 0x4
	  addi      r3, r27, 0x2
	  sthx      r6, r5, r0
	  addi      r0, r27, 0x6
	  addi      r26, r26, 0x1C
	  lwz       r6, 0x4(r28)
	  lwz       r5, 0xC(r28)
	  mullw     r6, r24, r6
	  add       r6, r23, r6
	  sthx      r6, r5, r27
	  addi      r24, r24, 0x1
	  lwz       r6, 0x4(r28)
	  lwz       r5, 0xC(r28)
	  sub       r6, r6, r23
	  sub       r6, r6, r22
	  sthx      r6, r5, r4
	  lwz       r5, 0x8(r28)
	  lwz       r4, 0xC(r28)
	  mullw     r5, r25, r5
	  sthx      r5, r4, r3
	  lwz       r4, 0x8(r28)
	  lwz       r3, 0xC(r28)
	  subi      r4, r4, 0x1
	  sthx      r4, r3, r0
	  lwz       r0, 0xC(r28)
	  add       r3, r0, r27
	  lha       r0, 0x0(r3)
	  stw       r0, 0xC(r3)
	  lwz       r0, 0xC(r28)
	  add       r3, r0, r27
	  lha       r0, 0x2(r3)
	  stw       r0, 0x10(r3)
	  lwz       r0, 0xC(r28)
	  add       r4, r0, r27
	  lha       r3, 0x0(r4)
	  lha       r0, 0x4(r4)
	  add       r0, r3, r0
	  stw       r0, 0x14(r4)
	  lwz       r0, 0xC(r28)
	  add       r5, r0, r27
	  lha       r3, 0x6(r5)
	  addi      r27, r27, 0x1C
	  lha       r4, 0x2(r5)
	  subi      r0, r3, 0x1
	  add       r0, r4, r0
	  stw       r0, 0x18(r5)

	.loc_0x2A8:
	  cmpw      r24, r30
	  blt+      .loc_0x88
	  addi      r25, r25, 0x1

	.loc_0x2B4:
	  cmpw      r25, r31
	  blt+      .loc_0x7C
	  lmw       r19, 0x24(r1)
	  lwz       r0, 0x5C(r1)
	  addi      r1, r1, 0x58
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80027F88
 * Size:	00002C
 */
FontChar::FontChar()
{
	_00 = _02 = 0;
	mWidth    = 0;
	mHeight   = 0;
}

/*
 * --INFO--
 * Address:	80027FB4
 * Size:	00000C
 */
int Font::charToIndex(char c)
{
	return (c & 0xFF) - 0x20;
}

/*
 * --INFO--
 * Address:	80027FC0
 * Size:	000098
 */
void searchKanjiCode(u16)
{
	/*
	.loc_0x0:
	  mflr      r0
	  lis       r4, 0x8022
	  stw       r0, 0x4(r1)
	  rlwinm    r0,r3,0,16,31
	  stwu      r1, -0x28(r1)
	  stw       r31, 0x24(r1)
	  rlwinm    r31,r3,24,24,31
	  stw       r30, 0x20(r1)
	  rlwinm    r30,r0,0,24,31
	  stw       r29, 0x1C(r1)
	  addi      r29, r4, 0x7A40
	  addi      r3, r29, 0
	  bl        0x1F141C
	  rlwinm    r0,r3,31,1,31
	  extsh     r4, r0
	  li        r3, -0x1
	  li        r5, 0
	  b         .loc_0x70

	.loc_0x48:
	  lbz       r0, 0x0(r29)
	  cmplw     r31, r0
	  bne-      .loc_0x68
	  lbz       r0, 0x1(r29)
	  cmplw     r30, r0
	  bne-      .loc_0x68
	  mr        r3, r5
	  b         .loc_0x7C

	.loc_0x68:
	  addi      r29, r29, 0x2
	  addi      r5, r5, 0x1

	.loc_0x70:
	  extsh     r0, r5
	  cmpw      r0, r4
	  blt+      .loc_0x48

	.loc_0x7C:
	  lwz       r0, 0x2C(r1)
	  lwz       r31, 0x24(r1)
	  lwz       r30, 0x20(r1)
	  lwz       r29, 0x1C(r1)
	  addi      r1, r1, 0x28
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80028058
 * Size:	0000DC
 */
void Font::charToIndex(u16 c)
{
	/*
	.loc_0x0:
	  mflr      r0
	  lis       r3, 0x8022
	  stw       r0, 0x4(r1)
	  rlwinm    r0,r4,0,16,31
	  cmplwi    r0, 0x8140
	  stwu      r1, -0x30(r1)
	  stw       r31, 0x2C(r1)
	  addi      r31, r3, 0x7540
	  stw       r30, 0x28(r1)
	  stw       r29, 0x24(r1)
	  blt-      .loc_0x48
	  cmplwi    r0, 0x8396
	  bgt-      .loc_0x48
	  subis     r3, r31, 0x1
	  rlwinm    r0,r0,1,0,30
	  add       r3, r3, r0
	  lhz       r3, -0x24C(r3)
	  b         .loc_0xC0

	.loc_0x48:
	  rlwinm    r30,r4,24,24,31
	  rlwinm    r29,r4,0,24,31
	  addi      r3, r31, 0x500
	  bl        0x1F1360
	  rlwinm    r0,r3,31,1,31
	  extsh     r5, r0
	  addi      r6, r31, 0x500
	  li        r4, -0x1
	  li        r3, 0
	  b         .loc_0x98

	.loc_0x70:
	  lbz       r0, 0x0(r6)
	  cmplw     r30, r0
	  bne-      .loc_0x90
	  lbz       r0, 0x1(r6)
	  cmplw     r29, r0
	  bne-      .loc_0x90
	  mr        r4, r3
	  b         .loc_0xA4

	.loc_0x90:
	  addi      r6, r6, 0x2
	  addi      r3, r3, 0x1

	.loc_0x98:
	  extsh     r0, r3
	  cmpw      r0, r5
	  blt+      .loc_0x70

	.loc_0xA4:
	  extsh     r0, r4
	  extsh     r3, r0
	  cmpwi     r3, -0x1
	  beq-      .loc_0xBC
	  addi      r3, r3, 0x126
	  b         .loc_0xC0

	.loc_0xBC:
	  li        r3, 0x5F

	.loc_0xC0:
	  lwz       r0, 0x34(r1)
	  lwz       r31, 0x2C(r1)
	  lwz       r30, 0x28(r1)
	  lwz       r29, 0x24(r1)
	  addi      r1, r1, 0x30
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80028134
 * Size:	0000E0
 */
int Font::stringWidth(char*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  lis       r5, 0x8022
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x30(r1)
	  stw       r31, 0x2C(r1)
	  li        r31, 0
	  stw       r30, 0x28(r1)
	  addi      r30, r4, 0
	  stw       r29, 0x24(r1)
	  addi      r29, r3, 0
	  stw       r28, 0x20(r1)
	  addi      r28, r5, 0x7574
	  b         .loc_0xB0

	.loc_0x34:
	  rlwinm.   r0,r3,0,24,24
	  beq-      .loc_0x94
	  lbz       r0, 0x1(r30)
	  rlwimi    r0,r3,8,0,23
	  rlwinm    r3,r0,0,16,31
	  cmplwi    r3, 0x8140
	  blt-      .loc_0x6C
	  cmplwi    r3, 0x8396
	  bgt-      .loc_0x6C
	  rlwinm    r0,r3,1,0,30
	  add       r3, r28, r0
	  subis     r3, r3, 0x1
	  lhz       r0, -0x280(r3)
	  b         .loc_0x8C

	.loc_0x6C:
	  bl        -0x1E0
	  extsh     r0, r3
	  extsh     r3, r0
	  cmpwi     r3, -0x1
	  beq-      .loc_0x88
	  addi      r0, r3, 0x126
	  b         .loc_0x8C

	.loc_0x88:
	  li        r0, 0x5F

	.loc_0x8C:
	  addi      r30, r30, 0x2
	  b         .loc_0x9C

	.loc_0x94:
	  subi      r0, r3, 0x20
	  addi      r30, r30, 0x1

	.loc_0x9C:
	  mulli     r3, r0, 0x1C
	  lwz       r4, 0xC(r29)
	  addi      r0, r3, 0x8
	  lhax      r0, r4, r0
	  add       r31, r31, r0

	.loc_0xB0:
	  lbz       r3, 0x0(r30)
	  cmplwi    r3, 0
	  bne+      .loc_0x34
	  addi      r3, r31, 0x1
	  lwz       r0, 0x34(r1)
	  lwz       r31, 0x2C(r1)
	  lwz       r30, 0x28(r1)
	  lwz       r29, 0x24(r1)
	  lwz       r28, 0x20(r1)
	  addi      r1, r1, 0x30
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	0003A0
 */
void GfxInfo::createCollData(Vector3f*, f32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80028214
 * Size:	000058
 */
CollTriInfo::CollTriInfo()
{
	/*
	.loc_0x0:
	  mflr      r0
	  li        r5, 0
	  stw       r0, 0x4(r1)
	  li        r6, 0x10
	  li        r7, 0x3
	  stwu      r1, -0x18(r1)
	  stw       r31, 0x14(r1)
	  addi      r31, r3, 0
	  lis       r3, 0x8003
	  lfs       f0, -0x7DD4(r2)
	  subi      r4, r3, 0x7D94
	  addi      r3, r31, 0x28
	  stfs      f0, 0x20(r31)
	  stfs      f0, 0x1C(r31)
	  stfs      f0, 0x18(r31)
	  bl        0x1EC820
	  mr        r3, r31
	  lwz       r0, 0x1C(r1)
	  lwz       r31, 0x14(r1)
	  addi      r1, r1, 0x18
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80028280
 * Size:	000034
 */
void MaterialHandler::setMaterial(Material*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  li        r5, 0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x8(r1)
	  lwz       r3, 0x0(r3)
	  lwz       r12, 0x3B4(r3)
	  lwz       r12, 0xC4(r12)
	  mtlr      r12
	  blrl
	  lwz       r0, 0xC(r1)
	  addi      r1, r1, 0x8
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800282B4
 * Size:	000030
 */
void MaterialHandler::setTexMatrix(bool)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x8(r1)
	  lwz       r3, 0x0(r3)
	  lwz       r12, 0x3B4(r3)
	  lwz       r12, 0xE8(r12)
	  mtlr      r12
	  blrl
	  lwz       r0, 0xC(r1)
	  addi      r1, r1, 0x8
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800282E4
 * Size:	0001C8
 */
Graphics::Graphics()
{
	PRINT("dgxgraphics constructor\n");

	_00 = 0;

	for (int i = 0; i < 0x1000; i++) {
		sintable[i] = NMathF::sin(i / 4096.0f * TAU);
		costable[i] = NMathF::cos(i / 4096.0f * TAU);
	}

	mActiveTexture[0] = nullptr;
	mActiveTexture[1] = nullptr;
	mActiveTexture[2] = nullptr;
	mActiveTexture[3] = nullptr;
	mActiveTexture[4] = nullptr;
	mActiveTexture[5] = nullptr;
	mActiveTexture[6] = nullptr;
	mActiveTexture[7] = nullptr;

	_308 = 0;

	mCurrentMaterial = nullptr;
	mLightCam        = nullptr;

	Matrix4f::ident.makeIdentity();

	mCurrentMaterialHandler = nullptr;
	_34C                    = new MaterialHandler();

	mMaxMatrixCount = gsys->mMatrixCount;
	mSystemMatrices = gsys->mMatrices;

	mCachedShapeMax = 1000;
	mCachedShapes   = new CachedShape[mCachedShapeMax];

	mAmbientFogColour.set(0, 0, 0x30, 0xFF);
	mLightIntensity = 1.0f;
}

/*
//  * --INFO--
//  * Address:	800284AC
//  * Size:	00000C
//  */
// CachedShape::CachedShape()
// {
// 	/*
// 	.loc_0x0:
// 	  stw       r3, 0x4(r3)
// 	  stw       r3, 0x0(r3)
// 	  blr
// 	*/
// }

/*
 * --INFO--
 * Address:	800284B8
 * Size:	000050
 */
void Graphics::initRender(int, int)
{
	mActiveLightMask = 0;
	mLight.initCore("");
	resetMatrixBuffer();
	resetCacheBuffer();
}

/*
 * --INFO--
 * Address:	80028508
 * Size:	00000C
 */
void Graphics::resetMatrixBuffer()
{
	mActiveMatrixIdx = nullptr;
}

/*
 * --INFO--
 * Address:	80028514
 * Size:	00001C
 */
Matrix4f* Graphics::getMatrices(int requestedMatrixCount)
{
	if (mActiveMatrixIdx + requestedMatrixCount > mMaxMatrixCount) {
		ERROR("using too many matrices!!\n");
	}

	Matrix4f* mtx = &mSystemMatrices[mActiveMatrixIdx];
	mActiveMatrixIdx += requestedMatrixCount;
	return mtx;
}

/*
 * --INFO--
 * Address:	80028530
 * Size:	000018
 */
void Graphics::resetCacheBuffer()
{
	_390.mNext = &_390;
	_390.mPrev = &_390;

	mCachedShapeCount = nullptr;
}

/*
 * --INFO--
 * Address:	80028548
 * Size:	000184
 */
void Graphics::cacheShape(BaseShape* shape, ShapeDynMaterials* mats)
{
	if (mCachedShapeCount >= mCachedShapeMax) {
		ERROR("using too many shapes!!\n");
	}

	CachedShape* cache = &mCachedShapes[mCachedShapeCount];
	Vector3f pos(shape->getAnimMatrix(0).mMtx[0][3], shape->getAnimMatrix(0).mMtx[1][3], shape->getAnimMatrix(0).mMtx[2][3]);
	cache->mDistanceFromOrigin = pos.length();

	bool far = false;
	for (CachedShape* i = _390.mPrev; i != &_390; i = i->mPrev) {
		if (cache->mDistanceFromOrigin >= i->mDistanceFromOrigin) {
			i->insertAfter(cache);
			far = true;
			break;
		}
	}

	if (!far) {
		_390.insertAfter(cache);
	}

	cache->mDynMaterials = mats;
	cache->mParentShape  = (Shape*)shape;
	cache->mAnimMatrices = shape->mAnimMatrices;
	mCachedShapeCount++;
}

/*
 * --INFO--
 * Address:	800286CC
 * Size:	0000A0
 */
void Graphics::flushCachedShapes()
{
	u32 oldRenderState = mRenderState;

	mRenderState = 1024;
	for (CachedShape* i = _390.mPrev; i != &_390; i = i->mPrev) {
		if (i->mDynMaterials) {
			for (ShapeDynMaterials* j = i->mDynMaterials; j; j = j->mParent) {
				j->updateContext();
			}
		}

		i->mParentShape->mAnimMatrices = i->mAnimMatrices;
		drawMeshes(*mCamera, i->mParentShape);
	}
	mRenderState = oldRenderState;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000018
 */
void TexImg::convFormat(u32)
{
	// UNUSED FUNCTION
}

char* fmtNames[]
    = { "TEX_FMT_RGB565", "TEX_FMT_S3TC", "TEX_FMT_RGB5A3", "TEX_FMT_I4", "TEX_FMT_I8", "TEX_FMT_IA4", "TEX_FMT_IA8", "TEX_FMT_RGBA8" };

/*
 * --INFO--
 * Address:	........
 * Size:	000018
 */
char* TexImg::formatName(u32 format)
{
	return fmtNames[format];
}

/*
 * --INFO--
 * Address:	8002876C
 * Size:	00009C
 */
int TexImg::calcDataSize(int format, int width, int height)
{
	s32 size = 0;

	switch (format) {
	case 1:
		size = (width * height / 8) * 4;
		break;
	case 0:
		size = width * height * 2;
		break;
	case 2:
		size = width * height * 2;
		break;
	case 3:
		size = width * height / 2;
		break;
	case 4:
		size = width * height;
		break;
	case 5:
		size = width * height;
		break;
	case 6:
		size = width * height * 2;
		break;
	case 7:
		size = width * height * 4;
		break;
	case 8:
		size = width * height;
		break;
	case 9:
		size = width * height;
		break;
	}

	return size;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00005C
 */
void TexImg::setColour(Colour&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80028808
 * Size:	000130
 */
void TexImg::read(RandomAccessStream& stream)
{
	mWidth  = stream.readShort();
	mHeight = stream.readShort();
	mFormat = static_cast<TexImgFormat>(stream.readInt());
	_24     = stream.readInt();

	s32 _ = stream.readInt();
	_     = stream.readInt();
	_     = stream.readInt();
	_     = stream.readInt();

	mDataSize    = stream.readInt();
	mTextureData = new (0x20) u8[mDataSize];
	stream.read(mTextureData, mDataSize);
}

/*
 * --INFO--
 * Address:	80028938
 * Size:	000058
 */
void TexImg::getTileSize(int format, u32& xSize, u32& ySize)
{
	switch (format) {
	case 3:
		xSize = 8;
		ySize = 8;
		break;
	case 4:
	case 5:
	case 9:
		xSize = 8;
		ySize = 4;
		break;
	default:
		xSize = 4;
		ySize = 4;
		break;
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	00014C
 */
void TexImg::readTexData(Texture* tex, RandomAccessStream& stream, u8* data)
{
	mDataSize = TexImg::calcDataSize(mFormat, mWidth, mHeight);

	if (data) {
		mTextureData = data;
	} else {
		mTextureData = new (0x20) u8[mDataSize];
	}

	stream.read(mTextureData, mDataSize);
	TexImg::getTileSize(mFormat, tex->mTileSizeX, tex->mTileSizeY);
	tex->mWidthFactor  = 1.0f / mWidth;
	tex->mHeightFactor = 1.0f / mHeight;
	tex->decodeData(this);
}

char* btitexFmts[] = { "GX_TF_I4", "GX_TF_I8", "GX_TF_IA4", "GX_TF_IA8", "GX_TF_RGB565", "GX_TF_RGB5A3", "GX_TF_RGBA8", "INVALID",
	                   "INVALID",  "INVALID",  "INVALID",   "INVALID",   "INVALID",      "INVALID",      "GX_TF_CMPR" };

char* btipalFmts[] = { "GX_TF_C4", "GX_TF_C8", "GX_TF_C14X2" };

/*
 * --INFO--
 * Address:	........
 * Size:	000004
 */
void TexImg::dumpBti(Texture* tex, char* name, RandomAccessStream& input, RandomAccessStream& output)
{
#ifndef __MWERKS__
	// read BTI function
	// blah blah

	// if some bollocks
	// now lets get to the fun parts

	// this is wrong btw, I can't be bothered to check if this shows up
	// but im doing it anyway, **** it
	output.print("// %s (%d colour) format %s : data = %d bytes\n", output.mPath, 0, btipalFmts[tex->mTexFormat]);
	output.print("// texture size = %d x %d\n");
	output.print("static u16 %s_palette[%d] ATTRIBUTE_ALIGN(32) = {\n");
	output.print("\t");
	PRINT("sending colour %d, %d, %d\n");
	output.print("0x%04x,");
	output.print("\n");
	output.print("\t};\n\n");

	// so much code i skipped over lol
	output.print("// %s got normal image of format %s : data = %d bytes\n");
	output.print("// texture size = %d x %d\n");

	output.print("static u8 %s_data[%d] ATTRIBUTE_ALIGN(32) = {\n");
	output.print("\t");
	output.print("0x%02x,");
	output.print("\n");
	output.print("\t};\n\n");

#endif
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80028990
 * Size:	0003EC
 */
void TexImg::importBti(Texture*, RandomAccessStream&, u8*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x68(r1)
	  stw       r31, 0x64(r1)
	  addi      r31, r6, 0
	  stw       r30, 0x60(r1)
	  addi      r30, r5, 0
	  stw       r29, 0x5C(r1)
	  addi      r29, r4, 0
	  stw       r28, 0x58(r1)
	  addi      r28, r3, 0
	  addi      r3, r30, 0
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x28(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x29(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x10(r12)
	  mtlr      r12
	  blrl
	  sth       r3, 0x2A(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x10(r12)
	  mtlr      r12
	  blrl
	  sth       r3, 0x2C(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x2E(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x2F(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x30(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x31(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x10(r12)
	  mtlr      r12
	  blrl
	  sth       r3, 0x32(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x34(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x38(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x39(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x3A(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x3B(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x3C(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x3D(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x3E(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x3F(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x40(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  stb       r3, 0x41(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x10(r12)
	  mtlr      r12
	  blrl
	  sth       r3, 0x42(r1)
	  mr        r3, r30
	  lwz       r12, 0x4(r30)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x44(r1)
	  lis       r3, 0x8022
	  addi      r0, r3, 0x7EDC
	  lbz       r3, 0x28(r1)
	  rlwinm    r3,r3,2,0,29
	  add       r3, r0, r3
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x18(r28)
	  lhz       r0, 0x2A(r1)
	  stw       r0, 0x1C(r28)
	  lhz       r0, 0x2C(r1)
	  stw       r0, 0x20(r28)
	  lwz       r0, 0x18(r28)
	  cmpwi     r0, 0x6
	  bge-      .loc_0x284
	  cmpwi     r0, 0x3
	  beq-      .loc_0x290
	  bge-      .loc_0x29C
	  b         .loc_0x2A8

	.loc_0x284:
	  cmpwi     r0, 0x9
	  beq-      .loc_0x29C
	  b         .loc_0x2A8

	.loc_0x290:
	  li        r4, 0x8
	  li        r5, 0x8
	  b         .loc_0x2B0

	.loc_0x29C:
	  li        r4, 0x8
	  li        r5, 0x4
	  b         .loc_0x2B0

	.loc_0x2A8:
	  li        r4, 0x4
	  li        r5, 0x4

	.loc_0x2B0:
	  lwz       r3, 0x1C(r28)
	  divwu     r0, r3, r4
	  mullw     r0, r0, r4
	  sub.      r0, r3, r0
	  bne-      .loc_0x2D4
	  lwz       r3, 0x20(r28)
	  divwu     r0, r3, r5
	  mullw     r0, r0, r5
	  sub.      r0, r3, r0

	.loc_0x2D4:
	  lwz       r0, 0x44(r1)
	  cmplwi    r0, 0x20
	  lbz       r0, 0x2F(r1)
	  cmplwi    r0, 0
	  bne-      .loc_0x2F0
	  li        r3, 0x100
	  b         .loc_0x2F4

	.loc_0x2F0:
	  li        r3, 0

	.loc_0x2F4:
	  lbz       r0, 0x2E(r1)
	  cmplwi    r0, 0
	  bne-      .loc_0x308
	  li        r0, 0x1
	  b         .loc_0x30C

	.loc_0x308:
	  li        r0, 0

	.loc_0x30C:
	  or        r0, r0, r3
	  sth       r0, 0x6(r29)
	  lwz       r3, 0x18(r28)
	  lwz       r4, 0x1C(r28)
	  lwz       r5, 0x20(r28)
	  bl        -0x544
	  cmplwi    r31, 0
	  stw       r3, 0x28(r28)
	  bne-      .loc_0x344
	  lwz       r3, 0x28(r28)
	  li        r4, 0x20
	  bl        0x1E4A0
	  stw       r3, 0x2C(r28)
	  b         .loc_0x348

	.loc_0x344:
	  stw       r31, 0x2C(r28)

	.loc_0x348:
	  mr        r3, r30
	  lwz       r4, 0x2C(r28)
	  lwz       r12, 0x4(r30)
	  lwz       r5, 0x28(r28)
	  lwz       r12, 0x3C(r12)
	  mtlr      r12
	  blrl
	  lwz       r3, 0x18(r28)
	  addi      r4, r29, 0xC
	  addi      r5, r29, 0x10
	  bl        -0x3C8
	  lwz       r0, 0x1C(r28)
	  lis       r5, 0x4330
	  lfd       f1, -0x7DA8(r2)
	  addi      r3, r29, 0
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x54(r1)
	  mr        r4, r28
	  lfs       f2, -0x7DC8(r2)
	  stw       r5, 0x50(r1)
	  lfd       f0, 0x50(r1)
	  fsubs     f0, f0, f1
	  fdivs     f0, f2, f0
	  stfs      f0, 0x28(r29)
	  lwz       r0, 0x20(r28)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x4C(r1)
	  stw       r5, 0x48(r1)
	  lfd       f0, 0x48(r1)
	  fsubs     f0, f0, f1
	  fdivs     f0, f2, f0
	  stfs      f0, 0x2C(r29)
	  bl        0x1BA00
	  lwz       r0, 0x6C(r1)
	  lwz       r31, 0x64(r1)
	  lwz       r30, 0x60(r1)
	  lwz       r29, 0x5C(r1)
	  lwz       r28, 0x58(r1)
	  addi      r1, r1, 0x68
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80028D7C
 * Size:	0001A8
 */
void TexImg::importTxe(Texture* tex, RandomAccessStream& stream)
{
	mWidth         = stream.readShort();
	mHeight        = stream.readShort();
	mFormat        = static_cast<TexImgFormat>((u16)stream.readShort());
	tex->mTexFlags = mFormat >> 8;

	mFormat = static_cast<TexImgFormat>(mFormat & 0xFF);

	s16 _  = stream.readShort();
	s32 __ = stream.readInt();
	for (int i = 0; i < 10; i++) {
		stream.readShort();
	}

	readTexData(tex, stream, nullptr);
}

/*
 * --INFO--
 * Address:	80028F24
 * Size:	0001E4
 */
void TexAttr::initImage()
{
	mTexture = new Texture();

	if (!mTexture) {
		ERROR("could not make texture!!\n");
	}

	TexImg::getTileSize(mImage->mFormat, mTexture->mTileSizeX, mTexture->mTileSizeY);

	if (_20) {
		mTexture->mTexObj      = (GXTexObj*)(mImage->_24 - 1);
		mTexture->mWidthFactor = _24;
	} else {
		mTexture->mTexObj      = nullptr;
		mTexture->mWidthFactor = 0.0f;
	}

	mTexture->mWidthFactor  = 1.0f / mImage->mWidth;
	mTexture->mHeightFactor = 1.0f / mImage->mHeight;

	mTexture->mTexFlags = mTilingType;

	// ISSUES HERE, obviously lol
	// Find last occurrence of '/' in the path
	int i = strlen(&gsys->mTextureBase2[1]) - 1;
	while (i >= 0 && (&gsys->mTextureBase2[1])[i] != '/') {
		i--;
	}

	char path[PATH_MAX];
	sprintf(path, "%s:%d", &gsys->mTextureBase2[i + 1], mTextureIndex);

	gsys->addTexture(mTexture, path);
	mTexture->decodeData(mImage);
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x128(r1)
	  stw       r31, 0x124(r1)
	  addi      r31, r3, 0
	  li        r3, 0x3C
	  stw       r30, 0x120(r1)
	  bl        0x1E0C4
	  addi      r30, r3, 0
	  mr.       r3, r30
	  beq-      .loc_0x30
	  bl        0x1B244

	.loc_0x30:
	  stw       r30, 0x2C(r31)
	  lwz       r3, 0x30(r31)
	  lwz       r5, 0x2C(r31)
	  lwz       r0, 0x18(r3)
	  addi      r4, r5, 0x10
	  cmpwi     r0, 0x6
	  addi      r3, r5, 0xC
	  bge-      .loc_0x60
	  cmpwi     r0, 0x3
	  beq-      .loc_0x6C
	  bge-      .loc_0x7C
	  b         .loc_0x90

	.loc_0x60:
	  cmpwi     r0, 0x9
	  beq-      .loc_0x7C
	  b         .loc_0x90

	.loc_0x6C:
	  li        r0, 0x8
	  stw       r0, 0x0(r3)
	  stw       r0, 0x0(r4)
	  b         .loc_0x9C

	.loc_0x7C:
	  li        r0, 0x8
	  stw       r0, 0x0(r3)
	  li        r0, 0x4
	  stw       r0, 0x0(r4)
	  b         .loc_0x9C

	.loc_0x90:
	  li        r0, 0x4
	  stw       r0, 0x0(r3)
	  stw       r0, 0x0(r4)

	.loc_0x9C:
	  lhz       r0, 0x20(r31)
	  cmplwi    r0, 0
	  beq-      .loc_0xCC
	  lwz       r4, 0x30(r31)
	  lwz       r3, 0x2C(r31)
	  lwz       r4, 0x24(r4)
	  subi      r0, r4, 0x1
	  stw       r0, 0x18(r3)
	  lfs       f0, 0x24(r31)
	  lwz       r3, 0x2C(r31)
	  stfs      f0, 0x1C(r3)
	  b         .loc_0xE4

	.loc_0xCC:
	  lwz       r3, 0x2C(r31)
	  li        r0, 0
	  stw       r0, 0x18(r3)
	  lfs       f0, -0x7DD4(r2)
	  lwz       r3, 0x2C(r31)
	  stfs      f0, 0x1C(r3)

	.loc_0xE4:
	  lwz       r3, 0x30(r31)
	  lis       r5, 0x4330
	  lfd       f1, -0x7DA8(r2)
	  lwz       r0, 0x1C(r3)
	  lfs       f2, -0x7DC8(r2)
	  xoris     r0, r0, 0x8000
	  lwz       r3, 0x2C(r31)
	  stw       r0, 0x11C(r1)
	  stw       r5, 0x118(r1)
	  lfd       f0, 0x118(r1)
	  fsubs     f0, f0, f1
	  fdivs     f0, f2, f0
	  stfs      f0, 0x28(r3)
	  lwz       r4, 0x30(r31)
	  lwz       r3, 0x2C(r31)
	  lwz       r0, 0x20(r4)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x114(r1)
	  stw       r5, 0x110(r1)
	  lfd       f0, 0x110(r1)
	  fsubs     f0, f0, f1
	  fdivs     f0, f2, f0
	  stfs      f0, 0x2C(r3)
	  lhz       r0, 0x1C(r31)
	  lwz       r3, 0x2C(r31)
	  sth       r0, 0x6(r3)
	  lwz       r3, 0x2DEC(r13)
	  lwz       r3, 0x1FC(r3)
	  lwz       r3, 0x4(r3)
	  bl        0x1F0390
	  subic.    r5, r3, 0x1
	  lwz       r4, 0x2DEC(r13)
	  addi      r0, r5, 0x1
	  mtctr     r0
	  blt-      .loc_0x18C

	.loc_0x170:
	  lwz       r3, 0x1FC(r4)
	  lwz       r3, 0x4(r3)
	  lbzx      r0, r3, r5
	  cmplwi    r0, 0x2F
	  beq-      .loc_0x18C
	  subi      r5, r5, 0x1
	  bdnz+     .loc_0x170

	.loc_0x18C:
	  lwz       r4, 0x1FC(r4)
	  addi      r3, r1, 0x10
	  lwz       r6, 0x18(r31)
	  crclr     6, 0x6
	  lwz       r0, 0x4(r4)
	  subi      r4, r13, 0x7DF0
	  add       r5, r5, r0
	  addi      r5, r5, 0x1
	  bl        0x1ED4C8
	  lwz       r3, 0x2DEC(r13)
	  addi      r5, r1, 0x10
	  lwz       r4, 0x2C(r31)
	  bl        0x16718
	  lwz       r3, 0x2C(r31)
	  lwz       r4, 0x30(r31)
	  bl        0x1B66C
	  lwz       r0, 0x12C(r1)
	  lwz       r31, 0x124(r1)
	  lwz       r30, 0x120(r1)
	  addi      r1, r1, 0x128
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80029108
 * Size:	0000AC
 */
void TexAttr::read(RandomAccessStream& stream)
{
	mTextureIndex = stream.readShort();
	stream.readShort();
	mTilingType = stream.readShort();
	_20         = stream.readShort();
	_24         = stream.readFloat();
}

/*
 * --INFO--
 * Address:	800291B4
 * Size:	0002BC
 */
void Graphics::drawCylinder(Vector3f& a1, Vector3f& a2, f32 a3, Matrix4f& a4)
{
	useTexture(nullptr, 0);

	Vector3f v0  = a1;
	Vector3f v1  = a2 - a1;
	f32 distance = v1.normalise();

	// some bollocks with multiplication here

	for (int i = 0; i < 16; i++) {
		Matrix4f a, b;

		Vector3f v2(0.0f, i * (PI / 8), 0.0f);
		Vector3f v3(1.0f, 1.0f, 1.0f);

		a.makeSRT(v3, v2, v0);
		a4.multiplyTo(a, b);
		useMatrix(b, 0);

		for (int j = 0; j < 16; j++) {
			// Calculate angles for current and next point
			f32 currentAngle = i * PI / 8.0f;
			f32 nextAngle    = ((i + 1) % 32) * PI / 8.0f;

			// Calculate points
			Vector3f start(NMathF::sin(currentAngle) * a3, 0.0f, NMathF::cos(currentAngle) * a3);
			Vector3f end(NMathF::sin(nextAngle) * a3, 0.0f, NMathF::cos(nextAngle) * a3);

			drawLine(start, end);
		}

		// more bollocks with multiplication here
	}
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x1B0(r1)
	  stfd      f31, 0x1A8(r1)
	  stfd      f30, 0x1A0(r1)
	  stfd      f29, 0x198(r1)
	  stfd      f28, 0x190(r1)
	  stfd      f27, 0x188(r1)
	  stfd      f26, 0x180(r1)
	  fmr       f26, f1
	  stfd      f25, 0x178(r1)
	  stfd      f24, 0x170(r1)
	  stfd      f23, 0x168(r1)
	  stmw      r23, 0x144(r1)
	  mr        r23, r3
	  addi      r26, r4, 0
	  addi      r25, r5, 0
	  addi      r24, r6, 0
	  li        r4, 0
	  li        r5, 0
	  lwz       r12, 0x3B4(r23)
	  lwz       r12, 0xCC(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0x0(r26)
	  stfs      f0, 0x124(r1)
	  lfs       f0, 0x4(r26)
	  stfs      f0, 0x128(r1)
	  lfs       f0, 0x8(r26)
	  stfs      f0, 0x12C(r1)
	  lfs       f3, 0x0(r25)
	  lfs       f2, 0x0(r26)
	  lfs       f1, 0x4(r25)
	  lfs       f0, 0x4(r26)
	  fsubs     f25, f3, f2
	  lfs       f2, 0x8(r25)
	  fsubs     f27, f1, f0
	  lfs       f0, 0x8(r26)
	  fmuls     f1, f25, f25
	  fsubs     f28, f2, f0
	  fmuls     f0, f27, f27
	  fmuls     f2, f28, f28
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0x1B624
	  lfs       f0, -0x7DD4(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0xCC
	  fdivs     f25, f25, f1
	  fdivs     f27, f27, f1
	  fdivs     f28, f28, f1

	.loc_0xCC:
	  lfs       f0, -0x7D80(r2)
	  addi      r28, r1, 0x50
	  lfs       f30, -0x7D7C(r2)
	  addi      r27, r1, 0x60
	  fmuls     f0, f1, f0
	  lfd       f31, -0x7DA8(r2)
	  addi      r30, r1, 0x70
	  addi      r29, r1, 0x7C
	  fmuls     f29, f28, f0
	  fmuls     f28, f27, f0
	  li        r26, 0
	  fmuls     f27, f25, f0
	  lis       r31, 0x4330

	.loc_0x100:
	  xoris     r0, r26, 0x8000
	  lfs       f4, -0x7DDC(r13)
	  stw       r0, 0x13C(r1)
	  mr        r4, r29
	  lfs       f0, -0x7DE8(r13)
	  mr        r5, r30
	  stw       r31, 0x138(r1)
	  lfs       f1, -0x7DE4(r13)
	  addi      r3, r1, 0xD4
	  lfd       f2, 0x138(r1)
	  addi      r6, r1, 0x124
	  stfs      f0, 0x7C(r1)
	  fsubs     f3, f2, f31
	  lfs       f2, -0x7DD8(r13)
	  stfs      f4, 0x70(r1)
	  lfs       f0, -0x7DE0(r13)
	  fmuls     f3, f30, f3
	  stfs      f1, 0x80(r1)
	  stfs      f3, 0x74(r1)
	  stfs      f2, 0x78(r1)
	  stfs      f0, 0x84(r1)
	  bl        0x14DEC
	  addi      r3, r24, 0
	  addi      r4, r1, 0xD4
	  addi      r5, r1, 0x94
	  bl        0x14DBC
	  mr        r3, r23
	  lwz       r12, 0x3B4(r23)
	  addi      r4, r1, 0x94
	  li        r5, 0
	  lwz       r12, 0x74(r12)
	  mtlr      r12
	  blrl
	  li        r25, 0

	.loc_0x188:
	  addi      r3, r25, 0x1
	  srawi     r0, r3, 0x5
	  addze     r0, r0
	  rlwinm    r0,r0,5,0,26
	  subc      r0, r3, r0
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x134(r1)
	  xoris     r0, r25, 0x8000
	  stw       r31, 0x130(r1)
	  stw       r0, 0x13C(r1)
	  lfd       f0, 0x130(r1)
	  stw       r31, 0x138(r1)
	  fsubs     f0, f0, f31
	  lfd       f1, 0x138(r1)
	  fsubs     f1, f1, f31
	  fmuls     f23, f30, f0
	  fmuls     f24, f30, f1
	  fmr       f1, f23
	  bl        0x1F27D0
	  fmuls     f25, f26, f1
	  fmr       f1, f23
	  bl        0x1F2958
	  fmuls     f2, f26, f1
	  lfs       f0, -0x7DD0(r13)
	  fmr       f1, f24
	  stfs      f2, 0x4C(r1)
	  lfs       f2, 0x4C(r1)
	  stfs      f2, 0x50(r1)
	  stfs      f0, 0x54(r1)
	  stfs      f25, 0x58(r1)
	  bl        0x1F27A0
	  fmuls     f25, f26, f1
	  fmr       f1, f24
	  bl        0x1F2928
	  fmuls     f1, f26, f1
	  lfs       f0, -0x7DD4(r13)
	  addi      r3, r23, 0
	  addi      r4, r27, 0
	  stfs      f1, 0x5C(r1)
	  mr        r5, r28
	  lfs       f1, 0x5C(r1)
	  stfs      f1, 0x60(r1)
	  stfs      f0, 0x64(r1)
	  stfs      f25, 0x68(r1)
	  lwz       r12, 0x3B4(r23)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  addi      r25, r25, 0x1
	  cmpwi     r25, 0x10
	  blt+      .loc_0x188
	  lfs       f0, 0x124(r1)
	  addi      r26, r26, 0x1
	  lfs       f1, 0x128(r1)
	  cmpwi     r26, 0x10
	  fadds     f0, f0, f27
	  lfs       f2, 0x12C(r1)
	  fadds     f1, f1, f28
	  stfs      f0, 0x124(r1)
	  fadds     f0, f2, f29
	  stfs      f1, 0x128(r1)
	  stfs      f0, 0x12C(r1)
	  blt+      .loc_0x100
	  lmw       r23, 0x144(r1)
	  lwz       r0, 0x1B4(r1)
	  lfd       f31, 0x1A8(r1)
	  lfd       f30, 0x1A0(r1)
	  lfd       f29, 0x198(r1)
	  lfd       f28, 0x190(r1)
	  lfd       f27, 0x188(r1)
	  lfd       f26, 0x180(r1)
	  lfd       f25, 0x178(r1)
	  lfd       f24, 0x170(r1)
	  lfd       f23, 0x168(r1)
	  addi      r1, r1, 0x1B0
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	0001E8
 */
void Graphics::drawCircle(Vector3f&, f32, Matrix4f&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80029470
 * Size:	0001FC
 */
void Graphics::drawSphere(Vector3f&, f32, Matrix4f&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x148(r1)
	  stfd      f31, 0x140(r1)
	  fmr       f31, f1
	  stfd      f30, 0x138(r1)
	  stfd      f29, 0x130(r1)
	  stfd      f28, 0x128(r1)
	  stfd      f27, 0x120(r1)
	  stfd      f26, 0x118(r1)
	  stmw      r22, 0xF0(r1)
	  mr        r22, r3
	  addi      r23, r4, 0
	  addi      r24, r5, 0
	  li        r4, 0
	  li        r5, 0
	  lwz       r12, 0x3B4(r22)
	  lwz       r12, 0xCC(r12)
	  mtlr      r12
	  blrl
	  lfs       f29, -0x7D7C(r2)
	  addi      r28, r1, 0x24
	  lfd       f30, -0x7DA8(r2)
	  addi      r27, r1, 0x34
	  addi      r30, r1, 0x44
	  addi      r29, r1, 0x50
	  li        r26, 0
	  lis       r31, 0x4330

	.loc_0x70:
	  xoris     r0, r26, 0x8000
	  lfs       f4, -0x7DC0(r13)
	  stw       r0, 0xEC(r1)
	  mr        r4, r29
	  lfs       f0, -0x7DCC(r13)
	  mr        r5, r30
	  stw       r31, 0xE8(r1)
	  lfs       f1, -0x7DC8(r13)
	  mr        r6, r23
	  lfd       f2, 0xE8(r1)
	  addi      r3, r1, 0x9C
	  stfs      f0, 0x50(r1)
	  fsubs     f3, f2, f30
	  lfs       f2, -0x7DBC(r13)
	  stfs      f4, 0x44(r1)
	  lfs       f0, -0x7DC4(r13)
	  fmuls     f3, f29, f3
	  stfs      f1, 0x54(r1)
	  stfs      f3, 0x48(r1)
	  stfs      f2, 0x4C(r1)
	  stfs      f0, 0x58(r1)
	  bl        0x14BC0
	  addi      r3, r24, 0
	  addi      r4, r1, 0x9C
	  addi      r5, r1, 0x5C
	  bl        0x14B90
	  mr        r3, r22
	  lwz       r12, 0x3B4(r22)
	  addi      r4, r1, 0x5C
	  li        r5, 0
	  lwz       r12, 0x74(r12)
	  mtlr      r12
	  blrl
	  li        r25, 0

	.loc_0xF8:
	  addi      r3, r25, 0x1
	  srawi     r0, r3, 0x5
	  addze     r0, r0
	  rlwinm    r0,r0,5,0,26
	  subc      r0, r3, r0
	  xoris     r0, r0, 0x8000
	  stw       r0, 0xE4(r1)
	  xoris     r0, r25, 0x8000
	  stw       r31, 0xE0(r1)
	  stw       r0, 0xEC(r1)
	  lfd       f0, 0xE0(r1)
	  stw       r31, 0xE8(r1)
	  fsubs     f0, f0, f30
	  lfd       f1, 0xE8(r1)
	  fsubs     f1, f1, f30
	  fmuls     f26, f29, f0
	  fmuls     f27, f29, f1
	  fmr       f1, f26
	  bl        0x1F25A4
	  fmuls     f28, f31, f1
	  fmr       f1, f26
	  bl        0x1F272C
	  fmuls     f2, f31, f1
	  lfs       f0, -0x7DB4(r13)
	  fmr       f1, f27
	  stfs      f2, 0x20(r1)
	  lfs       f2, 0x20(r1)
	  stfs      f2, 0x24(r1)
	  stfs      f28, 0x28(r1)
	  stfs      f0, 0x2C(r1)
	  bl        0x1F2574
	  fmuls     f28, f31, f1
	  fmr       f1, f27
	  bl        0x1F26FC
	  fmuls     f1, f31, f1
	  lfs       f0, -0x7DB8(r13)
	  addi      r3, r22, 0
	  addi      r4, r27, 0
	  stfs      f1, 0x30(r1)
	  mr        r5, r28
	  lfs       f1, 0x30(r1)
	  stfs      f1, 0x34(r1)
	  stfs      f28, 0x38(r1)
	  stfs      f0, 0x3C(r1)
	  lwz       r12, 0x3B4(r22)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  addi      r25, r25, 0x1
	  cmpwi     r25, 0x10
	  blt+      .loc_0xF8
	  addi      r26, r26, 0x1
	  cmpwi     r26, 0x10
	  blt+      .loc_0x70
	  lmw       r22, 0xF0(r1)
	  lwz       r0, 0x14C(r1)
	  lfd       f31, 0x140(r1)
	  lfd       f30, 0x138(r1)
	  lfd       f29, 0x130(r1)
	  lfd       f28, 0x128(r1)
	  lfd       f27, 0x120(r1)
	  lfd       f26, 0x118(r1)
	  addi      r1, r1, 0x148
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8002966C
 * Size:	000170
 */
void Graphics::perspPrintf(Font*, Vector3f&, int, int, char*, ...)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x1C8(r1)
	  stmw      r25, 0x1AC(r1)
	  bne-      cr1, .loc_0x34
	  stfd      f1, 0x28(r1)
	  stfd      f2, 0x30(r1)
	  stfd      f3, 0x38(r1)
	  stfd      f4, 0x40(r1)
	  stfd      f5, 0x48(r1)
	  stfd      f6, 0x50(r1)
	  stfd      f7, 0x58(r1)
	  stfd      f8, 0x60(r1)

	.loc_0x34:
	  stw       r3, 0x8(r1)
	  addi      r25, r3, 0
	  lis       r0, 0x600
	  stw       r4, 0xC(r1)
	  addi      r26, r4, 0
	  addi      r27, r5, 0
	  stw       r5, 0x10(r1)
	  addi      r29, r6, 0
	  addi      r28, r7, 0
	  stw       r6, 0x14(r1)
	  addi      r4, r8, 0
	  addi      r3, r1, 0xA4
	  stw       r7, 0x18(r1)
	  stw       r8, 0x1C(r1)
	  stw       r9, 0x20(r1)
	  stw       r10, 0x24(r1)
	  stw       r0, 0x98(r1)
	  addi      r0, r1, 0x1D0
	  stw       r0, 0x9C(r1)
	  addi      r0, r1, 0x8
	  stw       r0, 0xA0(r1)
	  addi      r0, r1, 0x98
	  mr        r5, r0
	  bl        0x1ECF70
	  mr        r3, r25
	  lwz       r4, 0x0(r26)
	  lwz       r12, 0x3B4(r25)
	  li        r5, 0
	  lwz       r12, 0xCC(r12)
	  mtlr      r12
	  blrl
	  addi      r30, r29, 0
	  addi      r31, r1, 0xA4
	  li        r29, 0
	  b         .loc_0x14C

	.loc_0xC0:
	  lbz       r0, 0x0(r31)
	  mr        r3, r25
	  lwz       r4, 0xC(r26)
	  addi      r6, r27, 0
	  mulli     r0, r0, 0x1C
	  add       r5, r4, r0
	  lha       r7, -0x376(r5)
	  addi      r4, r1, 0x84
	  lha       r0, -0x37A(r5)
	  lha       r5, -0x37C(r5)
	  sub       r7, r30, r7
	  add       r0, r28, r0
	  stw       r7, 0x84(r1)
	  add       r5, r7, r5
	  stw       r0, 0x88(r1)
	  stw       r5, 0x8C(r1)
	  stw       r28, 0x90(r1)
	  lbz       r5, 0x0(r31)
	  lwz       r12, 0x3B4(r25)
	  subi      r0, r5, 0x20
	  lwz       r7, 0xC(r26)
	  mulli     r5, r0, 0x1C
	  lwz       r12, 0xD0(r12)
	  mtlr      r12
	  addi      r5, r5, 0xC
	  add       r5, r7, r5
	  blrl
	  lbz       r0, 0x0(r31)
	  addi      r31, r31, 0x1
	  lwz       r4, 0xC(r26)
	  addi      r29, r29, 0x1
	  mulli     r3, r0, 0x1C
	  subi      r0, r3, 0x378
	  lhax      r0, r4, r0
	  add       r30, r30, r0

	.loc_0x14C:
	  addi      r3, r1, 0xA4
	  bl        0x1EFC50
	  cmpw      r29, r3
	  blt+      .loc_0xC0
	  lmw       r25, 0x1AC(r1)
	  lwz       r0, 0x1CC(r1)
	  addi      r1, r1, 0x1C8
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800297DC
 * Size:	000114
 */
int Graphics::calcLighting(f32 intensity)
{
	mLightIntensity = intensity;

	setAmbient();

	s32 lightIndex   = 0;
	mActiveLightMask = 0;

	FOREACH_NODE(Light, mLight.mChild, l)
	{
		mActiveLightMask |= 1 << lightIndex;
		setLight(l, lightIndex);

		// 8 light maximum, restricted by GX
		if (++lightIndex == 7u) {
			break;
		}
	}

	if (mLight.mChild) {
		_370 = 50.0f;
		setLight((Light*)mLight.mChild, 7);
	}

	if (lightIndex > gsys->mActiveLightCount) {
		gsys->mActiveLightCount = lightIndex;
	}

	setLighting(true, nullptr);
	return lightIndex;

	s32 unused[2];
}

/*
 * --INFO--
 * Address:	800298F0
 * Size:	000004
 */
void Graphics::setAmbient()
{
}

/*
 * --INFO--
 * Address:	........
 * Size:	0001D0
 */
int Graphics::calcSphereLighting(Vector3f&, f32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0003A4
 */
int Graphics::calcBoxLighting(BoundBox&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800298F4
 * Size:	00007C
 */
void CacheTexture::makeResident()
{
	if (gsys->mCacher && !gsys->_260) {
		if (!_40) {
			gsys->mCacher->cacheTexture(this);
			gsys->copyCacheToTexture(this);
		} else {
			gsys->mCacher->updateInfo(this);
		}
	}
}

/*
 * --INFO--
 * Address:	80029970
 * Size:	000004
 */
void Graphics::videoReset()
{
}

/*
 * --INFO--
 * Address:	80029974
 * Size:	000004
 */
void Graphics::setVerticalFilter(u8*)
{
}

/*
 * --INFO--
 * Address:	80029978
 * Size:	000004
 */
void Graphics::getVerticalFilter(u8*)
{
}

/*
 * --INFO--
 * Address:	8002997C
 * Size:	000008
 */
u8* Graphics::getDListPtr()
{
	return nullptr;
}

/*
 * --INFO--
 * Address:	80029984
 * Size:	000008
 */
u32 Graphics::getDListRemainSize()
{
	return 0x0;
}

/*
 * --INFO--
 * Address:	8002998C
 * Size:	000008
 */
void Graphics::setLightcam(LightCamera* cam)
{
	mLightCam = cam;
}

/*
 * --INFO--
 * Address:	80029994
 * Size:	000004
 */
void Graphics::setBlendMode(u8, u8, u8)
{
}

/*
 * --INFO--
 * Address:	80029998
 * Size:	00007C
 */
void Graphics::setMatHandler(MaterialHandler*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x18(r1)
	  stw       r31, 0x14(r1)
	  addi      r31, r4, 0
	  stw       r30, 0x10(r1)
	  mr        r30, r3
	  lwz       r3, 0x350(r3)
	  cmplwi    r3, 0
	  beq-      .loc_0x44
	  cmplwi    r31, 0
	  bne-      .loc_0x44
	  lwz       r12, 0x4(r3)
	  li        r4, 0
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl

	.loc_0x44:
	  cmplwi    r31, 0
	  beq-      .loc_0x54
	  mr        r0, r31
	  b         .loc_0x58

	.loc_0x54:
	  lwz       r0, 0x34C(r30)

	.loc_0x58:
	  stw       r0, 0x350(r30)
	  lwz       r3, 0x350(r30)
	  stw       r30, 0x0(r3)
	  lwz       r0, 0x1C(r1)
	  lwz       r31, 0x14(r1)
	  lwz       r30, 0x10(r1)
	  addi      r1, r1, 0x18
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80029A14
 * Size:	000030
 */
void Graphics::useMaterial(Material*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x8(r1)
	  lwz       r3, 0x350(r3)
	  lwz       r12, 0x4(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  lwz       r0, 0xC(r1)
	  addi      r1, r1, 0x8
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80029A44
 * Size:	000004
 */
void Graphics::testRectangle(RectArea&)
{
}
