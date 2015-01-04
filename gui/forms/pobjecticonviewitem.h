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

class ActiveLabel;

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
    PObjectIconViewItem(PObject *o, QListWidget *iv, QPixmap &icon);
    ~PObjectIconViewItem();
};

class PObjectIconViewItemE : public QObject, public PObjectIconViewItemBase
{
    Q_OBJECT
public:
    PObjectIconViewItemE(PObject *o, RepositoryProperty *rp, QListWidget *iv, QPixmap &icon);
    ~PObjectIconViewItemE();

    void setDisplayProperty(RepositoryProperty *p);
    void showFull(bool full);

public slots:
     void editRequested();

private:
    QWidget *widget;
    QLabel *label1a;
    ActiveLabel *label1b;
    TextPropertyViewer *label2;



};

class ActiveLabel : public QLabel
{
Q_OBJECT
public:
    ActiveLabel(QString text, QWidget *parent=0) : QLabel(text,parent){}

protected:
    void mouseDoubleClickEvent( QMouseEvent * e );

signals:
    void clicked();
};

#endif
