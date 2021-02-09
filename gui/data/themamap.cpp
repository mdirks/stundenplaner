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

    m_thema=0;

}


ThemaMap::~ThemaMap()
{
}


void ThemaMap::setThema(thema *t)
{
    m_thema=t;
}

thema* ThemaMap::getThema()
{
    if(m_thema==0){
        m_thema = (thema*) ThemaMapmapper::getInstance()->findReference("Thema",getID());
    }
    return m_thema;
}



void ThemaMap::addItem(thema *th, const QPoint &pos)
{
	ThemaItem *item = (ThemaItem*) ThemaItemmapper::getInstance()->create();
	item->setThema(th);
	
	addGraphicsItem(item,pos);
	
	item->save();
}

