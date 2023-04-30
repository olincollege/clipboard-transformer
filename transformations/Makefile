# Makefile to compile all .c files as separate programs and save them to 'bin' directory

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra

# Directories
SRCDIR := .
BINDIR := bin

# Source files
SRCS := $(wildcard $(SRCDIR)/*.c)

# Target names (based on source file names)
TARGETS := $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%,$(SRCS))

# Default target
all: clean $(TARGETS)

# Rule to compile each program
$(BINDIR)/%: $(SRCDIR)/%.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

# Rule to create 'bin' directory
$(BINDIR):
	mkdir -p $@

# Clean rule
clean:
	rm -rf $(BINDIR)
