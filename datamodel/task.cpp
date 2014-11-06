//
// C++ Implementation: task
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "task.h"
#include "taskmapper.h"

task::task()
{
	setMapper(taskmapper::getInstance());
	bo=0;
}


task::~task()
{
}


QDate task::getDatum()
{
	return this->date;
}

void task::setDatum(QDate date)
{
	this->date = date;
}

/*!
    \fn task::getReference()
 */
PObject*  task::getBezugsobjekt()
{
    if(!bo){
	bo = taskmapper::getInstance()->findReference("Bezugsobjekt",getID());
    }	
    return bo;
}


/*!
    \fn task::setReference(PObject *r)
 */
void task::setBezugsobjekt(PObject *r)
{
    this->bo = r;
}
