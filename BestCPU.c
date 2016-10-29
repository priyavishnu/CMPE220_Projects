/*  BestCPU.c
 32 bit architecture */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define INSTRUCTION_MEMORY_BASE    	 10000
#define BOOT_MEMORY_BASE                     0
#define MEM_MAX                        	 65535
#define NUMBER_OF_INSTRUCTIONS              30
#define STACK_BASE                       15000
#define LABEL_MAX                          100

// Initialization of all the components 

int MEMORY[MEM_MAX + 1] = {0};   // Memory

// General Purpose registers r0-r7
int     r0 = 0, 
        r1 = 0,
        r2 = 0,
        r3 = 0,
        r4 = 0, 
        r5 = 0, 
        r6 = 0, 
        r7 = 0;


int         PC = 40000;            // Program Counter(Initiating the instruction memory[IM] address from MEMORY[10000], i.e. memory address 40000. Needs to be changed for booting OS later)
int         MAR;                   // Memory Address
int         MDR;                   // Memory Data Register
int         FLG;                   // Flag register
int         SP;                    // Stack Pointer
int         RA;                    // Return Address register
const int   ZERO = 0;               // Zero Address Register


// An array to store the Label names with thier index equal to the line number
char labels[LABEL_MAX][20] = {0};



/* Opcodes */

/*	FETCH 	= 00000,
	STORE 	= 00001,
	ADD	    = 00010,
	SUB	    = 00011,
	MUL	    = 00100
	DIV	    = 00101,
	MOD	    = 00110,
	LEAQ 	= 00111,
	CMPQ    = 01000,
    TEST	= 01001,
        	= 01010,
	       	= 01011,
	       	= 01100,
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

//Function to fetch the value from specified memeory location to register
void execute_Fetch(char *operation, char *reg, int address){
    char *FETCH = "FETCH";
    char *R0 = "R0";            //JUST FOR COMPARING WHICH REGISTER IS RECEIVED AS PARAMETER.
    char *R1 = "R1";
    char *R2 = "R2";
    char *R3 = "R3";
    char *R4 = "R4";
    char *R5 = "R5";
    char *R6 = "R6";
    char *R7 = "R7";
    
    printf("\n\nReceived parameters are: \n\tOperation = %s, Register = %s, Address = %d\n", operation, reg, address);
    
    int index = address/4;
   
    int i = 0;
    int reg_val=0;

    
    if(strcmp(reg,R0) == 0){
        r0 = MEMORY[index];
        
    }
    else if(strcmp(reg,R1) == 0){
        r1 = MEMORY[index];
    }
    else if(strcmp(reg,R2) == 0){
        r2 = MEMORY[index];
    }
    else if(strcmp(reg,R3) == 0){
        r3 = MEMORY[index];
       
    }
    else if(strcmp(reg,R4) == 0){
        r4 = MEMORY[index];
    }
    else if(strcmp(reg,R5) == 0){
        r5 = MEMORY[index];
    }
    else if(strcmp(reg,R6) == 0){
        r6 = MEMORY[index];
    }
    else if(strcmp(reg,R7) == 0){
        r7 = MEMORY[index];
    }
    
    reg_val=get_register(reg);
    printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], reg, reg_val);
    
    MAR = address;
    MDR = MEMORY[index];
    printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
    
}

//Function to store the register value to specified memeory location
void execute_store(char *operation, char *reg, int address){
    char *STORE = "STORE";
    char *R0 = "R0";
    char *R1 = "R1";
    char *R2 = "R2";
    char *R3 = "R3";
    char *R4 = "R4";
    char *R5 = "R5";
    char *R6 = "R6";
    char *R7 = "R7";
       
    printf("\n\nReceived parameters are: \n\tOperation = %s, Register = %s, Address = %d\n", operation, reg, address);
    
    int index = address/4;

    int i = 0;
    int reg_val=0;
    
    if(strcmp(operation, STORE) == 0)
    {
        if(strcmp(reg,R0) == 0){
            MEMORY[index] = r0;
        }
        else if(strcmp(reg,R1) == 0){
            MEMORY[index] = r1;
        }
        else if(strcmp(reg,R2) == 0){
            MEMORY[index] = r2;
        }
        else if(strcmp(reg,R3) == 0){
            MEMORY[index] = r3;
        }
        else if(strcmp(reg,R4) == 0){
            MEMORY[index] = r4;
        }
        else if(strcmp(reg,R5) == 0){
            MEMORY[index] = r5;
        }
        else if(strcmp(reg,R6) == 0){
            MEMORY[index] = r6;
        }
        else if(strcmp(reg,R7) == 0){
            MEMORY[index] = r7;
        }
        
    }
    
    reg_val=get_register(reg);
    printf("\tData at location %d is %d \n\tValue in Register %s now is %d\n", address, MEMORY[index], reg, reg_val);
    
    MAR = address;
    MDR = MEMORY[index];
    printf("\tThe MAR value %d\n\tThe MDR value %d\n\n", MAR, MDR);
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

//Function to set carry flag for division
void set_carry_div(){
    //printf("IN carry div\n");
    FLG = FLG | 0x04;
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

//Function to set overflow for div
void set_overflow_div(){
    //printf("IN overflow div\n");
    FLG = FLG | 0x08;
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
    
    printf("\n ******** RESULT ******** \n"); 
    printf("\n Mod result: %d \n", rmd);
    
    return;
    
}

//Function for adding two values
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


//Function for adding two registers ADD R1, R2 =>  R2 = R1 + R2
void call_add(char* reg1, char* reg2){
    
    int num1 = get_register(reg1);
    int num2 = get_register(reg2);
    int sum = add(num1,num2);;
    set_register(reg2, sum);
    
    printf("\n ******** RESULT ******** \n");
    printf("Addition result: %d \n", sum);
}

//Function to find twos compliment of a number
int twosCompliment (int num){
    num = ~(num);
    num = add(num, 1);
    return num;
}


//Function for subtracting two registers SUB R1, R2 =>  R2 = R1 - R2
void sub(char* reg1, char* reg2){

    int num1 = get_register(reg1);
    int num2 = get_register(reg2);

    int n1 = num1, n2 = twosCompliment(num2);
    
    if(num2 == 0){
        printf("Subtraction result: %d \n",num1);
      //Setting flags
        set_zero(num1);
        set_sign(num1);
        set_carry(n1,n2, num1);
        set_overflow_sub(n1, n2, num1);
    
    //Storing result in register
       set_register(reg2,num1);
        return;
    }
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
    
    printf("\n ******** RESULT ******** \n"); 
    printf("Subtraction result: %d \n", num1);
    return;
    
    
}


//Function for multiplying two registers MUL R1,R2 => R2 = R2 * R1 
void  mul(char* reg1, char* reg2) {
	
    int num1 = get_register(reg1);
    int num2 = get_register(reg2);
    int product = 0;
    
    if (num1 == 0 || num2 == 0){

        printf("\n Multiplication result: %d \n", product);
        set_register(reg2,product);
      //Setting flags
        set_zero(product);
        set_sign(product);
	return ;
    }	    
    else if (num1 ==1){ 
        product = num2;
        printf("\n Multiplication result: %d \n", product);
        set_register(reg2,product);
      //Setting flags
        set_zero(product);
        set_sign(product);
        return;
    }
    else if (num2 ==1){
	product = num1;	
        printf("\n Multiplication result: %d \n", product);
        set_register(reg2,product);
      //Setting flags
        set_zero(product);
        set_sign(product);
    	return;
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
    
    //Setting flags
    set_zero(product);
    set_sign(product);
    
    //Storing result in register
    set_register(reg2,product);
    
    printf("\n ******** RESULT ******** \n"); 
    printf("\n Multiplication result: %d \n", product);
    return ;
}

//Function for ALU Division. Here (Register1 = Dividend) And (Register2 = Divisor)
//Original Divisor will be Divisor in the next recursion.

int division(int dividend, int divisor, int originalDivisor, int remainder)
{
    int quotient = 1;
    int signFlag = 0;
    
    //printf("DIVIDEND %d     DIVISOR %d \n", dividend, divisor);
    
    if(dividend == -2147483648 && divisor == -1){
        set_overflow_div();
        set_carry_div();
        return 0;
    }
    
    if(dividend < 0){
        printf("DIVIDEND %d\n", dividend);
        signFlag = signFlag ^ 0x01;
        dividend = twosCompliment(dividend);
    }
    if(divisor < 0){
        printf("DIVISOR %d\n", divisor);
        signFlag = signFlag ^ 0x01;
        divisor = twosCompliment(divisor);
        printf("DIVISOR %d\n", divisor);
    }
    if(originalDivisor < 0){
        originalDivisor = twosCompliment(originalDivisor);
        
    }

    
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
    
    //quotient = quotient + division(dividend - divisor, originalDivisor, originalDivisor, remainder);
    
    quotient = add (quotient, division(dividend - divisor, originalDivisor, originalDivisor, remainder));
    
    if(signFlag){
        quotient = twosCompliment(quotient);
    }

    
    //Setting flags
    set_zero(quotient);
    set_sign(quotient);
    
    
    
    //Storing result in register
    return quotient;
}




//function for load_effective adress function

void call_leaq(int d,char *rb, char *ri,int s,char *dest_reg)
{

    int final_addr=0;
    
    int rb_value = get_register(rb);
    int ri_value = get_register(ri);
    
    final_addr= d+rb_value+(s*ri_value);
    
    printf("\n ******** RESULT ******** \n"); 
    printf("Effective address loaded by leaq is : %d", final_addr);
    
    set_register(dest_reg,final_addr);
    
    return;
    
}


//function call for test instruction whihc will be set flag depend upon test operation.and will not chnage any register value.
void call_test(char *reg1, char *reg2)
{
    int num1 = get_register(reg1);
    int num2 = get_register(reg2);
    
    int result = 0;
    
    if (num1 == 0 || num2 == 0)
    {
        result=0;
    }
    else if (num1 ==1)
    {
        result = num2;
    }
    else if (num2 ==1)
    {
        result = num1;
    }
    else
    {
        result= num1 & num2;
    }
    
    //Setting flags
    set_zero(result);
    set_sign(result);

    return;
}

//function call for cmpq instruction whihc will be set flag depend upon test operation.and will not chnage any register value.
void call_cmpq(char *reg1, char *reg2)
{
    int num1 = get_register(reg1);
    int num2 = get_register(reg2);
    
    int result = 0;
    
    if (num1 == 0 || num2 == 0)
    {
        result=0;
    }
    
    //Setting flags
    set_zero(result);
    set_sign(result);
    
    return;
}


// Function to save the label names in an array with index equal to the line number
void set_label_line_number(char *inst,int lines){
    
    char *label;
    char temp[100];
    memset(temp, '\0', sizeof(temp));
    strcpy(temp, inst);
    label = strtok(temp, ":");
    strcpy(labels[lines], label);
    
    printf("\n The substring is: %s\n", labels[lines]);
    printf("The line value is: %d\n", lines);
}

//Function that returns the line number matching the label name.
int get_line(char *label){
    
    printf("The input label is: %s\n", label);
    int i,v;
    
    for (i=0; i < LABEL_MAX ; i++){
        
        if (labels[i] != NULL){
            printf("The saved labels is: %s\n", labels[i]);
            printf("The i value is: %d\n", i);
            v = strcmp(labels[i],label);
            if(v == 0)
                return i;
        }
    }
    
    printf("\n Invalid label name \n");
    return -1;
    
}


//Function for storing the instruction to the memory
void storeInstructionToMemory(char *filename){
    
    char inst[NUMBER_OF_INSTRUCTIONS];
    int lines = 0;
    char *label_string;
    char *split = (char *) malloc(16);
    char * str = (char *) malloc(16);
    
    
    FILE *instructions_file;
    
    instructions_file = fopen(filename,"r");
    
    if (instructions_file == 0){
        printf("\nError in opening the file containing the instructions \n");
    }
    
    while (fgets(inst,NUMBER_OF_INSTRUCTIONS,instructions_file) != NULL){
        label_string = strstr(inst, ":");
        if (label_string != NULL){
            set_label_line_number(inst,lines);
        }
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
        char *binary_regrb = (char*) malloc(10);
        char *binary_regri = (char*) malloc(10);
        char *binary_regrd = (char*) malloc(10);
        
        
    
        int address;
        
        char code[34] = "";
        int instruction;

        int mod_result;
        
        label_string = strstr(inst, ":");
        
        if (label_string == NULL){
            
            strcpy(str,inst);
            split = strtok(str, " ,.-()");
        
        }
        
        else if (label_string != NULL){
            
            strtok(inst, ":");
            split = strtok(NULL," ");
            printf("The parsed label is: %s\n", split);
        }
    
        int argNum = 0;

        

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
                else if(strcmp(split, "CMPQ")==0){
                    strcat(code, "01000");
                    operation = split;
                }
                else if(strcmp(split, "TEST")==0){
                    strcat(code, "01001");
                    operation = split;
                }
                else if(strcmp(split, "JUMP")==0){
                    strcat(code, "01010");
                    operation = split;
                }
                argNum++;
                printf("\n \n ************ Now executing Instruction: %s ************* \n", operation);
                printf("\nOpcode: in string: %s And in binary: %s \n", operation, code);
            }
            
            else if(argNum == 1)
            {
                if(strcmp(operation,"JUMP")==0)
                {
                    int line_no;
                    label_string = split;
                    printf("The parsed label is: %s\n", label_string);
                    line_no = get_line(label_string);
                    printf("The line no obtained is: %d\n", line_no);
                    char* address_offset = decimal_to_binary(line_no, 27);
                    printf("Binary address offset to jump = %s\n", address_offset);
                    
                    strcat(code, address_offset);
                    printf("Binary code for jump = %s\n", code);
                    instruction = strtol(code,NULL,2);
                    printf("Binary instruction for jump = %d\n", instruction);
                    MEMORY[PC/4] = instruction;             //INSTRUCTION STORED IN THE MEMORY
                    argNum++;
                
                }
                
                
                else if(strcmp(operation,"LEAQ")==0)
                {
                    
                    D = atoi(split);
                    if (D==0)
                        S=0;
                    
                    char *memD = (char*) malloc(17);
                    strcpy(memD,decToBin(D));
                    int i = 0;
                    int len = 9 - strlen(memD);
                    memmove(memD+len, memD, strlen(memD));
                    for (i = 0; i < len; i++ )
                        memD[i] = '0';

                    strcat(code, memD);
                    printf("Register1: %s \n", memD);
                    //printf("inside D variable extract %d\n", D);
                    instruction = strtol(code,NULL,2);
                    MEMORY[PC/4] = instruction;                //INSTRUCTION STORED IN THE MEMORY
                    argNum++;
                    
                }
                else
                {
                    //register1
                    register1 = split;
                    int reg1 = split[1] - '0';
                    int bin1 = decimalToBinary(reg1);
                    
                    sprintf(binary_reg1, "%d", bin1);
                    
                    int i = 0;
                    int len = 5 - strlen(binary_reg1);
                    memmove(binary_reg1+len, binary_reg1, strlen(binary_reg1));
                    for (i = 0; i < len; i++ ){
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
                    int i = 0;
                    int len = 17 - strlen(memAddr);
                    memmove(memAddr+len, memAddr, strlen(memAddr));
                    for (i = 0; i < len; i++ )
                        memAddr[i] = '0';
                    
                    //unused register 2 value
                    strcat(code, "00000");
                    printf("Memory Address:%s\n", memAddr);
                    strcat(code, memAddr);
                    printf("\nCode to store in memory in binary: %s \n", code);
                    
                    instruction = strtol(code,NULL,2);
                    MEMORY[PC/4] = instruction ; // Store the instruction in Memory starting from the IM start address
                    printf("Final code to store in memory in int: %d\n", instruction);
                    printf("instruction code is = %d and memory location at which it is stored is = %d\n", instruction, PC/4);
                    printf("Memory[PC/4] = %d\n", MEMORY[PC/4]);
                    
                    argNum++;
                    
                }
                else if(strcmp(operation,"LEAQ")==0)
                {
                    Rb = split;
                    int regb = split[1] - '0';
                    int binrb = decimalToBinary(regb);
                    
                    sprintf(binary_regrb, "%d", binrb);
                    
                    int i = 0;
                    int len = 5 - strlen(binary_regrb);
                    memmove(binary_regrb+len, binary_regrb, strlen(binary_regrb));
                    for (i = 0; i < len; i++ ){
                        binary_regrb[i] = '0';
                    }
                    strcat(code, binary_regrb);
                    printf("Register Rb: %s \n", binary_regrb);

                    instruction = strtol(code,NULL,2);
                    MEMORY[PC/4] = instruction;                //INSTRUCTION STORED IN THE MEMORY

                    argNum++;
                    
                }
                
                else if(strcmp(operation,"ADD")==0 ||
                        strcmp(operation,"SUB")==0 ||
                        strcmp(operation,"DIV")==0 ||
                        strcmp(operation,"MUL")==0 ||
                        strcmp(operation,"MOD")==0 ||
                        strcmp(operation,"CMPQ")==0 ||
                        strcmp(operation,"TEST")==0 )
                {
                    //register 2
                    register2 = split;
                    int reg2 = split[1] - '0';
                    int bin2 = decimalToBinary(reg2);
                    sprintf(binary_reg2, "%d", bin2);
                    
                    int i = 0;
                    int len = 5 - strlen(binary_reg2);
                    memmove(binary_reg2+len, binary_reg2, strlen(binary_reg2));
                    for (i = 0; i < len; i++ ){
                        binary_reg2[i] = '0';
                    }
                    strcat(code, binary_reg2);
                    printf("Register2: %s \n", binary_reg2);
                    strcat(code, "00000000000000000");         //UNUSED ADDRESS PART IN THE INSTRUCTION
                    instruction = strtol(code,NULL,2);
                    MEMORY[PC/4] = instruction;                //INSTRUCTION STORED IN THE MEMORY
                    printf("Final code of ALU instruction to store in memory is = %s\n", code);
                    printf("Storing at address = %d\n",PC/4);
                    printf("INSTRUCTION IS = %d\n", instruction);
                    
                    argNum++;
                }
            }
            else if(argNum == 3)
            {
                
                if(strcmp(operation,"LEAQ")==0)
                {
                    Ri = split;
                    int regi = split[1] - '0';
                    int binri = decimalToBinary(regi);
                    
                    sprintf(binary_regri, "%d", binri);
                    
                    int i = 0;
                    int len = 5 - strlen(binary_regri);
                    memmove(binary_regri+len, binary_regri, strlen(binary_regri));
                    for (i = 0; i < len; i++ ){
                        binary_regri[i] = '0';
                    }
                    strcat(code, binary_regri);
                    printf("Register Ri: %s \n", binary_regri);

                    instruction = strtol(code,NULL,2);
                    MEMORY[PC/4] = instruction;                //INSTRUCTION STORED IN THE MEMORY

                    argNum++;
                }
                
            }
            else if(argNum == 4)
            {
                
                if(strcmp(operation,"LEAQ")==0)
                {
                    
                    S = atoi(split);
                    
                    if (S==0)
                        S=0;
                    
                    char *memS = (char*) malloc(17);
                    strcpy(memS,decToBin(S));
                    int i = 0;
                    int len = 3 - strlen(memS);
                    memmove(memS+len, memS, strlen(memS));
                    for (i = 0; i < len; i++ )
                        memS[i] = '0';
                    
                    strcat(code, memS);
                    printf("S: %s \n", memS);
                    //printf("inside S variable extract %d\n",S);
                    
                    instruction = strtol(code,NULL,2);
                    MEMORY[PC/4] = instruction;                //INSTRUCTION STORED IN THE MEMORY
                    if(!(argNum ==5)){
                        printf("Final code of ALU instruction to store in memory is = %s\n", code);
                        printf("Storing at address = %d\n",PC/4);
                        printf("INSTRUCTION IS = %d\n", instruction);
                    }
                    argNum++;
                    
                }
                
            }
            else if(argNum == 5)
            {
                
                if(strcmp(operation,"LEAQ")==0)
                {
                    
                    dest = split;
                    int regd = split[1] - '0';
                    int binrd = decimalToBinary(regd);
                    
                    sprintf(binary_regrd, "%d", binrd);
                    
                    int i = 0;
                    int len = 5 - strlen(binary_regrd);
                    memmove(binary_regrd+len, binary_regrd, strlen(binary_regrd));
                    for (i = 0; i < len; i++ ){
                        binary_regrd[i] = '0';
                    }
                    strcat(code, binary_regrd);
                    printf("Register Rd: %s \n", binary_regrd);

                    instruction = strtol(code,NULL,2);
                    MEMORY[PC/4] = instruction;                //INSTRUCTION STORED IN THE MEMORY
                    printf("Final code of ALU instruction to store in memory is = %s\n", code);
                    printf("Storing at address = %d\n",PC/4);
                    printf("INSTRUCTION IS = %d\n", instruction);

                    argNum++;
                    
                }
                
            }
            
            split = strtok(NULL, " ,.- ()\n");
            
        }
        
/*------------------------------FETCHING INSTRUCTION FROM MEMORY-----------------------------------------------*/
        char* instrucitonBinaryToExecute = decimal_to_binary(MEMORY[PC/4], 32);
        printf("***---Reading Instruction From Memory---***\n");
        printf("Binary Instruction Fetched From Memory Pointed By PC = %s\n", instrucitonBinaryToExecute);
        
        int i;
        char opCodeBinary[5];

        for(i = 0; i < 5; i++){
            opCodeBinary[i] = instrucitonBinaryToExecute[i];
        }
        int opCodeInt = strtol(opCodeBinary,NULL,2);
        printf("OP Code of the instruction is = %s\n", opCodeBinary);
        printf("OP code in decimal is = %d\n", opCodeInt);


        
	//Using Function pointers for ALU operations. Since div and add use different function parameters, have used different function pointers for them
	
	void (*fun_ptr_arr[])(char*,char*) = {call_mod,sub,mul,call_add};
	int (*fun_ptr_arr_div[])(int,int,int,int) = {division};
	int (*fun_ptr_arr_add[])(int,int) = {add};

    int dividend;
    int divisor;
    int divisionResult;

    switch(opCodeInt){
        case 0: execute_Fetch(operation, register1, address);
                break;
        case 1: execute_store(operation, register1, address);
                break;
        case 2: (*fun_ptr_arr[3])(register1, register2);
                break;
        case 3: (*fun_ptr_arr[1])(register1, register2);
                break;
        case 4: (*fun_ptr_arr[2])(register1, register2);    
                break;
        case 5: dividend = get_register(register1);
                divisor = get_register(register2);
                divisionResult= (*fun_ptr_arr_div[0])(dividend, divisor, divisor, 0);       //Initially we send remainder as '0'.
                set_register(register2, divisionResult);
                printf("\n ******** RESULT ******** \n"); 
                printf("Division Quotient: %d \n", divisionResult);
                break;
        case 6: (*fun_ptr_arr[0])(register1, register2);
                break;
        case 7: call_leaq(D,Rb,Ri,S,dest);
                break;
        case 8: call_cmpq(register1, register2);
                break;
        case 9: call_test(register1, register2);
                break;
        case 10: printf("\n Jump to be implemented after Tarshith's integration\n");
                break;
        default: printf("UNEXPECTED OPCODE, PLEASE CHECK IF YOU ADDED THE OPERATION INTO THE INSTRUCTION SET ARCHITECTURE!");
    }
    printf("\n\n========================Values after executing instruction : %s ==================\n", operation) ;
    print_values();
    PC += 4;    
    lines--;
    }
    fclose(instructions_file);
    return;
    
}
void print_values(){
    
    
    printf("\n\n========================Values of Special Registers ================================") ;
    printf("\n\nThe PC value is %d\n",PC);
    printf("The FLG value is %d\n", FLG);
    printf("The SP value  is %d\n", SP);
    printf("The RA value  is %d\n\n", RA);
    
    printf("\n========================Values of General Purpose Registers =========================") ;
    printf("\n \nThe value in register R0 is %d\n", r0);
    printf("The value in register R1 is %d\n", r1);
    printf("The value in register R2 is %d\n", r2);
    printf("The value in register R3 is %d\n", r3);
    printf("The value in register R4 is %d\n", r4);
    printf("The value in register R5 is %d\n", r5);
    printf("The value in register R6 is %d\n", r6);
    printf("The value in register R7 is %d\n\n", r7);
    
    return;
    
}


void initialize_code_test() {		
    
    MEMORY[20000] = 222;	
    r0 = 1;
    r1 = 4;
    r2 = 20;
    r3 = 4;
    r4 = 5; 
    r5 = 6;
    r6 = 7; 
    r7 = 8;
    FLG = 0;	

}

int main(int argc, char *argv[]){
    printf("\n========================Initializing registers ==================================") ;
    initialize_code_test();
    printf("\n\n========================Initial values before execution =========================") ;
    print_values();
    // read_instructions();
    storeInstructionToMemory(argv[1]);
    
    
    return 0;
}

