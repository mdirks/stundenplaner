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
#include "pobjectlistboxitem.h"
#include "qpainter.h"
#include "qpen.h"

PObjectListBoxItem::PObjectListBoxItem(PObject *o, QListBox *lb)
 : QListBoxItem(lb)
{
	this->o=o;
}


PObjectListBoxItem::~PObjectListBoxItem()
{
}




/*!
    \fn PObjectListBoxItem::paint(QPainter *p)
 */
void PObjectListBoxItem::paint(QPainter *p)
{
	if(o->isSaved()){
		p->setPen( Qt::blue );
        } else {
		p->setPen( Qt::red );
	}
	p->drawText(10,10, QString("%1 - %2").arg(o->getPersistenceObject()->getClassName()).arg(o->getID()) );
}


/*!
    \fn PObjectListBoxItem::height(const QListBox *lb) const
 */
int PObjectListBoxItem::height(const QListBox *lb) const
{
    return 20;
    /// @todo implement me
}


/*!
    \fn PObjectListBoxItem::width(const QListBox *lb) const
 */
int PObjectListBoxItem::width(const QListBox *lb) const
{
    return 200;
    /// @todo implement me
}


/*!
    \fn PObjectListBoxItem::getObject()
 */
PObject* PObjectListBoxItem::getObject()
{
   return this->o;
    /// @todo implement me
}
