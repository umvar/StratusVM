#pragma once

/* VM ALLOCATION */
#define VM_REG 0x3
#define VM_MEM 0x100

/* VM REGISTERS */
#define BP 0x0
#define SP 0x1
#define IP 0x2

/* VM  */
typedef struct {
	char memory[VM_MEM];
	char stack[VM_MEM];
	char regs[VM_REG];
    char args;
	char isRunning;
} VM;

/* FUNCTION PROTOTYPES */ 
VM* VM_new(char* filename);
void VM_free(VM* vm);
void VM_exec(VM* vm);
void VM_push(VM* vm, char val);
char VM_pop(VM* vm);
void VM_set(VM* vm, char index, char val);
char VM_get(VM* vm, char index);
char VM_fetch(VM* vm);
void VM_step(VM* vm);
void VM_loadProgram(VM* vm, char* filename);
void VM_exec(VM* vm);
void VM_exit(VM* vm);