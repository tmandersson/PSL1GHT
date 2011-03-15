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
	@make -C crt --no-print-directory
	@make -C sprx --no-print-directory
	@make -C librt --no-print-directory
	@make -C librsx --no-print-directory
	
install-headers:
	@[ -d $(DEVKITPRO)/libpsl1ght/ppu ] || mkdir -p $(DEVKITPRO)/libpsl1ght/ppu
	@cp -frv include $(DEVKITPRO)/libpsl1ght/ppu
	
install: install-headers
	@make -C crt install --no-print-directory
	@make -C sprx install --no-print-directory
	@make -C librt install --no-print-directory
	@make -C librsx install --no-print-directory
	
clean:
	@make -C crt clean --no-print-directory
	@make -C sprx clean --no-print-directory
	@make -C librt clean --no-print-directory
	@make -C librsx clean --no-print-directory
	
.PHONY: all clean install
