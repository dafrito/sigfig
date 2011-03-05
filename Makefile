CXXFLAGS=-Wall -Werror -g -std=c++0x
BUILDDIR=build
SRCDIR=src
TESTDIR=$(SRCDIR)/tests
NAME=phys
LIB=$(BUILDDIR)/lib$(NAME).so

libs=
cpp_sources=$(wildcard $(SRCDIR)/*.cpp)
cpp_headers=$(wildcard $(SRCDIR)/*.h $(SRCDIR)/*.hpp)
test_headers=$(wildcard $(TESTDIR)/*.h $(TESTDIR)/*.hpp)

all: $(LIB)
.PHONY: all

$(LIB): $(cpp_sources) $(cpp_headers) | $(BUILDDIR)
	g++ $(CXXFLAGS) -shared -fPIC -o $@ $(addprefix -l, $(libs)) $<

test: $(BUILDDIR)/testrunner
	$(BUILDDIR)/testrunner
.PHONY: test

$(BUILDDIR)/testrunner: $(test_headers) $(LIB) | $(BUILDDIR)
	cxxtestgen --error-printer $< | g++ $(CXXFLAGS) -L`pwd`/$(BUILDDIR) -Wl,-R`pwd`/$(BUILDDIR) -lphys -I./src -x c++ -o $@ -

$(BUILDDIR):
	mkdir $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)
.PHONY: clean
