#

CXX		= g++
CFLAGS		= -Wall -std=c++11
OFLAGS		= -O3


#

OBJ		= obj/main.o \
		  obj/bound.o \
		  obj/variable.o \
		  obj/tree.o \
		  obj/inequation.o \
		  obj/encoder.o \
		  obj/atom.o \
		  obj/literal.o \
		  obj/clause.o

TGT		= bin/csp2sat

# 

all:	$(TGT)
	@echo "build done"


$(TGT):	$(OBJ)
	$(CXX) $(CFLAGS) $(OFLAGS) -o $@ $^


obj/%.o:	src/%.cpp
	$(CXX) -c $(CFLAGS) $(OFLAGS) -o $@ $<


# 

clean:	$(TGT) $(OBJ)
	rm $^





