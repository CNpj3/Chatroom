CC = gcc
CFLAGS = -std=c99

all: basic-with-structure

variables.o: variables.h
operator.o: operator.h
statement.o: statement.h variables.h operator.h
basic-with-structure.o: statement.h variables.h operator.h

basic-with-structure: variables.o statement.o operator.o basic-with-structure.o