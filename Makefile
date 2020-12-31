LIB = libSimpleAI.a
PROGRAM1 = SimplAILearn
PROGRAM2 = SimplAITest

.PHONY: all
all: $(LIB) $(PROGRAM1) $(PROGRAM2)

$(LIB):
	$(MAKE) -C source
	#ranlib $(LIB)

$(PROGRAM1):
	$(MAKE) -f Makefile.Learn

$(PROGRAM2):
	$(MAKE) -f Makefile.Test

.PHONY: clean
clean:
	$(MAKE) clean -C source
	$(MAKE) clean -f Makefile.Learn
	$(MAKE) clean -f Makefile.Test
	$(RM) $(LIB) train-images-idx3-ubyte train-labels-idx1-ubyte *.a *.so
