memory_manager.out : main.o parser.o buddy_mm.o settings.o commands.o errors.o
	g++ -o memory_manager.out main.o parser.o buddy_mm.o settings.o commands.o errors.o

main.o : main.cpp
	g++ -std=c++14 -pedantic -Wall -Wextra -c main.cpp

parser.o : parser/parser.cpp
	g++ -std=c++14 -pedantic -Wall -Wextra -c parser/parser.cpp

settings.o : properties/settings.cpp
	g++ -std=c++14 -pedantic -Wall -Wextra -c properties/settings.cpp

errors.o : properties/errors.cpp
	g++ -std=c++14 -pedantic -Wall -Wextra -c properties/errors.cpp

commands.o : properties/commands.cpp
	g++ -std=c++14 -pedantic -Wall -Wextra -c properties/commands.cpp

buddy_mm.o : buddy_mm/buddy_mm.cpp
	g++ -std=c++14 -pedantic -Wall -Wextra -c buddy_mm/buddy_mm.cpp