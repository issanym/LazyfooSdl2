# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# SDL2-specific flags
# SDL2_CFLAGS = $(shell sdl2-config --cflags)
# SDL2_LDFLAGS = $(shell sdl2-config --libs)

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2main -lSDL2_image

# Target and source file
TARGET = 06
SRC = 06.cpp

# Build the target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -o $(TARGET) $(SRC) $(LINKER_FLAGS)

# Clean up build files
clean:
	rm -f $(TARGET)
