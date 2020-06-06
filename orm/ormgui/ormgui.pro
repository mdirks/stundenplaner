TEMPLATE = lib
TARGET = ormgui
DEPENDPATH += .
CONFIG += staticlib
CONFIG += qt c++11
QT+=sql widgets


#include(persistence/persistence.pro)
#include(mapping/mapping.pro)
##include(repository/repository.pro)
#include(transactions/transactions.pro)
#include(generator/generator.pro)
SOURCES += $$system(ls *.cpp)
HEADERS += $$system(ls *.h)



INCLUDEPATH += . .. \
    /usr/include/KDE


INSTALLS    += target

FORMS += \
    ormdialog.ui


