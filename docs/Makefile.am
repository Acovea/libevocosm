EXTRA_DIST = libevocosm.doxygen libevocosm_foot.html libevocosm_head.html

CLEANFILES = html/*

htmldir = $(datadir)/doc/$(GENERIC_LIBRARY_NAME)/api

html_DATA = html/index.html

html/index.html: libevocosm.doxygen
	doxygen libevocosm.doxygen

install-data-hook:
	cp -dR html/* $(DESTDIR)$(htmldir)
