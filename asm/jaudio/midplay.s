.include "macros.inc"
.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 8
.global CUTOFF_TO_IIR_TABLE
CUTOFF_TO_IIR_TABLE:
	.4byte 0x0F5C0A3D
	.4byte 0x46653999
	.4byte 0x103F0A28
	.4byte 0x45D73925
	.4byte 0x11220A14
	.4byte 0x454A38B0
	.4byte 0x120509FF
	.4byte 0x44BC383C
	.4byte 0x12E809EA
	.4byte 0x442E37C8
	.4byte 0x13CB09D6
	.4byte 0x43A03754
	.4byte 0x14AE09C1
	.4byte 0x431236E0
	.4byte 0x159109AC
	.4byte 0x4284366C
	.4byte 0x16740998
	.4byte 0x41F635F8
	.4byte 0x17570983
	.4byte 0x41683584
	.4byte 0x183A096E
	.4byte 0x40DA3510
	.4byte 0x191D095A
	.4byte 0x404C349C
	.4byte 0x1A000945
	.4byte 0x3FBE3427
	.4byte 0x1AE30931
	.4byte 0x3F3133B3
	.4byte 0x1BC6091C
	.4byte 0x3EA3333F
	.4byte 0x1CA90907
	.4byte 0x3E1532CB
	.4byte 0x1D8C08F3
	.4byte 0x3D873257
	.4byte 0x1E6F08DE
	.4byte 0x3CF931E3
	.4byte 0x1F5208C9
	.4byte 0x3C6B316F
	.4byte 0x203508B5
	.4byte 0x3BDD30FB
	.4byte 0x211808A0
	.4byte 0x3B4F3087
	.4byte 0x21FC088B
	.4byte 0x3AC13012
	.4byte 0x22DF0877
	.4byte 0x3A332F9E
	.4byte 0x23C20862
	.4byte 0x39A62F2A
	.4byte 0x24A5084D
	.4byte 0x39182EB6
	.4byte 0x25880839
	.4byte 0x388A2E42
	.4byte 0x266B0824
	.4byte 0x37FC2DCE
	.4byte 0x274E0810
	.4byte 0x376E2D5A
	.4byte 0x283107FB
	.4byte 0x36E02CE6
	.4byte 0x291407E6
	.4byte 0x36522C72
	.4byte 0x29F707D2
	.4byte 0x35C42BFE
	.4byte 0x2ADA07BD
	.4byte 0x35362B89
	.4byte 0x2BBD07A8
	.4byte 0x34A82B15
	.4byte 0x2CA00794
	.4byte 0x341B2AA1
	.4byte 0x2D83077F
	.4byte 0x338D2A2D
	.4byte 0x2E66076A
	.4byte 0x32FF29B9
	.4byte 0x2F490756
	.4byte 0x32712945
	.4byte 0x302C0741
	.4byte 0x31E328D1
	.4byte 0x310F072D
	.4byte 0x3155285D
	.4byte 0x31F20718
	.4byte 0x30C727E9
	.4byte 0x32D50703
	.4byte 0x30392775
	.4byte 0x33B806EF
	.4byte 0x2FAB2700
	.4byte 0x349C06DA
	.4byte 0x2F1D268C
	.4byte 0x357F06C5
	.4byte 0x2E8F2618
	.4byte 0x366206B1
	.4byte 0x2E0225A4
	.4byte 0x3745069C
	.4byte 0x2D742530
	.4byte 0x38280687
	.4byte 0x2CE624BC
	.4byte 0x390B0673
	.4byte 0x2C582448
	.4byte 0x39EE065E
	.4byte 0x2BCA23D4
	.4byte 0x3AD10649
	.4byte 0x2B3C2360
	.4byte 0x3BB40635
	.4byte 0x2AAE22EB
	.4byte 0x3C970620
	.4byte 0x2A202277
	.4byte 0x3D7A060C
	.4byte 0x29922203
	.4byte 0x3E5D05F7
	.4byte 0x2904218F
	.4byte 0x3F4005E2
	.4byte 0x2877211B
	.4byte 0x402305CE
	.4byte 0x27E920A7
	.4byte 0x410605B9
	.4byte 0x275B2033
	.4byte 0x41E905A4
	.4byte 0x26CD1FBF
	.4byte 0x42CC0590
	.4byte 0x263F1F4B
	.4byte 0x43AF057B
	.4byte 0x25B11ED7
	.4byte 0x44920566
	.4byte 0x25231E62
	.4byte 0x45750552
	.4byte 0x24951DEE
	.4byte 0x4658053D
	.4byte 0x24071D7A
	.4byte 0x473B0529
	.4byte 0x23791D06
	.4byte 0x481F0514
	.4byte 0x22EB1C92
	.4byte 0x490204FF
	.4byte 0x225E1C1E
	.4byte 0x49E504EB
	.4byte 0x21D01BAA
	.4byte 0x4AC804D6
	.4byte 0x21421B36
	.4byte 0x4BAB04C1
	.4byte 0x20B41AC2
	.4byte 0x4C8E04AD
	.4byte 0x20261A4E
	.4byte 0x4D710498
	.4byte 0x1F9819D9
	.4byte 0x4E540483
	.4byte 0x1F0A1965
	.4byte 0x4F37046F
	.4byte 0x1E7C18F1
	.4byte 0x501A045A
	.4byte 0x1DEE187D
	.4byte 0x50FD0445
	.4byte 0x1D601809
	.4byte 0x51E00431
	.4byte 0x1CD31795
	.4byte 0x52C3041C
	.4byte 0x1C451721
	.4byte 0x53A60408
	.4byte 0x1BB716AD
	.4byte 0x548903F3
	.4byte 0x1B291639
	.4byte 0x556C03DE
	.4byte 0x1A9B15C4
	.4byte 0x564F03CA
	.4byte 0x1A0D1550
	.4byte 0x573203B5
	.4byte 0x197F14DC
	.4byte 0x581503A0
	.4byte 0x18F11468
	.4byte 0x58F8038C
	.4byte 0x186313F4
	.4byte 0x59DB0377
	.4byte 0x17D51380
	.4byte 0x5ABF0362
	.4byte 0x1747130C
	.4byte 0x5BA2034E
	.4byte 0x16BA1298
	.4byte 0x5C850339
	.4byte 0x162C1224
	.4byte 0x5D680324
	.4byte 0x159E11B0
	.4byte 0x5E4B0310
	.4byte 0x1510113B
	.4byte 0x5F2E02FB
	.4byte 0x148210C7
	.4byte 0x601102E7
	.4byte 0x13F41053
	.4byte 0x60F402D2
	.4byte 0x13660FDF
	.4byte 0x61D702BD
	.4byte 0x12D80F6B
	.4byte 0x62BA02A9
	.4byte 0x124A0EF7
	.4byte 0x639D0294
	.4byte 0x11BC0E83
	.4byte 0x6480027F
	.4byte 0x112F0E0F
	.4byte 0x6563026B
	.4byte 0x10A10D9B
	.4byte 0x66460256
	.4byte 0x10130D27
	.4byte 0x67290241
	.4byte 0x0F850CB2
	.4byte 0x680C022D
	.4byte 0x0EF70C3E
	.4byte 0x68EF0218
	.4byte 0x0E690BCA
	.4byte 0x69D20204
	.4byte 0x0DDB0B56
	.4byte 0x6AB501EF
	.4byte 0x0D4D0AE2
	.4byte 0x6B9801DA
	.4byte 0x0CBF0A6E
	.4byte 0x6C7B01C6
	.4byte 0x0C3109FA
	.4byte 0x6D5F01B1
	.4byte 0x0BA30986
	.4byte 0x6E42019C
	.4byte 0x0B160912
	.4byte 0x6F250188
	.4byte 0x0A88089D
	.4byte 0x70080173
	.4byte 0x09FA0829
	.4byte 0x70EB015E
	.4byte 0x096C07B5
	.4byte 0x71CE014A
	.4byte 0x08DE0741
	.4byte 0x72B10135
	.4byte 0x085006CD
	.4byte 0x73940120
	.4byte 0x07C20659
	.4byte 0x7477010C
	.4byte 0x073405E5
	.4byte 0x755A00F7
	.4byte 0x06A60571
	.4byte 0x763D00E3
	.4byte 0x061804FD
	.4byte 0x772000CE
	.4byte 0x058B0489
	.4byte 0x780300B9
	.4byte 0x04FD0414
	.4byte 0x78E600A5
	.4byte 0x046F03A0
	.4byte 0x79C90090
	.4byte 0x03E1032C
	.4byte 0x7AAC007B
	.4byte 0x035302B8
	.4byte 0x7B8F0067
	.4byte 0x02C50244
	.4byte 0x7C720052
	.4byte 0x023701D0
	.4byte 0x7D55003D
	.4byte 0x01A9015C
	.4byte 0x7E380029
	.4byte 0x011B00E8
	.4byte 0x7F1B0014
	.4byte 0x008D0074
	.4byte 0x7FFF0000
	.4byte 0x00000000
