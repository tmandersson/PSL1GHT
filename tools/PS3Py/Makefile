
all: pkgcrypt.so

pkgcrypt.so: crypt.c setup.py
	@python setup.py build_ext
	@cp build/lib.*/pkgcrypt.* .

clean:
	rm -rf build pkgcrypt.*

install: all
	@cp -fv ICON0.PNG pkgcrypt.* $(PSL1GHT)/host/bin/
	@./install-scripts $(PSL1GHT)/host/bin/ fself.py Struct.py sfo.py pkg.py
