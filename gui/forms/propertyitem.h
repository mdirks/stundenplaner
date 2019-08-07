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
#ifndef PROPERTYITEM_H
#define PROPERTYITEM_H

#include <QListWidgetItem>
#include <qstring.h>

#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryproperty.h"
#include "repositoryitem.h"

/**
@author Marcus Dirks
*/
class PropertyItem : public QListWidgetItem, public RepositoryItem
{
public:
    PropertyItem(QListWidgetItem *parent, RepositoryProperty *rp, PObject *mo);
    ~PropertyItem();
    
    RepositoryProperty* getRepositoryProperty();
    virtual QString text ( int column ) const;
    PObject* getParent();

private:
	RepositoryProperty *rp;
	PObject *mo;

};

#endif
