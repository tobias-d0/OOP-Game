CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = $(wildcard src/*.cpp)
OUT = ArcticSurvival

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
    SFML_PATH = /opt/homebrew
    CXXFLAGS += -I$(SFML_PATH)/include
    LDFLAGS = -L$(SFML_PATH)/lib
else
    # Windows / Linux (MSYS2 etc.)
    SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    LDFLAGS =
endif

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS) $(SFML_LIBS)

clean:
	rm -f $(OUT)
