
all: pkgcrypt.so

pkgcrypt.so: crypt.c setup.py
	@python setup.py build_ext
	@cp build/lib.*/pkgcrypt.* .

clean:
	rm -rf build pkgcrypt.*

install: all
	@cp -fv fself.py Struct.py sfo.py sfo.xml pkg.py ICON0.PNG pkgcrypt.* $(PSL1GHT)/host/bin/
