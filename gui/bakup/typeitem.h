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
#ifndef TYPEITEM_H
#define TYPEITEM_H

#include <QListWidget>

#include "../orm/mapping/abstractmapper.h"
/**
@author Marcus Dirks
*/
class TypeItem : public QListWidgetItem
{
public:
    TypeItem(AbstractMapper *mapper, QListWidget *parent);
    ~TypeItem();

protected:
     virtual void activate();
 
private:
    AbstractMapper *mapper;   
 
};

#endif
