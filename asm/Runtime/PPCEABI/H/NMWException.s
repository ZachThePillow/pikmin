.include "macros.inc"
.file "NMWException.cp"

# 0x800054C0..0x80005500 | size: 0x40
.section extab, "a"
.balign 4

# extab:0x0 | 0x800054C0 | size: 0x8
.obj "@152", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r26-r31
 */
	.4byte 0x30080000
	.4byte 0x00000000
.endobj "@152"

# extab:0x8 | 0x800054C8 | size: 0x18
.obj "@174", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r28-r31
 * 
 * PC actions:
 * PC=00000064, Action: 000010
 * 
 * Exception actions:
 * 000010:
 * Type: DESTROYLOCAL
 * Local: 0x1C(SP)
 * Dtor: "__dt__26__partial_array_destructorFv".
 */
	.4byte 0x20080000
	.4byte 0x00000064
	.4byte 0x00000010
	.4byte 0x00000000
	.4byte 0x8200001C
	.4byte __dt__26__partial_array_destructorFv
.endobj "@174"

# extab:0x20 | 0x800054E0 | size: 0x8
.obj "@182", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r29-r31
 */
	.4byte 0x18080000
	.4byte 0x00000000
.endobj "@182"

# extab:0x28 | 0x800054E8 | size: 0x18
.obj "@201", local
/*
 * Flag values:
 * Has Elf Vector: No
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 * Saved GPR range: r27-r31
 * 
 * PC actions:
 * PC=00000074, Action: 000010
 * 
 * Exception actions:
 * 000010:
 * Type: DESTROYLOCAL
 * Local: 0x1C(SP)
 * Dtor: "__dt__26__partial_array_destructorFv".
 */
	.4byte 0x28080000
	.4byte 0x00000074
	.4byte 0x00000010
	.4byte 0x00000000
	.4byte 0x8200001C
	.4byte __dt__26__partial_array_destructorFv
.endobj "@201"

# 0x80005500..0x80005530 | size: 0x30
.section extabindex, "a"
.balign 4

# extabindex:0x0 | 0x80005500 | size: 0xC
.obj "@153", local
	.4byte __destroy_new_array
	.4byte 0x0000007C
	.4byte "@152"
.endobj "@153"

# extabindex:0xC | 0x8000550C | size: 0xC
.obj "@175", local
	.4byte __construct_array
	.4byte 0x00000100
	.4byte "@174"
.endobj "@175"

# extabindex:0x18 | 0x80005518 | size: 0xC
.obj "@183", local
	.4byte __dt__26__partial_array_destructorFv
	.4byte 0x000000B8
	.4byte "@182"
.endobj "@183"

# extabindex:0x24 | 0x80005524 | size: 0xC
.obj "@202", local
	.4byte __construct_new_array
	.4byte 0x00000108
	.4byte "@201"
.endobj "@202"

# 0x802149F4..0x80214D30 | size: 0x33C
.text
.balign 4

# .text:0x0 | 0x802149F4 | size: 0x7C
.fn __destroy_new_array, global
/* 802149F4 00211954  7C 08 02 A6 */	mflr r0
/* 802149F8 00211958  90 01 00 04 */	stw r0, 0x4(r1)
/* 802149FC 0021195C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80214A00 00211960  BF 41 00 10 */	stmw r26, 0x10(r1)
/* 80214A04 00211964  7C 7A 1B 79 */	mr. r26, r3
/* 80214A08 00211968  3B 64 00 00 */	addi r27, r4, 0x0
/* 80214A0C 0021196C  41 82 00 50 */	beq .L_80214A5C
/* 80214A10 00211970  28 1B 00 00 */	cmplwi r27, 0x0
/* 80214A14 00211974  41 82 00 40 */	beq .L_80214A54
/* 80214A18 00211978  83 DA FF F8 */	lwz r30, -0x8(r26)
/* 80214A1C 0021197C  3B A0 00 00 */	li r29, 0x0
/* 80214A20 00211980  83 FA FF FC */	lwz r31, -0x4(r26)
/* 80214A24 00211984  7C 1E F9 D6 */	mullw r0, r30, r31
/* 80214A28 00211988  7F 9A 02 14 */	add r28, r26, r0
/* 80214A2C 0021198C  48 00 00 20 */	b .L_80214A4C
.L_80214A30:
/* 80214A30 00211990  39 9B 00 00 */	addi r12, r27, 0x0
/* 80214A34 00211994  7F 9E E0 50 */	subf r28, r30, r28
/* 80214A38 00211998  7D 88 03 A6 */	mtlr r12
/* 80214A3C 0021199C  38 7C 00 00 */	addi r3, r28, 0x0
/* 80214A40 002119A0  38 80 FF FF */	li r4, -0x1
/* 80214A44 002119A4  4E 80 00 21 */	blrl
/* 80214A48 002119A8  3B BD 00 01 */	addi r29, r29, 0x1
.L_80214A4C:
/* 80214A4C 002119AC  7C 1D F8 40 */	cmplw r29, r31
/* 80214A50 002119B0  41 80 FF E0 */	blt .L_80214A30
.L_80214A54:
/* 80214A54 002119B4  38 7A FF F8 */	subi r3, r26, 0x8
/* 80214A58 002119B8  4B E3 27 59 */	bl __dla__FPv
.L_80214A5C:
/* 80214A5C 002119BC  BB 41 00 10 */	lmw r26, 0x10(r1)
/* 80214A60 002119C0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80214A64 002119C4  38 21 00 28 */	addi r1, r1, 0x28
/* 80214A68 002119C8  7C 08 03 A6 */	mtlr r0
/* 80214A6C 002119CC  4E 80 00 20 */	blr
.endfn __destroy_new_array

# .text:0x7C | 0x80214A70 | size: 0x100
.fn __construct_array, global
/* 80214A70 002119D0  7C 08 02 A6 */	mflr r0
/* 80214A74 002119D4  90 01 00 04 */	stw r0, 0x4(r1)
/* 80214A78 002119D8  38 00 00 00 */	li r0, 0x0
/* 80214A7C 002119DC  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80214A80 002119E0  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80214A84 002119E4  7C 7F 1B 78 */	mr r31, r3
/* 80214A88 002119E8  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80214A8C 002119EC  3B C7 00 00 */	addi r30, r7, 0x0
/* 80214A90 002119F0  93 A1 00 34 */	stw r29, 0x34(r1)
/* 80214A94 002119F4  3B A6 00 00 */	addi r29, r6, 0x0
/* 80214A98 002119F8  93 81 00 30 */	stw r28, 0x30(r1)
/* 80214A9C 002119FC  3B 84 00 00 */	addi r28, r4, 0x0
/* 80214AA0 00211A00  90 61 00 1C */	stw r3, 0x1c(r1)
/* 80214AA4 00211A04  93 A1 00 20 */	stw r29, 0x20(r1)
/* 80214AA8 00211A08  93 C1 00 24 */	stw r30, 0x24(r1)
/* 80214AAC 00211A0C  90 A1 00 28 */	stw r5, 0x28(r1)
/* 80214AB0 00211A10  80 61 00 24 */	lwz r3, 0x24(r1)
/* 80214AB4 00211A14  90 61 00 2C */	stw r3, 0x2c(r1)
/* 80214AB8 00211A18  90 01 00 2C */	stw r0, 0x2c(r1)
/* 80214ABC 00211A1C  48 00 00 28 */	b .L_80214AE4
.L_80214AC0:
/* 80214AC0 00211A20  39 9C 00 00 */	addi r12, r28, 0x0
/* 80214AC4 00211A24  7D 88 03 A6 */	mtlr r12
/* 80214AC8 00211A28  38 7F 00 00 */	addi r3, r31, 0x0
/* 80214ACC 00211A2C  38 80 00 01 */	li r4, 0x1
/* 80214AD0 00211A30  4E 80 00 21 */	blrl
/* 80214AD4 00211A34  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 80214AD8 00211A38  7F FF EA 14 */	add r31, r31, r29
/* 80214ADC 00211A3C  38 03 00 01 */	addi r0, r3, 0x1
/* 80214AE0 00211A40  90 01 00 2C */	stw r0, 0x2c(r1)
.L_80214AE4:
/* 80214AE4 00211A44  80 81 00 2C */	lwz r4, 0x2c(r1)
/* 80214AE8 00211A48  7C 04 F0 40 */	cmplw r4, r30
/* 80214AEC 00211A4C  41 80 FF D4 */	blt .L_80214AC0
/* 80214AF0 00211A50  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80214AF4 00211A54  7C 04 00 40 */	cmplw r4, r0
/* 80214AF8 00211A58  40 80 00 58 */	bge .L_80214B50
/* 80214AFC 00211A5C  80 01 00 28 */	lwz r0, 0x28(r1)
/* 80214B00 00211A60  28 00 00 00 */	cmplwi r0, 0x0
/* 80214B04 00211A64  41 82 00 4C */	beq .L_80214B50
/* 80214B08 00211A68  80 01 00 20 */	lwz r0, 0x20(r1)
/* 80214B0C 00211A6C  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80214B10 00211A70  7C 00 21 D6 */	mullw r0, r0, r4
/* 80214B14 00211A74  7F E3 02 14 */	add r31, r3, r0
/* 80214B18 00211A78  48 00 00 2C */	b .L_80214B44
.L_80214B1C:
/* 80214B1C 00211A7C  80 01 00 20 */	lwz r0, 0x20(r1)
/* 80214B20 00211A80  38 80 FF FF */	li r4, -0x1
/* 80214B24 00211A84  81 81 00 28 */	lwz r12, 0x28(r1)
/* 80214B28 00211A88  7F E0 F8 50 */	subf r31, r0, r31
/* 80214B2C 00211A8C  7D 88 03 A6 */	mtlr r12
/* 80214B30 00211A90  38 7F 00 00 */	addi r3, r31, 0x0
/* 80214B34 00211A94  4E 80 00 21 */	blrl
/* 80214B38 00211A98  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 80214B3C 00211A9C  38 03 FF FF */	subi r0, r3, 0x1
/* 80214B40 00211AA0  90 01 00 2C */	stw r0, 0x2c(r1)
.L_80214B44:
/* 80214B44 00211AA4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80214B48 00211AA8  28 00 00 00 */	cmplwi r0, 0x0
/* 80214B4C 00211AAC  40 82 FF D0 */	bne .L_80214B1C
.L_80214B50:
/* 80214B50 00211AB0  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80214B54 00211AB4  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80214B58 00211AB8  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80214B5C 00211ABC  7C 08 03 A6 */	mtlr r0
/* 80214B60 00211AC0  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80214B64 00211AC4  83 81 00 30 */	lwz r28, 0x30(r1)
/* 80214B68 00211AC8  38 21 00 40 */	addi r1, r1, 0x40
/* 80214B6C 00211ACC  4E 80 00 20 */	blr
.endfn __construct_array

# .text:0x17C | 0x80214B70 | size: 0xB8
# __partial_array_destructor::~__partial_array_destructor()
.fn __dt__26__partial_array_destructorFv, weak
/* 80214B70 00211AD0  7C 08 02 A6 */	mflr r0
/* 80214B74 00211AD4  90 01 00 04 */	stw r0, 0x4(r1)
/* 80214B78 00211AD8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80214B7C 00211ADC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80214B80 00211AE0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80214B84 00211AE4  3B C4 00 00 */	addi r30, r4, 0x0
/* 80214B88 00211AE8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80214B8C 00211AEC  7C 7D 1B 79 */	mr. r29, r3
/* 80214B90 00211AF0  41 82 00 78 */	beq .L_80214C08
/* 80214B94 00211AF4  80 9D 00 10 */	lwz r4, 0x10(r29)
/* 80214B98 00211AF8  80 1D 00 08 */	lwz r0, 0x8(r29)
/* 80214B9C 00211AFC  7C 04 00 40 */	cmplw r4, r0
/* 80214BA0 00211B00  40 80 00 58 */	bge .L_80214BF8
/* 80214BA4 00211B04  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80214BA8 00211B08  28 00 00 00 */	cmplwi r0, 0x0
/* 80214BAC 00211B0C  41 82 00 4C */	beq .L_80214BF8
/* 80214BB0 00211B10  80 1D 00 04 */	lwz r0, 0x4(r29)
/* 80214BB4 00211B14  80 7D 00 00 */	lwz r3, 0x0(r29)
/* 80214BB8 00211B18  7C 00 21 D6 */	mullw r0, r0, r4
/* 80214BBC 00211B1C  7F E3 02 14 */	add r31, r3, r0
/* 80214BC0 00211B20  48 00 00 2C */	b .L_80214BEC
.L_80214BC4:
/* 80214BC4 00211B24  80 1D 00 04 */	lwz r0, 0x4(r29)
/* 80214BC8 00211B28  38 80 FF FF */	li r4, -0x1
/* 80214BCC 00211B2C  81 9D 00 0C */	lwz r12, 0xc(r29)
/* 80214BD0 00211B30  7F E0 F8 50 */	subf r31, r0, r31
/* 80214BD4 00211B34  7D 88 03 A6 */	mtlr r12
/* 80214BD8 00211B38  38 7F 00 00 */	addi r3, r31, 0x0
/* 80214BDC 00211B3C  4E 80 00 21 */	blrl
/* 80214BE0 00211B40  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 80214BE4 00211B44  38 03 FF FF */	subi r0, r3, 0x1
/* 80214BE8 00211B48  90 1D 00 10 */	stw r0, 0x10(r29)
.L_80214BEC:
/* 80214BEC 00211B4C  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 80214BF0 00211B50  28 00 00 00 */	cmplwi r0, 0x0
/* 80214BF4 00211B54  40 82 FF D0 */	bne .L_80214BC4
.L_80214BF8:
/* 80214BF8 00211B58  7F C0 07 35 */	extsh. r0, r30
/* 80214BFC 00211B5C  40 81 00 0C */	ble .L_80214C08
/* 80214C00 00211B60  7F A3 EB 78 */	mr r3, r29
/* 80214C04 00211B64  4B E3 25 A9 */	bl __dl__FPv
.L_80214C08:
/* 80214C08 00211B68  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80214C0C 00211B6C  7F A3 EB 78 */	mr r3, r29
/* 80214C10 00211B70  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80214C14 00211B74  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80214C18 00211B78  7C 08 03 A6 */	mtlr r0
/* 80214C1C 00211B7C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80214C20 00211B80  38 21 00 20 */	addi r1, r1, 0x20
/* 80214C24 00211B84  4E 80 00 20 */	blr
.endfn __dt__26__partial_array_destructorFv

# .text:0x234 | 0x80214C28 | size: 0x108
.fn __construct_new_array, global
/* 80214C28 00211B88  7C 08 02 A6 */	mflr r0
/* 80214C2C 00211B8C  90 01 00 04 */	stw r0, 0x4(r1)
/* 80214C30 00211B90  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 80214C34 00211B94  BF 61 00 34 */	stmw r27, 0x34(r1)
/* 80214C38 00211B98  7C 7E 1B 79 */	mr. r30, r3
/* 80214C3C 00211B9C  3B 64 00 00 */	addi r27, r4, 0x0
/* 80214C40 00211BA0  3B 86 00 00 */	addi r28, r6, 0x0
/* 80214C44 00211BA4  3B A7 00 00 */	addi r29, r7, 0x0
/* 80214C48 00211BA8  41 82 00 D0 */	beq .L_80214D18
/* 80214C4C 00211BAC  93 9E 00 00 */	stw r28, 0x0(r30)
/* 80214C50 00211BB0  28 1B 00 00 */	cmplwi r27, 0x0
/* 80214C54 00211BB4  93 BE 00 04 */	stw r29, 0x4(r30)
/* 80214C58 00211BB8  3B DE 00 08 */	addi r30, r30, 0x8
/* 80214C5C 00211BBC  41 82 00 BC */	beq .L_80214D18
/* 80214C60 00211BC0  93 C1 00 1C */	stw r30, 0x1c(r1)
/* 80214C64 00211BC4  38 00 00 00 */	li r0, 0x0
/* 80214C68 00211BC8  3B FE 00 00 */	addi r31, r30, 0x0
/* 80214C6C 00211BCC  93 81 00 20 */	stw r28, 0x20(r1)
/* 80214C70 00211BD0  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80214C74 00211BD4  90 A1 00 28 */	stw r5, 0x28(r1)
/* 80214C78 00211BD8  80 61 00 24 */	lwz r3, 0x24(r1)
/* 80214C7C 00211BDC  90 61 00 2C */	stw r3, 0x2c(r1)
/* 80214C80 00211BE0  90 01 00 2C */	stw r0, 0x2c(r1)
/* 80214C84 00211BE4  48 00 00 28 */	b .L_80214CAC
.L_80214C88:
/* 80214C88 00211BE8  39 9B 00 00 */	addi r12, r27, 0x0
/* 80214C8C 00211BEC  7D 88 03 A6 */	mtlr r12
/* 80214C90 00211BF0  38 7F 00 00 */	addi r3, r31, 0x0
/* 80214C94 00211BF4  38 80 00 01 */	li r4, 0x1
/* 80214C98 00211BF8  4E 80 00 21 */	blrl
/* 80214C9C 00211BFC  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 80214CA0 00211C00  7F FF E2 14 */	add r31, r31, r28
/* 80214CA4 00211C04  38 03 00 01 */	addi r0, r3, 0x1
/* 80214CA8 00211C08  90 01 00 2C */	stw r0, 0x2c(r1)
.L_80214CAC:
/* 80214CAC 00211C0C  80 81 00 2C */	lwz r4, 0x2c(r1)
/* 80214CB0 00211C10  7C 04 E8 40 */	cmplw r4, r29
/* 80214CB4 00211C14  41 80 FF D4 */	blt .L_80214C88
/* 80214CB8 00211C18  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80214CBC 00211C1C  7C 04 00 40 */	cmplw r4, r0
/* 80214CC0 00211C20  40 80 00 58 */	bge .L_80214D18
/* 80214CC4 00211C24  80 01 00 28 */	lwz r0, 0x28(r1)
/* 80214CC8 00211C28  28 00 00 00 */	cmplwi r0, 0x0
/* 80214CCC 00211C2C  41 82 00 4C */	beq .L_80214D18
/* 80214CD0 00211C30  80 01 00 20 */	lwz r0, 0x20(r1)
/* 80214CD4 00211C34  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80214CD8 00211C38  7C 00 21 D6 */	mullw r0, r0, r4
/* 80214CDC 00211C3C  7F E3 02 14 */	add r31, r3, r0
/* 80214CE0 00211C40  48 00 00 2C */	b .L_80214D0C
.L_80214CE4:
/* 80214CE4 00211C44  80 01 00 20 */	lwz r0, 0x20(r1)
/* 80214CE8 00211C48  38 80 FF FF */	li r4, -0x1
/* 80214CEC 00211C4C  81 81 00 28 */	lwz r12, 0x28(r1)
/* 80214CF0 00211C50  7F E0 F8 50 */	subf r31, r0, r31
/* 80214CF4 00211C54  7D 88 03 A6 */	mtlr r12
/* 80214CF8 00211C58  38 7F 00 00 */	addi r3, r31, 0x0
/* 80214CFC 00211C5C  4E 80 00 21 */	blrl
/* 80214D00 00211C60  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 80214D04 00211C64  38 03 FF FF */	subi r0, r3, 0x1
/* 80214D08 00211C68  90 01 00 2C */	stw r0, 0x2c(r1)
.L_80214D0C:
/* 80214D0C 00211C6C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80214D10 00211C70  28 00 00 00 */	cmplwi r0, 0x0
/* 80214D14 00211C74  40 82 FF D0 */	bne .L_80214CE4
.L_80214D18:
/* 80214D18 00211C78  7F C3 F3 78 */	mr r3, r30
/* 80214D1C 00211C7C  BB 61 00 34 */	lmw r27, 0x34(r1)
/* 80214D20 00211C80  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80214D24 00211C84  38 21 00 48 */	addi r1, r1, 0x48
/* 80214D28 00211C88  7C 08 03 A6 */	mtlr r0
/* 80214D2C 00211C8C  4E 80 00 20 */	blr
.endfn __construct_new_array
