FLEX = flex
BISON = bison
LSRC = scanner.lex
YSRC = parser.yy
RM = rm -f

flex_bison_output:$(YSRC) $(LSRC)
	$(FLEX) $(LSRC)
	$(BISON) -v -d $(YSRC)

clean:
	$(RM) location.hh parser.hpp parser.cpp scanner.cpp scanner.hpp position.hh stack.hh parser.output demo

