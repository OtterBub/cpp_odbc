# Makefile for compiling the ODBC C++ example on Linux

CC = g++
TARGET = main
RM = rm -f
LDFLAGS = -lodbc
CFLAGS = -std=c++11 -Wall -Wextra -g

# Source file
SRC = main.cpp

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Clean up build files
clean:
	-$(RM) $(TARGET) *.o
