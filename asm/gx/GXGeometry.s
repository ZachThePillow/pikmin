.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.fn __GXSetDirtyState, global
/* 80210B48 0020DAA8  7C 08 02 A6 */	mflr r0
/* 80210B4C 0020DAAC  90 01 00 04 */	stw r0, 4(r1)
/* 80210B50 0020DAB0  94 21 FF F8 */	stwu r1, -8(r1)
/* 80210B54 0020DAB4  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210B58 0020DAB8  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80210B5C 0020DABC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80210B60 0020DAC0  41 82 00 08 */	beq .L_80210B68
/* 80210B64 0020DAC4  48 00 1E F9 */	bl __GXSetSUTexRegs
.L_80210B68:
/* 80210B68 0020DAC8  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210B6C 0020DACC  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80210B70 0020DAD0  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 80210B74 0020DAD4  41 82 00 08 */	beq .L_80210B7C
/* 80210B78 0020DAD8  48 00 23 35 */	bl __GXUpdateBPMask
.L_80210B7C:
/* 80210B7C 0020DADC  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210B80 0020DAE0  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80210B84 0020DAE4  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 80210B88 0020DAE8  41 82 00 08 */	beq .L_80210B90
/* 80210B8C 0020DAEC  48 00 03 51 */	bl __GXSetGenMode
.L_80210B90:
/* 80210B90 0020DAF0  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210B94 0020DAF4  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80210B98 0020DAF8  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 80210B9C 0020DAFC  41 82 00 08 */	beq .L_80210BA4
/* 80210BA0 0020DB00  4B FF EE F5 */	bl __GXSetVCD
.L_80210BA4:
/* 80210BA4 0020DB04  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210BA8 0020DB08  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80210BAC 0020DB0C  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 80210BB0 0020DB10  41 82 00 08 */	beq .L_80210BB8
/* 80210BB4 0020DB14  4B FF F7 6D */	bl __GXSetVAT
.L_80210BB8:
/* 80210BB8 0020DB18  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210BBC 0020DB1C  38 00 00 00 */	li r0, 0
/* 80210BC0 0020DB20  90 03 04 F0 */	stw r0, 0x4f0(r3)
/* 80210BC4 0020DB24  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80210BC8 0020DB28  38 21 00 08 */	addi r1, r1, 8
/* 80210BCC 0020DB2C  7C 08 03 A6 */	mtlr r0
/* 80210BD0 0020DB30  4E 80 00 20 */	blr 
.endfn __GXSetDirtyState

.fn GXBegin, global
/* 80210BD4 0020DB34  7C 08 02 A6 */	mflr r0
/* 80210BD8 0020DB38  90 01 00 04 */	stw r0, 4(r1)
/* 80210BDC 0020DB3C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80210BE0 0020DB40  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80210BE4 0020DB44  3B E5 00 00 */	addi r31, r5, 0
/* 80210BE8 0020DB48  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80210BEC 0020DB4C  3B C4 00 00 */	addi r30, r4, 0
/* 80210BF0 0020DB50  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80210BF4 0020DB54  3B A3 00 00 */	addi r29, r3, 0
/* 80210BF8 0020DB58  80 CD 2A 68 */	lwz r6, gx@sda21(r13)
/* 80210BFC 0020DB5C  80 06 04 F0 */	lwz r0, 0x4f0(r6)
/* 80210C00 0020DB60  28 00 00 00 */	cmplwi r0, 0
/* 80210C04 0020DB64  41 82 00 6C */	beq .L_80210C70
/* 80210C08 0020DB68  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80210C0C 0020DB6C  41 82 00 08 */	beq .L_80210C14
/* 80210C10 0020DB70  48 00 1E 4D */	bl __GXSetSUTexRegs
.L_80210C14:
/* 80210C14 0020DB74  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210C18 0020DB78  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80210C1C 0020DB7C  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 80210C20 0020DB80  41 82 00 08 */	beq .L_80210C28
/* 80210C24 0020DB84  48 00 22 89 */	bl __GXUpdateBPMask
.L_80210C28:
/* 80210C28 0020DB88  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210C2C 0020DB8C  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80210C30 0020DB90  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 80210C34 0020DB94  41 82 00 08 */	beq .L_80210C3C
/* 80210C38 0020DB98  48 00 02 A5 */	bl __GXSetGenMode
.L_80210C3C:
/* 80210C3C 0020DB9C  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210C40 0020DBA0  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80210C44 0020DBA4  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 80210C48 0020DBA8  41 82 00 08 */	beq .L_80210C50
/* 80210C4C 0020DBAC  4B FF EE 49 */	bl __GXSetVCD
.L_80210C50:
/* 80210C50 0020DBB0  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210C54 0020DBB4  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80210C58 0020DBB8  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 80210C5C 0020DBBC  41 82 00 08 */	beq .L_80210C64
/* 80210C60 0020DBC0  4B FF F6 C1 */	bl __GXSetVAT
.L_80210C64:
/* 80210C64 0020DBC4  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210C68 0020DBC8  38 00 00 00 */	li r0, 0
/* 80210C6C 0020DBCC  90 03 04 F0 */	stw r0, 0x4f0(r3)
.L_80210C70:
/* 80210C70 0020DBD0  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210C74 0020DBD4  80 03 00 00 */	lwz r0, 0(r3)
/* 80210C78 0020DBD8  28 00 00 00 */	cmplwi r0, 0
/* 80210C7C 0020DBDC  41 82 00 08 */	beq .L_80210C84
/* 80210C80 0020DBE0  48 00 00 31 */	bl __GXSendFlushPrim
.L_80210C84:
/* 80210C84 0020DBE4  7F C0 EB 78 */	or r0, r30, r29
/* 80210C88 0020DBE8  3C 60 CC 01 */	lis r3, 0xCC008000@ha
/* 80210C8C 0020DBEC  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 80210C90 0020DBF0  B3 E3 80 00 */	sth r31, 0xCC008000@l(r3)
/* 80210C94 0020DBF4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80210C98 0020DBF8  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80210C9C 0020DBFC  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80210CA0 0020DC00  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80210CA4 0020DC04  38 21 00 28 */	addi r1, r1, 0x28
/* 80210CA8 0020DC08  7C 08 03 A6 */	mtlr r0
/* 80210CAC 0020DC0C  4E 80 00 20 */	blr 
.endfn GXBegin

.fn __GXSendFlushPrim, global
/* 80210CB0 0020DC10  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210CB4 0020DC14  38 00 00 98 */	li r0, 0x98
/* 80210CB8 0020DC18  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80210CBC 0020DC1C  A0 C3 00 00 */	lhz r6, 0(r3)
/* 80210CC0 0020DC20  38 80 00 00 */	li r4, 0
/* 80210CC4 0020DC24  80 63 00 04 */	lwz r3, 4(r3)
/* 80210CC8 0020DC28  7C E6 19 D6 */	mullw r7, r6, r3
/* 80210CCC 0020DC2C  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80210CD0 0020DC30  B0 C5 80 00 */	sth r6, 0xCC008000@l(r5)
/* 80210CD4 0020DC34  38 67 00 03 */	addi r3, r7, 3
/* 80210CD8 0020DC38  28 07 00 00 */	cmplwi r7, 0
/* 80210CDC 0020DC3C  54 63 F0 BE */	srwi r3, r3, 2
/* 80210CE0 0020DC40  40 81 00 48 */	ble .L_80210D28
/* 80210CE4 0020DC44  54 60 E8 FF */	rlwinm. r0, r3, 0x1d, 3, 0x1f
/* 80210CE8 0020DC48  7C 09 03 A6 */	mtctr r0
/* 80210CEC 0020DC4C  41 82 00 30 */	beq .L_80210D1C
.L_80210CF0:
/* 80210CF0 0020DC50  90 85 80 00 */	stw r4, 0xCC008000@l(r5)
/* 80210CF4 0020DC54  90 85 80 00 */	stw r4, 0xCC008000@l(r5)
/* 80210CF8 0020DC58  90 85 80 00 */	stw r4, 0xCC008000@l(r5)
/* 80210CFC 0020DC5C  90 85 80 00 */	stw r4, 0xCC008000@l(r5)
/* 80210D00 0020DC60  90 85 80 00 */	stw r4, 0xCC008000@l(r5)
/* 80210D04 0020DC64  90 85 80 00 */	stw r4, 0xCC008000@l(r5)
/* 80210D08 0020DC68  90 85 80 00 */	stw r4, 0xCC008000@l(r5)
/* 80210D0C 0020DC6C  90 85 80 00 */	stw r4, 0xCC008000@l(r5)
/* 80210D10 0020DC70  42 00 FF E0 */	bdnz .L_80210CF0
/* 80210D14 0020DC74  70 63 00 07 */	andi. r3, r3, 7
/* 80210D18 0020DC78  41 82 00 10 */	beq .L_80210D28
.L_80210D1C:
/* 80210D1C 0020DC7C  7C 69 03 A6 */	mtctr r3
.L_80210D20:
/* 80210D20 0020DC80  90 85 80 00 */	stw r4, 0xCC008000@l(r5)
/* 80210D24 0020DC84  42 00 FF FC */	bdnz .L_80210D20
.L_80210D28:
/* 80210D28 0020DC88  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210D2C 0020DC8C  38 00 00 00 */	li r0, 0
/* 80210D30 0020DC90  B0 03 00 02 */	sth r0, 2(r3)
/* 80210D34 0020DC94  4E 80 00 20 */	blr 
.endfn __GXSendFlushPrim

.fn GXSetLineWidth, global
/* 80210D38 0020DC98  80 AD 2A 68 */	lwz r5, gx@sda21(r13)
/* 80210D3C 0020DC9C  54 86 80 1E */	slwi r6, r4, 0x10
/* 80210D40 0020DCA0  38 80 00 61 */	li r4, 0x61
/* 80210D44 0020DCA4  80 05 00 7C */	lwz r0, 0x7c(r5)
/* 80210D48 0020DCA8  38 E5 00 7C */	addi r7, r5, 0x7c
/* 80210D4C 0020DCAC  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80210D50 0020DCB0  54 00 00 2E */	rlwinm r0, r0, 0, 0, 0x17
/* 80210D54 0020DCB4  50 60 06 3E */	rlwimi r0, r3, 0, 0x18, 0x1f
/* 80210D58 0020DCB8  90 07 00 00 */	stw r0, 0(r7)
/* 80210D5C 0020DCBC  38 00 00 01 */	li r0, 1
/* 80210D60 0020DCC0  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210D64 0020DCC4  38 E3 00 7C */	addi r7, r3, 0x7c
/* 80210D68 0020DCC8  80 63 00 7C */	lwz r3, 0x7c(r3)
/* 80210D6C 0020DCCC  54 63 04 18 */	rlwinm r3, r3, 0, 0x10, 0xc
/* 80210D70 0020DCD0  7C 63 33 78 */	or r3, r3, r6
/* 80210D74 0020DCD4  90 67 00 00 */	stw r3, 0(r7)
/* 80210D78 0020DCD8  98 85 80 00 */	stb r4, 0xCC008000@l(r5)
/* 80210D7C 0020DCDC  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80210D80 0020DCE0  80 64 00 7C */	lwz r3, 0x7c(r4)
/* 80210D84 0020DCE4  90 65 80 00 */	stw r3, 0xCC008000@l(r5)
/* 80210D88 0020DCE8  B0 04 00 02 */	sth r0, 2(r4)
/* 80210D8C 0020DCEC  4E 80 00 20 */	blr 
.endfn GXSetLineWidth

.fn GXSetPointSize, global
/* 80210D90 0020DCF0  80 AD 2A 68 */	lwz r5, gx@sda21(r13)
/* 80210D94 0020DCF4  54 86 98 18 */	slwi r6, r4, 0x13
/* 80210D98 0020DCF8  84 05 00 7C */	lwzu r0, 0x7c(r5)
/* 80210D9C 0020DCFC  38 80 00 61 */	li r4, 0x61
/* 80210DA0 0020DD00  54 00 06 1E */	rlwinm r0, r0, 0, 0x18, 0xf
/* 80210DA4 0020DD04  50 60 44 2E */	rlwimi r0, r3, 8, 0x10, 0x17
/* 80210DA8 0020DD08  90 05 00 00 */	stw r0, 0(r5)
/* 80210DAC 0020DD0C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80210DB0 0020DD10  38 00 00 01 */	li r0, 1
/* 80210DB4 0020DD14  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210DB8 0020DD18  38 E3 00 7C */	addi r7, r3, 0x7c
/* 80210DBC 0020DD1C  80 63 00 7C */	lwz r3, 0x7c(r3)
/* 80210DC0 0020DD20  54 63 03 52 */	rlwinm r3, r3, 0, 0xd, 9
/* 80210DC4 0020DD24  7C 63 33 78 */	or r3, r3, r6
/* 80210DC8 0020DD28  90 67 00 00 */	stw r3, 0(r7)
/* 80210DCC 0020DD2C  98 85 80 00 */	stb r4, 0xCC008000@l(r5)
/* 80210DD0 0020DD30  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80210DD4 0020DD34  80 64 00 7C */	lwz r3, 0x7c(r4)
/* 80210DD8 0020DD38  90 65 80 00 */	stw r3, 0xCC008000@l(r5)
/* 80210DDC 0020DD3C  B0 04 00 02 */	sth r0, 2(r4)
/* 80210DE0 0020DD40  4E 80 00 20 */	blr 
.endfn GXSetPointSize

.fn GXEnableTexOffsets, global
/* 80210DE4 0020DD44  80 0D 2A 68 */	lwz r0, gx@sda21(r13)
/* 80210DE8 0020DD48  54 67 10 3A */	slwi r7, r3, 2
/* 80210DEC 0020DD4C  7C C0 3A 14 */	add r6, r0, r7
/* 80210DF0 0020DD50  80 66 00 B8 */	lwz r3, 0xb8(r6)
/* 80210DF4 0020DD54  54 80 91 9A */	rlwinm r0, r4, 0x12, 6, 0xd
/* 80210DF8 0020DD58  54 A4 99 58 */	rlwinm r4, r5, 0x13, 5, 0xc
/* 80210DFC 0020DD5C  54 63 03 98 */	rlwinm r3, r3, 0, 0xe, 0xc
/* 80210E00 0020DD60  7C 60 03 78 */	or r0, r3, r0
/* 80210E04 0020DD64  90 06 00 B8 */	stw r0, 0xb8(r6)
/* 80210E08 0020DD68  38 60 00 61 */	li r3, 0x61
/* 80210E0C 0020DD6C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80210E10 0020DD70  80 CD 2A 68 */	lwz r6, gx@sda21(r13)
/* 80210E14 0020DD74  38 00 00 01 */	li r0, 1
/* 80210E18 0020DD78  7D 06 3A 14 */	add r8, r6, r7
/* 80210E1C 0020DD7C  80 C8 00 B8 */	lwz r6, 0xb8(r8)
/* 80210E20 0020DD80  54 C6 03 56 */	rlwinm r6, r6, 0, 0xd, 0xb
/* 80210E24 0020DD84  7C C4 23 78 */	or r4, r6, r4
/* 80210E28 0020DD88  90 88 00 B8 */	stw r4, 0xb8(r8)
/* 80210E2C 0020DD8C  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80210E30 0020DD90  98 65 80 00 */	stb r3, 0xCC008000@l(r5)
/* 80210E34 0020DD94  7C 64 3A 14 */	add r3, r4, r7
/* 80210E38 0020DD98  80 63 00 B8 */	lwz r3, 0xb8(r3)
/* 80210E3C 0020DD9C  90 65 80 00 */	stw r3, 0xCC008000@l(r5)
/* 80210E40 0020DDA0  B0 04 00 02 */	sth r0, 2(r4)
/* 80210E44 0020DDA4  4E 80 00 20 */	blr 
.endfn GXEnableTexOffsets

.fn GXSetCullMode, global
/* 80210E48 0020DDA8  2C 03 00 02 */	cmpwi r3, 2
/* 80210E4C 0020DDAC  41 82 00 1C */	beq .L_80210E68
/* 80210E50 0020DDB0  40 80 00 1C */	bge .L_80210E6C
/* 80210E54 0020DDB4  2C 03 00 01 */	cmpwi r3, 1
/* 80210E58 0020DDB8  40 80 00 08 */	bge .L_80210E60
/* 80210E5C 0020DDBC  48 00 00 10 */	b .L_80210E6C
.L_80210E60:
/* 80210E60 0020DDC0  38 60 00 02 */	li r3, 2
/* 80210E64 0020DDC4  48 00 00 08 */	b .L_80210E6C
.L_80210E68:
/* 80210E68 0020DDC8  38 60 00 01 */	li r3, 1
.L_80210E6C:
/* 80210E6C 0020DDCC  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80210E70 0020DDD0  54 60 70 22 */	slwi r0, r3, 0xe
/* 80210E74 0020DDD4  84 64 02 04 */	lwzu r3, 0x204(r4)
/* 80210E78 0020DDD8  54 63 04 9E */	rlwinm r3, r3, 0, 0x12, 0xf
/* 80210E7C 0020DDDC  7C 60 03 78 */	or r0, r3, r0
/* 80210E80 0020DDE0  90 04 00 00 */	stw r0, 0(r4)
/* 80210E84 0020DDE4  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210E88 0020DDE8  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80210E8C 0020DDEC  60 00 00 04 */	ori r0, r0, 4
/* 80210E90 0020DDF0  90 03 04 F0 */	stw r0, 0x4f0(r3)
/* 80210E94 0020DDF4  4E 80 00 20 */	blr 
.endfn GXSetCullMode

.fn GXSetCoPlanar, global
/* 80210E98 0020DDF8  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80210E9C 0020DDFC  54 60 99 58 */	rlwinm r0, r3, 0x13, 5, 0xc
/* 80210EA0 0020DE00  38 A0 00 61 */	li r5, 0x61
/* 80210EA4 0020DE04  80 64 02 04 */	lwz r3, 0x204(r4)
/* 80210EA8 0020DE08  38 C4 02 04 */	addi r6, r4, 0x204
/* 80210EAC 0020DE0C  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80210EB0 0020DE10  54 63 03 56 */	rlwinm r3, r3, 0, 0xd, 0xb
/* 80210EB4 0020DE14  7C 60 03 78 */	or r0, r3, r0
/* 80210EB8 0020DE18  90 06 00 00 */	stw r0, 0(r6)
/* 80210EBC 0020DE1C  3C 00 FE 08 */	lis r0, 0xfe08
/* 80210EC0 0020DE20  98 A4 80 00 */	stb r5, 0xCC008000@l(r4)
/* 80210EC4 0020DE24  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210EC8 0020DE28  90 04 80 00 */	stw r0, 0xCC008000@l(r4)
/* 80210ECC 0020DE2C  98 A4 80 00 */	stb r5, 0xCC008000@l(r4)
/* 80210ED0 0020DE30  80 03 02 04 */	lwz r0, 0x204(r3)
/* 80210ED4 0020DE34  90 04 80 00 */	stw r0, 0xCC008000@l(r4)
/* 80210ED8 0020DE38  4E 80 00 20 */	blr 
.endfn GXSetCoPlanar

.fn __GXSetGenMode, global
/* 80210EDC 0020DE3C  38 00 00 61 */	li r0, 0x61
/* 80210EE0 0020DE40  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80210EE4 0020DE44  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80210EE8 0020DE48  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80210EEC 0020DE4C  38 00 00 01 */	li r0, 1
/* 80210EF0 0020DE50  80 64 02 04 */	lwz r3, 0x204(r4)
/* 80210EF4 0020DE54  90 65 80 00 */	stw r3, 0xCC008000@l(r5)
/* 80210EF8 0020DE58  B0 04 00 02 */	sth r0, 2(r4)
/* 80210EFC 0020DE5C  4E 80 00 20 */	blr 
.endfn __GXSetGenMode
