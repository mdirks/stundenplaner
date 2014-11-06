INCLUDES = -I$(top_srcdir)/src $(all_includes)
METASOURCES = AUTO
lib_LIBRARIES = libmapping.a
libmapping_a_SOURCES = abstractassociation.cpp abstractmapper.cpp \
	association.cpp mappedobject.cpp mappingcontroler.cpp mappingconverter.cpp \
	mappingeventlistener.cpp mappingeventlistener.h objectfactory.cpp objectfactoryimpl.cpp \
	property.cpp reference.cpp
noinst_HEADERS = abstractassociation.h abstractmapper.h association.h \
	mappedobject.h mappingcontroler.h mappingconverter.h mappinggenerator.h \
	objectfactory.h objectfactoryimpl.h property.h reference.h
mappinggenerator_LDFLAGS = $(all_libraries)
bin_PROGRAMS = mappinggenerator
mappinggenerator_LDADD = $(LIB_QT)
mappinggenerator_SOURCES = mappinggenerator.cpp
