//
// C++ Interface: pobjectdialog
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef POBJECTDIALOG_H
#define POBJECTDIALOG_H

#include <QListWidget>
#include <QDrag>

#include <KDialog>

#include "orm/persistence/pobject.h"
#include "orm/mapping/abstractmapper.h"
#include "pobjecticonview.h"

/*
class PObjectView : public QListWidget
{
public:
    PObjectView(list<PObject*> *listPObject, QWidget *parent=0);
    ~PObjectView();

    PObject* getSelectedPObject();
    //QDrag* dragObject();

protected:

	void contentsDragEnterEvent(QDragEnterEvent *e);


};
*/

/*
class PObjectViewItem : public QListWidgetItem
{
public:
	PObjectViewItem(PObject *obj, PObjectView *parent);
	PObject* getPObject();
	
private:
	PObject *obj;
};

*/


class PObjectDialog : public KDialog
{
public:
	PObjectDialog(AbstractMapper *mapper, QWidget *parent=0L);
	PObjectDialog(list<PObject*> *list_objects, QWidget *parent=0L);
	PObject* getSelectedPObject();

	static PObject* choosePObject(AbstractMapper *mapper);
	static PObject* choosePObject(list<PObject*> *list_objects);
	

private:
    PObjectIconView *objectView;
	AbstractMapper *mapper;
};

#endif
