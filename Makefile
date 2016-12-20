CC=g++
CCFLAGS=-Wall
OBJECTS=

lexer.cpp:
    flex --c++ -o lexer.cpp lexer.l

parser.cpp parser.hpp: parser.ypp
    bison -d -c parser.cpp parser.ypp

clean:
    -rm -f *.o lexer.cpp parser.cpp parser.hpp

.PHONY:
    clean