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
#include <QPoint>
#include <QGraphicsScene>
#include "gui/mapviews/mapviewspopupfactory.h"

#include "themamapview.h"


ThemaMapView::ThemaMapView(QWidget * parent, const char * name)
 : GenericMapView(parent,name)
{
    setMap(new ThemaMap());
}


ThemaMapView::~ThemaMapView()
{
}

QMenu* ThemaMapView::getPopupMenu()
{
        MapviewsPopupFactory *factory = MapviewsPopupFactory::getInstance();
    if(factory){
        return factory->getPopupForThemaMapView(this,currentPos);
    } else {
        return new QMenu();
    }
}

void ThemaMapView::setMap(ThemaMap *map)
{
    GenericMapView::setMap(map);
}



