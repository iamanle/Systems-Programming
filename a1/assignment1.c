//
//  assignemnt1.c
//  Assignment1
//
//  Name: An Le
//  Username: masc0749
//  Notes: hexdump program takes a binary/text file as input and show the hex or binary of
//  every byte in the file. The program does not handle error if the input other file types.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 20

char fileInName[MAX_INPUT];
char fileOutName[MAX_INPUT];
FILE *filein;

/*******************************Convert Byte To Binary***************************/
//Since only 1 & 1 = 1 and others and operations result 0, we can easily tell which position is 1 by using AND operation and shift right.
//Create a binaryString to store the binary number. Start with z = 1000 0000. Apply AND operation to given x and z, if the return value is euqal to z, then stringcat 1 to binaryString. Otherwise stringcat 0 to binaryString. Shift 1 byte of z to the right after that. Repeat these steps until 1 is at the end of string z, after the shift right operation, z will become a negative number and end the for loop.
const char *byteToBinary(int x){
    static char binaryString[9];
    binaryString[0] = '\0';
    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(binaryString, ((x & z) == z) ? "1" : "0");
    }
    return binaryString;
}

/*******************************Print Every Byte In Hex***************************/
int printHex(){
    int addr, count, count2;
    char buffer[MAX_INPUT];
    char *bufferPointer;
    
    //Open input file
    filein = fopen(fileInName, "rb");
    if(filein == NULL) {
        printf("File does not have data. \n");
        return 1;
    }
    
    //Read an array of 16 elements, each with size byte from filein and store to buffer.
    //The "count" variable store the number of elements successfully read in returned.
    while((count = fread(buffer, sizeof(unsigned char), 16, filein)) > 0){
        
        //Print address
        printf("%08lx:  ",addr);
        addr = addr + 16;
        
        //Print bytes in hex
        //use count2 to keep track of how many bytes have been printed out. If there is no more byte to print, then print space to replace.
        bufferPointer = buffer;
        count2 = 0;
        int i;
        for(i = 0; i < 8; i++) {
            if(count2 <= count) {
                printf("%02x%02x ", *bufferPointer++, *bufferPointer++);
            }
            else {
                printf("     ");
            }
            //Since we print 2 bytes together:
            count2 = count2 + 2;
            printf(" ");
        }
        
        //Print 16 human-readable chars
        printf("  ");
        count2 = 0;
        int j;
        for(j = 0; j < 16; j++) {
            count2 = count2 + 1;
            if(count2 <= count) {
                //Replace unreadable chars with "."
                if((buffer[j] < 33)||(buffer[j] > 126)){
                    printf("%c", '.');
                }
                else{
                    printf("%c", buffer[j]);
                }
            }
        }
        printf("\n");
    }
    
    fclose(filein);
    printf("        End of file.\n");
    return 0;
}

/*******************************Print Every Byte In Binary***************************/
int printBin() {
    int addr, count, count2;
    char buffer[MAX_INPUT];
    char *bufferPointer;
    
    filein = fopen(fileInName, "rb");
    if(filein == NULL) {
        printf("File does not have data. \n");
        return 1;
    }
    
    //Read an array of 6 bytes filein and store to buffer.
    while((count = fread(buffer, sizeof(unsigned char), 6, filein)) > 0){
        
        //Print address
        printf("%08lx:  ",addr);
        addr = addr + 6;
        
        //Print 6 bytes in bin
        bufferPointer = buffer;
        count2 = 0;
        int i;
        for(i = 0; i < 6; i++) {
            if(count2 <= count) {
                printf("%s", byteToBinary(*bufferPointer++));
            }
            else {
                printf("        ");
            }
            count2 = count2 + 1;
            printf(" ");
        }
        
        //Print 6 human-readable chars
        printf("  ");
        count2 = 0;
        int j;
        for(j = 0; j < 6; j++) {
            count2 = count2 + 1;
            if(count2 <= count) {
                if((buffer[j] < 33)||(buffer[j] > 126)){
                    printf("%c", '.');
                }
                else{
                    printf("%c", buffer[j]);
                }
            }
        }
        printf("\n");
    }
    
    fclose(filein);
    printf("        End of file.\n");
    return 0;
}

/*******************************Take User Input***************************/
int takeInput() {
    char type[MAX_INPUT];
    char input[MAX_INPUT];
    
    printf("An Le - masc0749\n");
    printf("Hexdump program \n");
    printf("Enter your input file name: \n");
    
    //Take in file name and validate
    if (fgets(input, MAX_INPUT, stdin) != NULL) {
        sscanf(input, "%s", fileInName);
    }
    else {
        printf("Please input file name.\n");
        return 1;
    }
    
    printf("Do you like to print in Hex or Bin? (type hex or bin)\n ");
    if (fgets(input, MAX_INPUT, stdin) != NULL) {
        sscanf(input, "%s", type);
        if (strcmp(type, "hex") == 0) {
            printHex();
        }
        if (strcmp(type, "bin") == 0) {
            printBin();
        }
    }
    else {
        printf("No answer. End Program");
        return 1;
    }
    return 0;
}

/*******************************Main***************************/
int main (int argc, const char * argv[]) {
    takeInput();
}

