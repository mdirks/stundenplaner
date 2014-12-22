#ifndef GUIMODE_H
#define GUIMODE_H

#include "orm/persistence/pobject.h"
#include <QListWidgetItem>
#include <QAction>

class GuiMode : public QAction
{
Q_OBJECT

public:
    GuiMode(QString title);

    virtual void setupMode(){};
    virtual void tearDownMode(){};
    virtual void activateObject(PObject *o){};
    virtual void showForm(QWidget *w){};
    virtual QList<QAction*>* getModeActions(){}


public slots:
    void doSetupMode();
    //void nocheiner();
};

#endif // GUIMODE_H
