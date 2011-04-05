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
	@[ -d $(PSL1GHT)/spu/include/vectormath ] || mkdir -p $(PSL1GHT)/spu/include/vectormath
	@cp -frv $(CURDIR)/c $(PSL1GHT)/spu/include/vectormath
	@cp -frv $(CURDIR)/cpp $(PSL1GHT)/spu/include/vectormath
	
clean:
	
.PHONY: all clean install
