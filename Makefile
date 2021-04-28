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


# make initialize
initialize:
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)

# make clean
clean:
	rm -rf $(OBJ) $(EXE)

#TODO add commands to make objects, and tests
#TODO fix compilier warning with tests so that all flags can be used

$(TST)/%.o: $(TST)/%.cpp
	$(PP) $(FLAGS) -c -o $@ $^

test: $(TST)/unit_node.o $(TST)/unit_quadTree.o 
	$(PP) -o $(EXE)/unit_node $(EXE)/unit_quadTree $^




