# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable
TARGET = main

# Source files
SRCS = main.cpp lexer.cpp symbole.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
HEADERS = lexer.h symbole.h

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean