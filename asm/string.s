.include "macros.inc"

.global getLength__6StringFv
getLength__6StringFv:
/* 800258F0 00022850  80 83 00 04 */	lwz r4, 4(r3)
/* 800258F4 00022854  38 60 00 00 */	li r3, 0
/* 800258F8 00022858  48 00 00 08 */	b lbl_80025900
lbl_800258FC:
/* 800258FC 0002285C  38 63 00 01 */	addi r3, r3, 1
lbl_80025900:
/* 80025900 00022860  88 04 00 00 */	lbz r0, 0(r4)
/* 80025904 00022864  38 84 00 01 */	addi r4, r4, 1
/* 80025908 00022868  28 00 00 00 */	cmplwi r0, 0
/* 8002590C 0002286C  40 82 FF F0 */	bne lbl_800258FC
/* 80025910 00022870  4E 80 00 20 */	blr 
