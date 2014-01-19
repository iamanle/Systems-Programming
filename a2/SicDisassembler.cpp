/*
 * Programmers: An Le & Ray Luu
 * Username: masc0749 & masc0720
 * CS570, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 2
 * Due Date: November 13, 2013
 * SicDisassembler.cpp
 */

#include "SicDisassembler.h"

void Disassemble::readFile(){
    char *input = new char[MAX_INPUT]();
    char *objName = new char[MAX_INPUT]();
    char *symtabName = new char[MAX_INPUT]();
    fileName =  new char[MAX_INPUT]();
    string line;
    
    printf("An Le - Ray Luu - masc0720\n");
    printf("SIC Dis-assembler \n");
    printf("Enter your object file name: \n");
    
    // Read file name
    if (fgets(input, MAX_INPUT, stdin) != NULL)
        sscanf(input, "%s", fileName);
    else
        printf("Please input file name.\n");
    
    // Assign extension to file name
    strcat(symtabName, fileName);
    strcat(symtabName, ".sym"); // read in file.sym
    strcat(objName, fileName);
    strcat(objName, ".obj");    // read in file.obj
    
    // Open obj file and assign each line to vector objContent.
    ifstream objfile(objName);
    if (objfile.is_open()) {
        while (objfile.good()) {
            getline(objfile, line);
            objContent.push_back(line);
        }
        objfile.close();
        
        // Open symtab file and assign each line to vector symContent.
        ifstream symfile(symtabName);
        if (symfile.is_open()) {
            while (symfile.good()) {
                getline(symfile, line);     // read each line
                symContent.push_back(line); // store each line in a vector
            }
            symfile.close();
        } else printf("Unable to open Symtab file \n");
        
        // After reading file successfully. Run program:
        printf("Dis-assembling %s ...\n\n", objName);
        
        Disassemble::run();
    }
    else printf("Unable to open Object file.\n");
}

void Disassemble::run(){
    /*-------------Split symbol and address then assign them to map----------------*/
    if (symContent.size() > 0) {
        for (int i = 0; i < symContent.size()-1; i++) {
            if (symContent[i].length() > 1
                && symContent[i][19] != 'r'
                && symContent[i][0] != '-')
            {
                string symbol = symContent[i].substr(0,6); // take the symbol names
                
                // take the address of the symbol table and convert it to in
                int symAddr = Converter::stringHexToInt(symContent[i].substr(16,4));
                
                if (symbol[0] == '=')               // encounter literal
                    litElement[symAddr] = symbol;   // store literals in a difference vector
                else {
                    symElement[symAddr] = symbol;
                    directive[symAddr] = symbol;
                }
            }
        } // end For loop
    }
    
    printf("Symbol table: \n");
    for (it = symElement.begin(); it != symElement.end(); ++it)
        cout << it->first << "  " << it->second << "\n";
    
    printf("\nLiteral table: \n");
    for (it = litElement.begin(); it != litElement.end(); ++it)
        cout << it->first << "  " << it->second << "\n";
    
    /*-------------------------Dis-assemble---------------------------------*/
    printf("\nDis-assembling...\n\n");
    
    char *outName = new char[MAX_INPUT]();
    
    // Write to File.sic:
    strcat(outName, fileName);
    strcat(outName, ".sic");
    
    ofstream outfile(outName);
    FILE *outFile;
    outFile = fopen(outName, "wb");
    
    // Check for H record:
    int lastAddr = 0;
    if (objContent[0][0] == 'H') {
        string pName = objContent[0].substr(1, 6); // name of the object file
        int hAddr = Converter::stringHexToInt(objContent[0].substr(7, 6)); // address
        int progLength = Converter::stringHexToInt(objContent[0].substr(13, 6)); // length of the object file
        lastAddr = hAddr + progLength;
        fprintf(outFile,"%-9s %-11s %04x \n", pName.c_str(), "START", hAddr); // write to file.sic
    }
    else {
        printf("Can't find Head record. \n");
        exit(EXIT_FAILURE);
    }
    
    // If there is H record, then dis-assemble other records.
    // Text Record:
    for (int i = 1; i < objContent.size(); i++) {
        if (objContent[i][0] == 'T') {
            //--------LOOP INSTRUCTIONS FROM HERE:---------------
            int tAddr = Converter::stringHexToInt(objContent[i].substr(1,6));   // text record address
            int tLength = Converter::stringHexToInt(objContent[i].substr(7,2)); // text record length
            int lastAddr = tAddr + tLength;
            int start = 9;
            int jump = 0;
            int baseAddr = 0;
            
            while (tAddr < lastAddr) {
                
                /*Get data at that address:
                 data[0] = mnemonic;
                 data[1] = skipDigits;
                 data[2] = originalSym;
                 data[3] = symbol for option field;
                 data[4] = format
                 */
                
                vector<string> data = Disassemble::printFormat(i,start,tAddr, baseAddr);
                
                string mnemonic = data[0];
                string skipDigits = data[1];
                jump = Converter::stringHexToInt(skipDigits);
                string option = data[3];
                int format = Converter::stringHexToInt(data[4]);
                
                // Check if address in symtab and littab
                string hasSym = ""; // initialize string to null
                if (symElement.find(tAddr) != symElement.end()) {
                    hasSym = symElement.find(tAddr)->second; //find symbol name in symbol table with the given address
                }
                
                string hasLit = "";
                if (litElement.find(tAddr) != litElement.end()) {
                    hasLit = litElement.find(tAddr)->second; //find literal in literal table with the given address
                }
                
                // 1) ****If tAddr's in symtab then print hasSym in Label field.
                if (hasSym.length() > 0) {
                    // Print: Addr Symbol Mnemonic Option.
                    if(format == 4)
                        fprintf(outFile,"%-9s %-11s %-5s %s %s \n", hasSym.c_str(), "","+", mnemonic.c_str(), option.c_str());
                    else
                        fprintf(outFile, "%-9s %-11s %s \n", hasSym.c_str(), mnemonic.c_str(), option.c_str());
                    
                    // Delete found symbol from symtab.
                    directive.erase(tAddr);
                    
                    // Jump to the next instruction.
                    start = start + jump;
                    
                    // Increase tAddr for the next instruction.
                    tAddr = tAddr + format;
                }
                
                // 2) ****If tAddr's in littab and the first element in littab, then print hasLit in option field.*****
                else if ((hasLit.length() > 0) && (litElement.begin()->second == hasLit)) {
                    //***Need to count how many literal before this and add to start and address
                    fprintf(outFile, "%-9s %-11s \n", "", "LTORG");
                    jump = 2;
                    
                    // Jump to the next instruction.
                    start = start + jump;
                    
                    // Increase tAddr for the next instruction.
                    tAddr = tAddr + 1;
                }
                
                // 3) ****If tAddr is not in both tables:
                else{
                    if(format == 4)
                        fprintf(outFile, "%-8s %s%-11s %s \n", "","+", mnemonic.c_str(), option.c_str());
                    else
                        fprintf(outFile, "%-9s %-11s %s \n", "", mnemonic.c_str(), option.c_str());
                    
                    // Print BASE after LDB and store BASE address
                    if(mnemonic == "LDB"){
                        fprintf(outFile, "%-9s %-11s %s \n", "", "BASE", data[2].c_str());
                        // Store Base address
                        if (format == 4) {
                            string sBaseAddr = objContent[i].substr(start + 4, 4);
                            baseAddr = Converter::stringHexToInt(sBaseAddr);
                        }
                        if (format == 3) {
                            string sDisp = objContent[i].substr(start + 3, 3);
                            int disp = Converter::stringHexToInt(sDisp);
                            baseAddr = disp + tAddr;
                        }
                    }
                    
                    // Jump to the next instruction.
                    start = start + jump;
                    
                    // Increase tAddr for the next instruction.
                    tAddr = tAddr + format;
                }
            } // End while loop
        } // End text record
    } // End for loop
    
    // Variable Declaration:
    unsigned long size = directive.size();
    for (int i = 0; i < size; i++) {
        int address = directive.begin()-> first;
        string label = directive.begin()-> second;
        directive.erase(address);
        
        int nextAddr = 0;
        int storage = 0;
        
        if (directive.size() == 0)
            storage = lastAddr - address;
        else {
            nextAddr = directive.begin()->first;
            storage = nextAddr - address;
        }
        
        if (storage % 3 == 0) { // check for RESW or RESB
            storage = storage / 3;
            fprintf(outFile, "%-9s %-11s %d \n", label.c_str(), "RESW", storage);
        } else
            fprintf(outFile, "%-9s %-11s %d \n", label.c_str(), "RESB", storage);
    }
    
    // End Record:
    for (int i = 1; i < objContent.size(); i++) {
        if (objContent[i][0] == 'E') {
            int loadAddr = Converter::stringHexToInt(objContent[i].substr(1, 6));
            string symbol = symElement.find(loadAddr)->second;
            fprintf(outFile, "%-9s %-11s %s \n", "", "END", symbol.c_str());
        }
    }
    outfile.close(); // close file.sic
}

/*-------------------------Check Format And Return Its Data------------------------------*/
vector<string> Disassemble::printFormat(int lineNumber, int start, int tAddr, int baseAddr){
    // start is the first position in the instruction.
    // tAddr is current address (PC)
    
    vector<string> data(5);
    /* Assign:
     data[0] = mnemonic;
     data[1] = skipDigits;
     data[2] = originalSym;
     data[3] = symbol for option field;
     data[4] = format*/
    
    Opcode *check = new Opcode();
    
    // Take the first 2 digits to put to getopcode
    string first2 = objContent[lineNumber].substr(start,2);
    
    // Get real opcode
    string opcode = check->get_opcode(first2);
    
    // Validate opcode if it's in optab then return its index in optab. If not, return -1
    int optabIndex = check->validateOpcode(opcode);
    
    // Check Format and store its data
    if (optabIndex != -1) {
        string format = check->getFormat(optabIndex);
        // Format "3/4"
        if (format.length() > 1) {
            // Get NIXBPE
            string stringNixbpe1 = objContent[lineNumber].substr(start+1,1);
            int intNixbpe1 = Converter::stringHexToInt(stringNixbpe1);
            string binNixbpe1 = Converter::hexToStringBinary(intNixbpe1);
            
            string stringNixbpe2 = objContent[lineNumber].substr(start+2,1);
            int intNixbpe2 = Converter::stringHexToInt(stringNixbpe2);
            string binNixbpe2 = Converter::hexToStringBinary(intNixbpe2);
            
            string nixbpe = binNixbpe1.substr(2,2);
            nixbpe = strcat((char *)nixbpe.c_str(), (char *)binNixbpe2.c_str());
            
            // Store Format 4 data
            if (nixbpe[5] == '1') {
                data[0] = Opcode::getInstruction(optabIndex);
                data[1] = "8";
                
                string sDirectAddr = objContent[lineNumber].substr(start+4, 4);
                int directAddr = Converter::stringHexToInt(sDirectAddr);
                string symbol = symElement.find(directAddr)->second;
                
                if(nixbpe[0] == '1' && nixbpe[1] == '1' && nixbpe[2] == '1')
                    symbol = symbol + ",X";
                else if(nixbpe[0] == '1' && nixbpe[1] == '0')
                    symbol = "@" + symbol;
                
                // Check if it's number
                else if (nixbpe[0] == '0' && nixbpe[1] == '1' ) {
                    // Check if the address is in Symbol Table:
                    if (symElement.find(directAddr) != symElement.end())
                        symbol = symElement.find(directAddr)->second;
                    else
                        symbol = Converter::integerToString(directAddr);
                    
                    symbol = "#" + symbol;
                }
                string originalSym = symElement.find(directAddr)->second;
                data[2] = originalSym;
                data[3] = symbol;
                data[4] = "4";
            } else {
                
                // Store Format 3 data
                data[0] = Opcode::getInstruction(optabIndex);
                data[1] = "6";
                
                string sDisp = objContent[lineNumber].substr(start+3, 3);
                if (   sDisp[0] == '8'
                    || sDisp[0] == '9'
                    || sDisp[0] == 'A'
                    || sDisp[0] == 'B'
                    || sDisp[0] == 'C'
                    || sDisp[0] == 'D'
                    || sDisp[0] == 'E'
                    || sDisp[0] == 'F') {
                    sDisp = "0x" + sDisp;
                }
                int disp = Converter::stringHexToInt(sDisp);
                string symbol;
                string originalSym;
                int targetAddr = 0;
                
                // >>> PC relative
                if ((nixbpe[0] == '1' && nixbpe[1] == '1' && nixbpe[2] == '0' && nixbpe[3] == '0' && nixbpe[4] == '0')
                    || (nixbpe[0] == '1' && nixbpe[1] == '1' && nixbpe[2] == '0' && nixbpe[3] == '0' && nixbpe[4] == '1')) {
                    
                    targetAddr = disp + tAddr + 3;
                    
                    // Check if targetAddr in symtab or littab
                    if (symElement.find(targetAddr) != symElement.end()) {
                        symbol = symElement.find(targetAddr)->second;
                        originalSym = symbol;
                    }
                    
                    if (litElement.find(targetAddr) != litElement.end()) {
                        symbol = litElement.find(targetAddr)->second;
                        originalSym = symbol;
                    }
                    
                    if (data[0].compare("RSUB") == 0) {
                        symbol = "";
                        originalSym = "";
                    }
                }
                
                // >>> Base relative
                if (nixbpe[0] == '1' && nixbpe[1] == '1' && nixbpe[2] == '0' && nixbpe[3] == '1' && nixbpe[4] == '0'){
                    targetAddr = disp + baseAddr;
                    symbol = symElement.find(targetAddr)->second;
                    originalSym = symbol;
                }
                
                // >>> Index addressing
                if ((nixbpe[0] == '1' && nixbpe[1] == '1' && nixbpe[2] == '1' && nixbpe[3] == '0' && nixbpe[4] == '0')
                    || (nixbpe[0] == '1' && nixbpe[1] == '1' && nixbpe[2] == '1' && nixbpe[3] == '0' && nixbpe[4] == '1'))
                {
                    if ((-2048 <= disp) && (disp <= 2047)) { // PC relative mode
                        targetAddr = disp + tAddr + 3;
                        symbol = symElement.find(targetAddr)->second;
                        originalSym = symbol;
                        symbol = symbol + ",X";
                    }
                    else { // base relative mode
                        targetAddr = disp + baseAddr;
                        symbol = symElement.find(targetAddr)->second;
                        originalSym = symbol;
                        symbol = symbol + ",X";
                    }
                }
                // - Index addressing using base relative
                if ((nixbpe[0] == '1' && nixbpe[1] == '1' && nixbpe[2] == '1' && nixbpe[3] == '1' && nixbpe[4] == '0')) {
                    targetAddr = disp + baseAddr;
                    symbol = symElement.find(targetAddr)->second;
                    originalSym = symbol;
                    symbol = symbol + ",X";
                }
                
                // >>> Indirect addressing
                if ((nixbpe[0] == '1' && nixbpe[1] == '0' && nixbpe[2] == '0' && nixbpe[3] == '0' && nixbpe[4] == '0')
                    || (nixbpe[0] == '1' && nixbpe[1] == '0' && nixbpe[2] == '0' && nixbpe[3] == '0' && nixbpe[4] == '1')) {
                    if ((-2048 <= disp) && (disp <= 2047)) { //PC relative mode
                        targetAddr = disp + tAddr + 3;
                        symbol = symElement.find(targetAddr)->second;
                        originalSym = symbol;
                        symbol = "@" + symbol;
                    }
                    else { // base relative mode
                        targetAddr = disp + baseAddr;
                        symbol = symElement.find(targetAddr)->second;
                        originalSym = symbol;
                        symbol = "@" + symbol;
                    }
                }
                // - Index addressing using base relative
                if ((nixbpe[0] == '1' && nixbpe[1] == '0' && nixbpe[2] == '0' && nixbpe[3] == '1' && nixbpe[4] == '0')) {
                    targetAddr = disp + baseAddr;
                    symbol = symElement.find(targetAddr)->second;
                    originalSym = symbol;
                    symbol = "@" + symbol;
                }
                
                // >>> Immediate addressing
                if ((nixbpe[0] == '0' && nixbpe[1] == '1' && nixbpe[2] == '0' && nixbpe[3] == '0' && nixbpe[4] == '0')
                    || (nixbpe[0] == '0' && nixbpe[1] == '1' && nixbpe[2] == '0' && nixbpe[3] == '0' && nixbpe[4] == '1')) {
                    if ((-2048 <= disp) && (disp <= 2047)) { // PC relative mode
                        targetAddr = disp + tAddr + 3;
                        if (symElement.find(targetAddr) != symElement.end()) {
                            symbol = symElement.find(targetAddr)->second;
                            originalSym = symbol;
                        } else {
                            symbol = Converter::integerToString(disp);
                            originalSym = symbol;
                        }
                        symbol = "#" + symbol;
                    }
                    else { // base relative mode
                        targetAddr = disp + baseAddr;
                        if (symElement.find(targetAddr) != symElement.end()) {
                            symbol = symElement.find(targetAddr)->second;
                            originalSym = symbol;
                        } else {
                            symbol = Converter::integerToString(disp);
                            originalSym = symbol;
                        }
                        symbol = "#" + symbol;
                    }
                }
                // - Index addressing using base relative
                if ((nixbpe[0] == '0' && nixbpe[1] == '1' && nixbpe[2] == '0' && nixbpe[3] == '1' && nixbpe[4] == '0')) {
                    targetAddr = disp + baseAddr;
                    if (symElement.find(targetAddr) != symElement.end()) {
                        symbol = symElement.find(targetAddr)->second;
                        originalSym = symbol;
                    } else {
                        symbol = Converter::integerToString(disp);
                        originalSym = symbol;
                    }
                    symbol = "#" + symbol;
                }
                data[2] = originalSym;
                data[3] = symbol;
                data[4] = "3";
            }
        }
        else {
            // Store Format 1 data
            if (format[0] == '1') {
                data[0] = Opcode::getInstruction(optabIndex);
                data[1] = "2";
                data[4] = "1";
                
                // Store Format 2 data
            } else if (format[0] == '2'){
                data[0] = Opcode::getInstruction(optabIndex);
                data[1] = "4";
                data[2] = "2"; // 2 registers
                data[4] = "2";
            }
        }
    }
    return data;
}
