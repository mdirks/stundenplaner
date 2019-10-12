#ifndef MODENOTES_H
#define MODENOTES_H

#include "gui/guimode.h"
#include "gui/forms/pobjectlistprovider.h"
#include "gui/forms/pobjecticonview.h"
#include "gui/forms/textpropertyviewer.h"
#include "gui/forms/textpropertyviewer2.h"

#include <QWidget>
#include <QToolBar>
#include <QSplitter>

class ModeNotes : public GuiMode
{
Q_OBJECT

public:
    ModeNotes();
    void setupMode();
    void tearDownMode();

public slots:
    void changeSatz();
    void changeSelectorSatz();
    void changeNotiz();
    void showSelector();

private:
    QSplitter *splitter;
    QWidget *displayWidget, *sdisplayWidget;
    QStackedWidget *editorWidget;
    PObjectIconView *viewSaetze, *viewNotizen;
    PObjectIconView *sviewSaetze, *sviewNotizen;
    //TextPropertyViewer *viewer;
    TextPropertyViewer2 *viewer;
    PObjectListProvider *prov,*sprov;
    QToolBar *toolBar;
};

#endif // MODENOTES_H
