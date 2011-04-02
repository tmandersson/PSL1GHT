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
	@$(MAKE) -C spuchain bin --no-print-directory
	@$(MAKE) -C spudma bin --no-print-directory
	@$(MAKE) -C sputest bin --no-print-directory
	@$(MAKE) -C sputhread bin --no-print-directory

	@$(MAKE) -C spuchain --no-print-directory
	@$(MAKE) -C spudma --no-print-directory
	@$(MAKE) -C sputest --no-print-directory
	@$(MAKE) -C sputhread --no-print-directory

clean:
	@$(MAKE) -C spuchain clean --no-print-directory
	@$(MAKE) -C spudma clean --no-print-directory
	@$(MAKE) -C sputest clean --no-print-directory
	@$(MAKE) -C sputhread clean --no-print-directory

.PHONY: all clean install
