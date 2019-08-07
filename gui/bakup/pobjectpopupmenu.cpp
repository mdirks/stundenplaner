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
#include "pobjectpopupmenu.h"
//#include "pobjectlistboxitem.h"
#include "guirepository.h"
#include "objectitem.h"

PObjectPopupMenu::PObjectPopupMenu()
 : QPopupMenu()
{
	//this->lb = lb;
	insertItem("Formular",this,SLOT(showFormForSelection()));
}


PObjectPopupMenu::~PObjectPopupMenu()
{
}




/*!
    \fn PObjectPopupMenu::showFormForSelection()
 */
void PObjectPopupMenu::showFormForSelection()
{
      if(currentObject){
	     GuiRepository::getInstance()->showFormForObject(currentObject);
	} else {
		qWarning("Cannot show Form: Current object not set !");
	}
	
}


/*!
    \fn PObjectPopupMenu::popup(QListBoxItem *item, QPoint *pos)
 */
void PObjectPopupMenu::popup(QListBoxItem *item, const QPoint &pos)
{
    qDebug("Slot popup !!");
    currentObject = ((PObjectListBoxItem*) item)->getObject();
    QPopupMenu::popup(pos);
}

void PObjectPopupMenu::popup(QListViewItem *item, const QPoint &pos)
{
	if(item->rtti() == ObjectItem::Rtti){
		currentObject = ((ObjectItem*) item)->getObject();
	}
	QPopupMenu::popup(pos);
}

