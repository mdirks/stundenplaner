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
#include <qwmatrix.h>
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
    \fn WeekMapView::initActions(KActionCollection *actionCollection)
 */
/*
list<KAction*>*  WeekMapView::initActions(KActionCollection *actionCollection)
{
    list<KAction*> *result  = GenericMapView::initActions(actionCollection);
    result->push_back(new KAction("Stundenplan", KStdAccel::shortcut(KStdAccel::New), this,SLOT(readStundenplan()), actionCollection, "zoomout"));
    return result;
}
*/

/*
void WeekMapView::readStundenplan()
{
	WeekMap *wm = dynamic_cast<WeekMap*>(getMap());
	if(wm){
		wm->readStundenplan();
		update();
	}
}
*/

/*
QPopupMenu* WeekMapView::getPopupMenu()
{
    //if(! pmenu){
		pmenu = new QPopupMenu(this);
		list<KAction*> *actionList = initActions();
		for(list<KAction*>::iterator it = actionList->begin(); it != actionList->end(); it++){
			if(*it){
			(*it)->plug(pmenu);
			}
		}
		if(QPopupMenu *sub = getPopupForSelected()){
			pmenu->insertItem("Daten",sub);
		}

	//}
	return pmenu;
}
*/

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
