GXX := g++
CC := gcc
CFLAGS := -g -O2 -std=c++11 -fPIC  # both fPIC and c++11 standard are needed (expect errors if removed)

# protocol buffer variables
PBDIR := pb
PBSRCDIR := $(PBDIR)/src
PBBUILDDIR := $(PBDIR)/build
PBPROTOEXT := proto
PBPROTOCOLS := $(shell find $(PBDIR) -type f -name *.$(PBPROTOEXT))
PBSRCEXT := pb.cc
PBSOURCES := $(patsubst $(PBDIR)/%, $(PBSRCDIR)/%, $(PBPROTOCOLS:.$(PBPROTOEXT)=.$(PBSRCEXT)))
PBOBJECTS := $(patsubst $(PBDIR)/%, $(PBBUILDDIR)/%, $(PBPROTOCOLS:.$(PBPROTOEXT)=.pb.o))

# event based simulator variables
SRCDIR := src
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
BUILDDIR := build
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
SIMLIBNAME := lifnetsim
SIMLIBOBJ := $(BUILDDIR)/$(SIMLIBNAME).o

# python wrapper variables
SFLAGS := -c++ -python
PWDIR := python_wrapper
PWTEMPNAME := $(SIMLIBNAME)_wrap
PWSRCDIR := $(PWDIR)/src
PWSRCEXT := cpp
PWSOURCE := $(PWSRCDIR)/$(PWTEMPNAME).$(PWSRCEXT)
PWBUILDDIR := $(PWDIR)/build
PWTEMPOBJ := $(PWBUILDDIR)/$(PWTEMPNAME).o
PWIFILE := $(shell find $(PWDIR) -type f -name '*.i')
PWTARGETDIR := $(PWDIR)/bin
PWTARGET := $(PWTARGETDIR)/_$(SIMLIBNAME).so # don't change underscore, wrapper needs it

PWINC := -Iinclude -I /usr/local/include/google/protobuf -I$(PBSRCDIR) -I/usr/include/python2.7 
PWLIB := -lprotobuf

# command line interface variables
CLTARGET := bin/cl_sim
CLLIB := -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -lprotobuf -lboost_program_options
CLINC := -Iinclude -I/usr/local/include/google/protobuf -I$(PBSRCDIR)

all: $(PBOBJECTS) $(PWTARGET) $(CLTARGET)

$(PBBUILDDIR)/%.pb.o : $(PBSRCDIR)/%.$(PBSRCEXT)
	@mkdir -p $(PBBUILDDIR)
	$(GXX) $(CFLAGS) -c $< -o $@

$(PBSRCDIR)/%.$(PBSRCEXT) : $(PBDIR)/%.$(PBPROTOEXT)
	@mkdir -p $(PBSRCDIR)
	protoc --proto_path=$(PBDIR) --cpp_out=pb/src $<

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(GXX) $(CFLAGS) $(CLINC) -c -o $@ $<
	@echo $^

python_interface: $(PWTARGET)

$(PWTARGET): $(SIMLIBOBJ) $(PBOBJECTS)
	@echo "Making python wrapper...";
	@mkdir -p $(PWBUILDDIR) $(PWSRCDIR) $(PWTARGETDIR)
	swig $(SFLAGS) -outdir $(PWTARGETDIR) -o $(PWSOURCE) $(PWIFILE)
	$(CC) $(CFLAGS) $(ALL_CFLAGS) -c $(PWSOURCE) -o $(PWTEMPOBJ) $(PWINC)
	$(GXX) -shared $(SIMLIBOBJ) $(PBOBJECTS) $(PWTEMPOBJ) $(PWINC) -o $(PWTARGET) $(PWLIB)

cmline_interface: $(CLTARGET)

$(CLTARGET): $(PBOBJECTS) $(OBJECTS)
	@echo " Linking..."
	$(GXX) $^ -o $(CLTARGET) $(CLLIB)

.SECONDARY: $(PBSOURCES)

clean_pw:
	@echo "Cleaning python wrapper files..."
	$(RM) -r $(PWBUILDDIR) $(PWTARGETDIR)

clean_pb:
	@echo "Cleaning protobuf files..."
	$(RM) -r $(PBBUILDDIR)

clean_sim :
	@echo "Cleaning simulator files..."
	$(RM) -r $(BUILDDIR)

clean_cl:
	@echo " Cleaning command line interface files..."
	$(RM) -r  $(CLTARGET)

clean: clean_pb clean_sim clean_pw clean_cl

