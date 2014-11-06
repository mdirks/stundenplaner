/***************************************************************************
                          stunde.cpp  -  description
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

#include "stunde.h"
//#include "stundepersistence.h"

#include "stundemapper.h"
#include "orm/persistence/database.h"
#include "services/utils/utils.h"




stunde::stunde(){
	str_rep.append("<qt> <h3 align=center> Thema </h3> ");
	str_rep+=getZielAsString();
	str_rep+=getOpoAsString();
	str_rep.append("</qt>");
	
	setMapper(stundemapper::getInstance());
	//setPersistenceObject(stundepersistence::getInstance());
	
	list_opos=0;
        list_materialien=0;
	th=0;
	//list_opos = Database::getInstance()->createCollection();
}
stunde::~stunde(){
}
/** Return the thema. Maybe 0 if none is set. */
thema* stunde::getThema(){
	if(th==0){
		th= (thema*) stundemapper::getInstance()->findReference("Thema",getID());
	}
	return th;
}
/** No descriptions */
string stunde::getZielAsString(){
	return * new string("<h3 align=center> Ziel der Stunde </h3>");
}
/** No descriptions */
string stunde::getOpoAsString(){
	return * new string("<h3 align=center> Opo </h3>");
}
/** No descriptions */
string stunde::toString(){
	return str_rep;
}

list<opo*>* stunde::getOpos()
{

	if(list_opos == 0){
		list_opos = stundemapper::getInstance()->findOpos(getID());
	}
	
	return list_opos;
}

void stunde::addToOpos(opo *o)
{
	getOpos()->push_back(o);
	saved=false;
}

/*!
    \fn stunde::deleteOpo(opo *o)
 */
void stunde::deleteFromOpos(opo *o)
{
    getOpos()->remove(o);
}


/*!
    \fn stunde::setThema(string &thema)
 */
void stunde::setThema(thema *th)
{
     this->th= th;
     saved=false;
}


/*!
    \fn stunde::setOpos(PCollection *col)
 */
 
/* 
void stunde::setOpos(PCollection *col)
{
     list_opos = col;
     //isSaved=false;
}
*/

/*!
    \fn stunde::getVerlauf()
 */
string stunde::getVerlauf()
{
    return verlauf;
}


/*!
    \fn stunde::setVerlauf(const string &verlauf)
 */
void stunde::setVerlauf(string verlauf)
{
    this->verlauf = verlauf;
}


/*!
    \fn stunde::getTitle()
 */
string stunde::getTitle()
{
    return this->title; //return getName();
}


/*!
    \fn stunde::setTitle(string t)
 */
void stunde::setTitle(string t)
{
    this->title = t;//setName(t);
}

list<material*> *stunde::getMaterialien()
{
	if(list_materialien == 0){
		list_materialien = (list<material*>*) stundemapper::getInstance()->findMaterialien(getID());
	}
	return list_materialien;
}

void stunde::addToMaterialien(material *ma)
{
	getMaterialien()->push_back(ma);
}

void stunde::deleteFromMaterialien(material *ma)
{
	getMaterialien()->remove(ma);
}
