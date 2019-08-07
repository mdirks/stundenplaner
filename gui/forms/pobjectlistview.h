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
#ifndef POBJECTLISTVIEW_H
#define POBJECTLISTVIEW_H

#include <QListWidget>

#include "orm/persistence/pobject.h"


/**
@author Marcus Dirks
*/
class PObjectListView : public QListWidget
{
public:
    PObjectListView(QWidget *parent);

    ~PObjectListView();
    void setObject(PObject *o);

};

#endif
