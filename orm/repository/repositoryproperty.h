/***************************************************************************
                          repositoryproperty.h  -  description
                             -------------------
    begin                : Sun Oct 6 2002
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

#ifndef REPOSITORYPROPERTY_H
#define REPOSITORYPROPERTY_H

#include <string>
#include <list>

#include <qdatetime.h>
#include <kaction.h>

#include "../persistence/pobject.h"
//#include "propertyaction.h"

using namespace std;
class PropertyAction;
/**
  *@author Marcus Dirks
  */

class RepositoryProperty {


public: 
	RepositoryProperty();
	~RepositoryProperty();
	
	virtual string getName()=0;
	virtual bool isPObject()=0;
	virtual PObject* asPObject(PObject* o)=0;
	virtual string asString(PObject* o)=0;
	virtual QDate asDate(PObject* o)=0;
	
	virtual bool isText() = 0;
        virtual void fromString(string text, PObject *parent) = 0;
	virtual void set(PObject *o, PObject *parent)=0;

         virtual bool isString() = 0;
    virtual bool isCollection() = 0;
    virtual list<PObject*>* asCollection(PObject *po) = 0;
    virtual string getType() = 0;
    virtual bool isDate() = 0;
    virtual QDateTime asDateTime(PObject *o) = 0;
    virtual bool isNumeric() = 0;
    virtual PropertyAction *  getAction(string name)=0;
    virtual list<PropertyAction*> * getAllActions()=0;
    virtual void registerAction(string name, PropertyAction *a)=0;
    virtual void add(PObject *o, PObject *oo) = 0;
    virtual bool isBoolean() = 0;
    virtual bool asBoolean(PObject *o) = 0;
    
};

#endif
