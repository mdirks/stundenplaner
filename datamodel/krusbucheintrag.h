//
// C++ Interface: krusbucheintrag
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef KRUSBUCHEINTRAG_H
#define KRUSBUCHEINTRAG_H

#include <qdatetime.h>

#include <string>

#include "orm/transactions/transactionobject.h"
//#include "stundenplaneintrag.h"


using namespace std;
class kursbuch;
class stundenplaneintrag;
/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class krusbucheintrag : public TransactionObject {
public:
    krusbucheintrag();

    ~krusbucheintrag();
    QDate getDatum();
    string getStunde();
    void setDatum(QDate date);
    string getEintrag();
    void setEintrag(string text);
    void setStunde(string st);
    kursbuch* getKursbuch();
    void setKursbuch(kursbuch *kb);
    stundenplaneintrag* getStundenplanEintrag();
    void setStundenplanEintrag(stundenplaneintrag *se);
    string getName();
    string getBemerkung();
    string getDetails();
    void setBemerkung(string bem);
    void setDetails(string det);

private:
	QDate date;
	string st, text, bem, det;
	kursbuch *kb;
	stundenplaneintrag* se;

};

#endif
