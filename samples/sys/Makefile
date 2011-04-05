#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

all:
	@$(MAKE) -C threadtest --no-print-directory
	@$(MAKE) -C msgdialog --no-print-directory

clean:
	@$(MAKE) -C threadtest clean --no-print-directory
	@$(MAKE) -C msgdialog clean --no-print-directory

.PHONY: all clean
