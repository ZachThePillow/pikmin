.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.global ClampStick
ClampStick:
/* 80203BCC 00200B2C  88 03 00 00 */	lbz r0, 0(r3)
/* 80203BD0 00200B30  89 84 00 00 */	lbz r12, 0(r4)
/* 80203BD4 00200B34  7C 00 07 75 */	extsb. r0, r0
/* 80203BD8 00200B38  7D 8C 07 74 */	extsb r12, r12
/* 80203BDC 00200B3C  7C 0B 03 78 */	mr r11, r0
/* 80203BE0 00200B40  41 80 00 0C */	blt lbl_80203BEC
/* 80203BE4 00200B44  38 00 00 01 */	li r0, 1
/* 80203BE8 00200B48  48 00 00 0C */	b lbl_80203BF4
lbl_80203BEC:
/* 80203BEC 00200B4C  38 00 FF FF */	li r0, -1
/* 80203BF0 00200B50  7D 6B 00 D0 */	neg r11, r11
lbl_80203BF4:
/* 80203BF4 00200B54  2C 0C 00 00 */	cmpwi r12, 0
/* 80203BF8 00200B58  41 80 00 0C */	blt lbl_80203C04
/* 80203BFC 00200B5C  39 00 00 01 */	li r8, 1
/* 80203C00 00200B60  48 00 00 0C */	b lbl_80203C0C
lbl_80203C04:
/* 80203C04 00200B64  39 00 FF FF */	li r8, -1
/* 80203C08 00200B68  7D 8C 00 D0 */	neg r12, r12
lbl_80203C0C:
/* 80203C0C 00200B6C  7C E7 07 74 */	extsb r7, r7
/* 80203C10 00200B70  7C 0B 38 00 */	cmpw r11, r7
/* 80203C14 00200B74  41 81 00 0C */	bgt lbl_80203C20
/* 80203C18 00200B78  39 60 00 00 */	li r11, 0
/* 80203C1C 00200B7C  48 00 00 08 */	b lbl_80203C24
lbl_80203C20:
/* 80203C20 00200B80  7D 67 58 50 */	subf r11, r7, r11
lbl_80203C24:
/* 80203C24 00200B84  7C 0C 38 00 */	cmpw r12, r7
/* 80203C28 00200B88  41 81 00 0C */	bgt lbl_80203C34
/* 80203C2C 00200B8C  39 80 00 00 */	li r12, 0
/* 80203C30 00200B90  48 00 00 08 */	b lbl_80203C38
lbl_80203C34:
/* 80203C34 00200B94  7D 87 60 50 */	subf r12, r7, r12
lbl_80203C38:
/* 80203C38 00200B98  2C 0B 00 00 */	cmpwi r11, 0
/* 80203C3C 00200B9C  40 82 00 1C */	bne lbl_80203C58
/* 80203C40 00200BA0  2C 0C 00 00 */	cmpwi r12, 0
/* 80203C44 00200BA4  40 82 00 14 */	bne lbl_80203C58
/* 80203C48 00200BA8  38 00 00 00 */	li r0, 0
/* 80203C4C 00200BAC  98 04 00 00 */	stb r0, 0(r4)
/* 80203C50 00200BB0  98 03 00 00 */	stb r0, 0(r3)
/* 80203C54 00200BB4  4E 80 00 20 */	blr 
lbl_80203C58:
/* 80203C58 00200BB8  7C C6 07 74 */	extsb r6, r6
/* 80203C5C 00200BBC  7D 26 61 D6 */	mullw r9, r6, r12
/* 80203C60 00200BC0  7C E6 59 D6 */	mullw r7, r6, r11
/* 80203C64 00200BC4  7C 09 38 00 */	cmpw r9, r7
/* 80203C68 00200BC8  41 81 00 44 */	bgt lbl_80203CAC
/* 80203C6C 00200BCC  7C A9 07 74 */	extsb r9, r5
/* 80203C70 00200BD0  7C A6 48 50 */	subf r5, r6, r9
/* 80203C74 00200BD4  7C AC 29 D6 */	mullw r5, r12, r5
/* 80203C78 00200BD8  7D 26 49 D6 */	mullw r9, r6, r9
/* 80203C7C 00200BDC  7C E7 2A 14 */	add r7, r7, r5
/* 80203C80 00200BE0  7C 09 38 00 */	cmpw r9, r7
/* 80203C84 00200BE4  40 80 00 64 */	bge lbl_80203CE8
/* 80203C88 00200BE8  7C CB 49 D6 */	mullw r6, r11, r9
/* 80203C8C 00200BEC  7C AC 49 D6 */	mullw r5, r12, r9
/* 80203C90 00200BF0  7C C6 3B D6 */	divw r6, r6, r7
/* 80203C94 00200BF4  7C A5 3B D6 */	divw r5, r5, r7
/* 80203C98 00200BF8  7C C6 07 74 */	extsb r6, r6
/* 80203C9C 00200BFC  7C A5 07 74 */	extsb r5, r5
/* 80203CA0 00200C00  39 66 00 00 */	addi r11, r6, 0
/* 80203CA4 00200C04  39 85 00 00 */	addi r12, r5, 0
/* 80203CA8 00200C08  48 00 00 40 */	b lbl_80203CE8
lbl_80203CAC:
/* 80203CAC 00200C0C  7C A7 07 74 */	extsb r7, r5
/* 80203CB0 00200C10  7C A6 38 50 */	subf r5, r6, r7
/* 80203CB4 00200C14  7C AB 29 D6 */	mullw r5, r11, r5
/* 80203CB8 00200C18  7D 46 39 D6 */	mullw r10, r6, r7
/* 80203CBC 00200C1C  7C E9 2A 14 */	add r7, r9, r5
/* 80203CC0 00200C20  7C 0A 38 00 */	cmpw r10, r7
/* 80203CC4 00200C24  40 80 00 24 */	bge lbl_80203CE8
/* 80203CC8 00200C28  7C CB 51 D6 */	mullw r6, r11, r10
/* 80203CCC 00200C2C  7C AC 51 D6 */	mullw r5, r12, r10
/* 80203CD0 00200C30  7C C6 3B D6 */	divw r6, r6, r7
/* 80203CD4 00200C34  7C A5 3B D6 */	divw r5, r5, r7
/* 80203CD8 00200C38  7C C6 07 74 */	extsb r6, r6
/* 80203CDC 00200C3C  7C A5 07 74 */	extsb r5, r5
/* 80203CE0 00200C40  39 66 00 00 */	addi r11, r6, 0
/* 80203CE4 00200C44  39 85 00 00 */	addi r12, r5, 0
lbl_80203CE8:
/* 80203CE8 00200C48  7C A0 59 D6 */	mullw r5, r0, r11
/* 80203CEC 00200C4C  7C 08 61 D6 */	mullw r0, r8, r12
/* 80203CF0 00200C50  98 A3 00 00 */	stb r5, 0(r3)
/* 80203CF4 00200C54  98 04 00 00 */	stb r0, 0(r4)
/* 80203CF8 00200C58  4E 80 00 20 */	blr 

.global PADClamp
PADClamp:
/* 80203CFC 00200C5C  7C 08 02 A6 */	mflr r0
/* 80203D00 00200C60  90 01 00 04 */	stw r0, 4(r1)
/* 80203D04 00200C64  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80203D08 00200C68  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80203D0C 00200C6C  3B E0 00 00 */	li r31, 0
/* 80203D10 00200C70  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80203D14 00200C74  3B C3 00 00 */	addi r30, r3, 0
/* 80203D18 00200C78  93 A1 00 14 */	stw r29, 0x14(r1)
lbl_80203D1C:
/* 80203D1C 00200C7C  88 1E 00 0A */	lbz r0, 0xa(r30)
/* 80203D20 00200C80  7C 00 07 75 */	extsb. r0, r0
/* 80203D24 00200C84  40 82 00 B4 */	bne lbl_80203DD8
/* 80203D28 00200C88  3B AD 2A 30 */	addi r29, r13, ClampRegion@sda21
/* 80203D2C 00200C8C  88 BD 00 03 */	lbz r5, 3(r29)
/* 80203D30 00200C90  38 7E 00 02 */	addi r3, r30, 2
/* 80203D34 00200C94  88 DD 00 04 */	lbz r6, 4(r29)
/* 80203D38 00200C98  38 9E 00 03 */	addi r4, r30, 3
/* 80203D3C 00200C9C  88 FD 00 02 */	lbz r7, 2(r29)
/* 80203D40 00200CA0  4B FF FE 8D */	bl ClampStick
/* 80203D44 00200CA4  88 BD 00 06 */	lbz r5, 6(r29)
/* 80203D48 00200CA8  38 7E 00 04 */	addi r3, r30, 4
/* 80203D4C 00200CAC  88 DD 00 07 */	lbz r6, 7(r29)
/* 80203D50 00200CB0  38 9E 00 05 */	addi r4, r30, 5
/* 80203D54 00200CB4  88 FD 00 05 */	lbz r7, 5(r29)
/* 80203D58 00200CB8  4B FF FE 75 */	bl ClampStick
/* 80203D5C 00200CBC  88 7E 00 06 */	lbz r3, 6(r30)
/* 80203D60 00200CC0  88 0D 2A 30 */	lbz r0, ClampRegion@sda21(r13)
/* 80203D64 00200CC4  7C 03 00 40 */	cmplw r3, r0
/* 80203D68 00200CC8  41 81 00 10 */	bgt lbl_80203D78
/* 80203D6C 00200CCC  38 00 00 00 */	li r0, 0
/* 80203D70 00200CD0  98 1E 00 06 */	stb r0, 6(r30)
/* 80203D74 00200CD4  48 00 00 24 */	b lbl_80203D98
lbl_80203D78:
/* 80203D78 00200CD8  88 1D 00 01 */	lbz r0, 1(r29)
/* 80203D7C 00200CDC  7C 00 18 40 */	cmplw r0, r3
/* 80203D80 00200CE0  40 80 00 08 */	bge lbl_80203D88
/* 80203D84 00200CE4  98 1E 00 06 */	stb r0, 6(r30)
lbl_80203D88:
/* 80203D88 00200CE8  88 6D 2A 30 */	lbz r3, ClampRegion@sda21(r13)
/* 80203D8C 00200CEC  88 1E 00 06 */	lbz r0, 6(r30)
/* 80203D90 00200CF0  7C 03 00 50 */	subf r0, r3, r0
/* 80203D94 00200CF4  98 1E 00 06 */	stb r0, 6(r30)
lbl_80203D98:
/* 80203D98 00200CF8  88 9E 00 07 */	lbz r4, 7(r30)
/* 80203D9C 00200CFC  88 0D 2A 30 */	lbz r0, ClampRegion@sda21(r13)
/* 80203DA0 00200D00  7C 04 00 40 */	cmplw r4, r0
/* 80203DA4 00200D04  41 81 00 10 */	bgt lbl_80203DB4
/* 80203DA8 00200D08  38 00 00 00 */	li r0, 0
/* 80203DAC 00200D0C  98 1E 00 07 */	stb r0, 7(r30)
/* 80203DB0 00200D10  48 00 00 28 */	b lbl_80203DD8
lbl_80203DB4:
/* 80203DB4 00200D14  38 6D 2A 30 */	addi r3, r13, ClampRegion@sda21
/* 80203DB8 00200D18  88 03 00 01 */	lbz r0, 1(r3)
/* 80203DBC 00200D1C  7C 00 20 40 */	cmplw r0, r4
/* 80203DC0 00200D20  40 80 00 08 */	bge lbl_80203DC8
/* 80203DC4 00200D24  98 1E 00 07 */	stb r0, 7(r30)
lbl_80203DC8:
/* 80203DC8 00200D28  88 6D 2A 30 */	lbz r3, ClampRegion@sda21(r13)
/* 80203DCC 00200D2C  88 1E 00 07 */	lbz r0, 7(r30)
/* 80203DD0 00200D30  7C 03 00 50 */	subf r0, r3, r0
/* 80203DD4 00200D34  98 1E 00 07 */	stb r0, 7(r30)
lbl_80203DD8:
/* 80203DD8 00200D38  3B FF 00 01 */	addi r31, r31, 1
/* 80203DDC 00200D3C  2C 1F 00 04 */	cmpwi r31, 4
/* 80203DE0 00200D40  3B DE 00 0C */	addi r30, r30, 0xc
/* 80203DE4 00200D44  41 80 FF 38 */	blt lbl_80203D1C
/* 80203DE8 00200D48  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80203DEC 00200D4C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80203DF0 00200D50  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80203DF4 00200D54  7C 08 03 A6 */	mtlr r0
/* 80203DF8 00200D58  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80203DFC 00200D5C  38 21 00 20 */	addi r1, r1, 0x20
/* 80203E00 00200D60  4E 80 00 20 */	blr 

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.balign 8
.global ClampRegion
ClampRegion:
	.4byte 0x1EB40F48
	.4byte 0x280F3B1F
