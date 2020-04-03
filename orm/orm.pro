TEMPLATE = lib
TARGET = orm
DEPENDPATH += .
CONFIG += staticlib
CONFIG += c++11

include(persistence/persistence.pro)
include(mapping/mapping.pro)
include(repository/repository.pro)
include(transactions/transactions.pro)

INCLUDEPATH += . .. \
    /usr/include/KDE

CONFIG += qt
QT+=sql widgets
