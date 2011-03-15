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
	
install:
	@[ -d $(DEVKITPRO)/libpsl1ght/ppu/include/vectormath ] || mkdir -p $(DEVKITPRO)/libpsl1ght/ppu/include/vectormath
	@cp -frv $(CURDIR)/c $(DEVKITPRO)/libpsl1ght/ppu/include/vectormath
	@cp -frv $(CURDIR)/cpp $(DEVKITPRO)/libpsl1ght/ppu/include/vectormath
	
clean:
	
.PHONY: all clean install
