/*
 * Programmers: An Le & Ray Luu
 * Username: masc0749 & masc0720
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 2
 * Due Date: November 13, 2013
 * Converter.cpp
 */

#include "Converter.h"

// Convert Hex in string to Int (Decimal)
int Converter::stringHexToInt(string hex){
    int num = 0;
    int pow16 = 1;

    string alpha = "0123456789ABCDEF";
    for(int i = hex.length() - 1; i >= 0; --i)
    {
        num += alpha.find(toupper(hex[i])) * pow16;
        pow16 *= 16;
    }
    return num;
}

// Take in 1 int and return Binary number as a string.
string Converter::hexToStringBinary(unsigned long hex) {
    if(hex == 0)
        return "0000";
    else if(hex == 1)
        return "0001";
    else if(hex == 2)
        return "0010";
    else if(hex == 3)
        return "0011";
    else if(hex == 4)
        return "0100";
    else if(hex == 5)
        return "0101";
    else if(hex == 6)
        return "0110";
    else if(hex == 7)
        return "0111";
    else if(hex == 8)
        return "1000";
    else if(hex == 9)
        return "1001";
    else if(hex == 0x0A)
        return "1010";
    else if(hex == 0x0B)
        return "1011";
    else if(hex == 0x0C)
        return "1100";
    else if(hex == 0x0D)
        return "1101";
    else if(hex == 0x0E)
        return "1110";
    else if (hex == 0x0F)
        return "1111";
    printf("Opcode Error!\n");
    exit(EXIT_FAILURE);
}

//Take in a 4 binary number as a string and return an integer (decimal)
string Converter::stringBinToHex(string s){
    if(s.compare("0000")==0)
        return "0";
    else if(s.compare("0001")==0)
        return "1";
    else if(s.compare("0010")==0)
        return "2";
    else if(s.compare("0011")==0)
        return "3";
    else if(s.compare("0100")==0)
        return "4";
    else if(s.compare("0101")==0)
        return "5";
    else if(s.compare("0110")==0)
        return "6";
    else if(s.compare("0111")==0)
        return "7";
    else if(s.compare("1000")==0)
        return "8";
    else if(s.compare("1001")==0)
        return "9";
    else if(s.compare("1010")==0)
        return "A";
    else if(s.compare("1011")==0)
        return "B";
    else if(s.compare("1100")==0)
        return "C";
    else if(s.compare("1101")==0)
        return "D";
    else if(s.compare("1110")==0)
        return "E";
    else if(s.compare("1111")==0)
        return "F";
    printf("Invalided Input!\n");
    exit(EXIT_FAILURE);
}

//Take in an integer (decimal) and return that int number as a string
string Converter::integerToString(int number){
    string convertToString;

    stringstream ss;  // stream used for the conversion
    ss << number;      // insert the textual representation of 'Number' in the
    convertToString = ss.str(); //characters in the stream

    return convertToString;
}
