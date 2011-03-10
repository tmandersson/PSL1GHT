CFLAGS	+=	-I/opt/local/include -I/opt/local -I/usr/include
LDFLAGS	+=	-L/opt/local/lib -L/usr/lib -lgmp -lcrypto -lz
POSTFIX	:=	
CC		:=	gcc

TARGETS	:=	make_self$(POSTFIX) make_self_npdrm$(POSTFIX) package_finalize$(POSTFIX)

all: $(TARGETS)

make_self$(POSTFIX): make_self.c
	@echo Building make_self$(POSTFIX)
	@$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

make_self_npdrm$(POSTFIX): make_self.c
	@echo Building make_self_npdrm$(POSTFIX)
	@$(CC) $< $(CFLAGS) $(LDFLAGS) -DNPDRM -o $@

package_finalize$(POSTFIX): package_finalize.c
	@echo Building package_finalize$(POSTFIX)
	@$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

install: $(TARGETS)
	@install -m 755 $(TARGETS) $(PSL1GHT)/host/bin/

clean:
	@echo clean...
	@rm -f $(TARGETS) *.exe

.PHONY: install clean
