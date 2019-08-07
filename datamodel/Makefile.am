BUILT_SOURCES = mapping

mapping: persistence.xml
	 ../mapping/mappinggenerator $(top_srcdir)/src/datamodel/persistence.xml .. $(top_srcdir)/src/datamodel; touch mapping 


INCLUDES = -I$(top_srcdir)/src $(all_includes)
METASOURCES = AUTO
libdatamodel_la_LDFLAGS = $(all_libraries)
lib_LTLIBRARIES = libdatamodel.la
libdatamodel_la_SOURCES = datamodelobjectfactory.cpp datamodelobjectfactory.h \
	datamodelrepository.cpp datamodelrepository.h fehlzeit.cpp fehlzeitmapper.cpp fehlzeitmapper.h \
	fehlzeitmeldung.cpp fehlzeitmeldungmapper.cpp fehlzeitmeldungmapper.h ferien.cpp \
	ferienmapper.cpp ferienmapper.h ferientag.cpp ferientagmapper.cpp ferientagmapper.h \
	klasse.cpp klasse.h klassemapper.cpp klassemapper.h klausur.cpp klausurmapper.cpp \
	krankmeldung.cpp krankmeldungmapper.cpp krankmeldungmapper.h krusbucheintrag.cpp \
	krusbucheintrag.h krusbucheintragmapper.cpp krusbucheintragmapper.h kursbuch.cpp \
	kursbuch.h kursbuchmapper.cpp kursbuchmapper.h lernkarte.cpp lernkartemapper.cpp \
	lernkartensatz.cpp lernkartensatzmapper.cpp material.cpp material.h materialmapper.cpp \
	materialmapper.h meldung.cpp meldungmapper.cpp meldungmapper.h note.cpp note.h \
	notemapper.cpp notemapper.h notiz.cpp notiz.h notizholder.cpp notizholder.h \
	notizholdermapper.cpp notizholdermapper.h notizmapper.cpp notizmapper.h opo.cpp opo.h \
	opomapper.cpp opomapper.h persistence.xml platz.cpp platz.h platzmapper.cpp \
	platzmapper.h reihe.cpp reihe.h reihemapper.cpp reihemapper.h schueler.cpp schueler.h \
	schuelermapper.cpp schuelermapper.h schuljahr.cpp schuljahrmapper.cpp schuljahrmapper.h \
	schultag.cpp schultag.h schultagmapper.cpp schultagmapper.h schulwoche.cpp \
	sitzplan.cpp sitzplan.h sitzplanmapper.cpp sitzplanmapper.h stunde.cpp stunde.h \
	stundemapper.cpp stundemapper.h stundenbewertung.cpp stundenbewertung.h \
	stundenbewertungen.cpp stundenbewertungenmapper.cpp stundenbewertungenmapper.h \
	stundenbewertungmapper.cpp stundenbewertungmapper.h stundenplan.cpp stundenplan.h \
	stundenplaneintrag.cpp stundenplaneintrag.h stundenplaneintragmapper.cpp \
	stundenplaneintragmapper.h stundenplanmapper.cpp stundenplanmapper.h stundenplantemplate.cpp \
	stundenplantemplate.h stundenplantemplate_impl.h stundenplantemplateeintrag.cpp \
	stundenplantemplateeintrag.h stundenplantemplateeintrag_impl.h stundenplantemplateeintragmapper.cpp \
	stundenplantemplateeintragmapper.h stundenplantemplatemapper.cpp stundenplantemplatemapper.h tag.cpp tag.h \
	tagmapper.cpp tagmapper.h teilleistung.cpp teilleistungberechnet.cpp \
	teilleistungberechnet.h teilleistungberechnetmapper.cpp teilleistungberechnetmapper.h \
	teilleistungmapper.cpp teilleistungmapper.h thema.cpp thema.h themamapper.cpp themamapper.h \
	tutorium.cpp tutoriummapper.cpp tutoriummapper.h unterrichtsthema.cpp \
	unterrichtsthema.h unterrichtsthemamapper.cpp unterrichtsthemamapper.h ziel.cpp ziel.h
noinst_HEADERS = fehlzeit.h fehlzeitmeldung.h ferien.h ferientag.h klausur.h \
	krankmeldung.h lernkarte.h lernkartensatz.h meldung.h schuljahr.h schulwoche.h \
	stundenbewertung.h stundenbewertungen.h teilleistung.h teilleistungberechnet.h tutorium.h
