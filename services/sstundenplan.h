//
// C++ Interface: sstundenplan
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SSTUNDENPLAN_H
#define SSTUNDENPLAN_H

#include "datamodel/stundenplaneintrag.h"
#include "datamodel/stundenplantemplateeintrag.h"
#include "datamodel/schultag.h"
#include "datamodel/stundenplan.h"
#include "datamodel/klasse.h"
#include "orm/transactions/transactionobject.h"
#include <list>
#include <map>
#include <set>
#include <ext/hash_map>

using namespace std;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class SStundenplan : public TransactionObject{

public:
    SStundenplan();
    ~SStundenplan();

public:
	//static SStundenplan* getInstance(stundenplan *sp);
	static SStundenplan* getInstance();
	static void close();
	static void setActiveStundenplan(stundenplan* sp);

public:
	void getStunden(QDate date, list<stundenplaneintrag*> *result);
	//schultag*  getSchultag(QDate date);
    	stundenplantemplateeintrag* createTemplateEintrag(int tag, int stunde, klasse *kl=0);
	stundenplaneintrag* createEintrag(stundenplantemplateeintrag*te, QDate date);
	list<stundenplaneintrag*>* getEintraegeForWeek(klasse *kl, QDate date);
    list<stundenplantemplateeintrag*> *getTemplateEintraege();
    void addToTemplateEintraege(stundenplantemplateeintrag* ste);
    void deleteFromTemplateEintraege(stundenplantemplateeintrag* ste);
    list<stundenplaneintrag*>* getEintraege(stundenplantemplateeintrag *te);
	list<stundenplaneintrag*>* getEintraege(QDate date);
	list<stundenplaneintrag*>* getEintraegeForWeek(QDate date);
	stundenplaneintrag* getPrevious(stundenplaneintrag *se);

private:
	void init();
	void initForTemplate(stundenplantemplateeintrag *te);
	void initForEintrag(stundenplaneintrag *eintrag);
    

private:
	static SStundenplan *instance;
	static stundenplan *active_sp;

private:
	map<int, set<stundenplantemplateeintrag*> *>  map_templates;
	//map<QDate, list<stundenplaneintrag*> *> mapEintraege;
	//map<klasse*, map<QDate, list<stundenplaneintrag*> *> > mapEintraegeKlassen;
	map<klasse*, set<stundenplantemplateeintrag*> *> mapTemplatesKlassen;
	list<stundenplantemplateeintrag*> *list_te;
};

#endif
