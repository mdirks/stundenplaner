#ifndef MODEPLANUNG_H
#define MODEPLANUNG_H

#include "gui/guimode.h"
#include "gui/base/doublepane.h"
#include "gui/forms/reiheplaner.h"
#include "gui/forms/teilleistungeditor.h"
#include "gui/mapviews/sitzplanmapview.h"
#include "gui/forms/kalenderview.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"
#include "ui_modeplanung.h"

#include <QSplitter>
#include <QToolBar>
#include <QStackedWidget>
#include <QThread>

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
    void showLeistungen();
    void showSitzplan();

private:
    static ModePlanung *instance;
    DoublePane *dp;
    QWidget *displayWidget;
    //QSplitter *spl;//, *spl_right;
    QStackedWidget *stack;
    QToolBar *toolBar;
    ReiheBrowser *browser;
    TeilleistungEditorDialog *leistungEditor;
    list<RepositoryProperty*> *sePropertyList;
    SitzplanMapViewDialog *spmvd;
    KalenderView *kw;

private:
    Ui::ModePlanung *ui;

};

class SpReader :public QThread
{
Q_OBJECT
public:
    SpReader(KalenderView *kw){this->kw=kw;}
    void run(){
        if(kw) kw->readStundenplan();
    }

signals:
    void ready();

private:
    KalenderView *kw;
};

#endif // MODEPLANUNG_H
