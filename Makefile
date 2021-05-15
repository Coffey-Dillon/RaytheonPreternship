# G++ is for the GCC compiler for C++
PP := g++

# CXXFLAGS are the complier flags for when we compile C++
FLAGS := -O0 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS)

# Folders
INC := inc
SRC := src
EXE := exe
OBJ := obj
TST := tests

#File groups
TESTS:= test-node test-quadTree test-satellite


# make initialize
initialize: 
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)

# make clean
clean:
	rm -rf $(OBJ) $(EXE)

#TODO add commands to make objects, and tests
test: initialize $(TESTS) 

$(TST)/%.o: $(TST)/%.cpp 
	$(PP) $(FLAGS) -c -o $(OBJ)/$(@F) $^

test-%: $(TST)/unit_%.o 
	$(PP) -o $(EXE)/$(@F) $(OBJ)/$(^F)

UI: initialize 
	$(PP) $(FLAGS) -c -o $(OBJ)/main.o $(SRC)/main.cpp
	$(PP) $(FLAGS) -o $(EXE)/UserInterface $(OBJ)/main.o
