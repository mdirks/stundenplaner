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
#include "themamap.h"
#include "themamapmapper.h"

#include "themaitemmapper.h"




ThemaMap::ThemaMap() : GenericMap(1400,1000)
{
	
	
	setMapper(ThemaMapmapper::getInstance());
}


ThemaMap::~ThemaMap()
{
}






void ThemaMap::addItem(thema *th, const QPoint &pos)
{
	ThemaItem *item = (ThemaItem*) ThemaItemmapper::getInstance()->create();
	item->setThema(th);
	
	addGraphicsItem(item,pos);
	
	item->save();
}

