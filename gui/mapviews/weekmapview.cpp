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
#include "weekmapview.h"
#include "services/sstundenplan.h"
#include "gui/data/weekmap.h"
#include "mapviewspopupfactory.h"
//#include <qwmatrix.h>
WeekMapView::WeekMapView(QWidget * parent, const char * name)
 : GenericMapView(parent,name)
{
    //QWMatrix wm = worldMatrix(); // set to convenient initial size
    //wm.scale(.7,.7);
    //setWorldMatrix(wm);
    acceptDrops();
}


WeekMapView::~WeekMapView()
{
}



/*!
    \fn WeekMapView::getPopupMenu()
 */
QMenu* WeekMapView::getPopupMenu()
{
    	MapviewsPopupFactory *factory = MapviewsPopupFactory::getInstance();
	if(factory){
		return factory->getPopupForWeekMapView(this,currentPos);
	} else {
        return new QMenu();
	}
}
