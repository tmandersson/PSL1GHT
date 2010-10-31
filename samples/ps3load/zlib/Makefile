ZLIB_VERSION	:=	1.2.5

all: libz.a zlib.h zconf.h

libz.a:
	@./build.sh
	@cp zlib-$(ZLIB_VERSION)/libz.a ./

zlib.h:
	@cp zlib-$(ZLIB_VERSION)/zlib.h ./

zconf.h:
	@cp zlib-$(ZLIB_VERSION)/zconf.h ./

clean:
	rm -rf zlib-$(ZLIB_VERSION).tar.gz zlib-$(ZLIB_VERSION) libz.a zlib.h zconf.h
