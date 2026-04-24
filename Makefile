CXX := g++
CXXFLAGS := -std=gnu++17 -O2 -pipe -s
LDFLAGS :=

SRC := main.cpp
BIN := code

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(BIN)

.PHONY: all clean
