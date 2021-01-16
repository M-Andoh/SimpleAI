LIB = libSimpleAI.a
PROGRAM1 = SimplAILearn
PROGRAM2 = SimplAITest
PROGRAM3 = SimplAILoto6
PROGRAM3 = SimplAILoto7
.PHONY: all
all: $(LIB) $(PROGRAM1) $(PROGRAM2) $(PROGRAM3) $(PROGRAM4)

$(LIB):
	$(MAKE) -C source
	#ranlib $(LIB)

$(PROGRAM1): $(LIB)
	$(MAKE) -f Makefile.Learn

$(PROGRAM2): $(LIB)
	$(MAKE) -f Makefile.Test

$(PROGRAM3): $(LIB)
	$(MAKE) -f Makefile.Loto6

$(PROGRAM4): $(LIB)
	$(MAKE) -f Makefile.Loto7

.PHONY: clean
clean:
	$(MAKE) clean -C source
	$(MAKE) clean -f Makefile.Learn
	$(MAKE) clean -f Makefile.Test
	$(MAKE) clean -f Makefile.Loto6
	$(MAKE) clean -f Makefile.Loto7
	$(RM) $(LIB) train-images-idx3-ubyte train-labels-idx1-ubyte *.a *.so
