.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.global __ct__13P2DOrthoGraphFiiii
__ct__13P2DOrthoGraphFiiii:
/* 801AFCF0 001ACC50  7C 08 02 A6 */	mflr r0
/* 801AFCF4 001ACC54  90 01 00 04 */	stw r0, 4(r1)
/* 801AFCF8 001ACC58  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 801AFCFC 001ACC5C  93 E1 00 34 */	stw r31, 0x34(r1)
/* 801AFD00 001ACC60  7C FF 3B 78 */	mr r31, r7
/* 801AFD04 001ACC64  93 C1 00 30 */	stw r30, 0x30(r1)
/* 801AFD08 001ACC68  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 801AFD0C 001ACC6C  7C DD 33 78 */	mr r29, r6
/* 801AFD10 001ACC70  90 61 00 08 */	stw r3, 8(r1)
/* 801AFD14 001ACC74  80 61 00 08 */	lwz r3, 8(r1)
/* 801AFD18 001ACC78  4B FF FA 95 */	bl __ct__14P2DGrafContextFiiii
/* 801AFD1C 001ACC7C  83 C1 00 08 */	lwz r30, 8(r1)
/* 801AFD20 001ACC80  3C 60 80 2E */	lis r3, __vt__13P2DOrthoGraph@ha
/* 801AFD24 001ACC84  38 03 06 24 */	addi r0, r3, __vt__13P2DOrthoGraph@l
/* 801AFD28 001ACC88  90 1E 00 00 */	stw r0, 0(r30)
/* 801AFD2C 001ACC8C  38 7E 00 D4 */	addi r3, r30, 0xd4
/* 801AFD30 001ACC90  38 80 00 00 */	li r4, 0
/* 801AFD34 001ACC94  38 A0 00 00 */	li r5, 0
/* 801AFD38 001ACC98  38 C0 00 00 */	li r6, 0
/* 801AFD3C 001ACC9C  38 E0 00 00 */	li r7, 0
/* 801AFD40 001ACCA0  48 00 38 E9 */	bl set__7PUTRectFiiii
/* 801AFD44 001ACCA4  38 DD 00 00 */	addi r6, r29, 0
/* 801AFD48 001ACCA8  38 FF 00 00 */	addi r7, r31, 0
/* 801AFD4C 001ACCAC  38 61 00 20 */	addi r3, r1, 0x20
/* 801AFD50 001ACCB0  38 80 00 00 */	li r4, 0
/* 801AFD54 001ACCB4  38 A0 00 00 */	li r5, 0
/* 801AFD58 001ACCB8  48 00 38 D1 */	bl set__7PUTRectFiiii
/* 801AFD5C 001ACCBC  80 A1 00 20 */	lwz r5, 0x20(r1)
/* 801AFD60 001ACCC0  38 00 FF FF */	li r0, -1
/* 801AFD64 001ACCC4  80 81 00 24 */	lwz r4, 0x24(r1)
/* 801AFD68 001ACCC8  3B E0 00 01 */	li r31, 1
/* 801AFD6C 001ACCCC  38 7E 00 00 */	addi r3, r30, 0
/* 801AFD70 001ACCD0  90 BE 00 D4 */	stw r5, 0xd4(r30)
/* 801AFD74 001ACCD4  90 9E 00 D8 */	stw r4, 0xd8(r30)
/* 801AFD78 001ACCD8  90 1E 00 DC */	stw r0, 0xdc(r30)
/* 801AFD7C 001ACCDC  93 FE 00 E0 */	stw r31, 0xe0(r30)
/* 801AFD80 001ACCE0  81 9E 00 00 */	lwz r12, 0(r30)
/* 801AFD84 001ACCE4  81 8C 00 20 */	lwz r12, 0x20(r12)
/* 801AFD88 001ACCE8  7D 88 03 A6 */	mtlr r12
/* 801AFD8C 001ACCEC  4E 80 00 21 */	blrl 
/* 801AFD90 001ACCF0  93 FE 00 04 */	stw r31, 4(r30)
/* 801AFD94 001ACCF4  7F C3 F3 78 */	mr r3, r30
/* 801AFD98 001ACCF8  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801AFD9C 001ACCFC  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 801AFDA0 001ACD00  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 801AFDA4 001ACD04  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 801AFDA8 001ACD08  38 21 00 38 */	addi r1, r1, 0x38
/* 801AFDAC 001ACD0C  7C 08 03 A6 */	mtlr r0
/* 801AFDB0 001ACD10  4E 80 00 20 */	blr 

.global setPort__13P2DOrthoGraphFv
setPort__13P2DOrthoGraphFv:
/* 801AFDB4 001ACD14  7C 08 02 A6 */	mflr r0
/* 801AFDB8 001ACD18  90 01 00 04 */	stw r0, 4(r1)
/* 801AFDBC 001ACD1C  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 801AFDC0 001ACD20  93 E1 00 44 */	stw r31, 0x44(r1)
/* 801AFDC4 001ACD24  7C 7F 1B 78 */	mr r31, r3
/* 801AFDC8 001ACD28  4B FF FA 99 */	bl setPort__14P2DGrafContextFv
/* 801AFDCC 001ACD2C  A8 9F 00 D6 */	lha r4, 0xd6(r31)
/* 801AFDD0 001ACD30  3D 00 43 30 */	lis r8, 0x4330
/* 801AFDD4 001ACD34  A8 1F 00 DA */	lha r0, 0xda(r31)
/* 801AFDD8 001ACD38  38 7F 00 30 */	addi r3, r31, 0x30
/* 801AFDDC 001ACD3C  A8 DF 00 D4 */	lha r6, 0xd4(r31)
/* 801AFDE0 001ACD40  A8 BF 00 D8 */	lha r5, 0xd8(r31)
/* 801AFDE4 001ACD44  6C 89 80 00 */	xoris r9, r4, 0x8000
/* 801AFDE8 001ACD48  80 9F 00 E0 */	lwz r4, 0xe0(r31)
/* 801AFDEC 001ACD4C  6C 07 80 00 */	xoris r7, r0, 0x8000
/* 801AFDF0 001ACD50  80 1F 00 DC */	lwz r0, 0xdc(r31)
/* 801AFDF4 001ACD54  6C C6 80 00 */	xoris r6, r6, 0x8000
/* 801AFDF8 001ACD58  91 21 00 3C */	stw r9, 0x3c(r1)
/* 801AFDFC 001ACD5C  6C A5 80 00 */	xoris r5, r5, 0x8000
/* 801AFE00 001ACD60  C8 C2 B6 70 */	lfd f6, lbl_803EB870@sda21(r2)
/* 801AFE04 001ACD64  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 801AFE08 001ACD68  90 E1 00 34 */	stw r7, 0x34(r1)
/* 801AFE0C 001ACD6C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 801AFE10 001ACD70  90 C1 00 2C */	stw r6, 0x2c(r1)
/* 801AFE14 001ACD74  90 A1 00 24 */	stw r5, 0x24(r1)
/* 801AFE18 001ACD78  90 81 00 1C */	stw r4, 0x1c(r1)
/* 801AFE1C 001ACD7C  90 01 00 14 */	stw r0, 0x14(r1)
/* 801AFE20 001ACD80  91 01 00 38 */	stw r8, 0x38(r1)
/* 801AFE24 001ACD84  91 01 00 30 */	stw r8, 0x30(r1)
/* 801AFE28 001ACD88  C8 21 00 38 */	lfd f1, 0x38(r1)
/* 801AFE2C 001ACD8C  91 01 00 28 */	stw r8, 0x28(r1)
/* 801AFE30 001ACD90  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 801AFE34 001ACD94  EC 21 30 28 */	fsubs f1, f1, f6
/* 801AFE38 001ACD98  91 01 00 20 */	stw r8, 0x20(r1)
/* 801AFE3C 001ACD9C  C8 61 00 28 */	lfd f3, 0x28(r1)
/* 801AFE40 001ACDA0  EC 40 30 28 */	fsubs f2, f0, f6
/* 801AFE44 001ACDA4  91 01 00 18 */	stw r8, 0x18(r1)
/* 801AFE48 001ACDA8  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 801AFE4C 001ACDAC  EC 63 30 28 */	fsubs f3, f3, f6
/* 801AFE50 001ACDB0  91 01 00 10 */	stw r8, 0x10(r1)
/* 801AFE54 001ACDB4  C8 A1 00 18 */	lfd f5, 0x18(r1)
/* 801AFE58 001ACDB8  EC 80 30 28 */	fsubs f4, f0, f6
/* 801AFE5C 001ACDBC  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 801AFE60 001ACDC0  EC A5 30 28 */	fsubs f5, f5, f6
/* 801AFE64 001ACDC4  EC C0 30 28 */	fsubs f6, f0, f6
/* 801AFE68 001ACDC8  48 04 E1 89 */	bl MTXOrtho
/* 801AFE6C 001ACDCC  38 7F 00 30 */	addi r3, r31, 0x30
/* 801AFE70 001ACDD0  38 80 00 01 */	li r4, 1
/* 801AFE74 001ACDD4  48 06 44 81 */	bl GXSetProjection
/* 801AFE78 001ACDD8  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 801AFE7C 001ACDDC  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 801AFE80 001ACDE0  38 21 00 48 */	addi r1, r1, 0x48
/* 801AFE84 001ACDE4  7C 08 03 A6 */	mtlr r0
/* 801AFE88 001ACDE8  4E 80 00 20 */	blr 

.global setLookat__13P2DOrthoGraphFv
setLookat__13P2DOrthoGraphFv:
/* 801AFE8C 001ACDEC  7C 08 02 A6 */	mflr r0
/* 801AFE90 001ACDF0  90 01 00 04 */	stw r0, 4(r1)
/* 801AFE94 001ACDF4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801AFE98 001ACDF8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801AFE9C 001ACDFC  3B E3 00 00 */	addi r31, r3, 0
/* 801AFEA0 001ACE00  38 7F 00 70 */	addi r3, r31, 0x70
/* 801AFEA4 001ACE04  4B E8 DF 19 */	bl makeIdentity__8Matrix4fFv
/* 801AFEA8 001ACE08  38 7F 00 70 */	addi r3, r31, 0x70
/* 801AFEAC 001ACE0C  38 80 00 00 */	li r4, 0
/* 801AFEB0 001ACE10  48 06 45 A5 */	bl GXLoadPosMtxImm
/* 801AFEB4 001ACE14  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801AFEB8 001ACE18  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801AFEBC 001ACE1C  38 21 00 18 */	addi r1, r1, 0x18
/* 801AFEC0 001ACE20  7C 08 03 A6 */	mtlr r0
/* 801AFEC4 001ACE24  4E 80 00 20 */	blr 

.global scissorBounds__13P2DOrthoGraphFP7PUTRectP7PUTRect
scissorBounds__13P2DOrthoGraphFP7PUTRectP7PUTRect:
/* 801AFEC8 001ACE28  94 21 FF 18 */	stwu r1, -0xe8(r1)
/* 801AFECC 001ACE2C  A9 43 00 08 */	lha r10, 8(r3)
/* 801AFED0 001ACE30  3C 00 43 30 */	lis r0, 0x4330
/* 801AFED4 001ACE34  A8 E3 00 0C */	lha r7, 0xc(r3)
/* 801AFED8 001ACE38  A9 23 00 D4 */	lha r9, 0xd4(r3)
/* 801AFEDC 001ACE3C  6D 48 80 00 */	xoris r8, r10, 0x8000
/* 801AFEE0 001ACE40  A8 C3 00 D8 */	lha r6, 0xd8(r3)
/* 801AFEE4 001ACE44  7C EA 38 50 */	subf r7, r10, r7
/* 801AFEE8 001ACE48  6C E7 80 00 */	xoris r7, r7, 0x8000
/* 801AFEEC 001ACE4C  7C C9 30 50 */	subf r6, r9, r6
/* 801AFEF0 001ACE50  90 E1 00 D4 */	stw r7, 0xd4(r1)
/* 801AFEF4 001ACE54  6C C6 80 00 */	xoris r6, r6, 0x8000
/* 801AFEF8 001ACE58  A8 E5 00 00 */	lha r7, 0(r5)
/* 801AFEFC 001ACE5C  90 C1 00 CC */	stw r6, 0xcc(r1)
/* 801AFF00 001ACE60  C8 22 B6 70 */	lfd f1, lbl_803EB870@sda21(r2)
/* 801AFF04 001ACE64  7C C9 38 50 */	subf r6, r9, r7
/* 801AFF08 001ACE68  90 01 00 D0 */	stw r0, 0xd0(r1)
/* 801AFF0C 001ACE6C  6C C6 80 00 */	xoris r6, r6, 0x8000
/* 801AFF10 001ACE70  C0 42 B6 78 */	lfs f2, lbl_803EB878@sda21(r2)
/* 801AFF14 001ACE74  90 01 00 C8 */	stw r0, 0xc8(r1)
/* 801AFF18 001ACE78  C8 61 00 D0 */	lfd f3, 0xd0(r1)
/* 801AFF1C 001ACE7C  C8 01 00 C8 */	lfd f0, 0xc8(r1)
/* 801AFF20 001ACE80  EC 63 08 28 */	fsubs f3, f3, f1
/* 801AFF24 001ACE84  90 C1 00 DC */	stw r6, 0xdc(r1)
/* 801AFF28 001ACE88  EC 00 08 28 */	fsubs f0, f0, f1
/* 801AFF2C 001ACE8C  90 01 00 D8 */	stw r0, 0xd8(r1)
/* 801AFF30 001ACE90  EC 03 00 24 */	fdivs f0, f3, f0
/* 801AFF34 001ACE94  91 01 00 E4 */	stw r8, 0xe4(r1)
/* 801AFF38 001ACE98  C8 61 00 D8 */	lfd f3, 0xd8(r1)
/* 801AFF3C 001ACE9C  90 01 00 E0 */	stw r0, 0xe0(r1)
/* 801AFF40 001ACEA0  C8 81 00 E0 */	lfd f4, 0xe0(r1)
/* 801AFF44 001ACEA4  EC 63 08 28 */	fsubs f3, f3, f1
/* 801AFF48 001ACEA8  EC 84 08 28 */	fsubs f4, f4, f1
/* 801AFF4C 001ACEAC  EC 03 00 32 */	fmuls f0, f3, f0
/* 801AFF50 001ACEB0  EC 04 00 2A */	fadds f0, f4, f0
/* 801AFF54 001ACEB4  EC 02 00 2A */	fadds f0, f2, f0
/* 801AFF58 001ACEB8  FC 00 00 1E */	fctiwz f0, f0
/* 801AFF5C 001ACEBC  D8 01 00 C0 */	stfd f0, 0xc0(r1)
/* 801AFF60 001ACEC0  80 C1 00 C4 */	lwz r6, 0xc4(r1)
/* 801AFF64 001ACEC4  7C C6 07 34 */	extsh r6, r6
/* 801AFF68 001ACEC8  B0 C4 00 00 */	sth r6, 0(r4)
/* 801AFF6C 001ACECC  A9 43 00 08 */	lha r10, 8(r3)
/* 801AFF70 001ACED0  A8 E3 00 0C */	lha r7, 0xc(r3)
/* 801AFF74 001ACED4  A9 23 00 D4 */	lha r9, 0xd4(r3)
/* 801AFF78 001ACED8  6D 48 80 00 */	xoris r8, r10, 0x8000
/* 801AFF7C 001ACEDC  A8 C3 00 D8 */	lha r6, 0xd8(r3)
/* 801AFF80 001ACEE0  7C EA 38 50 */	subf r7, r10, r7
/* 801AFF84 001ACEE4  6C E7 80 00 */	xoris r7, r7, 0x8000
/* 801AFF88 001ACEE8  7C C9 30 50 */	subf r6, r9, r6
/* 801AFF8C 001ACEEC  90 E1 00 AC */	stw r7, 0xac(r1)
/* 801AFF90 001ACEF0  6C C6 80 00 */	xoris r6, r6, 0x8000
/* 801AFF94 001ACEF4  A8 E5 00 04 */	lha r7, 4(r5)
/* 801AFF98 001ACEF8  90 C1 00 A4 */	stw r6, 0xa4(r1)
/* 801AFF9C 001ACEFC  7C C9 38 50 */	subf r6, r9, r7
/* 801AFFA0 001ACF00  C0 02 B6 7C */	lfs f0, lbl_803EB87C@sda21(r2)
/* 801AFFA4 001ACF04  90 01 00 A8 */	stw r0, 0xa8(r1)
/* 801AFFA8 001ACF08  6C C6 80 00 */	xoris r6, r6, 0x8000
/* 801AFFAC 001ACF0C  90 01 00 A0 */	stw r0, 0xa0(r1)
/* 801AFFB0 001ACF10  C8 81 00 A8 */	lfd f4, 0xa8(r1)
/* 801AFFB4 001ACF14  C8 61 00 A0 */	lfd f3, 0xa0(r1)
/* 801AFFB8 001ACF18  90 C1 00 B4 */	stw r6, 0xb4(r1)
/* 801AFFBC 001ACF1C  EC 84 08 28 */	fsubs f4, f4, f1
/* 801AFFC0 001ACF20  EC 63 08 28 */	fsubs f3, f3, f1
/* 801AFFC4 001ACF24  90 01 00 B0 */	stw r0, 0xb0(r1)
/* 801AFFC8 001ACF28  91 01 00 BC */	stw r8, 0xbc(r1)
/* 801AFFCC 001ACF2C  EC 64 18 24 */	fdivs f3, f4, f3
/* 801AFFD0 001ACF30  C8 81 00 B0 */	lfd f4, 0xb0(r1)
/* 801AFFD4 001ACF34  90 01 00 B8 */	stw r0, 0xb8(r1)
/* 801AFFD8 001ACF38  C8 A1 00 B8 */	lfd f5, 0xb8(r1)
/* 801AFFDC 001ACF3C  EC 84 08 28 */	fsubs f4, f4, f1
/* 801AFFE0 001ACF40  EC A5 08 28 */	fsubs f5, f5, f1
/* 801AFFE4 001ACF44  EC 64 00 F2 */	fmuls f3, f4, f3
/* 801AFFE8 001ACF48  EC 65 18 2A */	fadds f3, f5, f3
/* 801AFFEC 001ACF4C  EC 60 18 2A */	fadds f3, f0, f3
/* 801AFFF0 001ACF50  FC 60 18 1E */	fctiwz f3, f3
/* 801AFFF4 001ACF54  D8 61 00 98 */	stfd f3, 0x98(r1)
/* 801AFFF8 001ACF58  80 C1 00 9C */	lwz r6, 0x9c(r1)
/* 801AFFFC 001ACF5C  7C C6 07 34 */	extsh r6, r6
/* 801B0000 001ACF60  B0 C4 00 04 */	sth r6, 4(r4)
/* 801B0004 001ACF64  A9 43 00 0A */	lha r10, 0xa(r3)
/* 801B0008 001ACF68  A8 E3 00 0E */	lha r7, 0xe(r3)
/* 801B000C 001ACF6C  A9 23 00 D6 */	lha r9, 0xd6(r3)
/* 801B0010 001ACF70  6D 48 80 00 */	xoris r8, r10, 0x8000
/* 801B0014 001ACF74  A8 C3 00 DA */	lha r6, 0xda(r3)
/* 801B0018 001ACF78  7C EA 38 50 */	subf r7, r10, r7
/* 801B001C 001ACF7C  6C E7 80 00 */	xoris r7, r7, 0x8000
/* 801B0020 001ACF80  7C C9 30 50 */	subf r6, r9, r6
/* 801B0024 001ACF84  90 E1 00 84 */	stw r7, 0x84(r1)
/* 801B0028 001ACF88  6C C6 80 00 */	xoris r6, r6, 0x8000
/* 801B002C 001ACF8C  A8 E5 00 02 */	lha r7, 2(r5)
/* 801B0030 001ACF90  90 C1 00 7C */	stw r6, 0x7c(r1)
/* 801B0034 001ACF94  7C C9 38 50 */	subf r6, r9, r7
/* 801B0038 001ACF98  90 01 00 80 */	stw r0, 0x80(r1)
/* 801B003C 001ACF9C  6C C6 80 00 */	xoris r6, r6, 0x8000
/* 801B0040 001ACFA0  90 01 00 78 */	stw r0, 0x78(r1)
/* 801B0044 001ACFA4  C8 81 00 80 */	lfd f4, 0x80(r1)
/* 801B0048 001ACFA8  C8 61 00 78 */	lfd f3, 0x78(r1)
/* 801B004C 001ACFAC  90 C1 00 8C */	stw r6, 0x8c(r1)
/* 801B0050 001ACFB0  EC 84 08 28 */	fsubs f4, f4, f1
/* 801B0054 001ACFB4  EC 63 08 28 */	fsubs f3, f3, f1
/* 801B0058 001ACFB8  90 01 00 88 */	stw r0, 0x88(r1)
/* 801B005C 001ACFBC  91 01 00 94 */	stw r8, 0x94(r1)
/* 801B0060 001ACFC0  EC 64 18 24 */	fdivs f3, f4, f3
/* 801B0064 001ACFC4  C8 81 00 88 */	lfd f4, 0x88(r1)
/* 801B0068 001ACFC8  90 01 00 90 */	stw r0, 0x90(r1)
/* 801B006C 001ACFCC  C8 A1 00 90 */	lfd f5, 0x90(r1)
/* 801B0070 001ACFD0  EC 84 08 28 */	fsubs f4, f4, f1
/* 801B0074 001ACFD4  EC A5 08 28 */	fsubs f5, f5, f1
/* 801B0078 001ACFD8  EC 64 00 F2 */	fmuls f3, f4, f3
/* 801B007C 001ACFDC  EC 65 18 2A */	fadds f3, f5, f3
/* 801B0080 001ACFE0  EC 42 18 2A */	fadds f2, f2, f3
/* 801B0084 001ACFE4  FC 40 10 1E */	fctiwz f2, f2
/* 801B0088 001ACFE8  D8 41 00 70 */	stfd f2, 0x70(r1)
/* 801B008C 001ACFEC  80 C1 00 74 */	lwz r6, 0x74(r1)
/* 801B0090 001ACFF0  7C C6 07 34 */	extsh r6, r6
/* 801B0094 001ACFF4  B0 C4 00 02 */	sth r6, 2(r4)
/* 801B0098 001ACFF8  A9 23 00 0A */	lha r9, 0xa(r3)
/* 801B009C 001ACFFC  A8 C3 00 0E */	lha r6, 0xe(r3)
/* 801B00A0 001AD000  A9 03 00 D6 */	lha r8, 0xd6(r3)
/* 801B00A4 001AD004  6D 27 80 00 */	xoris r7, r9, 0x8000
/* 801B00A8 001AD008  A8 63 00 DA */	lha r3, 0xda(r3)
/* 801B00AC 001AD00C  7C C9 30 50 */	subf r6, r9, r6
/* 801B00B0 001AD010  6C C6 80 00 */	xoris r6, r6, 0x8000
/* 801B00B4 001AD014  7C 68 18 50 */	subf r3, r8, r3
/* 801B00B8 001AD018  90 C1 00 5C */	stw r6, 0x5c(r1)
/* 801B00BC 001AD01C  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 801B00C0 001AD020  A8 A5 00 06 */	lha r5, 6(r5)
/* 801B00C4 001AD024  90 61 00 54 */	stw r3, 0x54(r1)
/* 801B00C8 001AD028  7C 68 28 50 */	subf r3, r8, r5
/* 801B00CC 001AD02C  90 01 00 58 */	stw r0, 0x58(r1)
/* 801B00D0 001AD030  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 801B00D4 001AD034  90 01 00 50 */	stw r0, 0x50(r1)
/* 801B00D8 001AD038  C8 61 00 58 */	lfd f3, 0x58(r1)
/* 801B00DC 001AD03C  C8 41 00 50 */	lfd f2, 0x50(r1)
/* 801B00E0 001AD040  EC 63 08 28 */	fsubs f3, f3, f1
/* 801B00E4 001AD044  90 61 00 64 */	stw r3, 0x64(r1)
/* 801B00E8 001AD048  EC 42 08 28 */	fsubs f2, f2, f1
/* 801B00EC 001AD04C  90 01 00 60 */	stw r0, 0x60(r1)
/* 801B00F0 001AD050  EC 43 10 24 */	fdivs f2, f3, f2
/* 801B00F4 001AD054  90 E1 00 6C */	stw r7, 0x6c(r1)
/* 801B00F8 001AD058  C8 61 00 60 */	lfd f3, 0x60(r1)
/* 801B00FC 001AD05C  90 01 00 68 */	stw r0, 0x68(r1)
/* 801B0100 001AD060  C8 81 00 68 */	lfd f4, 0x68(r1)
/* 801B0104 001AD064  EC 63 08 28 */	fsubs f3, f3, f1
/* 801B0108 001AD068  EC 84 08 28 */	fsubs f4, f4, f1
/* 801B010C 001AD06C  EC 23 00 B2 */	fmuls f1, f3, f2
/* 801B0110 001AD070  EC 24 08 2A */	fadds f1, f4, f1
/* 801B0114 001AD074  EC 00 08 2A */	fadds f0, f0, f1
/* 801B0118 001AD078  FC 00 00 1E */	fctiwz f0, f0
/* 801B011C 001AD07C  D8 01 00 48 */	stfd f0, 0x48(r1)
/* 801B0120 001AD080  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 801B0124 001AD084  7C 00 07 34 */	extsh r0, r0
/* 801B0128 001AD088  B0 04 00 06 */	sth r0, 6(r4)
/* 801B012C 001AD08C  38 21 00 E8 */	addi r1, r1, 0xe8
/* 801B0130 001AD090  4E 80 00 20 */	blr 

.global __dt__13P2DOrthoGraphFv
__dt__13P2DOrthoGraphFv:
/* 801B0134 001AD094  7C 08 02 A6 */	mflr r0
/* 801B0138 001AD098  90 01 00 04 */	stw r0, 4(r1)
/* 801B013C 001AD09C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801B0140 001AD0A0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801B0144 001AD0A4  7C 7F 1B 79 */	or. r31, r3, r3
/* 801B0148 001AD0A8  41 82 00 30 */	beq lbl_801B0178
/* 801B014C 001AD0AC  3C 60 80 2E */	lis r3, __vt__13P2DOrthoGraph@ha
/* 801B0150 001AD0B0  38 03 06 24 */	addi r0, r3, __vt__13P2DOrthoGraph@l
/* 801B0154 001AD0B4  90 1F 00 00 */	stw r0, 0(r31)
/* 801B0158 001AD0B8  41 82 00 10 */	beq lbl_801B0168
/* 801B015C 001AD0BC  3C 60 80 2E */	lis r3, __vt__14P2DGrafContext@ha
/* 801B0160 001AD0C0  38 03 05 D4 */	addi r0, r3, __vt__14P2DGrafContext@l
/* 801B0164 001AD0C4  90 1F 00 00 */	stw r0, 0(r31)
lbl_801B0168:
/* 801B0168 001AD0C8  7C 80 07 35 */	extsh. r0, r4
/* 801B016C 001AD0CC  40 81 00 0C */	ble lbl_801B0178
/* 801B0170 001AD0D0  7F E3 FB 78 */	mr r3, r31
/* 801B0174 001AD0D4  4B E9 70 39 */	bl __dl__FPv
lbl_801B0178:
/* 801B0178 001AD0D8  7F E3 FB 78 */	mr r3, r31
/* 801B017C 001AD0DC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801B0180 001AD0E0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801B0184 001AD0E4  38 21 00 18 */	addi r1, r1, 0x18
/* 801B0188 001AD0E8  7C 08 03 A6 */	mtlr r0
/* 801B018C 001AD0EC  4E 80 00 20 */	blr 

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 8
lbl_802E05F8:
	.asciz "P2DOrthoGraph"
.balign 4
lbl_802E0608:
	.asciz "P2DGrafContext"
.balign 4
lbl_802E0618:
	.4byte __RTTI__14P2DGrafContext
	.4byte 0
	.4byte 0
.global __vt__13P2DOrthoGraph
__vt__13P2DOrthoGraph:
	.4byte __RTTI__13P2DOrthoGraph
	.4byte 0
	.4byte __dt__13P2DOrthoGraphFv
	.4byte place__14P2DGrafContextFRC7PUTRect
	.4byte place__14P2DGrafContextFiiii
	.4byte setPort__13P2DOrthoGraphFv
	.4byte setup2D__14P2DGrafContextFv
	.4byte setScissor__14P2DGrafContextFv
	.4byte setLookat__13P2DOrthoGraphFv

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.balign 8
__RTTI__14P2DGrafContext:
	.4byte lbl_802E0608
	.4byte 0
__RTTI__13P2DOrthoGraph:
	.4byte lbl_802E05F8
	.4byte lbl_802E0618

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.balign 8
lbl_803EB870:
	.4byte 0x43300000
	.4byte 0x80000000
lbl_803EB878:
	.4byte 0x3DCCCCCD
lbl_803EB87C:
	.4byte 0x3F666666
