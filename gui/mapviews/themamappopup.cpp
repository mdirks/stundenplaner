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
#include "themamappopup.h"
#include "gui/data/themaitem.h"
//#include "themaitemmapper.h"
#include "gui/data/genericmap.h"
#include "gui/data/pobjectgraphicsitem.h"
#include "gui/guirepository.h"
#include "datamodel/thema.h"
#include "datamodel/themamapper.h"
#include "gui/base/guiconfig.h"

ThemaMapPopup::ThemaMapPopup()
 : QMenu()
{
    addAction("Neues Thema",this,"newThema");
    addAction("Icon wählen",this,"selectIcon");
	map=0;
}


ThemaMapPopup::~ThemaMapPopup()
{
}

void ThemaMapPopup::popup(const QPoint &globalPos, const QPoint &pos, QGraphicsItem *selectedItem)
{
    if(PObjectGraphicsItem *oc = dynamic_cast<PObjectGraphicsItem*>(selectedItem)){
	    currentObject = oc->getObject();
     }
     
     popup(globalPos, pos);
}

void ThemaMapPopup::popup(const QPoint &globalPos, const QPoint &pos, PObject *selectedObject)
{
	currentObject = selectedObject;
	popup(globalPos, pos);
}


void ThemaMapPopup::popup(  const QPoint &globalPos, const QPoint &pos )
{  
    qDebug("Slot popup !!");
    currentGlobalPos = globalPos;
    currentPos = pos;
    
    QMenu::popup(globalPos);
}

void ThemaMapPopup::selectIcon()
{
	if(currentObject){
		GuiConfig::getInstance()->selectIcon(currentObject);
	}
}


void ThemaMapPopup::newThema()
{
    if(map!=0){
	thema *th = themamapper::getInstance()->create();
	map->addItem(th, currentPos);
	/*
	ThemaItem *item = ThemaItemmapper::getInstance()->create();
	item->setThema(th);
	item->setX(currentPos.x());
	item->setY(currentPos.y());
	map->addThemaItem(item);
	*/
	
	/*
	th->save();
	item->save();
	map->save();
	*/
    } else {
    	qDebug("ThemaMapPopup: Could not create new Thema : no Map defined");
    }
}

void ThemaMapPopup::insertThema()
{
	
}

void ThemaMapPopup::editThema()
{
	
}


/*!
    \fn ThemaMapPopup::setThemaMap(ThemaMap *map)
 */
void ThemaMapPopup::setMap(GenericMap *map)
{
    this->map = map;
}
