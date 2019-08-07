//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef NEWOBJECTITEM_H
#define NEWOBJECTITEM_H

#include <qlistview.h>

#include "actionitem.h"
#include "../orm/mapping/abstractmapper.h"
#include "typeitem.h"

/**
@author Marcus Dirks
*/
class NewObjectItem : public ActionItem
{
public:
    NewObjectItem(AbstractMapper *mapper, TypeItem *parent);
    ~NewObjectItem();
    
    void actionPerformed();

private:
    AbstractMapper *mapper;
    TypeItem *parent;
};

#endif
