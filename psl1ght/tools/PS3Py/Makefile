
all: pkgcrypt.so

pkgcrypt.so: crypt.c setup.py
	@python setup.py build_ext
	@cp build/lib.*/pkgcrypt.so .

clean:
	rm -rf build pkgcrypt.so
