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

.PHONY: samples

all: install-ctrl
	@$(MAKE) -C common --no-print-directory
	@$(MAKE) -C ppu --no-print-directory
	@$(MAKE) -C spu --no-print-directory
	@$(MAKE) -C tools --no-print-directory

samples:
	@$(MAKE) -C samples --no-print-directory

doc:
	@doxygen doxygen.conf

install-ctrl:
	@[ -d $(DEVKITPS3) ] || mkdir -p $(DEVKITPS3)
	@[ -f $(DEVKITPS3)/base_rules ] || cp -frv base_rules $(DEVKITPS3)
	@[ -f $(DEVKITPS3)/ppu_rules ]  || cp -frv ppu_rules  $(DEVKITPS3)
	@[ -f $(DEVKITPS3)/spu_rules ]  || cp -frv spu_rules  $(DEVKITPS3)
	
install-socat:
	@$(MAKE) -C tools install-socat --no-print-directory	
	
install:
	@$(MAKE) -C common install --no-print-directory
	@$(MAKE) -C ppu install --no-print-directory
	@$(MAKE) -C spu install --no-print-directory
	@$(MAKE) -C tools install --no-print-directory

clean:
	@$(MAKE) -C common clean --no-print-directory
	@$(MAKE) -C ppu clean --no-print-directory
	@$(MAKE) -C spu clean --no-print-directory
	@$(MAKE) -C tools clean --no-print-directory
	@rm -rf doc

.PHONY: all clean install
