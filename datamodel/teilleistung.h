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
#ifndef TEILLEISTUNG_H
#define TEILLEISTUNG_H

#include "orm/transactions/transactionobject.h"

#include <list>
#include <map>

using namespace std;

class klasse;
class schueler;
class note;
/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class teilleistung : public TransactionObject
{

public:
    teilleistung();
    ~teilleistung();
    list<note*>* getNoten();
    void addToNoten(note *n);
    void deleteFromNoten(note *n);
    klasse* getKlasse();
    void setKlasse(klasse *kl);
    note* getNote(schueler *s);
    double getDurchschnitt();
    int getAnzahl(int punkte);
    int getAnzahlNote(int note);

private:
	list<note*> *list_noten;
	klasse *kl;
	map<schueler*,note*> *map_noten;

};

#endif
