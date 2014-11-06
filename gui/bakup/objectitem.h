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
#ifndef OBJECTITEM_H
#define OBJECTITEM_H

#include <QListWidgetItem>

#include "../orm/persistence/pobject.h"
//#include "../orm/mappingmappedobject.h"

/**
@author Marcus Dirks
*/
class ObjectItem : public QListWidgetItem
{
public:
    ObjectItem(PObject *o, QListWidgetItem *parent);
    ObjectItem(PObject *o, QListWidgetItem *parent, QListWidgetItem *after);
    ~ObjectItem();
    
    PObject* getObject();
    int rtti() const;

public:
    static int Rtti;
    
private:
    PObject *o;
};

#endif
