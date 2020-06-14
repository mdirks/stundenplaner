TEMPLATE = app
TARGET = stundenplaner

SOURCES += \
    *.cpp

HEADERS += \
    *.h

OTHER_FILES += \
    stundenplanerui.rc

CONFIG += qt
CONFIG += c++11
unix {
        CONFIG += link_pkgconfig
        PKGCONFIG += poppler-qt5
}
QT+=sql xml widgets printsupport network


INCLUDEPATH += .. \
INCLUDEPATH += /usr/include/KDE
INCLUDEPATH += gui


LIBS     += -lpoppler-qt5

LIBS     +=  -lgui -lorm -ldatamodel -lservices -lklfbackend -lormgui

message($$OUT_PWD)

QMAKE_LIBDIR += -L/usr/lib
QMAKE_LIBDIR += $$OUT_PWD/../gui
QMAKE_LIBDIR += $$OUT_PWD/../orm
QMAKE_LIBDIR += $$OUT_PWD/../datamodel
QMAKE_LIBDIR += $$OUT_PWD/../services
QMAKE_LIBDIR += $$OUT_PWD/../klfbackend
QMAKE_LIBDIR += $$OUT_PWD/../orm/ormgui



message($$LIBS)

stundenplaner.path=/home/mopp/bin
stundenplaner.files=$$OUT_PWD/stundenplaner
stundenplaner.extra = echo "installing"
INSTALLS += stundenplaner

#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target


