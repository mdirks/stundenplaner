TEMPLATE = lib
TARGET = datamodel

SOURCES += \
    *.cpp

HEADERS += \
    *.h

OTHER_FILES += \
    persistence.xml

INCLUDEPATH += ../ /usr/include/KDE

CONFIG += qt
QT+=sql
