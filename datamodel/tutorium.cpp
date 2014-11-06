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
#include "tutorium.h"
#include "tutoriummapper.h"

tutorium::tutorium()
{
	list_fzm = 0;
	kl = 0;
	setMapper(tutoriummapper::getInstance());
}


tutorium::~tutorium()
{
}

klasse* tutorium::getKlasse()
{
	if(kl==0){
		kl= (klasse*) tutoriummapper::getInstance()->findReference("Klasse",getID());
	} 
	return kl;
}

void tutorium::setKlasse(klasse* kl)
{
	this->kl = kl;
}

void tutorium::addToFehlzeitmeldungen(fehlzeitmeldung *fzm)
{
	getFehlzeitmeldungen()->push_back(fzm);
}

void tutorium::deleteFromFehlzeitmeldungen(fehlzeitmeldung *fzm)
{
	getFehlzeitmeldungen()->remove(fzm);
}

list<fehlzeitmeldung*> *tutorium::getFehlzeitmeldungen()
{
	if(list_fzm == 0){
		list_fzm = tutoriummapper::getInstance()->findFehlzeitmeldungen(getID());
    	}
	return list_fzm;
}