#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(PS3DEV)),)
$(error "Please set PS3DEV in your environment. export PS3DEV=<path>")
endif

UNAME	:=	$(shell uname -s)

ifneq (,$(findstring MINGW,$(UNAME)))
	POSTFIX	:= .exe
endif

ifneq (,$(findstring CYGWIN,$(UNAME)))
	POSTFIX	:= .exe
endif

TARGET		:= sprxlinker$(POSTFIX)
SOURCE		:= .
INCLUDE		:= .

CFLAGS		:= -O2 -Wall --std=gnu99
LDFLAGS		:= -lelf

CC		:= gcc

CFILES		:= $(foreach dir,$(SOURCE),$(wildcard $(dir)/*.c))
INCLUDES	:= $(foreach dir,$(INCLUDE),-I$(dir))

all: $(TARGET)

install: all
	@echo Installing $(TARGET)
	@[ -d $(PS3DEV)/bin ] || mkdir -p $(PS3DEV)/bin
	@install -m 755 $(TARGET) $(PS3DEV)/bin

clean:
	@echo clean ...
	@rm -rf $(TARGET)

$(TARGET): $(CFILES)
			@echo building ... $(notdir $@)
			@$(CC) $(CFLAGS) $(INCLUDES) $< -o $@ $(LDFLAGS)

