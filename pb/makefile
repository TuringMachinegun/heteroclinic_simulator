CC = g++
CFLAGS = -O3 -fPIC

PROTODIR = .
BUILDDIR = build
SRCDIR = src
SRCEXT = pb.cc
PROTOSRCEXT = proto
PROTOSRC = $(shell find $(PROTODIR) -type f -name *.$(PROTOSRCEXT))
OBJECTS = $(patsubst $(PROTODIR)/%,$(BUILDDIR)/%,$(PROTOSRC:.$(PROTOSRCEXT)=.pb.o))

all : $(OBJECTS)

$(BUILDDIR)/%.pb.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/%.$(SRCEXT) : $(PROTODIR)/%.proto
	@mkdir -p $(SRCDIR)
	protoc --cpp_out=$(SRCDIR) --python_out=$(SRCDIR) $<

.PHONY: clean

clean:
	$(RM) -r $(BUILDDIR) $(SRCDIR)
