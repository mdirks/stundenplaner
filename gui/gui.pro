TEMPLATE = lib
TARGET = gui

CONFIG += qt
CONFIG += staticlib


SOURCES += \
    *.cpp \
    actions/modenotes.cpp \
    forms/testform.cpp \
    dialogs/collectionselectiondialog.cpp

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
    dialogs/collectionselectiondialog.h

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
INCLUDEPATH += /usr/include/KDE actions base data dialogs dragandrop forms mapviews
INCLUDEPATH += /usr/include/poppler/qt4

QT+=sql xml

OTHER_FILES += \
    actions/persistence.xml\
    stundenplanerui.rc

FORMS += \
    forms/testform.ui \
    actions/modematerial.ui
