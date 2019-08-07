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
#include "guiobject.h"
#include "guiobjectmapper.h"
#include "themamapmapper.h"

GuiObject* GuiObject::instance = 0;


GuiObject* GuiObject::getInstance()
{
	if(!instance){
		instance = (GuiObject*) GuiObjectmapper::getInstance()->getSingletonInstance();
	}
	return instance;
}


GuiObject::GuiObject()
{
	dashBoard = 0;
	setMapper(GuiObjectmapper::getInstance());
}


GuiObject::~GuiObject()
{
}




/*!
    \fn GuiObject::setDashBoard(ThemaMap *map)
 */
void GuiObject::setDashBoard(ThemaMap *map)
{
    dashBoard = map;
}


/*!
    \fn GuiObject::getDashBoard()
 */
ThemaMap*  GuiObject::getDashBoard()
{
	if(!dashBoard){
		dashBoard = (ThemaMap*) GuiObjectmapper::getInstance()->findReference("DashBoard",getID());
		if(!dashBoard){
			dashBoard = (ThemaMap*) ThemaMapmapper::getInstance()->create();
			dashBoard->setName("DashBoard");
			qDebug("Created new DashBoard");
		}
	} 
	return dashBoard;
	
}
