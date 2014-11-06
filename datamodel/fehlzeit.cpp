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
#include "fehlzeit.h"
#include "fehlzeitmapper.h"

fehlzeit::fehlzeit()
{
	setMapper(fehlzeitmapper::getInstance());
	s = 0;
	se = 0;
	is_ent = false;
}


fehlzeit::~fehlzeit()
{
}




/*!
    \fn fehlzeit::getBis()
 */
QDateTime fehlzeit::getBis()
{
    return this->bis;
}


/*!
    \fn fehlzeit::getVon()
 */
QDateTime fehlzeit::getVon()
{
    return this->von;
}


/*!
    \fn fehlzeit::setBis(QDate date)
 */
void fehlzeit::setBis(QDateTime date)
{
    this->bis = date;
}


/*!
    \fn fehlzeit::setVon(QDate date)
 */
void fehlzeit::setVon(QDateTime date)
{
    this->von = date;
}

void fehlzeit::setSchueler(schueler *s)
{
	this->s = s;
}

schueler* fehlzeit::getSchueler()
{
	if(s==0){
		s= (schueler*) fehlzeitmapper::getInstance()->findReference("Schueler",getID());
	} 
	return this->s;
}


/*!
    \fn fehlzeit::getBemerkung()
 */
string fehlzeit::getBemerkung()
{
    return this->bem;
}


/*!
    \fn fehlzeit::setBermerkung(string b)
 */
void fehlzeit::setBemerkung(string b)
{
    this->bem = b;
}


/*!
    \fn fehlzeit::getEntschuldigt()
 */
bool fehlzeit::getEntschuldigt()
{
    return this->is_ent;
}


/*!
    \fn fehlzeit::setEntschuldigt(bool e)
 */
void fehlzeit::setEntschuldigt(bool e)
{
    this->is_ent = e;
}


/*!
    \fn fehlzeit::getStundenplaneintrag()
 */
stundenplaneintrag* fehlzeit::getStundenplaneintrag()
{
    	if(!se){
		se = (stundenplaneintrag*) fehlzeitmapper::getInstance()->findReference("Stundenplaneintrag", getID());
	}
	return se;
}


/*!
    \fn fehlzeit::setStundenplaneintrag(stundenplaneintrag *se)
 */
void fehlzeit::setStundenplaneintrag(stundenplaneintrag *se)
{
    this->se = se;
}
