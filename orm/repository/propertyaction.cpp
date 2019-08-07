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
#include "propertyaction.h"

PropertyAction::PropertyAction(QString text)
    : QAction(0)
{
	connect(this,SIGNAL(activated()),this,SLOT(perform()));
}


PropertyAction::~PropertyAction()
{
}


void PropertyAction::setProperty(RepositoryProperty *rp)
{
	this->rp = rp;
}



/*!
    \fn PropertyAction::setPropertyObject(PObject *o)
 */
 void PropertyAction::setParentObject(PObject *o)
{
    this->o = o;
}


/*!
    \fn PropertyAction::getName()
 */
string PropertyAction::getName()
{
    return string("unknown");
}
