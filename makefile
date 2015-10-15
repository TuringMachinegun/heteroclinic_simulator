
BUILDDIR := build
PYDIR := python_wrapper
TARGET := bin/sim_executable
CC := g++ 
SRCDIR := src

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -std=c++11 -O2 -static -fPIC # -Wall
SFLAGS := -c++ -python
LIB := -lprotobuf -lboost_program_options
INC := -I include -I /usr/local/include/google/protobuf -L /usr/local/lib -L /usr/lib/x86_64-linux-gnu

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

wrapper:
	@echo "Making python wrapper...";
	@echo "swig $(SFLAGS) -o src/lifnetsim_wrap.cpp include/lifnetsim.i";
	@mkdir -p $(PYDIR)
	swig $(SFLAGS) -outdir $(PYDIR) -o $(PYDIR)/lifnetsim_wrap.cpp $(PYDIR)/lifnetsim.i
	@echo "gcc -std=c++11 -fPIC $(INC) -c lifnetsim_wrap.cpp -o lifnetsim_wrap.o -I/usr/include/python2.7";
	gcc -std=c++11 -fPIC $(INC) -c $(PYDIR)/lifnetsim_wrap.cpp -o $(PYDIR)/lifnetsim_wrap.o -I/usr/include/python2.7
	cp $(BUILDDIR)/*.* $(PYDIR)
	rm $(PYDIR)/sim.o
	@echo "g++ -shared $(OBJECTS) $(INC) -o build/_lifnetsim.so $(LIB)";
	g++ -shared build/lifnetsim.o $(PYDIR)/lifnetsim_wrap.o build/sim_data_transf.pb.o $(INC) -o $(PYDIR)/_lifnetsim.so $(LIB)


