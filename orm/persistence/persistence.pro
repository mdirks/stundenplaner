HEADERS += \
    persistence/persistenceclass.h \
    persistence/pcollectionpersistence.h \
    persistence/pcollection.h \
    persistence/databaseimpl_q.h \
    persistence/database.h \
    persistence/abstractpersistenceclass.h \
    persistence/variant.h \
    persistence/pobject.h \
    persistence/ptree.h \
    persistence/ptreepersistence.h

SOURCES += \
    persistence/pobject.cpp \
    persistence/persistenceclass.cpp \
    persistence/pcollectionpersistence.cpp \
    persistence/pcollection.cpp \
    persistence/databaseimpl_q.cpp \
    persistence/database.cpp \
    persistence/abstractpersistenceclass.cpp \
    persistence/variant.cpp \
    persistence/ptree.cpp \
    persistence/ptreepersistence.cpp

INCLUDEPATH += /usr/include/KDE
CONFIG += qt
QT+=sql
