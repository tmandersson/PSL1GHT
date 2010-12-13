-include ../Makefile.base

CFILES		:= $(wildcard *.c)
SFILES		:= $(wildcard *.S)
CRT0		:= lv2-crt0.o
CRT1		:= crt0.o crt1.o

STUBS		:= $(SFILES:.S=.o) $(CFILES:.c=.o)

all: $(STUBS)
	@ppu-ld -r $(CRT1) -o $(CRT0)

clean:
	rm -f $(STUBS) $(CRT0)

%.o: %.c
	$(CC) -I../include -c $< -o $@

%.o: %.S
	$(CC) -I../include -c $< -o $@

.PHONY: all clean
