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
	@$(MAKE) -C rsxtest --no-print-directory
	@$(MAKE) -C rsxtest_spu bin --no-print-directory
	@$(MAKE) -C rsxtest_spu --no-print-directory
	
clean:
	@$(MAKE) -C rsxtest clean --no-print-directory
	@$(MAKE) -C rsxtest_spu clean --no-print-directory
	
.PHONY: all clean install
