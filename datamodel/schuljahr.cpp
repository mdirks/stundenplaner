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
#include "schuljahr.h"

#include "schuljahrmapper.h"

schuljahr::schuljahr()
{
	setMapper ( schuljahrmapper::getInstance() );
	list_ferientage=0;
	list_klassen=0;
	list_ferien=0;
	sp1=0;
	sp2=0;
}


schuljahr::~schuljahr()
{
}


// list<ferientag*>* schuljahr::getFerientage()
// {
// 	if ( !list_ferientage )
// 	{
// 		list_ferientage = ( list<ferientag*>* ) schuljahrmapper::getInstance()->findFerientage ( getID() );
// 	}
// 	return list_ferientage;
// }
// 
// void schuljahr::addToFerientage ( ferientag *tag )
// {
// 	getFerientage()->push_back ( tag );
// }
// 
// void schuljahr::deleteFromFerientage ( ferientag *tag )
// {
// 	getFerientage()->remove ( tag );
// }

stundenplan* schuljahr::getStundenplana()
{
	if ( !sp1 )
	{
		sp1= ( stundenplan* ) schuljahrmapper::getInstance()->findReference ( "Stundenplana",getID() );
	}
	return sp1;
}

void schuljahr::setStundenplana ( stundenplan *sp )
{
	this->sp1=sp;
}

stundenplan* schuljahr::getStundenplan2()
{
	if ( !sp2 )
	{
		sp2= ( stundenplan* ) schuljahrmapper::getInstance()->findReference ( "Stundenplan2",getID() );
	}
	return sp2;
}

void schuljahr::setStundenplan2 ( stundenplan *sp )
{
	this->sp2 = sp;
}


list<klasse*> *schuljahr::getKlassen()
{
	if(!list_klassen){
		list_klassen = (list<klasse*>*) schuljahrmapper::getInstance()->findKlassen(getID());
	}
	return list_klassen;
}

void schuljahr::addToKlassen(klasse *kl)
{
	getKlassen()->push_back(kl);
}

void schuljahr::deleteFromKlassen(klasse *kl)
{
	getKlassen()->remove(kl);
}

/*!
    \fn schuljahr::addToFerien(ferien *f)
 */
void schuljahr::addToFerien(ferien *f)
{
    getFerien()->push_back(f);
}


/*!
    \fn schuljahr::deleteFromFerien(ferien *f)
 */
void schuljahr::deleteFromFerien(ferien *f)
{
    getFerien()->remove(f);
}


/*!
    \fn schuljahr::getFerien()
 */
list<ferien*>* schuljahr::getFerien()
{
    	if ( !list_ferien)
	{
		list_ferien = ( list<ferien*>* ) schuljahrmapper::getInstance()->findFerien ( getID() );
	}
	return list_ferien;/// @todo implement me
}


/*!
    \fn schuljahr::getVon()
 */
QDate schuljahr::getVon()
{
    return von;
}


/*!
    \fn schuljahr::setBis(QDate date)
 */
void schuljahr::setBis(QDate date)
{
    bis=date;
}


/*!
    \fn schuljahr::setVon(QDate date)
 */
void schuljahr::setVon(QDate date)
{
    von=date;
}


/*!
    \fn schuljahr::getBis()
 */
QDate schuljahr::getBis()
{
    return bis;
}
