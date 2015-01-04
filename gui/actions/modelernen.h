#ifndef MODELERNEN_H
#define MODELERNEN_H

#include "gui/guimode.h"
#include "gui/forms/pobjectdisplay.h"
#include "gui/forms/pobjectcombobox.h"
#include "gui/forms/pobjecticonview.h"

#include <QToolBar>

class ModeLernen : public GuiMode
{
Q_OBJECT
public:
    ModeLernen();

    void setupMode();
    void tearDownMode();
    void activateObject(PObject *o);
    void showForm(QWidget *w);
    QList<QAction*>* getModeActions();

public slots:
    void newListSelected(int i);
    void showKartenEditor();

private:
    QToolBar *toolBar;
    QWidget *mainWidget;
    PObjectComboBox *combo;
    PObjectDisplay *objectDisplay;
    PObjectIconView *editor;

};

#endif // MODELERNEN_H
