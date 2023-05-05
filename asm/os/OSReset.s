.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.fn OSRegisterResetFunction, global
/* 801FA0C0 001F7020  80 AD 32 08 */	lwz r5, ResetFunctionQueue@sda21(r13)
/* 801FA0C4 001F7024  48 00 00 08 */	b .L_801FA0CC
.L_801FA0C8:
/* 801FA0C8 001F7028  80 A5 00 08 */	lwz r5, 8(r5)
.L_801FA0CC:
/* 801FA0CC 001F702C  28 05 00 00 */	cmplwi r5, 0
/* 801FA0D0 001F7030  41 82 00 14 */	beq .L_801FA0E4
/* 801FA0D4 001F7034  80 85 00 04 */	lwz r4, 4(r5)
/* 801FA0D8 001F7038  80 03 00 04 */	lwz r0, 4(r3)
/* 801FA0DC 001F703C  7C 04 00 40 */	cmplw r4, r0
/* 801FA0E0 001F7040  40 81 FF E8 */	ble .L_801FA0C8
.L_801FA0E4:
/* 801FA0E4 001F7044  28 05 00 00 */	cmplwi r5, 0
/* 801FA0E8 001F7048  40 82 00 34 */	bne .L_801FA11C
/* 801FA0EC 001F704C  38 AD 32 08 */	addi r5, r13, ResetFunctionQueue@sda21
/* 801FA0F0 001F7050  84 85 00 04 */	lwzu r4, 4(r5)
/* 801FA0F4 001F7054  28 04 00 00 */	cmplwi r4, 0
/* 801FA0F8 001F7058  40 82 00 0C */	bne .L_801FA104
/* 801FA0FC 001F705C  90 6D 32 08 */	stw r3, ResetFunctionQueue@sda21(r13)
/* 801FA100 001F7060  48 00 00 08 */	b .L_801FA108
.L_801FA104:
/* 801FA104 001F7064  90 64 00 08 */	stw r3, 8(r4)
.L_801FA108:
/* 801FA108 001F7068  90 83 00 0C */	stw r4, 0xc(r3)
/* 801FA10C 001F706C  38 00 00 00 */	li r0, 0
/* 801FA110 001F7070  90 03 00 08 */	stw r0, 8(r3)
/* 801FA114 001F7074  90 65 00 00 */	stw r3, 0(r5)
/* 801FA118 001F7078  4E 80 00 20 */	blr 
.L_801FA11C:
/* 801FA11C 001F707C  90 A3 00 08 */	stw r5, 8(r3)
/* 801FA120 001F7080  80 85 00 0C */	lwz r4, 0xc(r5)
/* 801FA124 001F7084  90 65 00 0C */	stw r3, 0xc(r5)
/* 801FA128 001F7088  28 04 00 00 */	cmplwi r4, 0
/* 801FA12C 001F708C  90 83 00 0C */	stw r4, 0xc(r3)
/* 801FA130 001F7090  40 82 00 0C */	bne .L_801FA13C
/* 801FA134 001F7094  90 6D 32 08 */	stw r3, ResetFunctionQueue@sda21(r13)
/* 801FA138 001F7098  4E 80 00 20 */	blr 
.L_801FA13C:
/* 801FA13C 001F709C  90 64 00 08 */	stw r3, 8(r4)
/* 801FA140 001F70A0  4E 80 00 20 */	blr 
.endfn OSRegisterResetFunction

.fn Reset, local
/* 801FA144 001F70A4  48 00 00 20 */	b .L_801FA164
.L_801FA148:
/* 801FA148 001F70A8  7D 10 FA A6 */	mfspr r8, 0x3f0
/* 801FA14C 001F70AC  61 08 00 08 */	ori r8, r8, 8
/* 801FA150 001F70B0  7D 10 FB A6 */	mtspr 0x3f0, r8
/* 801FA154 001F70B4  4C 00 01 2C */	isync 
/* 801FA158 001F70B8  7C 00 04 AC */	sync 0
/* 801FA15C 001F70BC  60 00 00 00 */	nop 
/* 801FA160 001F70C0  48 00 00 08 */	b .L_801FA168
.L_801FA164:
/* 801FA164 001F70C4  48 00 00 20 */	b .L_801FA184
.L_801FA168:
/* 801FA168 001F70C8  7C AC 42 E6 */	mftb r5, 0x10c
.L_801FA16C:
/* 801FA16C 001F70CC  7C CC 42 E6 */	mftb r6, 0x10c
/* 801FA170 001F70D0  7C E5 30 50 */	subf r7, r5, r6
/* 801FA174 001F70D4  28 07 11 24 */	cmplwi r7, 0x1124
/* 801FA178 001F70D8  41 80 FF F4 */	blt .L_801FA16C
/* 801FA17C 001F70DC  60 00 00 00 */	nop 
/* 801FA180 001F70E0  48 00 00 08 */	b .L_801FA188
.L_801FA184:
/* 801FA184 001F70E4  48 00 00 20 */	b .L_801FA1A4
.L_801FA188:
/* 801FA188 001F70E8  3D 00 CC 00 */	lis r8, 0xCC003000@h
/* 801FA18C 001F70EC  61 08 30 00 */	ori r8, r8, 0xCC003000@l
/* 801FA190 001F70F0  38 80 00 03 */	li r4, 3
/* 801FA194 001F70F4  90 88 00 24 */	stw r4, 0x24(r8)
/* 801FA198 001F70F8  90 68 00 24 */	stw r3, 0x24(r8)
/* 801FA19C 001F70FC  60 00 00 00 */	nop 
/* 801FA1A0 001F7100  48 00 00 08 */	b .L_801FA1A8
.L_801FA1A4:
/* 801FA1A4 001F7104  48 00 00 0C */	b .L_801FA1B0
.L_801FA1A8:
/* 801FA1A8 001F7108  60 00 00 00 */	nop 
/* 801FA1AC 001F710C  4B FF FF FC */	b .L_801FA1A8
.L_801FA1B0:
/* 801FA1B0 001F7110  4B FF FF 98 */	b .L_801FA148
.endfn Reset

.fn __OSDoHotReset, global
/* 801FA1B4 001F7114  7C 08 02 A6 */	mflr r0
/* 801FA1B8 001F7118  90 01 00 04 */	stw r0, 4(r1)
/* 801FA1BC 001F711C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801FA1C0 001F7120  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801FA1C4 001F7124  7C 7F 1B 78 */	mr r31, r3
/* 801FA1C8 001F7128  4B FF ED B5 */	bl OSDisableInterrupts
/* 801FA1CC 001F712C  3C 60 CC 00 */	lis r3, 0xCC002000@ha
/* 801FA1D0 001F7130  38 63 20 00 */	addi r3, r3, 0xCC002000@l
/* 801FA1D4 001F7134  38 00 00 00 */	li r0, 0
/* 801FA1D8 001F7138  B0 03 00 02 */	sth r0, 2(r3)
/* 801FA1DC 001F713C  4B FF CB 3D */	bl ICFlashInvalidate
/* 801FA1E0 001F7140  57 E3 18 38 */	slwi r3, r31, 3
/* 801FA1E4 001F7144  4B FF FF 61 */	bl Reset
/* 801FA1E8 001F7148  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801FA1EC 001F714C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801FA1F0 001F7150  38 21 00 18 */	addi r1, r1, 0x18
/* 801FA1F4 001F7154  7C 08 03 A6 */	mtlr r0
/* 801FA1F8 001F7158  4E 80 00 20 */	blr 
.endfn __OSDoHotReset

.fn OSResetSystem, global
/* 801FA1FC 001F715C  7C 08 02 A6 */	mflr r0
/* 801FA200 001F7160  90 01 00 04 */	stw r0, 4(r1)
/* 801FA204 001F7164  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 801FA208 001F7168  BF 41 00 20 */	stmw r26, 0x20(r1)
/* 801FA20C 001F716C  7C 7A 1B 78 */	mr r26, r3
/* 801FA210 001F7170  7C 9E 23 78 */	mr r30, r4
/* 801FA214 001F7174  7C BF 2B 78 */	mr r31, r5
/* 801FA218 001F7178  48 00 19 0D */	bl OSDisableScheduler
/* 801FA21C 001F717C  4B FF C8 B1 */	bl __OSStopAudioSystem
/* 801FA220 001F7180  48 00 00 04 */	b .L_801FA224
.L_801FA224:
/* 801FA224 001F7184  48 00 00 04 */	b .L_801FA228
.L_801FA228:
/* 801FA228 001F7188  83 8D 32 08 */	lwz r28, ResetFunctionQueue@sda21(r13)
/* 801FA22C 001F718C  3B A0 00 00 */	li r29, 0
/* 801FA230 001F7190  48 00 00 04 */	b .L_801FA234
.L_801FA234:
/* 801FA234 001F7194  48 00 00 04 */	b .L_801FA238
.L_801FA238:
/* 801FA238 001F7198  48 00 00 24 */	b .L_801FA25C
.L_801FA23C:
/* 801FA23C 001F719C  38 60 00 00 */	li r3, 0
/* 801FA240 001F71A0  81 9C 00 00 */	lwz r12, 0(r28)
/* 801FA244 001F71A4  7D 88 03 A6 */	mtlr r12
/* 801FA248 001F71A8  4E 80 00 21 */	blrl 
/* 801FA24C 001F71AC  7C 60 00 34 */	cntlzw r0, r3
/* 801FA250 001F71B0  83 9C 00 08 */	lwz r28, 8(r28)
/* 801FA254 001F71B4  54 00 D9 7E */	srwi r0, r0, 5
/* 801FA258 001F71B8  7F BD 03 78 */	or r29, r29, r0
.L_801FA25C:
/* 801FA25C 001F71BC  28 1C 00 00 */	cmplwi r28, 0
/* 801FA260 001F71C0  40 82 FF DC */	bne .L_801FA23C
/* 801FA264 001F71C4  48 00 0A ED */	bl __OSSyncSram
/* 801FA268 001F71C8  7C 60 00 34 */	cntlzw r0, r3
/* 801FA26C 001F71CC  54 00 D9 7E */	srwi r0, r0, 5
/* 801FA270 001F71D0  7F BD 03 78 */	or r29, r29, r0
/* 801FA274 001F71D4  2C 1D 00 00 */	cmpwi r29, 0
/* 801FA278 001F71D8  41 82 00 0C */	beq .L_801FA284
/* 801FA27C 001F71DC  38 00 00 00 */	li r0, 0
/* 801FA280 001F71E0  48 00 00 08 */	b .L_801FA288
.L_801FA284:
/* 801FA284 001F71E4  38 00 00 01 */	li r0, 1
.L_801FA288:
/* 801FA288 001F71E8  2C 00 00 00 */	cmpwi r0, 0
/* 801FA28C 001F71EC  41 82 FF 9C */	beq .L_801FA228
/* 801FA290 001F71F0  2C 1A 00 00 */	cmpwi r26, 0
/* 801FA294 001F71F4  41 82 00 38 */	beq .L_801FA2CC
/* 801FA298 001F71F8  2C 1F 00 00 */	cmpwi r31, 0
/* 801FA29C 001F71FC  41 82 00 30 */	beq .L_801FA2CC
/* 801FA2A0 001F7200  48 00 06 A9 */	bl __OSLockSram
/* 801FA2A4 001F7204  88 03 00 13 */	lbz r0, 0x13(r3)
/* 801FA2A8 001F7208  60 00 00 40 */	ori r0, r0, 0x40
/* 801FA2AC 001F720C  98 03 00 13 */	stb r0, 0x13(r3)
/* 801FA2B0 001F7210  38 60 00 01 */	li r3, 1
/* 801FA2B4 001F7214  48 00 0A 55 */	bl __OSUnlockSram
/* 801FA2B8 001F7218  48 00 00 04 */	b .L_801FA2BC
.L_801FA2BC:
/* 801FA2BC 001F721C  48 00 00 04 */	b .L_801FA2C0
.L_801FA2C0:
/* 801FA2C0 001F7220  48 00 0A 91 */	bl __OSSyncSram
/* 801FA2C4 001F7224  2C 03 00 00 */	cmpwi r3, 0
/* 801FA2C8 001F7228  41 82 FF F8 */	beq .L_801FA2C0
.L_801FA2CC:
/* 801FA2CC 001F722C  4B FF EC B1 */	bl OSDisableInterrupts
/* 801FA2D0 001F7230  83 AD 32 08 */	lwz r29, ResetFunctionQueue@sda21(r13)
/* 801FA2D4 001F7234  7C 7B 1B 78 */	mr r27, r3
/* 801FA2D8 001F7238  3B 80 00 00 */	li r28, 0
/* 801FA2DC 001F723C  48 00 00 04 */	b .L_801FA2E0
.L_801FA2E0:
/* 801FA2E0 001F7240  48 00 00 04 */	b .L_801FA2E4
.L_801FA2E4:
/* 801FA2E4 001F7244  48 00 00 24 */	b .L_801FA308
.L_801FA2E8:
/* 801FA2E8 001F7248  38 60 00 01 */	li r3, 1
/* 801FA2EC 001F724C  81 9D 00 00 */	lwz r12, 0(r29)
/* 801FA2F0 001F7250  7D 88 03 A6 */	mtlr r12
/* 801FA2F4 001F7254  4E 80 00 21 */	blrl 
/* 801FA2F8 001F7258  7C 60 00 34 */	cntlzw r0, r3
/* 801FA2FC 001F725C  83 BD 00 08 */	lwz r29, 8(r29)
/* 801FA300 001F7260  54 00 D9 7E */	srwi r0, r0, 5
/* 801FA304 001F7264  7F 9C 03 78 */	or r28, r28, r0
.L_801FA308:
/* 801FA308 001F7268  28 1D 00 00 */	cmplwi r29, 0
/* 801FA30C 001F726C  40 82 FF DC */	bne .L_801FA2E8
/* 801FA310 001F7270  48 00 0A 41 */	bl __OSSyncSram
/* 801FA314 001F7274  2C 1A 00 01 */	cmpwi r26, 1
/* 801FA318 001F7278  40 82 00 28 */	bne .L_801FA340
/* 801FA31C 001F727C  4B FF EC 61 */	bl OSDisableInterrupts
/* 801FA320 001F7280  3C 60 CC 00 */	lis r3, 0xCC002000@ha
/* 801FA324 001F7284  38 63 20 00 */	addi r3, r3, 0xCC002000@l
/* 801FA328 001F7288  38 00 00 00 */	li r0, 0
/* 801FA32C 001F728C  B0 03 00 02 */	sth r0, 2(r3)
/* 801FA330 001F7290  4B FF C9 E9 */	bl ICFlashInvalidate
/* 801FA334 001F7294  57 C3 18 38 */	slwi r3, r30, 3
/* 801FA338 001F7298  4B FF FE 0D */	bl Reset
/* 801FA33C 001F729C  48 00 00 58 */	b .L_801FA394
.L_801FA340:
/* 801FA340 001F72A0  3C 60 80 00 */	lis r3, 0x800000DC@ha
/* 801FA344 001F72A4  80 63 00 DC */	lwz r3, 0x800000DC@l(r3)
/* 801FA348 001F72A8  48 00 00 04 */	b .L_801FA34C
.L_801FA34C:
/* 801FA34C 001F72AC  48 00 00 04 */	b .L_801FA350
.L_801FA350:
/* 801FA350 001F72B0  48 00 00 2C */	b .L_801FA37C
.L_801FA354:
/* 801FA354 001F72B4  A0 03 02 C8 */	lhz r0, 0x2c8(r3)
/* 801FA358 001F72B8  83 83 02 FC */	lwz r28, 0x2fc(r3)
/* 801FA35C 001F72BC  2C 00 00 04 */	cmpwi r0, 4
/* 801FA360 001F72C0  41 82 00 14 */	beq .L_801FA374
/* 801FA364 001F72C4  40 80 00 14 */	bge .L_801FA378
/* 801FA368 001F72C8  2C 00 00 01 */	cmpwi r0, 1
/* 801FA36C 001F72CC  41 82 00 08 */	beq .L_801FA374
/* 801FA370 001F72D0  48 00 00 08 */	b .L_801FA378
.L_801FA374:
/* 801FA374 001F72D4  48 00 1F 55 */	bl OSCancelThread
.L_801FA378:
/* 801FA378 001F72D8  7F 83 E3 78 */	mr r3, r28
.L_801FA37C:
/* 801FA37C 001F72DC  28 03 00 00 */	cmplwi r3, 0
/* 801FA380 001F72E0  40 82 FF D4 */	bne .L_801FA354
/* 801FA384 001F72E4  48 00 17 E1 */	bl OSEnableScheduler
/* 801FA388 001F72E8  7F C3 F3 78 */	mr r3, r30
/* 801FA38C 001F72EC  7F E4 FB 78 */	mr r4, r31
/* 801FA390 001F72F0  4B FF FB 81 */	bl __OSReboot
.L_801FA394:
/* 801FA394 001F72F4  7F 63 DB 78 */	mr r3, r27
/* 801FA398 001F72F8  4B FF EC 0D */	bl OSRestoreInterrupts
/* 801FA39C 001F72FC  48 00 17 C9 */	bl OSEnableScheduler
/* 801FA3A0 001F7300  BB 41 00 20 */	lmw r26, 0x20(r1)
/* 801FA3A4 001F7304  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801FA3A8 001F7308  38 21 00 38 */	addi r1, r1, 0x38
/* 801FA3AC 001F730C  7C 08 03 A6 */	mtlr r0
/* 801FA3B0 001F7310  4E 80 00 20 */	blr 
.endfn OSResetSystem

.section .sbss, "wa"
.balign 8
.obj ResetFunctionQueue, local
	.skip 8
.endobj ResetFunctionQueue
