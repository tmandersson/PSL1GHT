#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

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
