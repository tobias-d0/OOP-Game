# Compiler
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Iinclude -I./SFML-2.6.0/include

# Source files
SRC = $(wildcard src/*.cpp) main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = ArcticSurvival

# Link directly to dylib files
LDFLAGS = ./SFML-2.6.0/lib/libsfml-graphics.2.6.0.dylib \
          ./SFML-2.6.0/lib/libsfml-window.2.6.0.dylib \
          ./SFML-2.6.0/lib/libsfml-system.2.6.0.dylib \
          ./SFML-2.6.0/lib/libsfml-audio.2.6.0.dylib \
          ./SFML-2.6.0/lib/libsfml-network.2.6.0.dylib

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
