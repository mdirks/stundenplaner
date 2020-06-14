QT       += core gui
QT+= sql xml widgets printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    appmainwindow.cpp

HEADERS += \
    appmainwindow.h

FORMS += \
    appmainwindow.ui

INCLUDEPATH += ../ ./ orm gui /usr/include/poppler/qt5/
LIBS     +=  -lgui -lorm -ldatamodel -lservices -lklfbackend -lormgui -lpoppler-qt5

#        CONFIG += link_pkgconfig
#        PKGCONFIG += poppler-qt5

QMAKE_LIBDIR += -L/usr/lib
QMAKE_LIBDIR += $$OUT_PWD/../gui
QMAKE_LIBDIR += $$OUT_PWD/../orm
QMAKE_LIBDIR += $$OUT_PWD/../datamodel
QMAKE_LIBDIR += $$OUT_PWD/../services
QMAKE_LIBDIR += $$OUT_PWD/../klfbackend
QMAKE_LIBDIR += $$OUT_PWD/../orm/ormgui



# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
