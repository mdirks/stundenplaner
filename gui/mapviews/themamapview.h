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
#ifndef THEMAMAPVIEW_H
#define THEMAMAPVIEW_H


#include "genericmapview.h"

#include <QMenu>

/**
@author Marcus Dirks
*/
class ThemaMapView : public GenericMapView
{
public:
    ThemaMapView(QWidget * parent = 0, const char * name = 0);
    ~ThemaMapView();
    
    QMenu* getPopupMenu();
    void setMap(ThemaMap *map);

   

};

#endif
