#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPro")
endif

ifeq ($(strip $(DEVKITPS3)),)
$(error "Please set DEVKITPS3 in your environment. export DEVKITPS3=<path>")
endif

all:
	@$(MAKE) -C audio --no-print-directory
	@$(MAKE) -C graphics --no-print-directory
	@$(MAKE) -C network --no-print-directory
	@$(MAKE) -C spu --no-print-directory
	@$(MAKE) -C sys --no-print-directory

clean:
	@$(MAKE) -C audio clean --no-print-directory
	@$(MAKE) -C graphics clean --no-print-directory
	@$(MAKE) -C network clean --no-print-directory
	@$(MAKE) -C spu clean --no-print-directory
	@$(MAKE) -C sys clean --no-print-directory
	
.PHONY: all clean
