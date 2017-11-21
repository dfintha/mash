BINARY=bin/mash
OBJECTS=obj/db/database.o 							\
		obj/expressions/basic.o 					\
		obj/expressions/binary.o 					\
		obj/expressions/container.o 				\
		obj/expressions/unary.o 					\
		obj/parser/parser.o 						\
		obj/parser/tokens.o 						\
		obj/system/system_custom.o 					\
		obj/system/system_posix.o 					\
		obj/system/system_win.o 					\
		obj/commands.o 								\
		obj/program.o

HEADERS=src/utilities.hpp

CXX=clang++
CXXFLAGS=-std=c++14	-I$(PWD)/src					\
         -Wall -Wextra -Weffc++ -Werror -pedantic	\
         -O2 -ffast-math -fomit-frame-pointer

BLD=`tput bold`
RED=`tput setaf 1`
GRN=`tput setaf 2`
YLW=`tput setaf 3`
BLU=`tput setaf 5`
TEL=`tput setaf 6`
NRM=`tput sgr0`

.PHONY: all clean

all: $(BINARY)

loc:
	@printf "%s[ Lines ]%s " "$(BLD)$(YLW)" $(NRM)
	@cat src/*p src/db/* src/expressions/* src/parser/* src/system/* | wc -l

$(BINARY): $(OBJECTS)
	@mkdir -p bin
	@printf "%s[Linking]%s $@\n" "$(BLD)$(TEL)" $(NRM)
	@$(CXX) $(OBJECTS) -o $@
	@printf "%s[ Strip ]%s $@\n" "$(BLD)$(TEL)" $(NRM)
	@strip $@
	@printf "%s[Success] Build Succeeded!%s\n" "$(BLD)$(GRN)" $(NRM)

obj/%.o: src/%.cpp $(HEADERS)
	@mkdir -p obj
	@printf "%s[Compile]%s $<\n" "$(BLD)$(BLU)" $(NRM)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

obj/db/%.o: src/db/%.cpp $(HEADERS)
	@mkdir -p obj/db
	@printf "%s[Compile]%s $<\n" "$(BLD)$(BLU)" $(NRM)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

obj/expressions/%.o: src/expressions/%.cpp $(HEADERS)
	@mkdir -p obj/expressions
	@printf "%s[Compile]%s $<\n" "$(BLD)$(BLU)" $(NRM)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

obj/parser/%.o: src/parser/%.cpp $(HEADERS)
	@mkdir -p obj/parser
	@printf "%s[Compile]%s $<\n" "$(BLD)$(BLU)" $(NRM)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

obj/system/%.o: src/system/%.cpp $(HEADERS)
	@mkdir -p obj/system
	@printf "%s[Compile]%s $<\n" "$(BLD)$(BLU)" $(NRM)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@printf "%s[ Clean ]%s bin\n" "$(BLD)$(RED)" $(NRM)
	@rm -rf bin
	@printf "%s[ Clean ]%s obj\n" "$(BLD)$(RED)" $(NRM)
	@rm -rf obj
