include common.mk

CORE_SRC = $(wildcard core/*.cpp)
CORE_OBJ = $(CORE_SRC:.cpp=.o)

all: couch
couch: $(CORE_OBJ) scripting/couch_wrap.o
	$(CXX) $(LIBS) -o $@ $^

$(CORE_OBJ): %.o: %.cpp
	$(MAKE) -C core $(notdir $@)

scripting/couch_wrap.o: scripting/couch.i
	$(MAKE) -C scripting $(notdir $@)
