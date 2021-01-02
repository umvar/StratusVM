#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/Assembler.h"

stream* stream_new(char* filename) {
    stream* stream = malloc(sizeof(stream));
    stream->filename = filename;
    stream_assemble(stream);
    return stream;
}

void stream_pushByte(stream* stream, char byte) {
    stream->bytecode[stream->index] = byte;
    stream->index++;
}

char stream_peek(stream* stream) {
    stream->symbol = fgetc(stream->input);
    return stream->symbol;
}

char stream_checkEOF(stream* stream) {
    return stream->eof;
}

void stream_parseMnemonic(stream* stream) {
    while (stream_peek(stream) != ' ') {
        if (stream->symbol == '\n')
            break;
        if (stream->symbol == EOF) {
            stream->eof = 1;
            break;
        }
        stream->mnemonic[stream->pos] = stream->symbol;
        stream->pos++;
    }
    stream->pos = 0;
}

void stream_parseOperand(stream* stream) {
    while (stream_peek(stream) != '\n') {
        stream->operand[stream->pos] = stream->symbol;
        stream->pos++;
    }
    stream->pos = 0;
}

void stream_matchInstruction(stream* stream) {
    for (int i = 0; i < sizeof(ops)/sizeof(optable); i++) {
        if (!strcmp(stream->mnemonic, ops[i].mnemonic)) {
            stream->format = ops[i].format;
            stream->opcode = ops[i].opcode;
        }
    }
}

void stream_clearInstruction(stream* stream) {
    memset(stream->mnemonic, '\0', strlen(stream->mnemonic));
    memset(stream->operand, '\0', strlen(stream->operand));
}

void stream_assemble(stream* stream) {
    stream->input = fopen(stream->filename, "r");
    
    while (1) {
        stream_parseMnemonic(stream);
        if (stream_checkEOF(stream))
          break;
        stream_matchInstruction(stream);
        stream_pushByte(stream, stream->opcode);
        if (stream->format == iB) {
            stream_parseOperand(stream);
            stream_pushByte(stream, (char)atoi(stream->operand));
        }
        stream_clearInstruction(stream);
    }
    fclose(stream->input);
}