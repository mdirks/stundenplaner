TEMPLATE = lib
TARGET = orm
DEPENDPATH += .
CONFIG += staticlib
CONFIG += c++11

#include(persistence/persistence.pro)
#include(mapping/mapping.pro)
##include(repository/repository.pro)
#include(transactions/transactions.pro)
#include(generator/generator.pro)
SOURCES += $$system(ls persistence/*.cpp) $$system(ls mapping/*.cpp) $$system(ls repository/*.cpp) $$system(ls transactions/*.cpp) \
    mapping/mappingeventsource.cpp \
    mapping/mtree.cpp \
    mapping/mtreemapper.cpp \
    persistence/sqlite.cpp
HEADERS += $$system(ls persistence/*.h) $$system(ls mapping/*.h) $$system(ls repository/*.h) $$system(ls transactions/*.h) \
    mapping/mappingeventsource.h \
    mapping/mtree.h \
    mapping/mtreemapper.h \
    persistence/sqlite.h



INCLUDEPATH += . .. \
    /usr/include/KDE

CONFIG += qt
QT+=sql widgets
