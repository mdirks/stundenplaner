TEMPLATE = lib
TARGET = datamodel
CONFIG += staticlib
SOURCES += \
    *.cpp

HEADERS += \
    *.h

OTHER_FILES += \
    persistence.xml

INCLUDEPATH += ../ /usr/include/KDE

CONFIG += qt
QT+=sql
