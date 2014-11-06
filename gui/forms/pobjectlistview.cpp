//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pobjectlistview.h"

#include "rootitem.h"

PObjectListView::PObjectListView(QWidget *parent)
 : QListWidget(parent)
{
    //addColumn("Properties");
}


PObjectListView::~PObjectListView()
{
}




/*!
    \fn PObjectListView::setObject(RepositoryEnabled *o)
 */
void PObjectListView::setObject(PObject *o)
{
    new RootItem(this,o);
    
}
