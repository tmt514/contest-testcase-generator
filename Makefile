all: formatting

# specify library paths
LIB = ./lib
INCLUDES = ./includes
SRC = ./src

# g++ settings
CC = g++
CPPFLAGS = -std=c++11 -I$(INCLUDES) -I. -L$(LIB)
LM = -lTestGen

# lexical analyzer
LEX = flex
LFLAGS = 
# syntax analyzer
YACC = bison
YFLAGS = -dvty

#####################################################
# This part concerns build of libraries
#####################################################
LIBOBJS = $(addprefix $(LIB)/,generator_program.o verifier_program.o)
LIBCPPFLAGS = -std=c++11 -static -I$(INCLUDES)

lib/libTestGen.a: $(LIBOBJS)
	ar rvs $@ $^

$(LIB)/%.o: $(SRC)/%.cpp
	$(CC) $(LIBCPPFLAGS) -o $@ -c $^


######################################################
# This part is the main formatting program
######################################################

OBJS = scanner.o parser.o main.o

formatting: $(OBJS) lib/libTestGen.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LM)

main.o: main.cpp parser.hh
	$(CC) $(CPPFLAGS) -c -o $@ main.cpp

parser.hh parser.cc: formatting.y
	$(YACC) $(YFLAGS) formatting.y -o parser.cc

parser.o: parser.cc
	$(CC) $(CPPFLAGS) -c -o $@ $^

scanner.o: scanner.cc
	$(CC) $(CPPFLAGS) -c -o $@ $^

scanner.cc: formatting.l parser.hh
	$(LEX) $(LFLAGS) -o $@ formatting.l

clean:
	$(RM) -v $(LIB)/*.o $(LIB)/*.a scanner.cc parser.cc parser.hh parser.output formatting
	
