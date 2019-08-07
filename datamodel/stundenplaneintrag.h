//
// C++ Interface: stundenplaneintrag
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STUNDENPLANEINTRAG_H
#define STUNDENPLANEINTRAG_H

#include <qdatetime.h>

#include "datamodel/stunde.h"
#include "datamodel/klasse.h"
#include "datamodel/krusbucheintrag.h"
#include "datamodel/notizholder.h"
#include "datamodel/stundenbewertung.h"
#include "datamodel/fehlzeit.h"

class stundenplantemplateeintrag;
/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class stundenplaneintrag : public notizholder{
public:
    stundenplaneintrag();

    ~stundenplaneintrag();
    stunde* getStunde();
    krusbucheintrag* getKursbuchEintrag();
    QDate getDatum();
    klasse* getKlasse();

    void setDatum(QDate date);
    void setKursbuchEintrag(krusbucheintrag *e);
    void setStunde(stunde *st);
    void setKlasse(klasse *kl);
    bool getActive();
    void setActive(bool is_active);
    string getVerlauf();
    void setVerlauf(string s);
	
    bool operator<(stundenplaneintrag &eintrag);
    
    string getName();
    void deleteFromBewertungen(stundenbewertung *sb);
    list<stundenbewertung*>* getBewertungen();
    void addToBewertungen(stundenbewertung *sb);
    stundenbewertung* getBewertung(schueler *s);
    list<fehlzeit*>* getFehlzeiten();
    void addToFehlzeiten(fehlzeit *fz);
    void deleteFromFehlzeiten(fehlzeit *fz);
    bool getDoppelstunde();
    void setDoppelstunde(bool d);
    fehlzeit* getFehlzeit(schueler *s);
    stundenplantemplateeintrag* getTemplate();
    void setTemplate(stundenplantemplateeintrag *te);
    int getNrStunde();
    int getTag();
    void setTag(int nt);
    void setNrStunde(int nrs);
    void addFehlzeit(schueler *s);
private:
	stunde *st;
	klasse *kl;
	QDate date;
	krusbucheintrag *ke;
	bool is_active, is_doppel;
	string verlauf;
	int n_st, n_t;
	list<stundenbewertung*> *list_bew;
	list<fehlzeit*> *list_fz;
	map<schueler*, stundenbewertung*> map_bew;
	map<schueler*, fehlzeit*>map_fehl;
	stundenplantemplateeintrag *te;

};

#endif
