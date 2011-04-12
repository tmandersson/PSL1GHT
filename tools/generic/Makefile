#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPS3)),)
$(error "Please set DEVKITPS3 in your environment. export DEVKITPS3=<path>")
endif

CC	:=	gcc

CFLAGS	:=	-Wall -Wno-char-subscripts -O2 -s

ifneq (,$(findstring MINGW,$(shell uname -s)))
	exeext		:= .exe
endif

ifneq (,$(findstring CYGWIN,$(UNAME)))
	exeext		:= .exe
endif

ifneq (,$(findstring Darwin,$(shell uname -s)))
	SDK	:=	/Developer/SDKs/MacOSX10.4u.sdk
	CFLAGS += -mmacosx-version-min=10.4 -isysroot $(SDK) -Wl,-syslibroot,$(SDK) -arch i386 -arch ppc
endif

TARGETS	:=	$(patsubst %.c,%$(exeext),$(wildcard *.c)) \
		$(patsubst %.cpp,%$(exeext),$(wildcard *.cpp))


all:	$(TARGETS)

clean:
	@echo clean ...
	@rm -f $(TARGETS)

%$(exeext)	:: %.c
	@$(CC) $< -o $@ $(CFLAGS)

%$(exeext)	:: %.cpp
	@$(CXX) $< -o $@ $(CFLAGS)

install: all
	@echo Installing $(TARGETS)
	@[ -d $(DEVKITPS3)/bin ] || mkdir -p $(DEVKITPS3)/bin
	@install -m 755 $(TARGETS) $(DEVKITPS3)/bin