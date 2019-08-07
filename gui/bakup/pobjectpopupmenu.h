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
#ifndef POBJECTPOPUPMENU_H
#define POBJECTPOPUPMENU_H

//#include <qlistbox.h>
#include <QMenu>
#include <QPoint>

//#include "pobjectlistbox.h"
//#include "pobjectlistboxitem.h"
//#include "qlistview.h"



/**
@author Marcus Dirks
*/
class PObjectPopupMenu : public QMenu
{
     Q_OBJECT

public:
    PObjectPopupMenu();

    ~PObjectPopupMenu();

public slots:
    virtual void showFormForSelection();
    virtual void popup(QListBoxItem *item, const QPoint &pos);
    virtual void popup(QListViewItem *item, const QPoint &pos);
    
private:
    //PObjectListBox *lb;
    PObject *currentObject;
};

#endif
