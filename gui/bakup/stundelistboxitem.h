//
// C++ Interface: stundelistboxitem
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STUNDELISTBOXITEM_H
#define STUNDELISTBOXITEM_H

#include <qlistbox.h>
#include <qpainter.h>
#include "../datamodel/stunde.h"

/**
@author Marcus Dirks
*/
class StundeListBoxItem : public QListBoxItem
{
public:
    StundeListBoxItem(stunde *st,QListBox *lb=0);

    ~StundeListBoxItem();
    void paint(QPainter *p);
    int height(const QListBox *lb) const;
    int width(const QListBox *lb) const;
    stunde* getStunde();
    
private:
    stunde *st;

};

#endif
