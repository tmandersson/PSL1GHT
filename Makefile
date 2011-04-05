#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(PS3DEV)),)
$(error "Please set PS3DEV in your environment. export PS3DEV=<path>")
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
	@[ -d $(PS3DEV) ] || mkdir -p $(PS3DEV)
	@[ -f $(PS3DEV)/base_rules ] || cp -frv base_rules $(PS3DEV)
	@[ -f $(PS3DEV)/ppu_rules ]  || cp -frv ppu_rules  $(PS3DEV)
	@[ -f $(PS3DEV)/spu_rules ]  || cp -frv spu_rules  $(PS3DEV)

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
