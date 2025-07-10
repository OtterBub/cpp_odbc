# Makefile for compiling the ODBC C++ example on multiple platforms

# Default to g++ for non-Windows environments
CC = g++
TARGET = main
RM = rm -f
LDFLAGS = -lodbc
CFLAGS = -std=c++11 -Wall -Wextra -g

# Detect Windows and override settings for Visual C++
ifeq ($(OS),Windows_NT)
    CC = cl.exe
    TARGET = main.exe
    RM = del /Q
    LDFLAGS = odbc32.lib
    CFLAGS = /EHsc /W4 /D_CRT_SECURE_NO_WARNINGS
endif

# Source file
SRC = main.cpp

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRC)
ifeq ($(OS),Windows_NT)
	$(CC) $(CFLAGS) $(SRC) /link $(LDFLAGS) /out:$(TARGET)
else
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)
endif

# Clean up build files
clean:
ifeq ($(OS),Windows_NT)
	-$(RM) $(TARGET) *.obj
else
	-$(RM) $(TARGET) *.o
endif