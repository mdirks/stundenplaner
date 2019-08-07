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
#ifndef TYPELISTVIEW_H
#define TYPELISTVIEW_H

#include <QWidget>
#include <QListWidget>

#include "orm/mapping/abstractmapper.h"
#include "orm/persistence/pobject.h"

/**
@author Marcus Dirks
*/
class TypeListView : public QListWidget
{
Q_OBJECT

public:
    TypeListView(QWidget *parent=0, const char *name=0);
    ~TypeListView();
    
    void addTypeNodes(list<AbstractMapper*> *list_mappers);
    void addTypeNode(AbstractMapper *mapper);

public slots:
     void checkForActionItem(QListWidgetItem *item);
    void checkForObjectItem(QListWidgetItem *item);
    void checkForDrag(QListWidgetItem *item);
 
protected:
      virtual void contentsMouseMoveEvent ( QMouseEvent * e );
  
private:
    //void dragStart(PObject *o);
    
private:
    PObject *draggedObject;
    QListWidgetItem *selection;
};

#endif
