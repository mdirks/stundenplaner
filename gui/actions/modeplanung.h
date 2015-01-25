#ifndef MODEPLANUNG_H
#define MODEPLANUNG_H

#include "gui/guimode.h"
#include "gui/base/doublepane.h"
#include "gui/forms/reiheplaner.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"

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
    list<RepositoryProperty*> *sePropertyList;
};

#endif // MODEPLANUNG_H
