#ifndef GUIMODE_H
#define GUIMODE_H

#include "orm/persistence/pobject.h"

#include <QListWidgetItem>
#include <QAction>
#include <QToolBar>
#include <QDebug>


class GuiMode : public QAction
{
Q_OBJECT

public:
    GuiMode(QString title);

    virtual void setupMode()=0;

    virtual void tearDownMode(){}
    virtual void close();  //called when GUI is closing e.g. for shutdown
    virtual void load(){}
    virtual void reload(); //called when GUI is reloaded e.g. for database change
    virtual void activate();   //called by the GuiRep when activated
    virtual void deactivate();  //called by the GuiRep whenever other mode gets activated.
    virtual void activateObject(PObject *o){}
    virtual void showForm(QWidget *w); //when active called by the GuiRep relating request from someohne
    virtual QList<QAction*>* getModeActions(){return 0;} //not used at the moment
    virtual void setModeWidget(QWidget *w);


public slots:
    void doSetupMode();  //called when mode (=action) is triggered, calls GuiRep::setActiveMode

private:
    QWidget *modeWidget;
    QWidget *emptyWidget;
    bool setupDone;

protected:
    QToolBar *modeToolBar;

    //void nocheiner();
};

#endif // GUIMODE_H
