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

char* decToBin(int n){
    printf("Num %d", n);
    char binary[16] = {0};
    int rem, i = 15;
    while(n != 0){
        rem = n%2;
        n = n/2;
        //printf("rem + 0 %c", (rem+'0'));
        binary[i] = rem + '0';
        i--;
        
    }
    printf("binary: %s\n", binary);
    return binary;
}


//Function for storing the instruction to the memory
void storeToMemory(char *inst){
    
    char *split = (char *) malloc(16);
    char * str = (char *) malloc(16);
    strcpy(str,inst);
    
    char code[33] = "";
    
    int argNum = 0;
    split = strtok(str, " ,.-");
    printf("Split: %s\n", split);
    while(split != NULL){
        if(argNum == 0){                    //opcode parsing
            if(strcmp(split, "FETCH")==0){
                strcat(code, "00000");
            }
            else if(strcmp(split, "STORE")==0){
                strcat(code, "00001");
            }
            argNum++;
            printf("code: %s %lu\n", code, sizeof(code));
        }
        
        else if(argNum == 1){              //register
            printf("Split: %s\n", split);
            int reg = split[1] - '0';
            int bin = decimalToBinary(reg);
            char binary[5];
            sprintf(binary, "%d", bin);
            
            int len = 10 - strlen(binary);
            memmove(binary+len, binary, strlen(binary));
            for ( int i = 0; i < len; i++ )
                binary[i] = '0';
            
            strcat(code, binary);
            printf("code: %s %lu\n", code, sizeof(code));
            argNum++;
        }
        
        else if(argNum == 2){
            printf("Split: %s\n", split);
            int addr = atoi(split);
            printf("Addr: %d\n", addr);
            //  "1100110011111111"
            //long binAddr = decimalToBinary(addr);
            //printf("binAddr %lu", binAddr);
            char memAddr[17];
            strcpy(memAddr,decToBin(addr));
            
            /*int len = 16 - strlen(memAddr);
            memmove(memAddr+len, memAddr, strlen(memAddr));
            for ( int i = 0; i < len; i++ )
                memAddr[i] = '0';
            */
            printf("MemAddr: %s\n", memAddr);
            strcat(code, memAddr);
            printf("code: %s %lu\n", code, sizeof(code));
            argNum++;
            
        }
        split = strtok(NULL, " ,.-");
        
    }
    return;
    
    
}


int main(int argc, char **argv)

{
    // General Purpose registers r0-r7
    int  r0, r1, r2, r3, r4, r5, r6, r7;

    int PC;                    // Program Counter
    int MAR;                   // Memory Address
    int MDR;                   // Memory Data Register
    int FLG;                   // Flag register
    int SP;                    // Stack Pointer
    int RA;                    // Return Address register
    const int ZERO = 0;        // Zero Address Register
    
    for(int i=1; i< argc; i++) {
        printf("%s\n", argv[i]);
        storeToMemory(argv[i]);
        //execute(argv[i]);
    }
    

    //int binaryArray = convertBinary(10);
 
    return 0 ;
}
