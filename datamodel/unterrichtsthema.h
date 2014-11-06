//
// C++ Interface: unterrichtsthema
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef UNTERRICHTSTHEMA_H
#define UNTERRICHTSTHEMA_H

#include <thema.h>

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class unterrichtsthema : public thema
{
public:
    unterrichtsthema();
    ~unterrichtsthema();
 list<stunde*> *getStunden();
    list<reihe*> *getReihen();
void addToReihen(reihe *r);
    void addToStunden(stunde* st);void deleteFromReihen(reihe * r);void deleteFromStunden(stunde *st);

private:
list<stunde*> *list_stunden;
    list<reihe*> *list_reihen;
    
};

#endif
