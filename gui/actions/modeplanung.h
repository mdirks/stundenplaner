#ifndef MODEPLANUNG_H
#define MODEPLANUNG_H

#include "gui/guimode.h"
#include "gui/base/doublepane.h"
#include "gui/forms/reiheplaner.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"

#include <QSplitter>
#include <QToolBar>
#include <QStackedWidget>

class ModePlanung : public GuiMode
{
Q_OBJECT
public:
    ModePlanung();
    void setupMode();
    void activateObject(PObject *o);
    void showForm(QWidget *w);
    void tearDownMode();

    static ModePlanung* getInstance();

public slots:
    void showReihePlaner();


private:
    static ModePlanung *instance;
    DoublePane *dp;
    QSplitter *spl;//, *spl_right;
    QStackedWidget *stack;
    QToolBar *toolBar;
    ReiheBrowser *browser;
    list<RepositoryProperty*> *sePropertyList;
};

#endif // MODEPLANUNG_H
