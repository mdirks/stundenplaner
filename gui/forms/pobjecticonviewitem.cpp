//
// C++ Implementation: pobjecticonviewitem
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pobjecticonviewitem.h"
#include <QDebug>

PObjectIconViewItem::PObjectIconViewItem(PObject *o, QListWidget *iv, QString text, QPixmap &icon)
 : QListWidgetItem(iv)
{
	this->object = o;


    QListWidgetItem::setText(o->getName().c_str());
    QListWidgetItem::setIcon(icon);

    setFlags(flags()|Qt::ItemIsEditable);


}


PObjectIconViewItem::~PObjectIconViewItem()
{
}

/*
void PObjectIconViewItem::setText(QString &text)
{
    qDebug() << "PObjectIconViewItem setText called";
    getObject()->setName(text.toStdString());
    QListWidgetItem::setText(text);
}
*/


/*!
    \fn PObjectIconViewItem::getObject()
 */
PObject* PObjectIconViewItem::getObject()
{
    return object;
}
