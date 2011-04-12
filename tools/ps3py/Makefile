UNAME	:=	$(shell uname -s)

ifneq (,$(findstring MINGW,$(UNAME)))
	PLATFORM	:= win32
	COMPILER	:= --compiler=mingw32
	OS			:= win32
endif

all: pkgcrypt.so

pkgcrypt.so: crypt.c setup.py
	@`./find-python2` setup.py build_ext $(COMPILER)
	@cp build/lib.*/pkgcrypt.* .

clean:
	@echo clean	...
	@rm -rf build pkgcrypt.*

install: all
	@[ -d $(DEVKITPS3)/bin ] || mkdir -p $(DEVKITPS3)/bin
	@echo Installing ICON0.PNG sfo.xml pkgcrypt.* fself.py Struct.py sfo.py pkg.py
	@install -m 755 ICON0.PNG sfo.xml pkgcrypt.* $(DEVKITPS3)/bin
	@./install-scripts $(DEVKITPS3)/bin/ fself.py Struct.py sfo.py pkg.py
