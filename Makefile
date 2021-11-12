CC := clang   # --analyze
SRCDIR := src
BUILDDIR := build
TARGET := bin/main

SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c11 -g  # -pedantic -Wall
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
	@mkdir -p bin
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
