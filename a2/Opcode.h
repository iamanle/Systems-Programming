/*
 * Programmers: An Le & Ray Luu
 * Username: masc0749 & masc0720
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 2
 * Due Date: November 13, 2013
 * Opcode.h
 */

#ifndef __Assignment2__get_opcode__
#define __Assignment2__get_opcode__

#include "Converter.h"

class Opcode{
public:
    static string get_opcode(string opcode);
    static int validateOpcode(string opcode);
    static string getInstruction(int optabIndex);
    static string getFormat(int optabIndex);
    static string getRegister(string register_code);
};

#endif /* defined(__Assignment2__get_opcode__) */
