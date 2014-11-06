/***************************************************************************
                          opo.cpp  -  description
                             -------------------
    begin                : Sam Feb 28 2004
    copyright            : (C) 2004 by Marcus Dirks
    email                : marcus.dirks@web.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "opo.h"
#include "opomapper.h"

opo::opo() : title("Empty title"){
	setMapper(opomapper::getInstance());
	list_materialien=0;
}
opo::~opo(){
}
/** Read property of QString title. */
string opo::getTitle(){
	return title;
}
/** Write property of QString title. */
void opo::setTitle(string title){
	this->title = title;
}

list<material*> *opo::getMaterialien()
{
	if(list_materialien == 0){
		list_materialien = (list<material*>*) opomapper::getInstance()->findMaterialien(getID());
	}
	return list_materialien;
}

void opo::addToMaterialien(material *ma)
{
	getMaterialien()->push_back(ma);
}

void opo::deleteFromMaterialien(material *ma)
{
	getMaterialien()->remove(ma);
}
