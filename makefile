BINARY=bin/mash
OBJECTS=obj/commands.o  	\
        obj/container.o         \
        obj/database.o          \
        obj/expr_basic.o        \
        obj/expr_binary.o       \
        obj/expr_unary.o        \
        obj/parser.o            \
        obj/plot.o              \
        obj/program.o 		\
        obj/system_custom.o     \
        obj/system_posix.o      \
        obj/system_win.o        \
        obj/tokens.o

HEADERS=include/utilities.hpp   \
        include/messages.hpp

CXX=clang++
CXXFLAGS=-std=c++14 -Iinclude -Wall -Wextra -Werror -pedantic -O2 -ffast-math
LDFLAGS=

BLD=`tput bold`
RED=`tput setaf 1`
GRN=`tput setaf 2`
YLW=`tput setaf 3`
BLU=`tput setaf 5`
TEL=`tput setaf 6`
NRM=`tput sgr0`

.PHONY: all clean

all: $(BINARY)

withplot: LDFLAGS += `sdl-config --libs` -lSDL_gfx -GL -lGLU
withplot: CXXFLAGS += `sdl-config --cflags` -DMASH_PLOT_FEATURE
withplot: $(BINARY)

loc:
	@printf "%s[ Lines ]%s " "$(BLD)$(YLW)" $(NRM)
	@cat src/*p src/db/* src/expressions/* src/parser/* src/system/* | wc -l

$(BINARY): $(OBJECTS)
	@mkdir -p bin
	@printf "%s[Linking]%s $@\n" "$(BLD)$(TEL)" $(NRM)
	@$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
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
