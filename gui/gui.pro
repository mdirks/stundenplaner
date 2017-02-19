TEMPLATE = lib
TARGET = gui

CONFIG += qt
CONFIG += staticlib

unix {
        CONFIG += link_pkgconfig
        PKGCONFIG += poppler-qt5
}

SOURCES += \
    *.cpp \
    actions/modenotes.cpp \
    forms/testform.cpp \
    dialogs/collectionselectiondialog.cpp \
    forms/pobjectform.cpp \
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
    forms/pdfview/synctex/synctex_parser_utils.c

SOURCES += $$system(ls mapviews/*.cpp) $$system(ls data/*.cpp) $$system(ls draganddrop/*.cpp)
SOURCES += $$system(ls actions/*.cpp) $$system(ls base/*.cpp) $$system(ls dialogs/*.cpp)
SOURCES += $$system(ls forms/*.cpp)


HEADERS += \
    *.h \
    forms/textviewer.h \
    data/reihemap.h \
    actions/modematerail.h \
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
    forms/pdfview/synctex/synctex_parser_utils.h

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
INCLUDEPATH += /usr/include/KF5
#INCLUDEPATH += /usr/include/KF5/KConfigCore
INCLUDEPATH += actions base data dialogs dragandrop forms mapviews
#INCLUDEPATH += /usr/include/poppler/qt5

unix {
        CONFIG += link_pkgconfig
        PKGCONFIG += poppler-qt5
}

QT+=sql xml widgets printsupport
QT+=KXmlGui
QT+=KIconThemes
QT+=KParts

OTHER_FILES += \
    actions/persistence.xml\
    stundenplanerui.rc

FORMS += \
    forms/testform.ui \
    actions/modematerial.ui \
    forms/reihebrowser.ui \
    actions/modeplanung.ui \
    forms/urleditor.ui \
    forms/formarea.ui
