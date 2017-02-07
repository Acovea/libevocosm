INCLUDES = -I$(top_srcdir) \
	-DEVOCOSM_VERSION=\"$(VERSION)\"

h_sources = evocommon.h evocosm.h evoreal.h fsm.h fsm_tools.h \
		fuzzy_machine.h landscape.h migrator.h mutator.h \
		organism.h reporter.h reproducer.h roulette.h \
		scaler.h selector.h simple_fsm.h

cpp_sources = evocommon.cpp evoreal.cpp roulette.cpp

lib_LTLIBRARIES = libevocosm.la

libevocosm_la_SOURCES = $(h_sources) $(cpp_sources)
libevocosm_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

DEFS=-I. -I$(srcdir)
