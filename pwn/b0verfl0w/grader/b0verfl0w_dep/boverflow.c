#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int hint() {
    asm(
    "mov %eax,%esp\n\t"
    "ret\n\t"
    "jmp *%eax\n\t"
    "ret\n\t"
    );
    return 1;
}

int main(int argc, char** argv) {
    char buffer[24];

    printf("\n======================\n");
    printf("\nWelcome to X-CTF 2016!\n");
    printf("\n======================\n");

    printf("What's your name?\n");
    fflush(stdout)
    fgets(buffer,40,stdin);

    printf("Hello %s.", buffer);
    fflush(stdout)
    return 1;
}
