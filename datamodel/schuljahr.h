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
#ifndef SCHULJAHR_H
#define SCHULJAHR_H

#include "notizholder.h"

class ferientag;
class ferien;
class stundenplan;
class klasse;
/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class schuljahr : public notizholder {
public:
	schuljahr();
	~schuljahr();

// 	list<ferientag*>* getFerientage();
// 	void addToFerientage(ferientag *tag);
// 	void deleteFromFerientage(ferientag *tag);
	stundenplan* getStundenplana();
	void setStundenplana(stundenplan *sp);
	stundenplan* getStundenplan2();
	void setStundenplan2(stundenplan *sp);
	
	list<klasse*> *getKlassen();
	void addToKlassen(klasse *kl);
	void deleteFromKlassen(klasse *kl);
    void addToFerien(ferien *f);
    void deleteFromFerien(ferien *f);
    list<ferien*>* getFerien();
    QDate getBis();
    QDate getVon();
    void setBis(QDate date);
    void setVon(QDate date);

	
private:
	list<ferientag*> *list_ferientage;
	list<klasse*> *list_klassen;
	list<ferien*> *list_ferien;
	stundenplan *sp1, *sp2;
	QDate von,bis;
};

#endif
