ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPro")
endif

ifeq ($(strip $(DEVKITPS3)),)
$(error "Please set DEVKITPS3 in your environment. export DEVKITPS3=<path>")
endif

all:
	@$(MAKE) -C ppu --no-print-directory
	@$(MAKE) -C spu --no-print-directory
	
install:
	@$(MAKE) -C ppu install --no-print-directory
	@$(MAKE) -C spu install --no-print-directory
	
clean:
	@$(MAKE) -C ppu clean --no-print-directory
	@$(MAKE) -C spu clean --no-print-directory
	
.PHONY: all clean install
