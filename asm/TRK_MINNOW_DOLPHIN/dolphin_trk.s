.include "macros.inc"
.section .init, "ax"  # 0x80003100 - 0x800054C0
.global __TRK_reset
__TRK_reset:
/* 800053EC 000023EC  7C 08 02 A6 */	mflr r0
/* 800053F0 000023F0  90 01 00 04 */	stw r0, 4(r1)
/* 800053F4 000023F4  94 21 FF F8 */	stwu r1, -8(r1)
/* 800053F8 000023F8  48 21 AB C5 */	bl __TRK_copy_vectors
/* 800053FC 000023FC  38 21 00 08 */	addi r1, r1, 8
/* 80005400 00002400  80 01 00 04 */	lwz r0, 4(r1)
/* 80005404 00002404  7C 08 03 A6 */	mtlr r0
/* 80005408 00002408  4E 80 00 20 */	blr 

.section .text, "ax"  # 0x80005560 - 0x80221F60
.global InitMetroTRK
InitMetroTRK:
/* 8021FE60 0021CDC0  38 21 FF FC */	addi r1, r1, -4
/* 8021FE64 0021CDC4  90 61 00 00 */	stw r3, 0(r1)
/* 8021FE68 0021CDC8  3C 60 80 3D */	lis r3, gTRKCPUState@h
/* 8021FE6C 0021CDCC  60 63 5E 40 */	ori r3, r3, gTRKCPUState@l
/* 8021FE70 0021CDD0  BC 03 00 00 */	stmw r0, 0(r3)
/* 8021FE74 0021CDD4  80 81 00 00 */	lwz r4, 0(r1)
/* 8021FE78 0021CDD8  38 21 00 04 */	addi r1, r1, 4
/* 8021FE7C 0021CDDC  90 23 00 04 */	stw r1, 4(r3)
/* 8021FE80 0021CDE0  90 83 00 0C */	stw r4, 0xc(r3)
/* 8021FE84 0021CDE4  7C 88 02 A6 */	mflr r4
/* 8021FE88 0021CDE8  90 83 00 84 */	stw r4, 0x84(r3)
/* 8021FE8C 0021CDEC  90 83 00 80 */	stw r4, 0x80(r3)
/* 8021FE90 0021CDF0  7C 80 00 26 */	mfcr r4
/* 8021FE94 0021CDF4  90 83 00 88 */	stw r4, 0x88(r3)
/* 8021FE98 0021CDF8  7C 80 00 A6 */	mfmsr r4
/* 8021FE9C 0021CDFC  60 83 80 00 */	ori r3, r4, 0x8000
/* 8021FEA0 0021CE00  68 63 80 00 */	xori r3, r3, 0x8000
/* 8021FEA4 0021CE04  7C 60 01 24 */	mtmsr r3
/* 8021FEA8 0021CE08  7C 9B 03 A6 */	mtspr 0x1b, r4
/* 8021FEAC 0021CE0C  48 00 01 F5 */	bl TRKSaveExtended1Block
/* 8021FEB0 0021CE10  3C 60 80 3D */	lis r3, gTRKCPUState@h
/* 8021FEB4 0021CE14  60 63 5E 40 */	ori r3, r3, gTRKCPUState@l
/* 8021FEB8 0021CE18  B8 03 00 00 */	.4byte 0xB8030000  /* illegal lmw r0, 0(r3) */
/* 8021FEBC 0021CE1C  38 00 00 00 */	li r0, 0
/* 8021FEC0 0021CE20  7C 12 FB A6 */	mtspr 0x3f2, r0
/* 8021FEC4 0021CE24  7C 15 FB A6 */	mtspr 0x3f5, r0
/* 8021FEC8 0021CE28  3C 20 80 3F */	lis r1, 0x803FE840@h
/* 8021FECC 0021CE2C  60 21 E8 40 */	ori r1, r1, 0x803FE840@l
/* 8021FED0 0021CE30  7C A3 2B 78 */	mr r3, r5
/* 8021FED4 0021CE34  48 00 06 4D */	bl InitMetroTRKCommTable
/* 8021FED8 0021CE38  2C 03 00 01 */	cmpwi r3, 1
/* 8021FEDC 0021CE3C  40 82 00 14 */	bne lbl_8021FEF0
/* 8021FEE0 0021CE40  80 83 00 84 */	lwz r4, 0x84(r3)
/* 8021FEE4 0021CE44  7C 88 03 A6 */	mtlr r4
/* 8021FEE8 0021CE48  B8 03 00 00 */	.4byte 0xB8030000  /* illegal lmw r0, 0(r3) */
/* 8021FEEC 0021CE4C  4E 80 00 20 */	blr 
lbl_8021FEF0:
/* 8021FEF0 0021CE50  48 00 05 28 */	b TRK_main

.global EnableMetroTRKInterrupts
EnableMetroTRKInterrupts:
/* 8021FEF4 0021CE54  7C 08 02 A6 */	mflr r0
/* 8021FEF8 0021CE58  90 01 00 04 */	stw r0, 4(r1)
/* 8021FEFC 0021CE5C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8021FF00 0021CE60  48 00 07 4D */	bl EnableEXI2Interrupts
/* 8021FF04 0021CE64  38 21 00 08 */	addi r1, r1, 8
/* 8021FF08 0021CE68  80 01 00 04 */	lwz r0, 4(r1)
/* 8021FF0C 0021CE6C  7C 08 03 A6 */	mtlr r0
/* 8021FF10 0021CE70  4E 80 00 20 */	blr 

.global TRKTargetTranslate
TRKTargetTranslate:
/* 8021FF14 0021CE74  3C 80 80 3D */	lis r4, lc_base@ha
/* 8021FF18 0021CE78  38 84 62 70 */	addi r4, r4, lc_base@l
/* 8021FF1C 0021CE7C  80 84 00 00 */	lwz r4, 0(r4)
/* 8021FF20 0021CE80  7C 03 20 40 */	cmplw r3, r4
/* 8021FF24 0021CE84  41 80 00 2C */	blt lbl_8021FF50
/* 8021FF28 0021CE88  38 04 40 00 */	addi r0, r4, 0x4000
/* 8021FF2C 0021CE8C  7C 03 00 40 */	cmplw r3, r0
/* 8021FF30 0021CE90  40 80 00 20 */	bge lbl_8021FF50
/* 8021FF34 0021CE94  3C 80 80 3D */	lis r4, gTRKCPUState@ha
/* 8021FF38 0021CE98  38 84 5E 40 */	addi r4, r4, gTRKCPUState@l
/* 8021FF3C 0021CE9C  80 04 02 38 */	lwz r0, 0x238(r4)
/* 8021FF40 0021CEA0  54 00 07 BE */	clrlwi r0, r0, 0x1e
/* 8021FF44 0021CEA4  28 00 00 00 */	cmplwi r0, 0
/* 8021FF48 0021CEA8  41 82 00 08 */	beq lbl_8021FF50
/* 8021FF4C 0021CEAC  48 00 00 0C */	b lbl_8021FF58
lbl_8021FF50:
/* 8021FF50 0021CEB0  54 60 00 BE */	clrlwi r0, r3, 2
/* 8021FF54 0021CEB4  64 03 80 00 */	oris r3, r0, 0x8000
lbl_8021FF58:
/* 8021FF58 0021CEB8  4E 80 00 20 */	blr 

.global TRK_copy_vector
TRK_copy_vector:
/* 8021FF5C 0021CEBC  7C 08 02 A6 */	mflr r0
/* 8021FF60 0021CEC0  90 01 00 04 */	stw r0, 4(r1)
/* 8021FF64 0021CEC4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8021FF68 0021CEC8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8021FF6C 0021CECC  93 C1 00 08 */	stw r30, 8(r1)
/* 8021FF70 0021CED0  7C 7E 1B 78 */	mr r30, r3
/* 8021FF74 0021CED4  7F C3 F3 78 */	mr r3, r30
/* 8021FF78 0021CED8  4B FF FF 9D */	bl TRKTargetTranslate
/* 8021FF7C 0021CEDC  3C 80 80 00 */	lis r4, metro@ha
/* 8021FF80 0021CEE0  38 04 34 B8 */	addi r0, r4, metro@l
/* 8021FF84 0021CEE4  7C 7F 1B 78 */	mr r31, r3
/* 8021FF88 0021CEE8  7C 80 F2 14 */	add r4, r0, r30
/* 8021FF8C 0021CEEC  7F E3 FB 78 */	mr r3, r31
/* 8021FF90 0021CEF0  38 A0 01 00 */	li r5, 0x100
/* 8021FF94 0021CEF4  4B DE 34 D1 */	bl TRK_memcpy
/* 8021FF98 0021CEF8  7F E3 FB 78 */	mr r3, r31
/* 8021FF9C 0021CEFC  38 80 01 00 */	li r4, 0x100
/* 8021FFA0 0021CF00  4B FF E7 E9 */	bl TRK_flush_cache
/* 8021FFA4 0021CF04  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8021FFA8 0021CF08  83 C1 00 08 */	lwz r30, 8(r1)
/* 8021FFAC 0021CF0C  38 21 00 10 */	addi r1, r1, 0x10
/* 8021FFB0 0021CF10  80 01 00 04 */	lwz r0, 4(r1)
/* 8021FFB4 0021CF14  7C 08 03 A6 */	mtlr r0
/* 8021FFB8 0021CF18  4E 80 00 20 */	blr 

.global __TRK_copy_vectors
__TRK_copy_vectors:
/* 8021FFBC 0021CF1C  7C 08 02 A6 */	mflr r0
/* 8021FFC0 0021CF20  90 01 00 04 */	stw r0, 4(r1)
/* 8021FFC4 0021CF24  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8021FFC8 0021CF28  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8021FFCC 0021CF2C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8021FFD0 0021CF30  93 A1 00 0C */	stw r29, 0xc(r1)
/* 8021FFD4 0021CF34  93 81 00 08 */	stw r28, 8(r1)
/* 8021FFD8 0021CF38  38 60 00 44 */	li r3, 0x44
/* 8021FFDC 0021CF3C  4B FF FF 39 */	bl TRKTargetTranslate
/* 8021FFE0 0021CF40  3B A0 00 00 */	li r29, 0
/* 8021FFE4 0021CF44  83 83 00 00 */	lwz r28, 0(r3)
/* 8021FFE8 0021CF48  3C 60 80 2F */	lis r3, TRK_ISR_OFFSETS@ha
/* 8021FFEC 0021CF4C  57 A4 10 3A */	slwi r4, r29, 2
/* 8021FFF0 0021CF50  38 03 95 B0 */	addi r0, r3, TRK_ISR_OFFSETS@l
/* 8021FFF4 0021CF54  7F C0 22 14 */	add r30, r0, r4
/* 8021FFF8 0021CF58  48 00 00 04 */	b lbl_8021FFFC
lbl_8021FFFC:
/* 8021FFFC 0021CF5C  3B E0 00 01 */	li r31, 1
/* 80220000 0021CF60  48 00 00 04 */	b lbl_80220004
.global lbl_80220004
lbl_80220004:
/* 80220004 0021CF64  48 00 00 04 */	b lbl_80220008
lbl_80220008:
/* 80220008 0021CF68  7F E0 E8 30 */	slw r0, r31, r29
/* 8022000C 0021CF6C  7F 80 00 38 */	and r0, r28, r0
/* 80220010 0021CF70  28 00 00 00 */	cmplwi r0, 0
/* 80220014 0021CF74  41 82 00 0C */	beq lbl_80220020
/* 80220018 0021CF78  80 7E 00 00 */	lwz r3, 0(r30)
/* 8022001C 0021CF7C  4B FF FF 41 */	bl TRK_copy_vector
lbl_80220020:
/* 80220020 0021CF80  3B DE 00 04 */	addi r30, r30, 4
/* 80220024 0021CF84  3B BD 00 01 */	addi r29, r29, 1
/* 80220028 0021CF88  2C 1D 00 0E */	cmpwi r29, 0xe
/* 8022002C 0021CF8C  40 81 FF DC */	ble lbl_80220008
/* 80220030 0021CF90  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80220034 0021CF94  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80220038 0021CF98  83 A1 00 0C */	lwz r29, 0xc(r1)
/* 8022003C 0021CF9C  83 81 00 08 */	lwz r28, 8(r1)
/* 80220040 0021CFA0  38 21 00 18 */	addi r1, r1, 0x18
/* 80220044 0021CFA4  80 01 00 04 */	lwz r0, 4(r1)
/* 80220048 0021CFA8  7C 08 03 A6 */	mtlr r0
/* 8022004C 0021CFAC  4E 80 00 20 */	blr 

.global TRKInitializeTarget
TRKInitializeTarget:
/* 80220050 0021CFB0  7C 08 02 A6 */	mflr r0
/* 80220054 0021CFB4  90 01 00 04 */	stw r0, 4(r1)
/* 80220058 0021CFB8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8022005C 0021CFBC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80220060 0021CFC0  3C 60 80 3D */	lis r3, gTRKState@ha
/* 80220064 0021CFC4  3B E3 5D 98 */	addi r31, r3, gTRKState@l
/* 80220068 0021CFC8  38 00 00 01 */	li r0, 1
/* 8022006C 0021CFCC  90 1F 00 98 */	stw r0, 0x98(r31)
/* 80220070 0021CFD0  4B FF E8 15 */	bl __TRK_get_MSR
/* 80220074 0021CFD4  90 7F 00 8C */	stw r3, 0x8c(r31)
/* 80220078 0021CFD8  3C 60 80 3D */	lis r3, lc_base@ha
/* 8022007C 0021CFDC  38 63 62 70 */	addi r3, r3, lc_base@l
/* 80220080 0021CFE0  3C 00 E0 00 */	lis r0, 0xe000
/* 80220084 0021CFE4  90 03 00 00 */	stw r0, 0(r3)
/* 80220088 0021CFE8  38 60 00 00 */	li r3, 0
/* 8022008C 0021CFEC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80220090 0021CFF0  38 21 00 10 */	addi r1, r1, 0x10
/* 80220094 0021CFF4  80 01 00 04 */	lwz r0, 4(r1)
/* 80220098 0021CFF8  7C 08 03 A6 */	mtlr r0
/* 8022009C 0021CFFC  4E 80 00 20 */	blr 

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 0x8
.global TRK_ISR_OFFSETS
TRK_ISR_OFFSETS:
	.4byte 0x00000100
	.4byte 0x00000200
	.4byte 0x00000300
	.4byte 0x00000400
	.4byte 0x00000500
	.4byte 0x00000600
	.4byte 0x00000700
	.4byte 0x00000800
	.4byte 0x00000900
	.4byte 0x00000C00
	.4byte 0x00000D00
	.4byte 0x00000F00
	.4byte 0x00001300
	.4byte 0x00001400
	.4byte 0x00001700
	.4byte 0x00000000
