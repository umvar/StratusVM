#pragma once

#include "Instruction.h"

/* ASSEMBLER ALLOCATION */
#define BUFFER_SIZE 0x100
#define MNEOMONIC_MAX 7
#define OPERAND_MAX 3

typedef struct {
    char bytecode[BUFFER_SIZE];
    const char* filename;
    FILE* input;
	char pos;
    char symbol;
	char mnemonic[MNEOMONIC_MAX];
	char opcode;
	char operand[OPERAND_MAX];
	char format;
	char index;
	char eof; 
} stream;

/* FUNCTION PROTOTYPES */
stream* stream_new(char* filename);
void stream_pushByte(stream* stream, char byte);
char stream_peek(stream* stream);
char stream_checkEOF(stream* stream);
void stream_parseMnemonic(stream* stream);
void stream_parseOperand(stream* stream);
void stream_matchInstruction(stream* stream);
void stream_clearInstruction(stream* stream);
void stream_assemble(stream* stream);