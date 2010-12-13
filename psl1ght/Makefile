-include Makefile.base

SPRXS		:= $(wildcard sprx/lib*)
LIBS		:= $(wildcard libs/lib*)

CGINCLUDE	:= /usr/include/Cg/cg.h

all:
	@make -C tools/raw2h --no-print-directory
	@make -C tools/ps3load --no-print-directory
	@make -C tools/sprxlinker --no-print-directory
	@if test -e $(CGINCLUDE); then make -C tools/vpcomp --no-print-directory; fi
	@make -C tools/PS3Py --no-print-directory
	@make -C crt --no-print-directory
	@make -f Makefile.lib --no-print-directory
	@for dir in $(SPRXS) $(LIBS); do \
		make -C $$dir --no-print-directory; \
	done

clean:
	rm -f $(STUBS) stub/crt1.o stub.a
	@make -C tools/raw2h clean --no-print-directory
	@make -C tools/ps3load clean --no-print-directory
	@make -C tools/sprxlinker clean --no-print-directory
	@if test -e $(CGINCLUDE); then make -C tools/vpcomp clean --no-print-directory; fi
	@make -C tools/PS3Py clean --no-print-directory
	@make -C crt clean --no-print-directory
	@make -f Makefile.lib clean --no-print-directory
	@for dir in $(SPRXS) $(LIBS); do \
		make -C $$dir clean --no-print-directory; \
	done

install: all
	@mkdir -p $(PSL1GHT)/include $(PSL1GHT)/lib $(PSL1GHT)/bin
	@cp crt/lv2-*.o $(PS3DEV)/host/ppu/ppu/lib/
	@sed "s:\$$PSL1GHT:$(PSL1GHT):" rules/lv2.ld > $(PS3DEV)/host/ppu/ppu/lib/lv2.ld
	@cp libpsl1ght.a sprx/*/*.a libs/*/*.a $(PSL1GHT)/lib/
	@cp -r include $(PSL1GHT)/
	@cp Makefile.base $(PSL1GHT)/
	@cp tools/raw2h/raw2h tools/ps3load/ps3load tools/sprxlinker/sprxlinker $(PSL1GHT)/bin/
	@if test -e $(CGINCLUDE); then cp tools/vpcomp/vpcomp $(PSL1GHT)/bin/; fi
	@cp tools/PS3Py/fself.py $(PSL1GHT)/bin/
	@cp tools/PS3Py/Struct.py $(PSL1GHT)/bin/
	@cp tools/PS3Py/sfo.py $(PSL1GHT)/bin/
	@cp tools/PS3Py/sfo.xml $(PSL1GHT)/bin/
	@cp tools/PS3Py/pkg.py $(PSL1GHT)/bin/
	@cp tools/PS3Py/ICON0.PNG $(PSL1GHT)/bin/
	@cp tools/PS3Py/pkgcrypt.* $(PSL1GHT)/bin/
	@echo Installed to $(PSL1GHT)

%.o: %.c
	$(CC) -Iinclude -c $< -o $@

%.o: %.S
	$(CC) -Iinclude -c $< -o $@

.PHONY: all clean install
