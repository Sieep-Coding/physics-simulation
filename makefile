# Makefile for raylib application

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# raylib library flags
LIBS = -lraylib -lm

# Source files
SRCS = raylib_game.c

# Executable name
EXEC = physics_engine

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC) $(LIBS)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(EXEC)
