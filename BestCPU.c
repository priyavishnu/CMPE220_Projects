//
//  BestCPU.c
//  
//
//  Created by Vishnu, Priya on 9/15/16.
// 16 bit architecture
//

#include <stdio.h>
#include <string.h>

/*int* convertBinary(int decimalNumber){
    int stroreBinaryArray[16] = {0};
    int i = 0;
    while(decimalNumber != 1){
        stroreBinaryArray[i] = (decimalNumber % 2);
        i++;
    }
    return stroreBinaryArray;
}*/
//
//int MEMORY[65536] = {0} ;
//
//int loadWord(char destinationRegister, char offset, char baseAddressRegister, char* MAR, char* MDR){
//    int tempLocal = atoi(offset) + atoi(baseAddressRegister);
//    destinationRegister = tempLocal
//    
//}
//
//int storeWord(int data, int offset, int baseAddress, int * MAR, int* MDR){
//
//}



int main()

{
    // General Purpose registers r0-r7
    //int i;
    //int* binary
    
    int  r0 ;
    int  r1 ;
    int  r2 ;
    int  r3 ;
    int  r4 ;
    int  r5 ;
    int  r6 ;
    int  r7 ;

    int PC ;                    // Program Counter
    
    int MAR ;                   // Memory Address
    
    int MDR ;                   // Memory Data Register
    
    int FLG ;                   // Flag register
    
    int SP ;                    // Stack Pointer
    
    int RA ;                    // Return Address register
    
    const int ZERO = 0;         // Zero Address Register
    
    int MEMORY[65536] = {0} ;   // Memory

    //int binaryArray = convertBinary(10);
    
    //r1 = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0} ;
    //r1 = {{0}, {1}};
//    
//    char temp[] = "0000000000001010" ;
//    
//    strcpy(r1,"110011000000100") ;
//    
//    printf ("%s", r1) ;
    
//    for (i= 0; i < sizeof(temp); i++) {
//        r1[i] = temp[i];
//        printf ("%c",r1[i]);
//    }
//    
//    printf ("\n");
//    
//    char temp[] = "0000000000001010" ;
//    
//    for (i= 0; i < sizeof(temp); i++) {
//        r1[i] = temp[i];
//        printf ("%c",r1[i]);
//    }
//    
//    printf ("\n");
//    
//    
//    printf("r1[0] = %c", r1[0]) ;
//  binary = convertBinary(10);

    
    return 0 ;
}
