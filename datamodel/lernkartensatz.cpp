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
#include "lernkartensatz.h"
#include "lernkarte.h"
#include "lernkartensatzmapper.h"

lernkartensatz::lernkartensatz()
{
	setMapper(lernkartensatzmapper::getInstance());
	list_lernkarten=0;
}


lernkartensatz::~lernkartensatz()
{
}




/*!
    \fn lernkartensatz::getLernkarten()
 */
list<lernkarte*> *lernkartensatz::getLernkarten()
{
	if(list_lernkarten==0){
		list_lernkarten=lernkartensatzmapper::getInstance()->findLernkarten(getID());
	}
	return list_lernkarten;
}


/*!
    \fn lernkartensatz::addToLernkarten(lernkarte *lk)
 */
void lernkartensatz::addToLernkarten(lernkarte *lk)
{
    getLernkarten()->push_back(lk);
}


/*!
    \fn lernkartensatz::deleteFromLernkarten(lernkarte* lk)
 */
void lernkartensatz::deleteFromLernkarten(lernkarte* lk)
{
    getLernkarten()->remove(lk);
}
