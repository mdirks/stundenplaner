//
// C++ Interface: datetimeproperty
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef DATETIMEPROPERTY_H
#define DATETIMEPROPERTY_H


#include "repositorypropertyimpl.h"

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
template<class ObjectType> class DateTimeProperty : public RepositoryPropertyImpl { 

typedef QDateTime (ObjectType::*pdategetter)();
typedef void (ObjectType::*pdatesetter)(QDateTime date);


public:
    DateTimeProperty(string name, string type, pdategetter g, pdatesetter s=0) : RepositoryPropertyImpl(name, type){getter = g; setter = s;} ;

    ~DateTimeProperty();

	QDate asDate(PObject *parent); 
	QDateTime asDateTime(PObject *parent);
	string asString(PObject *parent);
	void fromString(string st, PObject *parent);

    bool isDate(){return true;}

private:
	pdategetter getter;
	pdatesetter setter;
};

 template<class ObjectType>
QDateTime DateTimeProperty<ObjectType>::asDateTime(PObject *parent)
{
    ObjectType *ot = dynamic_cast<ObjectType*>(parent);
    if(ot){
	    return (ot->*getter)();
    } else {
	qDebug("Warning: Wrong parent type in DateProperty: returning nonsensical date");
    	return QDateTime::currentDateTime();
    }
}

template<class ObjectType>
QDate DateTimeProperty<ObjectType>::asDate(PObject *parent)
{
    ObjectType *ot = dynamic_cast<ObjectType*>(parent);
    if(ot){
	    return ((ot->*getter)()).date();
    } else {
	qDebug("Warning: Wrong parent type in DateProperty: returning nonsensical date");
    	return QDate::currentDate();
    }
}


template<class ObjectType>
string DateTimeProperty<ObjectType>::asString(PObject *o)
{
    ObjectType *ot = dynamic_cast<ObjectType*>(o);
    if(ot){
	    QDateTime d=(ot->*getter)();
        return d.toString().toStdString();
    } else {
    	return string("Conversion failed due to wrong object type");
    }
}

template<class ObjectType>
void DateTimeProperty<ObjectType>::fromString(string text, PObject *o)
{
	ObjectType *ot = dynamic_cast<ObjectType*>(o);
	if(ot){
		if(setter){
            QDateTime d = QDateTime(QDate::fromString(QString(text.c_str())));
			(ot->*setter)(d);
		} else {
			qDebug("Failed to set property: setter not provided");
		}
	} else {
    		qDebug("Conversion failed due to wrong object type");
   	 }
}

#endif

