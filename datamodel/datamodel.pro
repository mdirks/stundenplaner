TEMPLATE = lib
TARGET = datamodel
CONFIG += staticlib
SOURCES += \
    *.cpp \
    notizsatz.cpp \
    materialsatz.cpp

HEADERS += \
    *.h \
    notizsatz.h \
    materialsatz.h

OTHER_FILES += \
    persistence.xml

INCLUDEPATH += ../ /usr/include/KDE

CONFIG += qt
QT+=sql
