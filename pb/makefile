GXX := g++
CFLAGS := -O3 -fPIC

PROTODIR := .
BUILDDIR := build
SRCDIR := src
SRCEXT := pb.cc
PROTOSRCEXT := proto
PROTOSRC := $(shell find $(PROTODIR) -type f -name *.$(PROTOSRCEXT))
SOURCES := $(patsubst $(PROTODIR)/%,$(BUILDDIR)/%,$(PROTOSRC:.$(PROTOSRCEXT)=.$(SRCEXT)))
OBJECTS := $(patsubst $(PROTODIR)/%,$(BUILDDIR)/%,$(PROTOSRC:.$(PROTOSRCEXT)=.pb.o))

all : $(OBJECTS)

$(BUILDDIR)/%.pb.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(GXX) $(CFLAGS) -c $< -o $@

$(SRCDIR)/%.$(SRCEXT) : $(PROTODIR)/%.proto
	@mkdir -p $(SRCDIR)
	protoc --proto_path=$(PROTODIR) --python_out=$(SRCDIR) $<

.SECONDARY: $(SOURCES)

.PHONY: clean

clean:
	$(RM) -r $(BUILDDIR)
