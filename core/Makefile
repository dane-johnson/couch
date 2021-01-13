include ../common.mk

SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:.cpp=.o)

all: couch
couch: $(OBJS)
	$(CXX) $(LIBS) -o $@ $^
