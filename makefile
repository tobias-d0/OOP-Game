CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = src/*.cpp
OUT = ArcticSurvival

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f $(OUT)