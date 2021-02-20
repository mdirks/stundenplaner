TEMPLATE = lib
TARGET = datamodel
CONFIG += staticlib
CONFIG += c++11
SOURCES += \
    *.cpp \
    bookmark.cpp \
    kopie.cpp \
    lektueresatz.cpp \
    notizsatz.cpp \
    materialsatz.cpp \
    tweet.cpp

HEADERS += \
    *.h \
    bookmark.h \
    kopie.h \
    lektueresatz.h \
    notizsatz.h \
    materialsatz.h \
    tweet.h

OTHER_FILES += \
    persistence.xml

INCLUDEPATH += ../ /usr/include/KDE

CONFIG += qt
QT+=sql widgets
