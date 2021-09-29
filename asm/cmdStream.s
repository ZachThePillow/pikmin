.include "macros.inc"

.global __ct__9CmdStreamFP6Stream
__ct__9CmdStreamFP6Stream:
/* 80040B7C 0003DADC  7C 08 02 A6 */	mflr r0
/* 80040B80 0003DAE0  90 01 00 04 */	stw r0, 4(r1)
/* 80040B84 0003DAE4  38 00 00 00 */	li r0, 0
/* 80040B88 0003DAE8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80040B8C 0003DAEC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80040B90 0003DAF0  7C 9F 23 78 */	mr r31, r4
/* 80040B94 0003DAF4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80040B98 0003DAF8  3B C3 00 00 */	addi r30, r3, 0
/* 80040B9C 0003DAFC  90 03 00 04 */	stw r0, 4(r3)
/* 80040BA0 0003DB00  80 0D 2D E0 */	lwz r0, statbuff__9CmdStream@sda21(r13)
/* 80040BA4 0003DB04  28 00 00 00 */	cmplwi r0, 0
/* 80040BA8 0003DB08  40 82 00 14 */	bne lbl_80040BBC
/* 80040BAC 0003DB0C  3C 60 00 01 */	lis r3, 0x00008000@ha
/* 80040BB0 0003DB10  38 63 80 00 */	addi r3, r3, 0x00008000@l
/* 80040BB4 0003DB14  48 00 64 51 */	bl alloc__6SystemFUl
/* 80040BB8 0003DB18  90 6D 2D E0 */	stw r3, statbuff__9CmdStream@sda21(r13)
lbl_80040BBC:
/* 80040BBC 0003DB1C  3C 80 00 01 */	lis r4, 0x00008000@ha
/* 80040BC0 0003DB20  80 6D 2D E0 */	lwz r3, statbuff__9CmdStream@sda21(r13)
/* 80040BC4 0003DB24  38 A4 80 00 */	addi r5, r4, 0x00008000@l
/* 80040BC8 0003DB28  38 80 00 00 */	li r4, 0
/* 80040BCC 0003DB2C  4B FC 27 55 */	bl memset
/* 80040BD0 0003DB30  93 FE 00 00 */	stw r31, 0(r30)
/* 80040BD4 0003DB34  80 7E 00 00 */	lwz r3, 0(r30)
/* 80040BD8 0003DB38  81 83 00 04 */	lwz r12, 4(r3)
/* 80040BDC 0003DB3C  81 8C 00 44 */	lwz r12, 0x44(r12)
/* 80040BE0 0003DB40  7D 88 03 A6 */	mtlr r12
/* 80040BE4 0003DB44  4E 80 00 21 */	blrl 
/* 80040BE8 0003DB48  90 7E 01 08 */	stw r3, 0x108(r30)
/* 80040BEC 0003DB4C  38 00 00 00 */	li r0, 0
/* 80040BF0 0003DB50  38 7E 00 00 */	addi r3, r30, 0
/* 80040BF4 0003DB54  90 1E 01 14 */	stw r0, 0x114(r30)
/* 80040BF8 0003DB58  38 80 00 01 */	li r4, 1
/* 80040BFC 0003DB5C  90 1E 01 0C */	stw r0, 0x10c(r30)
/* 80040C00 0003DB60  90 1E 01 10 */	stw r0, 0x110(r30)
/* 80040C04 0003DB64  80 0D 2D E0 */	lwz r0, statbuff__9CmdStream@sda21(r13)
/* 80040C08 0003DB68  90 1E 00 04 */	stw r0, 4(r30)
/* 80040C0C 0003DB6C  48 00 00 21 */	bl fillBuffer__9CmdStreamFb
/* 80040C10 0003DB70  7F C3 F3 78 */	mr r3, r30
/* 80040C14 0003DB74  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80040C18 0003DB78  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80040C1C 0003DB7C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80040C20 0003DB80  38 21 00 18 */	addi r1, r1, 0x18
/* 80040C24 0003DB84  7C 08 03 A6 */	mtlr r0
/* 80040C28 0003DB88  4E 80 00 20 */	blr 

.global fillBuffer__9CmdStreamFb
fillBuffer__9CmdStreamFb:
/* 80040C2C 0003DB8C  7C 08 02 A6 */	mflr r0
/* 80040C30 0003DB90  90 01 00 04 */	stw r0, 4(r1)
/* 80040C34 0003DB94  54 80 06 3F */	clrlwi. r0, r4, 0x18
/* 80040C38 0003DB98  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80040C3C 0003DB9C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80040C40 0003DBA0  3B E3 00 00 */	addi r31, r3, 0
/* 80040C44 0003DBA4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80040C48 0003DBA8  40 82 00 18 */	bne lbl_80040C60
/* 80040C4C 0003DBAC  80 7F 01 10 */	lwz r3, 0x110(r31)
/* 80040C50 0003DBB0  80 1F 01 14 */	lwz r0, 0x114(r31)
/* 80040C54 0003DBB4  7C 03 00 50 */	subf r0, r3, r0
/* 80040C58 0003DBB8  2C 00 40 00 */	cmpwi r0, 0x4000
/* 80040C5C 0003DBBC  41 80 00 A4 */	blt lbl_80040D00
lbl_80040C60:
/* 80040C60 0003DBC0  80 1F 01 0C */	lwz r0, 0x10c(r31)
/* 80040C64 0003DBC4  2C 00 00 00 */	cmpwi r0, 0
/* 80040C68 0003DBC8  41 82 00 38 */	beq lbl_80040CA0
/* 80040C6C 0003DBCC  80 1F 01 10 */	lwz r0, 0x110(r31)
/* 80040C70 0003DBD0  38 A0 40 00 */	li r5, 0x4000
/* 80040C74 0003DBD4  80 7F 00 04 */	lwz r3, 4(r31)
/* 80040C78 0003DBD8  7C 63 02 14 */	add r3, r3, r0
/* 80040C7C 0003DBDC  38 83 00 00 */	addi r4, r3, 0
/* 80040C80 0003DBE0  38 84 40 00 */	addi r4, r4, 0x4000
/* 80040C84 0003DBE4  4B FC 27 91 */	bl memcpy
/* 80040C88 0003DBE8  80 7F 00 04 */	lwz r3, 4(r31)
/* 80040C8C 0003DBEC  38 03 C0 00 */	addi r0, r3, -16384
/* 80040C90 0003DBF0  90 1F 00 04 */	stw r0, 4(r31)
/* 80040C94 0003DBF4  80 7F 01 10 */	lwz r3, 0x110(r31)
/* 80040C98 0003DBF8  38 03 40 00 */	addi r0, r3, 0x4000
/* 80040C9C 0003DBFC  90 1F 01 10 */	stw r0, 0x110(r31)
lbl_80040CA0:
/* 80040CA0 0003DC00  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80040CA4 0003DC04  2C 04 00 00 */	cmpwi r4, 0
/* 80040CA8 0003DC08  41 82 00 0C */	beq lbl_80040CB4
/* 80040CAC 0003DC0C  38 60 40 00 */	li r3, 0x4000
/* 80040CB0 0003DC10  48 00 00 0C */	b lbl_80040CBC
lbl_80040CB4:
/* 80040CB4 0003DC14  3C 60 00 01 */	lis r3, 0x00008000@ha
/* 80040CB8 0003DC18  38 63 80 00 */	addi r3, r3, 0x00008000@l
lbl_80040CBC:
/* 80040CBC 0003DC1C  80 1F 01 08 */	lwz r0, 0x108(r31)
/* 80040CC0 0003DC20  3B C3 00 00 */	addi r30, r3, 0
/* 80040CC4 0003DC24  7C 04 00 50 */	subf r0, r4, r0
/* 80040CC8 0003DC28  7C 00 18 00 */	cmpw r0, r3
/* 80040CCC 0003DC2C  40 80 00 08 */	bge lbl_80040CD4
/* 80040CD0 0003DC30  7C 1E 03 78 */	mr r30, r0
lbl_80040CD4:
/* 80040CD4 0003DC34  80 7F 00 00 */	lwz r3, 0(r31)
/* 80040CD8 0003DC38  7F C5 F3 78 */	mr r5, r30
/* 80040CDC 0003DC3C  80 1F 00 04 */	lwz r0, 4(r31)
/* 80040CE0 0003DC40  81 83 00 04 */	lwz r12, 4(r3)
/* 80040CE4 0003DC44  7C 80 22 14 */	add r4, r0, r4
/* 80040CE8 0003DC48  81 8C 00 3C */	lwz r12, 0x3c(r12)
/* 80040CEC 0003DC4C  7D 88 03 A6 */	mtlr r12
/* 80040CF0 0003DC50  4E 80 00 21 */	blrl 
/* 80040CF4 0003DC54  80 1F 01 0C */	lwz r0, 0x10c(r31)
/* 80040CF8 0003DC58  7C 00 F2 14 */	add r0, r0, r30
/* 80040CFC 0003DC5C  90 1F 01 0C */	stw r0, 0x10c(r31)
lbl_80040D00:
/* 80040D00 0003DC60  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80040D04 0003DC64  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80040D08 0003DC68  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80040D0C 0003DC6C  38 21 00 18 */	addi r1, r1, 0x18
/* 80040D10 0003DC70  7C 08 03 A6 */	mtlr r0
/* 80040D14 0003DC74  4E 80 00 20 */	blr 

.global whiteSpace__9CmdStreamFc
whiteSpace__9CmdStreamFc:
/* 80040D18 0003DC78  54 83 06 3F */	clrlwi. r3, r4, 0x18
/* 80040D1C 0003DC7C  41 82 00 2C */	beq lbl_80040D48
/* 80040D20 0003DC80  28 03 00 0D */	cmplwi r3, 0xd
/* 80040D24 0003DC84  41 82 00 24 */	beq lbl_80040D48
/* 80040D28 0003DC88  38 04 FF F7 */	addi r0, r4, -9
/* 80040D2C 0003DC8C  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 80040D30 0003DC90  28 00 00 01 */	cmplwi r0, 1
/* 80040D34 0003DC94  40 81 00 14 */	ble lbl_80040D48
/* 80040D38 0003DC98  28 03 00 20 */	cmplwi r3, 0x20
/* 80040D3C 0003DC9C  41 82 00 0C */	beq lbl_80040D48
/* 80040D40 0003DCA0  28 03 00 2C */	cmplwi r3, 0x2c
/* 80040D44 0003DCA4  40 82 00 0C */	bne lbl_80040D50
lbl_80040D48:
/* 80040D48 0003DCA8  38 60 00 01 */	li r3, 1
/* 80040D4C 0003DCAC  4E 80 00 20 */	blr 
lbl_80040D50:
/* 80040D50 0003DCB0  38 60 00 00 */	li r3, 0
/* 80040D54 0003DCB4  4E 80 00 20 */	blr 

.global endOfCmds__9CmdStreamFv
endOfCmds__9CmdStreamFv:
/* 80040D58 0003DCB8  7C 08 02 A6 */	mflr r0
/* 80040D5C 0003DCBC  90 01 00 04 */	stw r0, 4(r1)
/* 80040D60 0003DCC0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80040D64 0003DCC4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80040D68 0003DCC8  7C 7F 1B 78 */	mr r31, r3
/* 80040D6C 0003DCCC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80040D70 0003DCD0  80 63 01 10 */	lwz r3, 0x110(r3)
/* 80040D74 0003DCD4  80 1F 01 14 */	lwz r0, 0x114(r31)
/* 80040D78 0003DCD8  7C 03 00 50 */	subf r0, r3, r0
/* 80040D7C 0003DCDC  2C 00 40 00 */	cmpwi r0, 0x4000
/* 80040D80 0003DCE0  41 80 00 AC */	blt lbl_80040E2C
/* 80040D84 0003DCE4  80 1F 01 0C */	lwz r0, 0x10c(r31)
/* 80040D88 0003DCE8  2C 00 00 00 */	cmpwi r0, 0
/* 80040D8C 0003DCEC  41 82 00 34 */	beq lbl_80040DC0
/* 80040D90 0003DCF0  80 1F 00 04 */	lwz r0, 4(r31)
/* 80040D94 0003DCF4  38 A0 40 00 */	li r5, 0x4000
/* 80040D98 0003DCF8  7C 60 1A 14 */	add r3, r0, r3
/* 80040D9C 0003DCFC  38 83 00 00 */	addi r4, r3, 0
/* 80040DA0 0003DD00  38 84 40 00 */	addi r4, r4, 0x4000
/* 80040DA4 0003DD04  4B FC 26 71 */	bl memcpy
/* 80040DA8 0003DD08  80 7F 00 04 */	lwz r3, 4(r31)
/* 80040DAC 0003DD0C  38 03 C0 00 */	addi r0, r3, -16384
/* 80040DB0 0003DD10  90 1F 00 04 */	stw r0, 4(r31)
/* 80040DB4 0003DD14  80 7F 01 10 */	lwz r3, 0x110(r31)
/* 80040DB8 0003DD18  38 03 40 00 */	addi r0, r3, 0x4000
/* 80040DBC 0003DD1C  90 1F 01 10 */	stw r0, 0x110(r31)
lbl_80040DC0:
/* 80040DC0 0003DD20  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80040DC4 0003DD24  2C 04 00 00 */	cmpwi r4, 0
/* 80040DC8 0003DD28  41 82 00 0C */	beq lbl_80040DD4
/* 80040DCC 0003DD2C  3B C0 40 00 */	li r30, 0x4000
/* 80040DD0 0003DD30  48 00 00 0C */	b lbl_80040DDC
lbl_80040DD4:
/* 80040DD4 0003DD34  3C 60 00 01 */	lis r3, 0x00008000@ha
/* 80040DD8 0003DD38  3B C3 80 00 */	addi r30, r3, 0x00008000@l
lbl_80040DDC:
/* 80040DDC 0003DD3C  80 1F 01 08 */	lwz r0, 0x108(r31)
/* 80040DE0 0003DD40  7C 04 00 50 */	subf r0, r4, r0
/* 80040DE4 0003DD44  7C 00 F0 00 */	cmpw r0, r30
/* 80040DE8 0003DD48  40 80 00 08 */	bge lbl_80040DF0
/* 80040DEC 0003DD4C  7C 1E 03 78 */	mr r30, r0
lbl_80040DF0:
/* 80040DF0 0003DD50  80 7F 00 00 */	lwz r3, 0(r31)
/* 80040DF4 0003DD54  7F C5 F3 78 */	mr r5, r30
/* 80040DF8 0003DD58  80 1F 00 04 */	lwz r0, 4(r31)
/* 80040DFC 0003DD5C  81 83 00 04 */	lwz r12, 4(r3)
/* 80040E00 0003DD60  7C 80 22 14 */	add r4, r0, r4
/* 80040E04 0003DD64  81 8C 00 3C */	lwz r12, 0x3c(r12)
/* 80040E08 0003DD68  7D 88 03 A6 */	mtlr r12
/* 80040E0C 0003DD6C  4E 80 00 21 */	blrl 
/* 80040E10 0003DD70  80 1F 01 0C */	lwz r0, 0x10c(r31)
/* 80040E14 0003DD74  7C 00 F2 14 */	add r0, r0, r30
/* 80040E18 0003DD78  90 1F 01 0C */	stw r0, 0x10c(r31)
/* 80040E1C 0003DD7C  48 00 00 10 */	b lbl_80040E2C
lbl_80040E20:
/* 80040E20 0003DD80  80 7F 01 14 */	lwz r3, 0x114(r31)
/* 80040E24 0003DD84  38 03 00 01 */	addi r0, r3, 1
/* 80040E28 0003DD88  90 1F 01 14 */	stw r0, 0x114(r31)
lbl_80040E2C:
/* 80040E2C 0003DD8C  80 9F 01 14 */	lwz r4, 0x114(r31)
/* 80040E30 0003DD90  80 BF 01 08 */	lwz r5, 0x108(r31)
/* 80040E34 0003DD94  7C 04 28 00 */	cmpw r4, r5
/* 80040E38 0003DD98  40 80 00 50 */	bge lbl_80040E88
/* 80040E3C 0003DD9C  80 7F 00 04 */	lwz r3, 4(r31)
/* 80040E40 0003DDA0  7C 63 20 AE */	lbzx r3, r3, r4
/* 80040E44 0003DDA4  28 03 00 00 */	cmplwi r3, 0
/* 80040E48 0003DDA8  41 82 00 2C */	beq lbl_80040E74
/* 80040E4C 0003DDAC  28 03 00 0D */	cmplwi r3, 0xd
/* 80040E50 0003DDB0  41 82 00 24 */	beq lbl_80040E74
/* 80040E54 0003DDB4  38 03 FF F7 */	addi r0, r3, -9
/* 80040E58 0003DDB8  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 80040E5C 0003DDBC  28 00 00 01 */	cmplwi r0, 1
/* 80040E60 0003DDC0  40 81 00 14 */	ble lbl_80040E74
/* 80040E64 0003DDC4  28 03 00 20 */	cmplwi r3, 0x20
/* 80040E68 0003DDC8  41 82 00 0C */	beq lbl_80040E74
/* 80040E6C 0003DDCC  28 03 00 2C */	cmplwi r3, 0x2c
/* 80040E70 0003DDD0  40 82 00 0C */	bne lbl_80040E7C
lbl_80040E74:
/* 80040E74 0003DDD4  38 00 00 01 */	li r0, 1
/* 80040E78 0003DDD8  48 00 00 08 */	b lbl_80040E80
lbl_80040E7C:
/* 80040E7C 0003DDDC  38 00 00 00 */	li r0, 0
lbl_80040E80:
/* 80040E80 0003DDE0  54 00 06 3F */	clrlwi. r0, r0, 0x18
/* 80040E84 0003DDE4  40 82 FF 9C */	bne lbl_80040E20
lbl_80040E88:
/* 80040E88 0003DDE8  7C 04 28 00 */	cmpw r4, r5
/* 80040E8C 0003DDEC  40 80 00 24 */	bge lbl_80040EB0
/* 80040E90 0003DDF0  80 7F 00 04 */	lwz r3, 4(r31)
/* 80040E94 0003DDF4  7C 03 20 AE */	lbzx r0, r3, r4
/* 80040E98 0003DDF8  2C 00 FF FF */	cmpwi r0, -1
/* 80040E9C 0003DDFC  40 82 00 0C */	bne lbl_80040EA8
/* 80040EA0 0003DE00  38 60 00 01 */	li r3, 1
/* 80040EA4 0003DE04  48 00 00 10 */	b lbl_80040EB4
lbl_80040EA8:
/* 80040EA8 0003DE08  38 60 00 00 */	li r3, 0
/* 80040EAC 0003DE0C  48 00 00 08 */	b lbl_80040EB4
lbl_80040EB0:
/* 80040EB0 0003DE10  38 60 00 01 */	li r3, 1
lbl_80040EB4:
/* 80040EB4 0003DE14  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80040EB8 0003DE18  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80040EBC 0003DE1C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80040EC0 0003DE20  38 21 00 18 */	addi r1, r1, 0x18
/* 80040EC4 0003DE24  7C 08 03 A6 */	mtlr r0
/* 80040EC8 0003DE28  4E 80 00 20 */	blr 

.global copyToToken__9CmdStreamFi
copyToToken__9CmdStreamFi:
/* 80040ECC 0003DE2C  2C 04 00 00 */	cmpwi r4, 0
/* 80040ED0 0003DE30  7C 89 03 A6 */	mtctr r4
/* 80040ED4 0003DE34  38 A0 00 00 */	li r5, 0
/* 80040ED8 0003DE38  40 81 00 34 */	ble lbl_80040F0C
lbl_80040EDC:
/* 80040EDC 0003DE3C  80 03 01 14 */	lwz r0, 0x114(r3)
/* 80040EE0 0003DE40  80 83 00 04 */	lwz r4, 4(r3)
/* 80040EE4 0003DE44  7C 00 2A 14 */	add r0, r0, r5
/* 80040EE8 0003DE48  7C 04 00 AE */	lbzx r0, r4, r0
/* 80040EEC 0003DE4C  28 00 00 09 */	cmplwi r0, 9
/* 80040EF0 0003DE50  7C 04 03 78 */	mr r4, r0
/* 80040EF4 0003DE54  40 82 00 08 */	bne lbl_80040EFC
/* 80040EF8 0003DE58  38 80 00 20 */	li r4, 0x20
lbl_80040EFC:
/* 80040EFC 0003DE5C  38 05 00 08 */	addi r0, r5, 8
/* 80040F00 0003DE60  7C 83 01 AE */	stbx r4, r3, r0
/* 80040F04 0003DE64  38 A5 00 01 */	addi r5, r5, 1
/* 80040F08 0003DE68  42 00 FF D4 */	bdnz lbl_80040EDC
lbl_80040F0C:
/* 80040F0C 0003DE6C  7C 63 2A 14 */	add r3, r3, r5
/* 80040F10 0003DE70  38 00 00 00 */	li r0, 0
/* 80040F14 0003DE74  98 03 00 08 */	stb r0, 8(r3)
/* 80040F18 0003DE78  4E 80 00 20 */	blr 

.global skipLine__9CmdStreamFv
skipLine__9CmdStreamFv:
/* 80040F1C 0003DE7C  7C 08 02 A6 */	mflr r0
/* 80040F20 0003DE80  90 01 00 04 */	stw r0, 4(r1)
/* 80040F24 0003DE84  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80040F28 0003DE88  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80040F2C 0003DE8C  7C 7F 1B 78 */	mr r31, r3
/* 80040F30 0003DE90  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80040F34 0003DE94  80 63 01 10 */	lwz r3, 0x110(r3)
/* 80040F38 0003DE98  80 1F 01 14 */	lwz r0, 0x114(r31)
/* 80040F3C 0003DE9C  7C 03 00 50 */	subf r0, r3, r0
/* 80040F40 0003DEA0  2C 00 40 00 */	cmpwi r0, 0x4000
/* 80040F44 0003DEA4  41 80 00 9C */	blt lbl_80040FE0
/* 80040F48 0003DEA8  80 1F 01 0C */	lwz r0, 0x10c(r31)
/* 80040F4C 0003DEAC  2C 00 00 00 */	cmpwi r0, 0
/* 80040F50 0003DEB0  41 82 00 34 */	beq lbl_80040F84
/* 80040F54 0003DEB4  80 1F 00 04 */	lwz r0, 4(r31)
/* 80040F58 0003DEB8  38 A0 40 00 */	li r5, 0x4000
/* 80040F5C 0003DEBC  7C 60 1A 14 */	add r3, r0, r3
/* 80040F60 0003DEC0  38 83 00 00 */	addi r4, r3, 0
/* 80040F64 0003DEC4  38 84 40 00 */	addi r4, r4, 0x4000
/* 80040F68 0003DEC8  4B FC 24 AD */	bl memcpy
/* 80040F6C 0003DECC  80 7F 00 04 */	lwz r3, 4(r31)
/* 80040F70 0003DED0  38 03 C0 00 */	addi r0, r3, -16384
/* 80040F74 0003DED4  90 1F 00 04 */	stw r0, 4(r31)
/* 80040F78 0003DED8  80 7F 01 10 */	lwz r3, 0x110(r31)
/* 80040F7C 0003DEDC  38 03 40 00 */	addi r0, r3, 0x4000
/* 80040F80 0003DEE0  90 1F 01 10 */	stw r0, 0x110(r31)
lbl_80040F84:
/* 80040F84 0003DEE4  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80040F88 0003DEE8  2C 04 00 00 */	cmpwi r4, 0
/* 80040F8C 0003DEEC  41 82 00 0C */	beq lbl_80040F98
/* 80040F90 0003DEF0  3B C0 40 00 */	li r30, 0x4000
/* 80040F94 0003DEF4  48 00 00 0C */	b lbl_80040FA0
lbl_80040F98:
/* 80040F98 0003DEF8  3C 60 00 01 */	lis r3, 0x00008000@ha
/* 80040F9C 0003DEFC  3B C3 80 00 */	addi r30, r3, 0x00008000@l
lbl_80040FA0:
/* 80040FA0 0003DF00  80 1F 01 08 */	lwz r0, 0x108(r31)
/* 80040FA4 0003DF04  7C 04 00 50 */	subf r0, r4, r0
/* 80040FA8 0003DF08  7C 00 F0 00 */	cmpw r0, r30
/* 80040FAC 0003DF0C  40 80 00 08 */	bge lbl_80040FB4
/* 80040FB0 0003DF10  7C 1E 03 78 */	mr r30, r0
lbl_80040FB4:
/* 80040FB4 0003DF14  80 7F 00 00 */	lwz r3, 0(r31)
/* 80040FB8 0003DF18  7F C5 F3 78 */	mr r5, r30
/* 80040FBC 0003DF1C  80 1F 00 04 */	lwz r0, 4(r31)
/* 80040FC0 0003DF20  81 83 00 04 */	lwz r12, 4(r3)
/* 80040FC4 0003DF24  7C 80 22 14 */	add r4, r0, r4
/* 80040FC8 0003DF28  81 8C 00 3C */	lwz r12, 0x3c(r12)
/* 80040FCC 0003DF2C  7D 88 03 A6 */	mtlr r12
/* 80040FD0 0003DF30  4E 80 00 21 */	blrl 
/* 80040FD4 0003DF34  80 1F 01 0C */	lwz r0, 0x10c(r31)
/* 80040FD8 0003DF38  7C 00 F2 14 */	add r0, r0, r30
/* 80040FDC 0003DF3C  90 1F 01 0C */	stw r0, 0x10c(r31)
lbl_80040FE0:
/* 80040FE0 0003DF40  80 9F 01 14 */	lwz r4, 0x114(r31)
/* 80040FE4 0003DF44  80 1F 01 08 */	lwz r0, 0x108(r31)
/* 80040FE8 0003DF48  7C 85 23 78 */	mr r5, r4
/* 80040FEC 0003DF4C  48 00 00 08 */	b lbl_80040FF4
lbl_80040FF0:
/* 80040FF0 0003DF50  38 A5 00 01 */	addi r5, r5, 1
lbl_80040FF4:
/* 80040FF4 0003DF54  7C 05 00 00 */	cmpw r5, r0
/* 80040FF8 0003DF58  40 80 00 1C */	bge lbl_80041014
/* 80040FFC 0003DF5C  80 7F 00 04 */	lwz r3, 4(r31)
/* 80041000 0003DF60  7C 63 28 AE */	lbzx r3, r3, r5
/* 80041004 0003DF64  28 03 00 0A */	cmplwi r3, 0xa
/* 80041008 0003DF68  41 82 00 0C */	beq lbl_80041014
/* 8004100C 0003DF6C  28 03 00 0D */	cmplwi r3, 0xd
/* 80041010 0003DF70  40 82 FF E0 */	bne lbl_80040FF0
lbl_80041014:
/* 80041014 0003DF74  7C 04 28 51 */	subf. r0, r4, r5
/* 80041018 0003DF78  38 80 00 00 */	li r4, 0
/* 8004101C 0003DF7C  7C 09 03 A6 */	mtctr r0
/* 80041020 0003DF80  40 81 00 30 */	ble lbl_80041050
lbl_80041024:
/* 80041024 0003DF84  80 1F 01 14 */	lwz r0, 0x114(r31)
/* 80041028 0003DF88  80 7F 00 04 */	lwz r3, 4(r31)
/* 8004102C 0003DF8C  7C 00 22 14 */	add r0, r0, r4
/* 80041030 0003DF90  7C 63 00 AE */	lbzx r3, r3, r0
/* 80041034 0003DF94  28 03 00 09 */	cmplwi r3, 9
/* 80041038 0003DF98  40 82 00 08 */	bne lbl_80041040
/* 8004103C 0003DF9C  38 60 00 20 */	li r3, 0x20
lbl_80041040:
/* 80041040 0003DFA0  38 04 00 08 */	addi r0, r4, 8
/* 80041044 0003DFA4  7C 7F 01 AE */	stbx r3, r31, r0
/* 80041048 0003DFA8  38 84 00 01 */	addi r4, r4, 1
/* 8004104C 0003DFAC  42 00 FF D8 */	bdnz lbl_80041024
lbl_80041050:
/* 80041050 0003DFB0  7C 7F 22 14 */	add r3, r31, r4
/* 80041054 0003DFB4  38 00 00 00 */	li r0, 0
/* 80041058 0003DFB8  98 03 00 08 */	stb r0, 8(r3)
/* 8004105C 0003DFBC  80 1F 00 04 */	lwz r0, 4(r31)
/* 80041060 0003DFC0  7C 80 2A 14 */	add r4, r0, r5
/* 80041064 0003DFC4  38 64 00 00 */	addi r3, r4, 0
/* 80041068 0003DFC8  48 00 00 10 */	b lbl_80041078
lbl_8004106C:
/* 8004106C 0003DFCC  38 84 00 01 */	addi r4, r4, 1
/* 80041070 0003DFD0  38 A5 00 01 */	addi r5, r5, 1
/* 80041074 0003DFD4  38 63 00 01 */	addi r3, r3, 1
lbl_80041078:
/* 80041078 0003DFD8  88 04 00 00 */	lbz r0, 0(r4)
/* 8004107C 0003DFDC  28 00 00 0A */	cmplwi r0, 0xa
/* 80041080 0003DFE0  41 82 FF EC */	beq lbl_8004106C
/* 80041084 0003DFE4  88 03 00 00 */	lbz r0, 0(r3)
/* 80041088 0003DFE8  28 00 00 0D */	cmplwi r0, 0xd
/* 8004108C 0003DFEC  41 82 FF E0 */	beq lbl_8004106C
/* 80041090 0003DFF0  90 BF 01 14 */	stw r5, 0x114(r31)
/* 80041094 0003DFF4  38 7F 00 08 */	addi r3, r31, 8
/* 80041098 0003DFF8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8004109C 0003DFFC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800410A0 0003E000  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800410A4 0003E004  38 21 00 18 */	addi r1, r1, 0x18
/* 800410A8 0003E008  7C 08 03 A6 */	mtlr r0
/* 800410AC 0003E00C  4E 80 00 20 */	blr 

.global getToken__9CmdStreamFb
getToken__9CmdStreamFb:
/* 800410B0 0003E010  7C 08 02 A6 */	mflr r0
/* 800410B4 0003E014  90 01 00 04 */	stw r0, 4(r1)
/* 800410B8 0003E018  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800410BC 0003E01C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800410C0 0003E020  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800410C4 0003E024  7C 9E 23 78 */	mr r30, r4
/* 800410C8 0003E028  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800410CC 0003E02C  7C 7D 1B 78 */	mr r29, r3
/* 800410D0 0003E030  93 81 00 10 */	stw r28, 0x10(r1)
/* 800410D4 0003E034  80 63 01 10 */	lwz r3, 0x110(r3)
/* 800410D8 0003E038  80 1D 01 14 */	lwz r0, 0x114(r29)
/* 800410DC 0003E03C  7C 03 00 50 */	subf r0, r3, r0
/* 800410E0 0003E040  2C 00 40 00 */	cmpwi r0, 0x4000
/* 800410E4 0003E044  41 80 00 9C */	blt lbl_80041180
/* 800410E8 0003E048  80 1D 01 0C */	lwz r0, 0x10c(r29)
/* 800410EC 0003E04C  2C 00 00 00 */	cmpwi r0, 0
/* 800410F0 0003E050  41 82 00 34 */	beq lbl_80041124
/* 800410F4 0003E054  80 1D 00 04 */	lwz r0, 4(r29)
/* 800410F8 0003E058  38 A0 40 00 */	li r5, 0x4000
/* 800410FC 0003E05C  7C 60 1A 14 */	add r3, r0, r3
/* 80041100 0003E060  38 83 00 00 */	addi r4, r3, 0
/* 80041104 0003E064  38 84 40 00 */	addi r4, r4, 0x4000
/* 80041108 0003E068  4B FC 23 0D */	bl memcpy
/* 8004110C 0003E06C  80 7D 00 04 */	lwz r3, 4(r29)
/* 80041110 0003E070  38 03 C0 00 */	addi r0, r3, -16384
/* 80041114 0003E074  90 1D 00 04 */	stw r0, 4(r29)
/* 80041118 0003E078  80 7D 01 10 */	lwz r3, 0x110(r29)
/* 8004111C 0003E07C  38 03 40 00 */	addi r0, r3, 0x4000
/* 80041120 0003E080  90 1D 01 10 */	stw r0, 0x110(r29)
lbl_80041124:
/* 80041124 0003E084  80 9D 01 0C */	lwz r4, 0x10c(r29)
/* 80041128 0003E088  2C 04 00 00 */	cmpwi r4, 0
/* 8004112C 0003E08C  41 82 00 0C */	beq lbl_80041138
/* 80041130 0003E090  3B 80 40 00 */	li r28, 0x4000
/* 80041134 0003E094  48 00 00 0C */	b lbl_80041140
lbl_80041138:
/* 80041138 0003E098  3C 60 00 01 */	lis r3, 0x00008000@ha
/* 8004113C 0003E09C  3B 83 80 00 */	addi r28, r3, 0x00008000@l
lbl_80041140:
/* 80041140 0003E0A0  80 1D 01 08 */	lwz r0, 0x108(r29)
/* 80041144 0003E0A4  7C 04 00 50 */	subf r0, r4, r0
/* 80041148 0003E0A8  7C 00 E0 00 */	cmpw r0, r28
/* 8004114C 0003E0AC  40 80 00 08 */	bge lbl_80041154
/* 80041150 0003E0B0  7C 1C 03 78 */	mr r28, r0
lbl_80041154:
/* 80041154 0003E0B4  80 7D 00 00 */	lwz r3, 0(r29)
/* 80041158 0003E0B8  7F 85 E3 78 */	mr r5, r28
/* 8004115C 0003E0BC  80 1D 00 04 */	lwz r0, 4(r29)
/* 80041160 0003E0C0  81 83 00 04 */	lwz r12, 4(r3)
/* 80041164 0003E0C4  7C 80 22 14 */	add r4, r0, r4
/* 80041168 0003E0C8  81 8C 00 3C */	lwz r12, 0x3c(r12)
/* 8004116C 0003E0CC  7D 88 03 A6 */	mtlr r12
/* 80041170 0003E0D0  4E 80 00 21 */	blrl 
/* 80041174 0003E0D4  80 1D 01 0C */	lwz r0, 0x10c(r29)
/* 80041178 0003E0D8  7C 00 E2 14 */	add r0, r0, r28
/* 8004117C 0003E0DC  90 1D 01 0C */	stw r0, 0x10c(r29)
lbl_80041180:
/* 80041180 0003E0E0  57 C0 06 3F */	clrlwi. r0, r30, 0x18
/* 80041184 0003E0E4  41 82 00 CC */	beq lbl_80041250
/* 80041188 0003E0E8  48 00 00 88 */	b lbl_80041210
lbl_8004118C:
/* 8004118C 0003E0EC  38 7D 00 00 */	addi r3, r29, 0
/* 80041190 0003E0F0  38 80 00 00 */	li r4, 0
/* 80041194 0003E0F4  4B FF FA 99 */	bl fillBuffer__9CmdStreamFb
/* 80041198 0003E0F8  80 9D 01 14 */	lwz r4, 0x114(r29)
/* 8004119C 0003E0FC  80 1D 01 08 */	lwz r0, 0x108(r29)
/* 800411A0 0003E100  7C 9C 23 78 */	mr r28, r4
/* 800411A4 0003E104  48 00 00 08 */	b lbl_800411AC
lbl_800411A8:
/* 800411A8 0003E108  3B 9C 00 01 */	addi r28, r28, 1
lbl_800411AC:
/* 800411AC 0003E10C  7C 1C 00 00 */	cmpw r28, r0
/* 800411B0 0003E110  40 80 00 1C */	bge lbl_800411CC
/* 800411B4 0003E114  80 7D 00 04 */	lwz r3, 4(r29)
/* 800411B8 0003E118  7C 63 E0 AE */	lbzx r3, r3, r28
/* 800411BC 0003E11C  28 03 00 0A */	cmplwi r3, 0xa
/* 800411C0 0003E120  41 82 00 0C */	beq lbl_800411CC
/* 800411C4 0003E124  28 03 00 0D */	cmplwi r3, 0xd
/* 800411C8 0003E128  40 82 FF E0 */	bne lbl_800411A8
lbl_800411CC:
/* 800411CC 0003E12C  38 7D 00 00 */	addi r3, r29, 0
/* 800411D0 0003E130  7C 84 E0 50 */	subf r4, r4, r28
/* 800411D4 0003E134  4B FF FC F9 */	bl copyToToken__9CmdStreamFi
/* 800411D8 0003E138  80 1D 00 04 */	lwz r0, 4(r29)
/* 800411DC 0003E13C  7C 80 E2 14 */	add r4, r0, r28
/* 800411E0 0003E140  38 64 00 00 */	addi r3, r4, 0
/* 800411E4 0003E144  48 00 00 10 */	b lbl_800411F4
lbl_800411E8:
/* 800411E8 0003E148  38 84 00 01 */	addi r4, r4, 1
/* 800411EC 0003E14C  3B 9C 00 01 */	addi r28, r28, 1
/* 800411F0 0003E150  38 63 00 01 */	addi r3, r3, 1
lbl_800411F4:
/* 800411F4 0003E154  88 04 00 00 */	lbz r0, 0(r4)
/* 800411F8 0003E158  28 00 00 0A */	cmplwi r0, 0xa
/* 800411FC 0003E15C  41 82 FF EC */	beq lbl_800411E8
/* 80041200 0003E160  88 03 00 00 */	lbz r0, 0(r3)
/* 80041204 0003E164  28 00 00 0D */	cmplwi r0, 0xd
/* 80041208 0003E168  41 82 FF E0 */	beq lbl_800411E8
/* 8004120C 0003E16C  93 9D 01 14 */	stw r28, 0x114(r29)
lbl_80041210:
/* 80041210 0003E170  80 7D 00 04 */	lwz r3, 4(r29)
/* 80041214 0003E174  80 1D 01 14 */	lwz r0, 0x114(r29)
/* 80041218 0003E178  7C 63 02 14 */	add r3, r3, r0
/* 8004121C 0003E17C  88 03 00 00 */	lbz r0, 0(r3)
/* 80041220 0003E180  28 00 00 23 */	cmplwi r0, 0x23
/* 80041224 0003E184  41 82 00 18 */	beq lbl_8004123C
/* 80041228 0003E188  28 00 00 2F */	cmplwi r0, 0x2f
/* 8004122C 0003E18C  40 82 00 18 */	bne lbl_80041244
/* 80041230 0003E190  88 03 00 01 */	lbz r0, 1(r3)
/* 80041234 0003E194  28 00 00 2F */	cmplwi r0, 0x2f
/* 80041238 0003E198  40 82 00 0C */	bne lbl_80041244
lbl_8004123C:
/* 8004123C 0003E19C  38 00 00 01 */	li r0, 1
/* 80041240 0003E1A0  48 00 00 08 */	b lbl_80041248
lbl_80041244:
/* 80041244 0003E1A4  38 00 00 00 */	li r0, 0
lbl_80041248:
/* 80041248 0003E1A8  54 00 06 3F */	clrlwi. r0, r0, 0x18
/* 8004124C 0003E1AC  40 82 FF 40 */	bne lbl_8004118C
lbl_80041250:
/* 80041250 0003E1B0  80 1D 01 14 */	lwz r0, 0x114(r29)
/* 80041254 0003E1B4  3B C0 00 00 */	li r30, 0
/* 80041258 0003E1B8  80 7D 00 04 */	lwz r3, 4(r29)
/* 8004125C 0003E1BC  7C 1F 03 78 */	mr r31, r0
/* 80041260 0003E1C0  7C 03 00 AE */	lbzx r0, r3, r0
/* 80041264 0003E1C4  28 00 00 22 */	cmplwi r0, 0x22
/* 80041268 0003E1C8  41 82 00 0C */	beq lbl_80041274
/* 8004126C 0003E1CC  28 00 00 27 */	cmplwi r0, 0x27
/* 80041270 0003E1D0  40 82 00 18 */	bne lbl_80041288
lbl_80041274:
/* 80041274 0003E1D4  80 7D 01 14 */	lwz r3, 0x114(r29)
/* 80041278 0003E1D8  3B C0 00 01 */	li r30, 1
/* 8004127C 0003E1DC  3B FF 00 01 */	addi r31, r31, 1
/* 80041280 0003E1E0  38 03 00 01 */	addi r0, r3, 1
/* 80041284 0003E1E4  90 1D 01 14 */	stw r0, 0x114(r29)
lbl_80041288:
/* 80041288 0003E1E8  57 DC 06 3E */	clrlwi r28, r30, 0x18
/* 8004128C 0003E1EC  48 00 00 08 */	b lbl_80041294
lbl_80041290:
/* 80041290 0003E1F0  3B FF 00 01 */	addi r31, r31, 1
lbl_80041294:
/* 80041294 0003E1F4  28 1C 00 00 */	cmplwi r28, 0
/* 80041298 0003E1F8  41 82 00 28 */	beq lbl_800412C0
/* 8004129C 0003E1FC  80 7D 00 04 */	lwz r3, 4(r29)
/* 800412A0 0003E200  38 00 00 00 */	li r0, 0
/* 800412A4 0003E204  7C 63 F8 AE */	lbzx r3, r3, r31
/* 800412A8 0003E208  28 03 00 22 */	cmplwi r3, 0x22
/* 800412AC 0003E20C  41 82 00 30 */	beq lbl_800412DC
/* 800412B0 0003E210  28 03 00 27 */	cmplwi r3, 0x27
/* 800412B4 0003E214  41 82 00 28 */	beq lbl_800412DC
/* 800412B8 0003E218  38 00 00 01 */	li r0, 1
/* 800412BC 0003E21C  48 00 00 20 */	b lbl_800412DC
lbl_800412C0:
/* 800412C0 0003E220  80 9D 00 04 */	lwz r4, 4(r29)
/* 800412C4 0003E224  7F A3 EB 78 */	mr r3, r29
/* 800412C8 0003E228  7C 84 F8 AE */	lbzx r4, r4, r31
/* 800412CC 0003E22C  4B FF FA 4D */	bl whiteSpace__9CmdStreamFc
/* 800412D0 0003E230  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 800412D4 0003E234  7C 00 00 34 */	cntlzw r0, r0
/* 800412D8 0003E238  54 00 D9 7E */	srwi r0, r0, 5
lbl_800412DC:
/* 800412DC 0003E23C  54 00 06 3F */	clrlwi. r0, r0, 0x18
/* 800412E0 0003E240  40 82 FF B0 */	bne lbl_80041290
/* 800412E4 0003E244  80 1D 01 14 */	lwz r0, 0x114(r29)
/* 800412E8 0003E248  38 80 00 00 */	li r4, 0
/* 800412EC 0003E24C  7C 00 F8 51 */	subf. r0, r0, r31
/* 800412F0 0003E250  7C 09 03 A6 */	mtctr r0
/* 800412F4 0003E254  40 81 00 30 */	ble lbl_80041324
lbl_800412F8:
/* 800412F8 0003E258  80 1D 01 14 */	lwz r0, 0x114(r29)
/* 800412FC 0003E25C  80 7D 00 04 */	lwz r3, 4(r29)
/* 80041300 0003E260  7C 00 22 14 */	add r0, r0, r4
/* 80041304 0003E264  7C 63 00 AE */	lbzx r3, r3, r0
/* 80041308 0003E268  28 03 00 09 */	cmplwi r3, 9
/* 8004130C 0003E26C  40 82 00 08 */	bne lbl_80041314
/* 80041310 0003E270  38 60 00 20 */	li r3, 0x20
lbl_80041314:
/* 80041314 0003E274  38 04 00 08 */	addi r0, r4, 8
/* 80041318 0003E278  7C 7D 01 AE */	stbx r3, r29, r0
/* 8004131C 0003E27C  38 84 00 01 */	addi r4, r4, 1
/* 80041320 0003E280  42 00 FF D8 */	bdnz lbl_800412F8
lbl_80041324:
/* 80041324 0003E284  7C 7D 22 14 */	add r3, r29, r4
/* 80041328 0003E288  38 80 00 00 */	li r4, 0
/* 8004132C 0003E28C  57 C0 06 3F */	clrlwi. r0, r30, 0x18
/* 80041330 0003E290  98 83 00 08 */	stb r4, 8(r3)
/* 80041334 0003E294  41 82 00 18 */	beq lbl_8004134C
/* 80041338 0003E298  80 1D 01 14 */	lwz r0, 0x114(r29)
/* 8004133C 0003E29C  7C 00 F8 50 */	subf r0, r0, r31
/* 80041340 0003E2A0  7C 7D 02 14 */	add r3, r29, r0
/* 80041344 0003E2A4  98 83 00 08 */	stb r4, 8(r3)
/* 80041348 0003E2A8  3B FF 00 01 */	addi r31, r31, 1
lbl_8004134C:
/* 8004134C 0003E2AC  80 9D 01 08 */	lwz r4, 0x108(r29)
/* 80041350 0003E2B0  48 00 00 08 */	b lbl_80041358
lbl_80041354:
/* 80041354 0003E2B4  3B FF 00 01 */	addi r31, r31, 1
lbl_80041358:
/* 80041358 0003E2B8  7C 1F 20 00 */	cmpw r31, r4
/* 8004135C 0003E2BC  40 80 00 50 */	bge lbl_800413AC
/* 80041360 0003E2C0  80 7D 00 04 */	lwz r3, 4(r29)
/* 80041364 0003E2C4  7C 63 F8 AE */	lbzx r3, r3, r31
/* 80041368 0003E2C8  28 03 00 00 */	cmplwi r3, 0
/* 8004136C 0003E2CC  41 82 00 2C */	beq lbl_80041398
/* 80041370 0003E2D0  28 03 00 0D */	cmplwi r3, 0xd
/* 80041374 0003E2D4  41 82 00 24 */	beq lbl_80041398
/* 80041378 0003E2D8  38 03 FF F7 */	addi r0, r3, -9
/* 8004137C 0003E2DC  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 80041380 0003E2E0  28 00 00 01 */	cmplwi r0, 1
/* 80041384 0003E2E4  40 81 00 14 */	ble lbl_80041398
/* 80041388 0003E2E8  28 03 00 20 */	cmplwi r3, 0x20
/* 8004138C 0003E2EC  41 82 00 0C */	beq lbl_80041398
/* 80041390 0003E2F0  28 03 00 2C */	cmplwi r3, 0x2c
/* 80041394 0003E2F4  40 82 00 0C */	bne lbl_800413A0
lbl_80041398:
/* 80041398 0003E2F8  38 00 00 01 */	li r0, 1
/* 8004139C 0003E2FC  48 00 00 08 */	b lbl_800413A4
lbl_800413A0:
/* 800413A0 0003E300  38 00 00 00 */	li r0, 0
lbl_800413A4:
/* 800413A4 0003E304  54 00 06 3F */	clrlwi. r0, r0, 0x18
/* 800413A8 0003E308  40 82 FF AC */	bne lbl_80041354
lbl_800413AC:
/* 800413AC 0003E30C  93 FD 01 14 */	stw r31, 0x114(r29)
/* 800413B0 0003E310  38 7D 00 08 */	addi r3, r29, 8
/* 800413B4 0003E314  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800413B8 0003E318  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800413BC 0003E31C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800413C0 0003E320  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800413C4 0003E324  83 81 00 10 */	lwz r28, 0x10(r1)
/* 800413C8 0003E328  38 21 00 20 */	addi r1, r1, 0x20
/* 800413CC 0003E32C  7C 08 03 A6 */	mtlr r0
/* 800413D0 0003E330  4E 80 00 20 */	blr 

.global isToken__9CmdStreamFPc
isToken__9CmdStreamFPc:
/* 800413D4 0003E334  7C 08 02 A6 */	mflr r0
/* 800413D8 0003E338  90 01 00 04 */	stw r0, 4(r1)
/* 800413DC 0003E33C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800413E0 0003E340  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800413E4 0003E344  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800413E8 0003E348  3B C4 00 00 */	addi r30, r4, 0
/* 800413EC 0003E34C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800413F0 0003E350  3B A3 00 00 */	addi r29, r3, 0
/* 800413F4 0003E354  38 7D 00 08 */	addi r3, r29, 8
/* 800413F8 0003E358  48 1D 80 15 */	bl strlen
/* 800413FC 0003E35C  28 03 00 00 */	cmplwi r3, 0
/* 80041400 0003E360  41 82 00 20 */	beq lbl_80041420
/* 80041404 0003E364  7F C3 F3 78 */	mr r3, r30
/* 80041408 0003E368  48 1D 80 05 */	bl strlen
/* 8004140C 0003E36C  3B E3 00 00 */	addi r31, r3, 0
/* 80041410 0003E370  38 7D 00 08 */	addi r3, r29, 8
/* 80041414 0003E374  48 1D 7F F9 */	bl strlen
/* 80041418 0003E378  7C 03 F8 40 */	cmplw r3, r31
/* 8004141C 0003E37C  41 82 00 0C */	beq lbl_80041428
lbl_80041420:
/* 80041420 0003E380  38 60 00 00 */	li r3, 0
/* 80041424 0003E384  48 00 00 48 */	b lbl_8004146C
lbl_80041428:
/* 80041428 0003E388  3B FE 00 00 */	addi r31, r30, 0
/* 8004142C 0003E38C  3B C0 00 00 */	li r30, 0
/* 80041430 0003E390  48 00 00 28 */	b lbl_80041458
lbl_80041434:
/* 80041434 0003E394  38 7E 00 08 */	addi r3, r30, 8
/* 80041438 0003E398  88 1F 00 00 */	lbz r0, 0(r31)
/* 8004143C 0003E39C  7C 7D 18 AE */	lbzx r3, r29, r3
/* 80041440 0003E3A0  7C 03 00 40 */	cmplw r3, r0
/* 80041444 0003E3A4  41 82 00 0C */	beq lbl_80041450
/* 80041448 0003E3A8  38 60 00 00 */	li r3, 0
/* 8004144C 0003E3AC  48 00 00 20 */	b lbl_8004146C
lbl_80041450:
/* 80041450 0003E3B0  3B DE 00 01 */	addi r30, r30, 1
/* 80041454 0003E3B4  3B FF 00 01 */	addi r31, r31, 1
lbl_80041458:
/* 80041458 0003E3B8  38 7D 00 08 */	addi r3, r29, 8
/* 8004145C 0003E3BC  48 1D 7F B1 */	bl strlen
/* 80041460 0003E3C0  7C 1E 18 00 */	cmpw r30, r3
/* 80041464 0003E3C4  41 80 FF D0 */	blt lbl_80041434
/* 80041468 0003E3C8  38 60 00 01 */	li r3, 1
lbl_8004146C:
/* 8004146C 0003E3CC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80041470 0003E3D0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80041474 0003E3D4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80041478 0003E3D8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004147C 0003E3DC  38 21 00 20 */	addi r1, r1, 0x20
/* 80041480 0003E3E0  7C 08 03 A6 */	mtlr r0
/* 80041484 0003E3E4  4E 80 00 20 */	blr 

.global endOfSection__9CmdStreamFv
endOfSection__9CmdStreamFv:
/* 80041488 0003E3E8  7C 08 02 A6 */	mflr r0
/* 8004148C 0003E3EC  90 01 00 04 */	stw r0, 4(r1)
/* 80041490 0003E3F0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80041494 0003E3F4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80041498 0003E3F8  7C 7F 1B 78 */	mr r31, r3
/* 8004149C 0003E3FC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800414A0 0003E400  80 63 01 10 */	lwz r3, 0x110(r3)
/* 800414A4 0003E404  80 1F 01 14 */	lwz r0, 0x114(r31)
/* 800414A8 0003E408  7C 03 00 50 */	subf r0, r3, r0
/* 800414AC 0003E40C  2C 00 40 00 */	cmpwi r0, 0x4000
/* 800414B0 0003E410  41 80 00 9C */	blt lbl_8004154C
/* 800414B4 0003E414  80 1F 01 0C */	lwz r0, 0x10c(r31)
/* 800414B8 0003E418  2C 00 00 00 */	cmpwi r0, 0
/* 800414BC 0003E41C  41 82 00 34 */	beq lbl_800414F0
/* 800414C0 0003E420  80 1F 00 04 */	lwz r0, 4(r31)
/* 800414C4 0003E424  38 A0 40 00 */	li r5, 0x4000
/* 800414C8 0003E428  7C 60 1A 14 */	add r3, r0, r3
/* 800414CC 0003E42C  38 83 00 00 */	addi r4, r3, 0
/* 800414D0 0003E430  38 84 40 00 */	addi r4, r4, 0x4000
/* 800414D4 0003E434  4B FC 1F 41 */	bl memcpy
/* 800414D8 0003E438  80 7F 00 04 */	lwz r3, 4(r31)
/* 800414DC 0003E43C  38 03 C0 00 */	addi r0, r3, -16384
/* 800414E0 0003E440  90 1F 00 04 */	stw r0, 4(r31)
/* 800414E4 0003E444  80 7F 01 10 */	lwz r3, 0x110(r31)
/* 800414E8 0003E448  38 03 40 00 */	addi r0, r3, 0x4000
/* 800414EC 0003E44C  90 1F 01 10 */	stw r0, 0x110(r31)
lbl_800414F0:
/* 800414F0 0003E450  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 800414F4 0003E454  2C 04 00 00 */	cmpwi r4, 0
/* 800414F8 0003E458  41 82 00 0C */	beq lbl_80041504
/* 800414FC 0003E45C  3B C0 40 00 */	li r30, 0x4000
/* 80041500 0003E460  48 00 00 0C */	b lbl_8004150C
lbl_80041504:
/* 80041504 0003E464  3C 60 00 01 */	lis r3, 0x00008000@ha
/* 80041508 0003E468  3B C3 80 00 */	addi r30, r3, 0x00008000@l
lbl_8004150C:
/* 8004150C 0003E46C  80 1F 01 08 */	lwz r0, 0x108(r31)
/* 80041510 0003E470  7C 04 00 50 */	subf r0, r4, r0
/* 80041514 0003E474  7C 00 F0 00 */	cmpw r0, r30
/* 80041518 0003E478  40 80 00 08 */	bge lbl_80041520
/* 8004151C 0003E47C  7C 1E 03 78 */	mr r30, r0
lbl_80041520:
/* 80041520 0003E480  80 7F 00 00 */	lwz r3, 0(r31)
/* 80041524 0003E484  7F C5 F3 78 */	mr r5, r30
/* 80041528 0003E488  80 1F 00 04 */	lwz r0, 4(r31)
/* 8004152C 0003E48C  81 83 00 04 */	lwz r12, 4(r3)
/* 80041530 0003E490  7C 80 22 14 */	add r4, r0, r4
/* 80041534 0003E494  81 8C 00 3C */	lwz r12, 0x3c(r12)
/* 80041538 0003E498  7D 88 03 A6 */	mtlr r12
/* 8004153C 0003E49C  4E 80 00 21 */	blrl 
/* 80041540 0003E4A0  80 1F 01 0C */	lwz r0, 0x10c(r31)
/* 80041544 0003E4A4  7C 00 F2 14 */	add r0, r0, r30
/* 80041548 0003E4A8  90 1F 01 0C */	stw r0, 0x10c(r31)
lbl_8004154C:
/* 8004154C 0003E4AC  80 7F 00 04 */	lwz r3, 4(r31)
/* 80041550 0003E4B0  80 1F 01 14 */	lwz r0, 0x114(r31)
/* 80041554 0003E4B4  7C 03 00 AE */	lbzx r0, r3, r0
/* 80041558 0003E4B8  28 00 00 7D */	cmplwi r0, 0x7d
/* 8004155C 0003E4BC  40 82 00 0C */	bne lbl_80041568
/* 80041560 0003E4C0  38 60 00 01 */	li r3, 1
/* 80041564 0003E4C4  48 00 00 08 */	b lbl_8004156C
lbl_80041568:
/* 80041568 0003E4C8  38 60 00 00 */	li r3, 0
lbl_8004156C:
/* 8004156C 0003E4CC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80041570 0003E4D0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80041574 0003E4D4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80041578 0003E4D8  38 21 00 18 */	addi r1, r1, 0x18
/* 8004157C 0003E4DC  7C 08 03 A6 */	mtlr r0
/* 80041580 0003E4E0  4E 80 00 20 */	blr 
