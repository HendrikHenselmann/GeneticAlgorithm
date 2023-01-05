CC := clang   # --analyze
CFLAGS := -std=c11 # -g -pedantic -Wall -Wextra
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

# Defining compile commands that include linking
compileAll: compile compileTests
compile: $(TARGET)
	@echo "Creating log output directory..."
	@mkdir -p logs
compileTests: $(TESTTARGETS)

# Compiling target and execute it
exec: compile $(TARGET)
	$(TARGET)

# Running test targets
test: $(TESTTARGETS)
	$(foreach test, $(TESTTARGETS), echo "\n$$(basename $(test))..." && ./$(test) &&) echo "\nPassed all that should pass.\n"

# Linking object files
$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p bin
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

# Compiling source code into object files
# Not including test cases
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

# Linking tests
$(TESTTARGETS): bin/%: $(TESTBUILDDIR)/%.o $(filter-out $(BUILDDIR)/$(TARGETSRC).o, $(OBJECTS))
	@echo " Linking..."
	@mkdir -p bin
	@echo " $(CC) $^ -o $@ $(LIB)"; $(CC) $^ -o $@ $(LIB)

# Compiling source code into object files
# Including test cases
$(TESTBUILDDIR)/%.o: $(TESTDIR)/%.$(SRCEXT)
	@mkdir -p $(TESTBUILDDIR)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

# Deleting all intermediate files of the compile step
# Not deleting executable binaries and program execution logs
clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TESTBUILDDIR) ";
	$(RM) -r $(BUILDDIR) $(TESTBUILDDIR)

# Resetting the whole project folder to its initial state after download
reset:
	@echo " Resetting...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) $(TESTBUILDDIR) $(TESTTARGETS) ";
	$(RM) -r $(BUILDDIR) $(TARGET)  $(TESTBUILDDIR) $(TESTTARGETS)
	$(RM) -r logs
