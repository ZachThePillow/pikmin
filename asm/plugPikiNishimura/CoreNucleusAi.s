.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.fn __ct__13CoreNucleusAiFP11CoreNucleus, global
/* 8017AD44 00177CA4  3C A0 80 2B */	lis r5, __vt__19PaniAnimKeyListener@ha
/* 8017AD48 00177CA8  38 05 DB 94 */	addi r0, r5, __vt__19PaniAnimKeyListener@l
/* 8017AD4C 00177CAC  3C A0 80 2D */	lis r5, __vt__13CoreNucleusAi@ha
/* 8017AD50 00177CB0  90 03 00 00 */	stw r0, 0(r3)
/* 8017AD54 00177CB4  38 05 15 DC */	addi r0, r5, __vt__13CoreNucleusAi@l
/* 8017AD58 00177CB8  90 03 00 00 */	stw r0, 0(r3)
/* 8017AD5C 00177CBC  90 83 00 08 */	stw r4, 8(r3)
/* 8017AD60 00177CC0  4E 80 00 20 */	blr 
.endfn __ct__13CoreNucleusAiFP11CoreNucleus

.fn initAI__13CoreNucleusAiFP11CoreNucleus, global
/* 8017AD64 00177CC4  7C 08 02 A6 */	mflr r0
/* 8017AD68 00177CC8  90 01 00 04 */	stw r0, 4(r1)
/* 8017AD6C 00177CCC  38 00 00 02 */	li r0, 2
/* 8017AD70 00177CD0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8017AD74 00177CD4  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8017AD78 00177CD8  7C 7F 1B 78 */	mr r31, r3
/* 8017AD7C 00177CDC  38 BF 00 00 */	addi r5, r31, 0
/* 8017AD80 00177CE0  90 83 00 08 */	stw r4, 8(r3)
/* 8017AD84 00177CE4  38 80 00 02 */	li r4, 2
/* 8017AD88 00177CE8  80 C3 00 08 */	lwz r6, 8(r3)
/* 8017AD8C 00177CEC  38 61 00 1C */	addi r3, r1, 0x1c
/* 8017AD90 00177CF0  90 06 02 E4 */	stw r0, 0x2e4(r6)
/* 8017AD94 00177CF4  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017AD98 00177CF8  90 06 02 E8 */	stw r0, 0x2e8(r6)
/* 8017AD9C 00177CFC  4B FA 41 F1 */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 8017ADA0 00177D00  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017ADA4 00177D04  38 83 00 00 */	addi r4, r3, 0
/* 8017ADA8 00177D08  38 65 03 3C */	addi r3, r5, 0x33c
/* 8017ADAC 00177D0C  4B FA 44 15 */	bl startMotion__12PaniAnimatorFR14PaniMotionInfo
/* 8017ADB0 00177D10  C0 02 AE 80 */	lfs f0, lbl_803EB080@sda21(r2)
/* 8017ADB4 00177D14  38 00 00 00 */	li r0, 0
/* 8017ADB8 00177D18  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017ADBC 00177D1C  D0 03 02 D8 */	stfs f0, 0x2d8(r3)
/* 8017ADC0 00177D20  98 1F 00 04 */	stb r0, 4(r31)
/* 8017ADC4 00177D24  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8017ADC8 00177D28  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8017ADCC 00177D2C  38 21 00 30 */	addi r1, r1, 0x30
/* 8017ADD0 00177D30  7C 08 03 A6 */	mtlr r0
/* 8017ADD4 00177D34  4E 80 00 20 */	blr 
.endfn initAI__13CoreNucleusAiFP11CoreNucleus

.fn animationKeyUpdated__13CoreNucleusAiFR16PaniAnimKeyEvent, global
/* 8017ADD8 00177D38  7C 08 02 A6 */	mflr r0
/* 8017ADDC 00177D3C  90 01 00 04 */	stw r0, 4(r1)
/* 8017ADE0 00177D40  94 21 FF F8 */	stwu r1, -8(r1)
/* 8017ADE4 00177D44  80 04 00 00 */	lwz r0, 0(r4)
/* 8017ADE8 00177D48  2C 00 00 02 */	cmpwi r0, 2
/* 8017ADEC 00177D4C  41 82 00 38 */	beq .L_8017AE24
/* 8017ADF0 00177D50  40 80 00 14 */	bge .L_8017AE04
/* 8017ADF4 00177D54  2C 00 00 00 */	cmpwi r0, 0
/* 8017ADF8 00177D58  41 82 00 3C */	beq .L_8017AE34
/* 8017ADFC 00177D5C  40 80 00 20 */	bge .L_8017AE1C
/* 8017AE00 00177D60  48 00 00 44 */	b .L_8017AE44
.L_8017AE04:
/* 8017AE04 00177D64  2C 00 00 07 */	cmpwi r0, 7
/* 8017AE08 00177D68  41 82 00 34 */	beq .L_8017AE3C
/* 8017AE0C 00177D6C  40 80 00 38 */	bge .L_8017AE44
/* 8017AE10 00177D70  2C 00 00 06 */	cmpwi r0, 6
/* 8017AE14 00177D74  40 80 00 18 */	bge .L_8017AE2C
/* 8017AE18 00177D78  48 00 00 2C */	b .L_8017AE44
.L_8017AE1C:
/* 8017AE1C 00177D7C  48 00 00 39 */	bl keyAction0__13CoreNucleusAiFv
/* 8017AE20 00177D80  48 00 00 24 */	b .L_8017AE44
.L_8017AE24:
/* 8017AE24 00177D84  48 00 00 35 */	bl keyAction1__13CoreNucleusAiFv
/* 8017AE28 00177D88  48 00 00 1C */	b .L_8017AE44
.L_8017AE2C:
/* 8017AE2C 00177D8C  48 00 00 31 */	bl keyLoopEnd__13CoreNucleusAiFv
/* 8017AE30 00177D90  48 00 00 14 */	b .L_8017AE44
.L_8017AE34:
/* 8017AE34 00177D94  48 00 00 3D */	bl keyFinished__13CoreNucleusAiFv
/* 8017AE38 00177D98  48 00 00 0C */	b .L_8017AE44
.L_8017AE3C:
/* 8017AE3C 00177D9C  80 84 00 04 */	lwz r4, 4(r4)
/* 8017AE40 00177DA0  48 00 00 41 */	bl playSound__13CoreNucleusAiFi
.L_8017AE44:
/* 8017AE44 00177DA4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8017AE48 00177DA8  38 21 00 08 */	addi r1, r1, 8
/* 8017AE4C 00177DAC  7C 08 03 A6 */	mtlr r0
/* 8017AE50 00177DB0  4E 80 00 20 */	blr 
.endfn animationKeyUpdated__13CoreNucleusAiFR16PaniAnimKeyEvent

.fn keyAction0__13CoreNucleusAiFv, global
/* 8017AE54 00177DB4  4E 80 00 20 */	blr 
.endfn keyAction0__13CoreNucleusAiFv

.fn keyAction1__13CoreNucleusAiFv, global
/* 8017AE58 00177DB8  4E 80 00 20 */	blr 
.endfn keyAction1__13CoreNucleusAiFv

.fn keyLoopEnd__13CoreNucleusAiFv, global
/* 8017AE5C 00177DBC  80 83 00 08 */	lwz r4, 8(r3)
/* 8017AE60 00177DC0  80 64 02 EC */	lwz r3, 0x2ec(r4)
/* 8017AE64 00177DC4  38 03 00 01 */	addi r0, r3, 1
/* 8017AE68 00177DC8  90 04 02 EC */	stw r0, 0x2ec(r4)
/* 8017AE6C 00177DCC  4E 80 00 20 */	blr 
.endfn keyLoopEnd__13CoreNucleusAiFv

.fn keyFinished__13CoreNucleusAiFv, global
/* 8017AE70 00177DD0  80 63 00 08 */	lwz r3, 8(r3)
/* 8017AE74 00177DD4  38 00 00 01 */	li r0, 1
/* 8017AE78 00177DD8  98 03 02 BD */	stb r0, 0x2bd(r3)
/* 8017AE7C 00177DDC  4E 80 00 20 */	blr 
.endfn keyFinished__13CoreNucleusAiFv

.fn playSound__13CoreNucleusAiFi, global
/* 8017AE80 00177DE0  4E 80 00 20 */	blr 
.endfn playSound__13CoreNucleusAiFi

.fn setHitMotionStart__13CoreNucleusAiFv, global
/* 8017AE84 00177DE4  38 00 00 01 */	li r0, 1
/* 8017AE88 00177DE8  98 03 00 04 */	stb r0, 4(r3)
/* 8017AE8C 00177DEC  4E 80 00 20 */	blr 
.endfn setHitMotionStart__13CoreNucleusAiFv

.fn update__13CoreNucleusAiFv, global
/* 8017AE90 00177DF0  7C 08 02 A6 */	mflr r0
/* 8017AE94 00177DF4  90 01 00 04 */	stw r0, 4(r1)
/* 8017AE98 00177DF8  94 21 FE F0 */	stwu r1, -0x110(r1)
/* 8017AE9C 00177DFC  DB E1 01 08 */	stfd f31, 0x108(r1)
/* 8017AEA0 00177E00  93 E1 01 04 */	stw r31, 0x104(r1)
/* 8017AEA4 00177E04  7C 7F 1B 78 */	mr r31, r3
/* 8017AEA8 00177E08  93 C1 01 00 */	stw r30, 0x100(r1)
/* 8017AEAC 00177E0C  80 83 00 08 */	lwz r4, 8(r3)
/* 8017AEB0 00177E10  80 64 03 BC */	lwz r3, 0x3bc(r4)
/* 8017AEB4 00177E14  C0 03 03 E8 */	lfs f0, 0x3e8(r3)
/* 8017AEB8 00177E18  D0 04 00 94 */	stfs f0, 0x94(r4)
/* 8017AEBC 00177E1C  80 9F 00 08 */	lwz r4, 8(r31)
/* 8017AEC0 00177E20  80 64 03 BC */	lwz r3, 0x3bc(r4)
/* 8017AEC4 00177E24  C0 03 03 F0 */	lfs f0, 0x3f0(r3)
/* 8017AEC8 00177E28  D0 04 00 9C */	stfs f0, 0x9c(r4)
/* 8017AECC 00177E2C  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017AED0 00177E30  C0 23 02 C0 */	lfs f1, 0x2c0(r3)
/* 8017AED4 00177E34  80 63 03 BC */	lwz r3, 0x3bc(r3)
/* 8017AED8 00177E38  80 63 04 00 */	lwz r3, 0x400(r3)
/* 8017AEDC 00177E3C  4B FE 9D 55 */	bl addDamagePoint__7SlimeAiFf
/* 8017AEE0 00177E40  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017AEE4 00177E44  80 03 02 E4 */	lwz r0, 0x2e4(r3)
/* 8017AEE8 00177E48  2C 00 00 02 */	cmpwi r0, 2
/* 8017AEEC 00177E4C  41 82 01 E0 */	beq .L_8017B0CC
/* 8017AEF0 00177E50  40 80 00 14 */	bge .L_8017AF04
/* 8017AEF4 00177E54  2C 00 00 00 */	cmpwi r0, 0
/* 8017AEF8 00177E58  41 82 04 B4 */	beq .L_8017B3AC
/* 8017AEFC 00177E5C  40 80 00 14 */	bge .L_8017AF10
/* 8017AF00 00177E60  48 00 04 AC */	b .L_8017B3AC
.L_8017AF04:
/* 8017AF04 00177E64  2C 00 00 04 */	cmpwi r0, 4
/* 8017AF08 00177E68  40 80 04 A4 */	bge .L_8017B3AC
/* 8017AF0C 00177E6C  48 00 03 94 */	b .L_8017B2A0
.L_8017AF10:
/* 8017AF10 00177E70  C0 23 02 C4 */	lfs f1, 0x2c4(r3)
/* 8017AF14 00177E74  C0 02 AE 84 */	lfs f0, lbl_803EB084@sda21(r2)
/* 8017AF18 00177E78  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8017AF1C 00177E7C  7C 00 00 26 */	mfcr r0
/* 8017AF20 00177E80  54 00 17 FF */	rlwinm. r0, r0, 2, 0x1f, 0x1f
/* 8017AF24 00177E84  40 82 00 B4 */	bne .L_8017AFD8
/* 8017AF28 00177E88  38 00 00 00 */	li r0, 0
/* 8017AF2C 00177E8C  90 03 02 E8 */	stw r0, 0x2e8(r3)
/* 8017AF30 00177E90  38 BF 00 00 */	addi r5, r31, 0
/* 8017AF34 00177E94  38 61 00 F4 */	addi r3, r1, 0xf4
/* 8017AF38 00177E98  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017AF3C 00177E9C  38 80 00 01 */	li r4, 1
/* 8017AF40 00177EA0  98 06 02 BD */	stb r0, 0x2bd(r6)
/* 8017AF44 00177EA4  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017AF48 00177EA8  90 06 02 EC */	stw r0, 0x2ec(r6)
/* 8017AF4C 00177EAC  4B FA 40 41 */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 8017AF50 00177EB0  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017AF54 00177EB4  38 83 00 00 */	addi r4, r3, 0
/* 8017AF58 00177EB8  38 65 03 3C */	addi r3, r5, 0x33c
/* 8017AF5C 00177EBC  4B FA 42 65 */	bl startMotion__12PaniAnimatorFR14PaniMotionInfo
/* 8017AF60 00177EC0  C0 02 AE 84 */	lfs f0, lbl_803EB084@sda21(r2)
/* 8017AF64 00177EC4  38 80 00 39 */	li r4, 0x39
/* 8017AF68 00177EC8  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017AF6C 00177ECC  38 C0 00 00 */	li r6, 0
/* 8017AF70 00177ED0  38 E0 00 00 */	li r7, 0
/* 8017AF74 00177ED4  D0 03 02 D4 */	stfs f0, 0x2d4(r3)
/* 8017AF78 00177ED8  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017AF7C 00177EDC  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8017AF80 00177EE0  38 A5 00 94 */	addi r5, r5, 0x94
/* 8017AF84 00177EE4  48 02 1B B5 */	bl "create__9EffectMgrFQ29EffectMgr12effTypeTableR8Vector3fPQ23zen37CallBack1<PQ23zen17particleGenerator>PQ23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"
/* 8017AF88 00177EE8  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017AF8C 00177EEC  38 80 00 38 */	li r4, 0x38
/* 8017AF90 00177EF0  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8017AF94 00177EF4  38 C0 00 00 */	li r6, 0
/* 8017AF98 00177EF8  38 A5 00 94 */	addi r5, r5, 0x94
/* 8017AF9C 00177EFC  38 E0 00 00 */	li r7, 0
/* 8017AFA0 00177F00  48 02 1B 99 */	bl "create__9EffectMgrFQ29EffectMgr12effTypeTableR8Vector3fPQ23zen37CallBack1<PQ23zen17particleGenerator>PQ23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"
/* 8017AFA4 00177F04  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017AFA8 00177F08  38 80 00 37 */	li r4, 0x37
/* 8017AFAC 00177F0C  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8017AFB0 00177F10  38 C0 00 00 */	li r6, 0
/* 8017AFB4 00177F14  38 A5 00 94 */	addi r5, r5, 0x94
/* 8017AFB8 00177F18  38 E0 00 00 */	li r7, 0
/* 8017AFBC 00177F1C  48 02 1B 7D */	bl "create__9EffectMgrFQ29EffectMgr12effTypeTableR8Vector3fPQ23zen37CallBack1<PQ23zen17particleGenerator>PQ23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"
/* 8017AFC0 00177F20  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017AFC4 00177F24  81 83 00 00 */	lwz r12, 0(r3)
/* 8017AFC8 00177F28  81 8C 01 0C */	lwz r12, 0x10c(r12)
/* 8017AFCC 00177F2C  7D 88 03 A6 */	mtlr r12
/* 8017AFD0 00177F30  4E 80 00 21 */	blrl 
/* 8017AFD4 00177F34  48 00 03 D8 */	b .L_8017B3AC
.L_8017AFD8:
/* 8017AFD8 00177F38  88 1F 00 04 */	lbz r0, 4(r31)
/* 8017AFDC 00177F3C  28 00 00 00 */	cmplwi r0, 0
/* 8017AFE0 00177F40  41 82 00 A4 */	beq .L_8017B084
/* 8017AFE4 00177F44  38 00 00 03 */	li r0, 3
/* 8017AFE8 00177F48  90 03 02 E8 */	stw r0, 0x2e8(r3)
/* 8017AFEC 00177F4C  38 00 00 00 */	li r0, 0
/* 8017AFF0 00177F50  38 BF 00 00 */	addi r5, r31, 0
/* 8017AFF4 00177F54  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017AFF8 00177F58  38 61 00 EC */	addi r3, r1, 0xec
/* 8017AFFC 00177F5C  38 80 00 0A */	li r4, 0xa
/* 8017B000 00177F60  98 06 02 BD */	stb r0, 0x2bd(r6)
/* 8017B004 00177F64  4B FA 3F 89 */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 8017B008 00177F68  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B00C 00177F6C  38 83 00 00 */	addi r4, r3, 0
/* 8017B010 00177F70  38 65 03 3C */	addi r3, r5, 0x33c
/* 8017B014 00177F74  4B FA 41 AD */	bl startMotion__12PaniAnimatorFR14PaniMotionInfo
/* 8017B018 00177F78  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017B01C 00177F7C  C0 23 00 A0 */	lfs f1, 0xa0(r3)
/* 8017B020 00177F80  48 0A 0B 35 */	bl cosf
/* 8017B024 00177F84  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017B028 00177F88  FF E0 08 90 */	fmr f31, f1
/* 8017B02C 00177F8C  C0 23 00 A0 */	lfs f1, 0xa0(r3)
/* 8017B030 00177F90  48 0A 0C B9 */	bl sinf
/* 8017B034 00177F94  D0 21 00 E0 */	stfs f1, 0xe0(r1)
/* 8017B038 00177F98  38 80 00 59 */	li r4, 0x59
/* 8017B03C 00177F9C  C0 0D 07 D8 */	lfs f0, lbl_803E54F8@sda21(r13)
/* 8017B040 00177FA0  38 C0 00 00 */	li r6, 0
/* 8017B044 00177FA4  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8017B048 00177FA8  D0 01 00 E4 */	stfs f0, 0xe4(r1)
/* 8017B04C 00177FAC  38 E0 00 00 */	li r7, 0
/* 8017B050 00177FB0  D3 E1 00 E8 */	stfs f31, 0xe8(r1)
/* 8017B054 00177FB4  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B058 00177FB8  38 A5 00 94 */	addi r5, r5, 0x94
/* 8017B05C 00177FBC  48 02 1A DD */	bl "create__9EffectMgrFQ29EffectMgr12effTypeTableR8Vector3fPQ23zen37CallBack1<PQ23zen17particleGenerator>PQ23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"
/* 8017B060 00177FC0  28 03 00 00 */	cmplwi r3, 0
/* 8017B064 00177FC4  41 82 03 48 */	beq .L_8017B3AC
/* 8017B068 00177FC8  80 81 00 E0 */	lwz r4, 0xe0(r1)
/* 8017B06C 00177FCC  80 01 00 E4 */	lwz r0, 0xe4(r1)
/* 8017B070 00177FD0  90 83 00 A0 */	stw r4, 0xa0(r3)
/* 8017B074 00177FD4  90 03 00 A4 */	stw r0, 0xa4(r3)
/* 8017B078 00177FD8  80 01 00 E8 */	lwz r0, 0xe8(r1)
/* 8017B07C 00177FDC  90 03 00 A8 */	stw r0, 0xa8(r3)
/* 8017B080 00177FE0  48 00 03 2C */	b .L_8017B3AC
.L_8017B084:
/* 8017B084 00177FE4  88 03 02 BD */	lbz r0, 0x2bd(r3)
/* 8017B088 00177FE8  28 00 00 00 */	cmplwi r0, 0
/* 8017B08C 00177FEC  41 82 03 20 */	beq .L_8017B3AC
/* 8017B090 00177FF0  38 00 00 02 */	li r0, 2
/* 8017B094 00177FF4  90 03 02 E8 */	stw r0, 0x2e8(r3)
/* 8017B098 00177FF8  3B C0 00 00 */	li r30, 0
/* 8017B09C 00177FFC  38 BF 00 00 */	addi r5, r31, 0
/* 8017B0A0 00178000  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017B0A4 00178004  38 61 00 D8 */	addi r3, r1, 0xd8
/* 8017B0A8 00178008  38 80 00 02 */	li r4, 2
/* 8017B0AC 0017800C  9B C6 02 BD */	stb r30, 0x2bd(r6)
/* 8017B0B0 00178010  4B FA 3E DD */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 8017B0B4 00178014  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B0B8 00178018  38 83 00 00 */	addi r4, r3, 0
/* 8017B0BC 0017801C  38 65 03 3C */	addi r3, r5, 0x33c
/* 8017B0C0 00178020  4B FA 41 01 */	bl startMotion__12PaniAnimatorFR14PaniMotionInfo
/* 8017B0C4 00178024  9B DF 00 04 */	stb r30, 4(r31)
/* 8017B0C8 00178028  48 00 02 E4 */	b .L_8017B3AC
.L_8017B0CC:
/* 8017B0CC 0017802C  C0 03 02 C4 */	lfs f0, 0x2c4(r3)
/* 8017B0D0 00178030  C0 22 AE 84 */	lfs f1, lbl_803EB084@sda21(r2)
/* 8017B0D4 00178034  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8017B0D8 00178038  7C 00 00 26 */	mfcr r0
/* 8017B0DC 0017803C  54 00 17 FF */	rlwinm. r0, r0, 2, 0x1f, 0x1f
/* 8017B0E0 00178040  40 82 00 B4 */	bne .L_8017B194
/* 8017B0E4 00178044  38 00 00 00 */	li r0, 0
/* 8017B0E8 00178048  90 03 02 E8 */	stw r0, 0x2e8(r3)
/* 8017B0EC 0017804C  38 BF 00 00 */	addi r5, r31, 0
/* 8017B0F0 00178050  38 61 00 D0 */	addi r3, r1, 0xd0
/* 8017B0F4 00178054  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017B0F8 00178058  38 80 00 01 */	li r4, 1
/* 8017B0FC 0017805C  98 06 02 BD */	stb r0, 0x2bd(r6)
/* 8017B100 00178060  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017B104 00178064  90 06 02 EC */	stw r0, 0x2ec(r6)
/* 8017B108 00178068  4B FA 3E 85 */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 8017B10C 0017806C  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B110 00178070  38 83 00 00 */	addi r4, r3, 0
/* 8017B114 00178074  38 65 03 3C */	addi r3, r5, 0x33c
/* 8017B118 00178078  4B FA 40 A9 */	bl startMotion__12PaniAnimatorFR14PaniMotionInfo
/* 8017B11C 0017807C  C0 02 AE 84 */	lfs f0, lbl_803EB084@sda21(r2)
/* 8017B120 00178080  38 80 00 39 */	li r4, 0x39
/* 8017B124 00178084  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017B128 00178088  38 C0 00 00 */	li r6, 0
/* 8017B12C 0017808C  38 E0 00 00 */	li r7, 0
/* 8017B130 00178090  D0 03 02 D4 */	stfs f0, 0x2d4(r3)
/* 8017B134 00178094  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B138 00178098  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8017B13C 0017809C  38 A5 00 94 */	addi r5, r5, 0x94
/* 8017B140 001780A0  48 02 19 F9 */	bl "create__9EffectMgrFQ29EffectMgr12effTypeTableR8Vector3fPQ23zen37CallBack1<PQ23zen17particleGenerator>PQ23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"
/* 8017B144 001780A4  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B148 001780A8  38 80 00 38 */	li r4, 0x38
/* 8017B14C 001780AC  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8017B150 001780B0  38 C0 00 00 */	li r6, 0
/* 8017B154 001780B4  38 A5 00 94 */	addi r5, r5, 0x94
/* 8017B158 001780B8  38 E0 00 00 */	li r7, 0
/* 8017B15C 001780BC  48 02 19 DD */	bl "create__9EffectMgrFQ29EffectMgr12effTypeTableR8Vector3fPQ23zen37CallBack1<PQ23zen17particleGenerator>PQ23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"
/* 8017B160 001780C0  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B164 001780C4  38 80 00 37 */	li r4, 0x37
/* 8017B168 001780C8  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8017B16C 001780CC  38 C0 00 00 */	li r6, 0
/* 8017B170 001780D0  38 A5 00 94 */	addi r5, r5, 0x94
/* 8017B174 001780D4  38 E0 00 00 */	li r7, 0
/* 8017B178 001780D8  48 02 19 C1 */	bl "create__9EffectMgrFQ29EffectMgr12effTypeTableR8Vector3fPQ23zen37CallBack1<PQ23zen17particleGenerator>PQ23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"
/* 8017B17C 001780DC  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017B180 001780E0  81 83 00 00 */	lwz r12, 0(r3)
/* 8017B184 001780E4  81 8C 01 0C */	lwz r12, 0x10c(r12)
/* 8017B188 001780E8  7D 88 03 A6 */	mtlr r12
/* 8017B18C 001780EC  4E 80 00 21 */	blrl 
/* 8017B190 001780F0  48 00 02 1C */	b .L_8017B3AC
.L_8017B194:
/* 8017B194 001780F4  88 1F 00 04 */	lbz r0, 4(r31)
/* 8017B198 001780F8  28 00 00 00 */	cmplwi r0, 0
/* 8017B19C 001780FC  41 82 00 A4 */	beq .L_8017B240
/* 8017B1A0 00178100  38 00 00 03 */	li r0, 3
/* 8017B1A4 00178104  90 03 02 E8 */	stw r0, 0x2e8(r3)
/* 8017B1A8 00178108  38 00 00 00 */	li r0, 0
/* 8017B1AC 0017810C  38 BF 00 00 */	addi r5, r31, 0
/* 8017B1B0 00178110  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017B1B4 00178114  38 61 00 C8 */	addi r3, r1, 0xc8
/* 8017B1B8 00178118  38 80 00 0A */	li r4, 0xa
/* 8017B1BC 0017811C  98 06 02 BD */	stb r0, 0x2bd(r6)
/* 8017B1C0 00178120  4B FA 3D CD */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 8017B1C4 00178124  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B1C8 00178128  38 83 00 00 */	addi r4, r3, 0
/* 8017B1CC 0017812C  38 65 03 3C */	addi r3, r5, 0x33c
/* 8017B1D0 00178130  4B FA 3F F1 */	bl startMotion__12PaniAnimatorFR14PaniMotionInfo
/* 8017B1D4 00178134  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017B1D8 00178138  C0 23 00 A0 */	lfs f1, 0xa0(r3)
/* 8017B1DC 0017813C  48 0A 09 79 */	bl cosf
/* 8017B1E0 00178140  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017B1E4 00178144  FF E0 08 90 */	fmr f31, f1
/* 8017B1E8 00178148  C0 23 00 A0 */	lfs f1, 0xa0(r3)
/* 8017B1EC 0017814C  48 0A 0A FD */	bl sinf
/* 8017B1F0 00178150  D0 21 00 BC */	stfs f1, 0xbc(r1)
/* 8017B1F4 00178154  38 80 00 59 */	li r4, 0x59
/* 8017B1F8 00178158  C0 0D 07 D8 */	lfs f0, lbl_803E54F8@sda21(r13)
/* 8017B1FC 0017815C  38 C0 00 00 */	li r6, 0
/* 8017B200 00178160  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8017B204 00178164  D0 01 00 C0 */	stfs f0, 0xc0(r1)
/* 8017B208 00178168  38 E0 00 00 */	li r7, 0
/* 8017B20C 0017816C  D3 E1 00 C4 */	stfs f31, 0xc4(r1)
/* 8017B210 00178170  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B214 00178174  38 A5 00 94 */	addi r5, r5, 0x94
/* 8017B218 00178178  48 02 19 21 */	bl "create__9EffectMgrFQ29EffectMgr12effTypeTableR8Vector3fPQ23zen37CallBack1<PQ23zen17particleGenerator>PQ23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"
/* 8017B21C 0017817C  28 03 00 00 */	cmplwi r3, 0
/* 8017B220 00178180  41 82 01 8C */	beq .L_8017B3AC
/* 8017B224 00178184  80 81 00 BC */	lwz r4, 0xbc(r1)
/* 8017B228 00178188  80 01 00 C0 */	lwz r0, 0xc0(r1)
/* 8017B22C 0017818C  90 83 00 A0 */	stw r4, 0xa0(r3)
/* 8017B230 00178190  90 03 00 A4 */	stw r0, 0xa4(r3)
/* 8017B234 00178194  80 01 00 C4 */	lwz r0, 0xc4(r1)
/* 8017B238 00178198  90 03 00 A8 */	stw r0, 0xa8(r3)
/* 8017B23C 0017819C  48 00 01 70 */	b .L_8017B3AC
.L_8017B240:
/* 8017B240 001781A0  C0 03 02 C0 */	lfs f0, 0x2c0(r3)
/* 8017B244 001781A4  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8017B248 001781A8  40 81 00 0C */	ble .L_8017B254
/* 8017B24C 001781AC  38 00 00 01 */	li r0, 1
/* 8017B250 001781B0  48 00 00 08 */	b .L_8017B258
.L_8017B254:
/* 8017B254 001781B4  38 00 00 00 */	li r0, 0
.L_8017B258:
/* 8017B258 001781B8  54 00 06 3F */	clrlwi. r0, r0, 0x18
/* 8017B25C 001781BC  41 82 01 50 */	beq .L_8017B3AC
/* 8017B260 001781C0  38 00 00 01 */	li r0, 1
/* 8017B264 001781C4  90 03 02 E8 */	stw r0, 0x2e8(r3)
/* 8017B268 001781C8  38 00 00 00 */	li r0, 0
/* 8017B26C 001781CC  38 BF 00 00 */	addi r5, r31, 0
/* 8017B270 001781D0  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017B274 001781D4  38 61 00 B4 */	addi r3, r1, 0xb4
/* 8017B278 001781D8  38 80 00 01 */	li r4, 1
/* 8017B27C 001781DC  98 06 02 BD */	stb r0, 0x2bd(r6)
/* 8017B280 001781E0  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017B284 001781E4  90 06 02 EC */	stw r0, 0x2ec(r6)
/* 8017B288 001781E8  4B FA 3D 05 */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 8017B28C 001781EC  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B290 001781F0  38 83 00 00 */	addi r4, r3, 0
/* 8017B294 001781F4  38 65 03 3C */	addi r3, r5, 0x33c
/* 8017B298 001781F8  4B FA 3F 29 */	bl startMotion__12PaniAnimatorFR14PaniMotionInfo
/* 8017B29C 001781FC  48 00 01 10 */	b .L_8017B3AC
.L_8017B2A0:
/* 8017B2A0 00178200  C0 23 02 C4 */	lfs f1, 0x2c4(r3)
/* 8017B2A4 00178204  C0 02 AE 84 */	lfs f0, lbl_803EB084@sda21(r2)
/* 8017B2A8 00178208  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8017B2AC 0017820C  7C 00 00 26 */	mfcr r0
/* 8017B2B0 00178210  54 00 17 FF */	rlwinm. r0, r0, 2, 0x1f, 0x1f
/* 8017B2B4 00178214  40 82 00 B4 */	bne .L_8017B368
/* 8017B2B8 00178218  38 00 00 00 */	li r0, 0
/* 8017B2BC 0017821C  90 03 02 E8 */	stw r0, 0x2e8(r3)
/* 8017B2C0 00178220  38 BF 00 00 */	addi r5, r31, 0
/* 8017B2C4 00178224  38 61 00 AC */	addi r3, r1, 0xac
/* 8017B2C8 00178228  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017B2CC 0017822C  38 80 00 01 */	li r4, 1
/* 8017B2D0 00178230  98 06 02 BD */	stb r0, 0x2bd(r6)
/* 8017B2D4 00178234  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017B2D8 00178238  90 06 02 EC */	stw r0, 0x2ec(r6)
/* 8017B2DC 0017823C  4B FA 3C B1 */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 8017B2E0 00178240  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B2E4 00178244  38 83 00 00 */	addi r4, r3, 0
/* 8017B2E8 00178248  38 65 03 3C */	addi r3, r5, 0x33c
/* 8017B2EC 0017824C  4B FA 3E D5 */	bl startMotion__12PaniAnimatorFR14PaniMotionInfo
/* 8017B2F0 00178250  C0 02 AE 84 */	lfs f0, lbl_803EB084@sda21(r2)
/* 8017B2F4 00178254  38 80 00 39 */	li r4, 0x39
/* 8017B2F8 00178258  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017B2FC 0017825C  38 C0 00 00 */	li r6, 0
/* 8017B300 00178260  38 E0 00 00 */	li r7, 0
/* 8017B304 00178264  D0 03 02 D4 */	stfs f0, 0x2d4(r3)
/* 8017B308 00178268  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B30C 0017826C  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8017B310 00178270  38 A5 00 94 */	addi r5, r5, 0x94
/* 8017B314 00178274  48 02 18 25 */	bl "create__9EffectMgrFQ29EffectMgr12effTypeTableR8Vector3fPQ23zen37CallBack1<PQ23zen17particleGenerator>PQ23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"
/* 8017B318 00178278  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B31C 0017827C  38 80 00 38 */	li r4, 0x38
/* 8017B320 00178280  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8017B324 00178284  38 C0 00 00 */	li r6, 0
/* 8017B328 00178288  38 A5 00 94 */	addi r5, r5, 0x94
/* 8017B32C 0017828C  38 E0 00 00 */	li r7, 0
/* 8017B330 00178290  48 02 18 09 */	bl "create__9EffectMgrFQ29EffectMgr12effTypeTableR8Vector3fPQ23zen37CallBack1<PQ23zen17particleGenerator>PQ23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"
/* 8017B334 00178294  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B338 00178298  38 80 00 37 */	li r4, 0x37
/* 8017B33C 0017829C  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8017B340 001782A0  38 C0 00 00 */	li r6, 0
/* 8017B344 001782A4  38 A5 00 94 */	addi r5, r5, 0x94
/* 8017B348 001782A8  38 E0 00 00 */	li r7, 0
/* 8017B34C 001782AC  48 02 17 ED */	bl "create__9EffectMgrFQ29EffectMgr12effTypeTableR8Vector3fPQ23zen37CallBack1<PQ23zen17particleGenerator>PQ23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"
/* 8017B350 001782B0  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017B354 001782B4  81 83 00 00 */	lwz r12, 0(r3)
/* 8017B358 001782B8  81 8C 01 0C */	lwz r12, 0x10c(r12)
/* 8017B35C 001782BC  7D 88 03 A6 */	mtlr r12
/* 8017B360 001782C0  4E 80 00 21 */	blrl 
/* 8017B364 001782C4  48 00 00 48 */	b .L_8017B3AC
.L_8017B368:
/* 8017B368 001782C8  88 03 02 BD */	lbz r0, 0x2bd(r3)
/* 8017B36C 001782CC  28 00 00 00 */	cmplwi r0, 0
/* 8017B370 001782D0  41 82 00 3C */	beq .L_8017B3AC
/* 8017B374 001782D4  38 00 00 02 */	li r0, 2
/* 8017B378 001782D8  90 03 02 E8 */	stw r0, 0x2e8(r3)
/* 8017B37C 001782DC  3B C0 00 00 */	li r30, 0
/* 8017B380 001782E0  38 BF 00 00 */	addi r5, r31, 0
/* 8017B384 001782E4  80 DF 00 08 */	lwz r6, 8(r31)
/* 8017B388 001782E8  38 61 00 A4 */	addi r3, r1, 0xa4
/* 8017B38C 001782EC  38 80 00 02 */	li r4, 2
/* 8017B390 001782F0  9B C6 02 BD */	stb r30, 0x2bd(r6)
/* 8017B394 001782F4  4B FA 3B F9 */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 8017B398 001782F8  80 BF 00 08 */	lwz r5, 8(r31)
/* 8017B39C 001782FC  38 83 00 00 */	addi r4, r3, 0
/* 8017B3A0 00178300  38 65 03 3C */	addi r3, r5, 0x33c
/* 8017B3A4 00178304  4B FA 3E 1D */	bl startMotion__12PaniAnimatorFR14PaniMotionInfo
/* 8017B3A8 00178308  9B DF 00 04 */	stb r30, 4(r31)
.L_8017B3AC:
/* 8017B3AC 0017830C  C0 02 AE 84 */	lfs f0, lbl_803EB084@sda21(r2)
/* 8017B3B0 00178310  80 7F 00 08 */	lwz r3, 8(r31)
/* 8017B3B4 00178314  D0 03 02 C0 */	stfs f0, 0x2c0(r3)
/* 8017B3B8 00178318  80 01 01 14 */	lwz r0, 0x114(r1)
/* 8017B3BC 0017831C  CB E1 01 08 */	lfd f31, 0x108(r1)
/* 8017B3C0 00178320  83 E1 01 04 */	lwz r31, 0x104(r1)
/* 8017B3C4 00178324  83 C1 01 00 */	lwz r30, 0x100(r1)
/* 8017B3C8 00178328  38 21 01 10 */	addi r1, r1, 0x110
/* 8017B3CC 0017832C  7C 08 03 A6 */	mtlr r0
/* 8017B3D0 00178330  4E 80 00 20 */	blr 
.endfn update__13CoreNucleusAiFv

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 8
.obj lbl_802D1598, local
	.asciz "CoreNucleusAi.cpp"
.endobj lbl_802D1598
.balign 4
.obj lbl_802D15AC, local
	.asciz "CoreNucleusAi"
.endobj lbl_802D15AC
.balign 4
.obj lbl_802D15BC, local
	.asciz "PaniAnimKeyListener"
.endobj lbl_802D15BC
.balign 4
.obj lbl_802D15D0, local
	.4byte __RTTI__19PaniAnimKeyListener
	.4byte 0
	.4byte 0
.endobj lbl_802D15D0
.obj __vt__13CoreNucleusAi, global
	.4byte __RTTI__13CoreNucleusAi
	.4byte 0
	.4byte animationKeyUpdated__13CoreNucleusAiFR16PaniAnimKeyEvent
.endobj __vt__13CoreNucleusAi
	.4byte 0
	.4byte 0
	.4byte 0
	.4byte 0

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.balign 8
.obj lbl_803E54F8, local
	.float 0.0
.endobj lbl_803E54F8
.obj __RTTI__19PaniAnimKeyListener, local
	.4byte lbl_802D15BC
	.4byte 0x00000000
.endobj __RTTI__19PaniAnimKeyListener
.obj __RTTI__13CoreNucleusAi, local
	.4byte lbl_802D15AC
	.4byte lbl_802D15D0
.endobj __RTTI__13CoreNucleusAi

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.balign 8
.obj lbl_803EB080, local
	.float 30.0
.endobj lbl_803EB080
.obj lbl_803EB084, local
	.float 0.0
.endobj lbl_803EB084
