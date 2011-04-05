#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

all:
	@$(MAKE) -C rsxtest --no-print-directory
	@$(MAKE) -C rsxtest_spu bin --no-print-directory
	@$(MAKE) -C rsxtest_spu --no-print-directory

clean:
	@$(MAKE) -C rsxtest clean --no-print-directory
	@$(MAKE) -C rsxtest_spu clean --no-print-directory

.PHONY: all clean install
