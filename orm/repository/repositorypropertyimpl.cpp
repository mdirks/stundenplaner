//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "repositorypropertyimpl.h"

RepositoryPropertyImpl::RepositoryPropertyImpl(string n, string t, bool cp)
	: name(n), type(t), collection_property(cp)
{
	/*
	this->name = name;
	isText = false;
	*/
	actionList = new list<PropertyAction*>();
}


RepositoryPropertyImpl::~RepositoryPropertyImpl()
{
}






/*!
    \fn RepositoryPropertyImpl::isText()
 */
bool RepositoryPropertyImpl::isText()
{
    return false;
}

bool RepositoryPropertyImpl::isString()
{
	return false;
}


/*!
    \fn RepositoryPropertyImpl::isCollection()
 */
bool RepositoryPropertyImpl::isCollection()
{
    return collection_property;
}





/*!
    \fn RepositoryPropertyImpl::getType()
 */
string RepositoryPropertyImpl::getType()
{
    return type;
}

/*!
    \fn RepositoryProperty::getAction(string name)
 */
PropertyAction *  RepositoryPropertyImpl::getAction(string name)
{
    return actionMap[name];
}


/*!
    \fn RepositoryProperty::getAllActions()
 */
list<PropertyAction*> * RepositoryPropertyImpl::getAllActions()
{
    return actionList;
}


/*!
    \fn RepositoryProperty::registerAction(string name, QAction *a)
 */
void RepositoryPropertyImpl::registerAction(string name, PropertyAction *a)
{
    actionMap[name] = a;
    actionList -> push_back(a);
}




/*!
    \fn RepositoryPropertyImpl::add(PObject *o, PObject *oo)
 */
void RepositoryPropertyImpl::add(PObject *o, PObject *oo)
{
    qDebug("RepositoryPropertyImpl::add : WARNING : implemented only for CollectionProperty");
}
