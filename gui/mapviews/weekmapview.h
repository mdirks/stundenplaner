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
#ifndef WEEKMAPVIEW_H
#define WEEKMAPVIEW_H

#include "genericmapview.h"

//#include <QGraphicsScene>

/**  Shows the week map including its items in standard layout day by day. 
@author Marcus Dirks
*/
class WeekMapView : public GenericMapView
{

Q_OBJECT


public:
    WeekMapView(QWidget * parent = 0, const char * name = 0);
    ~WeekMapView();

    //list<KAction*>*  initActions(KActionCollection *actionCollection=0);
    virtual void dummy(){};
    QMenu* getPopupMenu();
    //QPopupMenu* getPopupMenu();

public slots:
	//void readStundenplan();
};

#endif
