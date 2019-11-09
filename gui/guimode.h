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

    virtual void setupMode(){qDebug() << "GuiMode: calling empty setupMode()";}

    virtual void tearDownMode(){}
    virtual void close(){}
    virtual void load(){}
    virtual void reload();
    virtual void activate();
    virtual void deactivate();
    virtual void activateObject(PObject *o){}
    virtual void showForm(QWidget *w){}
    virtual QList<QAction*>* getModeActions(){}
    virtual void setModeWidget(QWidget *w);


public slots:
    void doSetupMode();

private:
    QWidget *modeWidget;
    QWidget *emptyWidget;
    bool setupDone;

protected:
    QToolBar *modeToolBar;

    //void nocheiner();
};

#endif // GUIMODE_H
