#ifndef MODEPLANUNG_H
#define MODEPLANUNG_H

#include "gui/guimode.h"
#include "gui/base/doublepane.h"


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
};

#endif // MODEPLANUNG_H
