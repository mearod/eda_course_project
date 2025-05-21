TARGET = demo

FLEX = flex
BISON = bison
LSRC = parser/scanner.lex
YSRC = parser/parser.yy
RM = rm -f
CXX = g++
CSRCS = $(shell find . -name "*.c" -or -name "*.cc" -or -name "*.cpp") 

all: $(TARGET)

demo: $(CSRCS) $(LSRC) $(YSRC)
	@echo "compiling..."
	make -C /home/kyon/eda_course/assignment4/hw4_project/parser flex_bison_output
	$(CXX) -g -I .  -o $@ $(CSRCS) -larmadillo -llapack -lblas -lfl -ly

.PHOYN: clean distclean

clean:
	make -C /home/kyon/eda_course/assignment4/hw4_project/parser clean
	$(RM) demo
