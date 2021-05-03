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
TESTS:= $(TST)/unit_node.o $(TST)/unit_quadTree.o


# make initialize
initialize:
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)

# make clean
clean:
	rm -rf $(OBJ) $(EXE)

#TODO add commands to make objects, and tests
test: $(TESTS)

$(TST)/%.o: $(TST)/%.cpp 
	$(PP) $(FLAGS) -c -o $(OBJ)/$(@F) $^

test-%: $(TST)/unit_%.o
	$(PP) -o $(EXE)/$(@F) $(OBJ)/$(^F)

