#ifndef MODEMAPS_H
#define MODEMAPS_H

#include "gui/guimode.h"
#include "gui/data/themamap.h"
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
    void loadContentsList();


private:
    Ui::ModeMapsCentral *ui;
    QWidget *displayWidget;
    //QToolBar *toolBar;
    ThemaMap *m_map;
};


#endif // MODEMAPS_H
