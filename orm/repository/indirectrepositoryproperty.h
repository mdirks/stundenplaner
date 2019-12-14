/***************************************************************************
 *   Copyright (C) 2008 by Marcus Dirks   *
 *   m-dirks@web.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef INDIRECTREPOSITORYPROPERTY_H
#define INDIRECTREPOSITORYPROPERTY_H

#include "repositorypropertyimpl.h"

#include <list>

using namespace std;
/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class IndirectRepositoryProperty : public RepositoryPropertyImpl{
public:
	IndirectRepositoryProperty(list<RepositoryProperty*> *list_properties, string name);
	~IndirectRepositoryProperty();

	//virtual string getName(){return name;};
    
	string asString(PObject *o);
	void fromString(string text, PObject *parent);
    	void set(PObject *o, PObject *parent);

    	QDate asDate(PObject *parent);
    	QDateTime asDateTime(PObject *o);

    	PObject* asPObject(PObject *o);

    	bool isText();
    	bool isString();
    	bool isCollection();
    	bool isDate();
    	bool isPObject();
    	bool isNumeric();
    	bool isBoolean();
    	bool asBoolean(PObject *o);
    
    	list<PObject*>* asCollection(PObject *po);
    	string getType();
    	PropertyAction *  getAction(string name);
    	list<PropertyAction*> * getAllActions();
    	void registerAction(string name, PropertyAction *a);
     	void add(PObject *o, PObject *oo);
        PObject* getTrueParent(PObject *o);

private:


private:
	list<RepositoryProperty*> *list_properties;
	RepositoryProperty *rp_last;
	
};

#endif
