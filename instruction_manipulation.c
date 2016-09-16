//
//  instructions.c
//  
//
//  Created by Vishnu, Priya on 9/15/16.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 33



char *inttobinary(int num, char *buf, int bufSize) {
    buf += (bufSize - 1);
    
    for (int i = 0; i <= 31; i++ , num >>= 1) {
        *buf-- = (num & 1) + '0';

    }
    
    return buf;
}




int main(){
    
    
    int i ;
    
    // Have hard coded opcode, regvalue and memvale for now.. Just an example
    
    char opcode[30] = "000100" ;
    char regvalue[50] = "11100" ;
    char memvalue[50] = "000000000011000001" ;
    
    
    int Memory[655356] = {0};
    char inst[50] = {0};
    int instruction = 0 ;
    int output[32] = {0};
    int size = 0;
    
    char buffer[BUF_SIZE];
    buffer[BUF_SIZE - 1] = '\0';
    

    
    strcat(opcode,regvalue) ;
    strcat(opcode,memvalue) ;
    
    
    printf("Complete Instruction in binary is %s\n",opcode) ;
    
    instruction = strtol(opcode,NULL,2);
    printf("\n Instruction Converted to int %d\n",instruction);
    
    Memory[10000] = instruction ;
    
    printf("\n instruction in memory = %d \n", Memory[10000]);
    
    // Converting int back to binary string to read the instruction back from memory
    
    inttobinary(Memory[10000], buffer, BUF_SIZE - 1);
    
    printf(" \n instruction read from memory back to binary string = %s \n", buffer);
    
    
    return 0;
}
