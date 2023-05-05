.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.fn OSGetTime, global
/* 801FD3A0 001FA300  7C 6D 42 E6 */	mftbu r3
/* 801FD3A4 001FA304  7C 8C 42 E6 */	mftb r4, 0x10c
/* 801FD3A8 001FA308  7C AD 42 E6 */	mftbu r5
/* 801FD3AC 001FA30C  7C 03 28 00 */	cmpw r3, r5
/* 801FD3B0 001FA310  40 82 FF F0 */	bne OSGetTime
/* 801FD3B4 001FA314  4E 80 00 20 */	blr 
.endfn OSGetTime

.fn OSGetTick, global
/* 801FD3B8 001FA318  7C 6C 42 E6 */	mftb r3, 0x10c
/* 801FD3BC 001FA31C  4E 80 00 20 */	blr 
.endfn OSGetTick

.fn __OSGetSystemTime, global
/* 801FD3C0 001FA320  7C 08 02 A6 */	mflr r0
/* 801FD3C4 001FA324  90 01 00 04 */	stw r0, 4(r1)
/* 801FD3C8 001FA328  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 801FD3CC 001FA32C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801FD3D0 001FA330  93 C1 00 18 */	stw r30, 0x18(r1)
/* 801FD3D4 001FA334  93 A1 00 14 */	stw r29, 0x14(r1)
/* 801FD3D8 001FA338  4B FF BB A5 */	bl OSDisableInterrupts
/* 801FD3DC 001FA33C  7C 7F 1B 78 */	mr r31, r3
/* 801FD3E0 001FA340  4B FF FF C1 */	bl OSGetTime
/* 801FD3E4 001FA344  3C C0 80 00 */	lis r6, 0x800030DC@ha
/* 801FD3E8 001FA348  80 A6 30 DC */	lwz r5, 0x800030DC@l(r6)
/* 801FD3EC 001FA34C  80 06 30 D8 */	lwz r0, 0x30d8(r6)
/* 801FD3F0 001FA350  7F A5 20 14 */	addc r29, r5, r4
/* 801FD3F4 001FA354  7F C0 19 14 */	adde r30, r0, r3
/* 801FD3F8 001FA358  7F E3 FB 78 */	mr r3, r31
/* 801FD3FC 001FA35C  4B FF BB A9 */	bl OSRestoreInterrupts
/* 801FD400 001FA360  7F A4 EB 78 */	mr r4, r29
/* 801FD404 001FA364  7F C3 F3 78 */	mr r3, r30
/* 801FD408 001FA368  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801FD40C 001FA36C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801FD410 001FA370  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 801FD414 001FA374  7C 08 03 A6 */	mtlr r0
/* 801FD418 001FA378  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 801FD41C 001FA37C  38 21 00 20 */	addi r1, r1, 0x20
/* 801FD420 001FA380  4E 80 00 20 */	blr 
.endfn __OSGetSystemTime

.fn GetDates, local
/* 801FD424 001FA384  3C A0 92 49 */	lis r5, 0x92492493@ha
/* 801FD428 001FA388  38 05 24 93 */	addi r0, r5, 0x92492493@l
/* 801FD42C 001FA38C  38 E3 00 06 */	addi r7, r3, 6
/* 801FD430 001FA390  7C C0 38 96 */	mulhw r6, r0, r7
/* 801FD434 001FA394  3C A0 B3 8D */	lis r5, 0xB38CF9B1@ha
/* 801FD438 001FA398  38 05 F9 B1 */	addi r0, r5, 0xB38CF9B1@l
/* 801FD43C 001FA39C  7C 00 18 96 */	mulhw r0, r0, r3
/* 801FD440 001FA3A0  7C A6 3A 14 */	add r5, r6, r7
/* 801FD444 001FA3A4  7C A5 16 70 */	srawi r5, r5, 2
/* 801FD448 001FA3A8  54 A6 0F FE */	srwi r6, r5, 0x1f
/* 801FD44C 001FA3AC  7C A5 32 14 */	add r5, r5, r6
/* 801FD450 001FA3B0  7C 00 1A 14 */	add r0, r0, r3
/* 801FD454 001FA3B4  1C C5 00 07 */	mulli r6, r5, 7
/* 801FD458 001FA3B8  7C 00 46 70 */	srawi r0, r0, 8
/* 801FD45C 001FA3BC  54 05 0F FE */	srwi r5, r0, 0x1f
/* 801FD460 001FA3C0  7C A0 2A 14 */	add r5, r0, r5
/* 801FD464 001FA3C4  7C 06 38 50 */	subf r0, r6, r7
/* 801FD468 001FA3C8  1D 65 01 6D */	mulli r11, r5, 0x16d
/* 801FD46C 001FA3CC  90 04 00 18 */	stw r0, 0x18(r4)
/* 801FD470 001FA3D0  48 00 00 04 */	b .L_801FD474
.L_801FD474:
/* 801FD474 001FA3D4  3C C0 51 EC */	lis r6, 0x51EB851F@ha
/* 801FD478 001FA3D8  39 46 85 1F */	addi r10, r6, 0x51EB851F@l
/* 801FD47C 001FA3DC  48 00 00 04 */	b .L_801FD480
.L_801FD480:
/* 801FD480 001FA3E0  48 00 00 0C */	b .L_801FD48C
.L_801FD484:
/* 801FD484 001FA3E4  39 6B FE 93 */	addi r11, r11, -365
/* 801FD488 001FA3E8  38 A5 FF FF */	addi r5, r5, -1
.L_801FD48C:
/* 801FD48C 001FA3EC  2C 05 00 01 */	cmpwi r5, 1
/* 801FD490 001FA3F0  40 80 00 0C */	bge .L_801FD49C
/* 801FD494 001FA3F4  38 00 00 00 */	li r0, 0
/* 801FD498 001FA3F8  48 00 00 38 */	b .L_801FD4D0
.L_801FD49C:
/* 801FD49C 001FA3FC  38 05 FF FF */	addi r0, r5, -1
/* 801FD4A0 001FA400  7C 0A 00 96 */	mulhw r0, r10, r0
/* 801FD4A4 001FA404  7C 08 3E 70 */	srawi r8, r0, 7
/* 801FD4A8 001FA408  7C 06 2E 70 */	srawi r6, r0, 5
/* 801FD4AC 001FA40C  38 05 00 03 */	addi r0, r5, 3
/* 801FD4B0 001FA410  54 C7 0F FE */	srwi r7, r6, 0x1f
/* 801FD4B4 001FA414  7C 00 16 70 */	srawi r0, r0, 2
/* 801FD4B8 001FA418  55 09 0F FE */	srwi r9, r8, 0x1f
/* 801FD4BC 001FA41C  7C C6 3A 14 */	add r6, r6, r7
/* 801FD4C0 001FA420  7C 00 01 94 */	addze r0, r0
/* 801FD4C4 001FA424  7C E8 4A 14 */	add r7, r8, r9
/* 801FD4C8 001FA428  7C 06 00 50 */	subf r0, r6, r0
/* 801FD4CC 001FA42C  7C 07 02 14 */	add r0, r7, r0
.L_801FD4D0:
/* 801FD4D0 001FA430  7C 0B 02 14 */	add r0, r11, r0
/* 801FD4D4 001FA434  7C 03 00 00 */	cmpw r3, r0
/* 801FD4D8 001FA438  41 80 FF AC */	blt .L_801FD484
/* 801FD4DC 001FA43C  7C A6 16 70 */	srawi r6, r5, 2
/* 801FD4E0 001FA440  90 A4 00 14 */	stw r5, 0x14(r4)
/* 801FD4E4 001FA444  7C C6 01 94 */	addze r6, r6
/* 801FD4E8 001FA448  54 C6 10 3A */	slwi r6, r6, 2
/* 801FD4EC 001FA44C  7C C6 28 10 */	subfc r6, r6, r5
/* 801FD4F0 001FA450  7C 00 18 50 */	subf r0, r0, r3
/* 801FD4F4 001FA454  2C 06 00 00 */	cmpwi r6, 0
/* 801FD4F8 001FA458  90 04 00 1C */	stw r0, 0x1c(r4)
/* 801FD4FC 001FA45C  38 E0 00 01 */	li r7, 1
/* 801FD500 001FA460  39 00 00 00 */	li r8, 0
/* 801FD504 001FA464  40 82 00 30 */	bne .L_801FD534
/* 801FD508 001FA468  3C 60 51 EC */	lis r3, 0x51EB851F@ha
/* 801FD50C 001FA46C  38 63 85 1F */	addi r3, r3, 0x51EB851F@l
/* 801FD510 001FA470  7C 63 28 96 */	mulhw r3, r3, r5
/* 801FD514 001FA474  7C 63 2E 70 */	srawi r3, r3, 5
/* 801FD518 001FA478  54 66 0F FE */	srwi r6, r3, 0x1f
/* 801FD51C 001FA47C  7C 63 32 14 */	add r3, r3, r6
/* 801FD520 001FA480  1C 63 00 64 */	mulli r3, r3, 0x64
/* 801FD524 001FA484  7C 63 28 50 */	subf r3, r3, r5
/* 801FD528 001FA488  2C 03 00 00 */	cmpwi r3, 0
/* 801FD52C 001FA48C  41 82 00 08 */	beq .L_801FD534
/* 801FD530 001FA490  7C E8 3B 78 */	mr r8, r7
.L_801FD534:
/* 801FD534 001FA494  2C 08 00 00 */	cmpwi r8, 0
/* 801FD538 001FA498  40 82 00 30 */	bne .L_801FD568
/* 801FD53C 001FA49C  3C 60 51 EC */	lis r3, 0x51EB851F@ha
/* 801FD540 001FA4A0  38 63 85 1F */	addi r3, r3, 0x51EB851F@l
/* 801FD544 001FA4A4  7C 63 28 96 */	mulhw r3, r3, r5
/* 801FD548 001FA4A8  7C 63 3E 70 */	srawi r3, r3, 7
/* 801FD54C 001FA4AC  54 66 0F FE */	srwi r6, r3, 0x1f
/* 801FD550 001FA4B0  7C 63 32 14 */	add r3, r3, r6
/* 801FD554 001FA4B4  1C 63 01 90 */	mulli r3, r3, 0x190
/* 801FD558 001FA4B8  7C 63 28 50 */	subf r3, r3, r5
/* 801FD55C 001FA4BC  2C 03 00 00 */	cmpwi r3, 0
/* 801FD560 001FA4C0  41 82 00 08 */	beq .L_801FD568
/* 801FD564 001FA4C4  38 E0 00 00 */	li r7, 0
.L_801FD568:
/* 801FD568 001FA4C8  2C 07 00 00 */	cmpwi r7, 0
/* 801FD56C 001FA4CC  41 82 00 10 */	beq .L_801FD57C
/* 801FD570 001FA4D0  3C 60 80 2F */	lis r3, LeapYearDays@ha
/* 801FD574 001FA4D4  38 C3 84 18 */	addi r6, r3, LeapYearDays@l
/* 801FD578 001FA4D8  48 00 00 0C */	b .L_801FD584
.L_801FD57C:
/* 801FD57C 001FA4DC  3C 60 80 2F */	lis r3, YearDays@ha
/* 801FD580 001FA4E0  38 C3 83 E8 */	addi r6, r3, YearDays@l
.L_801FD584:
/* 801FD584 001FA4E4  38 E0 00 0C */	li r7, 0xc
/* 801FD588 001FA4E8  38 60 00 30 */	li r3, 0x30
/* 801FD58C 001FA4EC  48 00 00 04 */	b .L_801FD590
.L_801FD590:
/* 801FD590 001FA4F0  48 00 00 04 */	b .L_801FD594
.L_801FD594:
/* 801FD594 001FA4F4  38 63 FF FC */	addi r3, r3, -4
/* 801FD598 001FA4F8  7C A6 18 2E */	lwzx r5, r6, r3
/* 801FD59C 001FA4FC  38 E7 FF FF */	addi r7, r7, -1
/* 801FD5A0 001FA500  7C 00 28 00 */	cmpw r0, r5
/* 801FD5A4 001FA504  41 80 FF F0 */	blt .L_801FD594
/* 801FD5A8 001FA508  90 E4 00 10 */	stw r7, 0x10(r4)
/* 801FD5AC 001FA50C  7C 66 18 2E */	lwzx r3, r6, r3
/* 801FD5B0 001FA510  7C 63 00 50 */	subf r3, r3, r0
/* 801FD5B4 001FA514  38 03 00 01 */	addi r0, r3, 1
/* 801FD5B8 001FA518  90 04 00 0C */	stw r0, 0xc(r4)
/* 801FD5BC 001FA51C  4E 80 00 20 */	blr 
.endfn GetDates

.fn OSTicksToCalendarTime, global
/* 801FD5C0 001FA520  7C 08 02 A6 */	mflr r0
/* 801FD5C4 001FA524  90 01 00 04 */	stw r0, 4(r1)
/* 801FD5C8 001FA528  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 801FD5CC 001FA52C  BF 21 00 1C */	stmw r25, 0x1c(r1)
/* 801FD5D0 001FA530  7C 7D 1B 78 */	mr r29, r3
/* 801FD5D4 001FA534  7C 9E 23 78 */	mr r30, r4
/* 801FD5D8 001FA538  7C BF 2B 78 */	mr r31, r5
/* 801FD5DC 001FA53C  3F 60 80 00 */	lis r27, 0x800000F8@ha
/* 801FD5E0 001FA540  80 1B 00 F8 */	lwz r0, 0x800000F8@l(r27)
/* 801FD5E4 001FA544  7F A3 EB 78 */	mr r3, r29
/* 801FD5E8 001FA548  7F C4 F3 78 */	mr r4, r30
/* 801FD5EC 001FA54C  54 06 F0 BE */	srwi r6, r0, 2
/* 801FD5F0 001FA550  38 A0 00 00 */	li r5, 0
/* 801FD5F4 001FA554  48 01 7B D1 */	bl __mod2i
/* 801FD5F8 001FA558  7C 7A 1B 78 */	mr r26, r3
/* 801FD5FC 001FA55C  38 A0 00 00 */	li r5, 0
/* 801FD600 001FA560  7C 99 23 78 */	mr r25, r4
/* 801FD604 001FA564  6F 44 80 00 */	xoris r4, r26, 0x8000
/* 801FD608 001FA568  6C A3 80 00 */	xoris r3, r5, 0x8000
/* 801FD60C 001FA56C  7C 05 C8 10 */	subfc r0, r5, r25
/* 801FD610 001FA570  7C 63 21 10 */	subfe r3, r3, r4
/* 801FD614 001FA574  7C 64 21 10 */	subfe r3, r4, r4
/* 801FD618 001FA578  7C 63 00 D0 */	neg r3, r3
/* 801FD61C 001FA57C  2C 03 00 00 */	cmpwi r3, 0
/* 801FD620 001FA580  41 82 00 14 */	beq .L_801FD634
/* 801FD624 001FA584  80 1B 00 F8 */	lwz r0, 0xf8(r27)
/* 801FD628 001FA588  54 00 F0 BE */	srwi r0, r0, 2
/* 801FD62C 001FA58C  7F 39 00 14 */	addc r25, r25, r0
/* 801FD630 001FA590  7F 5A 29 14 */	adde r26, r26, r5
.L_801FD634:
/* 801FD634 001FA594  38 80 00 08 */	li r4, 8
/* 801FD638 001FA598  7C 7A 21 D6 */	mullw r3, r26, r4
/* 801FD63C 001FA59C  7C 19 20 16 */	mulhwu r0, r25, r4
/* 801FD640 001FA5A0  3F 60 80 00 */	lis r27, 0x800000F8@ha
/* 801FD644 001FA5A4  80 DB 00 F8 */	lwz r6, 0x800000F8@l(r27)
/* 801FD648 001FA5A8  3C A0 43 1C */	lis r5, 0x431BDE83@ha
/* 801FD64C 001FA5AC  38 A5 DE 83 */	addi r5, r5, 0x431BDE83@l
/* 801FD650 001FA5B0  54 C6 F0 BE */	srwi r6, r6, 2
/* 801FD654 001FA5B4  7C A5 30 16 */	mulhwu r5, r5, r6
/* 801FD658 001FA5B8  54 A6 8B FE */	srwi r6, r5, 0xf
/* 801FD65C 001FA5BC  3B 80 00 00 */	li r28, 0
/* 801FD660 001FA5C0  7C 63 02 14 */	add r3, r3, r0
/* 801FD664 001FA5C4  7C 19 E1 D6 */	mullw r0, r25, r28
/* 801FD668 001FA5C8  7C 99 21 D6 */	mullw r4, r25, r4
/* 801FD66C 001FA5CC  7C 63 02 14 */	add r3, r3, r0
/* 801FD670 001FA5D0  38 A0 00 00 */	li r5, 0
/* 801FD674 001FA5D4  48 01 79 35 */	bl __div2i
/* 801FD678 001FA5D8  38 A0 00 00 */	li r5, 0
/* 801FD67C 001FA5DC  38 C0 03 E8 */	li r6, 0x3e8
/* 801FD680 001FA5E0  48 01 7B 45 */	bl __mod2i
/* 801FD684 001FA5E4  90 9F 00 24 */	stw r4, 0x24(r31)
/* 801FD688 001FA5E8  3C 60 10 62 */	lis r3, 0x10624DD3@ha
/* 801FD68C 001FA5EC  38 A3 4D D3 */	addi r5, r3, 0x10624DD3@l
/* 801FD690 001FA5F0  80 1B 00 F8 */	lwz r0, 0xf8(r27)
/* 801FD694 001FA5F4  7F 43 D3 78 */	mr r3, r26
/* 801FD698 001FA5F8  7F 24 CB 78 */	mr r4, r25
/* 801FD69C 001FA5FC  54 00 F0 BE */	srwi r0, r0, 2
/* 801FD6A0 001FA600  7C 05 00 16 */	mulhwu r0, r5, r0
/* 801FD6A4 001FA604  54 06 D1 BE */	srwi r6, r0, 6
/* 801FD6A8 001FA608  38 A0 00 00 */	li r5, 0
/* 801FD6AC 001FA60C  48 01 78 FD */	bl __div2i
/* 801FD6B0 001FA610  38 A0 00 00 */	li r5, 0
/* 801FD6B4 001FA614  38 C0 03 E8 */	li r6, 0x3e8
/* 801FD6B8 001FA618  48 01 7B 0D */	bl __mod2i
/* 801FD6BC 001FA61C  90 9F 00 20 */	stw r4, 0x20(r31)
/* 801FD6C0 001FA620  7F D9 F0 10 */	subfc r30, r25, r30
/* 801FD6C4 001FA624  7F BA E9 10 */	subfe r29, r26, r29
/* 801FD6C8 001FA628  80 1B 00 F8 */	lwz r0, 0xf8(r27)
/* 801FD6CC 001FA62C  3C A0 00 01 */	lis r5, 0x00015180@ha
/* 801FD6D0 001FA630  3B 25 51 80 */	addi r25, r5, 0x00015180@l
/* 801FD6D4 001FA634  7F A3 EB 78 */	mr r3, r29
/* 801FD6D8 001FA638  54 06 F0 BE */	srwi r6, r0, 2
/* 801FD6DC 001FA63C  7F C4 F3 78 */	mr r4, r30
/* 801FD6E0 001FA640  38 A0 00 00 */	li r5, 0
/* 801FD6E4 001FA644  48 01 78 C5 */	bl __div2i
/* 801FD6E8 001FA648  7F 26 CB 78 */	mr r6, r25
/* 801FD6EC 001FA64C  38 A0 00 00 */	li r5, 0
/* 801FD6F0 001FA650  48 01 78 B9 */	bl __div2i
/* 801FD6F4 001FA654  3C A0 00 0B */	lis r5, 0x000B2575@ha
/* 801FD6F8 001FA658  80 1B 00 F8 */	lwz r0, 0xf8(r27)
/* 801FD6FC 001FA65C  38 A5 25 75 */	addi r5, r5, 0x000B2575@l
/* 801FD700 001FA660  7F 44 28 14 */	addc r26, r4, r5
/* 801FD704 001FA664  54 06 F0 BE */	srwi r6, r0, 2
/* 801FD708 001FA668  7C 03 E1 14 */	adde r0, r3, r28
/* 801FD70C 001FA66C  7F A3 EB 78 */	mr r3, r29
/* 801FD710 001FA670  7F C4 F3 78 */	mr r4, r30
/* 801FD714 001FA674  38 A0 00 00 */	li r5, 0
/* 801FD718 001FA678  48 01 78 91 */	bl __div2i
/* 801FD71C 001FA67C  7F 26 CB 78 */	mr r6, r25
/* 801FD720 001FA680  38 A0 00 00 */	li r5, 0
/* 801FD724 001FA684  48 01 7A A1 */	bl __mod2i
/* 801FD728 001FA688  7C 9B 23 78 */	mr r27, r4
/* 801FD72C 001FA68C  2C 1B 00 00 */	cmpwi r27, 0
/* 801FD730 001FA690  40 80 00 10 */	bge .L_801FD740
/* 801FD734 001FA694  3F 7B 00 01 */	addis r27, r27, 1
/* 801FD738 001FA698  3B 5A FF FF */	addi r26, r26, -1
/* 801FD73C 001FA69C  3B 7B 51 80 */	addi r27, r27, 0x5180
.L_801FD740:
/* 801FD740 001FA6A0  7F 43 D3 78 */	mr r3, r26
/* 801FD744 001FA6A4  7F E4 FB 78 */	mr r4, r31
/* 801FD748 001FA6A8  4B FF FC DD */	bl GetDates
/* 801FD74C 001FA6AC  3C 60 88 89 */	lis r3, 0x88888889@ha
/* 801FD750 001FA6B0  38 A3 88 89 */	addi r5, r3, 0x88888889@l
/* 801FD754 001FA6B4  7C 05 D8 96 */	mulhw r0, r5, r27
/* 801FD758 001FA6B8  7C 80 DA 14 */	add r4, r0, r27
/* 801FD75C 001FA6BC  7C 80 2E 70 */	srawi r0, r4, 5
/* 801FD760 001FA6C0  54 03 0F FE */	srwi r3, r0, 0x1f
/* 801FD764 001FA6C4  7C E0 1A 14 */	add r7, r0, r3
/* 801FD768 001FA6C8  7C 05 38 96 */	mulhw r0, r5, r7
/* 801FD76C 001FA6CC  7C 00 3A 14 */	add r0, r0, r7
/* 801FD770 001FA6D0  7C 05 2E 70 */	srawi r5, r0, 5
/* 801FD774 001FA6D4  7C 00 2E 70 */	srawi r0, r0, 5
/* 801FD778 001FA6D8  54 03 0F FE */	srwi r3, r0, 0x1f
/* 801FD77C 001FA6DC  7C 60 1A 14 */	add r3, r0, r3
/* 801FD780 001FA6E0  7C 80 2E 70 */	srawi r0, r4, 5
/* 801FD784 001FA6E4  54 A6 0F FE */	srwi r6, r5, 0x1f
/* 801FD788 001FA6E8  1C 83 00 3C */	mulli r4, r3, 0x3c
/* 801FD78C 001FA6EC  54 03 0F FE */	srwi r3, r0, 0x1f
/* 801FD790 001FA6F0  7C A5 32 14 */	add r5, r5, r6
/* 801FD794 001FA6F4  7C 00 1A 14 */	add r0, r0, r3
/* 801FD798 001FA6F8  90 BF 00 08 */	stw r5, 8(r31)
/* 801FD79C 001FA6FC  1C 00 00 3C */	mulli r0, r0, 0x3c
/* 801FD7A0 001FA700  7C 64 38 50 */	subf r3, r4, r7
/* 801FD7A4 001FA704  90 7F 00 04 */	stw r3, 4(r31)
/* 801FD7A8 001FA708  7C 00 D8 50 */	subf r0, r0, r27
/* 801FD7AC 001FA70C  90 1F 00 00 */	stw r0, 0(r31)
/* 801FD7B0 001FA710  BB 21 00 1C */	lmw r25, 0x1c(r1)
/* 801FD7B4 001FA714  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801FD7B8 001FA718  38 21 00 38 */	addi r1, r1, 0x38
/* 801FD7BC 001FA71C  7C 08 03 A6 */	mtlr r0
/* 801FD7C0 001FA720  4E 80 00 20 */	blr 
.endfn OSTicksToCalendarTime

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 8
.obj YearDays, local
	.4byte 0x00000000
	.4byte 0x0000001F
	.4byte 0x0000003B
	.4byte 0x0000005A
	.4byte 0x00000078
	.4byte 0x00000097
	.4byte 0x000000B5
	.4byte 0x000000D4
	.4byte 0x000000F3
	.4byte 0x00000111
	.4byte 0x00000130
	.4byte 0x0000014E
.endobj YearDays
.obj LeapYearDays, local
	.4byte 0x00000000
	.4byte 0x0000001F
	.4byte 0x0000003C
	.4byte 0x0000005B
	.4byte 0x00000079
	.4byte 0x00000098
	.4byte 0x000000B6
	.4byte 0x000000D5
	.4byte 0x000000F4
	.4byte 0x00000112
	.4byte 0x00000131
	.4byte 0x0000014F
.endobj LeapYearDays
