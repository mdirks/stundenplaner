BUILT_SOURCES = mapping

mapping: persistence.xml
	 ../mapping/mappinggenerator $(top_srcdir)/src/services/persistence.xml .. $(top_srcdir)/src/services; touch mapping 

INCLUDES = -I$(top_srcdir)/src $(all_includes)
METASOURCES = AUTO
libservices_la_LDFLAGS = $(all_libraries)
lib_LTLIBRARIES = libservices.la
libservices_la_SOURCES = persistence.xml skalender.cpp skalendermapper.cpp \
	skalendermapper.h sstundenplan.cpp sstundenplan.h sstundenplanmapper.cpp \
	sstundenplanmapper.h stundenplan.xml
noinst_HEADERS = skalender.h
