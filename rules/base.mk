OBJCOPY		:= $(PREFIX)objcopy
AR			:= $(PREFIX)ar
AS			:= $(PREFIX)gcc
CC			:= $(PREFIX)gcc
CXX			:= $(PREFIX)g++
LD			:= $(CC)
STRIP		:= $(PREFIX)strip
RAW2H		:= $(PSL1GHT)/host/bin/raw2h

DEPSOPTIONS	=	-MMD -MP -MF $(DEPSDIR)/$*.d

%.o: %.c
	@echo "[CC]  $(notdir $<)"
	@$(CC) $(DEPSOPTIONS) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.cpp
	@echo "[CXX] $(notdir $<)"
	@$(CXX) $(DEPSOPTIONS) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.S
	@echo "[CC]  $(notdir $<)"
	@$(AS) $(DEPSOPTIONS) -x assembler-with-cpp $(ASFLAGS) $(INCLUDES) -c $< -o $@

%.a:
	@echo "[AR]  $(notdir $@)"
	@$(AR) -rcs $@ $^

%.elf:
	@echo "[LD]  $(notdir $@)"
	@$(LD) $^ $(LIBPATHS) $(LIBS) $(LDFLAGS) -o $@

%.bin.h: %.bin
	@echo "[R2H] $(notdir $<)"
	@$(RAW2H) $< $(BUILDDIR)/$(notdir $<).h $(BUILDDIR)/$(notdir $<).S $(notdir $(basename $<)_bin)
	@$(AS) -x assembler-with-cpp $(ASFLAGS) -c $(BUILDDIR)/$(notdir $<).S -o $(BUILDDIR)/$(notdir $<).o

