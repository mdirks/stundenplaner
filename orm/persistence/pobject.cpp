/***************************************************************************
                          pobject.cpp  -  description
                             -------------------
    begin                : Fri Oct 4 2002
    copyright            : (C) 2002 by Marcus Dirks
    email                : marcus.dirks@t-online.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "pobject.h"
#include "services/utils/utils.h"

//static PersistenceClass* persObj=0;

PObject::PObject():name("Unknown"){
	id=999;
	saved=true;
	removed=false;
}
PObject::~PObject(){
}
/**  */
int PObject::getID(){
	return id;
}

void PObject::setID(int id){
	this->id = id;
}

/**  */

string PObject::getName(){
	return name;
}

void PObject::setName(string name){
	this->name=name;
	saved=false;
}

string PObject::toString(){
	return to_string(getID()) + getName();
}


PersistenceClass* PObject::getPersistenceObject(){
	return this->persObj;
}


void PObject::setPersistenceObject(PersistenceClass* persObj){
	this->persObj = persObj;
}


void PObject::save(){
	this->getPersistenceObject()->save(this);
	saved=true;
}

/*!
    \fn PObject::delete()
 */
void PObject::deleteObject()
{
	this->getPersistenceObject()->deleteObject(this);
}



/*
void PObject::save(PObject *realSubject){
	this->persObj->save(realSubject);
}
*/




/*!
    \fn PObject::isSaved()
 */
bool PObject::isSaved()
{
    return saved;
}




/*!
    \fn PObject::getClassName()
 */
string PObject::getClassName()
{
    return getPersistenceObject()->getClassName();
}


/*!
    \fn PObject::getRemoved()
 */
bool PObject::getRemoved()
{
    return removed;
}


/*!
    \fn PObject::setRemoved(bool removed)
 */
void PObject::setRemoved(bool removed)
{
    this->removed = removed;
}
