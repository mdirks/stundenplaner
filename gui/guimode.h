#ifndef GUIMODE_H
#define GUIMODE_H

#include "orm/persistence/pobject.h"
#include <QListWidgetItem>
#include <QAction>
#include <QDebug>

class GuiMode : public QAction
{
Q_OBJECT

public:
    GuiMode(QString title);

    virtual void setupMode(){qDebug() << "GuiMode: calling empty setupMode()";};

    virtual void tearDownMode(){};
    virtual void close(){};
    virtual void activateObject(PObject *o){};
    virtual void showForm(QWidget *w){};
    virtual QList<QAction*>* getModeActions(){}


public slots:
    void doSetupMode();
    //void nocheiner();
};

#endif // GUIMODE_H
