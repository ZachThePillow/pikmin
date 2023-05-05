.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.fn __ct__6ActBouFP4Piki, global
/* 800AC79C 000A96FC  7C 08 02 A6 */	mflr r0
/* 800AC7A0 000A9700  38 A0 00 01 */	li r5, 1
/* 800AC7A4 000A9704  90 01 00 04 */	stw r0, 4(r1)
/* 800AC7A8 000A9708  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800AC7AC 000A970C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800AC7B0 000A9710  3B E3 00 00 */	addi r31, r3, 0
/* 800AC7B4 000A9714  48 01 76 1D */	bl __ct__6ActionFP4Pikib
/* 800AC7B8 000A9718  3C 60 80 2B */	lis r3, __vt__6ActBou@ha
/* 800AC7BC 000A971C  38 03 5B 4C */	addi r0, r3, __vt__6ActBou@l
/* 800AC7C0 000A9720  90 1F 00 00 */	stw r0, 0(r31)
/* 800AC7C4 000A9724  38 8D B1 40 */	addi r4, r13, lbl_803DFE60@sda21
/* 800AC7C8 000A9728  38 00 FF FF */	li r0, -1
/* 800AC7CC 000A972C  C0 02 8F 40 */	lfs f0, lbl_803E9140@sda21(r2)
/* 800AC7D0 000A9730  7F E3 FB 78 */	mr r3, r31
/* 800AC7D4 000A9734  D0 1F 00 20 */	stfs f0, 0x20(r31)
/* 800AC7D8 000A9738  D0 1F 00 1C */	stfs f0, 0x1c(r31)
/* 800AC7DC 000A973C  D0 1F 00 18 */	stfs f0, 0x18(r31)
/* 800AC7E0 000A9740  D0 1F 00 30 */	stfs f0, 0x30(r31)
/* 800AC7E4 000A9744  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800AC7E8 000A9748  D0 1F 00 28 */	stfs f0, 0x28(r31)
/* 800AC7EC 000A974C  90 9F 00 10 */	stw r4, 0x10(r31)
/* 800AC7F0 000A9750  B0 1F 00 08 */	sth r0, 8(r31)
/* 800AC7F4 000A9754  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800AC7F8 000A9758  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800AC7FC 000A975C  38 21 00 18 */	addi r1, r1, 0x18
/* 800AC800 000A9760  7C 08 03 A6 */	mtlr r0
/* 800AC804 000A9764  4E 80 00 20 */	blr 
.endfn __ct__6ActBouFP4Piki

.fn init__6ActBouFP8Creature, global
/* 800AC808 000A9768  7C 08 02 A6 */	mflr r0
/* 800AC80C 000A976C  28 04 00 00 */	cmplwi r4, 0
/* 800AC810 000A9770  90 01 00 04 */	stw r0, 4(r1)
/* 800AC814 000A9774  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800AC818 000A9778  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800AC81C 000A977C  93 C1 00 30 */	stw r30, 0x30(r1)
/* 800AC820 000A9780  3B C3 00 00 */	addi r30, r3, 0
/* 800AC824 000A9784  41 82 00 14 */	beq .L_800AC838
/* 800AC828 000A9788  80 04 00 6C */	lwz r0, 0x6c(r4)
/* 800AC82C 000A978C  2C 00 00 1D */	cmpwi r0, 0x1d
/* 800AC830 000A9790  40 82 00 08 */	bne .L_800AC838
/* 800AC834 000A9794  90 9E 00 24 */	stw r4, 0x24(r30)
.L_800AC838:
/* 800AC838 000A9798  38 00 00 00 */	li r0, 0
/* 800AC83C 000A979C  B0 1E 00 14 */	sth r0, 0x14(r30)
/* 800AC840 000A97A0  38 61 00 1C */	addi r3, r1, 0x1c
/* 800AC844 000A97A4  38 80 00 02 */	li r4, 2
/* 800AC848 000A97A8  48 07 27 11 */	bl __ct__14PaniMotionInfoFi
/* 800AC84C 000A97AC  3B E3 00 00 */	addi r31, r3, 0
/* 800AC850 000A97B0  38 61 00 24 */	addi r3, r1, 0x24
/* 800AC854 000A97B4  38 80 00 02 */	li r4, 2
/* 800AC858 000A97B8  48 07 27 01 */	bl __ct__14PaniMotionInfoFi
/* 800AC85C 000A97BC  7C 64 1B 78 */	mr r4, r3
/* 800AC860 000A97C0  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 800AC864 000A97C4  7F E5 FB 78 */	mr r5, r31
/* 800AC868 000A97C8  48 01 E1 71 */	bl startMotion__4PikiFR14PaniMotionInfoR14PaniMotionInfo
/* 800AC86C 000A97CC  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 800AC870 000A97D0  80 03 02 AC */	lwz r0, 0x2ac(r3)
/* 800AC874 000A97D4  28 00 00 00 */	cmplwi r0, 0
/* 800AC878 000A97D8  41 82 00 10 */	beq .L_800AC888
/* 800AC87C 000A97DC  38 00 00 03 */	li r0, 3
/* 800AC880 000A97E0  98 03 04 08 */	stb r0, 0x408(r3)
/* 800AC884 000A97E4  48 00 00 0C */	b .L_800AC890
.L_800AC888:
/* 800AC888 000A97E8  38 00 00 02 */	li r0, 2
/* 800AC88C 000A97EC  98 03 04 08 */	stb r0, 0x408(r3)
.L_800AC890:
/* 800AC890 000A97F0  38 00 00 78 */	li r0, 0x78
/* 800AC894 000A97F4  B0 1E 00 16 */	sth r0, 0x16(r30)
/* 800AC898 000A97F8  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800AC89C 000A97FC  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 800AC8A0 000A9800  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 800AC8A4 000A9804  38 21 00 38 */	addi r1, r1, 0x38
/* 800AC8A8 000A9808  7C 08 03 A6 */	mtlr r0
/* 800AC8AC 000A980C  4E 80 00 20 */	blr 
.endfn init__6ActBouFP8Creature

.fn exec__6ActBouFv, global
/* 800AC8B0 000A9810  7C 08 02 A6 */	mflr r0
/* 800AC8B4 000A9814  90 01 00 04 */	stw r0, 4(r1)
/* 800AC8B8 000A9818  94 21 FF F8 */	stwu r1, -8(r1)
/* 800AC8BC 000A981C  A0 03 00 14 */	lhz r0, 0x14(r3)
/* 800AC8C0 000A9820  2C 00 00 01 */	cmpwi r0, 1
/* 800AC8C4 000A9824  41 82 00 1C */	beq .L_800AC8E0
/* 800AC8C8 000A9828  40 80 00 20 */	bge .L_800AC8E8
/* 800AC8CC 000A982C  2C 00 00 00 */	cmpwi r0, 0
/* 800AC8D0 000A9830  40 80 00 08 */	bge .L_800AC8D8
/* 800AC8D4 000A9834  48 00 00 14 */	b .L_800AC8E8
.L_800AC8D8:
/* 800AC8D8 000A9838  48 00 00 25 */	bl gotoLeg__6ActBouFv
/* 800AC8DC 000A983C  48 00 00 10 */	b .L_800AC8EC
.L_800AC8E0:
/* 800AC8E0 000A9840  48 00 03 AD */	bl climb__6ActBouFv
/* 800AC8E4 000A9844  48 00 00 08 */	b .L_800AC8EC
.L_800AC8E8:
/* 800AC8E8 000A9848  38 60 00 00 */	li r3, 0
.L_800AC8EC:
/* 800AC8EC 000A984C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800AC8F0 000A9850  38 21 00 08 */	addi r1, r1, 8
/* 800AC8F4 000A9854  7C 08 03 A6 */	mtlr r0
/* 800AC8F8 000A9858  4E 80 00 20 */	blr 
.endfn exec__6ActBouFv

.fn gotoLeg__6ActBouFv, global
/* 800AC8FC 000A985C  7C 08 02 A6 */	mflr r0
/* 800AC900 000A9860  90 01 00 04 */	stw r0, 4(r1)
/* 800AC904 000A9864  94 21 FF 68 */	stwu r1, -0x98(r1)
/* 800AC908 000A9868  93 E1 00 94 */	stw r31, 0x94(r1)
/* 800AC90C 000A986C  7C 7F 1B 78 */	mr r31, r3
/* 800AC910 000A9870  93 C1 00 90 */	stw r30, 0x90(r1)
/* 800AC914 000A9874  80 63 00 0C */	lwz r3, 0xc(r3)
/* 800AC918 000A9878  80 03 01 88 */	lwz r0, 0x188(r3)
/* 800AC91C 000A987C  28 00 00 00 */	cmplwi r0, 0
/* 800AC920 000A9880  41 82 01 0C */	beq .L_800ACA2C
/* 800AC924 000A9884  38 00 00 01 */	li r0, 1
/* 800AC928 000A9888  B0 1F 00 14 */	sth r0, 0x14(r31)
/* 800AC92C 000A988C  38 61 00 38 */	addi r3, r1, 0x38
/* 800AC930 000A9890  38 80 00 3E */	li r4, 0x3e
/* 800AC934 000A9894  80 BF 00 0C */	lwz r5, 0xc(r31)
/* 800AC938 000A9898  C0 0D B1 44 */	lfs f0, lbl_803DFE64@sda21(r13)
/* 800AC93C 000A989C  D4 05 00 70 */	stfsu f0, 0x70(r5)
/* 800AC940 000A98A0  C0 0D B1 48 */	lfs f0, lbl_803DFE68@sda21(r13)
/* 800AC944 000A98A4  D0 05 00 04 */	stfs f0, 4(r5)
/* 800AC948 000A98A8  C0 0D B1 4C */	lfs f0, lbl_803DFE6C@sda21(r13)
/* 800AC94C 000A98AC  D0 05 00 08 */	stfs f0, 8(r5)
/* 800AC950 000A98B0  80 BF 00 0C */	lwz r5, 0xc(r31)
/* 800AC954 000A98B4  C0 0D B1 50 */	lfs f0, lbl_803DFE70@sda21(r13)
/* 800AC958 000A98B8  D4 05 00 A4 */	stfsu f0, 0xa4(r5)
/* 800AC95C 000A98BC  C0 0D B1 54 */	lfs f0, lbl_803DFE74@sda21(r13)
/* 800AC960 000A98C0  D0 05 00 04 */	stfs f0, 4(r5)
/* 800AC964 000A98C4  C0 0D B1 58 */	lfs f0, lbl_803DFE78@sda21(r13)
/* 800AC968 000A98C8  D0 05 00 08 */	stfs f0, 8(r5)
/* 800AC96C 000A98CC  48 07 25 ED */	bl __ct__14PaniMotionInfoFi
/* 800AC970 000A98D0  3B C3 00 00 */	addi r30, r3, 0
/* 800AC974 000A98D4  38 61 00 40 */	addi r3, r1, 0x40
/* 800AC978 000A98D8  38 80 00 3E */	li r4, 0x3e
/* 800AC97C 000A98DC  48 07 25 DD */	bl __ct__14PaniMotionInfoFi
/* 800AC980 000A98E0  7C 64 1B 78 */	mr r4, r3
/* 800AC984 000A98E4  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 800AC988 000A98E8  7F C5 F3 78 */	mr r5, r30
/* 800AC98C 000A98EC  48 01 E0 4D */	bl startMotion__4PikiFR14PaniMotionInfoR14PaniMotionInfo
/* 800AC990 000A98F0  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 800AC994 000A98F4  80 03 00 C8 */	lwz r0, 0xc8(r3)
/* 800AC998 000A98F8  60 00 00 80 */	ori r0, r0, 0x80
/* 800AC99C 000A98FC  90 03 00 C8 */	stw r0, 0xc8(r3)
/* 800AC9A0 000A9900  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 800AC9A4 000A9904  48 02 CD 21 */	bl finishLook__4PikiFv
/* 800AC9A8 000A9908  C0 02 8F 40 */	lfs f0, lbl_803E9140@sda21(r2)
/* 800AC9AC 000A990C  38 81 00 70 */	addi r4, r1, 0x70
/* 800AC9B0 000A9910  D0 01 00 78 */	stfs f0, 0x78(r1)
/* 800AC9B4 000A9914  D0 01 00 74 */	stfs f0, 0x74(r1)
/* 800AC9B8 000A9918  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 800AC9BC 000A991C  D0 01 00 84 */	stfs f0, 0x84(r1)
/* 800AC9C0 000A9920  D0 01 00 80 */	stfs f0, 0x80(r1)
/* 800AC9C4 000A9924  D0 01 00 7C */	stfs f0, 0x7c(r1)
/* 800AC9C8 000A9928  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 800AC9CC 000A992C  80 63 01 88 */	lwz r3, 0x188(r3)
/* 800AC9D0 000A9930  4B FD C1 BD */	bl makeTube__8CollPartFR4Tube
/* 800AC9D4 000A9934  C0 02 8F 40 */	lfs f0, lbl_803E9140@sda21(r2)
/* 800AC9D8 000A9938  38 61 00 70 */	addi r3, r1, 0x70
/* 800AC9DC 000A993C  38 A1 00 64 */	addi r5, r1, 0x64
/* 800AC9E0 000A9940  D0 01 00 6C */	stfs f0, 0x6c(r1)
/* 800AC9E4 000A9944  38 C1 00 58 */	addi r6, r1, 0x58
/* 800AC9E8 000A9948  D0 01 00 60 */	stfs f0, 0x60(r1)
/* 800AC9EC 000A994C  D0 01 00 68 */	stfs f0, 0x68(r1)
/* 800AC9F0 000A9950  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 800AC9F4 000A9954  D0 01 00 64 */	stfs f0, 0x64(r1)
/* 800AC9F8 000A9958  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 800AC9FC 000A995C  80 9F 00 0C */	lwz r4, 0xc(r31)
/* 800ACA00 000A9960  C0 24 01 94 */	lfs f1, 0x194(r4)
/* 800ACA04 000A9964  38 84 00 94 */	addi r4, r4, 0x94
/* 800ACA08 000A9968  4B FD AE 89 */	bl getPosGradient__4TubeFR8Vector3ffR8Vector3fR8Vector3f
/* 800ACA0C 000A996C  80 81 00 58 */	lwz r4, 0x58(r1)
/* 800ACA10 000A9970  38 60 00 00 */	li r3, 0
/* 800ACA14 000A9974  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 800ACA18 000A9978  90 9F 00 18 */	stw r4, 0x18(r31)
/* 800ACA1C 000A997C  90 1F 00 1C */	stw r0, 0x1c(r31)
/* 800ACA20 000A9980  80 01 00 60 */	lwz r0, 0x60(r1)
/* 800ACA24 000A9984  90 1F 00 20 */	stw r0, 0x20(r31)
/* 800ACA28 000A9988  48 00 00 CC */	b .L_800ACAF4
.L_800ACA2C:
/* 800ACA2C 000A998C  A8 7F 00 16 */	lha r3, 0x16(r31)
/* 800ACA30 000A9990  38 63 FF FF */	addi r3, r3, -1
/* 800ACA34 000A9994  7C 60 07 35 */	extsh. r0, r3
/* 800ACA38 000A9998  B0 7F 00 16 */	sth r3, 0x16(r31)
/* 800ACA3C 000A999C  41 81 00 18 */	bgt .L_800ACA54
/* 800ACA40 000A99A0  80 9F 00 0C */	lwz r4, 0xc(r31)
/* 800ACA44 000A99A4  38 00 00 01 */	li r0, 1
/* 800ACA48 000A99A8  38 60 00 01 */	li r3, 1
/* 800ACA4C 000A99AC  98 04 04 00 */	stb r0, 0x400(r4)
/* 800ACA50 000A99B0  48 00 00 A4 */	b .L_800ACAF4
.L_800ACA54:
/* 800ACA54 000A99B4  80 9F 00 0C */	lwz r4, 0xc(r31)
/* 800ACA58 000A99B8  80 7F 00 24 */	lwz r3, 0x24(r31)
/* 800ACA5C 000A99BC  C4 23 00 94 */	lfsu f1, 0x94(r3)
/* 800ACA60 000A99C0  C4 04 00 94 */	lfsu f0, 0x94(r4)
/* 800ACA64 000A99C4  C0 63 00 04 */	lfs f3, 4(r3)
/* 800ACA68 000A99C8  C0 44 00 04 */	lfs f2, 4(r4)
/* 800ACA6C 000A99CC  EC 01 00 28 */	fsubs f0, f1, f0
/* 800ACA70 000A99D0  C0 83 00 08 */	lfs f4, 8(r3)
/* 800ACA74 000A99D4  C0 24 00 08 */	lfs f1, 8(r4)
/* 800ACA78 000A99D8  EC 43 10 28 */	fsubs f2, f3, f2
/* 800ACA7C 000A99DC  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 800ACA80 000A99E0  EC 04 08 28 */	fsubs f0, f4, f1
/* 800ACA84 000A99E4  D0 41 00 50 */	stfs f2, 0x50(r1)
/* 800ACA88 000A99E8  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 800ACA8C 000A99EC  C0 21 00 4C */	lfs f1, 0x4c(r1)
/* 800ACA90 000A99F0  C0 01 00 50 */	lfs f0, 0x50(r1)
/* 800ACA94 000A99F4  C0 41 00 54 */	lfs f2, 0x54(r1)
/* 800ACA98 000A99F8  EC 21 00 72 */	fmuls f1, f1, f1
/* 800ACA9C 000A99FC  EC 00 00 32 */	fmuls f0, f0, f0
/* 800ACAA0 000A9A00  EC 42 00 B2 */	fmuls f2, f2, f2
/* 800ACAA4 000A9A04  EC 01 00 2A */	fadds f0, f1, f0
/* 800ACAA8 000A9A08  EC 22 00 2A */	fadds f1, f2, f0
/* 800ACAAC 000A9A0C  4B F6 11 95 */	bl sqrtf__3stdFf
/* 800ACAB0 000A9A10  C0 02 8F 40 */	lfs f0, lbl_803E9140@sda21(r2)
/* 800ACAB4 000A9A14  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800ACAB8 000A9A18  41 82 00 28 */	beq .L_800ACAE0
/* 800ACABC 000A9A1C  C0 01 00 4C */	lfs f0, 0x4c(r1)
/* 800ACAC0 000A9A20  EC 00 08 24 */	fdivs f0, f0, f1
/* 800ACAC4 000A9A24  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 800ACAC8 000A9A28  C0 01 00 50 */	lfs f0, 0x50(r1)
/* 800ACACC 000A9A2C  EC 00 08 24 */	fdivs f0, f0, f1
/* 800ACAD0 000A9A30  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 800ACAD4 000A9A34  C0 01 00 54 */	lfs f0, 0x54(r1)
/* 800ACAD8 000A9A38  EC 00 08 24 */	fdivs f0, f0, f1
/* 800ACADC 000A9A3C  D0 01 00 54 */	stfs f0, 0x54(r1)
.L_800ACAE0:
/* 800ACAE0 000A9A40  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 800ACAE4 000A9A44  38 81 00 4C */	addi r4, r1, 0x4c
/* 800ACAE8 000A9A48  C0 22 8F 44 */	lfs f1, lbl_803E9144@sda21(r2)
/* 800ACAEC 000A9A4C  48 01 F2 ED */	bl setSpeed__4PikiFfR8Vector3f
/* 800ACAF0 000A9A50  38 60 00 00 */	li r3, 0
.L_800ACAF4:
/* 800ACAF4 000A9A54  80 01 00 9C */	lwz r0, 0x9c(r1)
/* 800ACAF8 000A9A58  83 E1 00 94 */	lwz r31, 0x94(r1)
/* 800ACAFC 000A9A5C  83 C1 00 90 */	lwz r30, 0x90(r1)
/* 800ACB00 000A9A60  38 21 00 98 */	addi r1, r1, 0x98
/* 800ACB04 000A9A64  7C 08 03 A6 */	mtlr r0
/* 800ACB08 000A9A68  4E 80 00 20 */	blr 
.endfn gotoLeg__6ActBouFv

.fn procCollideMsg__6ActBouFP4PikiP10MsgCollide, global
/* 800ACB0C 000A9A6C  7C 08 02 A6 */	mflr r0
/* 800ACB10 000A9A70  90 01 00 04 */	stw r0, 4(r1)
/* 800ACB14 000A9A74  94 21 FF 68 */	stwu r1, -0x98(r1)
/* 800ACB18 000A9A78  DB E1 00 90 */	stfd f31, 0x90(r1)
/* 800ACB1C 000A9A7C  DB C1 00 88 */	stfd f30, 0x88(r1)
/* 800ACB20 000A9A80  DB A1 00 80 */	stfd f29, 0x80(r1)
/* 800ACB24 000A9A84  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 800ACB28 000A9A88  3B E5 00 00 */	addi r31, r5, 0
/* 800ACB2C 000A9A8C  93 C1 00 78 */	stw r30, 0x78(r1)
/* 800ACB30 000A9A90  3B C3 00 00 */	addi r30, r3, 0
/* 800ACB34 000A9A94  80 03 00 24 */	lwz r0, 0x24(r3)
/* 800ACB38 000A9A98  80 65 00 04 */	lwz r3, 4(r5)
/* 800ACB3C 000A9A9C  7C 03 00 40 */	cmplw r3, r0
/* 800ACB40 000A9AA0  40 82 01 28 */	bne .L_800ACC68
/* 800ACB44 000A9AA4  80 1F 00 08 */	lwz r0, 8(r31)
/* 800ACB48 000A9AA8  28 00 00 00 */	cmplwi r0, 0
/* 800ACB4C 000A9AAC  41 82 01 1C */	beq .L_800ACC68
/* 800ACB50 000A9AB0  80 9E 00 0C */	lwz r4, 0xc(r30)
/* 800ACB54 000A9AB4  80 04 01 84 */	lwz r0, 0x184(r4)
/* 800ACB58 000A9AB8  28 00 00 00 */	cmplwi r0, 0
/* 800ACB5C 000A9ABC  40 82 01 0C */	bne .L_800ACC68
/* 800ACB60 000A9AC0  81 84 00 00 */	lwz r12, 0(r4)
/* 800ACB64 000A9AC4  38 61 00 18 */	addi r3, r1, 0x18
/* 800ACB68 000A9AC8  81 8C 00 58 */	lwz r12, 0x58(r12)
/* 800ACB6C 000A9ACC  7D 88 03 A6 */	mtlr r12
/* 800ACB70 000A9AD0  4E 80 00 21 */	blrl 
/* 800ACB74 000A9AD4  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 800ACB78 000A9AD8  C3 E1 00 18 */	lfs f31, 0x18(r1)
/* 800ACB7C 000A9ADC  81 83 00 00 */	lwz r12, 0(r3)
/* 800ACB80 000A9AE0  C3 C1 00 1C */	lfs f30, 0x1c(r1)
/* 800ACB84 000A9AE4  81 8C 00 5C */	lwz r12, 0x5c(r12)
/* 800ACB88 000A9AE8  C3 A1 00 20 */	lfs f29, 0x20(r1)
/* 800ACB8C 000A9AEC  7D 88 03 A6 */	mtlr r12
/* 800ACB90 000A9AF0  4E 80 00 21 */	blrl 
/* 800ACB94 000A9AF4  C0 02 8F 40 */	lfs f0, lbl_803E9140@sda21(r2)
/* 800ACB98 000A9AF8  38 81 00 38 */	addi r4, r1, 0x38
/* 800ACB9C 000A9AFC  D3 E1 00 58 */	stfs f31, 0x58(r1)
/* 800ACBA0 000A9B00  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 800ACBA4 000A9B04  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 800ACBA8 000A9B08  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 800ACBAC 000A9B0C  D3 C1 00 5C */	stfs f30, 0x5c(r1)
/* 800ACBB0 000A9B10  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 800ACBB4 000A9B14  D3 A1 00 60 */	stfs f29, 0x60(r1)
/* 800ACBB8 000A9B18  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 800ACBBC 000A9B1C  D0 21 00 64 */	stfs f1, 0x64(r1)
/* 800ACBC0 000A9B20  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 800ACBC4 000A9B24  80 7F 00 08 */	lwz r3, 8(r31)
/* 800ACBC8 000A9B28  4B FD BF C5 */	bl makeTube__8CollPartFR4Tube
/* 800ACBCC 000A9B2C  80 9E 00 24 */	lwz r4, 0x24(r30)
/* 800ACBD0 000A9B30  38 61 00 38 */	addi r3, r1, 0x38
/* 800ACBD4 000A9B34  C0 22 8F 48 */	lfs f1, lbl_803E9148@sda21(r2)
/* 800ACBD8 000A9B38  C0 04 00 98 */	lfs f0, 0x98(r4)
/* 800ACBDC 000A9B3C  EC 21 00 2A */	fadds f1, f1, f0
/* 800ACBE0 000A9B40  4B FD A7 81 */	bl getYRatio__4TubeFf
/* 800ACBE4 000A9B44  C0 02 8F 40 */	lfs f0, lbl_803E9140@sda21(r2)
/* 800ACBE8 000A9B48  38 61 00 38 */	addi r3, r1, 0x38
/* 800ACBEC 000A9B4C  38 81 00 58 */	addi r4, r1, 0x58
/* 800ACBF0 000A9B50  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 800ACBF4 000A9B54  38 A1 00 28 */	addi r5, r1, 0x28
/* 800ACBF8 000A9B58  38 C1 00 24 */	addi r6, r1, 0x24
/* 800ACBFC 000A9B5C  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 800ACC00 000A9B60  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 800ACC04 000A9B64  4B FD A7 89 */	bl collide__4TubeFRC6SphereR8Vector3fRf
/* 800ACC08 000A9B68  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800ACC0C 000A9B6C  41 82 00 5C */	beq .L_800ACC68
/* 800ACC10 000A9B70  38 00 00 78 */	li r0, 0x78
/* 800ACC14 000A9B74  B0 1E 00 16 */	sth r0, 0x16(r30)
/* 800ACC18 000A9B78  38 C0 FF FF */	li r6, -1
/* 800ACC1C 000A9B7C  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 800ACC20 000A9B80  80 9F 00 04 */	lwz r4, 4(r31)
/* 800ACC24 000A9B84  80 BF 00 08 */	lwz r5, 8(r31)
/* 800ACC28 000A9B88  C0 22 8F 40 */	lfs f1, lbl_803E9140@sda21(r2)
/* 800ACC2C 000A9B8C  4B FE 3A 8D */	bl startStickObject__8CreatureFP8CreatureP8CollPartif
/* 800ACC30 000A9B90  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 800ACC34 000A9B94  48 02 CA 91 */	bl finishLook__4PikiFv
/* 800ACC38 000A9B98  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 800ACC3C 000A9B9C  C0 22 8F 4C */	lfs f1, lbl_803E914C@sda21(r2)
/* 800ACC40 000A9BA0  C0 42 8F 50 */	lfs f2, lbl_803E9150@sda21(r2)
/* 800ACC44 000A9BA4  38 63 02 BC */	addi r3, r3, 0x2bc
/* 800ACC48 000A9BA8  48 02 0B CD */	bl start__8OdoMeterFff
/* 800ACC4C 000A9BAC  80 9E 00 0C */	lwz r4, 0xc(r30)
/* 800ACC50 000A9BB0  80 64 00 94 */	lwz r3, 0x94(r4)
/* 800ACC54 000A9BB4  80 04 00 98 */	lwz r0, 0x98(r4)
/* 800ACC58 000A9BB8  90 7E 00 28 */	stw r3, 0x28(r30)
/* 800ACC5C 000A9BBC  90 1E 00 2C */	stw r0, 0x2c(r30)
/* 800ACC60 000A9BC0  80 04 00 9C */	lwz r0, 0x9c(r4)
/* 800ACC64 000A9BC4  90 1E 00 30 */	stw r0, 0x30(r30)
.L_800ACC68:
/* 800ACC68 000A9BC8  80 01 00 9C */	lwz r0, 0x9c(r1)
/* 800ACC6C 000A9BCC  CB E1 00 90 */	lfd f31, 0x90(r1)
/* 800ACC70 000A9BD0  CB C1 00 88 */	lfd f30, 0x88(r1)
/* 800ACC74 000A9BD4  CB A1 00 80 */	lfd f29, 0x80(r1)
/* 800ACC78 000A9BD8  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 800ACC7C 000A9BDC  83 C1 00 78 */	lwz r30, 0x78(r1)
/* 800ACC80 000A9BE0  38 21 00 98 */	addi r1, r1, 0x98
/* 800ACC84 000A9BE4  7C 08 03 A6 */	mtlr r0
/* 800ACC88 000A9BE8  4E 80 00 20 */	blr 
.endfn procCollideMsg__6ActBouFP4PikiP10MsgCollide

.fn climb__6ActBouFv, global
/* 800ACC8C 000A9BEC  7C 08 02 A6 */	mflr r0
/* 800ACC90 000A9BF0  90 01 00 04 */	stw r0, 4(r1)
/* 800ACC94 000A9BF4  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 800ACC98 000A9BF8  93 E1 00 44 */	stw r31, 0x44(r1)
/* 800ACC9C 000A9BFC  7C 7F 1B 78 */	mr r31, r3
/* 800ACCA0 000A9C00  80 83 00 0C */	lwz r4, 0xc(r3)
/* 800ACCA4 000A9C04  80 04 01 88 */	lwz r0, 0x188(r4)
/* 800ACCA8 000A9C08  28 00 00 00 */	cmplwi r0, 0
/* 800ACCAC 000A9C0C  40 82 00 0C */	bne .L_800ACCB8
/* 800ACCB0 000A9C10  38 60 00 01 */	li r3, 1
/* 800ACCB4 000A9C14  48 00 00 CC */	b .L_800ACD80
.L_800ACCB8:
/* 800ACCB8 000A9C18  38 64 02 BC */	addi r3, r4, 0x2bc
/* 800ACCBC 000A9C1C  38 84 00 94 */	addi r4, r4, 0x94
/* 800ACCC0 000A9C20  38 BF 00 28 */	addi r5, r31, 0x28
/* 800ACCC4 000A9C24  48 02 0B 69 */	bl moving__8OdoMeterFR8Vector3fR8Vector3f
/* 800ACCC8 000A9C28  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800ACCCC 000A9C2C  40 82 00 0C */	bne .L_800ACCD8
/* 800ACCD0 000A9C30  38 60 00 01 */	li r3, 1
/* 800ACCD4 000A9C34  48 00 00 AC */	b .L_800ACD80
.L_800ACCD8:
/* 800ACCD8 000A9C38  80 9F 00 0C */	lwz r4, 0xc(r31)
/* 800ACCDC 000A9C3C  80 64 00 94 */	lwz r3, 0x94(r4)
/* 800ACCE0 000A9C40  80 04 00 98 */	lwz r0, 0x98(r4)
/* 800ACCE4 000A9C44  90 7F 00 28 */	stw r3, 0x28(r31)
/* 800ACCE8 000A9C48  90 1F 00 2C */	stw r0, 0x2c(r31)
/* 800ACCEC 000A9C4C  80 04 00 9C */	lwz r0, 0x9c(r4)
/* 800ACCF0 000A9C50  90 1F 00 30 */	stw r0, 0x30(r31)
/* 800ACCF4 000A9C54  48 16 B3 7D */	bl rand
/* 800ACCF8 000A9C58  6C 60 80 00 */	xoris r0, r3, 0x8000
/* 800ACCFC 000A9C5C  C8 42 8F 60 */	lfd f2, lbl_803E9160@sda21(r2)
/* 800ACD00 000A9C60  90 01 00 3C */	stw r0, 0x3c(r1)
/* 800ACD04 000A9C64  3C 00 43 30 */	lis r0, 0x4330
/* 800ACD08 000A9C68  C0 82 8F 54 */	lfs f4, lbl_803E9154@sda21(r2)
/* 800ACD0C 000A9C6C  38 60 00 00 */	li r3, 0
/* 800ACD10 000A9C70  90 01 00 38 */	stw r0, 0x38(r1)
/* 800ACD14 000A9C74  C0 62 8F 4C */	lfs f3, lbl_803E914C@sda21(r2)
/* 800ACD18 000A9C78  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 800ACD1C 000A9C7C  C0 22 8F 5C */	lfs f1, lbl_803E915C@sda21(r2)
/* 800ACD20 000A9C80  EC A0 10 28 */	fsubs f5, f0, f2
/* 800ACD24 000A9C84  C0 42 8F 58 */	lfs f2, lbl_803E9158@sda21(r2)
/* 800ACD28 000A9C88  C0 1F 00 18 */	lfs f0, 0x18(r31)
/* 800ACD2C 000A9C8C  EC 85 20 24 */	fdivs f4, f5, f4
/* 800ACD30 000A9C90  EC 63 01 32 */	fmuls f3, f3, f4
/* 800ACD34 000A9C94  EC 21 00 F2 */	fmuls f1, f1, f3
/* 800ACD38 000A9C98  EC 22 08 2A */	fadds f1, f2, f1
/* 800ACD3C 000A9C9C  EC 00 00 72 */	fmuls f0, f0, f1
/* 800ACD40 000A9CA0  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800ACD44 000A9CA4  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 800ACD48 000A9CA8  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 800ACD4C 000A9CAC  C0 1F 00 1C */	lfs f0, 0x1c(r31)
/* 800ACD50 000A9CB0  EC 00 00 72 */	fmuls f0, f0, f1
/* 800ACD54 000A9CB4  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 800ACD58 000A9CB8  C0 1F 00 20 */	lfs f0, 0x20(r31)
/* 800ACD5C 000A9CBC  EC 00 00 72 */	fmuls f0, f0, f1
/* 800ACD60 000A9CC0  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 800ACD64 000A9CC4  80 BF 00 0C */	lwz r5, 0xc(r31)
/* 800ACD68 000A9CC8  80 81 00 28 */	lwz r4, 0x28(r1)
/* 800ACD6C 000A9CCC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800ACD70 000A9CD0  90 85 00 70 */	stw r4, 0x70(r5)
/* 800ACD74 000A9CD4  90 05 00 74 */	stw r0, 0x74(r5)
/* 800ACD78 000A9CD8  80 01 00 30 */	lwz r0, 0x30(r1)
/* 800ACD7C 000A9CDC  90 05 00 78 */	stw r0, 0x78(r5)
.L_800ACD80:
/* 800ACD80 000A9CE0  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800ACD84 000A9CE4  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 800ACD88 000A9CE8  38 21 00 48 */	addi r1, r1, 0x48
/* 800ACD8C 000A9CEC  7C 08 03 A6 */	mtlr r0
/* 800ACD90 000A9CF0  4E 80 00 20 */	blr 
.endfn climb__6ActBouFv

.fn cleanup__6ActBouFv, global
/* 800ACD94 000A9CF4  7C 08 02 A6 */	mflr r0
/* 800ACD98 000A9CF8  90 01 00 04 */	stw r0, 4(r1)
/* 800ACD9C 000A9CFC  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800ACDA0 000A9D00  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800ACDA4 000A9D04  7C 7F 1B 78 */	mr r31, r3
/* 800ACDA8 000A9D08  C0 4D B1 5C */	lfs f2, lbl_803DFE7C@sda21(r13)
/* 800ACDAC 000A9D0C  C0 03 00 18 */	lfs f0, 0x18(r3)
/* 800ACDB0 000A9D10  C0 23 00 20 */	lfs f1, 0x20(r3)
/* 800ACDB4 000A9D14  EC 00 00 B2 */	fmuls f0, f0, f2
/* 800ACDB8 000A9D18  EC 21 00 B2 */	fmuls f1, f1, f2
/* 800ACDBC 000A9D1C  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 800ACDC0 000A9D20  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 800ACDC4 000A9D24  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 800ACDC8 000A9D28  C0 03 00 1C */	lfs f0, 0x1c(r3)
/* 800ACDCC 000A9D2C  EC 00 00 B2 */	fmuls f0, f0, f2
/* 800ACDD0 000A9D30  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 800ACDD4 000A9D34  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 800ACDD8 000A9D38  80 83 00 0C */	lwz r4, 0xc(r3)
/* 800ACDDC 000A9D3C  80 61 00 20 */	lwz r3, 0x20(r1)
/* 800ACDE0 000A9D40  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800ACDE4 000A9D44  90 64 00 70 */	stw r3, 0x70(r4)
/* 800ACDE8 000A9D48  90 04 00 74 */	stw r0, 0x74(r4)
/* 800ACDEC 000A9D4C  80 01 00 28 */	lwz r0, 0x28(r1)
/* 800ACDF0 000A9D50  90 04 00 78 */	stw r0, 0x78(r4)
/* 800ACDF4 000A9D54  80 9F 00 0C */	lwz r4, 0xc(r31)
/* 800ACDF8 000A9D58  80 64 00 70 */	lwz r3, 0x70(r4)
/* 800ACDFC 000A9D5C  80 04 00 74 */	lwz r0, 0x74(r4)
/* 800ACE00 000A9D60  90 64 00 A4 */	stw r3, 0xa4(r4)
/* 800ACE04 000A9D64  90 04 00 A8 */	stw r0, 0xa8(r4)
/* 800ACE08 000A9D68  80 04 00 78 */	lwz r0, 0x78(r4)
/* 800ACE0C 000A9D6C  90 04 00 AC */	stw r0, 0xac(r4)
/* 800ACE10 000A9D70  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 800ACE14 000A9D74  4B FE 3A 65 */	bl endStickObject__8CreatureFv
/* 800ACE18 000A9D78  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 800ACE1C 000A9D7C  80 03 00 C8 */	lwz r0, 0xc8(r3)
/* 800ACE20 000A9D80  54 00 06 6E */	rlwinm r0, r0, 0, 0x19, 0x17
/* 800ACE24 000A9D84  90 03 00 C8 */	stw r0, 0xc8(r3)
/* 800ACE28 000A9D88  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800ACE2C 000A9D8C  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 800ACE30 000A9D90  38 21 00 38 */	addi r1, r1, 0x38
/* 800ACE34 000A9D94  7C 08 03 A6 */	mtlr r0
/* 800ACE38 000A9D98  4E 80 00 20 */	blr 
.endfn cleanup__6ActBouFv

.fn __dt__6ActBouFv, weak
/* 800ACE3C 000A9D9C  7C 08 02 A6 */	mflr r0
/* 800ACE40 000A9DA0  90 01 00 04 */	stw r0, 4(r1)
/* 800ACE44 000A9DA4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800ACE48 000A9DA8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800ACE4C 000A9DAC  3B E4 00 00 */	addi r31, r4, 0
/* 800ACE50 000A9DB0  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800ACE54 000A9DB4  7C 7E 1B 79 */	or. r30, r3, r3
/* 800ACE58 000A9DB8  41 82 00 2C */	beq .L_800ACE84
/* 800ACE5C 000A9DBC  3C 60 80 2B */	lis r3, __vt__6ActBou@ha
/* 800ACE60 000A9DC0  38 03 5B 4C */	addi r0, r3, __vt__6ActBou@l
/* 800ACE64 000A9DC4  90 1E 00 00 */	stw r0, 0(r30)
/* 800ACE68 000A9DC8  38 7E 00 00 */	addi r3, r30, 0
/* 800ACE6C 000A9DCC  38 80 00 00 */	li r4, 0
/* 800ACE70 000A9DD0  48 01 6F 99 */	bl __dt__6ActionFv
/* 800ACE74 000A9DD4  7F E0 07 35 */	extsh. r0, r31
/* 800ACE78 000A9DD8  40 81 00 0C */	ble .L_800ACE84
/* 800ACE7C 000A9DDC  7F C3 F3 78 */	mr r3, r30
/* 800ACE80 000A9DE0  4B F9 A3 2D */	bl __dl__FPv
.L_800ACE84:
/* 800ACE84 000A9DE4  7F C3 F3 78 */	mr r3, r30
/* 800ACE88 000A9DE8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800ACE8C 000A9DEC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800ACE90 000A9DF0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800ACE94 000A9DF4  38 21 00 18 */	addi r1, r1, 0x18
/* 800ACE98 000A9DF8  7C 08 03 A6 */	mtlr r0
/* 800ACE9C 000A9DFC  4E 80 00 20 */	blr 
.endfn __dt__6ActBouFv

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 8
.obj lbl_802B5B10, local
	.asciz "aiBou.cpp"
.endobj lbl_802B5B10
.balign 4
.obj lbl_802B5B1C, local
	.asciz "Receiver<Piki>"
.endobj lbl_802B5B1C
.balign 4
.obj lbl_802B5B2C, local
	.4byte "__RTTI__15Receiver<4Piki>"
	.4byte 0
	.4byte 0
.endobj lbl_802B5B2C
.obj lbl_802B5B38, local
	.4byte "__RTTI__15Receiver<4Piki>"
	.4byte 0
	.4byte __RTTI__6Action
	.4byte 0
	.4byte 0
.endobj lbl_802B5B38
.obj __vt__6ActBou, global
	.4byte __RTTI__6ActBou
	.4byte 0
	.4byte "procMsg__15Receiver<4Piki>FP4PikiP3Msg"
	.4byte "procBounceMsg__15Receiver<4Piki>FP4PikiP9MsgBounce"
	.4byte "procStickMsg__15Receiver<4Piki>FP4PikiP8MsgStick"
	.4byte "procHangMsg__15Receiver<4Piki>FP4PikiP7MsgHang"
	.4byte "procTargetMsg__15Receiver<4Piki>FP4PikiP9MsgTarget"
	.4byte procCollideMsg__6ActBouFP4PikiP10MsgCollide
	.4byte "procAnimMsg__15Receiver<4Piki>FP4PikiP7MsgAnim"
	.4byte "procDamageMsg__15Receiver<4Piki>FP4PikiP9MsgDamage"
	.4byte "procWallMsg__15Receiver<4Piki>FP4PikiP7MsgWall"
	.4byte "procOffWallMsg__15Receiver<4Piki>FP4PikiP10MsgOffWall"
	.4byte "procUserMsg__15Receiver<4Piki>FP4PikiP7MsgUser"
	.4byte "procGroundMsg__15Receiver<4Piki>FP4PikiP9MsgGround"
	.4byte defaultInitialiser__6ActionFv
	.4byte dump__6ActionFv
	.4byte draw__6ActionFR8Graphics
	.4byte __dt__6ActBouFv
	.4byte init__6ActBouFP8Creature
	.4byte exec__6ActBouFv
	.4byte cleanup__6ActBouFv
	.4byte resume__6ActionFv
	.4byte restart__6ActionFv
	.4byte resumable__6ActionFv
	.4byte getInfo__6ActionFPc
.endobj __vt__6ActBou
.obj lbl_802B5BB0, local
	.4byte .L_800A7908
	.4byte .L_800A7930
	.4byte .L_800A7944
	.4byte .L_800A7958
	.4byte .L_800A796C
	.4byte .L_800A7980
	.4byte .L_800A7994
	.4byte .L_800A79A8
	.4byte .L_800A791C
	.4byte .L_800A79D0
	.4byte .L_800A79BC
.endobj lbl_802B5BB0

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.balign 8
.obj lbl_803DFE60, local
	.asciz "Bou"
.endobj lbl_803DFE60
.balign 4
.obj lbl_803DFE64, local
	.float 0.0
.endobj lbl_803DFE64
.obj lbl_803DFE68, local
	.float 0.0
.endobj lbl_803DFE68
.obj lbl_803DFE6C, local
	.float 0.0
.endobj lbl_803DFE6C
.obj lbl_803DFE70, local
	.float 0.0
.endobj lbl_803DFE70
.obj lbl_803DFE74, local
	.float 0.0
.endobj lbl_803DFE74
.obj lbl_803DFE78, local
	.float 0.0
.endobj lbl_803DFE78
.obj lbl_803DFE7C, local
	.float 150.0
.endobj lbl_803DFE7C
.balign 4
.obj lbl_803DFE80, local
	.asciz "ActBou"
.endobj lbl_803DFE80
.balign 4
.obj "__RTTI__15Receiver<4Piki>", local
	.4byte lbl_802B5B1C
	.4byte 0
.endobj "__RTTI__15Receiver<4Piki>"
.balign 4
.obj lbl_803DFE90, local
	.asciz "Action"
.endobj lbl_803DFE90
.balign 4
.obj __RTTI__6Action, local
	.4byte lbl_803DFE90
	.4byte lbl_802B5B2C
.endobj __RTTI__6Action
.obj __RTTI__6ActBou, local
	.4byte lbl_803DFE80
	.4byte lbl_802B5B38
.endobj __RTTI__6ActBou

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.balign 8
.obj lbl_803E9140, local
	.float 0.0
.endobj lbl_803E9140
.obj lbl_803E9144, local
	.float 0.5
.endobj lbl_803E9144
.obj lbl_803E9148, local
	.float 10.0
.endobj lbl_803E9148
.obj lbl_803E914C, local
	.float 1.0
.endobj lbl_803E914C
.obj lbl_803E9150, local
	.float 5.0
.endobj lbl_803E9150
.obj lbl_803E9154, local
	.float 32767.0
.endobj lbl_803E9154
.obj lbl_803E9158, local
	.float 22.0
.endobj lbl_803E9158
.obj lbl_803E915C, local
	.float 4.0
.endobj lbl_803E915C
.balign 8
.obj lbl_803E9160, local
	.8byte 0x4330000080000000
.endobj lbl_803E9160
