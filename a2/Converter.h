/*
 * Programmers: An Le & Ray Luu
 * Username: masc0749 & masc0720
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 2
 * Due Date: November 13, 2013
 * Converter.h
 */

#ifndef __Assignment2__Converter__
#define __Assignment2__Converter__

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;

class Converter{
public:
    static int stringHexToInt(string s);
    static string hexToStringBinary(unsigned long hex);
    static string stringBinToHex(string s);
    static string integerToString(int number);
};

#endif /* defined(__Assignment2__Converter__) */
