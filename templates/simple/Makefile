##
## Configuration
##

PREFIX          := ppu

TARGET		:= audiosync.elf

FLAGS		:= -std=gnu99
INCLUDES	:=
LIBS		:= -laudio -lrt -llv2 -lm

##
## Tools
##

AS		:= $(PREFIX)-as
CC		:= $(PREFIX)-gcc
CPP		:= $(PREFIX)-g++
LD		:= $(PREFIX)-g++

ASFLAGS		:=
CFLAGS		:= -Wall -pedantic -O3 $(FLAGS) -I$(PSL1GHT)/$(PREFIX)/include $(INCLUDES)
CPPFLAGS	:= $(CFLAGS)
LDFLAGS		:= -L$(PSL1GHT)/$(PREFIX)/lib $(LIBS)

##
## Files
##

RAWFILES	:= $(shell find * -name "*.raw" -print )
CFILES		:= $(shell find * -name "*.c"   -print )
CPPFILES	:= $(shell find * -name "*.cpp" -print )
SFILES		:= $(shell find * -name "*.s"   -print )

OFILES		:= ${RAWFILES:.raw=.o} ${CFILES:.c=.o} ${CPPFILES:.cpp=.o} ${SFILES:.s=.o}

##
## Rules
##

default: $(TARGET)

clean:
	rm -f $(OFILES) $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

%.o: %.raw
	@bin2s -a 64 $< | $(AS) $(ASFLAGS) -o $@
	@echo "extern const u8"  `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"_end[];" >  `(echo $< | tr . _)`.h
	@echo "extern const u8"  `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];"     >> `(echo $< | tr . _)`.h
	@echo "extern const u32" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";"  >> `(echo $< | tr . _)`.h

%.o: %.s
	$(AS) $(ASFLAGS) -o $@

%.a: $(OFILES)
	$(AR) cru $@ $(OFILES)

%.elf: $(OFILES)
	$(LD) $(OFILES) $(LDFLAGS) -o $@

%.self: %.elf
	@echo "TODO"

%.pkg: %.self
	@echo "TODO"

