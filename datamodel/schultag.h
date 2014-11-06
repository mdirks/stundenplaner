//
// C++ Interface: schultag
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SCHULTAG_H
#define SCHULTAG_H

#include <qdatetime.h>

#include "notizholder.h"
#include "stundenplaneintrag.h"

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class schultag : public notizholder {
public:
    schultag();
    ~schultag();

    list<stundenplaneintrag*>* getEintraege();
    void addToEintraege(stundenplaneintrag *eintrag);
    void deleteFromEintraege(stundenplaneintrag *eintrag);
    QDateTime getDatum();
    void setDatum(QDateTime date);


private:
	list<stundenplaneintrag*> *list_eintraege;
	QDateTime date;
};

#endif
