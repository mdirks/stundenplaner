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
#ifndef BOOLEANPROPERTY_H
#define BOOLEANPROPERTY_H

#include "repositorypropertyimpl.h"

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
template<class ObjectType> class BooleanProperty : public RepositoryPropertyImpl
{

typedef bool (ObjectType::*pboolgetter)();
typedef void (ObjectType::*pboolsetter)(bool b);

public:
    BooleanProperty(string name, string type, pboolgetter g, pboolsetter s=0)
	: RepositoryPropertyImpl(name, type){getter = g; setter = s;};
    ~BooleanProperty(){};

	string asString(PObject *o);
   	void fromString(string text, PObject *o);
    	bool asBoolean(PObject *o);
    
    	bool isBoolean(){return true;}

private:
	pboolgetter getter;
    	pboolsetter setter;

};


template<class ObjectType>
string BooleanProperty<ObjectType>::asString(PObject *o)
{
	ObjectType *ot = 0;
    ot = dynamic_cast<ObjectType*>(o);
    if(ot){
        QString st("%1");
        return st.arg((ot->*getter)()).toStdString();
    } else {
        return string("Conversion failed due to wrong object type");
    }
}

template<class ObjectType>
void BooleanProperty<ObjectType>::fromString(string text, PObject *o)
{
	ObjectType *ot = dynamic_cast<ObjectType*>(o);
	if(ot){
		if(setter){
            QString str(text.c_str());
            (ot->*setter)(str.toLower() == "true");
		} else {
			qDebug("Failed to set property: setter not provided");
		}
	} else {
    		qDebug("Conversion failed due to wrong object type");
   	 }
}

template<class ObjectType>
bool BooleanProperty<ObjectType>::asBoolean(PObject *o)
{
	ObjectType *ot = dynamic_cast<ObjectType*>(o);
	if(ot){
		return (ot->*getter)();
	} else {
		return -1;
	}
}
#endif
