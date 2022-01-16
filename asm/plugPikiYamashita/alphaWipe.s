.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.global __ct__Q23zen9AlphaWipeFv
__ct__Q23zen9AlphaWipeFv:
/* 801F19D8 001EE938  38 80 00 00 */	li r4, 0
/* 801F19DC 001EE93C  90 83 00 00 */	stw r4, 0(r3)
/* 801F19E0 001EE940  38 00 00 FF */	li r0, 0xff
/* 801F19E4 001EE944  90 83 00 04 */	stw r4, 4(r3)
/* 801F19E8 001EE948  90 83 00 08 */	stw r4, 8(r3)
/* 801F19EC 001EE94C  C0 02 C2 38 */	lfs f0, lbl_803EC438@sda21(r2)
/* 801F19F0 001EE950  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 801F19F4 001EE954  C0 02 C2 3C */	lfs f0, lbl_803EC43C@sda21(r2)
/* 801F19F8 001EE958  D0 03 00 10 */	stfs f0, 0x10(r3)
/* 801F19FC 001EE95C  98 03 00 20 */	stb r0, 0x20(r3)
/* 801F1A00 001EE960  98 03 00 21 */	stb r0, 0x21(r3)
/* 801F1A04 001EE964  98 03 00 22 */	stb r0, 0x22(r3)
/* 801F1A08 001EE968  98 03 00 23 */	stb r0, 0x23(r3)
/* 801F1A0C 001EE96C  98 03 00 24 */	stb r0, 0x24(r3)
/* 801F1A10 001EE970  98 03 00 25 */	stb r0, 0x25(r3)
/* 801F1A14 001EE974  98 03 00 26 */	stb r0, 0x26(r3)
/* 801F1A18 001EE978  98 03 00 27 */	stb r0, 0x27(r3)
/* 801F1A1C 001EE97C  4E 80 00 20 */	blr 

.global update__Q23zen9AlphaWipeFv
update__Q23zen9AlphaWipeFv:
/* 801F1A20 001EE980  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 801F1A24 001EE984  80 03 00 00 */	lwz r0, 0(r3)
/* 801F1A28 001EE988  2C 00 00 01 */	cmpwi r0, 1
/* 801F1A2C 001EE98C  40 82 01 F8 */	bne lbl_801F1C24
/* 801F1A30 001EE990  80 8D 2D EC */	lwz r4, gsys@sda21(r13)
/* 801F1A34 001EE994  C0 23 00 0C */	lfs f1, 0xc(r3)
/* 801F1A38 001EE998  C0 04 02 8C */	lfs f0, 0x28c(r4)
/* 801F1A3C 001EE99C  EC 01 00 2A */	fadds f0, f1, f0
/* 801F1A40 001EE9A0  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 801F1A44 001EE9A4  80 8D 2D EC */	lwz r4, gsys@sda21(r13)
/* 801F1A48 001EE9A8  C0 23 00 14 */	lfs f1, 0x14(r3)
/* 801F1A4C 001EE9AC  C0 04 02 8C */	lfs f0, 0x28c(r4)
/* 801F1A50 001EE9B0  EC 01 00 2A */	fadds f0, f1, f0
/* 801F1A54 001EE9B4  D0 03 00 14 */	stfs f0, 0x14(r3)
/* 801F1A58 001EE9B8  C0 23 00 0C */	lfs f1, 0xc(r3)
/* 801F1A5C 001EE9BC  C0 03 00 10 */	lfs f0, 0x10(r3)
/* 801F1A60 001EE9C0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 801F1A64 001EE9C4  40 81 00 10 */	ble lbl_801F1A74
/* 801F1A68 001EE9C8  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 801F1A6C 001EE9CC  C0 82 C2 3C */	lfs f4, lbl_803EC43C@sda21(r2)
/* 801F1A70 001EE9D0  48 00 00 08 */	b lbl_801F1A78
lbl_801F1A74:
/* 801F1A74 001EE9D4  EC 81 00 24 */	fdivs f4, f1, f0
lbl_801F1A78:
/* 801F1A78 001EE9D8  C0 43 00 14 */	lfs f2, 0x14(r3)
/* 801F1A7C 001EE9DC  C0 23 00 10 */	lfs f1, 0x10(r3)
/* 801F1A80 001EE9E0  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 801F1A84 001EE9E4  40 81 00 10 */	ble lbl_801F1A94
/* 801F1A88 001EE9E8  D0 23 00 14 */	stfs f1, 0x14(r3)
/* 801F1A8C 001EE9EC  C0 A2 C2 3C */	lfs f5, lbl_803EC43C@sda21(r2)
/* 801F1A90 001EE9F0  48 00 00 1C */	b lbl_801F1AAC
lbl_801F1A94:
/* 801F1A94 001EE9F4  C0 02 C2 38 */	lfs f0, lbl_803EC438@sda21(r2)
/* 801F1A98 001EE9F8  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 801F1A9C 001EE9FC  40 80 00 0C */	bge lbl_801F1AA8
/* 801F1AA0 001EEA00  FC A0 00 90 */	fmr f5, f0
/* 801F1AA4 001EEA04  48 00 00 08 */	b lbl_801F1AAC
lbl_801F1AA8:
/* 801F1AA8 001EEA08  EC A2 08 24 */	fdivs f5, f2, f1
lbl_801F1AAC:
/* 801F1AAC 001EEA0C  80 83 00 04 */	lwz r4, 4(r3)
/* 801F1AB0 001EEA10  54 80 07 FF */	clrlwi. r0, r4, 0x1f
/* 801F1AB4 001EEA14  41 82 00 48 */	beq lbl_801F1AFC
/* 801F1AB8 001EEA18  C0 02 C2 3C */	lfs f0, lbl_803EC43C@sda21(r2)
/* 801F1ABC 001EEA1C  C0 22 C2 40 */	lfs f1, lbl_803EC440@sda21(r2)
/* 801F1AC0 001EEA20  FC 00 28 00 */	fcmpu cr0, f0, f5
/* 801F1AC4 001EEA24  EC C1 01 32 */	fmuls f6, f1, f4
/* 801F1AC8 001EEA28  EC 61 01 72 */	fmuls f3, f1, f5
/* 801F1ACC 001EEA2C  40 82 00 68 */	bne lbl_801F1B34
/* 801F1AD0 001EEA30  54 80 00 3C */	rlwinm r0, r4, 0, 0, 0x1e
/* 801F1AD4 001EEA34  90 03 00 04 */	stw r0, 4(r3)
/* 801F1AD8 001EEA38  80 03 00 04 */	lwz r0, 4(r3)
/* 801F1ADC 001EEA3C  60 00 00 02 */	ori r0, r0, 2
/* 801F1AE0 001EEA40  90 03 00 04 */	stw r0, 4(r3)
/* 801F1AE4 001EEA44  C0 02 C2 38 */	lfs f0, lbl_803EC438@sda21(r2)
/* 801F1AE8 001EEA48  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 801F1AEC 001EEA4C  C0 03 00 1C */	lfs f0, 0x1c(r3)
/* 801F1AF0 001EEA50  FC 00 00 50 */	fneg f0, f0
/* 801F1AF4 001EEA54  D0 03 00 14 */	stfs f0, 0x14(r3)
/* 801F1AF8 001EEA58  48 00 00 3C */	b lbl_801F1B34
lbl_801F1AFC:
/* 801F1AFC 001EEA5C  54 80 07 BD */	rlwinm. r0, r4, 0, 0x1e, 0x1e
/* 801F1B00 001EEA60  41 82 00 34 */	beq lbl_801F1B34
/* 801F1B04 001EEA64  C0 42 C2 3C */	lfs f2, lbl_803EC43C@sda21(r2)
/* 801F1B08 001EEA68  C0 62 C2 40 */	lfs f3, lbl_803EC440@sda21(r2)
/* 801F1B0C 001EEA6C  EC 22 20 28 */	fsubs f1, f2, f4
/* 801F1B10 001EEA70  EC 02 28 28 */	fsubs f0, f2, f5
/* 801F1B14 001EEA74  FC 02 28 00 */	fcmpu cr0, f2, f5
/* 801F1B18 001EEA78  EC C3 00 72 */	fmuls f6, f3, f1
/* 801F1B1C 001EEA7C  EC 63 00 32 */	fmuls f3, f3, f0
/* 801F1B20 001EEA80  40 82 00 14 */	bne lbl_801F1B34
/* 801F1B24 001EEA84  54 80 07 FA */	rlwinm r0, r4, 0, 0x1f, 0x1d
/* 801F1B28 001EEA88  90 03 00 04 */	stw r0, 4(r3)
/* 801F1B2C 001EEA8C  38 00 00 00 */	li r0, 0
/* 801F1B30 001EEA90  90 03 00 00 */	stw r0, 0(r3)
lbl_801F1B34:
/* 801F1B34 001EEA94  80 03 00 08 */	lwz r0, 8(r3)
/* 801F1B38 001EEA98  2C 00 00 01 */	cmpwi r0, 1
/* 801F1B3C 001EEA9C  41 82 00 80 */	beq lbl_801F1BBC
/* 801F1B40 001EEAA0  40 80 00 E4 */	bge lbl_801F1C24
/* 801F1B44 001EEAA4  2C 00 00 00 */	cmpwi r0, 0
/* 801F1B48 001EEAA8  40 80 00 08 */	bge lbl_801F1B50
/* 801F1B4C 001EEAAC  48 00 00 D8 */	b lbl_801F1C24
lbl_801F1B50:
/* 801F1B50 001EEAB0  C0 02 C2 38 */	lfs f0, lbl_803EC438@sda21(r2)
/* 801F1B54 001EEAB4  FC 06 00 40 */	fcmpo cr0, f6, f0
/* 801F1B58 001EEAB8  4C 41 13 82 */	cror 2, 1, 2
/* 801F1B5C 001EEABC  40 82 00 10 */	bne lbl_801F1B6C
/* 801F1B60 001EEAC0  C0 02 C2 44 */	lfs f0, lbl_803EC444@sda21(r2)
/* 801F1B64 001EEAC4  EC 00 30 2A */	fadds f0, f0, f6
/* 801F1B68 001EEAC8  48 00 00 0C */	b lbl_801F1B74
lbl_801F1B6C:
/* 801F1B6C 001EEACC  C0 02 C2 44 */	lfs f0, lbl_803EC444@sda21(r2)
/* 801F1B70 001EEAD0  EC 06 00 28 */	fsubs f0, f6, f0
lbl_801F1B74:
/* 801F1B74 001EEAD4  FC 00 00 1E */	fctiwz f0, f0
/* 801F1B78 001EEAD8  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 801F1B7C 001EEADC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801F1B80 001EEAE0  98 03 00 23 */	stb r0, 0x23(r3)
/* 801F1B84 001EEAE4  C0 02 C2 38 */	lfs f0, lbl_803EC438@sda21(r2)
/* 801F1B88 001EEAE8  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 801F1B8C 001EEAEC  4C 41 13 82 */	cror 2, 1, 2
/* 801F1B90 001EEAF0  40 82 00 10 */	bne lbl_801F1BA0
/* 801F1B94 001EEAF4  C0 02 C2 44 */	lfs f0, lbl_803EC444@sda21(r2)
/* 801F1B98 001EEAF8  EC 00 18 2A */	fadds f0, f0, f3
/* 801F1B9C 001EEAFC  48 00 00 0C */	b lbl_801F1BA8
lbl_801F1BA0:
/* 801F1BA0 001EEB00  C0 02 C2 44 */	lfs f0, lbl_803EC444@sda21(r2)
/* 801F1BA4 001EEB04  EC 03 00 28 */	fsubs f0, f3, f0
lbl_801F1BA8:
/* 801F1BA8 001EEB08  FC 00 00 1E */	fctiwz f0, f0
/* 801F1BAC 001EEB0C  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 801F1BB0 001EEB10  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801F1BB4 001EEB14  98 03 00 27 */	stb r0, 0x27(r3)
/* 801F1BB8 001EEB18  48 00 00 6C */	b lbl_801F1C24
lbl_801F1BBC:
/* 801F1BBC 001EEB1C  C0 02 C2 38 */	lfs f0, lbl_803EC438@sda21(r2)
/* 801F1BC0 001EEB20  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 801F1BC4 001EEB24  4C 41 13 82 */	cror 2, 1, 2
/* 801F1BC8 001EEB28  40 82 00 10 */	bne lbl_801F1BD8
/* 801F1BCC 001EEB2C  C0 02 C2 44 */	lfs f0, lbl_803EC444@sda21(r2)
/* 801F1BD0 001EEB30  EC 00 18 2A */	fadds f0, f0, f3
/* 801F1BD4 001EEB34  48 00 00 0C */	b lbl_801F1BE0
lbl_801F1BD8:
/* 801F1BD8 001EEB38  C0 02 C2 44 */	lfs f0, lbl_803EC444@sda21(r2)
/* 801F1BDC 001EEB3C  EC 03 00 28 */	fsubs f0, f3, f0
lbl_801F1BE0:
/* 801F1BE0 001EEB40  FC 00 00 1E */	fctiwz f0, f0
/* 801F1BE4 001EEB44  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 801F1BE8 001EEB48  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801F1BEC 001EEB4C  98 03 00 23 */	stb r0, 0x23(r3)
/* 801F1BF0 001EEB50  C0 02 C2 38 */	lfs f0, lbl_803EC438@sda21(r2)
/* 801F1BF4 001EEB54  FC 06 00 40 */	fcmpo cr0, f6, f0
/* 801F1BF8 001EEB58  4C 41 13 82 */	cror 2, 1, 2
/* 801F1BFC 001EEB5C  40 82 00 10 */	bne lbl_801F1C0C
/* 801F1C00 001EEB60  C0 02 C2 44 */	lfs f0, lbl_803EC444@sda21(r2)
/* 801F1C04 001EEB64  EC 00 30 2A */	fadds f0, f0, f6
/* 801F1C08 001EEB68  48 00 00 0C */	b lbl_801F1C14
lbl_801F1C0C:
/* 801F1C0C 001EEB6C  C0 02 C2 44 */	lfs f0, lbl_803EC444@sda21(r2)
/* 801F1C10 001EEB70  EC 06 00 28 */	fsubs f0, f6, f0
lbl_801F1C14:
/* 801F1C14 001EEB74  FC 00 00 1E */	fctiwz f0, f0
/* 801F1C18 001EEB78  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 801F1C1C 001EEB7C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801F1C20 001EEB80  98 03 00 27 */	stb r0, 0x27(r3)
lbl_801F1C24:
/* 801F1C24 001EEB84  38 21 00 40 */	addi r1, r1, 0x40
/* 801F1C28 001EEB88  4E 80 00 20 */	blr 

.global draw__Q23zen9AlphaWipeFR8Graphics
draw__Q23zen9AlphaWipeFR8Graphics:
/* 801F1C2C 001EEB8C  7C 08 02 A6 */	mflr r0
/* 801F1C30 001EEB90  90 01 00 04 */	stw r0, 4(r1)
/* 801F1C34 001EEB94  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 801F1C38 001EEB98  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 801F1C3C 001EEB9C  93 C1 00 78 */	stw r30, 0x78(r1)
/* 801F1C40 001EEBA0  3B C4 00 00 */	addi r30, r4, 0
/* 801F1C44 001EEBA4  93 A1 00 74 */	stw r29, 0x74(r1)
/* 801F1C48 001EEBA8  7C 7D 1B 78 */	mr r29, r3
/* 801F1C4C 001EEBAC  80 03 00 00 */	lwz r0, 0(r3)
/* 801F1C50 001EEBB0  2C 00 00 01 */	cmpwi r0, 1
/* 801F1C54 001EEBB4  40 82 00 A0 */	bne lbl_801F1CF4
/* 801F1C58 001EEBB8  80 DE 03 10 */	lwz r6, 0x310(r30)
/* 801F1C5C 001EEBBC  3B E0 00 00 */	li r31, 0
/* 801F1C60 001EEBC0  80 1E 03 0C */	lwz r0, 0x30c(r30)
/* 801F1C64 001EEBC4  38 A1 00 20 */	addi r5, r1, 0x20
/* 801F1C68 001EEBC8  38 7E 00 00 */	addi r3, r30, 0
/* 801F1C6C 001EEBCC  93 E1 00 20 */	stw r31, 0x20(r1)
/* 801F1C70 001EEBD0  38 81 00 30 */	addi r4, r1, 0x30
/* 801F1C74 001EEBD4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 801F1C78 001EEBD8  90 01 00 28 */	stw r0, 0x28(r1)
/* 801F1C7C 001EEBDC  90 C1 00 2C */	stw r6, 0x2c(r1)
/* 801F1C80 001EEBE0  81 9E 03 B4 */	lwz r12, 0x3b4(r30)
/* 801F1C84 001EEBE4  81 8C 00 40 */	lwz r12, 0x40(r12)
/* 801F1C88 001EEBE8  7D 88 03 A6 */	mtlr r12
/* 801F1C8C 001EEBEC  4E 80 00 21 */	blrl 
/* 801F1C90 001EEBF0  7F C3 F3 78 */	mr r3, r30
/* 801F1C94 001EEBF4  81 9E 03 B4 */	lwz r12, 0x3b4(r30)
/* 801F1C98 001EEBF8  38 9D 00 20 */	addi r4, r29, 0x20
/* 801F1C9C 001EEBFC  38 A0 00 01 */	li r5, 1
/* 801F1CA0 001EEC00  81 8C 00 A8 */	lwz r12, 0xa8(r12)
/* 801F1CA4 001EEC04  7D 88 03 A6 */	mtlr r12
/* 801F1CA8 001EEC08  4E 80 00 21 */	blrl 
/* 801F1CAC 001EEC0C  7F C3 F3 78 */	mr r3, r30
/* 801F1CB0 001EEC10  81 9E 03 B4 */	lwz r12, 0x3b4(r30)
/* 801F1CB4 001EEC14  38 9D 00 24 */	addi r4, r29, 0x24
/* 801F1CB8 001EEC18  81 8C 00 AC */	lwz r12, 0xac(r12)
/* 801F1CBC 001EEC1C  7D 88 03 A6 */	mtlr r12
/* 801F1CC0 001EEC20  4E 80 00 21 */	blrl 
/* 801F1CC4 001EEC24  80 BE 03 10 */	lwz r5, 0x310(r30)
/* 801F1CC8 001EEC28  38 81 00 10 */	addi r4, r1, 0x10
/* 801F1CCC 001EEC2C  80 1E 03 0C */	lwz r0, 0x30c(r30)
/* 801F1CD0 001EEC30  7F C3 F3 78 */	mr r3, r30
/* 801F1CD4 001EEC34  93 E1 00 10 */	stw r31, 0x10(r1)
/* 801F1CD8 001EEC38  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801F1CDC 001EEC3C  90 01 00 18 */	stw r0, 0x18(r1)
/* 801F1CE0 001EEC40  90 A1 00 1C */	stw r5, 0x1c(r1)
/* 801F1CE4 001EEC44  81 9E 03 B4 */	lwz r12, 0x3b4(r30)
/* 801F1CE8 001EEC48  81 8C 00 D4 */	lwz r12, 0xd4(r12)
/* 801F1CEC 001EEC4C  7D 88 03 A6 */	mtlr r12
/* 801F1CF0 001EEC50  4E 80 00 21 */	blrl 
lbl_801F1CF4:
/* 801F1CF4 001EEC54  80 01 00 84 */	lwz r0, 0x84(r1)
/* 801F1CF8 001EEC58  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 801F1CFC 001EEC5C  83 C1 00 78 */	lwz r30, 0x78(r1)
/* 801F1D00 001EEC60  83 A1 00 74 */	lwz r29, 0x74(r1)
/* 801F1D04 001EEC64  38 21 00 80 */	addi r1, r1, 0x80
/* 801F1D08 001EEC68  7C 08 03 A6 */	mtlr r0
/* 801F1D0C 001EEC6C  4E 80 00 20 */	blr 

.global start__Q23zen9AlphaWipeFffQ33zen9AlphaWipe8typeFlag
start__Q23zen9AlphaWipeFffQ33zen9AlphaWipe8typeFlag:
/* 801F1D10 001EEC70  C0 02 C2 44 */	lfs f0, lbl_803EC444@sda21(r2)
/* 801F1D14 001EEC74  38 00 00 01 */	li r0, 1
/* 801F1D18 001EEC78  90 03 00 00 */	stw r0, 0(r3)
/* 801F1D1C 001EEC7C  EC 21 00 32 */	fmuls f1, f1, f0
/* 801F1D20 001EEC80  90 03 00 04 */	stw r0, 4(r3)
/* 801F1D24 001EEC84  C0 02 C2 38 */	lfs f0, lbl_803EC438@sda21(r2)
/* 801F1D28 001EEC88  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 801F1D2C 001EEC8C  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 801F1D30 001EEC90  D0 23 00 10 */	stfs f1, 0x10(r3)
/* 801F1D34 001EEC94  40 80 00 08 */	bge lbl_801F1D3C
/* 801F1D38 001EEC98  FC 40 00 90 */	fmr f2, f0
lbl_801F1D3C:
/* 801F1D3C 001EEC9C  FC 00 10 50 */	fneg f0, f2
/* 801F1D40 001EECA0  D0 43 00 1C */	stfs f2, 0x1c(r3)
/* 801F1D44 001EECA4  38 00 00 00 */	li r0, 0
/* 801F1D48 001EECA8  D0 03 00 14 */	stfs f0, 0x14(r3)
/* 801F1D4C 001EECAC  D0 23 00 18 */	stfs f1, 0x18(r3)
/* 801F1D50 001EECB0  90 83 00 08 */	stw r4, 8(r3)
/* 801F1D54 001EECB4  98 03 00 23 */	stb r0, 0x23(r3)
/* 801F1D58 001EECB8  98 03 00 27 */	stb r0, 0x27(r3)
/* 801F1D5C 001EECBC  4E 80 00 20 */	blr 

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.balign 8
.global lbl_803EC438
lbl_803EC438:
	.float 0.0
.global lbl_803EC43C
lbl_803EC43C:
	.float 1.0
.global lbl_803EC440
lbl_803EC440:
	.float 255.0
.global lbl_803EC444
lbl_803EC444:
	.float 0.5
