/*
 * Programmers: An Le 
 * Username: masc0749 
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 3
 * Parser.cpp
 */

#include "Parser.h"

// -------------------readFile---------------------
void Parser::readFile() {
    char *input = new char[MAX_INPUT]();
    char *inputFile = new char[MAX_INPUT]();
    char *fileName =  new char[MAX_INPUT]();
    string line;
    
    printf("An Le - masc0749\n");
    printf("Assingmnet 3: Parser Program\n");
    printf("Enter a text file name: \n");
    
    // Read text file name.
    if (fgets(input, MAX_INPUT, stdin) != NULL) {
        sscanf(input, "%s", fileName);
    }
    else {
        printf("Input file name.\n");
    }
    
    strcat(inputFile, fileName);
    strcat(inputFile, ".txt");
    
    
    // Open text file and assign each line to vector textContent.
    ifstream textFile(inputFile);
    if (textFile.is_open()) {
        while (textFile.good()) {
            getline(textFile,line);
            textContent.push_back(line);
        }
        textFile.close();
        // After reading file successfully. Run program:
        printf("Parsing %s ...\n\n", inputFile);
        Parser::run();
    } else printf("Unable to open text file.\n");
}

// -------------------Run---------------------
void Parser::run() {
    
    // Open output file
    char *outFileName = new char[MAX_INPUT]();
    strcat(outFileName, "out.txt");
    ofstream outfile(outFileName);
    FILE *outFile = fopen(outFileName, "wb");
    
    printf("Read %lu lines \n", textContent.size());
    
    
    bool pass = true;
    fprintf(outFile, "Line                          Input                                   Validation \n");
    for(int i = 0; i < textContent.size(); i++) {
        // If line is not empty then proceed
        if(!textContent[i].empty()) {
            // Tokenize to string named token
            vector<string> token;
            istringstream f(textContent[i]);
            string s;
            while (getline(f, s, ' ')) {
                token.push_back(s);
            }
            
            // Write to out.txt
            vector<string> temp = chooseVal(token);
            fprintf(outFile, "%3d: %-60s  %-20s %-20s \n", i, textContent[i].c_str(), temp[0].c_str(), temp[1].c_str());
            
            // If there is an invalid instruction then set pass = false
            if (temp[0].length() > 16) {
                pass = false;
            }
        }
        else{
	        fprintf(outFile, "%3d: \n", i);
        }
    }
    fprintf(outFile,"\n => File Validation: %s", pass ? "Pass":"Fail");
    printf("Done parsing! Written output to out.txt successfully! \n");
    outfile.close();
}

// -------------------chooseVal---------------------
// Choose an approriate validation for each instruction
vector<string> Parser::chooseVal(vector<string> token) {
    vector<string> result(2), temp(2);
    stringstream ss;
    Validate *validate = new Validate;
    for (int i = 0; i < token.size(); i++) {
        // If the instruction has "=" then call assignemnt validation
        if (token[i] == "=") {
            temp = validate->validateAssg(token);
            if (temp[0] == "1"){
                result[0] = "Valid Assignment.";
                result[1] = " ";
                return result;
            }
            result[0] = "Invalid Assignment.";
            result[1] = temp[1];
            return result;
        }
    }
    temp = validate->validateExp(token);
    if (temp[0] == "1") {
        result[0] = "Valid Expression.";
        result[1] = " ";
        return result;
    }
    result[0] = "Invalid Expression.";
    result[1] = temp[1];
    return result;
}
