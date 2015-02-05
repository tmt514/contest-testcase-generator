LEX = flex
YACC = bison -y
OBJECTS = scanner.o parser.o
CC = g++
CPPFLAGS = -std=c++11

all: formatting
	
formatting: scanner.o parser.o main.o libyywrap.o
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $^

parser.cpp: formatting.y
	$(YACC) $(YFLAGS) -o $@ $^

parser.o: parser.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $^

scanner.o: scanner.cpp libyywrap.o
	$(CC) $(CPPFLAGS) -c -o $@ $^

libyywrap.o: libyywrap.cc
	$(CC) $(CPPFLAGS) -c -o $@ $^

scanner.cpp: formatting.l
	$(LEX) $(LFLAGS) -o $@ $^

clean:
	$(RM) *.o scanner.c parser.c
	
