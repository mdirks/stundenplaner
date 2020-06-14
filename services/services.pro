TEMPLATE = lib
TARGET = services
CONFIG += staticlib
CONFIG += c++11

#SOURCES += \
#    *.cpp \
#   docstore/annexdocstore.cpp \
#    docstore/docstore.cpp \
#    filter/collectionpropertyfilter.cpp

SOURCES += $$system(ls *.cpp) $$system(ls reports/*.cpp) $$system(ls filter/*.cpp) $$system(ls xml-export/*.cpp) \
    mail/smtp.cpp
SOURCES += $$system(ls utils/*.cpp) $$system(ls actions/*.cpp) $$system(ls docstore/*.cpp) $$system(ls mail/*.cpp)

#HEADERS += \
#    *.h \
#    docstore/annexdocstore.h \
#    docstore/docstore.h \
#    filter/collectionpropertyfilter.h

HEADERS += $$system(ls *.h)  $$system(ls reports/*.h) $$system(ls filter/*.h) $$system(ls xml-export/*.h) \
    mail/smtp.h
HEADERS += $$system(ls utils/*.h) $$system(ls actions/*.h) $$system(ls docstore/*.h) $$system(ls mail/*.h)

message(The projects sources: $$SOURCES)



DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += ..
INCLUDEPATH += reports filter
#INCLUDEPATH += /usr/include/poppler/qt5
#INCLUDEPATH += /usr/include/KDE

CONFIG += qt

unix: {
        CONFIG += link_pkgconfig
        PKGCONFIG += poppler-qt5
}
QT+=sql xml widgets
#QT+=KIOCore KIOFileWidgets KIOWidgets KNTLM
#QT+=KIconThemes
#QT+=KParts
