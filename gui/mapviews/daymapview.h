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
#ifndef DAYMAPVIEW_H
#define DAYMAPVIEW_H

#include "genericmapview.h"



/**
@author Marcus Dirks
*/
 class DayMapView  :  public GenericMapView {
public:
	DayMapView(QWidget * parent=0, const char * name=0);
	~DayMapView();

};

#endif
