#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPro")
endif

ifeq ($(strip $(DEVKITPS3)),)
$(error "Please set DEVKITPS3 in your environment. export DEVKITPS3=<path>")
endif

include	$(DEVKITPS3)/ppu_rules

BUILD		:=	build

#---------------------------------------------------------------------------------
ifeq ($(strip $(PLATFORM)),)
#---------------------------------------------------------------------------------
export BASEDIR		:= $(CURDIR)
export DEPS			:= $(BASEDIR)/deps
export LIBS			:= $(BASEDIR)/lib

#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------

export LIBDIR		:= $(LIBS)/$(PLATFORM)
export DEPSDIR		:= $(DEPS)/$(PLATFORM)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

LIBRARY		:= $(LIBDIR)/librt

#---------------------------------------------------------------------------------
INCLUDES	:= -I$(BASEDIR) -I$(BASEDIR)/../include -I$(BASEDIR)/../include/lv2 -I$(BASEDIR)/../include/sys

CFLAGS		:= -O2 -mregnames -Wall -mcpu=cell $(MACHDEP) -DLIBRT_INTERNAL $(INCLUDES) -Wa,-mcell
ASFLAGS		:= $(MACHDEP) -mregnames -mcpu=cell -D__ASSEMBLY__ -Wa,-mcell $(INCLUDES)

#---------------------------------------------------------------------------------
VPATH :=	$(BASEDIR)

#---------------------------------------------------------------------------------
OBJS		:= \
			sbrk.o exit.o close.o lseek.o read.o open.o sleep.o write.o fstat.o \
			socket.o lock.o dirent.o mkdir.o times.o umask.o lv2errno.o heap.o \
			chmod.o rmdir.o isatty.o
			
all: ppu

#---------------------------------------------------------------------------------
ppu:
#---------------------------------------------------------------------------------
	@[ -d $(LIBS)/ppu ] || mkdir -p $(LIBS)/ppu
	@[ -d $(DEPS)/ppu ] || mkdir -p $(DEPS)/ppu
	@[ -d ppu ] || mkdir -p ppu
	@$(MAKE) PLATFORM=ppu lib -C ppu -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
install: all
#---------------------------------------------------------------------------------
	@[ -d $(DEVKITPRO)/libpsl1ght/ppu/lib ] || mkdir -p $(DEVKITPRO)/libpsl1ght/ppu/lib
	@cp -frv $(CURDIR)/lib/ppu/*.a $(DEVKITPRO)/libpsl1ght/ppu/lib

#---------------------------------------------------------------------------------
$(LIBRARY).a: $(OBJS)	
#---------------------------------------------------------------------------------

.PHONY: lib ppu install

#---------------------------------------------------------------------------------
lib: $(LIBRARY).a
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
clean:
#---------------------------------------------------------------------------------
	@echo clean ...
	@rm -rf ppu
	@rm -rf $(DEPS)
	@rm -rf $(LIBS)

-include $(DEPSDIR)/*.d
