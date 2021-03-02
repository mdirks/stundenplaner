TEMPLATE = lib
TARGET = gui


#include(/home/mopp/dev/qtmathjax/qtmathjax.pri)

CONFIG += qt
CONFIG += staticlib
CONFIG += c++11

unix {
        CONFIG += link_pkgconfig
        PKGCONFIG += poppler-qt5
}

SOURCES += \
    *.cpp \
    actions/actionpopup.cpp \
    actions/importtodocstoreaction.cpp \
    actions/modemaps.cpp \
    actions/modenotes.cpp \
    actions/pobjectaction.cpp \
    base/myactionlist.cpp \
    data/themamapsatz.cpp \
    dialogs/iconchooser.cpp \
    dialogs/scanner.cpp \
    forms/bildlistviewer.cpp \
    forms/collectiondisplay.cpp \
    forms/collectionpropertyviewer.cpp \
    forms/testform.cpp \
    dialogs/collectionselectiondialog.cpp \
    forms/pobjectform.cpp \
    forms/textpropertyviewer2.cpp \
    forms/tweeteditor.cpp \
    forms/urleditor.cpp \
    forms/formarea.cpp \
    actions/servicepdf.cpp \
    forms/pdfview/actionhandler.cpp \
    forms/pdfview/bookmarkshandler.cpp \
    forms/pdfview/filesettings.cpp \
    forms/pdfview/globallocale.cpp \
    forms/pdfview/pageitem.cpp \
    forms/pdfview/pdfview.cpp \
    forms/pdfview/printhandler.cpp \
    forms/pdfview/selectaction.cpp \
    forms/pdfview/selectpageaction.cpp \
    forms/pdfview/synctexhandler.cpp \
    forms/pdfview/zoomaction.cpp \
    forms/pdfview/synctex/synctex_parser.c \
    forms/pdfview/synctex/synctex_parser_utils.c \
    stundenplanermainwindow.cpp

SOURCES += $$system(ls mapviews/*.cpp) $$system(ls data/*.cpp) $$system(ls draganddrop/*.cpp)
SOURCES += $$system(ls actions/*.cpp) $$system(ls base/*.cpp) $$system(ls dialogs/*.cpp)
SOURCES += $$system(ls forms/*.cpp)


HEADERS += \
    *.h \
    actions/actionpopup.h \
    actions/importtodocstoreaction.h \
    actions/modemaps.h \
    actions/pobjectaction.h \
    base/myactionlist.h \
    data/themamapsatz.h \
    dialogs/iconchooser.h \
    dialogs/scanner.h \
    forms/bildlistviewer.h \
    forms/collectiondisplay.h \
    forms/collectionpropertyviewer.h \
    forms/textpropertyviewer2.h \
    forms/textviewer.h \
    data/reihemap.h \
    actions/modematerail.h \
    forms/tweeteditor.h \
    guiservice.h \
    draganddrop/pobjectdroptarget.h \
    actions/servicelatex.h \
    forms/pobjectdisplay.h \
    actions/modelernen.h \
    forms/pobjectlistprovider.h \
    actions/servicexml.h \
    actions/modenotes.h \
    forms/testform.h \
    dialogs/collectionselectiondialog.h \
    forms/pobjectform.h \
    forms/urleditor.h \
    forms/formarea.h \
    actions/servicepdf.h \
    forms/pdfview/actionhandler.h \
    forms/pdfview/bookmarkshandler.h \
    forms/pdfview/filesettings.h \
    forms/pdfview/globallocale.h \
    forms/pdfview/pageitem.h \
    forms/pdfview/pdfview.h \
    forms/pdfview/pdfview_p.h \
    forms/pdfview/printhandler.h \
    forms/pdfview/selectaction.h \
    forms/pdfview/selectpageaction.h \
    forms/pdfview/synctexhandler.h \
    forms/pdfview/zoomaction.h \
    forms/pdfview/synctex/synctex_parser.h \
    forms/pdfview/synctex/synctex_parser_local.h \
    forms/pdfview/synctex/synctex_parser_utils.h \
    stundenplanermainwindow.h

HEADERS += $$system(ls mapviews/*.h) $$system(ls data/*.h) $$system(ls draganddrop/*.h)
HEADERS += $$system(ls actions/*.h) $$system(ls base/*.h) $$system(ls dialogs/*.h)
HEADERS += $$system(ls forms/*.h)

message(The projects sources: $$SOURCES)

#include(mapviews/mapviews.pro)
#include(actions/actions.pro)
#include(base/base.pro)
#include(data/data.pro)
#include(dialogs/dialogs.pro)
#include(draganddrop/draganddrop.pro)
#include(forms/forms.pro)

#SUBDIRS = mapviews actions base data dialogs draganddrop forms


DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += ..
#INCLUDEPATH += /usr/include/KF5
#INCLUDEPATH += /usr/include/KF5/KConfigCore
INCLUDEPATH += actions base data dialogs dragandrop forms mapviews
#INCLUDEPATH += /usr/include/poppler/qt5

#unix {
        CONFIG += link_pkgconfig
        PKGCONFIG += poppler-qt5
#}

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build-KLFBackend/ -lklfbackend
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build-KLFBackend/ -lklfbackend
#else:unix: LIBS += -L$$PWD/../../bruceoutdoors-tiny-tex-bed47a5e2a7a/build-KLFBackend/ -lKLFBackend

#INCLUDEPATH += $$PWD/../../bruceoutdoors-tiny-tex-bed47a5e2a7a/klfbackend
message($$INCLUDEPATH)

#message($$LIBS)


QT+=sql xml widgets printsupport
#QT+=KXmlGui
#QT+=KIOFileWidgets KIOWidgets KNTLM
#QT+=KIconThemes
#QT+=KParts
#QT+=KIOCore



OTHER_FILES += \
    actions/persistence.xml\
    data/persistence.xml\
    mapviews/persistence\
    persistence.xml
    stundenplanerui.rc

FORMS += \
    actions/modemaps.ui \
    forms/collectiondisplay.ui \
    forms/testform.ui \
    actions/modematerial.ui \
    forms/reihebrowser.ui \
    actions/modeplanung.ui \
    forms/urleditor.ui \
    forms/formarea.ui

DISTFILES += \
    icons/Favorites/icons8-aktie-3-100.png \
    icons/Favorites/icons8-aktie-3-50.png \
    icons/Favorites/icons8-aktualisieren-100.png \
    icons/Favorites/icons8-aktualisieren-50.png \
    icons/Favorites/icons8-box-100.png \
    icons/Favorites/icons8-box-50.png \
    icons/Favorites/icons8-dokument-100.png \
    icons/Favorites/icons8-dokument-50.png \
    icons/Favorites/icons8-entfernen-100.png \
    icons/Favorites/icons8-entfernen-50.png \
    icons/Favorites/icons8-geprüft-100.png \
    icons/Favorites/icons8-geprüft-50.png \
    icons/Favorites/icons8-löschen-100.png \
    icons/Favorites/icons8-löschen-50.png \
    icons/Favorites/icons8-neustart-100.png \
    icons/Favorites/icons8-neustart-50.png \
    icons/Favorites/icons8-ordner-öffnen-100.png \
    icons/Favorites/icons8-ordner-öffnen-50.png \
    icons/Favorites/icons8-puzzle-100.png \
    icons/Favorites/icons8-puzzle-50.png \
    icons/Favorites/icons8-support-100.png \
    icons/Favorites/icons8-support-50.png \
    icons/Favorites/icons8-teilen-2-100.png \
    icons/Favorites/icons8-teilen-2-50.png \
    icons/Favorites/icons8-uhr-100.png \
    icons/Favorites/icons8-uhr-50.png \
    icons/Favorites/icons8-zuhause-100.png \
    icons/Favorites/icons8-zuhause-50.png
