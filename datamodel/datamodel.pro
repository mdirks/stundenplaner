TEMPLATE = lib
TARGET = datamodel
CONFIG += staticlib
SOURCES += \
    *.cpp \
    notizsatz.cpp

HEADERS += \
    *.h \
    notizsatz.h

OTHER_FILES += \
    persistence.xml

INCLUDEPATH += ../ /usr/include/KDE

CONFIG += qt
QT+=sql
