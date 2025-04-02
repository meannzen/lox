# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Target executable name
TARGET = myprogram

# Source files
SOURCES = main.c chunk.c debug.c memory.c value.c

# Object files (replace .c with .o)
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets (not actual files)
.PHONY: all clean
