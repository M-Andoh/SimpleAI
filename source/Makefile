PROGRAM = libSimpleAI.a
SRCS += Adapter.cpp
SRCS += Data.cpp
SRCS += Layer.cpp
SRCS += LayerManager.cpp
SRCS += Node.cpp
SRCS += TestData.cpp
SRCS += TrainData.cpp
SRCS += Sigmoid.cpp
SRCS += ReLU.cpp
SRCS += mkbmp.cpp
OBJS = ${SRCS:.cpp=.o}
DATE := $(shell date +"%Y/%m/%d %H:%M:%S")

CC = gcc
CXX = g++ -std=c++14
CFLAGS += -Wall -g -fPIC -DDEBUG -DVERSION="002.002" -DDATE="${DATE}" -I/usr/local/include -I../header
#CFLAGS += -Wall -O3  -DDATE="${DATE}"
LDFLAGS += -g -shared
#LDFLAGS += -O3
#LIBS += -L/usr/local/lib 
#LIBS += -L/usr/local/lib -lcurl -lyajl -lboost_regex -liconv
LIBS += -L/usr/local/lib -lcurl -lz
SUFFIX = /usr/local
ARFLAGS = rcs

.SUFFIXES:	.cpp .o

.PHONY: all
all: depend $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(AR) $(ARFLAGS) $(PROGRAM) $(OBJS)
	#$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)
	cp $(PROGRAM) ../
	

install:
	install -s $(PROGRAM) $(SUFFIX)/bin

.cpp.o:
	$(CXX) $(CFLAGS) -c $<

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS) depend.inc

.PHONY: depend
depend: $(SRCS)
	-@ echo 'Making depend'
	-@ $(RM) depend.inc
	-@ for i in $^;\
	   do\
		if test -e $i; then\
			echo 'target: ' $$i ;\
			sh -c "${CXX} -I../header -MM $$i |\
			sed 's/\ [_a-zA-Z0-9][_a-zA-Z0-9]*\.cpp//g' |\
			sed 's/\ [_a-zA-Z0-9][_a-zA-Z0-9]*\.c//g' >> depend.inc";\
		fi;\
	  done

-include depend.inc
