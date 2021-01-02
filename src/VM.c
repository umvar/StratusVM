#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/VM.h"
#include "Assembler.c"

VM* VM_new(char* filename) {
    VM* vm = malloc(sizeof(vm));
    vm->regs[BP] = 0;
    vm->regs[SP] = 0;
    vm->regs[IP] = 0;
    if (filename)
        VM_loadProgram(vm, filename);
}

void VM_free(VM* vm) {
    free(vm);
}

void VM_push(VM* vm, char val) {
    vm->stack[vm->regs[SP]] = val;
    vm->regs[SP]++;
}

char VM_pop(VM* vm) {
    vm->regs[SP]--;
    char val = vm->stack[vm->regs[SP]];
    return val;
}

void VM_set(VM* vm, char index, char val) {
    vm->stack[index] = val;
}

char VM_get(VM* vm, char index) {
    char val = vm->stack[index];
    return val;
}

char VM_fetch(VM* vm) {
    char val = vm->memory[vm->regs[IP]];
    vm->regs[IP]++;
    return val;
}

void VM_step(VM* vm) {
    char op = VM_fetch(vm);
    char a, b; 

    switch (op) {
    case HLT:
        vm->isRunning = 0;
        //exit(EXIT_SUCCESS);
        break;
    case ADD:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a + b);
        break;
    case SUB:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a - b);
        break;
    case MUL:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a * b);
        break;
    case DIV:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a / b);
        break;
    case MOD:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a % b);
        break;
    case NEG:
        a = VM_pop(vm);
        VM_push(vm, -a);
        break;
    case NOT:
        a = VM_pop(vm);
        VM_push(vm, ~a);
        break;
    case OR:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a | b);
        break;
    case XOR:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a ^ b);
        break;
    case SHL:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a << b);
        break;
    case SHR:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a >> b);
        break;
    case EQ:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a == b);
        break;
    case NEQ:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a != b);
        break;
    case LT:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a < b);
        break;
    case LE:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a <= b);
        break;
    case GT:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a > b);
        break;
    case GE:
        b = VM_pop(vm);
        a = VM_pop(vm);
        VM_push(vm, a >= b);
        break;
    case JMP:
        vm->regs[IP] = VM_fetch(vm);
        break;
    case JMPREL:
        vm->regs[IP] += VM_fetch(vm);
        break;
    case JMPF:
        a = VM_pop(vm);
        if (!a)
            vm->regs[IP] = VM_fetch(vm);
        break;
    case JMPFREL:
        a = VM_pop(vm);
        if (!a)
            vm->regs[IP] += VM_fetch(vm);
        break;
    case JMPT:
        a = VM_pop(vm);
        if (a)
            vm->regs[IP] = VM_fetch(vm);
        break;
    case JMPTREL:
        a = VM_pop(vm);
        if (a)
            vm->regs[IP] += VM_fetch(vm);
        break;
    case IMM:
        a = VM_fetch(vm);
        VM_push(vm, a);
        break;
    case INV:
        a = VM_fetch(vm);
        VM_push(vm, vm->regs[BP]); 
        VM_push(vm, vm->regs[IP]);
        vm->regs[BP] = vm->regs[SP];
        vm->regs[IP] = a;
        break;
    case INVREL:
        a = VM_fetch(vm);
        VM_push(vm, vm->regs[BP]); 
        VM_push(vm, vm->regs[IP]);
        vm->regs[BP] = vm->regs[SP];
        vm->regs[IP] += a;
        break;
    case CPY:
        a = VM_fetch(vm);
        VM_push(vm, VM_get(vm, vm->regs[BP] + a));
        break;
    case ARG:
        vm->args = VM_fetch(vm);
        break;
    case REP:
        a = VM_pop(vm);
        VM_set(vm, vm->regs[BP] + VM_fetch(vm), a);
        break;
    case RET:
        a = VM_pop(vm);
        vm->regs[SP] = vm->regs[BP]; 
        vm->regs[IP] = VM_pop(vm);
        vm->regs[BP] = VM_pop(vm);
        vm->regs[SP] -= vm->args;
        VM_push(vm, a);
        break;
    default:
        exit(EXIT_FAILURE);
        break;
    }
}

void VM_loadProgram(VM* vm, char* filename) {
    stream* program = stream_new(filename);
    memcpy(vm->memory, program->bytecode, 0x100);
}

void VM_exec(VM* vm) {
    vm->isRunning = 1;
    while (vm->isRunning)   
        VM_step(vm);
}

void VM_exit(VM* vm) {
    VM_free(vm);
    exit(EXIT_SUCCESS);
}
