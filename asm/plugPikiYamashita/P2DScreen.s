.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.global update__9P2DScreenFv
update__9P2DScreenFv:
/* 801B2B50 001AFAB0  7C 08 02 A6 */	mflr r0
/* 801B2B54 001AFAB4  90 01 00 04 */	stw r0, 4(r1)
/* 801B2B58 001AFAB8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801B2B5C 001AFABC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801B2B60 001AFAC0  7C 7F 1B 78 */	mr r31, r3
/* 801B2B64 001AFAC4  4B FF DB E1 */	bl update__7P2DPaneFv
/* 801B2B68 001AFAC8  80 7F 00 F0 */	lwz r3, 0xf0(r31)
/* 801B2B6C 001AFACC  28 03 00 00 */	cmplwi r3, 0
/* 801B2B70 001AFAD0  41 82 00 08 */	beq .L_801B2B78
/* 801B2B74 001AFAD4  4B FC C4 A9 */	bl update__Q23zen12PikaAlphaMgrFv
.L_801B2B78:
/* 801B2B78 001AFAD8  80 7F 00 F4 */	lwz r3, 0xf4(r31)
/* 801B2B7C 001AFADC  28 03 00 00 */	cmplwi r3, 0
/* 801B2B80 001AFAE0  41 82 00 08 */	beq .L_801B2B88
/* 801B2B84 001AFAE4  4B FC D4 4D */	bl update__Q23zen12ogTexAnimMgrFv
.L_801B2B88:
/* 801B2B88 001AFAE8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801B2B8C 001AFAEC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801B2B90 001AFAF0  38 21 00 18 */	addi r1, r1, 0x18
/* 801B2B94 001AFAF4  7C 08 03 A6 */	mtlr r0
/* 801B2B98 001AFAF8  4E 80 00 20 */	blr 

.global __dt__9P2DScreenFv
__dt__9P2DScreenFv:
/* 801B2B9C 001AFAFC  7C 08 02 A6 */	mflr r0
/* 801B2BA0 001AFB00  90 01 00 04 */	stw r0, 4(r1)
/* 801B2BA4 001AFB04  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801B2BA8 001AFB08  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801B2BAC 001AFB0C  3B E4 00 00 */	addi r31, r4, 0
/* 801B2BB0 001AFB10  93 C1 00 10 */	stw r30, 0x10(r1)
/* 801B2BB4 001AFB14  7C 7E 1B 79 */	or. r30, r3, r3
/* 801B2BB8 001AFB18  41 82 00 2C */	beq .L_801B2BE4
/* 801B2BBC 001AFB1C  3C 60 80 2E */	lis r3, __vt__9P2DScreen@ha
/* 801B2BC0 001AFB20  38 03 07 E0 */	addi r0, r3, __vt__9P2DScreen@l
/* 801B2BC4 001AFB24  90 1E 00 00 */	stw r0, 0(r30)
/* 801B2BC8 001AFB28  38 7E 00 00 */	addi r3, r30, 0
/* 801B2BCC 001AFB2C  38 80 00 00 */	li r4, 0
/* 801B2BD0 001AFB30  4B FF E1 F5 */	bl __dt__7P2DPaneFv
/* 801B2BD4 001AFB34  7F E0 07 35 */	extsh. r0, r31
/* 801B2BD8 001AFB38  40 81 00 0C */	ble .L_801B2BE4
/* 801B2BDC 001AFB3C  7F C3 F3 78 */	mr r3, r30
/* 801B2BE0 001AFB40  4B E9 45 CD */	bl __dl__FPv
.L_801B2BE4:
/* 801B2BE4 001AFB44  7F C3 F3 78 */	mr r3, r30
/* 801B2BE8 001AFB48  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801B2BEC 001AFB4C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801B2BF0 001AFB50  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 801B2BF4 001AFB54  38 21 00 18 */	addi r1, r1, 0x18
/* 801B2BF8 001AFB58  7C 08 03 A6 */	mtlr r0
/* 801B2BFC 001AFB5C  4E 80 00 20 */	blr 

.global set__9P2DScreenFPCcbbb
set__9P2DScreenFPCcbbb:
/* 801B2C00 001AFB60  7C 08 02 A6 */	mflr r0
/* 801B2C04 001AFB64  90 01 00 04 */	stw r0, 4(r1)
/* 801B2C08 001AFB68  94 21 FE D8 */	stwu r1, -0x128(r1)
/* 801B2C0C 001AFB6C  93 E1 01 24 */	stw r31, 0x124(r1)
/* 801B2C10 001AFB70  3B E7 00 00 */	addi r31, r7, 0
/* 801B2C14 001AFB74  93 C1 01 20 */	stw r30, 0x120(r1)
/* 801B2C18 001AFB78  3B C6 00 00 */	addi r30, r6, 0
/* 801B2C1C 001AFB7C  93 A1 01 1C */	stw r29, 0x11c(r1)
/* 801B2C20 001AFB80  3B A5 00 00 */	addi r29, r5, 0
/* 801B2C24 001AFB84  38 A1 00 14 */	addi r5, r1, 0x14
/* 801B2C28 001AFB88  93 81 01 18 */	stw r28, 0x118(r1)
/* 801B2C2C 001AFB8C  3B 83 00 00 */	addi r28, r3, 0
/* 801B2C30 001AFB90  48 00 06 1D */	bl makeResName__9P2DScreenFPCcPc
/* 801B2C34 001AFB94  80 6D 2D EC */	lwz r3, gsys@sda21(r13)
/* 801B2C38 001AFB98  38 BF 00 00 */	addi r5, r31, 0
/* 801B2C3C 001AFB9C  38 81 00 14 */	addi r4, r1, 0x14
/* 801B2C40 001AFBA0  81 83 01 A0 */	lwz r12, 0x1a0(r3)
/* 801B2C44 001AFBA4  38 C0 00 01 */	li r6, 1
/* 801B2C48 001AFBA8  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 801B2C4C 001AFBAC  7D 88 03 A6 */	mtlr r12
/* 801B2C50 001AFBB0  4E 80 00 21 */	blrl 
/* 801B2C54 001AFBB4  7C 7F 1B 79 */	or. r31, r3, r3
/* 801B2C58 001AFBB8  41 82 00 30 */	beq .L_801B2C88
/* 801B2C5C 001AFBBC  38 7C 00 00 */	addi r3, r28, 0
/* 801B2C60 001AFBC0  38 9C 00 00 */	addi r4, r28, 0
/* 801B2C64 001AFBC4  38 BF 00 00 */	addi r5, r31, 0
/* 801B2C68 001AFBC8  38 C0 00 01 */	li r6, 1
/* 801B2C6C 001AFBCC  38 E0 00 01 */	li r7, 1
/* 801B2C70 001AFBD0  48 00 00 BD */	bl makeHiearachyPanes__9P2DScreenFP7P2DPaneP18RandomAccessStreambb
/* 801B2C74 001AFBD4  7F E3 FB 78 */	mr r3, r31
/* 801B2C78 001AFBD8  81 9F 00 04 */	lwz r12, 4(r31)
/* 801B2C7C 001AFBDC  81 8C 00 4C */	lwz r12, 0x4c(r12)
/* 801B2C80 001AFBE0  7D 88 03 A6 */	mtlr r12
/* 801B2C84 001AFBE4  4E 80 00 21 */	blrl 
.L_801B2C88:
/* 801B2C88 001AFBE8  7F 83 E3 78 */	mr r3, r28
/* 801B2C8C 001AFBEC  81 9C 00 00 */	lwz r12, 0(r28)
/* 801B2C90 001AFBF0  81 8C 00 08 */	lwz r12, 8(r12)
/* 801B2C94 001AFBF4  7D 88 03 A6 */	mtlr r12
/* 801B2C98 001AFBF8  4E 80 00 21 */	blrl 
/* 801B2C9C 001AFBFC  57 A0 06 3F */	clrlwi. r0, r29, 0x18
/* 801B2CA0 001AFC00  41 82 00 30 */	beq .L_801B2CD0
/* 801B2CA4 001AFC04  38 60 01 98 */	li r3, 0x198
/* 801B2CA8 001AFC08  4B E9 43 5D */	bl alloc__6SystemFUl
/* 801B2CAC 001AFC0C  3B E3 00 00 */	addi r31, r3, 0
/* 801B2CB0 001AFC10  7F E3 FB 79 */	or. r3, r31, r31
/* 801B2CB4 001AFC14  41 82 00 0C */	beq .L_801B2CC0
/* 801B2CB8 001AFC18  7F 84 E3 78 */	mr r4, r28
/* 801B2CBC 001AFC1C  4B FC BE C5 */	bl __ct__Q23zen12PikaAlphaMgrFP9P2DScreen
.L_801B2CC0:
/* 801B2CC0 001AFC20  93 FC 00 F0 */	stw r31, 0xf0(r28)
/* 801B2CC4 001AFC24  80 7C 00 F0 */	lwz r3, 0xf0(r28)
/* 801B2CC8 001AFC28  4B FC C1 E1 */	bl start__Q23zen12PikaAlphaMgrFv
/* 801B2CCC 001AFC2C  48 00 00 0C */	b .L_801B2CD8
.L_801B2CD0:
/* 801B2CD0 001AFC30  38 00 00 00 */	li r0, 0
/* 801B2CD4 001AFC34  90 1C 00 F0 */	stw r0, 0xf0(r28)
.L_801B2CD8:
/* 801B2CD8 001AFC38  57 C0 06 3F */	clrlwi. r0, r30, 0x18
/* 801B2CDC 001AFC3C  41 82 00 28 */	beq .L_801B2D04
/* 801B2CE0 001AFC40  38 60 01 94 */	li r3, 0x194
/* 801B2CE4 001AFC44  4B E9 43 21 */	bl alloc__6SystemFUl
/* 801B2CE8 001AFC48  3B E3 00 00 */	addi r31, r3, 0
/* 801B2CEC 001AFC4C  7F E3 FB 79 */	or. r3, r31, r31
/* 801B2CF0 001AFC50  41 82 00 0C */	beq .L_801B2CFC
/* 801B2CF4 001AFC54  7F 84 E3 78 */	mr r4, r28
/* 801B2CF8 001AFC58  4B FC D1 E5 */	bl __ct__Q23zen12ogTexAnimMgrFP9P2DScreen
.L_801B2CFC:
/* 801B2CFC 001AFC5C  93 FC 00 F4 */	stw r31, 0xf4(r28)
/* 801B2D00 001AFC60  48 00 00 0C */	b .L_801B2D0C
.L_801B2D04:
/* 801B2D04 001AFC64  38 00 00 00 */	li r0, 0
/* 801B2D08 001AFC68  90 1C 00 F4 */	stw r0, 0xf4(r28)
.L_801B2D0C:
/* 801B2D0C 001AFC6C  80 01 01 2C */	lwz r0, 0x12c(r1)
/* 801B2D10 001AFC70  83 E1 01 24 */	lwz r31, 0x124(r1)
/* 801B2D14 001AFC74  83 C1 01 20 */	lwz r30, 0x120(r1)
/* 801B2D18 001AFC78  83 A1 01 1C */	lwz r29, 0x11c(r1)
/* 801B2D1C 001AFC7C  83 81 01 18 */	lwz r28, 0x118(r1)
/* 801B2D20 001AFC80  38 21 01 28 */	addi r1, r1, 0x128
/* 801B2D24 001AFC84  7C 08 03 A6 */	mtlr r0
/* 801B2D28 001AFC88  4E 80 00 20 */	blr 

.global makeHiearachyPanes__9P2DScreenFP7P2DPaneP18RandomAccessStreambb
makeHiearachyPanes__9P2DScreenFP7P2DPaneP18RandomAccessStreambb:
/* 801B2D2C 001AFC8C  7C 08 02 A6 */	mflr r0
/* 801B2D30 001AFC90  90 01 00 04 */	stw r0, 4(r1)
/* 801B2D34 001AFC94  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 801B2D38 001AFC98  BF 21 00 34 */	stmw r25, 0x34(r1)
/* 801B2D3C 001AFC9C  3B 64 00 00 */	addi r27, r4, 0
/* 801B2D40 001AFCA0  3C 80 80 2E */	lis r4, lbl_802E0784@ha
/* 801B2D44 001AFCA4  3B 43 00 00 */	addi r26, r3, 0
/* 801B2D48 001AFCA8  3B 85 00 00 */	addi r28, r5, 0
/* 801B2D4C 001AFCAC  3B BB 00 00 */	addi r29, r27, 0
/* 801B2D50 001AFCB0  3B C4 07 84 */	addi r30, r4, lbl_802E0784@l
/* 801B2D54 001AFCB4  54 FF 06 3E */	clrlwi r31, r7, 0x18
.L_801B2D58:
/* 801B2D58 001AFCB8  7F 83 E3 78 */	mr r3, r28
/* 801B2D5C 001AFCBC  81 9C 00 04 */	lwz r12, 4(r28)
/* 801B2D60 001AFCC0  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 801B2D64 001AFCC4  7D 88 03 A6 */	mtlr r12
/* 801B2D68 001AFCC8  4E 80 00 21 */	blrl 
/* 801B2D6C 001AFCCC  54 60 04 3E */	clrlwi r0, r3, 0x10
/* 801B2D70 001AFCD0  28 00 00 13 */	cmplwi r0, 0x13
/* 801B2D74 001AFCD4  3B 23 00 00 */	addi r25, r3, 0
/* 801B2D78 001AFCD8  41 81 FF E0 */	bgt .L_801B2D58
/* 801B2D7C 001AFCDC  54 00 10 3A */	slwi r0, r0, 2
/* 801B2D80 001AFCE0  7C 1E 00 2E */	lwzx r0, r30, r0
/* 801B2D84 001AFCE4  7C 09 03 A6 */	mtctr r0
/* 801B2D88 001AFCE8  4E 80 04 20 */	bctr 
.L_801B2D8C:
/* 801B2D8C 001AFCEC  48 00 01 2C */	b .L_801B2EB8
.L_801B2D90:
/* 801B2D90 001AFCF0  7F 83 E3 78 */	mr r3, r28
/* 801B2D94 001AFCF4  81 9C 00 04 */	lwz r12, 4(r28)
/* 801B2D98 001AFCF8  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 801B2D9C 001AFCFC  7D 88 03 A6 */	mtlr r12
/* 801B2DA0 001AFD00  4E 80 00 21 */	blrl 
/* 801B2DA4 001AFD04  38 7A 00 00 */	addi r3, r26, 0
/* 801B2DA8 001AFD08  38 9D 00 00 */	addi r4, r29, 0
/* 801B2DAC 001AFD0C  38 BC 00 00 */	addi r5, r28, 0
/* 801B2DB0 001AFD10  38 C0 00 01 */	li r6, 1
/* 801B2DB4 001AFD14  38 E0 00 00 */	li r7, 0
/* 801B2DB8 001AFD18  4B FF FF 75 */	bl makeHiearachyPanes__9P2DScreenFP7P2DPaneP18RandomAccessStreambb
/* 801B2DBC 001AFD1C  4B FF FF 9C */	b .L_801B2D58
.L_801B2DC0:
/* 801B2DC0 001AFD20  7F 83 E3 78 */	mr r3, r28
/* 801B2DC4 001AFD24  81 9C 00 04 */	lwz r12, 4(r28)
/* 801B2DC8 001AFD28  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 801B2DCC 001AFD2C  7D 88 03 A6 */	mtlr r12
/* 801B2DD0 001AFD30  4E 80 00 21 */	blrl 
/* 801B2DD4 001AFD34  48 00 00 E4 */	b .L_801B2EB8
.L_801B2DD8:
/* 801B2DD8 001AFD38  38 60 00 EC */	li r3, 0xec
/* 801B2DDC 001AFD3C  4B E9 42 29 */	bl alloc__6SystemFUl
/* 801B2DE0 001AFD40  3B A3 00 00 */	addi r29, r3, 0
/* 801B2DE4 001AFD44  7F A3 EB 79 */	or. r3, r29, r29
/* 801B2DE8 001AFD48  41 82 00 14 */	beq .L_801B2DFC
/* 801B2DEC 001AFD4C  38 9B 00 00 */	addi r4, r27, 0
/* 801B2DF0 001AFD50  38 BC 00 00 */	addi r5, r28, 0
/* 801B2DF4 001AFD54  38 D9 00 00 */	addi r6, r25, 0
/* 801B2DF8 001AFD58  4B FF DD 3D */	bl __ct__7P2DPaneFP7P2DPaneP18RandomAccessStreamUs
.L_801B2DFC:
/* 801B2DFC 001AFD5C  28 1F 00 00 */	cmplwi r31, 0
/* 801B2E00 001AFD60  41 82 FF 58 */	beq .L_801B2D58
/* 801B2E04 001AFD64  A8 FD 00 1A */	lha r7, 0x1a(r29)
/* 801B2E08 001AFD68  38 61 00 28 */	addi r3, r1, 0x28
/* 801B2E0C 001AFD6C  A8 DD 00 1E */	lha r6, 0x1e(r29)
/* 801B2E10 001AFD70  38 80 00 00 */	li r4, 0
/* 801B2E14 001AFD74  A8 BD 00 18 */	lha r5, 0x18(r29)
/* 801B2E18 001AFD78  A8 1D 00 1C */	lha r0, 0x1c(r29)
/* 801B2E1C 001AFD7C  7C E7 30 50 */	subf r7, r7, r6
/* 801B2E20 001AFD80  7C C5 00 50 */	subf r6, r5, r0
/* 801B2E24 001AFD84  38 A0 00 00 */	li r5, 0
/* 801B2E28 001AFD88  48 00 08 01 */	bl set__7PUTRectFiiii
/* 801B2E2C 001AFD8C  80 61 00 28 */	lwz r3, 0x28(r1)
/* 801B2E30 001AFD90  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 801B2E34 001AFD94  90 7A 00 18 */	stw r3, 0x18(r26)
/* 801B2E38 001AFD98  90 1A 00 1C */	stw r0, 0x1c(r26)
/* 801B2E3C 001AFD9C  4B FF FF 1C */	b .L_801B2D58
.L_801B2E40:
/* 801B2E40 001AFDA0  38 60 01 2C */	li r3, 0x12c
/* 801B2E44 001AFDA4  4B E9 41 C1 */	bl alloc__6SystemFUl
/* 801B2E48 001AFDA8  3B A3 00 00 */	addi r29, r3, 0
/* 801B2E4C 001AFDAC  7F A3 EB 79 */	or. r3, r29, r29
/* 801B2E50 001AFDB0  41 82 FF 08 */	beq .L_801B2D58
/* 801B2E54 001AFDB4  38 9B 00 00 */	addi r4, r27, 0
/* 801B2E58 001AFDB8  38 BC 00 00 */	addi r5, r28, 0
/* 801B2E5C 001AFDBC  38 C0 00 11 */	li r6, 0x11
/* 801B2E60 001AFDC0  48 00 0B 79 */	bl __ct__9P2DWindowFP7P2DPaneP18RandomAccessStreamUs
/* 801B2E64 001AFDC4  4B FF FE F4 */	b .L_801B2D58
.L_801B2E68:
/* 801B2E68 001AFDC8  38 60 01 14 */	li r3, 0x114
/* 801B2E6C 001AFDCC  4B E9 41 99 */	bl alloc__6SystemFUl
/* 801B2E70 001AFDD0  3B A3 00 00 */	addi r29, r3, 0
/* 801B2E74 001AFDD4  7F A3 EB 79 */	or. r3, r29, r29
/* 801B2E78 001AFDD8  41 82 FE E0 */	beq .L_801B2D58
/* 801B2E7C 001AFDDC  38 9B 00 00 */	addi r4, r27, 0
/* 801B2E80 001AFDE0  38 BC 00 00 */	addi r5, r28, 0
/* 801B2E84 001AFDE4  38 C0 00 12 */	li r6, 0x12
/* 801B2E88 001AFDE8  4B FF EB BD */	bl __ct__10P2DPictureFP7P2DPaneP18RandomAccessStreamUs
/* 801B2E8C 001AFDEC  4B FF FE CC */	b .L_801B2D58
.L_801B2E90:
/* 801B2E90 001AFDF0  38 60 01 18 */	li r3, 0x118
/* 801B2E94 001AFDF4  4B E9 41 71 */	bl alloc__6SystemFUl
/* 801B2E98 001AFDF8  3B A3 00 00 */	addi r29, r3, 0
/* 801B2E9C 001AFDFC  7F A3 EB 79 */	or. r3, r29, r29
/* 801B2EA0 001AFE00  41 82 FE B8 */	beq .L_801B2D58
/* 801B2EA4 001AFE04  38 9B 00 00 */	addi r4, r27, 0
/* 801B2EA8 001AFE08  38 BC 00 00 */	addi r5, r28, 0
/* 801B2EAC 001AFE0C  38 C0 00 13 */	li r6, 0x13
/* 801B2EB0 001AFE10  48 00 16 85 */	bl __ct__10P2DTextBoxFP7P2DPaneP18RandomAccessStreamUs
/* 801B2EB4 001AFE14  4B FF FE A4 */	b .L_801B2D58
.L_801B2EB8:
/* 801B2EB8 001AFE18  BB 21 00 34 */	lmw r25, 0x34(r1)
/* 801B2EBC 001AFE1C  80 01 00 54 */	lwz r0, 0x54(r1)
/* 801B2EC0 001AFE20  38 21 00 50 */	addi r1, r1, 0x50
/* 801B2EC4 001AFE24  7C 08 03 A6 */	mtlr r0
/* 801B2EC8 001AFE28  4E 80 00 20 */	blr 

.global makeUserPane__9P2DScreenFUsP7P2DPaneP18RandomAccessStream
makeUserPane__9P2DScreenFUsP7P2DPaneP18RandomAccessStream:
/* 801B2ECC 001AFE2C  38 60 00 00 */	li r3, 0
/* 801B2ED0 001AFE30  4E 80 00 20 */	blr 

.global draw__9P2DScreenFiiPC14P2DGrafContext
draw__9P2DScreenFiiPC14P2DGrafContext:
/* 801B2ED4 001AFE34  7C 08 02 A6 */	mflr r0
/* 801B2ED8 001AFE38  90 01 00 04 */	stw r0, 4(r1)
/* 801B2EDC 001AFE3C  94 21 FE 18 */	stwu r1, -0x1e8(r1)
/* 801B2EE0 001AFE40  BF 61 01 D4 */	stmw r27, 0x1d4(r1)
/* 801B2EE4 001AFE44  7C DE 33 79 */	or. r30, r6, r6
/* 801B2EE8 001AFE48  3B 63 00 00 */	addi r27, r3, 0
/* 801B2EEC 001AFE4C  3B 84 00 00 */	addi r28, r4, 0
/* 801B2EF0 001AFE50  3B A5 00 00 */	addi r29, r5, 0
/* 801B2EF4 001AFE54  41 82 02 38 */	beq .L_801B312C
/* 801B2EF8 001AFE58  3C 60 80 2E */	lis r3, __vt__14P2DGrafContext@ha
/* 801B2EFC 001AFE5C  3B E3 05 D4 */	addi r31, r3, __vt__14P2DGrafContext@l
/* 801B2F00 001AFE60  93 E1 00 FC */	stw r31, 0xfc(r1)
/* 801B2F04 001AFE64  38 61 01 04 */	addi r3, r1, 0x104
/* 801B2F08 001AFE68  38 9E 00 08 */	addi r4, r30, 8
/* 801B2F0C 001AFE6C  80 1E 00 04 */	lwz r0, 4(r30)
/* 801B2F10 001AFE70  90 01 01 00 */	stw r0, 0x100(r1)
/* 801B2F14 001AFE74  48 00 07 39 */	bl copy__7PUTRectFRC7PUTRect
/* 801B2F18 001AFE78  38 61 01 0C */	addi r3, r1, 0x10c
/* 801B2F1C 001AFE7C  38 9E 00 10 */	addi r4, r30, 0x10
/* 801B2F20 001AFE80  48 00 07 2D */	bl copy__7PUTRectFRC7PUTRect
/* 801B2F24 001AFE84  88 1E 00 18 */	lbz r0, 0x18(r30)
/* 801B2F28 001AFE88  98 01 01 14 */	stb r0, 0x114(r1)
/* 801B2F2C 001AFE8C  88 1E 00 19 */	lbz r0, 0x19(r30)
/* 801B2F30 001AFE90  98 01 01 15 */	stb r0, 0x115(r1)
/* 801B2F34 001AFE94  88 1E 00 1A */	lbz r0, 0x1a(r30)
/* 801B2F38 001AFE98  98 01 01 16 */	stb r0, 0x116(r1)
/* 801B2F3C 001AFE9C  88 1E 00 1B */	lbz r0, 0x1b(r30)
/* 801B2F40 001AFEA0  98 01 01 17 */	stb r0, 0x117(r1)
/* 801B2F44 001AFEA4  88 1E 00 1C */	lbz r0, 0x1c(r30)
/* 801B2F48 001AFEA8  98 01 01 18 */	stb r0, 0x118(r1)
/* 801B2F4C 001AFEAC  88 1E 00 1D */	lbz r0, 0x1d(r30)
/* 801B2F50 001AFEB0  98 01 01 19 */	stb r0, 0x119(r1)
/* 801B2F54 001AFEB4  88 1E 00 1E */	lbz r0, 0x1e(r30)
/* 801B2F58 001AFEB8  98 01 01 1A */	stb r0, 0x11a(r1)
/* 801B2F5C 001AFEBC  88 1E 00 1F */	lbz r0, 0x1f(r30)
/* 801B2F60 001AFEC0  98 01 01 1B */	stb r0, 0x11b(r1)
/* 801B2F64 001AFEC4  88 1E 00 20 */	lbz r0, 0x20(r30)
/* 801B2F68 001AFEC8  98 01 01 1C */	stb r0, 0x11c(r1)
/* 801B2F6C 001AFECC  88 1E 00 21 */	lbz r0, 0x21(r30)
/* 801B2F70 001AFED0  98 01 01 1D */	stb r0, 0x11d(r1)
/* 801B2F74 001AFED4  88 1E 00 22 */	lbz r0, 0x22(r30)
/* 801B2F78 001AFED8  98 01 01 1E */	stb r0, 0x11e(r1)
/* 801B2F7C 001AFEDC  88 1E 00 23 */	lbz r0, 0x23(r30)
/* 801B2F80 001AFEE0  98 01 01 1F */	stb r0, 0x11f(r1)
/* 801B2F84 001AFEE4  88 1E 00 24 */	lbz r0, 0x24(r30)
/* 801B2F88 001AFEE8  98 01 01 20 */	stb r0, 0x120(r1)
/* 801B2F8C 001AFEEC  88 1E 00 25 */	lbz r0, 0x25(r30)
/* 801B2F90 001AFEF0  98 01 01 21 */	stb r0, 0x121(r1)
/* 801B2F94 001AFEF4  88 1E 00 26 */	lbz r0, 0x26(r30)
/* 801B2F98 001AFEF8  98 01 01 22 */	stb r0, 0x122(r1)
/* 801B2F9C 001AFEFC  88 1E 00 27 */	lbz r0, 0x27(r30)
/* 801B2FA0 001AFF00  98 01 01 23 */	stb r0, 0x123(r1)
/* 801B2FA4 001AFF04  88 1E 00 28 */	lbz r0, 0x28(r30)
/* 801B2FA8 001AFF08  98 01 01 24 */	stb r0, 0x124(r1)
/* 801B2FAC 001AFF0C  A8 1E 00 2A */	lha r0, 0x2a(r30)
/* 801B2FB0 001AFF10  B0 01 01 26 */	sth r0, 0x126(r1)
/* 801B2FB4 001AFF14  A8 1E 00 2C */	lha r0, 0x2c(r30)
/* 801B2FB8 001AFF18  B0 01 01 28 */	sth r0, 0x128(r1)
/* 801B2FBC 001AFF1C  80 7E 00 30 */	lwz r3, 0x30(r30)
/* 801B2FC0 001AFF20  80 1E 00 34 */	lwz r0, 0x34(r30)
/* 801B2FC4 001AFF24  90 61 01 2C */	stw r3, 0x12c(r1)
/* 801B2FC8 001AFF28  90 01 01 30 */	stw r0, 0x130(r1)
/* 801B2FCC 001AFF2C  80 7E 00 38 */	lwz r3, 0x38(r30)
/* 801B2FD0 001AFF30  80 1E 00 3C */	lwz r0, 0x3c(r30)
/* 801B2FD4 001AFF34  90 61 01 34 */	stw r3, 0x134(r1)
/* 801B2FD8 001AFF38  90 01 01 38 */	stw r0, 0x138(r1)
/* 801B2FDC 001AFF3C  80 7E 00 40 */	lwz r3, 0x40(r30)
/* 801B2FE0 001AFF40  80 1E 00 44 */	lwz r0, 0x44(r30)
/* 801B2FE4 001AFF44  90 61 01 3C */	stw r3, 0x13c(r1)
/* 801B2FE8 001AFF48  90 01 01 40 */	stw r0, 0x140(r1)
/* 801B2FEC 001AFF4C  80 7E 00 48 */	lwz r3, 0x48(r30)
/* 801B2FF0 001AFF50  80 1E 00 4C */	lwz r0, 0x4c(r30)
/* 801B2FF4 001AFF54  90 61 01 44 */	stw r3, 0x144(r1)
/* 801B2FF8 001AFF58  90 01 01 48 */	stw r0, 0x148(r1)
/* 801B2FFC 001AFF5C  80 7E 00 50 */	lwz r3, 0x50(r30)
/* 801B3000 001AFF60  80 1E 00 54 */	lwz r0, 0x54(r30)
/* 801B3004 001AFF64  90 61 01 4C */	stw r3, 0x14c(r1)
/* 801B3008 001AFF68  90 01 01 50 */	stw r0, 0x150(r1)
/* 801B300C 001AFF6C  80 7E 00 58 */	lwz r3, 0x58(r30)
/* 801B3010 001AFF70  80 1E 00 5C */	lwz r0, 0x5c(r30)
/* 801B3014 001AFF74  90 61 01 54 */	stw r3, 0x154(r1)
/* 801B3018 001AFF78  90 01 01 58 */	stw r0, 0x158(r1)
/* 801B301C 001AFF7C  80 7E 00 60 */	lwz r3, 0x60(r30)
/* 801B3020 001AFF80  80 1E 00 64 */	lwz r0, 0x64(r30)
/* 801B3024 001AFF84  90 61 01 5C */	stw r3, 0x15c(r1)
/* 801B3028 001AFF88  90 01 01 60 */	stw r0, 0x160(r1)
/* 801B302C 001AFF8C  80 7E 00 68 */	lwz r3, 0x68(r30)
/* 801B3030 001AFF90  80 1E 00 6C */	lwz r0, 0x6c(r30)
/* 801B3034 001AFF94  90 61 01 64 */	stw r3, 0x164(r1)
/* 801B3038 001AFF98  90 01 01 68 */	stw r0, 0x168(r1)
/* 801B303C 001AFF9C  80 7E 00 70 */	lwz r3, 0x70(r30)
/* 801B3040 001AFFA0  80 1E 00 74 */	lwz r0, 0x74(r30)
/* 801B3044 001AFFA4  90 61 01 6C */	stw r3, 0x16c(r1)
/* 801B3048 001AFFA8  90 01 01 70 */	stw r0, 0x170(r1)
/* 801B304C 001AFFAC  80 7E 00 78 */	lwz r3, 0x78(r30)
/* 801B3050 001AFFB0  80 1E 00 7C */	lwz r0, 0x7c(r30)
/* 801B3054 001AFFB4  90 61 01 74 */	stw r3, 0x174(r1)
/* 801B3058 001AFFB8  90 01 01 78 */	stw r0, 0x178(r1)
/* 801B305C 001AFFBC  80 7E 00 80 */	lwz r3, 0x80(r30)
/* 801B3060 001AFFC0  80 1E 00 84 */	lwz r0, 0x84(r30)
/* 801B3064 001AFFC4  90 61 01 7C */	stw r3, 0x17c(r1)
/* 801B3068 001AFFC8  90 01 01 80 */	stw r0, 0x180(r1)
/* 801B306C 001AFFCC  80 7E 00 88 */	lwz r3, 0x88(r30)
/* 801B3070 001AFFD0  80 1E 00 8C */	lwz r0, 0x8c(r30)
/* 801B3074 001AFFD4  90 61 01 84 */	stw r3, 0x184(r1)
/* 801B3078 001AFFD8  90 01 01 88 */	stw r0, 0x188(r1)
/* 801B307C 001AFFDC  80 7E 00 90 */	lwz r3, 0x90(r30)
/* 801B3080 001AFFE0  80 1E 00 94 */	lwz r0, 0x94(r30)
/* 801B3084 001AFFE4  90 61 01 8C */	stw r3, 0x18c(r1)
/* 801B3088 001AFFE8  90 01 01 90 */	stw r0, 0x190(r1)
/* 801B308C 001AFFEC  80 7E 00 98 */	lwz r3, 0x98(r30)
/* 801B3090 001AFFF0  80 1E 00 9C */	lwz r0, 0x9c(r30)
/* 801B3094 001AFFF4  90 61 01 94 */	stw r3, 0x194(r1)
/* 801B3098 001AFFF8  90 01 01 98 */	stw r0, 0x198(r1)
/* 801B309C 001AFFFC  80 7E 00 A0 */	lwz r3, 0xa0(r30)
/* 801B30A0 001B0000  80 1E 00 A4 */	lwz r0, 0xa4(r30)
/* 801B30A4 001B0004  90 61 01 9C */	stw r3, 0x19c(r1)
/* 801B30A8 001B0008  90 01 01 A0 */	stw r0, 0x1a0(r1)
/* 801B30AC 001B000C  80 7E 00 A8 */	lwz r3, 0xa8(r30)
/* 801B30B0 001B0010  80 1E 00 AC */	lwz r0, 0xac(r30)
/* 801B30B4 001B0014  90 61 01 A4 */	stw r3, 0x1a4(r1)
/* 801B30B8 001B0018  90 01 01 A8 */	stw r0, 0x1a8(r1)
/* 801B30BC 001B001C  80 DE 00 B0 */	lwz r6, 0xb0(r30)
/* 801B30C0 001B0020  7F 63 DB 78 */	mr r3, r27
/* 801B30C4 001B0024  80 1E 00 B4 */	lwz r0, 0xb4(r30)
/* 801B30C8 001B0028  38 9C 00 00 */	addi r4, r28, 0
/* 801B30CC 001B002C  38 BD 00 00 */	addi r5, r29, 0
/* 801B30D0 001B0030  90 C1 01 AC */	stw r6, 0x1ac(r1)
/* 801B30D4 001B0034  7F C6 F3 78 */	mr r6, r30
/* 801B30D8 001B0038  90 01 01 B0 */	stw r0, 0x1b0(r1)
/* 801B30DC 001B003C  80 1E 00 B8 */	lwz r0, 0xb8(r30)
/* 801B30E0 001B0040  90 01 01 B4 */	stw r0, 0x1b4(r1)
/* 801B30E4 001B0044  80 FE 00 BC */	lwz r7, 0xbc(r30)
/* 801B30E8 001B0048  80 1E 00 C0 */	lwz r0, 0xc0(r30)
/* 801B30EC 001B004C  90 E1 01 B8 */	stw r7, 0x1b8(r1)
/* 801B30F0 001B0050  90 01 01 BC */	stw r0, 0x1bc(r1)
/* 801B30F4 001B0054  80 1E 00 C4 */	lwz r0, 0xc4(r30)
/* 801B30F8 001B0058  90 01 01 C0 */	stw r0, 0x1c0(r1)
/* 801B30FC 001B005C  80 FE 00 C8 */	lwz r7, 0xc8(r30)
/* 801B3100 001B0060  80 1E 00 CC */	lwz r0, 0xcc(r30)
/* 801B3104 001B0064  90 E1 01 C4 */	stw r7, 0x1c4(r1)
/* 801B3108 001B0068  90 01 01 C8 */	stw r0, 0x1c8(r1)
/* 801B310C 001B006C  80 1E 00 D0 */	lwz r0, 0xd0(r30)
/* 801B3110 001B0070  90 01 01 CC */	stw r0, 0x1cc(r1)
/* 801B3114 001B0074  88 FB 00 EC */	lbz r7, 0xec(r27)
/* 801B3118 001B0078  4B FF DD 8D */	bl draw__7P2DPaneFiiPC14P2DGrafContextb
/* 801B311C 001B007C  38 61 00 FC */	addi r3, r1, 0xfc
/* 801B3120 001B0080  4B FF C9 81 */	bl setScissor__14P2DGrafContextFv
/* 801B3124 001B0084  93 E1 00 FC */	stw r31, 0xfc(r1)
/* 801B3128 001B0088  48 00 00 5C */	b .L_801B3184
.L_801B312C:
/* 801B312C 001B008C  38 61 00 18 */	addi r3, r1, 0x18
/* 801B3130 001B0090  38 80 00 00 */	li r4, 0
/* 801B3134 001B0094  38 A0 00 00 */	li r5, 0
/* 801B3138 001B0098  38 C0 02 80 */	li r6, 0x280
/* 801B313C 001B009C  38 E0 01 E0 */	li r7, 0x1e0
/* 801B3140 001B00A0  4B FF CB B1 */	bl __ct__13P2DOrthoGraphFiiii
/* 801B3144 001B00A4  38 61 00 18 */	addi r3, r1, 0x18
/* 801B3148 001B00A8  4B FF CC 6D */	bl setPort__13P2DOrthoGraphFv
/* 801B314C 001B00AC  88 FB 00 EC */	lbz r7, 0xec(r27)
/* 801B3150 001B00B0  38 7B 00 00 */	addi r3, r27, 0
/* 801B3154 001B00B4  38 9C 00 00 */	addi r4, r28, 0
/* 801B3158 001B00B8  38 BD 00 00 */	addi r5, r29, 0
/* 801B315C 001B00BC  38 C1 00 18 */	addi r6, r1, 0x18
/* 801B3160 001B00C0  4B FF DD 45 */	bl draw__7P2DPaneFiiPC14P2DGrafContextb
/* 801B3164 001B00C4  38 61 00 18 */	addi r3, r1, 0x18
/* 801B3168 001B00C8  4B FF C9 39 */	bl setScissor__14P2DGrafContextFv
/* 801B316C 001B00CC  3C 60 80 2E */	lis r3, __vt__13P2DOrthoGraph@ha
/* 801B3170 001B00D0  38 03 06 24 */	addi r0, r3, __vt__13P2DOrthoGraph@l
/* 801B3174 001B00D4  3C 60 80 2E */	lis r3, __vt__14P2DGrafContext@ha
/* 801B3178 001B00D8  90 01 00 18 */	stw r0, 0x18(r1)
/* 801B317C 001B00DC  38 03 05 D4 */	addi r0, r3, __vt__14P2DGrafContext@l
/* 801B3180 001B00E0  90 01 00 18 */	stw r0, 0x18(r1)
.L_801B3184:
/* 801B3184 001B00E4  38 60 00 00 */	li r3, 0
/* 801B3188 001B00E8  48 05 D5 A1 */	bl GXSetNumTexGens
/* 801B318C 001B00EC  38 60 00 01 */	li r3, 1
/* 801B3190 001B00F0  48 06 07 D5 */	bl GXSetNumTevStages
/* 801B3194 001B00F4  38 60 00 00 */	li r3, 0
/* 801B3198 001B00F8  38 80 00 04 */	li r4, 4
/* 801B319C 001B00FC  48 05 FE 01 */	bl GXSetTevOp
/* 801B31A0 001B0100  38 60 00 00 */	li r3, 0
/* 801B31A4 001B0104  38 80 00 FF */	li r4, 0xff
/* 801B31A8 001B0108  38 A0 00 FF */	li r5, 0xff
/* 801B31AC 001B010C  38 C0 00 04 */	li r6, 4
/* 801B31B0 001B0110  48 06 06 15 */	bl GXSetTevOrder
/* 801B31B4 001B0114  38 60 00 04 */	li r3, 4
/* 801B31B8 001B0118  38 80 00 00 */	li r4, 0
/* 801B31BC 001B011C  38 A0 00 00 */	li r5, 0
/* 801B31C0 001B0120  38 C0 00 01 */	li r6, 1
/* 801B31C4 001B0124  38 E0 00 00 */	li r7, 0
/* 801B31C8 001B0128  39 00 00 00 */	li r8, 0
/* 801B31CC 001B012C  39 20 00 02 */	li r9, 2
/* 801B31D0 001B0130  48 05 ED 51 */	bl GXSetChanCtrl
/* 801B31D4 001B0134  38 60 00 0D */	li r3, 0xd
/* 801B31D8 001B0138  38 80 00 00 */	li r4, 0
/* 801B31DC 001B013C  48 05 C2 25 */	bl GXSetVtxDesc
/* 801B31E0 001B0140  38 60 00 00 */	li r3, 0
/* 801B31E4 001B0144  48 05 DC 65 */	bl GXSetCullMode
/* 801B31E8 001B0148  BB 61 01 D4 */	lmw r27, 0x1d4(r1)
/* 801B31EC 001B014C  80 01 01 EC */	lwz r0, 0x1ec(r1)
/* 801B31F0 001B0150  38 21 01 E8 */	addi r1, r1, 0x1e8
/* 801B31F4 001B0154  7C 08 03 A6 */	mtlr r0
/* 801B31F8 001B0158  4E 80 00 20 */	blr 

.global search__9P2DScreenFUlb
search__9P2DScreenFUlb:
/* 801B31FC 001B015C  7C 08 02 A6 */	mflr r0
/* 801B3200 001B0160  28 04 00 00 */	cmplwi r4, 0
/* 801B3204 001B0164  90 01 00 04 */	stw r0, 4(r1)
/* 801B3208 001B0168  94 21 FF F8 */	stwu r1, -8(r1)
/* 801B320C 001B016C  40 82 00 0C */	bne .L_801B3218
/* 801B3210 001B0170  38 60 00 00 */	li r3, 0
/* 801B3214 001B0174  48 00 00 08 */	b .L_801B321C
.L_801B3218:
/* 801B3218 001B0178  4B FF E1 7D */	bl search__7P2DPaneFUlb
.L_801B321C:
/* 801B321C 001B017C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801B3220 001B0180  38 21 00 08 */	addi r1, r1, 8
/* 801B3224 001B0184  7C 08 03 A6 */	mtlr r0
/* 801B3228 001B0188  4E 80 00 20 */	blr 

.global loadResource__9P2DScreenFv
loadResource__9P2DScreenFv:
/* 801B322C 001B018C  7C 08 02 A6 */	mflr r0
/* 801B3230 001B0190  90 01 00 04 */	stw r0, 4(r1)
/* 801B3234 001B0194  94 21 FF F8 */	stwu r1, -8(r1)
/* 801B3238 001B0198  4B FF E4 5D */	bl loadChildResource__7P2DPaneFv
/* 801B323C 001B019C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801B3240 001B01A0  38 21 00 08 */	addi r1, r1, 8
/* 801B3244 001B01A4  7C 08 03 A6 */	mtlr r0
/* 801B3248 001B01A8  4E 80 00 20 */	blr 

.global makeResName__9P2DScreenFPCcPc
makeResName__9P2DScreenFPCcPc:
/* 801B324C 001B01AC  7C 08 02 A6 */	mflr r0
/* 801B3250 001B01B0  90 01 00 04 */	stw r0, 4(r1)
/* 801B3254 001B01B4  94 21 FF F8 */	stwu r1, -8(r1)
/* 801B3258 001B01B8  80 6D 2D EC */	lwz r3, gsys@sda21(r13)
/* 801B325C 001B01BC  80 63 00 44 */	lwz r3, 0x44(r3)
/* 801B3260 001B01C0  48 03 F1 C5 */	bl makePathName__3zenFPCcPCcPc
/* 801B3264 001B01C4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801B3268 001B01C8  38 21 00 08 */	addi r1, r1, 8
/* 801B326C 001B01CC  7C 08 03 A6 */	mtlr r0
/* 801B3270 001B01D0  4E 80 00 20 */	blr 

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 8
lbl_802E0768:
	.asciz "P2DScreen.cpp"
.balign 4
lbl_802E0778:
	.asciz "P2DScreen"
.balign 4
lbl_802E0784:
	.4byte .L_801B2D8C
	.4byte .L_801B2D90
	.4byte .L_801B2DC0
	.4byte .L_801B2D58
	.4byte .L_801B2D58
	.4byte .L_801B2D58
	.4byte .L_801B2D58
	.4byte .L_801B2D58
	.4byte .L_801B2D58
	.4byte .L_801B2D58
	.4byte .L_801B2D58
	.4byte .L_801B2D58
	.4byte .L_801B2D58
	.4byte .L_801B2D58
	.4byte .L_801B2D58
	.4byte .L_801B2D58
	.4byte .L_801B2DD8
	.4byte .L_801B2E40
	.4byte .L_801B2E68
	.4byte .L_801B2E90
lbl_802E07D4:
	.4byte __RTTI__7P2DPane
	.4byte 0x00000000
	.4byte 0x00000000
.global __vt__9P2DScreen
__vt__9P2DScreen:
	.4byte __RTTI__9P2DScreen
	.4byte 0
	.4byte loadResource__9P2DScreenFv
	.4byte makeResident__7P2DPaneFv
	.4byte __dt__9P2DScreenFv
	.4byte move__7P2DPaneFii
	.4byte move__7P2DPaneFR8Vector3f
	.4byte move__7P2DPaneFiif
	.4byte moveZ__7P2DPaneFf
	.4byte add__7P2DPaneFii
	.4byte resize__7P2DPaneFii
	.4byte drawSelf__7P2DPaneFii
	.4byte drawSelf__7P2DPaneFiiP8Matrix4f
	.4byte search__9P2DScreenFUlb
	.4byte makeMatrix__7P2DPaneFii
	.4byte makeUserPane__9P2DScreenFUsP7P2DPaneP18RandomAccessStream

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.balign 8
lbl_803E6640:
	.asciz "P2DPane"
.balign 4
__RTTI__7P2DPane:
	.4byte lbl_803E6640
	.4byte 0
__RTTI__9P2DScreen:
	.4byte lbl_802E0778
	.4byte lbl_802E07D4
