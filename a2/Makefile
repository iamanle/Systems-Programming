###########################################################
# Programmers: An Le & Ray Luu
# Username: masc0749 & masc0720
# CS530, Fall 2013
# Instructor: Guy Leonard
# Assignment 2
# Due Date: November 13, 2013
# Makefile 
###########################################################

CC = CC
CFLAGS = -g
LDFLAGS = -lm

dasm : main.o Opcode.o Converter.o SicDisassembler.o
	${CC} ${CFLAGS} Opcode.o Converter.o SicDisassembler.o main.o ${LDFLAGS} -o dasm

Opcode.o : Opcode.cpp
	${CC} ${CFLAGS} -c Opcode.cpp

Converter.o : Converter.cpp 
	${CC} ${CFLAGS} -c Converter.cpp

SicDisassembler.o : SicDisassembler.cpp 
	${CC} ${CFLAGS} -c SicDisassembler.cpp
	
main.o : main.cpp
	${CC} ${CFLAGS} -c main.cpp

clean: 
	rm -f dasm *.o
