#------------------------------------------------------------------------------
# Makefile for nqueens.c with macros
#------------------------------------------------------------------------------

PROGRAM_NAME = nqueens
EXEBIN       = $(PROGRAM_NAME)
SOURCE       = $(PROGRAM_NAME).c
OBJECT       = $(PROGRAM_NAME).o
COMPILE      = gcc -c -Wall
LINK         = gcc -o

$(EXEBIN) : $(OBJECT)
	$(LINK) $(EXEBIN) $(OBJECT)

$(OBJECT) : $(SOURCE)
	$(COMPILE) $(SOURCE)

clean :
	rm $(EXEBIN) $(OBJECT)

memcheck :
	valgrind --leak-check=full $(EXEBIN) -v 8
