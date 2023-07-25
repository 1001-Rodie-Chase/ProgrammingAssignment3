#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_SIZE 100
#define FILE_NAME "input.txt"

// Function prototypes
void displayHexadecimalValue(FILE*);
void execute_mov(uint32_t *reg, uint32_t value, int register_number);
void execute_adds(uint32_t *dest_reg, uint32_t src_reg1, uint32_t src_reg2);
void execute_subs(uint32_t *dest_reg, uint32_t src_reg1, uint32_t src_reg2);
void execute_ands(uint32_t *dest_reg, uint32_t src_reg1, uint32_t src_reg2);
void execute_orr(uint32_t *dest_reg, uint32_t src_reg1, uint32_t src_reg2);
void execute_xor(uint32_t *dest_reg, uint32_t src_reg1, uint32_t src_reg2);
void execute_lsrs(uint32_t *dest_reg, uint32_t src_reg1, uint32_t shiftNum);
void execute_lsls(uint32_t *dest_reg, uint32_t src_reg1, uint32_t shiftNum);
void execute_cmp(uint32_t *dest_reg, uint32_t src_reg1, bool *N, bool *Z, bool *C, bool *V);
void execute_tst(uint32_t *dest_reg, uint32_t src_reg1, bool *N, bool *Z, bool *C, bool *V);
void update_status_flags(uint32_t value, bool *N, bool *Z, bool *C, bool *V);


int main() {
    char string[MAX_SIZE];
    FILE* dest_fp;
    // Check to see if file stream connection is valid
    dest_fp = fopen(FILE_NAME, "r");
    if (dest_fp == NULL) {
        printf("Can't open file.\n");
    } else {
        // Function Call 
        displayHexadecimalValue(dest_fp);
        fclose(dest_fp);
    }
    return 0;
}

void displayHexadecimalValue(FILE* fptr) {
    bool N, Z, C, V;
    uint32_t registers[8] = {0};
    char line[MAX_SIZE];
    // While loop that reads a string and evaluates the hexadecimal values
    while (fgets(line, sizeof(line), fptr) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        uint32_t value; // Declare the 'value' variable to store the extracted hexadecimal value
        int dest_register, src_register1, src_register2, shiftValue;
        
        // Check for "MOV Rn, #0x..." instruction
        if (sscanf(line, "MOV R%d, #%x", &dest_register, &value) == 2) {
            if (dest_register >= 0 && dest_register < 8) {
                execute_mov(&registers[dest_register], value, dest_register);
                printf("MOV R%d, #0x%08X\n", dest_register, registers[dest_register]);
            }
        }
        if (sscanf(line, "mov r%d, #%x", &dest_register, &value) == 2) {
            if (dest_register >= 0 && dest_register < 8) {
                execute_mov(&registers[dest_register], value, dest_register);
                printf("mov r%d, #0x%08X\n", dest_register, registers[dest_register]);
            }
        }
        // Check for "ADDS Rn, Rm, Rp" instruction
        else if (sscanf(line, "ADDS R%d, R%d, R%d", &dest_register, &src_register1, &src_register2) == 3) {
            if (dest_register >= 0 && dest_register < 8 && src_register1 >= 0 && src_register1 < 8 && src_register2 >= 0 && src_register2 < 8) {
                execute_adds(&registers[dest_register], registers[src_register1], registers[src_register2]);
                printf("ADDS R%d, R%d, R%d\n", dest_register, src_register1, src_register2);
            }
        }
        else if (sscanf(line, "SUBS R%d, R%d, R%d", &dest_register, &src_register1, &src_register2) == 3) {
            if (dest_register >= 0 && dest_register < 8 && src_register1 >= 0 && src_register1 < 8 && src_register2 >= 0 && src_register2 < 8) {
                execute_subs(&registers[dest_register], registers[src_register1], registers[src_register2]);
                printf("SUBS R%d, R%d, R%d\n", dest_register, src_register1, src_register2);
            }
        }
        else if (sscanf(line, "ands r%d, r%d, r%d", &dest_register, &src_register1, &src_register2) == 3) {
            if (dest_register >= 0 && dest_register < 8 && src_register1 >= 0 && src_register1 < 8 && src_register2 >= 0 && src_register2 < 8) {
                execute_ands(&registers[dest_register], registers[src_register1], registers[src_register2]);
                printf("ands r%d, r%d, r%d\n", dest_register, src_register1, src_register2);
            }
        }
        else if (sscanf(line, "orr r%d, r%d, r%d", &dest_register, &src_register1, &src_register2) == 3) {
            if (dest_register >= 0 && dest_register < 8 && src_register1 >= 0 && src_register1 < 8 && src_register2 >= 0 && src_register2 < 8) {
                execute_orr(&registers[dest_register], registers[src_register1], registers[src_register2]);
                printf("orr r%d, r%d, r%d\n", dest_register, src_register1, src_register2);
            }
        }
        else if (sscanf(line, "xor r%d, r%d, r%d", &dest_register, &src_register1, &src_register2) == 3) {
            if (dest_register >= 0 && dest_register < 8 && src_register1 >= 0 && src_register1 < 8 && src_register2 >= 0 && src_register2 < 8) {
                execute_xor(&registers[dest_register], registers[src_register1], registers[src_register2]);
                printf("xor r%d, r%d, r%d\n", dest_register, src_register1, src_register2);
            }
        }
        else if (sscanf(line, "lsrs R%d, R%d, #%d", &dest_register, &src_register1, &shiftValue) == 3) {
            if (dest_register >= 0 && dest_register < 8 && src_register1 >= 0 && src_register1 < 8 && src_register2 >= 0 && src_register2 < 8) {
                execute_lsrs(&registers[dest_register], registers[src_register1], shiftValue);
                printf("lsrs R%d, R%d, #%d\n", dest_register, src_register1, shiftValue);
            }
        }
        else if (sscanf(line, "LSLS R%d, R%d, #%d", &dest_register, &src_register1, &shiftValue) == 3) {
            if (dest_register >= 0 && dest_register < 8 && src_register1 >= 0 && src_register1 < 8 && src_register2 >= 0 && src_register2 < 8) {
                execute_lsls(&registers[dest_register], registers[src_register1], shiftValue);
                printf("LSLS R%d, R%d, #%d\n", dest_register, src_register1, shiftValue);
            }
        }
        else if (sscanf(line, "CMP R%d, R%d", &dest_register, &src_register1) == 2) {
            if (dest_register >= 0 && dest_register < 8 && src_register1 >= 0 && src_register1 < 8 && src_register2 >= 0 && src_register2 < 8) {
                execute_cmp(&registers[dest_register], registers[src_register1], &N, &Z, &C, &V);
                printf("CMP R%d, R%d\n", dest_register, src_register1);
            }
        }
        else if (sscanf(line, "tst R%d, R%d", &dest_register, &src_register1) == 2) {
            if (dest_register >= 0 && dest_register < 8 && src_register1 >= 0 && src_register1 < 8 && src_register2 >= 0 && src_register2 < 8) {
                execute_tst(&registers[dest_register], registers[src_register1], &N, &Z, &C, &V);
                printf("tst R%d, R%d\n", dest_register, src_register1);
            }
        }
        update_status_flags(registers[dest_register], &N, &Z, &C, &V);
        printf("R0:0x%0X R1:0x%0X R2:0x%0X R3:0x%0X\nR4:0x%0X R5:0x%0X R6:0x%0X R7:0x%0X\n", registers[0], registers[1], registers[2], registers[3], registers[4], registers[5], registers[6], registers[7]);
        printf("N = %d Z = %d C = %d V = %d\n", N, Z, C, V);
    }
}

void execute_mov(uint32_t *reg, uint32_t value, int register_number) {
    *reg = value;
}

void execute_adds(uint32_t *dest_reg, uint32_t src_reg1, uint32_t src_reg2) {
    *dest_reg = src_reg1 + src_reg2;
}

void execute_subs(uint32_t *dest_reg, uint32_t src_reg1, uint32_t src_reg2) {
    *dest_reg = src_reg1 - src_reg2;
}

void execute_ands(uint32_t *dest_reg, uint32_t src_reg1, uint32_t src_reg2) {
    *dest_reg = src_reg1 & src_reg2;
}

void execute_orr(uint32_t *dest_reg, uint32_t src_reg1, uint32_t src_reg2) {
    *dest_reg = src_reg1 | src_reg2;
}

void execute_xor(uint32_t *dest_reg, uint32_t src_reg1, uint32_t src_reg2) {
    *dest_reg = src_reg1 ^ src_reg2;
}

void execute_lsrs(uint32_t *dest_reg, uint32_t src_reg1, uint32_t shiftNum) {
    *dest_reg = src_reg1 >> shiftNum;
}

void execute_lsls(uint32_t *dest_reg, uint32_t src_reg1, uint32_t shiftNum) {
    *dest_reg = src_reg1 << shiftNum;
}

void execute_cmp(uint32_t *dest_reg, uint32_t src_reg1, bool *N, bool *Z, bool *C, bool *V) {
    uint32_t results = *dest_reg - src_reg1;
    update_status_flags(results, N, Z, C, V);
}

void execute_tst(uint32_t *dest_reg, uint32_t src_reg1, bool *N, bool *Z, bool *C, bool *V) {
    uint32_t result = *dest_reg & src_reg1;
    update_status_flags(result, N, Z, C, V);

}

void update_status_flags(uint32_t value, bool *N, bool *Z, bool *C, bool *V) {
    *N = (value & 0x80000000) != 0;
    *Z = (value == 0);
    // Update Carry flag: Set if there was a carry (borrow) in the most significant bit.
    *C = (value > 0xFFFFFFFF);
    // Update Overflow flag: Set if signed overflow occurred.
    *V = ((value & 0x80000000) != (*N << 31));
}





