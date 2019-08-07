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
#include "themaitem.h"
#include "themaitemmapper.h"
#include "themamap.h"

ThemaItem::ThemaItem()
 : PObjectGraphicsItem(),RTTI(1001)
{
	this->th=0;
	
	setMapper(ThemaItemmapper::getInstance());
}

ThemaItem::ThemaItem(QGraphicsScene *sc)
 : PObjectGraphicsItem(sc),RTTI(1001)
{
	this->th=0;
	
	setMapper(ThemaItemmapper::getInstance());
}

ThemaItem::ThemaItem(thema *th, QGraphicsScene *sc)
 : PObjectGraphicsItem(sc),RTTI(1001)
{
	setThema(th);
	
	setMapper(ThemaItemmapper::getInstance());
}

ThemaItem::~ThemaItem(){}




/*!
    \fn ThemaItem::getThema()
 */
thema* ThemaItem::getThema()
{
    if(th==0){
    	th = (thema*) ThemaItemmapper::getInstance()->findReference("Thema",getID());
    }
    return th;
}


/*!
    \fn ThemaItem::setThema(thema *th)
 */
void ThemaItem::setThema(thema *th)
{
    this->th = th;
    setObject(th);
    //setText(th->getTitle());
}


/*!
    \fn ThemaItem::rtti() const
 */
int ThemaItem::rtti() const
{
     return RTTI;
}
