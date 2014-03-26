# Make recognizes makefile and Makefile, otherwise need to -f and specify
#	make -f mymakefile.txt

COMPILER = g++			# compiler specific to file extension, g++ only invoked on .cpp
PROGNAME = bombermanc
CFLAGS = -g -Wall -std=c++11	# gnu99 in for declarations, c++11 for non static data member initialiazer
#LIBS = -lmyLib 
LIBS =  
SRC = client.cpp
OBJ = client.o 

# Explicit rules: Which files depend on the compile of other files
#myProgram : main.c
#g++ -o myProgram main.c	# command here, tab char before each command

# Explicit rules: Which files depend on the compile of other files
$(PROGNAME) : $(OBJ)
	$(COMPILER) $(CFLAGS) -o $(PROGNAME) $(OBJ) $(LIBS) 


# Implicit rules: like explicit, but no commands, suffex tells what commandtodo
client.o: client.cpp

# Note;
# -v for verbose; print all steps gcc/g++ takes to do compile
# -Werror; warnings are errors
# add external flags from a file using @;
#	gcc main.c @optionFile

#ifdef MY_MACRO
  #printf("\n Macro defined \n");
#endif

#then; use -D, to def macro; called compile time macros
#gcc -Wall -DMY_MACRO main.c -o main