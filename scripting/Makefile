include ../common.mk

SWIG := swig
SWIG_OPTS := -lua

all: couch_wrap.o

couch_wrap.o: couch_wrap.cpp
	$(CXX) $(CXXFLAGS) -I../core -c -o $@ $^

couch_wrap.cpp: couch.i
	$(SWIG) -c++ $(SWIG_OPTS) -I../core -o $@ $^
