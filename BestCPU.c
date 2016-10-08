/*  BestCPU.c
 32 bit architecture */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int MEMORY[65536] = {0};   // Memory

// General Purpose registers r0-r7
int  r0 = 0, r1 = 34, r2 = 5, r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0;	//Lets assume that the registers have some value
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
    if(strcmp(operation, STORE) == 0)
    {
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

// function for register  value
int get_register (char *reg)
{
    char *R0 = "R0";
    char *R1 = "R1";
    char *R2 = "R2";
    char *R3 = "R3";
    char *R4 = "R4";
    char *R5 = "R5";
    char *R6 = "R6";
    char *R7 = "R7";
    
    //find first register value
    if(strcmp(reg,R0) == 0){
        return r0;
    }
    else if(strcmp(reg,R1) == 0){
        return r1;
    }
    else if(strcmp(reg,R2) == 0){
        return r2;
    }
    else if(strcmp(reg,R3) == 0){
       return r2;
    }
    else if(strcmp(reg,R4) == 0){
        return r4;
    }
    else if(strcmp(reg,R5) == 0){
        return r5;
    }
    else if(strcmp(reg,R6) == 0){
        return r6;
    }
    else if(strcmp(reg,R7) == 0){
        return r7;
    }
    
    return 0;
}

//Function for ALU Division. Here (Register1 = Dividend) And (Register2 = Divisor) 
//Original Divisor will be Divisor in the next recursion.

int division(int dividend, int divisor, int originalDivisor, int remainder)
{
    int quotient = 1;

    if (dividend == divisor)
    {
        remainder = 0;
        return 1;
    }

    else if (dividend < divisor)
    {
        remainder = dividend;
        return 0;
    }

    while (divisor <= dividend)
    {
      /*printf("------------Entered While-------------------\n");
    	printf("divisor = %d\n", divisor);
    	printf("dividend = %d\n", dividend);
    	printf("quotient = %d\n", quotient);*/

        divisor = divisor << 1;
        quotient = quotient << 1;
    }

    if (dividend < divisor)
    {
	/*printf("----------entered IF---------------------\n");
    printf("divisor = %d\n", divisor);
    	printf("dividend = %d\n", dividend);
    	printf("quotient = %d\n", quotient);*/
        divisor >>= 1;
        quotient >>= 1;
    }

    quotient = quotient + division(dividend - divisor, originalDivisor, originalDivisor, remainder);

    return quotient;
}


// function for register2 value

int call_mod(char *register1, char *register2)
{
    int qnt = 0;
    int rmd = 0;
    int i=0;
    int dvnd=0,dvsr=0;
    
   
    dvnd = get_register(register1);
    dvsr = get_register(register2);
    
    
    
    if (dvsr == 0 || dvnd == 0)
    {
        rmd=0;
    }
    else
        
    {
        
        while(i<32)
        {
            rmd = (rmd << 1) | ((dvnd >> 31) & 0x1);
            printf("rem inside while = %d\n", rmd);
            
            if (rmd < dvsr)
            {
                qnt = (qnt << 1) ;
            }
            else
            {
                qnt = (qnt << 1) | 0x1;
                rmd = rmd - dvsr;
            }
            
            
            dvnd = dvnd << 1;
            
            i++;
        }
        
    }
    
    return rmd;
    
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
    
    int mod_result;
    
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
            else if(strcmp(split, "ADD")==0){
                strcat(code, "0010");
                operation = split;
            }
            else if(strcmp(split, "SUB")==0){
                strcat(code, "0011");
                operation = split;
            }
            else if(strcmp(split, "MUL")==0){
                strcat(code, "0100");
                operation = split;
            }
            else if(strcmp(split, "DIV")==0){
                strcat(code, "0101");
                operation = split;
            }
            else if(strcmp(split, "MOD")==0){
                strcat(code, "0110");
                operation = split;
            }
            argNum++;
            printf("\nOpcode: %s \n", operation);
        }
        
        else if(argNum == 1){              //register1
            printf("inside register1 vaibale extract\n");
            register1 = split;
            int reg1 = split[1] - '0';
            int bin1 = decimalToBinary(reg1);
            char *binary_reg1 = (char*) malloc(10);
            sprintf(binary_reg1, "%d", bin1);
            
            
            int len = 12 - strlen(binary_reg1);
            memmove(binary_reg1+len, binary_reg1, strlen(binary_reg1));
            for ( int i = 0; i < len; i++ ){
                binary_reg1[i] = '0';
            }
            strcat(code, binary_reg1);
            printf("Register1: %s \n", binary_reg1);
            argNum++;
        }
        
        else if(argNum == 2)
        {
            
            if((strcmp(operation,"FETCH")==0)||(strcmp(operation,"STORE")==0))
                    {
                        
                        printf("inside memory vaibale extract\n");
                                                //memory
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
            else {
                
                printf("inside register2 vaibale extract\n");
                                                            //register 2
                register2 = split;
                int reg2 = split[1] - '0';
                int bin2 = decimalToBinary(reg2);
                char *binary_reg2 = (char*) malloc(10);
                sprintf(binary_reg2, "%d", bin2);
                
                
                int len = 12 - strlen(binary_reg2);
                memmove(binary_reg2+len, binary_reg2, strlen(binary_reg2));
                for ( int i = 0; i < len; i++ ){
                    binary_reg2[i] = '0';
                }
                strcat(code, binary_reg2);
                printf("Register2: %s \n", binary_reg2);
                argNum++;
                    }
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
    else if (strcmp(operation, "MOD")==0)
    {
        
        mod_result= call_mod(register1, register2);
        
        printf("mod result: %d \n", mod_result);
    }
    else if (strcmp(operation, "DIV")==0)
    {
			int dividend = get_register(register1);
			int divisor = get_register(register2);
        
			int divisionResult= division(dividend, divisor, divisor, 0);		//Initially we send remainder as '0'.

			printf("Division Quotient: %d \n", divisionResult);
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
