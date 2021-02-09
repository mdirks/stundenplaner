#ifndef MODEMAPS_H
#define MODEMAPS_H

#include "gui/guimode.h"

namespace Ui{
 class ModeMapsCentral;
};

class ModeMaps : public GuiMode
{
Q_OBJECT

public:
    ModeMaps();
    ~ModeMaps();

    void setupMode();
    void tearDownMode();
    void activateObject(PObject *o);
    void showForm(QWidget *w);
    QList<QAction*>* getModeActions();

public slots:
    void activateNewMap();

private:
    Ui::ModeMapsCentral *ui;
    QWidget *displayWidget;
    //QToolBar *toolBar;
};


#endif // MODEMAPS_H
