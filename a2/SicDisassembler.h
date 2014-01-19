/*
 * Programmers: An Le & Ray Luu
 * Username: masc0749 & masc0720
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 2
 * Due Date: November 13, 2013
 * SicDisassembler.h
 */

#ifndef __Assignment2__SicDisassembler__
#define __Assignment2__SicDisassembler__

#include "Opcode.h"

#include <fstream>
#include <vector>
#include <map>

class Disassemble{

public:
    void readFile();
    void run();

    char *fileName;

private:
    vector<string> printFormat(int lineNumber, int start, int tAddr, int baseAddr);
    vector<string> objContent;
    vector<string> symContent;
    map<int,string> litElement, symElement, directive;
    map<int,string>::iterator it;
};

#endif /* defined(__Assignment2__SicDisassembler__) */
