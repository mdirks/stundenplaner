#ifndef MODEPLANUNG_H
#define MODEPLANUNG_H

#include "gui/guimode.h"
#include "gui/base/doublepane.h"
#include "gui/forms/reiheplaner.h"

#include <QSplitter>

class ModePlanung : public GuiMode
{

public:
    ModePlanung();
    void setupMode();
    void activateObject(PObject *o);
    void showForm(QWidget *w);

    static ModePlanung* getInstance();

private:
    static ModePlanung *instance;
    DoublePane *dp;
    QSplitter *spl;
    ReiheBrowser *browser;
};

#endif // MODEPLANUNG_H
