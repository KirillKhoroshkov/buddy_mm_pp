memory_manager.out : main.o parser.o
	g++ -o memory_manager.out main.o parser.o

main.o : main.cpp
	g++ -std=c++14 -pedantic -Wall -Wextra -c main.cpp

parser.o : parser/parser.cpp
	g++ -std=c++14 -pedantic -Wall -Wextra -c parser/parser.cpp

