#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define FILE_NAME "input.txt"
#define SIZE 90

void dispData(FILE* ptr);

int main() {
    FILE* fp;
    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Can't open file\n");
    } else {
        dispData(fp);
        fclose(fp);
    }
    return 0;
}

void dispData(FILE *ptr) {
    uint32_t regnum;
    uint32_t regnum2;
    uint32_t regnum3;
    uint32_t reg[8] = {0};
    uint32_t var2;
    uint32_t total;
    uint32_t var3;
    uint32_t aluA;
    uint32_t aluB;
    int shift, Nflag, Zflag, Cflag, Vflag;

    char string[SIZE];
    while (fgets(string, sizeof(string), ptr) != NULL) {
        // Reset flags and registers for each instruction
        uint32_t regnum;
    uint32_t regnum2;
    uint32_t regnum3;
        Nflag = Zflag = Cflag = Vflag = 0;
        reg[0] = reg[1] = reg[2] = reg[3] = reg[4] = reg[5] = reg[6] = reg[7] = 0;

        string[strcspn(string, "\n")] = '\0';

        if (strncmp(string, "MOV ", 4) == 0) {
            sscanf(string, "MOV R%d, #%x", &regnum, &var2);
            reg[regnum] = var2; 
            printf("MOV R%d, #0x%08X\n", regnum, var2);
        } else if (strncmp(string, "ADDS ", 4) == 0){
            if (regnum >= 0 && regnum < 8 && regnum2 >= 0 && regnum2 < 8 && regnum3 >= 0 && regnum3 < 8) {
                reg[regnum] = reg[regnum2] + reg[regnum3];
                printf("ADDS R%d, R%d, R%d\n", regnum, regnum2, regnum3);

            }

            // Set flags based on the result of the ADDS operation
            Nflag = (total >> 31) & 1;
            Zflag = total == 0;
            Cflag = total < aluA; // Check for unsigned overflow
            Vflag = (aluA >> 31 == aluB >> 31) && (total >> 31 != aluA >> 31);
        }
         printf("R0:0x%08X R1:0x%08X R2:0x%08X R3:0x%08X R4:0x%08X R5:0x%08X R6:0x%08X R7:0x%08X\n",
           reg[0], reg[1], reg[2], reg[3], reg[4], reg[5], reg[6], reg[7]);
        printf("N = %d Z = %d C = %d V = %d\n", Nflag, Zflag, Cflag, Vflag);
    }

}
