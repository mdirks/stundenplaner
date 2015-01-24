TARGET = stundenplaner

SOURCES += \
    *.cpp

HEADERS += \
    *.h

OTHER_FILES += \
    stundenplanerui.rc

CONFIG += qt
QT+=sql xml


INCLUDEPATH += .. \
INCLUDEPATH += /usr/include/KDE
INCLUDEPATH += gui

LIBS     += -lkdeui
LIBS     += -lkdecore
LIBS     += -lkio
LIBS     += -lkparts
LIBS     += -lpoppler-qt4
LIBS     += -lpdfview

LIBS     +=  -lgui -lorm -ldatamodel -lservices


QMAKE_LIBDIR += -L/usr/lib
CONFIG( debug,debug|release){
     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/gui
     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/orm
     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/datamodel
     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/services
} else {
     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/gui
     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/orm
     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/datamodel
     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/services
}


stundenplaner.path=/usr/bin
stundenplaner.files=/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/main/stundenplaner
unix:stundenplaner.extra = echo "installing"
INSTALLS += stundenplaner

