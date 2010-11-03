
all: libpng.a png.h pngconf.h

libpng.a:
	@./build.sh
	@cp lib/libpng.a ./

png.h:
	@cp include/png.h ./

pngconf.h:
	@cp include/pngconf.h ./

clean:
	rm -rf *.tar.gz zlib-* libpng-* bin include lib share libpng.a pnglib.h pngconf.h
