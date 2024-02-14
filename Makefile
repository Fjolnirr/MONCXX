CXX		  := g++ -g -O0
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb -g -O0

BIN		:= bin
SRC		:= src/*.cpp $(shell find $(lib) -name *.cpp)
INCLUDE	:= -Iinclude -Ilib \
 -I/usr/local/include/mongocxx/v_noabi \
 -I/usr/local/include/bsoncxx/v_noabi \
 -I/usr/local/include/bsoncxx/v_noabi/bsoncxx/third_party/mnmlstc
LIB		:= lib 

LIBRARIES	:= -lpthread -lcrypto \
-lssl -lmongocxx -lbsoncxx
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*