.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.balign 32, 0
.fn Jac_SendStreamData__FPUcUl, global
/* 8001DA80 0001A9E0  80 AD 81 38 */	lwz r5, buf@sda21(r13)
/* 8001DA84 0001A9E4  80 05 00 18 */	lwz r0, 0x18(r5)
/* 8001DA88 0001A9E8  7C 00 20 40 */	cmplw r0, r4
/* 8001DA8C 0001A9EC  40 80 00 0C */	bge .L_8001DA98
/* 8001DA90 0001A9F0  38 60 00 00 */	li r3, 0
/* 8001DA94 0001A9F4  4E 80 00 20 */	blr 
.L_8001DA98:
/* 8001DA98 0001A9F8  38 00 00 00 */	li r0, 0
/* 8001DA9C 0001A9FC  7C 89 03 A6 */	mtctr r4
/* 8001DAA0 0001AA00  28 04 00 00 */	cmplwi r4, 0
/* 8001DAA4 0001AA04  40 81 00 44 */	ble .L_8001DAE8
.L_8001DAA8:
/* 8001DAA8 0001AA08  81 2D 81 38 */	lwz r9, buf@sda21(r13)
/* 8001DAAC 0001AA0C  89 03 00 00 */	lbz r8, 0(r3)
/* 8001DAB0 0001AA10  80 C9 00 0C */	lwz r6, 0xc(r9)
/* 8001DAB4 0001AA14  80 E9 00 04 */	lwz r7, 4(r9)
/* 8001DAB8 0001AA18  38 A6 00 01 */	addi r5, r6, 1
/* 8001DABC 0001AA1C  90 A9 00 0C */	stw r5, 0xc(r9)
/* 8001DAC0 0001AA20  7D 07 31 AE */	stbx r8, r7, r6
/* 8001DAC4 0001AA24  80 AD 81 38 */	lwz r5, buf@sda21(r13)
/* 8001DAC8 0001AA28  38 E5 00 0C */	addi r7, r5, 0xc
/* 8001DACC 0001AA2C  80 A5 00 08 */	lwz r5, 8(r5)
/* 8001DAD0 0001AA30  80 C7 00 00 */	lwz r6, 0(r7)
/* 8001DAD4 0001AA34  7C 06 28 40 */	cmplw r6, r5
/* 8001DAD8 0001AA38  40 82 00 08 */	bne .L_8001DAE0
/* 8001DADC 0001AA3C  90 07 00 00 */	stw r0, 0(r7)
.L_8001DAE0:
/* 8001DAE0 0001AA40  38 63 00 01 */	addi r3, r3, 1
/* 8001DAE4 0001AA44  42 00 FF C4 */	bdnz .L_8001DAA8
.L_8001DAE8:
/* 8001DAE8 0001AA48  80 AD 81 38 */	lwz r5, buf@sda21(r13)
/* 8001DAEC 0001AA4C  38 60 00 01 */	li r3, 1
/* 8001DAF0 0001AA50  80 05 00 18 */	lwz r0, 0x18(r5)
/* 8001DAF4 0001AA54  7C 04 00 50 */	subf r0, r4, r0
/* 8001DAF8 0001AA58  90 05 00 18 */	stw r0, 0x18(r5)
/* 8001DAFC 0001AA5C  80 AD 81 38 */	lwz r5, buf@sda21(r13)
/* 8001DB00 0001AA60  80 05 00 14 */	lwz r0, 0x14(r5)
/* 8001DB04 0001AA64  7C 00 22 14 */	add r0, r0, r4
/* 8001DB08 0001AA68  90 05 00 14 */	stw r0, 0x14(r5)
/* 8001DB0C 0001AA6C  4E 80 00 20 */	blr 
.endfn Jac_SendStreamData__FPUcUl

.balign 32, 0
.fn Jac_CheckStreamFree__FUl, global
/* 8001DB20 0001AA80  80 8D 81 38 */	lwz r4, buf@sda21(r13)
/* 8001DB24 0001AA84  80 04 00 18 */	lwz r0, 0x18(r4)
/* 8001DB28 0001AA88  7C 00 18 40 */	cmplw r0, r3
/* 8001DB2C 0001AA8C  41 80 00 0C */	blt .L_8001DB38
/* 8001DB30 0001AA90  38 60 00 01 */	li r3, 1
/* 8001DB34 0001AA94  4E 80 00 20 */	blr 
.L_8001DB38:
/* 8001DB38 0001AA98  38 60 00 00 */	li r3, 0
/* 8001DB3C 0001AA9C  4E 80 00 20 */	blr 
.endfn Jac_CheckStreamFree__FUl

.balign 32, 0
.fn Jac_CheckStreamRemain__FUl, global
/* 8001DB40 0001AAA0  80 8D 81 38 */	lwz r4, buf@sda21(r13)
/* 8001DB44 0001AAA4  80 04 00 14 */	lwz r0, 0x14(r4)
/* 8001DB48 0001AAA8  7C 00 18 40 */	cmplw r0, r3
/* 8001DB4C 0001AAAC  40 80 00 0C */	bge .L_8001DB58
/* 8001DB50 0001AAB0  38 60 00 00 */	li r3, 0
/* 8001DB54 0001AAB4  4E 80 00 20 */	blr 
.L_8001DB58:
/* 8001DB58 0001AAB8  38 60 00 01 */	li r3, 1
/* 8001DB5C 0001AABC  4E 80 00 20 */	blr 
.endfn Jac_CheckStreamRemain__FUl

.balign 32, 0
.fn Jac_GetStreamData__FPUcUl, global
/* 8001DB60 0001AAC0  80 CD 81 38 */	lwz r6, buf@sda21(r13)
/* 8001DB64 0001AAC4  80 06 00 00 */	lwz r0, 0(r6)
/* 8001DB68 0001AAC8  2C 00 00 00 */	cmpwi r0, 0
/* 8001DB6C 0001AACC  41 82 00 28 */	beq .L_8001DB94
/* 8001DB70 0001AAD0  80 06 00 08 */	lwz r0, 8(r6)
/* 8001DB74 0001AAD4  80 A6 00 14 */	lwz r5, 0x14(r6)
/* 8001DB78 0001AAD8  54 00 F8 7E */	srwi r0, r0, 1
/* 8001DB7C 0001AADC  7C 05 00 40 */	cmplw r5, r0
/* 8001DB80 0001AAE0  40 80 00 0C */	bge .L_8001DB8C
/* 8001DB84 0001AAE4  38 60 00 00 */	li r3, 0
/* 8001DB88 0001AAE8  4E 80 00 20 */	blr 
.L_8001DB8C:
/* 8001DB8C 0001AAEC  38 00 00 00 */	li r0, 0
/* 8001DB90 0001AAF0  90 06 00 00 */	stw r0, 0(r6)
.L_8001DB94:
/* 8001DB94 0001AAF4  80 AD 81 38 */	lwz r5, buf@sda21(r13)
/* 8001DB98 0001AAF8  80 05 00 14 */	lwz r0, 0x14(r5)
/* 8001DB9C 0001AAFC  7C 00 20 40 */	cmplw r0, r4
/* 8001DBA0 0001AB00  40 80 00 08 */	bge .L_8001DBA8
/* 8001DBA4 0001AB04  7C 04 03 78 */	mr r4, r0
.L_8001DBA8:
/* 8001DBA8 0001AB08  38 00 00 00 */	li r0, 0
/* 8001DBAC 0001AB0C  7C 89 03 A6 */	mtctr r4
/* 8001DBB0 0001AB10  28 04 00 00 */	cmplwi r4, 0
/* 8001DBB4 0001AB14  40 81 00 44 */	ble .L_8001DBF8
.L_8001DBB8:
/* 8001DBB8 0001AB18  81 0D 81 38 */	lwz r8, buf@sda21(r13)
/* 8001DBBC 0001AB1C  80 C8 00 10 */	lwz r6, 0x10(r8)
/* 8001DBC0 0001AB20  80 E8 00 04 */	lwz r7, 4(r8)
/* 8001DBC4 0001AB24  38 A6 00 01 */	addi r5, r6, 1
/* 8001DBC8 0001AB28  90 A8 00 10 */	stw r5, 0x10(r8)
/* 8001DBCC 0001AB2C  7C A7 30 AE */	lbzx r5, r7, r6
/* 8001DBD0 0001AB30  98 A3 00 00 */	stb r5, 0(r3)
/* 8001DBD4 0001AB34  80 AD 81 38 */	lwz r5, buf@sda21(r13)
/* 8001DBD8 0001AB38  38 E5 00 10 */	addi r7, r5, 0x10
/* 8001DBDC 0001AB3C  80 A5 00 08 */	lwz r5, 8(r5)
/* 8001DBE0 0001AB40  80 C7 00 00 */	lwz r6, 0(r7)
/* 8001DBE4 0001AB44  7C 06 28 40 */	cmplw r6, r5
/* 8001DBE8 0001AB48  40 82 00 08 */	bne .L_8001DBF0
/* 8001DBEC 0001AB4C  90 07 00 00 */	stw r0, 0(r7)
.L_8001DBF0:
/* 8001DBF0 0001AB50  38 63 00 01 */	addi r3, r3, 1
/* 8001DBF4 0001AB54  42 00 FF C4 */	bdnz .L_8001DBB8
.L_8001DBF8:
/* 8001DBF8 0001AB58  80 AD 81 38 */	lwz r5, buf@sda21(r13)
/* 8001DBFC 0001AB5C  7C 83 23 78 */	mr r3, r4
/* 8001DC00 0001AB60  80 05 00 14 */	lwz r0, 0x14(r5)
/* 8001DC04 0001AB64  7C 04 00 50 */	subf r0, r4, r0
/* 8001DC08 0001AB68  90 05 00 14 */	stw r0, 0x14(r5)
/* 8001DC0C 0001AB6C  80 AD 81 38 */	lwz r5, buf@sda21(r13)
/* 8001DC10 0001AB70  80 05 00 18 */	lwz r0, 0x18(r5)
/* 8001DC14 0001AB74  7C 00 22 14 */	add r0, r0, r4
/* 8001DC18 0001AB78  90 05 00 18 */	stw r0, 0x18(r5)
/* 8001DC1C 0001AB7C  4E 80 00 20 */	blr 
.endfn Jac_GetStreamData__FPUcUl

.balign 32, 0
.fn Jac_InitStreamData__FPUcUl, global
/* 8001DC20 0001AB80  80 CD 81 38 */	lwz r6, buf@sda21(r13)
/* 8001DC24 0001AB84  38 A0 00 00 */	li r5, 0
/* 8001DC28 0001AB88  38 00 00 01 */	li r0, 1
/* 8001DC2C 0001AB8C  90 66 00 04 */	stw r3, 4(r6)
/* 8001DC30 0001AB90  80 6D 81 38 */	lwz r3, buf@sda21(r13)
/* 8001DC34 0001AB94  90 83 00 08 */	stw r4, 8(r3)
/* 8001DC38 0001AB98  80 6D 81 38 */	lwz r3, buf@sda21(r13)
/* 8001DC3C 0001AB9C  90 A3 00 0C */	stw r5, 0xc(r3)
/* 8001DC40 0001ABA0  80 6D 81 38 */	lwz r3, buf@sda21(r13)
/* 8001DC44 0001ABA4  90 A3 00 10 */	stw r5, 0x10(r3)
/* 8001DC48 0001ABA8  80 6D 81 38 */	lwz r3, buf@sda21(r13)
/* 8001DC4C 0001ABAC  90 A3 00 14 */	stw r5, 0x14(r3)
/* 8001DC50 0001ABB0  80 6D 81 38 */	lwz r3, buf@sda21(r13)
/* 8001DC54 0001ABB4  90 83 00 18 */	stw r4, 0x18(r3)
/* 8001DC58 0001ABB8  80 6D 81 38 */	lwz r3, buf@sda21(r13)
/* 8001DC5C 0001ABBC  90 03 00 00 */	stw r0, 0(r3)
/* 8001DC60 0001ABC0  4E 80 00 20 */	blr 
.endfn Jac_InitStreamData__FPUcUl

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.balign 8
.obj buf, local
	.4byte interleavebuf
.endobj buf
