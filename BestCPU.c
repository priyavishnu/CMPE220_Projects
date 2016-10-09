/*  BestCPU.c
 32 bit architecture */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int MEMORY[65536] = {0};   // Memory

// General Purpose registers r0-r7
int     r0 = 0, 
        r1 = -2147483648,
        r2 = 5,
        r3 = 0,
        r4 = 3, 
        r5 = 0, 
        r6 = 0, 
        r7 = 0;	//Lets assume that the registers have some value before the execution began. //r1 = 34


int         PC = 40000;            // Program Counter(Initiating the instruction memory[IM] address from MEMORY[10000], i.e. memory address 40000. Needs to be changed for booting OS later)
int         MAR;                   // Memory Address
int         MDR;                   // Memory Data Register
int         FLG;                   // Flag register
int         SP;                    // Stack Pointer
int         RA;                    // Return Address register
const int   ZERO = 0;               // Zero Address Register

#define INSTRUCTION_MEMORY_STACK_BASE    10000
#define BOOT_MEMORY_BASE                     0
#define STACK_TOP                        65536
#define NUMBER_OF_INSTRUCTIONS              30

/* Opcodes */

/*	FETCH 	= 00000,
	STORE 	= 00001,
	ADD		= 00010,
	SUB		= 00011,
	MUL		= 00100
	DIV		= 00101,
	MOD		= 00110,
	LEAQ 	= 00111,
	ADDI    = 01000,
    SUBI	= 01001,
	MULI	= 01010,
	DIVI	= 01011,
	MODI	= 01100,
            = 01101,     // For Future Instructions
            = 01110,
            = 01111     */

/*Flags
 
    Zero flag = FLG[0]
    Sign flag = FLG[1]
    Carry flag = FLG[2]
    Overflow flag = FLG[3]
 
 */

//Function definition for printing all the values
void print_values();

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


//Function to convert any decimal Number into Binary --------------Tarshith
char *decimal_to_binary(int decimal, int No_of_bits_in_binary_you_need)
{
   int bits, d, totalBits;
   char *binary;
 
   totalBits = 0;
   binary = (char*)malloc(No_of_bits_in_binary_you_need+1);
 
   if ( binary == NULL )
      exit(EXIT_FAILURE);
 
   for (bits = No_of_bits_in_binary_you_need-1 ; bits >= 0 ; bits--)
   {
      d = decimal >> bits;
 
      if ( d & 1 )
         *(binary+totalBits) = 1 + '0';
      else
         *(binary+totalBits) = 0 + '0';
 
      totalBits++;
   }
   *(binary+totalBits) = '\0';
 
   return  binary;
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
       return r3;
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

// function for register  value
void set_register (char *reg,int val)
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
       r0=val;
    }
    else if(strcmp(reg,R1) == 0){
        r1=val;
    }
    else if(strcmp(reg,R2) == 0){
        r2=val;
    }
    else if(strcmp(reg,R3) == 0){
        r3=val;
    }
    else if(strcmp(reg,R4) == 0){
        r4=val;
    }
    else if(strcmp(reg,R5) == 0){
        r5=val;
    }
    else if(strcmp(reg,R6) == 0){
        r6=val;
    }
    else if(strcmp(reg,R7) == 0){
        r7=val;
    }
    
    return;
}

//Function to check whether or not to set zero flag
void set_zero(int num){
    
    if(num == 0){
        FLG = FLG | 0x01;
    }
    else if(FLG& 0x1){
        FLG = FLG ^ 0x01;
    }
    return;
}

//Function to check whether or not to set sign flag
void set_sign(int num){
    
    if(num<0){
        FLG = FLG | 0x02;
    }
    else if((FLG>>1)& 0x01){
        FLG = FLG ^ 0x02;
    }
    return;
}


//Function to set carry flag when operation is add
void set_carry(int num1, int num2, int result){
    int msbNum1, msbNum2, msbResult;
    
    msbNum1 = (num1>>31) & 0x1;
    msbNum2 = (num2>>31) & 0x1;
    msbResult = (result>>31) & 0x1;
    
    if((msbNum1 && msbNum2) || (msbNum1 && !(msbResult)) ||(msbNum2 && !(msbResult)) ){
        FLG = FLG | 0x04;
    }
    else if((FLG>>2) & 0x01){
        FLG = FLG ^ 0x04;
    }

}

//Function to set overflow flag when the operation is add
void set_overflow_add(int num1, int num2, int result){
    
    int msbNum1, msbNum2, msbResult;
    
    msbNum1 = (num1>>31) & 0x1;
    msbNum2 = (num2>>31) & 0x1;
    msbResult = (result>>31) & 0x1;
    
    
    if((msbNum1 == msbNum2) && (msbResult != msbNum1)){
        FLG = FLG | 0x08;
    }
    else if((FLG>>3) & 0x1){
        FLG = FLG ^ 0x08;
    }
    
    return;
}

//Function to set overflow flag when the operation is subtract
void set_overflow_sub(int num1, int num2, int result){
    
    int msbNum1, msbNum2, msbResult;
    
    msbNum1 = (num1>>31) & 0x1;
    msbNum2 = (num2>>31) & 0x1;
    msbResult = (result>>31) & 0x1;
    
    if((msbNum1 != msbNum2) && (msbResult == msbNum2)){
            FLG = FLG | 0x08;
        }
    else if((FLG>>3) & 0x1){
        FLG = FLG ^ 0x08;
    }
    
    return;
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
    
    //quotient = add (quotient, division(dividend - divisor, originalDivisor, originalDivisor, remainder));
    
    //Setting flags
    set_zero(quotient);
    set_sign(quotient);
    
    //Storing result in register
    return quotient;
}


// function for ALU MOD function register 1=dividend and register 2= divisor

void call_mod(char *register1, char *register2)
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
    
    //Setting flags
    set_zero(rmd);
    set_sign(rmd);
    
    //Storing result in register
    set_register(register2,rmd);
    
    return;
    
}

//Function for adding two registers ADD R1, R2 =>  R1 = R1 + R2
int add(int num1, int num2){
    
    //Checking if either input is 0
    
    int n1 = num1, n2 = num2;
    
    if(num1 == 0){
        return num2;
    }
    
    if(num2 == 0){
        return num1;
    }
    
    while(num2){
        int carry = num1 & num2;
        num1 = num1 ^ num2;
        
        num2 = carry << 1;
    }
    
    //Setting flags
    set_zero(num1);
    set_sign(num1);
    set_carry(n1, n2, num1);
    set_overflow_add(n1, n2, num1);
    
    return num1;
    
}

//Function to find twos compliment of a number
int twosCompliment (int num){
    num = ~(num);
    num = add(num, 1);
    return num;
}


//Function for subtracting two registers SUB R1, R2 =>  R1 = R1 - R2
int sub(char* reg1, char* reg2){

    int num1 = get_register(reg1);
    int num2 = get_register(reg2);
    
    int n1 = num1, n2 = twosCompliment(num2);
    
    if(num2 == 0)
        return num1;
    
    while(num2){
        
        int borrow = (~num1) & num2;
        num1 = num1 ^ num2;
        
        
        num2 = borrow<<1;
    }
    
    //Setting flags
    set_zero(num1);
    set_sign(num1);
    set_carry(n1,n2, num1);
    set_overflow_sub(n1, n2, num1);
    
    //Storing result in register
    set_register(reg2,num1);
    
    
    return num1;
    
    
}


//Function for multiplying two registers MUL R1,R2 => R2 = R2 * R1 
int mul(char* reg1, char* reg2) {
	
    int num1 = get_register(reg1);
    int num2 = get_register(reg2);
    int product = 0;
    int negflag = 0;
    
    printf("\n Value of reg1 %s", reg1);
    printf("\n Value of reg2 %s", reg2);
    printf("\n Value of num1 %d", num1);
    printf("\n Value of num2 %d", num2);
   
    if (num1 == 0 || num2 == 0){
	    return 0;
    }	    
    else if (num1 ==1){ 
	return num2;
    }
    else if (num2 ==1){
    	return num1;
    }
    else if ((num1 < 0 && num2 > 0) || (num1 > 0 && num2 < 0)){
         negflag = 1;
    }
    else if (num1 <0 && num2 < 0){
    	num1 = abs(num1);
	num2 = abs(num2);
    }
    while(num2 != 0){ 
    	if (num2 & 0x01){
	    product  = add(product,num1);
	}
	num1 <<= 1;
	num2 >>= 1;
    }
    if (negflag){
        product  = add(~product,1);
    }
    
    //Setting flags
    set_zero(product);
    set_sign(product);
    
    //Storing result in register
    set_register(reg2,product);
    
    return product;
}


//function for load_effective adress function

void call_leaq(int d,char *rb, char *ri,int s,char *dest_reg)
{

    int final_addr=0;
    
    int rb_value = get_register(rb);
    int ri_value = get_register(ri);
    
    final_addr= d+rb_value+(s*ri_value);
    
    printf("Effective address loaded by leaq is : %d", final_addr);
    
    set_register(dest_reg,final_addr);
    
    return;
    
}

//Function for storing the instruction to the memory
void storeInstructionToMemory(char *filename){
    
    char inst[NUMBER_OF_INSTRUCTIONS];
    int lines = 0;
    char *split = (char *) malloc(16);
    char * str = (char *) malloc(16);
    
    FILE *instructions_file;
    
    instructions_file = fopen(filename,"r");
    
    if (instructions_file == 0){
        printf("\nError in opening the file containing the instructions \n");
    }
    
    while (fgets(inst,NUMBER_OF_INSTRUCTIONS,instructions_file) != NULL){
        lines++;
    }
    
    instructions_file = fopen(filename,"r");
    
    while (lines != 0){
        fgets(inst,NUMBER_OF_INSTRUCTIONS,instructions_file);
        char *operation;
        char *register1;
        char *register2;
        char *Rb;
        char *Ri;
        char *dest;
        int S=0,D=0;
    
        char *binary_reg1 = (char*) malloc(10);
        char *binary_reg2 = (char*) malloc(10);
    
        int address;
        char code[34] = "";
    
        int mod_result;
    
        int argNum = 0;

        
        strcpy(str,inst);
        split = strtok(str, " ,.-()");
        while(split != NULL)
        {
            if(argNum == 0)
            {                    //opcode parsing
                if(strcmp(split, "FETCH")==0){
                    strcat(code, "00000");
                    operation = split;
                }
                else if(strcmp(split, "STORE")==0){
                    strcat(code, "00001");
                    operation = split;
                }
                else if(strcmp(split, "ADD")==0){
                    strcat(code, "00010");
                    operation = split;
                }
                else if(strcmp(split, "SUB")==0){
                    strcat(code, "00011");
                    operation = split;
                }
                else if(strcmp(split, "MUL")==0){
                    strcat(code, "00100");
                    operation = split;
                }
                else if(strcmp(split, "DIV")==0){
                    strcat(code, "00101");
                    operation = split;
                }
                else if(strcmp(split, "MOD")==0){
                    strcat(code, "00110");
                    operation = split;
                }
                else if(strcmp(split, "LEAQ")==0){
                    strcat(code, "00111");
                    operation = split;
                }
                argNum++;
                printf("\nOpcode: in string: %s And in binary: %s \n", operation, code);
            }
            
            else if(argNum == 1)
            {
                
                if(strcmp(operation,"LEAQ")==0)
                {
                    
                    D = atoi(split);
                    //printf("inside D variable extract %d\n", D);
                    argNum++;
                    
                }
                else
                {
                    //register1
                    register1 = split;
                    int reg1 = split[1] - '0';
                    int bin1 = decimalToBinary(reg1);
                    
                    sprintf(binary_reg1, "%d", bin1);
                    
                    
                    int len = 5 - strlen(binary_reg1);
                    memmove(binary_reg1+len, binary_reg1, strlen(binary_reg1));
                    for ( int i = 0; i < len; i++ ){
                        binary_reg1[i] = '0';
                    }
                    strcat(code, binary_reg1);
                    printf("Register1: %s \n", binary_reg1);
                    argNum++;
                }
            }
            
            else if(argNum == 2)
            {
                if((strcmp(operation,"FETCH")==0)||(strcmp(operation,"STORE")==0))
                {
                    
                    printf("inside memory vaibale extract\n");
                    //memory
                    int addr = atoi(split);
                    address = addr;
                    char *memAddr = (char*) malloc(17);
                    strcpy(memAddr,decToBin(addr));
                    
                    int len = 17 - strlen(memAddr);
                    memmove(memAddr+len, memAddr, strlen(memAddr));
                    for ( int i = 0; i < len; i++ )
                        memAddr[i] = '0';
                    
                    //unused register 2 value
                    strcat(code, "00000");
                    printf("Memory Address:%s\n", memAddr);
                    strcat(code, memAddr);
                    printf("\nCode to store in memory in binary: %s \n", code);
                    int instruction = strtol(code,NULL,2);
                    
                    MEMORY[PC/4] = instruction ; // Store the instruction in Memory starting from the IM start address
                    printf("Final code to store in memory in int: %d\n", instruction);
                    printf("instruction code is = %d and memory location at which it is stored is = %d\n", instruction, PC/4);
                    printf("Memory[PC/4] = %d\n", MEMORY[PC/4]);
                    
                    char* instructionBinary = decimal_to_binary(instruction, 32);
                    
                    PC += 4 ;
                    argNum++;
                    
                }
                else if(strcmp(operation,"LEAQ")==0)
                {
                    Rb = split;
                    argNum++;
                    
                }
                
                else if(strcmp(operation,"ADD")==0 ||
                        strcmp(operation,"SUB")==0 ||
                        strcmp(operation,"DIV")==0 ||
                        strcmp(operation,"MUL")==0 ||
                        strcmp(operation,"MOD")==0)
                {
                    //register 2
                    register2 = split;
                    int reg2 = split[1] - '0';
                    int bin2 = decimalToBinary(reg2);
                    sprintf(binary_reg2, "%d", bin2);
                    
                    
                    int len = 5 - strlen(binary_reg2);
                    memmove(binary_reg2+len, binary_reg2, strlen(binary_reg2));
                    for ( int i = 0; i < len; i++ ){
                        binary_reg2[i] = '0';
                    }
                    strcat(code, binary_reg2);
                    printf("Register2: %s \n", binary_reg2);
                    strcat(code, "00000000000000000");         //UNUSED ADDRESS PART IN THE INSTRUCTION
                    int instruction = strtol(code,NULL,2);
                    MEMORY[PC/4] = instruction;                //INSTRUCTION STORED IN THE MEMORY
                    printf("Final code of ALU instruction to store in memory is = %s\n", code);
                    printf("Storing at address = %d\n",PC/4);
                    printf("INSTRUCTION IS = %d\n", instruction);
                    PC += 4;
                    
                    argNum++;
                }
            }
            else if(argNum == 3)
            {
                
                if(strcmp(operation,"LEAQ")==0)
                {
                    Ri = split;
                    argNum++;
                }
                
            }
            else if(argNum == 4)
            {
                
                if(strcmp(operation,"LEAQ")==0)
                {
                    
                    S = atoi(split);
                    //printf("inside S variable extract %d\n",S);
                    argNum++;
                    
                }
                
            }
            else if(argNum == 5)
            {
                
                if(strcmp(operation,"LEAQ")==0)
                {
                    
                    dest = split;
                    argNum++;
                    
                }
                
            }
            
            split = strtok(NULL, " ,.- ()\n");
            
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
            
            call_mod(register1, register2);
            
        }
        else if (strcmp(operation, "DIV")==0)
        {
            int dividend = get_register(register1);
            int divisor = get_register(register2);
            
            int divisionResult= division(dividend, divisor, divisor, 0);		//Initially we send remainder as '0'.
            set_register(register2, divisionResult);
            
            printf("Division Quotient: %d \n", divisionResult);
        }
        else if(strcmp(operation, "ADD")==0){
            int num1 = get_register(register1);
            int num2 = get_register(register2);
            int sum = add(num1,num2);
            printf("Addition result: %d \n", sum);
        }
        else if(strcmp(operation, "SUB")==0){
            int difference = sub(register1, register2);
            printf("Subtraction result: %d \n", difference);
        }
        else if(strcmp(operation, "MUL")==0){
            int product  = mul(register1, register2);
            printf("\n Multiplication result: %d \n", product);
        }
        else if(strcmp(operation, "LEAQ")==0)
        {
            
            call_leaq(D,Rb,Ri,S,dest);
            
        }
        
        printf("\n========================Values after executing instruction : %s ================================", operation) ;
        print_values();
        
        lines--;
    }
    
    fclose(instructions_file);
    return;
    
}
void print_values(){
    
    printf("\n\nThe PC value is %d\n",PC);
    printf("The FLG value is %d\n", FLG);
    printf("The SP value  is %d\n", SP);
    printf("The RA value  is %d\n\n", RA);
    
    printf("The value in register R0 is %d\n", r0);
    printf("The value in register R1 is %d\n", r1);
    printf("The value in register R2 is %d\n", r2);
    printf("The value in register R3 is %d\n", r3);
    printf("The value in register R4 is %d\n", r4);
    printf("The value in register R5 is %d\n", r5);
    printf("The value in register R6 is %d\n", r6);
    printf("The value in register R7 is %d\n\n", r7);
    
    return;
    
}


int main(int argc, char *argv[]){
    MEMORY[20000] = 222;             //LETS ASSUME AT THAT MOMENT MEMORY[20000], i.e. memory address 80000 HAS A VALUE 222 AND TRY TO FETCH IT.
    printf("\n========================Initial values before execution===========================") ;
    print_values();
    // read_instructions();
    storeInstructionToMemory(argv[1]);
    
    
    return 0;
}
