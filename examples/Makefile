EXAMPLES = $(wildcard *Example)
SUBDIRSCLEAN = $(addsuffix clean,$(EXAMPLES))
SUBDIRSBUILD = $(addsuffix build,$(EXAMPLES))

.PHONY: clean all

all: $(SUBDIRSBUILD)
	@echo "build OK"

clean: $(SUBDIRSCLEAN)

%build: %
	$(MAKE) -C $<

%clean: %
	$(MAKE) -C $< clean
	
