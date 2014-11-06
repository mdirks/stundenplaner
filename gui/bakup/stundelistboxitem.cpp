//
// C++ Implementation: stundelistboxitem
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "stundelistboxitem.h"
#include "../utils/utils.h"

StundeListBoxItem::StundeListBoxItem(stunde *st, QListBox *lb)
 : QListBoxItem(lb)
{
	this->st = st;
}


StundeListBoxItem::~StundeListBoxItem()
{
}




/*!
    \fn StundeListBoxItem::paint(QPainter *p)
 */
void StundeListBoxItem::paint(QPainter *p)
{
    p->setPen( Qt::blue );
    p->drawText(10,10, QString("Stunde %1").arg(st->getID()) );/// @todo implement me
    //qDebug("paint done");
}


/*!
    \fn StundeListBoxItem::height(QListBox *lb)
 */
int StundeListBoxItem::height(const QListBox *lb) const
{
    return 20;
}


/*!
    \fn StundeListBoxItem::width(QListBox *lb)
 */
int StundeListBoxItem::width(const QListBox *lb) const
{
    return 200;
}


/*!
    \fn StundeListBoxItem::getStunde()
 */
stunde* StundeListBoxItem::getStunde()
{
    return this->st;
}
