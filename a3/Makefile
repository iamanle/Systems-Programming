###########################################################
# Programmers: An Le
# Username: masc0749
# CS530, Fall 2013
# Instructor: Guy Leonard
# Assignment 3
# Makefile 
###########################################################

CC = CC
CFLAGS = -g
LDFLAGS = -lm

parser : main.o Parser.o Validate.o
	${CC} ${CFLAGS} main.o Parser.o Validate.o ${LDFLAGS} -o parser

Parser.o : Parser.cpp
	${CC} ${CFLAGS} -c Parser.cpp

Validate.o : Validate.cpp 
	${CC} ${CFLAGS} -c Validate.cpp
	
main.o : main.cpp
	${CC} ${CFLAGS} -c main.cpp

clean: 
	rm -f parser *.o