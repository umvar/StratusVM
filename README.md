# StratusVM

*StratusVM* is a virtualized instructional model of a computer which models a von Neumann architecture computer. 

## Specification

StratusVM is a stack-based virtual machine.

### Registers
Registers are used to hold various states that cannot exist on the stack.

Register | Description
---------|-------------------------------------------------------------
IP       | Instruction Pointer
SP       | Stack Pointer
BP       | Base Pointer

### Instruction Formats
FMT     | Encoding
--------|---------------------
iA      | opcode
iB      | opcode op1

### Instruction Reference
Opcode (FMT) | Mnemonic            | Description
-------------|---------------------|------------------------------------------------------------------
0x00 (iA)    | HLT                 | exit();
0x01 (iA)    | ADD                 | x = pop(); push(pop() + x); 
0x02 (iA)    | SUB                 | x = pop(); push(pop() - x);
0x03 (iA)    | MUL                 | x = pop(); push(pop() * x);
0x04 (iA)    | DIV                 | x = pop(); push(pop() / x);
0x05 (iA)    | MOD                 | x = pop(); push(pop() % x);
0x06 (iA)    | NEG                 | push(-pop());
0x07 (iA)    | NOT                 | push(~pop());
0x08 (iA)    | OR                  | x = pop(); push(pop() \| x);
0x09 (iA)    | AND                 | x = pop(); push(pop() & x);
0x0A (iA)    | XOR                 | x = pop(); push(pop() ^ x);
0x0B (iA)    | SHL                 | x = pop(); push(pop() << x);
0x0C (iA)    | SHR                 | x = pop(); push(pop() >> x);
0x0D (iA)    | EQ                  | x = pop(); push(pop() == x);
0x0E (iA)    | NEQ                 | x = pop(); push(pop() != x);
0x0F (iA)    | LT                  | x = pop(); push(pop() < x);
0x10 (iA)    | LE                  | x = pop(); push(pop() <= x);
0x11 (iA)    | GT                  | x = pop(); push(pop() > x);
0x12 (iA)    | GE                  | x = pop(); push(pop() >= x);
0x13 (iB)    | JMP op1             | IP = op1;
0x14 (iB)    | JMPREL op1          | IP += op1;
0x15 (iB)    | JMPF op1            | if (!pop()) { IP = op1 };
0x16 (iB)    | JMPT op1            | if (pop()) { IP = op1 };
0x16 (iB)    | JMPFREL op1         | if (!pop()) { IP += op1 };
0x16 (iB)    | JMPTREL op1         | if (pop()) { IP += op1 };
0x17 (iB)    | IMM op1             | push(op1)
0x18 (iB)    | INV op1             | PUSH(BP); PUSH(IP); BP = SP; IP = op1;
0x19 (iB)    | INVREL op1          | PUSH(BP); PUSH(IP); BP = SP; IP += op1;
0x1A (iB)	 | CPY op1		       | push(BP + op1)
0x1B (iB)    | ARG op1             | args = op1
0x1C (iB)    | REP op1             | push(BP + op1, pop())
0x1D (iA)    | RET                 | x = pop(); SP = BP; IP = pop(); BP = pop(); SP -= args; push(x); 
