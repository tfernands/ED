
# Name of the project and folder structure config
PROJ_NAME=tp3

CPP_PATH=./src/
HPP_PATH=./include/
BUILD_PATH=./obj/
BIN_PATH=./bin/

# .cpp files
CPP_SOURCE=$(wildcard $(CPP_PATH)*.cpp)

# .h files
HPP_SOURCE=$(wildcard $(HPP_PATH)*.hpp)

# .o files
OBJ_SOURCE=$(subst .cpp,.o, $(subst $(CPP_PATH), $(BUILD_PATH), $(CPP_SOURCE)))

# Compiler
CC=g++

# Flags for compiler
CC_FLAGS=-c			\
		 -W			\
		 -Wall		\
		 -ansi		\
		 -pedantic  \
		 -Ofast     \
		 -std=c++11

#
# Compilation and linking
#

all: folderStructure $(PROJ_NAME) 

$(PROJ_NAME): $(OBJ_SOURCE)
	@ $(CC) -o $(BIN_PATH)$@ $^

./obj/%.o: $(CPP_PATH)%.cpp
	@ $(CC) $< $(CC_FLAGS) -o $@

folderStructure:
	@ mkdir -p $(BUILD_PATH)
	@ mkdir -p $(BIN_PATH)

clean:
	@ rm -rf $(BUILD_PATH)/*
	@ rm -f $(BIN_PATH)/*

run:
	@ clear && make clean && make all && clear && $(BIN_PATH)$(PROJ_NAME)

.PHONY: all clean run