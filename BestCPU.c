/*  BestCPU.c
 32 bit architecture */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int MEMORY[65536] = {0};   // Memory

// General Purpose registers r0-r7
int  r0 = 0, r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0;	//Lets assume that the registers have some value 
																										//before the execution began.

int PC;                    // Program Counter
int MAR;                   // Memory Address
int MDR;                   // Memory Data Register
int FLG;                   // Flag register
int SP;                    // Stack Pointer
int RA;                    // Return Address register
const int ZERO = 0;        // Zero Address Register

//Function to convert decimal to binary
int decimalToBinary(int n) {
    int remainder;
    int binary = 0;
    int i = 1;
    
    while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}

//Function to Convert integer to binary string. This code is not used for now, for future use.
char *inttobinary(int num, char *buf, int bufSize) {
    buf += (bufSize - 1);
    
    for (int i = 0; i <= 31; i++ , num >>= 1) {
        *buf-- = (num & 1) + '0';
        
    }
    return buf;
}


//Function to convert large decimal numbers to binary. Answer returned in a char string
char* decToBin(int decimalNumber){
    char *binary = (char*) malloc(16);
    int remainder, i = 0;
    while(decimalNumber != 0){
        remainder = decimalNumber % 2;
        decimalNumber = decimalNumber/2;
        binary[i] = remainder + '0';
        i++;
    }
    binary[i] = '\0';

    //Reverse string
    char *start = binary;
    char *end = start + strlen(binary) - 1; /* -1 because of \0 */
    char temp;
    
    /* reverse */
    while (end > start)
    {
        /* swap */
        temp = *start;
        *start = *end;
        *end = temp;
        
        /* move */
        ++start;
        --end;
    }
    return binary;
}

void execute_Fetch(char *operation, char *register1, int address){             
    char *FETCH = "FETCH";
    char *R0 = "R0";            //JUST FOR COMPARING WHICH REGISTER IS RECEIVED AS PARAMETER.
    char *R1 = "R1";
    char *R2 = "R2";
    char *R3 = "R3";
    char *R4 = "R4";
    char *R5 = "R5";
    char *R6 = "R6";
    char *R7 = "R7";
    
    printf("\n\nReceived parameters are: \n\tOperation = %s, Register = %s, Address = %d\n", operation, register1, address);
    
    int index = address/4;
   
    int i = 0;
    if(strcmp(register1,R0) == 0){                    
        r0 = MEMORY[index];
        MAR = address;
        MDR = MEMORY[index];
        printf("\tData at location %d is %d \n\t\tValue in Register %s now is %d\n", address, MEMORY[index], R0, r0);
        printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
    }
    else if(strcmp(register1,R1) == 0){                    
        r1 = MEMORY[index];
        MAR = address;
        MDR = MEMORY[index];
        printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R1, r1);
        printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
    }
    else if(strcmp(register1,R2) == 0){                    
        r2 = MEMORY[index];
        MAR = address;
        MDR = MEMORY[index];
        printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R2, r2);
        printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
    }
    else if(strcmp(register1,R3) == 0){                    
        r3 = MEMORY[index];
        MAR = address;
        MDR = MEMORY[index];
        printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R3, r3);
        printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
    }
    else if(strcmp(register1,R4) == 0){                    
        r4 = MEMORY[index];
        MAR = address;
        MDR = MEMORY[index];
        printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R4, r4);
        printf("\tThe MAR value %d\n\tThe MDR value %d\n", MAR, MDR);
    }
    else if(strcmp(register1,R5) == 0){                    
        r5 = MEMORY[index];
        MAR = address;
        MDR = MEMORY[index];
        printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R5, r5);
        printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
    }
    else if(strcmp(register1,R6) == 0){                    
        r6 = MEMORY[index];
        MAR = address;
        MDR = MEMORY[index];
        printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R6, r6);
        printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
    }
    else if(strcmp(register1,R7) == 0){                    
        r7 = MEMORY[index];
        MAR = address;
        MDR = MEMORY[index];
        printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R7, r7);
        printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
    }
}

void execute_store(char *operation, char *register1, int address){
    char *STORE = "STORE";
    char *R0 = "R0";
    char *R1 = "R1";
    char *R2 = "R2";
    char *R3 = "R3";
    char *R4 = "R4";
    char *R5 = "R5";
    char *R6 = "R6";
    char *R7 = "R7";
       
    printf("\n\nReceived parameters are: \n\tOperation = %s, Register = %s, Address = %d\n", operation, register1, address);
    
    int index = address/4;

    int i = 0;
    if(strcmp(operation, STORE) == 0){             
        if(strcmp(register1,R0) == 0){
            MEMORY[index] = r0;
            MAR = address;
            MDR = MEMORY[index];
            
            printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R0, r0);
            printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
        }
        else if(strcmp(register1,R1) == 0){
            MEMORY[index] = r1;
            MAR = address;
            MDR = MEMORY[index];
            printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R1, r1);
            printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
        }
        else if(strcmp(register1,R2) == 0){
            MEMORY[index] = r2;
            MAR = address;
            MDR = MEMORY[index];
            printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R2, r2);
            printf("\tThe MAR value %d\n\tThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R3) == 0){
            MEMORY[index] = r3;
            MAR = address;
            MDR = MEMORY[index];
            printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R3, r3);
            printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
        }
        else if(strcmp(register1,R4) == 0){
            MEMORY[index] = r4;
            MAR = address;
            MDR = MEMORY[index];
            printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R4, r4);
            printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
        }
        else if(strcmp(register1,R5) == 0){
            MEMORY[index] = r5;
            MAR = address;
            MDR = MEMORY[index];
            printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R5, r5);
            printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
        }
        else if(strcmp(register1,R6) == 0){
            MEMORY[index] = r6;
            MAR = address;
            MDR = MEMORY[index];
            printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R6, r6);
            printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
        }
        else if(strcmp(register1,R7) == 0){
            MEMORY[index] = r7;
            MAR = address;
            MDR = MEMORY[index];
            printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], R7, r7);
            printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
        }
        
    }
}


//Function for storing the instruction to the memory
void storeToMemory(char *inst){
    
    char *split = (char *) malloc(16);
    char * str = (char *) malloc(16);
    strcpy(str,inst);

    char *operation;
    char *register1;
    char *register2;
    int address;
    char code[34] = "";
    
    int argNum = 0;
    split = strtok(str, " ,.-");
    while(split != NULL){
        if(argNum == 0){                    //opcode parsing
            if(strcmp(split, "FETCH")==0){
                strcat(code, "0000");
                operation = split;
            }
            else if(strcmp(split, "STORE")==0){
                strcat(code, "0001");
                operation = split;
            }
            argNum++;
            printf("\nOpcode: %s \n", operation);
        }
        
        else if(argNum == 1){              //register
            register1 = split;
            int reg = split[1] - '0';
            int bin = decimalToBinary(reg);
            char *binary = (char*) malloc(10);
            sprintf(binary, "%d", bin);
            
            
            int len = 12 - strlen(binary);
            memmove(binary+len, binary, strlen(binary));
            for ( int i = 0; i < len; i++ ){
                binary[i] = '0';
            }
            strcat(code, binary);
            printf("Register: %s \n", binary);
            argNum++;
        }
        
        else if(argNum == 2){           //memory
            int addr = atoi(split);
            address = addr;
            char *memAddr = (char*) malloc(18);
            strcpy(memAddr,decToBin(addr));
            
            int len = 16 - strlen(memAddr);
            memmove(memAddr+len, memAddr, strlen(memAddr));
            for ( int i = 0; i < len; i++ )
                memAddr[i] = '0';
            
            printf("Memory Address:%s\n", memAddr);
            strcat(code, memAddr);
            printf("\nCode to store in memory in binary: %s \n", code);
            int instruction = strtol(code,NULL,2);
            
            MEMORY[PC/4] = instruction ; // Store the instruction in Memory starting from the IM start address
            printf("Final code to store in memory in int: %d", instruction);
            PC += 4 ;
            argNum++;
            
        }
        split = strtok(NULL, " ,.-");
        
    }
        
    if(strcmp(operation, "STORE")==0){
        execute_store(operation, register1, address);
    }
    else if (strcmp(operation, "FETCH")==0){
        execute_Fetch(operation, register1, address);
    }  
    return;
}


int main(int argc, char *argv[]){
    MEMORY[20000] = 222;             //LETS ASSUME AT THAT MOMENT MEMORY[20000], i.e. memory address 80000 HAS A VALUE 222 AND TRY TO FETCH IT.
    
    // Initiating the instruction memory[IM] address from MEMORY[10000], i.e. memory address 40000. Needs to be changed for booting OS later.
    PC = 40000;
    
    for(int i=1; i< argc; i++) {
        printf("\n========================Executing Instruction %d===========================", i) ;
        storeToMemory(argv[i]);
        printf("\n\nThe PC value at %s Instruction is %d\n",argv[i], PC);
        printf("The FLG value at the end of this Instruction is %d\n", FLG);
        printf("The SP value at the end of this Instruction is %d\n", SP);
        printf("The RA value at the end of this Instruction is %d\n\n", RA);

        printf("The value in register R0 is %d\n", r0);
        printf("The value in register R1 is %d\n", r1);
        printf("The value in register R2 is %d\n", r2);
        printf("The value in register R3 is %d\n", r3);
        printf("The value in register R4 is %d\n", r4);
        printf("The value in register R5 is %d\n", r5);
        printf("The value in register R6 is %d\n", r6);
        printf("The value in register R7 is %d\n\n", r7);
    }
    
    return 0;
}
