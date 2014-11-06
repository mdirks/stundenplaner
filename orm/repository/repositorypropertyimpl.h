//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef REPOSITORYPROPERTYIMPL_H
#define REPOSITORYPROPERTYIMPL_H

#include <string>
#include "repositoryproperty.h"

using namespace std;

/**
@author Marcus Dirks
*/
class RepositoryPropertyImpl : public RepositoryProperty 
{
public:
    RepositoryPropertyImpl(string name, string type, bool cp=false);
    //RepositoryPropertyImpl(string name);
    ~RepositoryPropertyImpl();
    
    virtual string getName(){return name;};
    
    virtual string asString(PObject *o){return string("null");}
    virtual void fromString(string text, PObject *parent){qDebug("Warning: Failed to set property: fromString not implemented");}
    virtual void set(PObject *o, PObject *parent){ qDebug("Warning: Failde to set property: set(PObject) not implemented");}

    virtual QDate asDate(PObject *parent){return QDate::currentDate();}
    virtual QDateTime asDateTime(PObject *o){return QDateTime::currentDateTime();}

    virtual PObject* asPObject(PObject *o){qDebug("Warning: failed to getproperty, asPObject() not implemented"); return 0;};

    virtual bool isText();
    virtual bool isString();
    virtual bool isCollection();
    virtual bool isDate(){return false;};
    virtual bool isPObject(){return false;};
    virtual bool isNumeric(){return false;};
    virtual bool isBoolean(){return false;};
    virtual bool asBoolean(PObject *o){qDebug("Warning: failed to getproperty, asBoolean() not implemented"); return false;}
    
    virtual list<PObject*>* asCollection(PObject *po){return 0;};
    string getType();
    PropertyAction *  getAction(string name);
    list<PropertyAction*> * getAllActions();
    void registerAction(string name, PropertyAction *a);
    virtual void add(PObject *o, PObject *oo);
 
private:
    string name, type;
    bool collection_property;
    map<string,PropertyAction*> actionMap;
    list<PropertyAction*> *actionList;

};

#endif
