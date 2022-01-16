.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.global load__Q23zen14particleLoaderFPcb
load__Q23zen14particleLoaderFPcb:
/* 801A0F24 0019DE84  7C 08 02 A6 */	mflr r0
/* 801A0F28 0019DE88  3C C0 5F 62 */	lis r6, 0x5F62696E@ha
/* 801A0F2C 0019DE8C  90 01 00 04 */	stw r0, 4(r1)
/* 801A0F30 0019DE90  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 801A0F34 0019DE94  BF 61 00 2C */	stmw r27, 0x2c(r1)
/* 801A0F38 0019DE98  7C 7F 1B 78 */	mr r31, r3
/* 801A0F3C 0019DE9C  3B 65 00 00 */	addi r27, r5, 0
/* 801A0F40 0019DEA0  3B C4 00 00 */	addi r30, r4, 0
/* 801A0F44 0019DEA4  38 A6 69 6E */	addi r5, r6, 0x5F62696E@l
/* 801A0F48 0019DEA8  80 6D 2D EC */	lwz r3, gsys@sda21(r13)
/* 801A0F4C 0019DEAC  4B E9 E1 2D */	bl findGfxObject__9StdSystemFPcUl
/* 801A0F50 0019DEB0  28 03 00 00 */	cmplwi r3, 0
/* 801A0F54 0019DEB4  41 82 00 0C */	beq lbl_801A0F60
/* 801A0F58 0019DEB8  80 63 00 20 */	lwz r3, 0x20(r3)
/* 801A0F5C 0019DEBC  48 00 01 0C */	b lbl_801A1068
lbl_801A0F60:
/* 801A0F60 0019DEC0  38 7F 00 00 */	addi r3, r31, 0
/* 801A0F64 0019DEC4  38 9E 00 00 */	addi r4, r30, 0
/* 801A0F68 0019DEC8  48 00 01 15 */	bl pmFind__Q23zen14particleLoaderFPc
/* 801A0F6C 0019DECC  7C 7D 1B 79 */	or. r29, r3, r3
/* 801A0F70 0019DED0  40 82 00 F4 */	bne lbl_801A1064
/* 801A0F74 0019DED4  80 6D 2D EC */	lwz r3, gsys@sda21(r13)
/* 801A0F78 0019DED8  38 9E 00 00 */	addi r4, r30, 0
/* 801A0F7C 0019DEDC  38 BB 00 00 */	addi r5, r27, 0
/* 801A0F80 0019DEE0  81 83 01 A0 */	lwz r12, 0x1a0(r3)
/* 801A0F84 0019DEE4  38 C0 00 01 */	li r6, 1
/* 801A0F88 0019DEE8  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 801A0F8C 0019DEEC  7D 88 03 A6 */	mtlr r12
/* 801A0F90 0019DEF0  4E 80 00 21 */	blrl 
/* 801A0F94 0019DEF4  7C 7C 1B 79 */	or. r28, r3, r3
/* 801A0F98 0019DEF8  41 82 00 CC */	beq lbl_801A1064
/* 801A0F9C 0019DEFC  7F 83 E3 78 */	mr r3, r28
/* 801A0FA0 0019DF00  81 9C 00 04 */	lwz r12, 4(r28)
/* 801A0FA4 0019DF04  81 8C 00 44 */	lwz r12, 0x44(r12)
/* 801A0FA8 0019DF08  7D 88 03 A6 */	mtlr r12
/* 801A0FAC 0019DF0C  4E 80 00 21 */	blrl 
/* 801A0FB0 0019DF10  3B 63 00 00 */	addi r27, r3, 0
/* 801A0FB4 0019DF14  38 60 00 14 */	li r3, 0x14
/* 801A0FB8 0019DF18  4B EA 60 4D */	bl alloc__6SystemFUl
/* 801A0FBC 0019DF1C  3B A3 00 00 */	addi r29, r3, 0
/* 801A0FC0 0019DF20  7F A0 EB 79 */	or. r0, r29, r29
/* 801A0FC4 0019DF24  41 82 00 40 */	beq lbl_801A1004
/* 801A0FC8 0019DF28  3C 60 80 2D */	lis r3, __vt__Q23zen7zenList@ha
/* 801A0FCC 0019DF2C  38 03 68 DC */	addi r0, r3, __vt__Q23zen7zenList@l
/* 801A0FD0 0019DF30  90 1D 00 00 */	stw r0, 0(r29)
/* 801A0FD4 0019DF34  3C 60 80 2E */	lis r3, __vt__Q23zen7PCRData@ha
/* 801A0FD8 0019DF38  38 03 A7 68 */	addi r0, r3, __vt__Q23zen7PCRData@l
/* 801A0FDC 0019DF3C  93 BD 00 08 */	stw r29, 8(r29)
/* 801A0FE0 0019DF40  7F C3 F3 78 */	mr r3, r30
/* 801A0FE4 0019DF44  93 BD 00 04 */	stw r29, 4(r29)
/* 801A0FE8 0019DF48  90 1D 00 00 */	stw r0, 0(r29)
/* 801A0FEC 0019DF4C  4B E9 F3 55 */	bl stringDup__9StdSystemFPc
/* 801A0FF0 0019DF50  90 7D 00 0C */	stw r3, 0xc(r29)
/* 801A0FF4 0019DF54  38 7B 00 00 */	addi r3, r27, 0
/* 801A0FF8 0019DF58  38 80 00 20 */	li r4, 0x20
/* 801A0FFC 0019DF5C  4B EA 61 6D */	bl __nwa__FUli
/* 801A1000 0019DF60  90 7D 00 10 */	stw r3, 0x10(r29)
lbl_801A1004:
/* 801A1004 0019DF64  81 9D 00 00 */	lwz r12, 0(r29)
/* 801A1008 0019DF68  7F A3 EB 78 */	mr r3, r29
/* 801A100C 0019DF6C  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 801A1010 0019DF70  7D 88 03 A6 */	mtlr r12
/* 801A1014 0019DF74  4E 80 00 21 */	blrl 
/* 801A1018 0019DF78  80 7F 00 00 */	lwz r3, 0(r31)
/* 801A101C 0019DF7C  7F A4 EB 78 */	mr r4, r29
/* 801A1020 0019DF80  81 83 00 00 */	lwz r12, 0(r3)
/* 801A1024 0019DF84  81 8C 00 08 */	lwz r12, 8(r12)
/* 801A1028 0019DF88  7D 88 03 A6 */	mtlr r12
/* 801A102C 0019DF8C  4E 80 00 21 */	blrl 
/* 801A1030 0019DF90  7F 83 E3 78 */	mr r3, r28
/* 801A1034 0019DF94  83 BD 00 10 */	lwz r29, 0x10(r29)
/* 801A1038 0019DF98  81 9C 00 04 */	lwz r12, 4(r28)
/* 801A103C 0019DF9C  38 BB 00 00 */	addi r5, r27, 0
/* 801A1040 0019DFA0  38 9D 00 00 */	addi r4, r29, 0
/* 801A1044 0019DFA4  81 8C 00 3C */	lwz r12, 0x3c(r12)
/* 801A1048 0019DFA8  7D 88 03 A6 */	mtlr r12
/* 801A104C 0019DFAC  4E 80 00 21 */	blrl 
/* 801A1050 0019DFB0  7F 83 E3 78 */	mr r3, r28
/* 801A1054 0019DFB4  81 9C 00 04 */	lwz r12, 4(r28)
/* 801A1058 0019DFB8  81 8C 00 4C */	lwz r12, 0x4c(r12)
/* 801A105C 0019DFBC  7D 88 03 A6 */	mtlr r12
/* 801A1060 0019DFC0  4E 80 00 21 */	blrl 
lbl_801A1064:
/* 801A1064 0019DFC4  7F A3 EB 78 */	mr r3, r29
lbl_801A1068:
/* 801A1068 0019DFC8  BB 61 00 2C */	lmw r27, 0x2c(r1)
/* 801A106C 0019DFCC  80 01 00 44 */	lwz r0, 0x44(r1)
/* 801A1070 0019DFD0  38 21 00 40 */	addi r1, r1, 0x40
/* 801A1074 0019DFD4  7C 08 03 A6 */	mtlr r0
/* 801A1078 0019DFD8  4E 80 00 20 */	blr 

.global pmFind__Q23zen14particleLoaderFPc
pmFind__Q23zen14particleLoaderFPc:
/* 801A107C 0019DFDC  7C 08 02 A6 */	mflr r0
/* 801A1080 0019DFE0  90 01 00 04 */	stw r0, 4(r1)
/* 801A1084 0019DFE4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 801A1088 0019DFE8  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 801A108C 0019DFEC  93 C1 00 28 */	stw r30, 0x28(r1)
/* 801A1090 0019DFF0  3B C0 00 00 */	li r30, 0
/* 801A1094 0019DFF4  93 A1 00 24 */	stw r29, 0x24(r1)
/* 801A1098 0019DFF8  3B A4 00 00 */	addi r29, r4, 0
/* 801A109C 0019DFFC  93 81 00 20 */	stw r28, 0x20(r1)
/* 801A10A0 0019E000  7C 7C 1B 78 */	mr r28, r3
/* 801A10A4 0019E004  80 63 00 00 */	lwz r3, 0(r3)
/* 801A10A8 0019E008  83 E3 00 08 */	lwz r31, 8(r3)
/* 801A10AC 0019E00C  48 00 00 24 */	b lbl_801A10D0
lbl_801A10B0:
/* 801A10B0 0019E010  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 801A10B4 0019E014  7F A4 EB 78 */	mr r4, r29
/* 801A10B8 0019E018  48 07 81 0D */	bl strcmp
/* 801A10BC 0019E01C  2C 03 00 00 */	cmpwi r3, 0
/* 801A10C0 0019E020  40 82 00 0C */	bne lbl_801A10CC
/* 801A10C4 0019E024  83 DF 00 10 */	lwz r30, 0x10(r31)
/* 801A10C8 0019E028  48 00 00 14 */	b lbl_801A10DC
lbl_801A10CC:
/* 801A10CC 0019E02C  83 FF 00 08 */	lwz r31, 8(r31)
lbl_801A10D0:
/* 801A10D0 0019E030  80 1C 00 00 */	lwz r0, 0(r28)
/* 801A10D4 0019E034  7C 1F 00 40 */	cmplw r31, r0
/* 801A10D8 0019E038  40 82 FF D8 */	bne lbl_801A10B0
lbl_801A10DC:
/* 801A10DC 0019E03C  7F C3 F3 78 */	mr r3, r30
/* 801A10E0 0019E040  80 01 00 34 */	lwz r0, 0x34(r1)
/* 801A10E4 0019E044  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 801A10E8 0019E048  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 801A10EC 0019E04C  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 801A10F0 0019E050  83 81 00 20 */	lwz r28, 0x20(r1)
/* 801A10F4 0019E054  38 21 00 30 */	addi r1, r1, 0x30
/* 801A10F8 0019E058  7C 08 03 A6 */	mtlr r0
/* 801A10FC 0019E05C  4E 80 00 20 */	blr 

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 8
lbl_802DA718:
	.asciz "particleLoader.cpp"
.balign 4
lbl_802DA72C:
	.asciz "particleLoader"
.balign 4
lbl_802DA73C:
	.asciz "zen::PCRData"
.balign 4
lbl_802DA74C:
	.asciz "zen::zenList"
.balign 4
lbl_802DA75C:
	.4byte __RTTI__Q23zen7zenList
	.4byte 0x00000000
	.4byte 0x00000000
.global __vt__Q23zen7PCRData
__vt__Q23zen7PCRData:
	.4byte __RTTI__Q23zen7PCRData
	.4byte 0
	.4byte insertAfter__Q23zen7zenListFPQ23zen7zenList
	.4byte remove__Q23zen7zenListFv
	.4byte 0
	.4byte 0
	.4byte 0
	.4byte 0

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.balign 8
__RTTI__Q23zen7zenList:
	.4byte lbl_802DA74C
	.4byte 0
__RTTI__Q23zen7PCRData:
	.4byte lbl_802DA73C
	.4byte lbl_802DA75C
