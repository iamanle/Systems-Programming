/*
 * Programmers: An Le 
 * Username: masc0749 
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 3
 * README.txt
 */
 							PARSER WRITTEN IN C++ 
1)File manifest: 
Validate.cpp, Validate.h, Parser.cpp, Parser.h, main.cpp, Makefile, README.txt
test.txt is included for testing purpose.

2)Compile Instructions: 
- Type "make clean" on the command line to delete .o files (optional)
- Type "make" on the command line. It will automatically compile the source code file using CC compiler and create a "parser" file. 
_ Type "parser" on the console, it will run the program. 
_ The program will display a message to prompt the user for input “Enter a text file name: ”. Type in your text file name without extension .txt. 
For example: to validate "test.txt" file, type test and enter.
_ The program will write the pass/fail result to file "out.txt" in the same directory.

3)Description:
- The program has main.cpp which calls the readFile() method from Parser.h to init the program with an input text file. If the input file is found, then parser program will validate it.

*** Parser.h contains 2 methods
void readFile();
void run();
    
*** Validate.h contains 6 methods:
public:
    static bool validateID (string token);
    bool validateExp (vector<string> token);
    bool validateAssg (vector<string> token); 
private:
    static bool validateCharacter (char character);
    static bool validateDigit (char digit);
    static bool validateOperators (char operators);

- The name of each method clearly says what it does. 
- This parser program currently can validate assignment and expression without parenthesis.
- Structs are used to check if the input character is valid.
- The program will output the validation for each instruction whether it is a valid assignment/expression or not. At the end of the output file, it will indicate if the program pass or fail.

4)Lesson Learned:
Doing this project, I learnt how a parser works such as how it scans each instruction, how it tokenizes the string and how it validates the instruction with a specified grammar. 

5)Grammar (BNF):
<assign> 	::= id = <exp> ;
<exp>   	::= <id> <op> <id> {<op> <id>}
<id>    	::= <char>|<id><char>|<id><digit>
<char>      	::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z
<digit> 	::= 0|1|2|3|4|5|6|7|8|9
<op> 		::= +|-|*|/|%

6) Program inputs and program outputs:
- As mentioned in Description, the program will take in a text file name (filename.txt) and output "out.txt" in the same directory.
- The program is able to read text file with empty lines.
- The validation for each instruction will be shown next to it.
- The result will be displayed at the end of out.txt such as " => File Validation: PASS" if every instruction is valid, or  "=> File Validation: FAIL" if there is an invalid instruction.

EXTRA:  Next to the validation statement is the reason and which token caused error.

Sample Output:

Line                          Input                                   Validation 
  0: first = one1 + two2 - three3 / four4 ;                        Valid Assignment.                         
  1: third = ONE + twenty - three3 ;                               Valid Assignment.                         
  2: third = old * thirty2 / b567 ;                                Valid Assignment.                         
  3: first = one1 + two2 - three3 ;                                Valid Assignment.                         
  4: 
  5: one1 * i8766e98e + three                                      Valid Expression.                         
  6: h1 + h2 - h3 / h4 % h5 * h6                                   Valid Expression.                         
  7: wqwe213 - s1123 % SDAS                                        Valid Expression.                         
  8: 
  9: second = one1 * (two2 * three3) ;                             Invalid Assignment.  The token "three3)" is not a valid ID. 
 10: first = = one1 + two2 - three3 / four4 ;                      Invalid Assignment.  The token "=" is not a valid ID. 
 11: first = one1 + two2 - three3 / four4                          Invalid Assignment.  The last token "four4" is not a semi colon. 
 12: first = 1 + - two2 - three3 / four4 ;                         Invalid Assignment.  The token "1" is not a valid ID. 
 13: first = one1 + two2 ? three3 / four4 ;                        Invalid Assignment.  The token "?" is not a valid Operator. 
 14: second = 4 + ( one1 * two2 ) * ( three3 + four4 ;             Invalid Assignment.  The token "4" is not a valid ID. 
 15: third = one1 + 24 - three3 ;                                  Invalid Assignment.  The token "24" is not a valid ID. 
 16: sixty6 / min = fourth ;                                       Invalid Assignment.  The second token "/" is not an equal sign. 
 17: 
 18: one1 +- delta                                                 Invalid Expression.  The token "+-" is not a valid Operator. 
 19: one1 * i8766e98e + bignum + two2 / sth5 sth5                  Invalid Expression.  The token "sth5" is not a valid Operator. 
 20: += one1 + two2 +three3                                        Invalid Expression.  The token "+=" is not a valid ID. 
 21: two2three +- three2 / kind3                                   Invalid Expression.  The token "+-" is not a valid Operator. 
 22: h1 / h2 % h3 h4                                               Invalid Expression.  The token "h4" is not a valid Operator. 
 23: / % h1 + h2 + h3                                              Invalid Expression.  The token "/" is not a valid ID. 
 24: h2 h2 + h3 - h4                                               Invalid Expression.  The token "h2" is not a valid Operator. 
 25: 
 26: 

 => File Validation: Fail