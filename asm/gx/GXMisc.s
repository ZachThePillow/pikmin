.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.fn GXFlush, global
/* 80210770 0020D6D0  7C 08 02 A6 */	mflr r0
/* 80210774 0020D6D4  90 01 00 04 */	stw r0, 4(r1)
/* 80210778 0020D6D8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8021077C 0020D6DC  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80210780 0020D6E0  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80210784 0020D6E4  28 00 00 00 */	cmplwi r0, 0
/* 80210788 0020D6E8  41 82 00 08 */	beq .L_80210790
/* 8021078C 0020D6EC  48 00 03 BD */	bl __GXSetDirtyState
.L_80210790:
/* 80210790 0020D6F0  38 00 00 04 */	li r0, 4
/* 80210794 0020D6F4  7C 09 03 A6 */	mtctr r0
/* 80210798 0020D6F8  38 00 00 00 */	li r0, 0
/* 8021079C 0020D6FC  3C 60 CC 01 */	lis r3, 0xCC008000@ha
.L_802107A0:
/* 802107A0 0020D700  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 802107A4 0020D704  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 802107A8 0020D708  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 802107AC 0020D70C  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 802107B0 0020D710  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 802107B4 0020D714  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 802107B8 0020D718  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 802107BC 0020D71C  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 802107C0 0020D720  42 00 FF E0 */	bdnz .L_802107A0
/* 802107C4 0020D724  4B FE 51 B1 */	bl PPCSync
/* 802107C8 0020D728  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802107CC 0020D72C  38 21 00 08 */	addi r1, r1, 8
/* 802107D0 0020D730  7C 08 03 A6 */	mtlr r0
/* 802107D4 0020D734  4E 80 00 20 */	blr 
.endfn GXFlush

.fn GXDrawDone, global
/* 802107D8 0020D738  7C 08 02 A6 */	mflr r0
/* 802107DC 0020D73C  90 01 00 04 */	stw r0, 4(r1)
/* 802107E0 0020D740  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802107E4 0020D744  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802107E8 0020D748  4B FE 87 95 */	bl OSDisableInterrupts
/* 802107EC 0020D74C  38 00 00 61 */	li r0, 0x61
/* 802107F0 0020D750  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 802107F4 0020D754  3C 80 45 00 */	lis r4, 0x45000002@ha
/* 802107F8 0020D758  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 802107FC 0020D75C  38 04 00 02 */	addi r0, r4, 0x45000002@l
/* 80210800 0020D760  90 05 80 00 */	stw r0, 0xCC008000@l(r5)
/* 80210804 0020D764  7C 7F 1B 78 */	mr r31, r3
/* 80210808 0020D768  4B FF FF 69 */	bl GXFlush
/* 8021080C 0020D76C  38 00 00 00 */	li r0, 0
/* 80210810 0020D770  98 0D 34 58 */	stb r0, DrawDone@sda21(r13)
/* 80210814 0020D774  7F E3 FB 78 */	mr r3, r31
/* 80210818 0020D778  4B FE 87 8D */	bl OSRestoreInterrupts
/* 8021081C 0020D77C  4B FE 87 61 */	bl OSDisableInterrupts
/* 80210820 0020D780  7C 7F 1B 78 */	mr r31, r3
/* 80210824 0020D784  48 00 00 0C */	b .L_80210830
.L_80210828:
/* 80210828 0020D788  38 6D 34 5C */	addi r3, r13, FinishQueue@sda21
/* 8021082C 0020D78C  4B FE C1 91 */	bl OSSleepThread
.L_80210830:
/* 80210830 0020D790  88 0D 34 58 */	lbz r0, DrawDone@sda21(r13)
/* 80210834 0020D794  28 00 00 00 */	cmplwi r0, 0
/* 80210838 0020D798  41 82 FF F0 */	beq .L_80210828
/* 8021083C 0020D79C  7F E3 FB 78 */	mr r3, r31
/* 80210840 0020D7A0  4B FE 87 65 */	bl OSRestoreInterrupts
/* 80210844 0020D7A4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80210848 0020D7A8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8021084C 0020D7AC  38 21 00 18 */	addi r1, r1, 0x18
/* 80210850 0020D7B0  7C 08 03 A6 */	mtlr r0
/* 80210854 0020D7B4  4E 80 00 20 */	blr 
.endfn GXDrawDone

.fn GXPixModeSync, global
/* 80210858 0020D7B8  38 00 00 61 */	li r0, 0x61
/* 8021085C 0020D7BC  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80210860 0020D7C0  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80210864 0020D7C4  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80210868 0020D7C8  38 00 00 01 */	li r0, 1
/* 8021086C 0020D7CC  80 64 01 DC */	lwz r3, 0x1dc(r4)
/* 80210870 0020D7D0  90 65 80 00 */	stw r3, 0xCC008000@l(r5)
/* 80210874 0020D7D4  B0 04 00 02 */	sth r0, 2(r4)
/* 80210878 0020D7D8  4E 80 00 20 */	blr 
.endfn GXPixModeSync

.fn GXPokeAlphaMode, global
/* 8021087C 0020D7DC  80 AD 34 28 */	lwz r5, __peReg@sda21(r13)
/* 80210880 0020D7E0  54 80 06 3E */	clrlwi r0, r4, 0x18
/* 80210884 0020D7E4  50 60 40 2E */	rlwimi r0, r3, 8, 0, 0x17
/* 80210888 0020D7E8  B0 05 00 06 */	sth r0, 6(r5)
/* 8021088C 0020D7EC  4E 80 00 20 */	blr 
.endfn GXPokeAlphaMode

.fn GXPokeAlphaRead, global
/* 80210890 0020D7F0  54 60 07 B8 */	rlwinm r0, r3, 0, 0x1e, 0x1c
/* 80210894 0020D7F4  80 6D 34 28 */	lwz r3, __peReg@sda21(r13)
/* 80210898 0020D7F8  60 00 00 04 */	ori r0, r0, 4
/* 8021089C 0020D7FC  B0 03 00 08 */	sth r0, 8(r3)
/* 802108A0 0020D800  4E 80 00 20 */	blr 
.endfn GXPokeAlphaRead

.fn GXPokeAlphaUpdate, global
/* 802108A4 0020D804  80 8D 34 28 */	lwz r4, __peReg@sda21(r13)
/* 802108A8 0020D808  54 60 25 36 */	rlwinm r0, r3, 4, 0x14, 0x1b
/* 802108AC 0020D80C  A4 64 00 02 */	lhzu r3, 2(r4)
/* 802108B0 0020D810  54 63 07 34 */	rlwinm r3, r3, 0, 0x1c, 0x1a
/* 802108B4 0020D814  7C 60 03 78 */	or r0, r3, r0
/* 802108B8 0020D818  B0 04 00 00 */	sth r0, 0(r4)
/* 802108BC 0020D81C  4E 80 00 20 */	blr 
.endfn GXPokeAlphaUpdate

.fn GXPokeBlendMode, global
/* 802108C0 0020D820  80 ED 34 28 */	lwz r7, __peReg@sda21(r13)
/* 802108C4 0020D824  2C 03 00 01 */	cmpwi r3, 1
/* 802108C8 0020D828  39 20 00 01 */	li r9, 1
/* 802108CC 0020D82C  39 47 00 02 */	addi r10, r7, 2
/* 802108D0 0020D830  A0 E7 00 02 */	lhz r7, 2(r7)
/* 802108D4 0020D834  41 82 00 10 */	beq .L_802108E4
/* 802108D8 0020D838  2C 03 00 03 */	cmpwi r3, 3
/* 802108DC 0020D83C  41 82 00 08 */	beq .L_802108E4
/* 802108E0 0020D840  39 20 00 00 */	li r9, 0
.L_802108E4:
/* 802108E4 0020D844  54 E8 00 3C */	rlwinm r8, r7, 0, 0, 0x1e
/* 802108E8 0020D848  20 03 00 03 */	subfic r0, r3, 3
/* 802108EC 0020D84C  7C 07 00 34 */	cntlzw r7, r0
/* 802108F0 0020D850  20 03 00 02 */	subfic r0, r3, 2
/* 802108F4 0020D854  7D 08 4B 78 */	or r8, r8, r9
/* 802108F8 0020D858  7C 00 00 34 */	cntlzw r0, r0
/* 802108FC 0020D85C  55 08 05 66 */	rlwinm r8, r8, 0, 0x15, 0x13
/* 80210900 0020D860  54 E3 30 28 */	rlwinm r3, r7, 6, 0, 0x14
/* 80210904 0020D864  7D 03 1B 78 */	or r3, r8, r3
/* 80210908 0020D868  54 63 07 FA */	rlwinm r3, r3, 0, 0x1f, 0x1d
/* 8021090C 0020D86C  54 00 E1 3C */	rlwinm r0, r0, 0x1c, 4, 0x1e
/* 80210910 0020D870  7C 60 03 78 */	or r0, r3, r0
/* 80210914 0020D874  54 03 05 1E */	rlwinm r3, r0, 0, 0x14, 0xf
/* 80210918 0020D878  54 C0 60 26 */	slwi r0, r6, 0xc
/* 8021091C 0020D87C  7C 60 03 78 */	or r0, r3, r0
/* 80210920 0020D880  54 03 06 28 */	rlwinm r3, r0, 0, 0x18, 0x14
/* 80210924 0020D884  54 80 40 2E */	slwi r0, r4, 8
/* 80210928 0020D888  7C 60 03 78 */	or r0, r3, r0
/* 8021092C 0020D88C  54 03 06 EE */	rlwinm r3, r0, 0, 0x1b, 0x17
/* 80210930 0020D890  54 A0 28 34 */	slwi r0, r5, 5
/* 80210934 0020D894  7C 60 03 78 */	or r0, r3, r0
/* 80210938 0020D898  54 00 02 3E */	clrlwi r0, r0, 8
/* 8021093C 0020D89C  64 00 41 00 */	oris r0, r0, 0x4100
/* 80210940 0020D8A0  B0 0A 00 00 */	sth r0, 0(r10)
/* 80210944 0020D8A4  4E 80 00 20 */	blr 
.endfn GXPokeBlendMode

.fn GXPokeColorUpdate, global
/* 80210948 0020D8A8  80 8D 34 28 */	lwz r4, __peReg@sda21(r13)
/* 8021094C 0020D8AC  54 60 1D 78 */	rlwinm r0, r3, 3, 0x15, 0x1c
/* 80210950 0020D8B0  A4 64 00 02 */	lhzu r3, 2(r4)
/* 80210954 0020D8B4  54 63 07 76 */	rlwinm r3, r3, 0, 0x1d, 0x1b
/* 80210958 0020D8B8  7C 60 03 78 */	or r0, r3, r0
/* 8021095C 0020D8BC  B0 04 00 00 */	sth r0, 0(r4)
/* 80210960 0020D8C0  4E 80 00 20 */	blr 
.endfn GXPokeColorUpdate

.fn GXPokeDstAlpha, global
/* 80210964 0020D8C4  80 AD 34 28 */	lwz r5, __peReg@sda21(r13)
/* 80210968 0020D8C8  54 60 44 2E */	rlwinm r0, r3, 8, 0x10, 0x17
/* 8021096C 0020D8CC  50 80 06 3E */	rlwimi r0, r4, 0, 0x18, 0x1f
/* 80210970 0020D8D0  B0 05 00 04 */	sth r0, 4(r5)
/* 80210974 0020D8D4  4E 80 00 20 */	blr 
.endfn GXPokeDstAlpha

.fn GXPokeDither, global
/* 80210978 0020D8D8  80 8D 34 28 */	lwz r4, __peReg@sda21(r13)
/* 8021097C 0020D8DC  54 60 15 BA */	rlwinm r0, r3, 2, 0x16, 0x1d
/* 80210980 0020D8E0  A4 64 00 02 */	lhzu r3, 2(r4)
/* 80210984 0020D8E4  54 63 07 B8 */	rlwinm r3, r3, 0, 0x1e, 0x1c
/* 80210988 0020D8E8  7C 60 03 78 */	or r0, r3, r0
/* 8021098C 0020D8EC  B0 04 00 00 */	sth r0, 0(r4)
/* 80210990 0020D8F0  4E 80 00 20 */	blr 
.endfn GXPokeDither

.fn GXPokeZMode, global
/* 80210994 0020D8F4  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 80210998 0020D8F8  80 6D 34 28 */	lwz r3, __peReg@sda21(r13)
/* 8021099C 0020D8FC  54 06 07 F6 */	rlwinm r6, r0, 0, 0x1f, 0x1b
/* 802109A0 0020D900  54 80 08 3C */	slwi r0, r4, 1
/* 802109A4 0020D904  7C C0 03 78 */	or r0, r6, r0
/* 802109A8 0020D908  54 04 07 34 */	rlwinm r4, r0, 0, 0x1c, 0x1a
/* 802109AC 0020D90C  54 A0 25 36 */	rlwinm r0, r5, 4, 0x14, 0x1b
/* 802109B0 0020D910  7C 80 03 78 */	or r0, r4, r0
/* 802109B4 0020D914  B0 03 00 00 */	sth r0, 0(r3)
/* 802109B8 0020D918  4E 80 00 20 */	blr 
.endfn GXPokeZMode

.fn GXTokenInterruptHandler, local
/* 802109BC 0020D91C  7C 08 02 A6 */	mflr r0
/* 802109C0 0020D920  90 01 00 04 */	stw r0, 4(r1)
/* 802109C4 0020D924  94 21 FD 20 */	stwu r1, -0x2e0(r1)
/* 802109C8 0020D928  93 E1 02 DC */	stw r31, 0x2dc(r1)
/* 802109CC 0020D92C  93 C1 02 D8 */	stw r30, 0x2d8(r1)
/* 802109D0 0020D930  7C 9E 23 78 */	mr r30, r4
/* 802109D4 0020D934  80 0D 34 50 */	lwz r0, TokenCB@sda21(r13)
/* 802109D8 0020D938  80 6D 34 28 */	lwz r3, __peReg@sda21(r13)
/* 802109DC 0020D93C  28 00 00 00 */	cmplwi r0, 0
/* 802109E0 0020D940  A3 E3 00 0E */	lhz r31, 0xe(r3)
/* 802109E4 0020D944  41 82 00 34 */	beq .L_80210A18
/* 802109E8 0020D948  38 61 00 10 */	addi r3, r1, 0x10
/* 802109EC 0020D94C  4B FE 6A 51 */	bl OSClearContext
/* 802109F0 0020D950  38 61 00 10 */	addi r3, r1, 0x10
/* 802109F4 0020D954  4B FE 68 81 */	bl OSSetCurrentContext
/* 802109F8 0020D958  81 8D 34 50 */	lwz r12, TokenCB@sda21(r13)
/* 802109FC 0020D95C  38 7F 00 00 */	addi r3, r31, 0
/* 80210A00 0020D960  7D 88 03 A6 */	mtlr r12
/* 80210A04 0020D964  4E 80 00 21 */	blrl 
/* 80210A08 0020D968  38 61 00 10 */	addi r3, r1, 0x10
/* 80210A0C 0020D96C  4B FE 6A 31 */	bl OSClearContext
/* 80210A10 0020D970  7F C3 F3 78 */	mr r3, r30
/* 80210A14 0020D974  4B FE 68 61 */	bl OSSetCurrentContext
.L_80210A18:
/* 80210A18 0020D978  80 6D 34 28 */	lwz r3, __peReg@sda21(r13)
/* 80210A1C 0020D97C  A4 03 00 0A */	lhzu r0, 0xa(r3)
/* 80210A20 0020D980  54 00 07 B8 */	rlwinm r0, r0, 0, 0x1e, 0x1c
/* 80210A24 0020D984  60 00 00 04 */	ori r0, r0, 4
/* 80210A28 0020D988  B0 03 00 00 */	sth r0, 0(r3)
/* 80210A2C 0020D98C  80 01 02 E4 */	lwz r0, 0x2e4(r1)
/* 80210A30 0020D990  83 E1 02 DC */	lwz r31, 0x2dc(r1)
/* 80210A34 0020D994  83 C1 02 D8 */	lwz r30, 0x2d8(r1)
/* 80210A38 0020D998  7C 08 03 A6 */	mtlr r0
/* 80210A3C 0020D99C  38 21 02 E0 */	addi r1, r1, 0x2e0
/* 80210A40 0020D9A0  4E 80 00 20 */	blr 
.endfn GXTokenInterruptHandler

.fn GXFinishInterruptHandler, local
/* 80210A44 0020D9A4  7C 08 02 A6 */	mflr r0
/* 80210A48 0020D9A8  38 60 00 01 */	li r3, 1
/* 80210A4C 0020D9AC  90 01 00 04 */	stw r0, 4(r1)
/* 80210A50 0020D9B0  94 21 FD 20 */	stwu r1, -0x2e0(r1)
/* 80210A54 0020D9B4  93 E1 02 DC */	stw r31, 0x2dc(r1)
/* 80210A58 0020D9B8  3B E4 00 00 */	addi r31, r4, 0
/* 80210A5C 0020D9BC  80 AD 34 28 */	lwz r5, __peReg@sda21(r13)
/* 80210A60 0020D9C0  A0 05 00 0A */	lhz r0, 0xa(r5)
/* 80210A64 0020D9C4  54 00 07 76 */	rlwinm r0, r0, 0, 0x1d, 0x1b
/* 80210A68 0020D9C8  60 00 00 08 */	ori r0, r0, 8
/* 80210A6C 0020D9CC  B0 05 00 0A */	sth r0, 0xa(r5)
/* 80210A70 0020D9D0  80 0D 34 54 */	lwz r0, DrawDoneCB@sda21(r13)
/* 80210A74 0020D9D4  98 6D 34 58 */	stb r3, DrawDone@sda21(r13)
/* 80210A78 0020D9D8  28 00 00 00 */	cmplwi r0, 0
/* 80210A7C 0020D9DC  41 82 00 30 */	beq .L_80210AAC
/* 80210A80 0020D9E0  38 61 00 10 */	addi r3, r1, 0x10
/* 80210A84 0020D9E4  4B FE 69 B9 */	bl OSClearContext
/* 80210A88 0020D9E8  38 61 00 10 */	addi r3, r1, 0x10
/* 80210A8C 0020D9EC  4B FE 67 E9 */	bl OSSetCurrentContext
/* 80210A90 0020D9F0  81 8D 34 54 */	lwz r12, DrawDoneCB@sda21(r13)
/* 80210A94 0020D9F4  7D 88 03 A6 */	mtlr r12
/* 80210A98 0020D9F8  4E 80 00 21 */	blrl 
/* 80210A9C 0020D9FC  38 61 00 10 */	addi r3, r1, 0x10
/* 80210AA0 0020DA00  4B FE 69 9D */	bl OSClearContext
/* 80210AA4 0020DA04  7F E3 FB 78 */	mr r3, r31
/* 80210AA8 0020DA08  4B FE 67 CD */	bl OSSetCurrentContext
.L_80210AAC:
/* 80210AAC 0020DA0C  38 6D 34 5C */	addi r3, r13, FinishQueue@sda21
/* 80210AB0 0020DA10  4B FE BF F9 */	bl OSWakeupThread
/* 80210AB4 0020DA14  80 01 02 E4 */	lwz r0, 0x2e4(r1)
/* 80210AB8 0020DA18  83 E1 02 DC */	lwz r31, 0x2dc(r1)
/* 80210ABC 0020DA1C  38 21 02 E0 */	addi r1, r1, 0x2e0
/* 80210AC0 0020DA20  7C 08 03 A6 */	mtlr r0
/* 80210AC4 0020DA24  4E 80 00 20 */	blr 
.endfn GXFinishInterruptHandler

.fn __GXPEInit, global
/* 80210AC8 0020DA28  7C 08 02 A6 */	mflr r0
/* 80210ACC 0020DA2C  3C 60 80 21 */	lis r3, GXTokenInterruptHandler@ha
/* 80210AD0 0020DA30  90 01 00 04 */	stw r0, 4(r1)
/* 80210AD4 0020DA34  38 83 09 BC */	addi r4, r3, GXTokenInterruptHandler@l
/* 80210AD8 0020DA38  38 60 00 12 */	li r3, 0x12
/* 80210ADC 0020DA3C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80210AE0 0020DA40  4B FE 84 E9 */	bl __OSSetInterruptHandler
/* 80210AE4 0020DA44  3C 60 80 21 */	lis r3, GXFinishInterruptHandler@ha
/* 80210AE8 0020DA48  38 83 0A 44 */	addi r4, r3, GXFinishInterruptHandler@l
/* 80210AEC 0020DA4C  38 60 00 13 */	li r3, 0x13
/* 80210AF0 0020DA50  4B FE 84 D9 */	bl __OSSetInterruptHandler
/* 80210AF4 0020DA54  38 6D 34 5C */	addi r3, r13, FinishQueue@sda21
/* 80210AF8 0020DA58  4B FE AF DD */	bl OSInitThreadQueue
/* 80210AFC 0020DA5C  38 60 20 00 */	li r3, 0x2000
/* 80210B00 0020DA60  4B FE 88 A5 */	bl __OSUnmaskInterrupts
/* 80210B04 0020DA64  38 60 10 00 */	li r3, 0x1000
/* 80210B08 0020DA68  4B FE 88 9D */	bl __OSUnmaskInterrupts
/* 80210B0C 0020DA6C  80 6D 34 28 */	lwz r3, __peReg@sda21(r13)
/* 80210B10 0020DA70  A4 03 00 0A */	lhzu r0, 0xa(r3)
/* 80210B14 0020DA74  54 00 07 B8 */	rlwinm r0, r0, 0, 0x1e, 0x1c
/* 80210B18 0020DA78  60 00 00 04 */	ori r0, r0, 4
/* 80210B1C 0020DA7C  54 00 07 76 */	rlwinm r0, r0, 0, 0x1d, 0x1b
/* 80210B20 0020DA80  60 00 00 08 */	ori r0, r0, 8
/* 80210B24 0020DA84  54 00 00 3C */	rlwinm r0, r0, 0, 0, 0x1e
/* 80210B28 0020DA88  60 00 00 01 */	ori r0, r0, 1
/* 80210B2C 0020DA8C  54 00 07 FA */	rlwinm r0, r0, 0, 0x1f, 0x1d
/* 80210B30 0020DA90  60 00 00 02 */	ori r0, r0, 2
/* 80210B34 0020DA94  B0 03 00 00 */	sth r0, 0(r3)
/* 80210B38 0020DA98  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80210B3C 0020DA9C  38 21 00 08 */	addi r1, r1, 8
/* 80210B40 0020DAA0  7C 08 03 A6 */	mtlr r0
/* 80210B44 0020DAA4  4E 80 00 20 */	blr 
.endfn __GXPEInit

.section .sbss, "wa"
.balign 8
.obj TokenCB, local
	.skip 0x4
.endobj TokenCB
.obj DrawDoneCB, local
	.skip 0x4
.endobj DrawDoneCB
.obj DrawDone, local
	.skip 0x1
.endobj DrawDone
.balign 4
.obj FinishQueue, local
	.skip 0x8
.endobj FinishQueue
