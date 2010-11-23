TARGET		:= vpcomp
SOURCE		:= .
INCLUDE		:= .

CFLAGS		:= -O2 -Wall --std=gnu99
LDFLAGS		:= -lstdc++

CC			:= gcc

CFILES		:= $(foreach dir,$(SOURCE),$(wildcard $(dir)/*.cpp))

CFLAGS		+= $(foreach dir,$(INCLUDE),-I$(dir))

all: $(TARGET)

clean:
	rm -rf $(TARGET)

$(TARGET): $(CFILES)
	$(CC) $< $(LDFLAGS) $(CFLAGS) -o $@
