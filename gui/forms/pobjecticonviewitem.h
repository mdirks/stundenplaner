//
// C++ Interface: pobjecticonviewitem
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef POBJECTICONVIEWITEM_H
#define POBJECTICONVIEWITEM_H

#include <QListWidgetItem>
#include <QLabel>
#include "orm/persistence/pobject.h"
#include "textpropertyviewer.h"
#include "orm/repository/repositoryproperty.h"
#include "gui/forms/stringeditor.h"

#include <QToolButton>
#include <list>

class ActiveLabel;
class PropertyButton;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/


class PObjectIconViewItemBase : public QListWidgetItem
{
public:
    PObjectIconViewItemBase(PObject *o, QListWidget *iv);
    ~PObjectIconViewItemBase();
    PObject* getObject();
    virtual void showFull(bool full){};

protected:
    QListWidget *lv;

private:
    PObject *object;

};



class PObjectIconViewItem : public PObjectIconViewItemBase
{

public:
    PObjectIconViewItem(PObject *o, QListWidget *iv, QPixmap &icon, RepositoryProperty *displayProp=0);
    ~PObjectIconViewItem();
};

class PObjectIconViewItemE : public QObject, public PObjectIconViewItemBase
{
    Q_OBJECT
public:
    PObjectIconViewItemE(PObject *o, list<RepositoryProperty*> *listRp, QListWidget *iv, QPixmap &icon);
    ~PObjectIconViewItemE();

    //void setDisplayProperty(RepositoryProperty *p);
    void showFull(bool full);

public slots:
     void editRequested();
     void setNewSize();

private:
    QWidget *widget;
    QLabel *label1a;
    ActiveLabel *label1b;
    //TextPropertyViewer *label2;
    QStackedWidget *sw;



};

class ActiveLabel : public QStackedWidget
{
Q_OBJECT
public:
    ActiveLabel(PObject *po, QWidget *parent=0);
protected:
    //void mouseDoubleClickEvent( QMouseEvent * e );
    void keyPressEvent(QKeyEvent *e);

public slots:
    void stopEdit();

signals:
    void clicked();

private:
    PObject *po;
    StringEditor *nameEditor;
    QLabel *nameLabel;
    bool editing;
};

class PropertyButton : public QToolButton
{
Q_OBJECT
public:
    PropertyButton(RepositoryProperty *rp, int i,QWidget *editor, QStackedWidget *editorStack, QWidget *parent);
public slots:
    void switchVisible();

signals:
    void resized();

private:
    int ind;
    QWidget *editor;
    QStackedWidget *editorStack;
};
#endif
