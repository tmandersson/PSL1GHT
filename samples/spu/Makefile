TARGETS := spuchain spudma sputest sputhread

all:
	@for TARGET in $(TARGETS); do $(MAKE) -C $$TARGET bin; done
	@for TARGET in $(TARGETS); do $(MAKE) -C $$TARGET; done

clean:
	@for TARGET in $(TARGETS); do $(MAKE) -C $$TARGET clean; done
