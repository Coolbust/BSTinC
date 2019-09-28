#Sidney Robinson
#Makefile for BST.h and BST.c with macros

FLAGS = -std=c99 -Wall
SOURCES = BST.c BST.h  BSTClient.c
OBJECTS = BST.o BSTClient.o
EXEBIN = BST
#EXEBIN is set to BST,makefile with macros and a valgrind check
all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)
clean :
	rm -f $(EXEBIN) $(OBJECTS)
check:
	valgrind --leak-check=full $(EXEBIN)

