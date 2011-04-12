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
	@$(MAKE) -C libsputhread --no-print-directory
	
install-headers:
	@[ -d $(DEVKITPRO)/libpsl1ght/spu ] || mkdir -p $(DEVKITPRO)/libpsl1ght/spu
	@cp -frv include $(DEVKITPRO)/libpsl1ght/spu
	
install: install-headers
	@$(MAKE) -C libsputhread install --no-print-directory
	
clean:
	@$(MAKE) -C libsputhread clean --no-print-directory
	
.PHONY: all clean install
