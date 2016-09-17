//
//  BestCPU.c
//
// 32 bit architecture
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int MEMORY[65536] = {0};   // Memory
// General Purpose registers r0-r7
    int  r0, r1 = 20, r2, r3, r4, r5, r6, r7;

    int PC;                    // Program Counter
    int MAR;                   // Memory Address
    int MDR;                   // Memory Data Register
    int FLG;                   // Flag register
    int SP;                    // Stack Pointer
    int RA;                    // Return Address register
    const int ZERO = 0;        // Zero Address Register

/*char* convertBinary(int decimalNumber){
    printf("Hello\n");
    char stroreBinaryArray[17] = {0};
    int i = 0;
    while(decimalNumber != 1){
        char dec;
        dec = (decimalNumber%2) + '0';
        printf("Hello again %c   %d\n", dec, decimalNumber%2);
        stroreBinaryArray[i] = dec;
        i++;
        decimalNumber = decimalNumber/2;
    }
    printf("NUM: %s\n", stroreBinaryArray);
    return stroreBinaryArray;
}*/


/* int loadWord(char destinationRegister, char offset, char baseAddressRegister, char* MAR, char* MDR){
    int tempLocal = atoi(offset) + atoi(baseAddressRegister);
    destinationRegister = tempLocal
 
}*/


/* int storeWord(int data, int offset, int baseAddress, int * MAR, int* MDR){
}*/
//Function to convert decimal to binary
int decimalToBinary(int n) {
    int rem;
    int binary = 0;
    int i = 1;
    
    while(n != 0) {
        rem = n%2;
        n = n/2;
        binary= binary + (rem*i);
        i = i*10;
    }
    return binary;
}

//Function to convert large decimal numbers to binary. Answer returned in a char string
char* decToBin(int n){
    //printf("Num %d\n", n);
    char *binary = (char*) malloc(16);
    int rem, i = 0;
    while(n != 0){
        rem = n%2;
        n = n/2;
        binary[i] = rem + '0';
        //printf("Rem: %d    Num: %d    binary[i]: %c\n", rem, n, binary[i]);
        i++;
        
    }
    binary[i] = '\0';
   // printf("binary before reversal: %s\n", binary);

    //Reverse string
    char *start = binary;
    char *end = start + strlen(binary) - 1; /* -1 for \0 */
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

    //printf("binary: %s\n", binary);
    return binary;
}

void execute_Fetch(char *operation, char *register1, int address){                         // -TARSHITH
    char *FETCH = "FETCH";
    char *R0 = "R0";            //JUST FOR COMPARING WHICH REGISTER IS RECEIVED AS PARAMETER.
    char *R1 = "R1";
    char *R2 = "R2";
    char *R3 = "R3";
    char *R4 = "R4";
    char *R5 = "R5";
    char *R6 = "R6";
    char *R7 = "R7";
    
    
    //printf("\nEntered executeFetch\n");
    printf("\nReceived parameters are: \n\tOperation = %s, Register = %s, Address = %d\n", operation, register1, address);
   
    int i = 0;
    if(strcmp(operation, FETCH) == 0){                    //CHECK IF THE INTRUCTION IS STORE OR NOT
        //printf("\nEntered instruction is FETCH\n");
        //printf("Register to store data after retreival is = %s and Address to retreive this data from is = %d\n", register1, address);

        if(strcmp(register1,R0) == 0){                    
            r0 = MEMORY[address];
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R0, r0);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R1) == 0){                    
            r1 = MEMORY[address];
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R1, r1);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R2) == 0){                    
            r2 = MEMORY[address];
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R2, r2);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R3) == 0){                    
            r3 = MEMORY[address];
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R3, r3);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R4) == 0){                    
            r4 = MEMORY[address];
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R4, r4);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R5) == 0){                    
            r5 = MEMORY[address];
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R5, r5);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R6) == 0){                    
            r6 = MEMORY[address];
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R6, r6);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R7) == 0){                    
            r7 = MEMORY[address];
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R7, r7);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
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
    
    
    
    //printf("\nReceived parameters are: \n\tOperation = %s, Register = %s, Address = %d\n", operation, register1, address);
    
    
    int i = 0;
    if(strcmp(operation, STORE) == 0)
    
    {
        
        
        if(strcmp(register1,R0) == 0){
            MEMORY[address]=r0;
            MAR=address;
            MDR=MEMORY[address];
            
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R0, r0);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R1) == 0){
            MEMORY[address]=r1;
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R1, r1);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R2) == 0){
            MEMORY[address]=r2;
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R2, r2);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R3) == 0){
            MEMORY[address]=r3;
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R3, r3);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R4) == 0){
            MEMORY[address]=r4;
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R4, r4);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R5) == 0){
            MEMORY[address]=r5;
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R5, r5);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R6) == 0){
            MEMORY[address]=r6;
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R6, r6);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
        }
        else if(strcmp(register1,R7) == 0){
            MEMORY[address]=r7;
            MAR=address;
            MDR=MEMORY[address];
            printf("Data at location %d is %d \nValue in Register %s now is %d\n", address, MEMORY[address], R7, r7);
            printf("The MAR value %d\nThe MDR value %d\n", MAR, MDR);
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
   // printf("Split: %s\n", split);
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
            printf("opcode: %s %lu\n", code, sizeof(code));
        }
        
        else if(argNum == 1){              //register
           // printf("Split: %s\n", split);
            register1 = split;
            //printf("***** Split[1] is = %c\n", split[0]);
            int reg = split[1] - '0';
            //printf("-------int reg is = %d\n", reg);
            int bin = decimalToBinary(reg);
            //printf("-------int bin is = %d\n", bin);
            char binary[5];
            sprintf(binary, "%d", bin);
            //printf("-------int binary is = %s\n", binary);
            
            int len = 12 - strlen(binary);
            memmove(binary+len, binary, strlen(binary));
            for ( int i = 0; i < len; i++ )
                binary[i] = '0';
            
            strcat(code, binary);
            printf("register: %s %lu\n", code, sizeof(code));
            argNum++;
        }
        
        else if(argNum == 2){           //memory
           // printf("Split: %s\n", split);
            int addr = atoi(split);
            address = addr;
            //printf("Addr: %d\n", addr);
            //char memAddr[17];
            char *memAddr = (char*) malloc(18);
            strcpy(memAddr,decToBin(addr));
            
            int len = 16 - strlen(memAddr);
            memmove(memAddr+len, memAddr, strlen(memAddr));
            for ( int i = 0; i < len; i++ )
                memAddr[i] = '0';
            
            printf("MemAddr:%s\n", memAddr);
            strcat(code, memAddr);
            printf("code: %s %lu\n", code, sizeof(code));
            argNum++;
            
        }
        split = strtok(NULL, " ,.-");
        
    }
    
    
    if(strcmp(operation, "STORE")==0)
    {
        execute_store(operation, register1, address);
    }
    else if (strcmp(operation, "FETCH")==0)
    {
        execute_Fetch(operation, register1, address);
    }
    
    return;
    
    
}


int main(int argc, char *argv[])    //CHANGED FROM **ARGV TO *ARGV[] - TARSHITH

{
    MEMORY[1000] = 222;             //LETS ASSUME AT THAT MOMENT MEMORY[1000] HAS A VALUE 222 AND TRY TO FETCH IT.
    
    for(int i=1; i< argc; i++) {
        printf("%s\n", argv[i]);
        storeToMemory(argv[i]);
    }

    
    printf("The PC value %d\n", PC);
    printf("The FLG value %d\n", FLG);
    printf("The SP value %d\n", SP);
    printf("The RA value %d\n", RA);
    
    return 0 ;
}
