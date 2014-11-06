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
#include "meldung.h"
#include "meldungmapper.h"

meldung::meldung()
{
	s=0;
	setMapper(meldungmapper::getInstance());
}


meldung::~meldung()
{
}


/*!
    \fn fehlzeitmeldung::setSchueler(schueler *s)
 */
void meldung::setSchueler(schueler *s)
{
    this->s=s;
}


/*!
    \fn fehlzeitmeldung::getSchueler()
 */
schueler* meldung::getSchueler()
{
	if(s==0){
		s= (schueler*) meldungmapper::getInstance()->findReference("Schueler",getID());
	} 
	return this->s;
}


/*!
    \fn fehlzeitmeldung::getDatum()
 */
QDate meldung::getDatum()
{
    return date;
}


/*!
    \fn fehlzeitmeldung::setDatum(QDate date)
 */
void meldung::setDatum(QDate date)
{
    this->date=date;
}


/*!
    \fn fehlzeitmeldung::getBemerkung()
 */
string meldung::getBemerkung()
{
    return bem;
}


/*!
    \fn fehlzeitmeldung::setBemerkung(string b)
 */
void meldung::setBemerkung(string b)
{
    this->bem=b;
}