/*
    Simple-As-Possible 1 (SAP1) Computer Emulator
    Paolo Miguel de Leon (c) 2011
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LDA 0x0
#define ADD 0x1
#define SUB 0x2
#define OUT 0xE
#define HLT 0xF

typedef unsigned char byte;
typedef unsigned short bool;

byte ROM[16] = {0};  // 16x8 ROM
byte PC = 0x0;       // Program Counter
byte IR;             // Instruction Register
byte Ax;             // Accumulator
byte B;              // B Register

int halt = 0;

/* void init() {
    ROM[0x0] = 0x0A; // LDA rA
    ROM[0x1] = 0x1B; // ADD rB
    ROM[0x2] = 0x2C; // SUB rC
    ROM[0x3] = 0xE0; // OUT
    ROM[0x4] = 0xF0; // HLT
    ROM[0xA] = 0xC0; // 0xC0
    ROM[0xB] = 0x36; // 0x36
    ROM[0xC] = 0x05; // 0x05
    // OUTPUT: F1 (1111 0001)
} */

bool is_LDA(char op) { return strcmp(op, "LDA") == 0; }
bool is_ADD(char op) { return strcmp(op, "ADD") == 0; }
bool is_SUB(char op) { return strcmp(op, "SUB") == 0; }
bool is_OUT(char op) { return strcmp(op, "OUT") == 0; }
bool is_HLT(char op) { return strcmp(op, "HLT") == 0; }

void load(char *filename) {
    FILE *f = fopen(filename, "r");

    char buffer[128], *op, *temp;
    byte addr, val;

    int index, len;
    while(fgets(buffer, sizeof(buffer), f) > 0) {
        temp = strtok(buffer, " ");

        sscanf(temp, "r%X:", &index);

        op = strtok(NULL, " ");
        len = strlen(op);

        if (op[1] == 'x' && len == 5) op[4] = '\0';
        if (len == 4) op[3] = '\0';

        if( is_LDA(op) ) {
            temp = strtok(NULL, " ");
            sscanf(temp, "r%X", &addr);
            ROM[index] = addr;

        } else if( is_ADD(op) ) {
            temp = strtok(NULL, " ");
            sscanf(temp, "r%X", &addr);
            ROM[index] = 0x10 + addr;

        } else if( is_SUB(op) ) {
            temp = strtok(NULL, " ");
            sscanf(temp, "r%X", &addr);
            ROM[index] = 0x20 + addr;

        } else if( is_OUT(op) ) {
            ROM[index] = 0xE0;

        } else if( is_HLT(op) ) {
            ROM[index] = 0xF0;

        } else {
            sscanf(op, "0x%X", &val);
            ROM[index] = val;

        }
    }
}

char *to_binary(byte hex) {
    char *binary = (char *)malloc(sizeof(char) * 10);
    int i;

    for(i = 0; i < 9; i++) {
        if(i == 4) { binary[i] = ' '; continue; }
        binary[i] = ( (hex & 128) >> 7 ) + 0x30;
        hex = hex << 1;
    }

    binary[i] = '\0';
    return binary;
}

void display_ROM() {
    int i;
    for(i = 0; i < 16; i++) {
         printf("r%X: %s\n", i, to_binary(ROM[i]));
    }
}

void fetch() {
    IR = ROM[PC];
    PC++;
}

void execute() {
    byte OPCODE  = IR >> 4 & 0xF;
    byte REGISTER = IR & 0xF;
    switch(OPCODE) {
        case LDA:
            Ax = ROM[REGISTER];
            break;
        case ADD:
            B = ROM[REGISTER];
            Ax += B;
            break;
        case SUB:
            B = ROM[REGISTER];
            Ax -= B;
            break;
        case OUT:
            printf("\nOUTPUT: %X (%s)\n", Ax, to_binary(Ax));
            break;
        case HLT:
            halt = 1;
            break;
    }
}

int main(int argc, char **argv) {
    argc--; argv++;

    load(argv[0]);
    display_ROM();
    while(!halt) {
        fetch();
        execute();
    }

    return 0;
}
