.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.fn __ct__5NLineFR9NVector3fR9NVector3f, global
/* 8011D3FC 0011A35C  7C 08 02 A6 */	mflr r0
/* 8011D400 0011A360  3C C0 80 2C */	lis r6, __vt__5NLine@ha
/* 8011D404 0011A364  90 01 00 04 */	stw r0, 4(r1)
/* 8011D408 0011A368  38 06 43 68 */	addi r0, r6, __vt__5NLine@l
/* 8011D40C 0011A36C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8011D410 0011A370  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8011D414 0011A374  3B E5 00 00 */	addi r31, r5, 0
/* 8011D418 0011A378  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8011D41C 0011A37C  3B C4 00 00 */	addi r30, r4, 0
/* 8011D420 0011A380  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8011D424 0011A384  3B A3 00 00 */	addi r29, r3, 0
/* 8011D428 0011A388  90 03 00 00 */	stw r0, 0(r3)
/* 8011D42C 0011A38C  38 7D 00 04 */	addi r3, r29, 4
/* 8011D430 0011A390  4B FF FA 25 */	bl __ct__9NVector3fFv
/* 8011D434 0011A394  38 7D 00 10 */	addi r3, r29, 0x10
/* 8011D438 0011A398  4B FF FA 1D */	bl __ct__9NVector3fFv
/* 8011D43C 0011A39C  38 7D 00 00 */	addi r3, r29, 0
/* 8011D440 0011A3A0  38 9E 00 00 */	addi r4, r30, 0
/* 8011D444 0011A3A4  38 BF 00 00 */	addi r5, r31, 0
/* 8011D448 0011A3A8  48 00 00 25 */	bl construct__5NLineFR9NVector3fR9NVector3f
/* 8011D44C 0011A3AC  7F A3 EB 78 */	mr r3, r29
/* 8011D450 0011A3B0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8011D454 0011A3B4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8011D458 0011A3B8  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8011D45C 0011A3BC  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8011D460 0011A3C0  38 21 00 28 */	addi r1, r1, 0x28
/* 8011D464 0011A3C4  7C 08 03 A6 */	mtlr r0
/* 8011D468 0011A3C8  4E 80 00 20 */	blr 
.endfn __ct__5NLineFR9NVector3fR9NVector3f

.fn construct__5NLineFR9NVector3fR9NVector3f, global
/* 8011D46C 0011A3CC  C0 04 00 00 */	lfs f0, 0(r4)
/* 8011D470 0011A3D0  D0 03 00 04 */	stfs f0, 4(r3)
/* 8011D474 0011A3D4  C0 04 00 04 */	lfs f0, 4(r4)
/* 8011D478 0011A3D8  D0 03 00 08 */	stfs f0, 8(r3)
/* 8011D47C 0011A3DC  C0 04 00 08 */	lfs f0, 8(r4)
/* 8011D480 0011A3E0  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 8011D484 0011A3E4  C0 05 00 00 */	lfs f0, 0(r5)
/* 8011D488 0011A3E8  D0 03 00 10 */	stfs f0, 0x10(r3)
/* 8011D48C 0011A3EC  C0 05 00 04 */	lfs f0, 4(r5)
/* 8011D490 0011A3F0  D0 03 00 14 */	stfs f0, 0x14(r3)
/* 8011D494 0011A3F4  C0 05 00 08 */	lfs f0, 8(r5)
/* 8011D498 0011A3F8  D0 03 00 18 */	stfs f0, 0x18(r3)
/* 8011D49C 0011A3FC  4E 80 00 20 */	blr 
.endfn construct__5NLineFR9NVector3fR9NVector3f

.fn calcDistance__5NLineFR9NVector3fPf, global
/* 8011D4A0 0011A400  7C 08 02 A6 */	mflr r0
/* 8011D4A4 0011A404  90 01 00 04 */	stw r0, 4(r1)
/* 8011D4A8 0011A408  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 8011D4AC 0011A40C  DB E1 00 48 */	stfd f31, 0x48(r1)
/* 8011D4B0 0011A410  93 E1 00 44 */	stw r31, 0x44(r1)
/* 8011D4B4 0011A414  93 C1 00 40 */	stw r30, 0x40(r1)
/* 8011D4B8 0011A418  3B C5 00 00 */	addi r30, r5, 0
/* 8011D4BC 0011A41C  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 8011D4C0 0011A420  3B A4 00 00 */	addi r29, r4, 0
/* 8011D4C4 0011A424  93 81 00 38 */	stw r28, 0x38(r1)
/* 8011D4C8 0011A428  3B 83 00 00 */	addi r28, r3, 0
/* 8011D4CC 0011A42C  38 61 00 2C */	addi r3, r1, 0x2c
/* 8011D4D0 0011A430  4B FF F9 85 */	bl __ct__9NVector3fFv
/* 8011D4D4 0011A434  3B E3 00 00 */	addi r31, r3, 0
/* 8011D4D8 0011A438  38 7C 00 00 */	addi r3, r28, 0
/* 8011D4DC 0011A43C  38 9D 00 00 */	addi r4, r29, 0
/* 8011D4E0 0011A440  48 00 00 81 */	bl calcVerticalProjection__5NLineFR9NVector3f
/* 8011D4E4 0011A444  FF E0 08 90 */	fmr f31, f1
/* 8011D4E8 0011A448  38 7C 00 00 */	addi r3, r28, 0
/* 8011D4EC 0011A44C  38 9F 00 00 */	addi r4, r31, 0
/* 8011D4F0 0011A450  48 00 00 D5 */	bl outputPosition__5NLineFfR9NVector3f
/* 8011D4F4 0011A454  28 1E 00 00 */	cmplwi r30, 0
/* 8011D4F8 0011A458  41 82 00 08 */	beq .L_8011D500
/* 8011D4FC 0011A45C  D3 FE 00 00 */	stfs f31, 0(r30)
.L_8011D500:
/* 8011D500 0011A460  C0 7D 00 00 */	lfs f3, 0(r29)
/* 8011D504 0011A464  C0 5F 00 00 */	lfs f2, 0(r31)
/* 8011D508 0011A468  C0 3D 00 04 */	lfs f1, 4(r29)
/* 8011D50C 0011A46C  C0 1F 00 04 */	lfs f0, 4(r31)
/* 8011D510 0011A470  EC 83 10 28 */	fsubs f4, f3, f2
/* 8011D514 0011A474  C0 5D 00 08 */	lfs f2, 8(r29)
/* 8011D518 0011A478  EC 61 00 28 */	fsubs f3, f1, f0
/* 8011D51C 0011A47C  C0 1F 00 08 */	lfs f0, 8(r31)
/* 8011D520 0011A480  EC 24 01 32 */	fmuls f1, f4, f4
/* 8011D524 0011A484  EC 42 00 28 */	fsubs f2, f2, f0
/* 8011D528 0011A488  EC 03 00 F2 */	fmuls f0, f3, f3
/* 8011D52C 0011A48C  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8011D530 0011A490  EC 01 00 2A */	fadds f0, f1, f0
/* 8011D534 0011A494  EC 22 00 2A */	fadds f1, f2, f0
/* 8011D538 0011A498  4B EF 07 09 */	bl sqrtf__3stdFf
/* 8011D53C 0011A49C  80 01 00 54 */	lwz r0, 0x54(r1)
/* 8011D540 0011A4A0  CB E1 00 48 */	lfd f31, 0x48(r1)
/* 8011D544 0011A4A4  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 8011D548 0011A4A8  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 8011D54C 0011A4AC  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 8011D550 0011A4B0  83 81 00 38 */	lwz r28, 0x38(r1)
/* 8011D554 0011A4B4  38 21 00 50 */	addi r1, r1, 0x50
/* 8011D558 0011A4B8  7C 08 03 A6 */	mtlr r0
/* 8011D55C 0011A4BC  4E 80 00 20 */	blr 
.endfn calcDistance__5NLineFR9NVector3fPf

.fn calcVerticalProjection__5NLineFR9NVector3f, global
/* 8011D560 0011A4C0  7C 08 02 A6 */	mflr r0
/* 8011D564 0011A4C4  38 A4 00 00 */	addi r5, r4, 0
/* 8011D568 0011A4C8  90 01 00 04 */	stw r0, 4(r1)
/* 8011D56C 0011A4CC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8011D570 0011A4D0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8011D574 0011A4D4  3B E3 00 00 */	addi r31, r3, 0
/* 8011D578 0011A4D8  38 61 00 10 */	addi r3, r1, 0x10
/* 8011D57C 0011A4DC  38 9F 00 04 */	addi r4, r31, 4
/* 8011D580 0011A4E0  4B FF F9 AD */	bl __ct__9NVector3fFR8Vector3fR8Vector3f
/* 8011D584 0011A4E4  C0 7F 00 10 */	lfs f3, 0x10(r31)
/* 8011D588 0011A4E8  C0 43 00 00 */	lfs f2, 0(r3)
/* 8011D58C 0011A4EC  C0 3F 00 14 */	lfs f1, 0x14(r31)
/* 8011D590 0011A4F0  C0 03 00 04 */	lfs f0, 4(r3)
/* 8011D594 0011A4F4  EC 43 00 B2 */	fmuls f2, f3, f2
/* 8011D598 0011A4F8  C0 7F 00 18 */	lfs f3, 0x18(r31)
/* 8011D59C 0011A4FC  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011D5A0 0011A500  C0 23 00 08 */	lfs f1, 8(r3)
/* 8011D5A4 0011A504  EC 23 00 72 */	fmuls f1, f3, f1
/* 8011D5A8 0011A508  EC 02 00 2A */	fadds f0, f2, f0
/* 8011D5AC 0011A50C  EC 21 00 2A */	fadds f1, f1, f0
/* 8011D5B0 0011A510  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8011D5B4 0011A514  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8011D5B8 0011A518  38 21 00 28 */	addi r1, r1, 0x28
/* 8011D5BC 0011A51C  7C 08 03 A6 */	mtlr r0
/* 8011D5C0 0011A520  4E 80 00 20 */	blr 
.endfn calcVerticalProjection__5NLineFR9NVector3f

.fn outputPosition__5NLineFfR9NVector3f, global
/* 8011D5C4 0011A524  7C 08 02 A6 */	mflr r0
/* 8011D5C8 0011A528  90 01 00 04 */	stw r0, 4(r1)
/* 8011D5CC 0011A52C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8011D5D0 0011A530  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 8011D5D4 0011A534  FF E0 08 90 */	fmr f31, f1
/* 8011D5D8 0011A538  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8011D5DC 0011A53C  3B E4 00 00 */	addi r31, r4, 0
/* 8011D5E0 0011A540  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8011D5E4 0011A544  3B C3 00 00 */	addi r30, r3, 0
/* 8011D5E8 0011A548  38 61 00 18 */	addi r3, r1, 0x18
/* 8011D5EC 0011A54C  4B FF F8 69 */	bl __ct__9NVector3fFv
/* 8011D5F0 0011A550  C0 1E 00 10 */	lfs f0, 0x10(r30)
/* 8011D5F4 0011A554  EC 1F 00 32 */	fmuls f0, f31, f0
/* 8011D5F8 0011A558  D0 03 00 00 */	stfs f0, 0(r3)
/* 8011D5FC 0011A55C  C0 1E 00 14 */	lfs f0, 0x14(r30)
/* 8011D600 0011A560  EC 1F 00 32 */	fmuls f0, f31, f0
/* 8011D604 0011A564  D0 03 00 04 */	stfs f0, 4(r3)
/* 8011D608 0011A568  C0 1E 00 18 */	lfs f0, 0x18(r30)
/* 8011D60C 0011A56C  EC 1F 00 32 */	fmuls f0, f31, f0
/* 8011D610 0011A570  D0 03 00 08 */	stfs f0, 8(r3)
/* 8011D614 0011A574  C0 3E 00 04 */	lfs f1, 4(r30)
/* 8011D618 0011A578  C0 03 00 00 */	lfs f0, 0(r3)
/* 8011D61C 0011A57C  C0 7E 00 08 */	lfs f3, 8(r30)
/* 8011D620 0011A580  C0 43 00 04 */	lfs f2, 4(r3)
/* 8011D624 0011A584  EC 01 00 2A */	fadds f0, f1, f0
/* 8011D628 0011A588  C0 9E 00 0C */	lfs f4, 0xc(r30)
/* 8011D62C 0011A58C  C0 23 00 08 */	lfs f1, 8(r3)
/* 8011D630 0011A590  EC 43 10 2A */	fadds f2, f3, f2
/* 8011D634 0011A594  D0 1F 00 00 */	stfs f0, 0(r31)
/* 8011D638 0011A598  EC 04 08 2A */	fadds f0, f4, f1
/* 8011D63C 0011A59C  D0 5F 00 04 */	stfs f2, 4(r31)
/* 8011D640 0011A5A0  D0 1F 00 08 */	stfs f0, 8(r31)
/* 8011D644 0011A5A4  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8011D648 0011A5A8  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 8011D64C 0011A5AC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8011D650 0011A5B0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8011D654 0011A5B4  38 21 00 38 */	addi r1, r1, 0x38
/* 8011D658 0011A5B8  7C 08 03 A6 */	mtlr r0
/* 8011D65C 0011A5BC  4E 80 00 20 */	blr 
.endfn outputPosition__5NLineFfR9NVector3f

.fn transform__5NLineFR12NTransform3D, global
/* 8011D660 0011A5C0  7C 08 02 A6 */	mflr r0
/* 8011D664 0011A5C4  90 01 00 04 */	stw r0, 4(r1)
/* 8011D668 0011A5C8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8011D66C 0011A5CC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8011D670 0011A5D0  3B E4 00 00 */	addi r31, r4, 0
/* 8011D674 0011A5D4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8011D678 0011A5D8  3B C3 00 00 */	addi r30, r3, 0
/* 8011D67C 0011A5DC  38 7F 00 00 */	addi r3, r31, 0
/* 8011D680 0011A5E0  38 9E 00 04 */	addi r4, r30, 4
/* 8011D684 0011A5E4  4B FF F6 21 */	bl transform__12NTransform3DFR8Vector3f
/* 8011D688 0011A5E8  38 7F 00 00 */	addi r3, r31, 0
/* 8011D68C 0011A5EC  38 9E 00 10 */	addi r4, r30, 0x10
/* 8011D690 0011A5F0  4B FF F4 79 */	bl rotate__12NTransform3DFR8Vector3f
/* 8011D694 0011A5F4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8011D698 0011A5F8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8011D69C 0011A5FC  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8011D6A0 0011A600  38 21 00 18 */	addi r1, r1, 0x18
/* 8011D6A4 0011A604  7C 08 03 A6 */	mtlr r0
/* 8011D6A8 0011A608  4E 80 00 20 */	blr 
.endfn transform__5NLineFR12NTransform3D

.fn println__5NLineFv, global
/* 8011D6AC 0011A60C  7C 08 02 A6 */	mflr r0
/* 8011D6B0 0011A610  90 01 00 04 */	stw r0, 4(r1)
/* 8011D6B4 0011A614  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8011D6B8 0011A618  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8011D6BC 0011A61C  3B E3 00 00 */	addi r31, r3, 0
/* 8011D6C0 0011A620  38 7F 00 04 */	addi r3, r31, 4
/* 8011D6C4 0011A624  4B FF F9 51 */	bl println__9NVector3fFv
/* 8011D6C8 0011A628  38 7F 00 10 */	addi r3, r31, 0x10
/* 8011D6CC 0011A62C  4B FF F9 49 */	bl println__9NVector3fFv
/* 8011D6D0 0011A630  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8011D6D4 0011A634  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8011D6D8 0011A638  38 21 00 18 */	addi r1, r1, 0x18
/* 8011D6DC 0011A63C  7C 08 03 A6 */	mtlr r0
/* 8011D6E0 0011A640  4E 80 00 20 */	blr 
.endfn println__5NLineFv

.fn __ct__6NPlaneFR9NVector3fR9NVector3f, global
/* 8011D6E4 0011A644  7C 08 02 A6 */	mflr r0
/* 8011D6E8 0011A648  3C C0 80 2C */	lis r6, __vt__6NPlane@ha
/* 8011D6EC 0011A64C  90 01 00 04 */	stw r0, 4(r1)
/* 8011D6F0 0011A650  38 06 43 58 */	addi r0, r6, __vt__6NPlane@l
/* 8011D6F4 0011A654  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8011D6F8 0011A658  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8011D6FC 0011A65C  3B E5 00 00 */	addi r31, r5, 0
/* 8011D700 0011A660  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8011D704 0011A664  3B C4 00 00 */	addi r30, r4, 0
/* 8011D708 0011A668  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8011D70C 0011A66C  3B A3 00 00 */	addi r29, r3, 0
/* 8011D710 0011A670  90 03 00 00 */	stw r0, 0(r3)
/* 8011D714 0011A674  38 7D 00 04 */	addi r3, r29, 4
/* 8011D718 0011A678  4B FF F7 3D */	bl __ct__9NVector3fFv
/* 8011D71C 0011A67C  38 7D 00 00 */	addi r3, r29, 0
/* 8011D720 0011A680  38 9E 00 00 */	addi r4, r30, 0
/* 8011D724 0011A684  38 BF 00 00 */	addi r5, r31, 0
/* 8011D728 0011A688  48 00 00 25 */	bl construct__6NPlaneFR9NVector3fR9NVector3f
/* 8011D72C 0011A68C  7F A3 EB 78 */	mr r3, r29
/* 8011D730 0011A690  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8011D734 0011A694  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8011D738 0011A698  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8011D73C 0011A69C  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8011D740 0011A6A0  38 21 00 28 */	addi r1, r1, 0x28
/* 8011D744 0011A6A4  7C 08 03 A6 */	mtlr r0
/* 8011D748 0011A6A8  4E 80 00 20 */	blr 
.endfn __ct__6NPlaneFR9NVector3fR9NVector3f

.fn construct__6NPlaneFR9NVector3fR9NVector3f, global
/* 8011D74C 0011A6AC  C0 04 00 00 */	lfs f0, 0(r4)
/* 8011D750 0011A6B0  D0 03 00 04 */	stfs f0, 4(r3)
/* 8011D754 0011A6B4  C0 04 00 04 */	lfs f0, 4(r4)
/* 8011D758 0011A6B8  D0 03 00 08 */	stfs f0, 8(r3)
/* 8011D75C 0011A6BC  C0 04 00 08 */	lfs f0, 8(r4)
/* 8011D760 0011A6C0  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 8011D764 0011A6C4  C0 63 00 04 */	lfs f3, 4(r3)
/* 8011D768 0011A6C8  C0 45 00 00 */	lfs f2, 0(r5)
/* 8011D76C 0011A6CC  C0 23 00 08 */	lfs f1, 8(r3)
/* 8011D770 0011A6D0  C0 05 00 04 */	lfs f0, 4(r5)
/* 8011D774 0011A6D4  EC 43 00 B2 */	fmuls f2, f3, f2
/* 8011D778 0011A6D8  C0 63 00 0C */	lfs f3, 0xc(r3)
/* 8011D77C 0011A6DC  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011D780 0011A6E0  C0 25 00 08 */	lfs f1, 8(r5)
/* 8011D784 0011A6E4  EC 23 00 72 */	fmuls f1, f3, f1
/* 8011D788 0011A6E8  EC 02 00 2A */	fadds f0, f2, f0
/* 8011D78C 0011A6EC  EC 01 00 2A */	fadds f0, f1, f0
/* 8011D790 0011A6F0  FC 00 00 50 */	fneg f0, f0
/* 8011D794 0011A6F4  D0 03 00 10 */	stfs f0, 0x10(r3)
/* 8011D798 0011A6F8  4E 80 00 20 */	blr 
.endfn construct__6NPlaneFR9NVector3fR9NVector3f

.fn outputVerticalPosition__6NPlaneFR9NVector3fR9NVector3f, global
/* 8011D79C 0011A6FC  7C 08 02 A6 */	mflr r0
/* 8011D7A0 0011A700  90 01 00 04 */	stw r0, 4(r1)
/* 8011D7A4 0011A704  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 8011D7A8 0011A708  DB E1 00 40 */	stfd f31, 0x40(r1)
/* 8011D7AC 0011A70C  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8011D7B0 0011A710  7C BF 2B 78 */	mr r31, r5
/* 8011D7B4 0011A714  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8011D7B8 0011A718  3B C4 00 00 */	addi r30, r4, 0
/* 8011D7BC 0011A71C  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8011D7C0 0011A720  3B A3 00 00 */	addi r29, r3, 0
/* 8011D7C4 0011A724  C0 63 00 04 */	lfs f3, 4(r3)
/* 8011D7C8 0011A728  C0 44 00 00 */	lfs f2, 0(r4)
/* 8011D7CC 0011A72C  C0 23 00 08 */	lfs f1, 8(r3)
/* 8011D7D0 0011A730  38 61 00 1C */	addi r3, r1, 0x1c
/* 8011D7D4 0011A734  C0 04 00 04 */	lfs f0, 4(r4)
/* 8011D7D8 0011A738  EC 43 00 B2 */	fmuls f2, f3, f2
/* 8011D7DC 0011A73C  C0 7D 00 0C */	lfs f3, 0xc(r29)
/* 8011D7E0 0011A740  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011D7E4 0011A744  C0 24 00 08 */	lfs f1, 8(r4)
/* 8011D7E8 0011A748  C0 9D 00 10 */	lfs f4, 0x10(r29)
/* 8011D7EC 0011A74C  EC 23 00 72 */	fmuls f1, f3, f1
/* 8011D7F0 0011A750  EC 02 00 2A */	fadds f0, f2, f0
/* 8011D7F4 0011A754  EC 01 00 2A */	fadds f0, f1, f0
/* 8011D7F8 0011A758  EF E4 00 2A */	fadds f31, f4, f0
/* 8011D7FC 0011A75C  4B FF F6 59 */	bl __ct__9NVector3fFv
/* 8011D800 0011A760  FC 20 F8 50 */	fneg f1, f31
/* 8011D804 0011A764  C0 1D 00 04 */	lfs f0, 4(r29)
/* 8011D808 0011A768  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011D80C 0011A76C  D0 03 00 00 */	stfs f0, 0(r3)
/* 8011D810 0011A770  C0 1D 00 08 */	lfs f0, 8(r29)
/* 8011D814 0011A774  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011D818 0011A778  D0 03 00 04 */	stfs f0, 4(r3)
/* 8011D81C 0011A77C  C0 1D 00 0C */	lfs f0, 0xc(r29)
/* 8011D820 0011A780  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011D824 0011A784  D0 03 00 08 */	stfs f0, 8(r3)
/* 8011D828 0011A788  C0 3E 00 00 */	lfs f1, 0(r30)
/* 8011D82C 0011A78C  C0 03 00 00 */	lfs f0, 0(r3)
/* 8011D830 0011A790  C0 7E 00 04 */	lfs f3, 4(r30)
/* 8011D834 0011A794  C0 43 00 04 */	lfs f2, 4(r3)
/* 8011D838 0011A798  EC 01 00 2A */	fadds f0, f1, f0
/* 8011D83C 0011A79C  C0 9E 00 08 */	lfs f4, 8(r30)
/* 8011D840 0011A7A0  C0 23 00 08 */	lfs f1, 8(r3)
/* 8011D844 0011A7A4  EC 43 10 2A */	fadds f2, f3, f2
/* 8011D848 0011A7A8  D0 1F 00 00 */	stfs f0, 0(r31)
/* 8011D84C 0011A7AC  EC 04 08 2A */	fadds f0, f4, f1
/* 8011D850 0011A7B0  D0 5F 00 04 */	stfs f2, 4(r31)
/* 8011D854 0011A7B4  D0 1F 00 08 */	stfs f0, 8(r31)
/* 8011D858 0011A7B8  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8011D85C 0011A7BC  CB E1 00 40 */	lfd f31, 0x40(r1)
/* 8011D860 0011A7C0  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8011D864 0011A7C4  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8011D868 0011A7C8  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8011D86C 0011A7CC  38 21 00 48 */	addi r1, r1, 0x48
/* 8011D870 0011A7D0  7C 08 03 A6 */	mtlr r0
/* 8011D874 0011A7D4  4E 80 00 20 */	blr 
.endfn outputVerticalPosition__6NPlaneFR9NVector3fR9NVector3f

.fn transform__6NPlaneFR12NTransform3D, global
/* 8011D878 0011A7D8  7C 08 02 A6 */	mflr r0
/* 8011D87C 0011A7DC  90 01 00 04 */	stw r0, 4(r1)
/* 8011D880 0011A7E0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8011D884 0011A7E4  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8011D888 0011A7E8  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8011D88C 0011A7EC  3B C4 00 00 */	addi r30, r4, 0
/* 8011D890 0011A7F0  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8011D894 0011A7F4  3B A3 00 00 */	addi r29, r3, 0
/* 8011D898 0011A7F8  38 61 00 14 */	addi r3, r1, 0x14
/* 8011D89C 0011A7FC  4B FF F5 B9 */	bl __ct__9NVector3fFv
/* 8011D8A0 0011A800  C0 3D 00 10 */	lfs f1, 0x10(r29)
/* 8011D8A4 0011A804  7C 7F 1B 78 */	mr r31, r3
/* 8011D8A8 0011A808  C0 1D 00 04 */	lfs f0, 4(r29)
/* 8011D8AC 0011A80C  38 7E 00 00 */	addi r3, r30, 0
/* 8011D8B0 0011A810  FC 20 08 50 */	fneg f1, f1
/* 8011D8B4 0011A814  38 9D 00 04 */	addi r4, r29, 4
/* 8011D8B8 0011A818  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011D8BC 0011A81C  D0 1F 00 00 */	stfs f0, 0(r31)
/* 8011D8C0 0011A820  C0 1D 00 08 */	lfs f0, 8(r29)
/* 8011D8C4 0011A824  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011D8C8 0011A828  D0 1F 00 04 */	stfs f0, 4(r31)
/* 8011D8CC 0011A82C  C0 1D 00 0C */	lfs f0, 0xc(r29)
/* 8011D8D0 0011A830  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011D8D4 0011A834  D0 1F 00 08 */	stfs f0, 8(r31)
/* 8011D8D8 0011A838  4B FF F2 31 */	bl rotate__12NTransform3DFR8Vector3f
/* 8011D8DC 0011A83C  38 7E 00 00 */	addi r3, r30, 0
/* 8011D8E0 0011A840  38 9F 00 00 */	addi r4, r31, 0
/* 8011D8E4 0011A844  4B FF F3 C1 */	bl transform__12NTransform3DFR8Vector3f
/* 8011D8E8 0011A848  C0 7D 00 04 */	lfs f3, 4(r29)
/* 8011D8EC 0011A84C  C0 5F 00 00 */	lfs f2, 0(r31)
/* 8011D8F0 0011A850  C0 3D 00 08 */	lfs f1, 8(r29)
/* 8011D8F4 0011A854  C0 1F 00 04 */	lfs f0, 4(r31)
/* 8011D8F8 0011A858  EC 43 00 B2 */	fmuls f2, f3, f2
/* 8011D8FC 0011A85C  C0 7D 00 0C */	lfs f3, 0xc(r29)
/* 8011D900 0011A860  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011D904 0011A864  C0 3F 00 08 */	lfs f1, 8(r31)
/* 8011D908 0011A868  EC 23 00 72 */	fmuls f1, f3, f1
/* 8011D90C 0011A86C  EC 02 00 2A */	fadds f0, f2, f0
/* 8011D910 0011A870  EC 01 00 2A */	fadds f0, f1, f0
/* 8011D914 0011A874  FC 00 00 50 */	fneg f0, f0
/* 8011D918 0011A878  D0 1D 00 10 */	stfs f0, 0x10(r29)
/* 8011D91C 0011A87C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8011D920 0011A880  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8011D924 0011A884  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8011D928 0011A888  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8011D92C 0011A88C  38 21 00 30 */	addi r1, r1, 0x30
/* 8011D930 0011A890  7C 08 03 A6 */	mtlr r0
/* 8011D934 0011A894  4E 80 00 20 */	blr 
.endfn transform__6NPlaneFR12NTransform3D

.fn println__6NPlaneFv, global
/* 8011D938 0011A898  7C 08 02 A6 */	mflr r0
/* 8011D93C 0011A89C  38 63 00 04 */	addi r3, r3, 4
/* 8011D940 0011A8A0  90 01 00 04 */	stw r0, 4(r1)
/* 8011D944 0011A8A4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8011D948 0011A8A8  4B FF F6 CD */	bl println__9NVector3fFv
/* 8011D94C 0011A8AC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8011D950 0011A8B0  38 21 00 08 */	addi r1, r1, 8
/* 8011D954 0011A8B4  7C 08 03 A6 */	mtlr r0
/* 8011D958 0011A8B8  4E 80 00 20 */	blr 
.endfn println__6NPlaneFv

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 8
.obj __vt__6NPlane, global
	.4byte __RTTI__6NPlane
	.4byte 0
	.4byte transform__6NPlaneFR12NTransform3D
	.4byte println__6NPlaneFv
.endobj __vt__6NPlane
.obj __vt__5NLine, global
	.4byte __RTTI__5NLine
	.4byte 0
	.4byte transform__5NLineFR12NTransform3D
	.4byte println__5NLineFv
.endobj __vt__5NLine

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.balign 8
.obj lbl_803E3038, local
	.asciz "NLine"
.endobj lbl_803E3038
.balign 4
.obj __RTTI__5NLine, local
	.4byte lbl_803E3038
	.4byte 0
.endobj __RTTI__5NLine
.balign 4
.obj lbl_803E3048, local
	.asciz "NPlane"
.endobj lbl_803E3048
.balign 4
.obj __RTTI__6NPlane, local
	.4byte lbl_803E3048
	.4byte 0
.endobj __RTTI__6NPlane
