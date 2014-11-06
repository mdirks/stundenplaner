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
#ifndef THEMAMAP_H
#define THEMAMAP_H

#include <list>

#include <QGraphicsScene>
#include <QPoint>

#include "themaitem.h"
#include "pobjectgraphicsitem.h"
#include "datamodel/thema.h"
#include "orm/persistence/pobject.h"
#include "orm/transactions/transactionobject.h"
#include "genericmap.h"

using namespace std;

/**
@author Marcus Dirks
*/
class ThemaMap : public GenericMap
{
public:
    ThemaMap();
    ~ThemaMap();
    
    void addItem(PObject *o, const QPoint &pos){qDebug("ThemaMap: Adding Object"); GenericMap::addItem(o,pos);}; // why is this required ?
    void addItem(thema *th, const QPoint &pos);
    
    //void init();
    
};

#endif
