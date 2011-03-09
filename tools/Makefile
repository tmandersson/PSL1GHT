TARGETS	:=	geohot ps3load raw2h sprxlinker cgcomp PS3Py

all:
	@for dir in $(TARGETS); do \
		echo; \
		echo Entering Directory $$dir; \
		$(MAKE) --no-print-directory -C $$dir; \
		echo Leaving Directory $$dir; \
	done

clean:
	@for dir in $(TARGETS); do \
		echo Cleaning $$dir; \
		$(MAKE) --no-print-directory -C $$dir clean; \
	done

install:
	@mkdir -p $(PSL1GHT)/host/bin
	@for dir in $(TARGETS); do \
		echo Installing $$dir; \
		$(MAKE) --no-print-directory -C $$dir install; \
	done

.PHONY: all install clean
