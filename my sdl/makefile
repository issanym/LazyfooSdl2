# Compiler settings
CC := g++
CFLAGS := -std=c++14 -Wall -Wextra -O3
LDFLAGS := -lSDL2

# Directories
SRCDIR := src
INCDIR := headers
BUILDDIR := build
BINDIR := bin

# Files
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRCS:.cpp=.o))
TARGET := $(BINDIR)/myProgram

# Targets
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(wildcard $(INCDIR)/*.h)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

clean:
	$(RM) -r $(BUILDDIR) $(BINDIR)

.PHONY: all clean

