# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -MMD -MP

# Target executable
TARGET = go

# Source files
SRCS = main.cpp lexer.cpp symbole.cpp automate.cpp Etat.cpp Expr.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Dependency files
DEPS = $(OBJS:.o=.d)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

# Phony targets
.PHONY: all clean