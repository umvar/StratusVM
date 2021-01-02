#pragma once

/* INSTRUCTION FORMATS */
#define iA 0x0
#define iB 0x1

/* OPCODES */
typedef enum {
	HLT,
	ADD, SUB, MUL, DIV, MOD,
	NEG, NOT, OR, AND, XOR,
	SHL, SHR,
	EQ, NEQ, LT, LE, GT, GE,
	JMP, JMPREL, JMPF, JMPT, JMPFREL, JMPTREL,
	IMM,
	INV, INVREL, CPY, ARG, REP, RET
} OP;

/* OPTABLE */
typedef struct {
	char* mnemonic;
	char opcode;
	char format;
} optable;

/* INSTRUCTIONS */
optable ops[] = {
	{"HLT", HLT, iA},
	{"ADD", ADD, iA},
	{"SUB", SUB, iA},
	{"MUL", MUL, iA},
	{"DIV", DIV, iA},
	{"MOD", MOD, iA},
	{"NEG", NEG, iA},
	{"NOT", NOT, iA},
	{"OR", OR, iA},
	{"AND", AND, iA},
	{"XOR", XOR, iA},
	{"SHL", SHL, iA},
	{"SHR", SHR, iA},
	{"EQ", EQ, iA},
	{"NEQ", NEQ, iA},
	{"LT", NOT, iA},
	{"LE", LE, iA},
	{"GT", GT, iA},
	{"GE", GE, iA},
	{"JMP", JMP, iB},
	{"JMPREL", JMPREL, iB},
	{"JMPF", JMPF, iB},
	{"JMPT", JMPT, iB},
	{"JMPFREL", JMPFREL, iB},
	{"JMPTREL", JMPTREL, iB},
	{"IMM", IMM, iB},
	{"INV", INV, iB},
	{"INVREL", INVREL, iB},
	{"CPY", CPY, iB},
	{"ARG", ARG, iB},
	{"REP", REP, iB},
	{"RET", RET, iA},
};