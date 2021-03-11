TEMPLATE = lib
TARGET = datamodel
CONFIG += staticlib
CONFIG += c++11
SOURCES += \
    *.cpp \
    bookmark.cpp \
    bspsatz.cpp \
    kopie.cpp \
    lektueresatz.cpp \
    notizsatz.cpp \
    materialsatz.cpp \
    tweet.cpp \
    vokabel.cpp \
    vokabelliste.cpp

HEADERS += \
    *.h \
    bookmark.h \
    bspsatz.h \
    kopie.h \
    lektueresatz.h \
    notizsatz.h \
    materialsatz.h \
    tweet.h \
    vokabel.h \
    vokabelliste.h

OTHER_FILES += \
    persistence.xml

INCLUDEPATH += ../ /usr/include/KDE

CONFIG += qt
QT+=sql widgets

DISTFILES += \
    persistence-new.xml
