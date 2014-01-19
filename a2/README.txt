/*
 * Programmers: An Le & Ray Luu
 * Username: masc0749 & masc0720
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 2
 * Due Date: November 13, 2013
 * README.txt
 */

Files in this assignment: Converter.cpp, Converter.h, Opcode.cpp, Opcode.h, 
SicDisassembler.cpp, SicDisassembler.h, main.cpp, Makefile, , README.txt

Compile Instruction: 
-  Type "make" on the command line. It will automatically compile the source code file using CC 
compiler and create a "dasm" file (which is an "a.out" file). By typing "dasm" on the console, 
it will run the program. After typing dasm to run the program, the program will display a message 
to prompt the user for input “Enter your object file name: ”. With object file (file.obj) and symbol 
file (file.sym) in the same directory, type the name of the object file and the program will start 
disassembling the object file. The program will also create the same file name with .sic extension 
(file.sic) to write out all of the outputs and place it in the same directory.

In the program
- In the program, main will call SicDisassembler.cpp, and SicDisassembler.cpp will do most of work. 
Therefore, it will call Converter.cpp and Opcode.cpp to help with the disassembling. 

   Converter.cpp will include the following four methods to do all of the conversions: 
* int Converter::stringHexToInt(string hex)
* string Converter::hexToStringBinary(unsigned long hex)
* string Converter::stringBinToHex(string s)
* string Converter::integerToString(int number){

Opcode.cpp will include the following five methods and 2 Struct tables to assist the 
SicDisassembler to get the opcode:
* string Opcode::getRegister(string register_code)
* string Opcode::get_opcode(string opcode)
* int Opcode::validateOpcode(string opcode)
* string Opcode::getInstruction(int optabIndex)
* string Opcode::getFormat(int optabIndex)
* struct op_code
* struct SIC_Reg

SicDisassembler.cpp will include the following two methods, three vectors (list of arrays)
and three maps (hashtables) and one map iterator:  
* void readFile()
* void run()
* vector<string> printFormat(int lineNumber, int start, int tAddr, int baseAddr)
* vector<string> objContent;
* vector<string> symContent;
* map<int,string> litElement, symElement, directive;
* map<int,string>::iterator it;

- Each method does exactly what they were named to be. For this program, our algorithm will 
cover all of the address mode scenarios that were listed in the SicAdressModes handout; including 
the addressing modes combination, whether it is simple address mode with index and extended flags 
on, or indirect addressing mode with extended flag on or with pc flag on, or immediate with extended
or pc or base flag on. Yet, it might or might not work for all of the cases because the object file 
that was given to us for this project only covered some of the many combination of addressing mode 
scenarios, but not all. Therefore, we cannot test our algorithm extensively to its full potential.

- In this project, we have learned what’s software engineering really about. The process is not really 
about the coding part, it is about coming up with the algorithm, break the problem into sub-problems, 
and analyze the methods needed each of those sub-problems. Once we got the analysis down, everything falls
through. The only thing with programming part is finding the bugs. There are numerous of ways of finding 
the bugs; one of it is testing each of the methods and each part of the algorithm to see which one is not
doing the work that it supposes to.
