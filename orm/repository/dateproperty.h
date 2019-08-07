//
// C++ Interface: dateproperty
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef DATEPROPERTY_H
#define DATEPROPERTY_H

#include "repositorypropertyimpl.h"

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
template<class ObjectType> class DateProperty : public RepositoryPropertyImpl { 

typedef QDate (ObjectType::*pdategetter)();
typedef void (ObjectType::*pdatesetter)(QDate date);


public:
    DateProperty(string name, string type, pdategetter g, pdatesetter s=0) : RepositoryPropertyImpl(name, type){getter = g; setter = s;} ;

    ~DateProperty();

	QDate asDate(PObject *parent);
	string asString(PObject *parent);
	void fromString(string st, PObject *parent);

    bool isDate(){return true;}

private:
	pdategetter getter;
	pdatesetter setter;
};

 template<class ObjectType>
QDate DateProperty<ObjectType>::asDate(PObject *parent)
{
    ObjectType *ot = dynamic_cast<ObjectType*>(parent);
    if(ot){
	    return (ot->*getter)();
    } else {
	qDebug("Warning: Wrong parent type in DateProperty: returning nonsensical date");
    	return QDate::currentDate();
    }
}


template<class ObjectType>
string DateProperty<ObjectType>::asString(PObject *o)
{
    ObjectType *ot = dynamic_cast<ObjectType*>(o);
    if(ot){
	    QDate d=(ot->*getter)();
        return d.toString().toStdString();
    } else {
    	return string("Conversion failed due to wrong object type");
    }
}

template<class ObjectType>
void DateProperty<ObjectType>::fromString(string text, PObject *o)
{
	ObjectType *ot = dynamic_cast<ObjectType*>(o);
	if(ot){
		if(setter){
            QDate d = QDate::fromString(QString(text.c_str()));
			(ot->*setter)(d);
		} else {
			qDebug("Failed to set property: setter not provided");
		}
	} else {
    		qDebug("Conversion failed due to wrong object type");
   	 }
}

#endif
