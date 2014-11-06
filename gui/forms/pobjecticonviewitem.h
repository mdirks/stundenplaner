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
#include "orm/persistence/pobject.h"

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class PObjectIconViewItem : public QListWidgetItem
{
public:
    PObjectIconViewItem(PObject *o, QListWidget *iv, QString text, QPixmap &icon);

    	~PObjectIconViewItem();
    	PObject* getObject();
	
    //void setText(QString &text);

private:
	PObject *object;

};

#endif
