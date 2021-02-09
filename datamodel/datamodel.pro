TEMPLATE = lib
TARGET = datamodel
CONFIG += staticlib
CONFIG += c++11
SOURCES += \
    *.cpp \
    kopie.cpp \
    lektueresatz.cpp \
    notizsatz.cpp \
    materialsatz.cpp

HEADERS += \
    *.h \
    kopie.h \
    lektueresatz.h \
    notizsatz.h \
    materialsatz.h

OTHER_FILES += \
    persistence.xml

INCLUDEPATH += ../ /usr/include/KDE

CONFIG += qt
QT+=sql widgets
