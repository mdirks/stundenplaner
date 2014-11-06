HEADERS += \
    mapping/mappingconverter.h \
    mapping/mappingcontroler.h \
    mapping/mappedobject.h \
    mapping/association.h \
    mapping/abstractmapper.h \
    mapping/abstractassociation.h \
    mapping/reference.h \
    mapping/property.h \
    mapping/objectfactoryimpl.h \
    mapping/objectfactory.h \
    mapping/mappingeventlistener.h

SOURCES += \
    mapping/mappingconverter.cpp \
    mapping/mappingcontroler.cpp \
    mapping/mappedobject.cpp \
    mapping/association.cpp \
    mapping/abstractmapper.cpp \
    mapping/abstractassociation.cpp \
    mapping/reference.cpp \
    mapping/property.cpp \
    mapping/objectfactoryimpl.cpp \
    mapping/objectfactory.cpp \
    mapping/mappingeventlistener.cpp

CONFIG += qt
QT+=sql
