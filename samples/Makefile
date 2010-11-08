
MAKEFILES :=  $(wildcard **/Makefile)
SUBDIRS :=  $(dir $(MAKEFILES))

.PHONY: all show

all:
	for dir in $(SUBDIRS); do \
		$(MAKE) clean pkg -C $$dir; \
	done

show:
	@echo 'MAKEFILES : ' $(MAKEFILES)
	@echo 'SUBDIR : ' $(SUBDIR)

