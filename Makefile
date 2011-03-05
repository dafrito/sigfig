CXXFLAGS=-Wall -Werror -g -std=c++0x
BUILDDIR=build
SRCDIR=src
TESTDIR=$(SRCDIR)/tests

libs=
cpp_headers=$(wildcard $(SRCDIR)/*.h $(SRCDIR)/*.hpp)
test_headers=$(wildcard $(TESTDIR)/*.h $(TESTDIR)/*.hpp)

all: $(BUILDDIR)/phys
.PHONY: all

$(BUILDDIR)/phys: $(cpp_headers)
	g++ $(CXXFLAGS) -o $(BUILDDIR)/phys $(addprefix -l, $(libs)) $(cpp_files)

test: $(BUILDDIR)/testrunner
	$(BUILDDIR)/testrunner
.PHONY: test

$(BUILDDIR)/testrunner: $(test_headers) | $(BUILDDIR)
	cxxtestgen --error-printer $< | g++ $(CXXFLAGS) -x c++ -o $@ -

$(BUILDDIR):
	mkdir $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)
.PHONY: clean
