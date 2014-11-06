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
#include "lernkarte.h"

#include "lernkartemapper.h"

#include <qstring.h>
#include <KUrl>




lernkarte::lernkarte()
{
	setMapper(lernkartemapper::getInstance());
	sourceh="";
	sourcev="";
	comp = false;
}


lernkarte::~lernkarte()
{
}

KUrl lernkarte::getVorn()
{
	return vorn;
}

void lernkarte::setVorn(KUrl vorn)
{
	this->vorn = vorn;
}

KUrl lernkarte::getHinten()
{
	return hinten;
}

void lernkarte::setHinten(KUrl hinten)
{
	this->hinten = hinten;
}



/*!
    \fn lernkarte::getSourceHinten()
 */
string lernkarte::getSourceHinten()
{
    return sourceh;
}


/*!
    \fn lernkarte::getSourceVorn()
 */
string lernkarte::getSourceVorn()
{
    	if(sourcev == ""){
        sourcev=QString("Vorn %1").arg(getID()).toStdString();
	}
	return sourcev;
}


/*!
    \fn lernkarte::setSourceHinten(string sh)
 */
	void lernkarte::setSourceHinten(string sh)
{
    sourceh = sh;
}


/*!
    \fn lernkarte::setSourceVorn(string sv)
 */
void lernkarte::setSourceVorn(string sv)
{
    sourcev=sv;
}

void lernkarte::setCompiled(bool comp)
{
	this->comp=comp;
}

bool lernkarte::getCompiled()
{
	return comp;
}
