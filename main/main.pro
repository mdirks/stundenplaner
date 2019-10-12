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

LIBS     +=  -lgui -lorm -ldatamodel -lservices -lklfbackend

message($$OUT_PWD)

QMAKE_LIBDIR += -L/usr/lib
QMAKE_LIBDIR += $$OUT_PWD/../gui
QMAKE_LIBDIR += $$OUT_PWD/../orm
QMAKE_LIBDIR += $$OUT_PWD/../datamodel
QMAKE_LIBDIR += $$OUT_PWD/../services
QMAKE_LIBDIR += $$OUT_PWD/../klfbackend

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

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build-KLFBackend/ -lklfbackend
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build-KLFBackend/ -lklfbackend
#else:unix: LIBS += -L$$PWD/../../bruceoutdoors-tiny-tex-bed47a5e2a7a/build-KLFBackend/ -lKLFBackend

message($$LIBS)

stundenplaner.path=/usr/bin
stundenplaner.files=$$OUT_PWD/stundenplaner
unix:stundenplaner.extra = echo "installing"
INSTALLS += stundenplaner

