TARGET		:= sprxlinker
SOURCE		:= .
INCLUDE		:= .

CFLAGS		:= -O2 -Wall --std=gnu99
LDFLAGS		:= -lelf

CC			:= gcc

CFILES		:= $(foreach dir,$(SOURCE),$(wildcard $(dir)/*.c))

CFLAGS		+= $(foreach dir,$(INCLUDE),-I$(dir))

all: $(TARGET)

clean:
	rm -rf $(TARGET)

install: all
	@cp -fv $(TARGET) $(PSL1GHT)/host/bin/

$(TARGET): $(CFILES)
	$(CC) $< $(LDFLAGS) $(CFLAGS) -o $@
