//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef RELATEACTION_H
#define RELATEACTION_H

#include "datamodel/stunde.h"
#include "datamodel/thema.h"
#include "datamodel/notiz.h"
#include "datamodel/klasse.h"
#include "orm/persistence/pobject.h"

/**
@author Marcus Dirks
*/
class RelateAction{
public:
    RelateAction();

    ~RelateAction();
    bool relate(opo *op, stunde *st);
    bool relate(stunde *st, thema *th);
    bool relate(notiz *n, stunde *st);
    bool relate(stunde *st, klasse *kl);
    bool relate(PObject *o1, PObject *o2);
    
    static RelateAction* getInstance();
    bool relate(schueler *s, platz *p);
 
private:
   
    static RelateAction *instance;

};

#endif
