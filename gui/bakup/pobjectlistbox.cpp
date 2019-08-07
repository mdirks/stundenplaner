//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pobjectlistbox.h"
#include "pobjectlistboxitem.h"

PObjectListBox::PObjectListBox(QWidget *parent, const char *name)
 : QListBox(parent,name)
{
	popupMenu = new PObjectPopupMenu();
	connect(this,SIGNAL(contextMenuRequested(QListBoxItem *, const QPoint&)), popupMenu, SLOT(popup(QListBoxItem *, const QPoint&)));
}


PObjectListBox::~PObjectListBox()
{
}




/*!
    \fn PObjectListBox::insertItem(PObject *o)
 */
void PObjectListBox::insertItem(PObject *o)
{
    PObjectListBoxItem *item = new PObjectListBoxItem(o,this);
}


/*!
    \fn PObjectListBox::addObjects(vector<PObject*> *)
 */
void PObjectListBox::addObjects(list<PObject*> *v)
{
    PObjectListBoxItem *item;
    for(list<PObject*>::iterator it=v->begin(); it!=v->end(); ++it){
	item = new PObjectListBoxItem(*it,this);
	//listBox->insertItem(item);
    }
    qDebug("done: insertion");

    /// @todo implement me
}


