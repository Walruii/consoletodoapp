# Compiler
CC = g++

# Compiler flags
CFLAGS = -c -Wall

# Linker flags
LDFLAGS = -lncurses

# executable name
EXEC = todo

# Source files
SRCS = main.cpp item.cpp todo.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(EXEC)

# Linking the object file to create the executable
$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(LDFLAGS)

# Compiling the source file to create the object file
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
