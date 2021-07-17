# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11
LFLAGS  = -L/usr/lib

# All Targets
all: bin/cTrace

# Tool invocations
bin/cTrace: bin/main.o bin/Session.o bin/Graph.o bin/Tree.o bin/Agent.o
	@echo 'Building target: main'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/cTrace bin/main.o bin/Session.o bin/Graph.o bin/Tree.o bin/Agent.o
	@echo 'Finished building target: main'
	@echo ' '

# Depends on the source and header files
bin/main.o: src/main.cpp include/Session.h include/Agent.h include/json.hpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp
bin/Agent.o: src/Agent.cpp include/Agent.h
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Agent.o src/Agent.cpp
bin/Session.o: src/Session.cpp include/Session.h include/Agent.h include/json.hpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Session.o src/Session.cpp
bin/Tree.o: src/Tree.cpp include/Tree.h include/Session.h
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Tree.o src/Tree.cpp
bin/Graph.o: src/Graph.cpp include/Graph.h 
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Graph.o src/Graph.cpp


#Clean the build directory
clean: 
	rm -f bin/*
