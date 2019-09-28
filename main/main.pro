TARGET = stundenplaner

SOURCES += \
    *.cpp

HEADERS += \
    *.h

OTHER_FILES += \
    stundenplanerui.rc

CONFIG += qt
unix {
        CONFIG += link_pkgconfig
        PKGCONFIG += poppler-qt5
}
QT+=sql xml widgets printsupport
#QT+=KIconThemes
#QT+=KXmlGui
#QT+=KIOFileWidgets KIOWidgets KNTLM
#QT+=KParts

INCLUDEPATH += .. \
INCLUDEPATH += /usr/include/KDE
INCLUDEPATH += gui

#LIBS     += -lkdeui
#LIBS     += -lkdecore
#LIBS     += -lkio
#LIBS     += -lkparts
LIBS     += -lpoppler-qt5
#LIBS     += -lpdfview

LIBS     +=  -lgui -lorm -ldatamodel -lservices

message($$OUT_PWD)

QMAKE_LIBDIR += -L/usr/lib
QMAKE_LIBDIR += $$OUT_PWD/../gui
QMAKE_LIBDIR += $$OUT_PWD/../orm
QMAKE_LIBDIR += $$OUT_PWD/../datamodel
QMAKE_LIBDIR += $$OUT_PWD/../services
#CONFIG( debug,debug|release){
#     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/gui
#     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/orm
#     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/datamodel
#     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Debug/services
#} else {
#     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/gui
#     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/orm
#     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/datamodel
#     QMAKE_LIBDIR += /home/mopp/dev/stundenplaner-build-desktop-Qt_4_8_1_in_PATH__System__Release/services
#}


stundenplaner.path=/usr/bin
stundenplaner.files=$$OUT_PWD/stundenplaner
unix:stundenplaner.extra = echo "installing"
INSTALLS += stundenplaner

