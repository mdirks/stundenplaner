//
// C++ Interface: schueler
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SCHUELER_H
#define SCHUELER_H

//#include "klasse.h"
#include "notizholder.h"
//#include "note.h"

#include <list>

using namespace std;

class klasse;
class note;
class fehlzeit;
class stundenbewertung;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class schueler : public notizholder {
public:
    schueler();

    ~schueler();
    klasse* getKlasse();
    void setKlasse(klasse* kl);
    list<note*> * getNoten();
    void addToNoten(note *n);
    void deleteFromNoten(note *n);
    string getVorname();
    string getNachname();
    void setNachname(string nname);
    void setVorname(string vname);
    string getTutor();
    void setTutor(string tutor);
    list<fehlzeit*> * getFehlzeiten();
    void addToFehlzeiten(fehlzeit *f);
    void deleteFromFehlzeiten(fehlzeit *);
    string getName();
    list<stundenbewertung*>* getStundenbewertungen();
    void addToStundenbewertungen(stundenbewertung *bew);
    void deleteFromStundenbewertungen(stundenbewertung *bew);


private:
	klasse *kl;
	string vorname,nachname,tutor;
	list<note*> *list_noten;
	list<fehlzeit*> *list_fehlzeiten;
	list<stundenbewertung*> *list_bewertungen;

};

#endif
