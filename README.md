# IASpie v1.0.0
Translator of IASlang mnemonic codes into opcodes that run on the IAS computer.

| Opcode | Instruction Type | Mnemonic | Operation |
| :---: | :---: | :---: | :---: |
| 0x00 | Exit | HALT | - |
| 0x01 | Data Transfer | LDM mem | LOAD M(x) |
| 0x02 | Data Transfer | LDMn mem | LOAD -M(x) |
| 0x03 | Data Transfer | LDMa mem | LOAD \|M(x)\| |
| 0x04 | Data Transfer | LDMan mem | LOAD -\|M(x)\| |
| 0x05 | Arithmetic | ADD mem | ADD M(x) |
| 0x06 | Arithmetic | SUB mem | SUB M(x) |
| 0x07 | Arithmetic | ADDa mem | ADD \|M(x)\| |
| 0x08 | Arithmetic | SUBa mem | SUB \|M(x)\| |
| 0x09 | Data Transfer | LDA mem | LOAD MQ, M(x) |
| 0x0A | Data Transfer | LDQ | LOAD MQ |
| 0x0B | Arithmetic | MUL mem | MUL M(x) |
| 0x0C | Arithmetic | DIV mem | DIV M(x) |
| 0x0D | Unconditional Branch | JMPT mem | JUMP M(x, 0:19) |
| 0x0E | Unconditional Branch | JMPB mem | JUMP M(x, 20:39) |
| 0x0F | Conditional Branch | JMPTs mem | JUMP+ M(x, 20:39) |
| 0x10 | Conditional Branch | JMPBs mem | JUMP+ M(x, 20:39) |
| 0x12 | Address Modify | RPLT mem | STOR M(x, 8:19) |
| 0x13 | Address Modify | RPLB mem | STOR M(x, 28:39) |
| 0x14 | Arithmetic | LSH | LSH |
| 0x15 | Arithmetic | RSH | RSH |
| 0x21 | Data Transfer | STR mem | STOR M(x) |
