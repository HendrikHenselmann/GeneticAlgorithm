CC := gcc  # This is the main compiler
# CC := clang --analyze  # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := bin/exe

SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c11 -g -pedantic -Wall
LIB := -lm
INC := -I include

# Phony targets (no files)
.PHONY: all compile test clean ticket

# Build, test and clean in one command
all: compile test clean

# Defining the compile command
compile: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
test:
	$(CC) $(CFLAGS) test/tester.c $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.c $(INC) $(LIB) -o bin/ticket
