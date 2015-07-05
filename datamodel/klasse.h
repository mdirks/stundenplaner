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
#ifndef KLASSE_H
#define KLASSE_H

#include <list>

#include "orm/transactions/transactionobject.h"
#include "stunde.h"
#include "notizholder.h"
#include "schueler.h"
//#include "kursbuch.h"
//#include "stundenplantemplateeintrag.h"

#include "sitzplan.h"
#include "schuljahr.h"

using namespace std;

class stundenplantemplateeintrag;
class sitzplan;
class kursbuch;
class teilleistung;

/**
@author Marcus Dirks
*/
class klasse : /*public TransactionObject,*/ public notizholder
{
public:
    klasse();

    ~klasse();
    list<stunde*>* getStunden();
    void addToStunden(stunde *st);
    void deleteFromStunden(stunde *st);
    list<schueler*> * getSchueler();
    void addToSchueler(schueler *s);
    void deleteFromSchueler(schueler *s);
    list<teilleistung*> *getTeilleistungen();
    void addToTeilleistungen(teilleistung *tl);
    void deleteFromTeilleistungen(teilleistung *tl);
    void addToReihen(reihe *r);
    void deleteFromReihen(reihe *r);
    list<reihe*>* getReihen();
    int getJahrgangsstufe();
    void setJahrgangsstufe(int i);
    string getKursnummer();
    void setKursnummer(string nr);
    string getFach();
    void setFach(string f);



    void setSitzplan(sitzplan *sp);
    sitzplan* getSitzplan();
    list<stundenplantemplateeintrag*> * getStundenplanTemplates();
    void addToStundenplanTemplates(stundenplantemplateeintrag *e);
    void deleteFromStundenplanTemplates(stundenplantemplateeintrag *e);
    kursbuch* getKursbuch();
    void setKursbuch(kursbuch *kb);
    schuljahr* getSchuljahr();
    void setSchuljahr(schuljahr *sj);

private:
     list<stunde*> *list_stunden;
	list<schueler*> *list_schueler;
	list<stundenplantemplateeintrag*> *list_templates;
	list<teilleistung*> *list_teilleistungen;
    list<reihe*> *list_reihen;

    sitzplan* sp;
	kursbuch* kb;
	schuljahr* sj;

    int jhrg;
    string kursnr, fach;

};

#endif
