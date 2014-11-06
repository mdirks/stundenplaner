TEMPLATE = lib
TARGET = services

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
INCLUDEPATH += /usr/include/poppler/qt4
INCLUDEPATH += /usr/include/KDE

CONFIG += qt
QT+=sql xml
