# IASpie v1.0.0
## An IAS Machine Assembler. Translates "IASlang" mnemonic codes into opcodes, executed on the IAS computer.

<p align="center">
 <a href="#objective">Objective</a> •
 <a href="#manual">Manual</a> • 
 <a href="#language">Language</a> • 
 <a href="#versions">Versions</a> • 
 <a href="#licence">Licence</a> • 
 <a href="#developer">Developer</a>
</p>

# Objective

The main objective is to facilitate learning on the subject of Computer Architecture and Organization through the use of programming for the IAS computer, using mnemonic instructions, similar to Assembly, as an introduction.

The use of the IAS computer is interesting in learning computer architectures, but its programming is complicated, mainly due to the use of numeric opcodes for this. This project brings a relatively powerful and simple assembler, which will assist in learning, through mnemonic instructions.

# Manual

<a href="https://www.ic.unicamp.br/~edson/disciplinas/mc404/2017-2s/abef/IAS-sim/">IAS Simulator</a>

| Opcode | Instruction Type | Mnemonic | Operation | Description |
| :---: | :---: | :---: | :---: | :---: |
| 0x00 | Exit | HALT | - | Halt the program execution. Will abort the simulator with "invalidInstruction" exception. |
| 0x01 | Data Transfer | LDM mem | LOAD M(x) | Load variable <i>mem</i> to <i>AC</i> register. |
| 0x02 | Data Transfer | LDMn mem | LOAD -M(x) | Load variable negative <i>mem</i> to <i>AC</i> register. | 
| 0x03 | Data Transfer | LDMa mem | LOAD \|M(x)\| | Load variable module <i>mem</i> to <i>AC</i> register. | 
| 0x04 | Data Transfer | LDMan mem | LOAD -\|M(x)\| | Load variable negative module <i>mem</i> to <i>AC</i> register. | 
| 0x05 | Arithmetic | ADD mem | ADD M(x) | Add variable <i>mem</i> to <i>AC</i> register. | 
| 0x06 | Arithmetic | SUB mem | SUB M(x) | Sub variable <i>mem</i> to <i>AC</i> register. | 
| 0x07 | Arithmetic | ADDa mem | ADD \|M(x)\| | Add the module of variable <i>mem</i> to <i>AC</i> register. | 
| 0x08 | Arithmetic | SUBa mem | SUB \|M(x)\| | Sub the module of variable <i>mem</i> to <i>AC</i> register. |
| 0x09 | Data Transfer | LDA mem | LOAD MQ, M(x) | Load variable <i>mem</i> to <i>MQ</i> register. | 
| 0x0A | Data Transfer | LDQ | LOAD MQ | Load <i>MQ</i> register to <i>AC</i> register. |
| 0x0B | Arithmetic | MUL mem | MUL M(x) | Multiply variable <i>mem</i> by <i>MQ</i> register. The most significant bit will be in AC and the least in MQ. |
| 0x0C | Arithmetic | DIV mem | DIV M(x) | Divide <i>AC</i> register by variable <i>mem</i>. The quocient will be in MQ and the remainder in AC. |
| 0x0D | Unconditional Branch | JMPT proc | JUMP M(x, 0:19) | Branch to the first instruction of the <i>proc</i> procedure. |
| 0x0E | Unconditional Branch | JMPB proc | JUMP M(x, 20:39) | Branch to the second instruction of the <i>proc</i> procedure.|
| 0x0F | Conditional Branch | JMPTs proc | JUMP+ M(x, 0:19) | Branch to the first instruction of the <i>proc</i> procedure if <i>AC</i> is nonnegative. | 
| 0x10 | Conditional Branch | JMPBs proc | JUMP+ M(x, 20:39) | Branch to the second instruction of the <i>proc</i> procedure if <i>AC</i> is nonnegative. |
| 0x12 | Address Modify | RPLT proc | STOR M(x, 8:19) | Replace the first instruction's operand, of the <i>proc</i> procedure, with the 12 rightmost bits of <i>AC</i>. |
| 0x13 | Address Modify | RPLB proc | STOR M(x, 28:39) | Replace the second instruction's operand, of the <i>proc</i> procedure, with the 12 rightmost bits of <i>AC</i>. |
| 0x14 | Arithmetic | LSH | LSH | Shift <i>AC</i> register one bit to the left. |
| 0x15 | Arithmetic | RSH | RSH | Shift <i>AC</i> register one bit to the right. |
| 0x21 | Data Transfer | STR mem | STOR M(x) | Store <i>AC</i> contents in <i>mem</i>. |


# Language
# Versions
# Licence
# Developer
