#include "../src/VM.c"


int main() {
    VM* vm = VM_new("test.txt");

    VM_exec(vm);

    printf("%d", VM_pop(vm));
    VM_exit(vm);

    return 0;
}