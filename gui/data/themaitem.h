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
#ifndef THEMAITEM_H
#define THEMAITEM_H

#include <QGraphicsScene>
#include "pobjectgraphicsitem.h"
#include "datamodel/thema.h"
#include "orm/transactions/transactionobject.h"

/**
@author Marcus Dirks
*/
class ThemaItem : /*public QGraphicsText, public TransactionObject*/ public PObjectGraphicsItem
{
public:
    ThemaItem();
    ThemaItem(QGraphicsScene *scene);
    ThemaItem(thema *th, QGraphicsScene *scene);
    
    ~ThemaItem();
    thema* getThema();
    void setThema(thema *th);
    int rtti() const;
    
   const int RTTI;
    
private:
   thema *th;

};

#endif
