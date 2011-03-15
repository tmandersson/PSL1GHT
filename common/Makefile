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
	@make -C libsimdmath --no-print-directory
	@make -C vectormath --no-print-directory
	
install:
	@make -C libsimdmath install --no-print-directory
	@make -C vectormath install --no-print-directory
	
clean:
	@make -C libsimdmath clean --no-print-directory
	@make -C vectormath clean --no-print-directory
	
.PHONY: all clean install
