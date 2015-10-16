CC = g++
CFLAGS = -O3 -fPIC

PROTODIR = .
BUILDDIR = build
SRCDIR = src
SRCEXT = pb.cc
PROTOSRCEXT = proto
PROTOSRC = $(shell find $(SRCDIR) -type f -name *.$(PROTOSRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(PROTOSRC:.$(PROTOSRCEXT)=.pb.o))

all : $(OBJECTS)

$(BUILDDIR)/%.pb.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/%.$(SRCEXT) : $(SRCDIR)/%.proto
	protoc --cpp_out=$(SRCDIR) $<

clean:
	$(RM) -r $(BUILDDIR)
