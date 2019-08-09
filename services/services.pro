TEMPLATE = lib
TARGET = services
CONFIG += staticlib
SOURCES += \
    *.cpp

SOURCES += $$system(ls reports/*.cpp) $$system(ls filter/*.cpp) $$system(ls xml-export/*.cpp)
SOURCES += $$system(ls utils/*.cpp) $$system(ls actions/*.cpp)

HEADERS += \
    *.h

HEADERS += $$system(ls reports/*.h) $$system(ls filter/*.h) $$system(ls xml-export/*.h)
HEADERS += $$system(ls utils/*.h) $$system(ls actions/*.h)

message(The projects sources: $$SOURCES)



DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += ..
INCLUDEPATH += reports filter
INCLUDEPATH += /usr/include/poppler/qt5
INCLUDEPATH += /usr/include/KDE

CONFIG += qt

unix {
        CONFIG += link_pkgconfig
        PKGCONFIG += poppler-qt5
}
QT+=sql xml widgets
QT+=KIOCore KIOFileWidgets KIOWidgets KNTLM
QT+=KIconThemes
QT+=KParts
