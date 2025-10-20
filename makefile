# Compiler
CXX = g++

# Source files
SRC = $(wildcard src/*.cpp)
OUT = ArcticSurvival

# Detect OS
UNAME_S := $(shell uname -s)

# ----------------- OS-Specific Settings -----------------
ifeq ($(UNAME_S),Darwin)
    SFML_PATH = /Library/Frameworks/SFML-3.0.2/Frameworks
    CXXFLAGS = -std=c++17 -Wall -Iinclude -F$(SFML_PATH)
    LDFLAGS = -framework sfml-graphics \
              -framework sfml-window \
              -framework sfml-system \
              -framework sfml-audio \
              -Wl,-rpath,$(SFML_PATH)
    SFML_LIBS =

else ifeq ($(UNAME_S),Linux)
    # Linux: SFML in home folder
    SFML_PATH = ~/SFML-3.0.2
    CXXFLAGS = -std=c++17 -Wall -Iinclude -I$(SFML_PATH)/include
    LDFLAGS = -L$(SFML_PATH)/lib
    SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

else
    # Windows: SFML in C:/SFML-3.0.2
    SFML_PATH = C:/SFML-3.0.2
    CXXFLAGS = -std=c++17 -Wall -Iinclude -I$(SFML_PATH)/include
    LDFLAGS = -L$(SFML_PATH)/lib
    SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif

# ----------------- Targets -----------------
all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS) $(SFML_LIBS)

clean:
	rm -f $(OUT)
