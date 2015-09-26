<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
INCLUDES = -I$(top_srcdir) \
	-DEVOCOSM_VERSION=\"$(VERSION)\"

h_sources = evocommon.h evocosm.h evoreal.h fsm.h fsm_tools.h \
		fuzzy_machine.h landscape.h migrator.h mutator.h \
		organism.h reporter.h reproducer.h roulette.h \
		scaler.h selector.h simple_fsm.h

cpp_sources = evocommon.cpp evoreal.cpp roulette.cpp
=======
ACLOCAL_AMFLAGS = -I m4

INCLUDES = -I$(top_srcdir) -DEVOCOSM_VERSION=\"$(VERSION)\"

h_sources = evocommon.h evocosm.h \
		evoreal.h roulette.h validator.h stats.h \
		state_machine.h machine_tools.h simple_machine.h fuzzy_machine.h \
		organism.h landscape.h \
		mutator.h scaler.h selector.h reproducer.h \
		analyzer.h listener.h \
		function_optimizer.h

cpp_sources = evocommon.cpp evoreal.cpp roulette.cpp function_optimizer.cpp
>>>>>>> version 4.0.2

lib_LTLIBRARIES = libevocosm.la

libevocosm_la_SOURCES = $(h_sources) $(cpp_sources)
libevocosm_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

DEFS=-I. -I$(srcdir)
