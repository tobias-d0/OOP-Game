CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = testcode/windowtest.cpp
OUT = windowtest

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f $(OUT)