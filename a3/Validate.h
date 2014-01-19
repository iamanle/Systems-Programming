/*
 * Programmers: An Le
 * Username: masc0749
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 3
 * Validate.h
 */

#ifndef __Assignment3_530__Validate__
#define __Assignment3_530__Validate__

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Validate {
public:
    bool validateID (string token);
    vector<string> validateExp (vector<string> token);
    vector<string> validateAssg (vector<string> token);
    
private:
    static bool validateCharacter (char character);
    static bool validateDigit (char digit);
    static bool validateOperators (char operators);
};

#endif /* defined(__Assignment3_530__Validate__) */
