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
#include "indirectrepositoryproperty.h"
#include <QDebug>

IndirectRepositoryProperty::IndirectRepositoryProperty(list<RepositoryProperty*> *lp, string name)
	: list_properties(lp), rp_last(lp->back()), RepositoryPropertyImpl(name,(lp->back())->getType(),false)
{
	qDebug("IndirectRepositoryPropert() ok");
}


IndirectRepositoryProperty::~IndirectRepositoryProperty()
{

}


PObject* IndirectRepositoryProperty::getTrueParent(PObject *o)
{
	PObject *oo = o;
	for(list<RepositoryProperty*>::iterator it=list_properties->begin(); it != (--list_properties->end()); it++){
		oo = (*it)->asPObject(oo);
		if(!oo){
			qDebug("IndirectRepositoryProperty::asString() : invalid state()");
		}
	}
	return oo;
}

string IndirectRepositoryProperty::asString(PObject *o)
{
	if(rp_last){
		return rp_last->asString(getTrueParent(o));
	} else {
        qDebug() << QString("IndirectRepositoryProperty::asString : invalid state");
		return "";
	}
}

void IndirectRepositoryProperty::fromString(string text, PObject *parent)
{
	if(rp_last){
		rp_last->fromString(text,getTrueParent(parent));
	} else {
        qDebug() << QString("IndirectRepositoryProperty::asString : invalid state");
	}
}

void IndirectRepositoryProperty::set(PObject *o, PObject *parent)
{
	if(rp_last){
		rp_last->set(o, getTrueParent(parent));
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
	}
}


QDate IndirectRepositoryProperty::asDate(PObject *parent)
{
	if(rp_last){
		return rp_last->asDate(getTrueParent(parent));
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return RepositoryPropertyImpl::asDate(parent);
	}
}


QDateTime IndirectRepositoryProperty::asDateTime(PObject *o)
{
	if(rp_last){
		return rp_last->asDateTime(getTrueParent(o));
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return RepositoryPropertyImpl::asDateTime(o);
	}
}

PObject* IndirectRepositoryProperty::asPObject(PObject *o)
{
	if(rp_last){
		return rp_last->asPObject(getTrueParent(o));
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return RepositoryPropertyImpl::asPObject(o);
	}
}



bool IndirectRepositoryProperty::isText()
{
	if(rp_last){
		return rp_last->isText();
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return false;
	}
}

bool IndirectRepositoryProperty::isString()
{
	if(rp_last){
		return rp_last->isString();
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return false;
	}
}

bool IndirectRepositoryProperty::isCollection()
{
	if(rp_last){
		return rp_last->isCollection();
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return false;
	}
}

bool IndirectRepositoryProperty::isDate()
{
	if(rp_last){
		return rp_last->isDate();
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return false;
	}
}

bool IndirectRepositoryProperty::isPObject()
{
	if(rp_last){
		return rp_last->isPObject();
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return false;
	}
}

bool IndirectRepositoryProperty::isNumeric()
{
	if(rp_last){
		return rp_last->isNumeric();
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return false;
	}
}

bool IndirectRepositoryProperty::isBoolean()
{
	if(rp_last){
		return rp_last->isBoolean();
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return false;
	}
}

bool IndirectRepositoryProperty::asBoolean(PObject *o)
{
	if(rp_last){
		return rp_last->asBoolean(getTrueParent(o));
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return false;
	}
}

list<PObject*>* IndirectRepositoryProperty::asCollection(PObject *po)
{
	if(rp_last){
		return rp_last->asCollection(getTrueParent(po));
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return RepositoryPropertyImpl::asCollection(po);
	}
}

string IndirectRepositoryProperty::getType()
{
	if(rp_last){
		return rp_last->getType();
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return RepositoryPropertyImpl::getType();
	}
}

PropertyAction *  IndirectRepositoryProperty::getAction(string name)
{
	if(rp_last){
		return rp_last->getAction(name);
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return 0;
	}
}

list<PropertyAction*> * IndirectRepositoryProperty::getAllActions()
{
	if(rp_last){
		return rp_last->getAllActions();
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
		return 0;
	}
}

void IndirectRepositoryProperty::registerAction(string name, PropertyAction *a)
{
	if(rp_last){
		rp_last->registerAction(name, a);
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
	}
}

void IndirectRepositoryProperty::add(PObject *o, PObject *oo)
{
	if(rp_last){
		rp_last->add(o, getTrueParent(oo));
	} else {
        qDebug() << QString("IndirectRepositoryProperty::set : invalid state");
	}
}
