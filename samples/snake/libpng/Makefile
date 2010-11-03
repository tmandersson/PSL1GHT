
all: libpng.a pnglib.h pngconf.h

libpng.a:
	@./build.sh
	@cp lib/libpng.a ./

pnglib.h:
	@cp include/pnglib.h ./

pngconf.h:
	@cp include/pngconf.h ./

clean:
	rm -rf *.tar.gz zlib-* libpng-* bin include lib share libpng.a pnglib.h pngconf.h
