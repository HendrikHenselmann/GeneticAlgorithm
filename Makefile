CC := clang   # --analyze
CFLAGS := -std=c11 -g # -pedantic -Wall
LIB := -lm
INC := -I include

SRCEXT := c

SRCDIR := src
BUILDDIR := build
TESTDIR := test
TESTBUILDDIR := testBuild
TARGET := bin/main
# Filename of TARGET source code
TARGETSRC := Main

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TESTSOURCES := $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))
TESTOBJECTS := $(patsubst $(TESTDIR)/%,$(TESTBUILDDIR)/%, $(TESTSOURCES:.$(SRCEXT)=.o))

TESTTARGETS := $(addprefix bin/, $(basename $(notdir $(TESTSOURCES))))

# Phony targets (no files)
.PHONY: all compileAll compile exec compileTests test clean

# Build, test and clean in one command
all: compile exe clean

# Defining the compile command
compileAll: compile compileTests
compile: $(TARGET)
compileTests: $(TESTTARGETS)

exec: $(TARGET)
	$(TARGET)

test: $(TESTTARGETS)
	$(foreach test,$(TESTTARGETS), ./$(test) &&) @echo "Passed all that should pass."

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p bin
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(TESTTARGETS): bin/%: $(TESTBUILDDIR)/%.o $(filter-out $(BUILDDIR)/$(TARGETSRC).o, $(OBJECTS))
	@echo " Linking..."
	@mkdir -p bin
	@echo " $(CC) $^ -o $@ $(LIB)"; $(CC) $^ -o $@ $(LIB)

$(TESTBUILDDIR)/%.o: $(TESTDIR)/%.$(SRCEXT)
	@mkdir -p $(TESTBUILDDIR)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) $(TESTBUILDDIR) $(TESTTARGETS) "; $(RM) -r $(BUILDDIR) $(TARGET)  $(TESTBUILDDIR) $(TESTTARGETS)
