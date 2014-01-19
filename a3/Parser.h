/*
 * Programmers: An Le 
 * Username: masc0749 
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 3
 * Parser.h
 */

#ifndef __Assignment3_530__Parser__
#define __Assignment3_530__Parser__

#include <iostream>
#include <fstream>
#include "Validate.h"

class Parser{
public:
    void readFile();
    void run();
    
private:
    vector<string> chooseVal(vector<string> token);
    vector<string> textContent;
};

#endif /* defined(__Assignment3_530__Parser__) */
