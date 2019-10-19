CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/runner

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
INC := -I include

ARGS := -std=c++2a -O3

$(TARGET) : $(OBJECTS)
	@echo "Linking..."
	@echo "$(CC) $(ARGS) $^ -o $(TARGET)"; $(CC) $(ARGS) $^ -o $(TARGET)

$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(ARGS) $(INC) -c -o $@ $<"; $(CC) $(ARGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning..."
	@echo "$(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean