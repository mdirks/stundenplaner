INCLUDES = -I$(top_srcdir)/src $(all_includes)
METASOURCES = AUTO
lib_LTLIBRARIES = libpersistence.la
libpersistence_la_LDFLAGS = $(all_libraries)
libpersistence_la_SOURCES = abstractpersistenceclass.cpp \
	abstractpersistenceclass.h database.cpp database.h databaseimpl_q.cpp databaseimpl_q.h \
	pcollection.cpp pcollection.h pcollectionpersistence.cpp pcollectionpersistence.h \
	persistenceclass.cpp persistenceclass.h pobject.cpp pobject.h variant.cpp variant.h
