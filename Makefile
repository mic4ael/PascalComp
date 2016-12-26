CC=g++
CCFLAGS=-Wall
OBJECTS=parser.o lexer.o main.o

main: $(OBJECTS)
	$(CC) $(OBJECTS) -ll -o main

lexer.cpp:
	flex -o lexer.cpp lexer.l

parser.cpp parser.hpp: parser.ypp
	bison -d -o parser.cpp parser.ypp

%.o: %.cpp parser.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o lexer.cpp parser.cpp parser.hpp

.PHONY:
	clean
