/*
 * Programmers: An Le 
 * Username: masc0749 
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 3
 * main.cpp
 */

#include <iostream>
#include "Parser.h"
#include "Validate.h"

int main(int argc, const char * argv[])
{
    Parser *test = new Parser;
    test -> readFile();
    return 0;
}

