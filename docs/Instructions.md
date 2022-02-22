# Fantasy Console - Instructions

1. [Instructions](#instructions)
	- [Address Modes](#address)
	- [Table](#table)

## Address Mode

For now the **CPU** supports a total of _3 Address Modes_, these beign `Implied, Immediate and Absolute`, the mode usually change the size of the instruction itself on the memory, for example:

| Mode       | Assembly        | Memory        |
|------------|-----------------|---------------|
|`Implied`   | `nop`           | `00`          |
|`Immediate` | `ldi r1, $ABCD` | `01 01 CD AB` |
|`Absolute`  | `lda r1, $FFFE` | `02 01 FE FF` |

- There a fundamental difference between `Immediate` and `Absolute` mode.
	- `Immediate¹` The values required to execute the instruction are placed next to the opcode itself in memory
	- `Absolute` The values required to execute the instruction are placed elsewhere in memory, and the next bytes only says where

¹ The `Immediate` mode can have 2, 3 or 4 bytes in size, while the `Absolute` can only have 3 or 4 bytes in size.

## Table

|Opcode |Mnemonic |Size |Mode       |Assembly         |Memory        |
|-------|---------|-----|-----------|-----------------|--------------|
|`0x00` |`NOP`    | 1   |`Implied`  |`NOP`            |`00`          |
|`0x01` |`LDI`    | 4   |`Immediate`|`LDI r1, $ABCD`  |`01 01 CD AB` |
|`0x02` |`LDA`    | 4   |`Absolute` |`LDA r2, [$FFFE]`|`02 01 FE FF` |
|`0x03` |`LDR`    | 3   |`Immediate`|`LDR r1, r2`     |`03 01 02`    |
|`0x04` |`LDS`    | 2   |`Immediate`|`LDS r3`         |`04 03`       |
|`0x05` |`STR`    | 4   |`Absolute` |`STR [$2000], r3`|`05 00 20 03` |
|`0x06` |`STS`    | 3   |`Absolute` |`STS [$3000]`    |`06 00 30`    |
|`0x07` |`INC`    | 2   |`Immediate`|`INC r1`         |`07 01`       |
|`0x08` |`DEC`    | 2   |`Immediate`|`DEC r1`         |`08 01`       |
|`0x09` |`SHL`    | 3   |`Immediate`|`SHL r1, 1`      |`09 01 01`    |
|`0x0A` |`SHR`    | 3   |`Immediate`|`SHR r1, 1`      |`0A 01 01`    |
|`0x0B` |`AND`    | 4   |`Immediate`|`AND r1, $FF00`  |`0B 01 00 FF` |
|`0x0C` |`BOR`    | 4   |`Immediate`|`BOR r1, $FF00`  |`0C 01 00 FF` |
|`0x0D` |`XOR`    | 4   |`Immediate`|`XOR r1, $FF00`  |`0D 01 00 FF` |
|`0x0E` |`NOT`    | 2   |`Immediate`|`NOT r1`         |`0E 01`       |
|`0x0F` |`PSI`    | 3   |`Immediate`|`PSI $ABCD`      |`0F CD AB`    |
|`0x10` |`PSA`    | 4   |`Absolute` |`PSA [$ABCD]`    |`10 CD AB`    |
|`0x11` |`PSR`    | 2   |`Immediate`|`PSR r1`         |`11 01`       |
|`0x12` |`POP`    | 3   |`Immediate`|`POP r1`         |`12 01`       |
|`0x13` |`ADI`    | 4   |`Immediate`|`ADI r1, $0010`  |`13 01 10 00` |
|`0x14` |`ADA`    | 4   |`Absolute` |`ADA r1, [$FDFF]`|`14 01 FF FD` |
|`0x15` |`ADR`    | 3   |`Immediate`|`ADR r1, r2`     |`15 01 02`    |
|`0x16` |`ADR`    | 2   |`Immediate`|`ADS r1`         |`16 01`       |
|`0x17` |`SUI`    | 4   |`Immediate`|`SUI r1, $0010`  |`17 01 10 00` |
|`0x18` |`SUA`    | 4   |`Absolute` |`SUA r1, [$DDEF]`|`18 01 EF DD` |
|`0x19` |`SUR`    | 3   |`Immediate`|`SUR r1, r2`     |`19 01 02`    |
|`0x1A` |`SUS`    | 2   |`Immediate`|`SUS r1`         |`1A 01`       |
|`0x1B` |`MUI`    | 4   |`Immediate`|`MUI r1, $0015`  |`1B 01 15 00` |
|`0x1C` |`MUA`    | 4   |`Absolute` |`MUA r1, [$AABB]`|`1C 01 BB AA` |
|`0x1D` |`MUR`    | 3   |`Immediate`|`MUR r1, r2`     |`1D 01 02`    |
|`0x1E` |`MUS`    | 3   |`Immediate`|`MUS r1`         |`1E 01`       |
|`0x1F` |`DIV`    | 4   |`Immediate`|`DIV r1, $0010`  |`1F 01 10 00` |
|`0x20` |`DIA`    | 4   |`Absolute` |`DUA r1, [$FFFE]`|`20 01 FE FF` |
|`0x21` |`DIR`    | 3   |`Immediate`|`DIR r1, r2`     |`21 01 02`    |
|`0x22` |`DIS`    | 2   |`Immediate`|`DIS r1`         |`22 01`       |
|`0x23` |`MOI`    | 4   |`Immediate`|`MOI r1, $0010`  |`23 01 10 00` |
|`0x24` |`MOA`    | 4   |`Absolute` |`MOA r1, [$CCDE]`|`24 01 DE CC` |
|`0x25` |`MOR`    | 3   |`Immediate`|`MOR r1, r2`     |`25 01 02`    |
|`0x26` |`MOS`    | 2   |`Immediate`|`SUS r1`         |`26 01`       |
|`0x27` |`CMI`    | 4   |`Immediate`|`CMI r1, $0010`  |`27 01 10 00` |
|`0x28` |`CMA`    | 4   |`Absolute` |`CMA r1, [$FFFE]`|`28 01 FE FF` |
|`0x29` |`CMR`    | 3   |`Immediate`|`CMR r1, r2`     |`29 01 02`    |
|`0x2A` |`CMS`    | 2   |`Immediate`|`CMS r1`         |`2A 01`       |
|`0x2B` |`JMP`    | 3   |`Absolute` |`JMP [$FFFE]`    |`2B FE FF`    |
|`0x2C` |`JEQ`    | 3   |`Absolute` |`JEQ [$FCFF]`    |`2C FF FC`    |
|`0x2D` |`JNQ`    | 3   |`Absolute` |`JNQ [$DEFF]`    |`2D FF DE`    |
|`0x2E` |`JMC`    | 3   |`Absolute` |`JMC [$FFFE]`    |`2E FE FF`    |
|`0x2F` |`JNC`    | 3   |`Absolute` |`JNC [$EECE]`    |`2F CE EE`    |
|`0x30` |`JMO`    | 3   |`Absolute` |`JMO [$ABCD]`    |`30 CD AB`    |
|`0x31` |`JNO`    | 3   |`Absolute` |`JNO [$CCDE]`    |`31 DE CC`    |
|`0x32` |`JSR`    | 3   |`Absolute` |`JSR [$FFEF]`    |`32 EF FF`    |
|`0x33` |`RTS`    | 1   |`Implied`  |`RET`            |`33`          |
|`0x34` |`OUT`    | 2   |`Immediate`|`OUT r1`         |`34 01`       |
|`0x35` |`HLT`    | 1   |`Implied`  |`HLT`            |`35`          |
