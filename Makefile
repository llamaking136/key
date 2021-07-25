CXX = g++-10
INCLUDES = -Iinclude -I/usr/local/include
UNAME = $(shell uname)
OUTPUT = key.exe
CXXFLAGS = $(INCLUDES) -std=c++17

TESTFILE = test.ky

.PHONY: clean

SRC := source
# OBJ := output

SOURCES := $(wildcard $(SRC)/*.cpp) $(wildcard include/*.cpp)
# OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

all: $(SOURCES)
	@printf "[ ALL ]\n"
	@$(CXX) $(CXXFLAGS) $^ -o $(OUTPUT)

#$(OBJ)/%.o: $(SRC)/%.cpp
#	@printf "[ COMPILE ]: src $<, out $@\n"
#	@$(CXX) $(CXXFLAGS) -c -o $@ $<
#
#$(OBJ)/%.o: include/%.cpp
#	@$(CXX) $(CXXFLAGS) -c -o $@ $<

clean: $(OUTPUT)
	@printf "[ CLEAN ]\n"
	@#rm output/*.o $(OUPUT)
	@rm $(OUTPUT)

install: $(OUTPUT)
	@printf "[ INSTALL ]\n"
	@cp $(OUTPUT) /usr/local/bin

test: $(TESTFILE)
ifeq (,$(wildcard ./$(OUTPUT)))
	@make
endif
	@printf "[ TEST ]\n"
	@./$(OUTPUT) $(TESTFILE)
