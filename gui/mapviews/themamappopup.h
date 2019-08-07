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
#ifndef THEMAMAPPOPUP_H
#define THEMAMAPPOPUP_H

#include <QMenu>
#include <QPoint>
#include <QGraphicsScene>

#include "orm/persistence/pobject.h"
#include "gui/data/themamap.h"
#include "gui/data/genericmap.h"

/**
@author Marcus Dirks
*/
class ThemaMapPopup : public QMenu
{
Q_OBJECT

public:
    ThemaMapPopup();
    ~ThemaMapPopup();
    
   void popup(const QPoint &globalPos, const QPoint &pos, QGraphicsItem *selectedItem);
   void popup(const QPoint &globalPos, const QPoint &pos, PObject *selectedObject);
   void popup(const QPoint &globalPos, const QPoint &pos);
    
    void setMap(GenericMap *map);
  
public slots:
   void newThema();
   void selectIcon();
   void insertThema();
   void editThema();
   
private:
    QPoint currentGlobalPos, currentPos;
    PObject *currentObject;
    GenericMap *map;
};

#endif
