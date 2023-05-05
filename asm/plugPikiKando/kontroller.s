.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.fn __ct__10KontrollerFi, global
/* 80115B8C 00112AEC  7C 08 02 A6 */	mflr r0
/* 80115B90 00112AF0  3C A0 80 22 */	lis r5, __vt__5ANode@ha
/* 80115B94 00112AF4  90 01 00 04 */	stw r0, 4(r1)
/* 80115B98 00112AF8  38 05 73 8C */	addi r0, r5, __vt__5ANode@l
/* 80115B9C 00112AFC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80115BA0 00112B00  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80115BA4 00112B04  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80115BA8 00112B08  3B C0 00 00 */	li r30, 0
/* 80115BAC 00112B0C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80115BB0 00112B10  3B A4 00 00 */	addi r29, r4, 0
/* 80115BB4 00112B14  93 81 00 10 */	stw r28, 0x10(r1)
/* 80115BB8 00112B18  3B 83 00 00 */	addi r28, r3, 0
/* 80115BBC 00112B1C  3C 60 80 22 */	lis r3, __vt__8CoreNode@ha
/* 80115BC0 00112B20  90 1C 00 00 */	stw r0, 0(r28)
/* 80115BC4 00112B24  38 03 73 7C */	addi r0, r3, __vt__8CoreNode@l
/* 80115BC8 00112B28  3C 60 80 2C */	lis r3, lbl_802C2D9C@ha
/* 80115BCC 00112B2C  90 1C 00 00 */	stw r0, 0(r28)
/* 80115BD0 00112B30  3B E3 2D 9C */	addi r31, r3, lbl_802C2D9C@l
/* 80115BD4 00112B34  38 7C 00 00 */	addi r3, r28, 0
/* 80115BD8 00112B38  93 DC 00 10 */	stw r30, 0x10(r28)
/* 80115BDC 00112B3C  38 9F 00 00 */	addi r4, r31, 0
/* 80115BE0 00112B40  93 DC 00 0C */	stw r30, 0xc(r28)
/* 80115BE4 00112B44  93 DC 00 08 */	stw r30, 8(r28)
/* 80115BE8 00112B48  4B F0 F2 ED */	bl setName__8CoreNodeFPc
/* 80115BEC 00112B4C  3C 60 80 23 */	lis r3, __vt__4Node@ha
/* 80115BF0 00112B50  38 03 8E 20 */	addi r0, r3, __vt__4Node@l
/* 80115BF4 00112B54  90 1C 00 00 */	stw r0, 0(r28)
/* 80115BF8 00112B58  38 7C 00 00 */	addi r3, r28, 0
/* 80115BFC 00112B5C  38 9F 00 00 */	addi r4, r31, 0
/* 80115C00 00112B60  4B F2 AB 3D */	bl init__4NodeFPc
/* 80115C04 00112B64  3C 60 80 23 */	lis r3, __vt__10Controller@ha
/* 80115C08 00112B68  38 03 8E B4 */	addi r0, r3, __vt__10Controller@l
/* 80115C0C 00112B6C  90 1C 00 00 */	stw r0, 0(r28)
/* 80115C10 00112B70  38 7C 00 00 */	addi r3, r28, 0
/* 80115C14 00112B74  38 9D 00 00 */	addi r4, r29, 0
/* 80115C18 00112B78  4B F2 AD 99 */	bl reset__10ControllerFUl
/* 80115C1C 00112B7C  3C 60 80 2C */	lis r3, __vt__10Kontroller@ha
/* 80115C20 00112B80  38 03 2E 24 */	addi r0, r3, __vt__10Kontroller@l
/* 80115C24 00112B84  90 1C 00 00 */	stw r0, 0(r28)
/* 80115C28 00112B88  7F 83 E3 78 */	mr r3, r28
/* 80115C2C 00112B8C  93 DC 00 50 */	stw r30, 0x50(r28)
/* 80115C30 00112B90  93 DC 00 54 */	stw r30, 0x54(r28)
/* 80115C34 00112B94  93 DC 00 58 */	stw r30, 0x58(r28)
/* 80115C38 00112B98  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80115C3C 00112B9C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80115C40 00112BA0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80115C44 00112BA4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80115C48 00112BA8  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80115C4C 00112BAC  38 21 00 20 */	addi r1, r1, 0x20
/* 80115C50 00112BB0  7C 08 03 A6 */	mtlr r0
/* 80115C54 00112BB4  4E 80 00 20 */	blr 
.endfn __ct__10KontrollerFi

.fn save__10KontrollerFP9RamStreami, global
/* 80115C58 00112BB8  7C 08 02 A6 */	mflr r0
/* 80115C5C 00112BBC  90 01 00 04 */	stw r0, 4(r1)
/* 80115C60 00112BC0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80115C64 00112BC4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80115C68 00112BC8  7C 7F 1B 78 */	mr r31, r3
/* 80115C6C 00112BCC  90 A3 00 54 */	stw r5, 0x54(r3)
/* 80115C70 00112BD0  7C 83 23 78 */	mr r3, r4
/* 80115C74 00112BD4  90 9F 00 58 */	stw r4, 0x58(r31)
/* 80115C78 00112BD8  38 80 00 00 */	li r4, 0
/* 80115C7C 00112BDC  81 83 00 04 */	lwz r12, 4(r3)
/* 80115C80 00112BE0  81 8C 00 5C */	lwz r12, 0x5c(r12)
/* 80115C84 00112BE4  7D 88 03 A6 */	mtlr r12
/* 80115C88 00112BE8  4E 80 00 21 */	blrl 
/* 80115C8C 00112BEC  38 00 00 01 */	li r0, 1
/* 80115C90 00112BF0  90 1F 00 50 */	stw r0, 0x50(r31)
/* 80115C94 00112BF4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80115C98 00112BF8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80115C9C 00112BFC  38 21 00 20 */	addi r1, r1, 0x20
/* 80115CA0 00112C00  7C 08 03 A6 */	mtlr r0
/* 80115CA4 00112C04  4E 80 00 20 */	blr 
.endfn save__10KontrollerFP9RamStreami

.fn load__10KontrollerFP9RamStreami, global
/* 80115CA8 00112C08  7C 08 02 A6 */	mflr r0
/* 80115CAC 00112C0C  90 01 00 04 */	stw r0, 4(r1)
/* 80115CB0 00112C10  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80115CB4 00112C14  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80115CB8 00112C18  7C 7F 1B 78 */	mr r31, r3
/* 80115CBC 00112C1C  90 A3 00 54 */	stw r5, 0x54(r3)
/* 80115CC0 00112C20  7C 83 23 78 */	mr r3, r4
/* 80115CC4 00112C24  90 9F 00 58 */	stw r4, 0x58(r31)
/* 80115CC8 00112C28  38 80 00 00 */	li r4, 0
/* 80115CCC 00112C2C  81 83 00 04 */	lwz r12, 4(r3)
/* 80115CD0 00112C30  81 8C 00 5C */	lwz r12, 0x5c(r12)
/* 80115CD4 00112C34  7D 88 03 A6 */	mtlr r12
/* 80115CD8 00112C38  4E 80 00 21 */	blrl 
/* 80115CDC 00112C3C  38 00 00 02 */	li r0, 2
/* 80115CE0 00112C40  90 1F 00 50 */	stw r0, 0x50(r31)
/* 80115CE4 00112C44  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80115CE8 00112C48  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80115CEC 00112C4C  38 21 00 20 */	addi r1, r1, 0x20
/* 80115CF0 00112C50  7C 08 03 A6 */	mtlr r0
/* 80115CF4 00112C54  4E 80 00 20 */	blr 
.endfn load__10KontrollerFP9RamStreami

.fn update__10KontrollerFv, global
/* 80115CF8 00112C58  7C 08 02 A6 */	mflr r0
/* 80115CFC 00112C5C  90 01 00 04 */	stw r0, 4(r1)
/* 80115D00 00112C60  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80115D04 00112C64  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80115D08 00112C68  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80115D0C 00112C6C  7C 7E 1B 78 */	mr r30, r3
/* 80115D10 00112C70  80 03 00 50 */	lwz r0, 0x50(r3)
/* 80115D14 00112C74  2C 00 00 01 */	cmpwi r0, 1
/* 80115D18 00112C78  41 82 00 64 */	beq .L_80115D7C
/* 80115D1C 00112C7C  40 80 00 10 */	bge .L_80115D2C
/* 80115D20 00112C80  2C 00 00 00 */	cmpwi r0, 0
/* 80115D24 00112C84  40 80 01 1C */	bge .L_80115E40
/* 80115D28 00112C88  48 00 01 20 */	b .L_80115E48
.L_80115D2C:
/* 80115D2C 00112C8C  2C 00 00 03 */	cmpwi r0, 3
/* 80115D30 00112C90  40 80 01 18 */	bge .L_80115E48
/* 80115D34 00112C94  7F C3 F3 78 */	mr r3, r30
/* 80115D38 00112C98  80 9E 00 58 */	lwz r4, 0x58(r30)
/* 80115D3C 00112C9C  81 9E 00 00 */	lwz r12, 0(r30)
/* 80115D40 00112CA0  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80115D44 00112CA4  7D 88 03 A6 */	mtlr r12
/* 80115D48 00112CA8  4E 80 00 21 */	blrl 
/* 80115D4C 00112CAC  80 7E 00 54 */	lwz r3, 0x54(r30)
/* 80115D50 00112CB0  34 03 FF FF */	addic. r0, r3, -1
/* 80115D54 00112CB4  90 1E 00 54 */	stw r0, 0x54(r30)
/* 80115D58 00112CB8  41 81 00 14 */	bgt .L_80115D6C
/* 80115D5C 00112CBC  38 00 00 00 */	li r0, 0
/* 80115D60 00112CC0  90 1E 00 50 */	stw r0, 0x50(r30)
/* 80115D64 00112CC4  90 1E 00 58 */	stw r0, 0x58(r30)
/* 80115D68 00112CC8  90 1E 00 54 */	stw r0, 0x54(r30)
.L_80115D6C:
/* 80115D6C 00112CCC  7F C3 F3 78 */	mr r3, r30
/* 80115D70 00112CD0  80 9E 00 5C */	lwz r4, 0x5c(r30)
/* 80115D74 00112CD4  4B F2 AC 61 */	bl updateCont__10ControllerFUl
/* 80115D78 00112CD8  48 00 00 D0 */	b .L_80115E48
.L_80115D7C:
/* 80115D7C 00112CDC  7F C3 F3 78 */	mr r3, r30
/* 80115D80 00112CE0  4B F2 AC F1 */	bl update__10ControllerFv
/* 80115D84 00112CE4  7F C3 F3 78 */	mr r3, r30
/* 80115D88 00112CE8  80 9E 00 58 */	lwz r4, 0x58(r30)
/* 80115D8C 00112CEC  48 00 00 DD */	bl write__10KontrollerFR18RandomAccessStream
/* 80115D90 00112CF0  80 7E 00 54 */	lwz r3, 0x54(r30)
/* 80115D94 00112CF4  34 03 FF FF */	addic. r0, r3, -1
/* 80115D98 00112CF8  90 1E 00 54 */	stw r0, 0x54(r30)
/* 80115D9C 00112CFC  41 81 00 AC */	bgt .L_80115E48
/* 80115DA0 00112D00  80 7E 00 58 */	lwz r3, 0x58(r30)
/* 80115DA4 00112D04  81 83 00 04 */	lwz r12, 4(r3)
/* 80115DA8 00112D08  83 E3 00 08 */	lwz r31, 8(r3)
/* 80115DAC 00112D0C  81 8C 00 58 */	lwz r12, 0x58(r12)
/* 80115DB0 00112D10  7D 88 03 A6 */	mtlr r12
/* 80115DB4 00112D14  4E 80 00 21 */	blrl 
/* 80115DB8 00112D18  38 83 00 00 */	addi r4, r3, 0
/* 80115DBC 00112D1C  38 7F 00 00 */	addi r3, r31, 0
/* 80115DC0 00112D20  48 0E 0E 29 */	bl DCFlushRange
/* 80115DC4 00112D24  38 00 00 02 */	li r0, 2
/* 80115DC8 00112D28  7C 09 03 A6 */	mtctr r0
/* 80115DCC 00112D2C  38 60 00 00 */	li r3, 0
.L_80115DD0:
/* 80115DD0 00112D30  38 63 00 40 */	addi r3, r3, 0x40
/* 80115DD4 00112D34  42 00 FF FC */	bdnz .L_80115DD0
/* 80115DD8 00112D38  80 7E 00 58 */	lwz r3, 0x58(r30)
/* 80115DDC 00112D3C  81 83 00 04 */	lwz r12, 4(r3)
/* 80115DE0 00112D40  81 8C 00 4C */	lwz r12, 0x4c(r12)
/* 80115DE4 00112D44  7D 88 03 A6 */	mtlr r12
/* 80115DE8 00112D48  4E 80 00 21 */	blrl 
/* 80115DEC 00112D4C  80 7E 00 58 */	lwz r3, 0x58(r30)
/* 80115DF0 00112D50  81 83 00 04 */	lwz r12, 4(r3)
/* 80115DF4 00112D54  81 8C 00 58 */	lwz r12, 0x58(r12)
/* 80115DF8 00112D58  7D 88 03 A6 */	mtlr r12
/* 80115DFC 00112D5C  4E 80 00 21 */	blrl 
/* 80115E00 00112D60  80 7E 00 58 */	lwz r3, 0x58(r30)
/* 80115E04 00112D64  81 83 00 04 */	lwz r12, 4(r3)
/* 80115E08 00112D68  81 8C 00 58 */	lwz r12, 0x58(r12)
/* 80115E0C 00112D6C  7D 88 03 A6 */	mtlr r12
/* 80115E10 00112D70  4E 80 00 21 */	blrl 
/* 80115E14 00112D74  80 9E 00 58 */	lwz r4, 0x58(r30)
/* 80115E18 00112D78  7C 66 1B 78 */	mr r6, r3
/* 80115E1C 00112D7C  80 6D 2F 88 */	lwz r3, kio@sda21(r13)
/* 80115E20 00112D80  80 A4 00 08 */	lwz r5, 8(r4)
/* 80115E24 00112D84  38 80 00 01 */	li r4, 1
/* 80115E28 00112D88  4B F6 E6 F9 */	bl startWrite__3KIOFiPUci
/* 80115E2C 00112D8C  38 00 00 00 */	li r0, 0
/* 80115E30 00112D90  90 1E 00 50 */	stw r0, 0x50(r30)
/* 80115E34 00112D94  90 1E 00 58 */	stw r0, 0x58(r30)
/* 80115E38 00112D98  90 1E 00 54 */	stw r0, 0x54(r30)
/* 80115E3C 00112D9C  48 00 00 0C */	b .L_80115E48
.L_80115E40:
/* 80115E40 00112DA0  7F C3 F3 78 */	mr r3, r30
/* 80115E44 00112DA4  4B F2 AC 2D */	bl update__10ControllerFv
.L_80115E48:
/* 80115E48 00112DA8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80115E4C 00112DAC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80115E50 00112DB0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80115E54 00112DB4  38 21 00 20 */	addi r1, r1, 0x20
/* 80115E58 00112DB8  7C 08 03 A6 */	mtlr r0
/* 80115E5C 00112DBC  4E 80 00 20 */	blr 
.endfn update__10KontrollerFv

.fn getSaveSize__10KontrollerFi, global
/* 80115E60 00112DC0  1C 63 00 0C */	mulli r3, r3, 0xc
/* 80115E64 00112DC4  4E 80 00 20 */	blr 
.endfn getSaveSize__10KontrollerFi

.fn write__10KontrollerFR18RandomAccessStream, global
/* 80115E68 00112DC8  7C 08 02 A6 */	mflr r0
/* 80115E6C 00112DCC  90 01 00 04 */	stw r0, 4(r1)
/* 80115E70 00112DD0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80115E74 00112DD4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80115E78 00112DD8  3B E4 00 00 */	addi r31, r4, 0
/* 80115E7C 00112DDC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80115E80 00112DE0  3B C3 00 00 */	addi r30, r3, 0
/* 80115E84 00112DE4  38 7F 00 00 */	addi r3, r31, 0
/* 80115E88 00112DE8  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115E8C 00112DEC  80 9E 00 20 */	lwz r4, 0x20(r30)
/* 80115E90 00112DF0  81 8C 00 24 */	lwz r12, 0x24(r12)
/* 80115E94 00112DF4  7D 88 03 A6 */	mtlr r12
/* 80115E98 00112DF8  4E 80 00 21 */	blrl 
/* 80115E9C 00112DFC  7F E3 FB 78 */	mr r3, r31
/* 80115EA0 00112E00  88 9E 00 45 */	lbz r4, 0x45(r30)
/* 80115EA4 00112E04  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115EA8 00112E08  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 80115EAC 00112E0C  7D 88 03 A6 */	mtlr r12
/* 80115EB0 00112E10  4E 80 00 21 */	blrl 
/* 80115EB4 00112E14  7F E3 FB 78 */	mr r3, r31
/* 80115EB8 00112E18  88 9E 00 46 */	lbz r4, 0x46(r30)
/* 80115EBC 00112E1C  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115EC0 00112E20  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 80115EC4 00112E24  7D 88 03 A6 */	mtlr r12
/* 80115EC8 00112E28  4E 80 00 21 */	blrl 
/* 80115ECC 00112E2C  7F E3 FB 78 */	mr r3, r31
/* 80115ED0 00112E30  88 9E 00 47 */	lbz r4, 0x47(r30)
/* 80115ED4 00112E34  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115ED8 00112E38  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 80115EDC 00112E3C  7D 88 03 A6 */	mtlr r12
/* 80115EE0 00112E40  4E 80 00 21 */	blrl 
/* 80115EE4 00112E44  7F E3 FB 78 */	mr r3, r31
/* 80115EE8 00112E48  88 9E 00 48 */	lbz r4, 0x48(r30)
/* 80115EEC 00112E4C  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115EF0 00112E50  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 80115EF4 00112E54  7D 88 03 A6 */	mtlr r12
/* 80115EF8 00112E58  4E 80 00 21 */	blrl 
/* 80115EFC 00112E5C  7F E3 FB 78 */	mr r3, r31
/* 80115F00 00112E60  88 9E 00 49 */	lbz r4, 0x49(r30)
/* 80115F04 00112E64  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115F08 00112E68  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 80115F0C 00112E6C  7D 88 03 A6 */	mtlr r12
/* 80115F10 00112E70  4E 80 00 21 */	blrl 
/* 80115F14 00112E74  7F E3 FB 78 */	mr r3, r31
/* 80115F18 00112E78  88 9E 00 4A */	lbz r4, 0x4a(r30)
/* 80115F1C 00112E7C  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115F20 00112E80  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 80115F24 00112E84  7D 88 03 A6 */	mtlr r12
/* 80115F28 00112E88  4E 80 00 21 */	blrl 
/* 80115F2C 00112E8C  7F E3 FB 78 */	mr r3, r31
/* 80115F30 00112E90  88 9E 00 4B */	lbz r4, 0x4b(r30)
/* 80115F34 00112E94  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115F38 00112E98  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 80115F3C 00112E9C  7D 88 03 A6 */	mtlr r12
/* 80115F40 00112EA0  4E 80 00 21 */	blrl 
/* 80115F44 00112EA4  7F E3 FB 78 */	mr r3, r31
/* 80115F48 00112EA8  88 9E 00 4C */	lbz r4, 0x4c(r30)
/* 80115F4C 00112EAC  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115F50 00112EB0  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 80115F54 00112EB4  7D 88 03 A6 */	mtlr r12
/* 80115F58 00112EB8  4E 80 00 21 */	blrl 
/* 80115F5C 00112EBC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80115F60 00112EC0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80115F64 00112EC4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80115F68 00112EC8  38 21 00 18 */	addi r1, r1, 0x18
/* 80115F6C 00112ECC  7C 08 03 A6 */	mtlr r0
/* 80115F70 00112ED0  4E 80 00 20 */	blr 
.endfn write__10KontrollerFR18RandomAccessStream

.fn read__10KontrollerFR18RandomAccessStream, global
/* 80115F74 00112ED4  7C 08 02 A6 */	mflr r0
/* 80115F78 00112ED8  90 01 00 04 */	stw r0, 4(r1)
/* 80115F7C 00112EDC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80115F80 00112EE0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80115F84 00112EE4  3B E4 00 00 */	addi r31, r4, 0
/* 80115F88 00112EE8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80115F8C 00112EEC  3B C3 00 00 */	addi r30, r3, 0
/* 80115F90 00112EF0  38 7F 00 00 */	addi r3, r31, 0
/* 80115F94 00112EF4  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115F98 00112EF8  81 8C 00 08 */	lwz r12, 8(r12)
/* 80115F9C 00112EFC  7D 88 03 A6 */	mtlr r12
/* 80115FA0 00112F00  4E 80 00 21 */	blrl 
/* 80115FA4 00112F04  90 7E 00 5C */	stw r3, 0x5c(r30)
/* 80115FA8 00112F08  7F E3 FB 78 */	mr r3, r31
/* 80115FAC 00112F0C  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115FB0 00112F10  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80115FB4 00112F14  7D 88 03 A6 */	mtlr r12
/* 80115FB8 00112F18  4E 80 00 21 */	blrl 
/* 80115FBC 00112F1C  98 7E 00 45 */	stb r3, 0x45(r30)
/* 80115FC0 00112F20  7F E3 FB 78 */	mr r3, r31
/* 80115FC4 00112F24  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115FC8 00112F28  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80115FCC 00112F2C  7D 88 03 A6 */	mtlr r12
/* 80115FD0 00112F30  4E 80 00 21 */	blrl 
/* 80115FD4 00112F34  98 7E 00 46 */	stb r3, 0x46(r30)
/* 80115FD8 00112F38  7F E3 FB 78 */	mr r3, r31
/* 80115FDC 00112F3C  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115FE0 00112F40  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80115FE4 00112F44  7D 88 03 A6 */	mtlr r12
/* 80115FE8 00112F48  4E 80 00 21 */	blrl 
/* 80115FEC 00112F4C  98 7E 00 47 */	stb r3, 0x47(r30)
/* 80115FF0 00112F50  7F E3 FB 78 */	mr r3, r31
/* 80115FF4 00112F54  81 9F 00 04 */	lwz r12, 4(r31)
/* 80115FF8 00112F58  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80115FFC 00112F5C  7D 88 03 A6 */	mtlr r12
/* 80116000 00112F60  4E 80 00 21 */	blrl 
/* 80116004 00112F64  98 7E 00 48 */	stb r3, 0x48(r30)
/* 80116008 00112F68  7F E3 FB 78 */	mr r3, r31
/* 8011600C 00112F6C  81 9F 00 04 */	lwz r12, 4(r31)
/* 80116010 00112F70  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80116014 00112F74  7D 88 03 A6 */	mtlr r12
/* 80116018 00112F78  4E 80 00 21 */	blrl 
/* 8011601C 00112F7C  98 7E 00 49 */	stb r3, 0x49(r30)
/* 80116020 00112F80  7F E3 FB 78 */	mr r3, r31
/* 80116024 00112F84  81 9F 00 04 */	lwz r12, 4(r31)
/* 80116028 00112F88  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 8011602C 00112F8C  7D 88 03 A6 */	mtlr r12
/* 80116030 00112F90  4E 80 00 21 */	blrl 
/* 80116034 00112F94  98 7E 00 4A */	stb r3, 0x4a(r30)
/* 80116038 00112F98  7F E3 FB 78 */	mr r3, r31
/* 8011603C 00112F9C  81 9F 00 04 */	lwz r12, 4(r31)
/* 80116040 00112FA0  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80116044 00112FA4  7D 88 03 A6 */	mtlr r12
/* 80116048 00112FA8  4E 80 00 21 */	blrl 
/* 8011604C 00112FAC  98 7E 00 4B */	stb r3, 0x4b(r30)
/* 80116050 00112FB0  7F E3 FB 78 */	mr r3, r31
/* 80116054 00112FB4  81 9F 00 04 */	lwz r12, 4(r31)
/* 80116058 00112FB8  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 8011605C 00112FBC  7D 88 03 A6 */	mtlr r12
/* 80116060 00112FC0  4E 80 00 21 */	blrl 
/* 80116064 00112FC4  98 7E 00 4C */	stb r3, 0x4c(r30)
/* 80116068 00112FC8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8011606C 00112FCC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80116070 00112FD0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80116074 00112FD4  38 21 00 18 */	addi r1, r1, 0x18
/* 80116078 00112FD8  7C 08 03 A6 */	mtlr r0
/* 8011607C 00112FDC  4E 80 00 20 */	blr 
.endfn read__10KontrollerFR18RandomAccessStream

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 8
.obj lbl_802C2D80, local
	.asciz "kontroller.cpp"
.endobj lbl_802C2D80
.balign 4
.obj lbl_802C2D90, local
	.asciz "Kontroller"
.endobj lbl_802C2D90
.balign 4
.obj lbl_802C2D9C, local
	.asciz "<Controller>"
.endobj lbl_802C2D9C
.balign 4
.obj lbl_802C2DAC, local
	.asciz "CoreNode"
.endobj lbl_802C2DAC
.balign 4
.obj lbl_802C2DB8, local
	.4byte __RTTI__5ANode
	.4byte 0x00000000
	.4byte 0x00000000
.endobj lbl_802C2DB8
.obj lbl_802C2DC4, local
	.4byte __RTTI__5ANode
	.4byte 0x00000000
	.4byte __RTTI__8CoreNode
	.4byte 0x00000000
	.4byte 0x00000000
.endobj lbl_802C2DC4
.balign 4
.obj lbl_802C2DD8, local
	.asciz "Controller"
.endobj lbl_802C2DD8
.balign 4
.obj lbl_802C2DE4, local
	.4byte __RTTI__5ANode
	.4byte 0x00000000
	.4byte __RTTI__8CoreNode
	.4byte 0x00000000
	.4byte __RTTI__4Node
	.4byte 0x00000000
	.4byte 0x00000000
.endobj lbl_802C2DE4
.obj lbl_802C2E00, local
	.4byte __RTTI__5ANode
	.4byte 0x00000000
	.4byte __RTTI__8CoreNode
	.4byte 0x00000000
	.4byte __RTTI__4Node
	.4byte 0x00000000
	.4byte __RTTI__10Controller
	.4byte 0x00000000
	.4byte 0x00000000
.endobj lbl_802C2E00
.obj __vt__10Kontroller, global
	.4byte __RTTI__10Kontroller
	.4byte 0
	.4byte getAgeNodeType__5ANodeFv
	.4byte read__10KontrollerFR18RandomAccessStream
	.4byte update__10KontrollerFv
	.4byte draw__4NodeFR8Graphics
	.4byte render__4NodeFR8Graphics
	.4byte concat__4NodeFv
	.4byte concat__4NodeFR3VQS
	.4byte concat__4NodeFR3SRT
	.4byte concat__4NodeFR8Matrix4f
	.4byte getModelMatrix__4NodeFv
.endobj __vt__10Kontroller
	.4byte 0
	.4byte 0
	.4byte 0
	.4byte 0
	.4byte 0
	.4byte 0
	.4byte 0

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.balign 8
.obj lbl_803E2978, local
	.asciz "ANode"
.endobj lbl_803E2978
.balign 4
.obj __RTTI__5ANode, local
	.4byte lbl_803E2978
	.4byte 0
.endobj __RTTI__5ANode
.obj __RTTI__8CoreNode, local
	.4byte lbl_802C2DAC
	.4byte lbl_802C2DB8
.endobj __RTTI__8CoreNode
.balign 4
.obj lbl_803E2990, local
	.asciz "Node"
.endobj lbl_803E2990
.balign 4
.obj __RTTI__4Node, local
	.4byte lbl_803E2990
	.4byte lbl_802C2DC4
.endobj __RTTI__4Node
.obj __RTTI__10Controller, local
	.4byte lbl_802C2DD8
	.4byte lbl_802C2DE4
.endobj __RTTI__10Controller
.obj __RTTI__10Kontroller, local
	.4byte lbl_802C2D90
	.4byte lbl_802C2E00
.endobj __RTTI__10Kontroller

.section .sbss, "wa"
.balign 8
.obj controllerBuffer, global
	.skip 0x4
.endobj controllerBuffer
