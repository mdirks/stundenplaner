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
#ifndef FEHLZEIT_H
#define FEHLZEIT_H

#include "notizholder.h"
#include "qdatetime.h"
#include "schueler.h"
#include "stundenplaneintrag.h"

#include <string>

using namespace std;
/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class fehlzeit : public notizholder {
public:
    fehlzeit();
    ~fehlzeit();
    QDateTime getBis();
    QDateTime getVon();
    void setBis(QDateTime date);
    void setVon(QDateTime date);
    schueler *getSchueler();
    void setSchueler(schueler*);
    string getBemerkung();
    void setBemerkung(string b);
    bool getEntschuldigt();
    void setEntschuldigt(bool e);
    stundenplaneintrag* getStundenplaneintrag();
    void setStundenplaneintrag(stundenplaneintrag *se);

private:
	QDateTime von,bis;
	schueler *s;
	string bem;
	stundenplaneintrag *se;
	bool is_ent;
};

#endif
