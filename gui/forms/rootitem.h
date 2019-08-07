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
#ifndef ROOTITEM_H
#define ROOTITEM_H

#include <QListWidgetItem>
#include <qstring.h>


#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryentry.h"


/**
@author Marcus Dirks
*/
class RootItem : public QListWidgetItem
{
public:
    RootItem(QListWidget *parent, PObject *mo);
    ~RootItem();
    
    virtual QString text( int column ) const;
    
protected:
     virtual void activate();
     
private:
     PObject *mo;
     RepositoryEntry *entry;
};

#endif
