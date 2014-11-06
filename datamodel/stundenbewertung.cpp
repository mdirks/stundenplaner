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
#include "stundenbewertung.h"
#include "stundenbewertungmapper.h"

stundenbewertung::stundenbewertung()
{
	eintrag=0;
	sch=0;
	fehl=false;
	setMapper(stundenbewertungmapper::getInstance());
}


stundenbewertung::~stundenbewertung()
{
}




/*!
    \fn stundenbewertung::getBewertung()
 */
string  stundenbewertung::getBewertung()
{
    return this->bw;
}


/*!
    \fn stundenbewertung::getStundenplaneintrag()
 */
stundenplaneintrag* stundenbewertung::getStundenplaneintrag()
{
    if(!eintrag){
	eintrag = (stundenplaneintrag*) stundenbewertungmapper::getInstance()->findReference("Stundenplaneintrag",getID());
    }
    return eintrag;
}


/*!
    \fn stundenbewertung::setBewertung(int b)
 */
void stundenbewertung::setBewertung(string b)
{
    this->bw=b;
}


/*!
    \fn stundenbewertung::setStundenplaneintrag(stundenplaneintrag *e)
 */
void stundenbewertung::setStundenplaneintrag(stundenplaneintrag *e)
{
    this->eintrag=e;
}


/*!
    \fn stundenbewertung::getSchueler()
 */
schueler* stundenbewertung::getSchueler()
{
    	if(!sch){
		sch= (schueler*) stundenbewertungmapper::getInstance()->findReference("Schueler",getID());
	}
	
	return this->sch;
}


/*!
    \fn stundenbewertung::setSchueler(schueler *s)
 */
void stundenbewertung::setSchueler(schueler *s)
{
    this->sch = s;
}


/*!
    \fn stundenbewertung::getBemerkung()
 */
string stundenbewertung::getBemerkung()
{
    return this->bem;
}


/*!
    \fn stundenbewertung::setBemerkung(string bem)
 */
void stundenbewertung::setBemerkung(string bem)
{
    this->bem = bem;
}


/*!
    \fn stundenbewertung::getGefehlt()
 */
bool stundenbewertung::getGefehlt()
{
    return fehl;
}


/*!
    \fn stundenbewertung::setGefehlt(bool fehl)
 */
void stundenbewertung::setGefehlt(bool fehl)
{
    this->fehl=fehl;
    if(fehl){
	if(eintrag && sch){
		eintrag-> addFehlzeit(sch);
	}
    }
}
