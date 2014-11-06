SOURCES += \
    *.cpp

HEADERS += \
    *.h

OTHER_FILES += \
    stundenplanerui.rc

INCLUDEPATH += .. \
INCLUDEPATH += /usr/include/KDE
INCLUDEPATH += gui

LIBS     += -lkdeui
LIBS     += -lkdecore
LIBS     += -lkio
LIBS     += -lkparts
LIBS     += -lpoppler-qt4
LIBS     += -lpdfview
release {
LIBS     += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/gui -lgui
LIBS     += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/orm -lorm
LIBS     += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/datamodel -ldatamodel
LIBS     += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/services -lservices
}

debug {
LIBS     += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/gui -lgui
LIBS     += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/orm -lorm
LIBS     += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/datamodel -ldatamodel
LIBS     += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/services -lservices
}
LIBS     += -L/usr/lib

#LIBS     +=  -lgui -lorm -ldatamodel -lservices
#LIBS     += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/orm -lorm
#LIBS     += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/datamodel -ldatamodel
#LIBS     += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/services -lservices


CONFIG += qt
QT+=sql

#CONFIG( debug,debug|release){
#     QMAKE_LIBDIR += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/gui
#     QMAKE_LIBDIR += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/orm
#     QMAKE_LIBDIR += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/datamodel
#     QMAKE_LIBDIR += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/services
#} else {
#     QMAKE_LIBDIR += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/gui
#     QMAKE_LIBDIR += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/orm
#     QMAKE_LIBDIR += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/datamodel
#     QMAKE_LIBDIR += -L/home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/services
#}
