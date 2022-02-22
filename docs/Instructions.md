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

- There a fundamental difference between `Immediate` and `Absolute` mode. <br>
	- `Immediate¹` The values required to execute the instruction are placed next to the opcode itself in memory
	- `Absolute` The values required to execute the instruction are placed elsewhere in memory, and the next bytes only says where

¹ The `Immediate` mode can have 3 or 4 bytes in size, while the `Absolute` can only have 4 bytes in size.

## Table

