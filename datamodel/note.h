//
// C++ Interface: note
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef NOTE_H
#define NOTE_H

#include "schueler.h"
#include "orm/transactions/transactionobject.h"
#include <string>
#include <qdatetime.h>

using namespace std;
/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class note : public TransactionObject {
public:
    note();

    ~note();
    int getPunkte();
    schueler* getSchueler();
    string getBemerkung();
    void setBemerkung(string bem);
    void setPunkte(int p);
    void setSchueler(schueler *);
    QDateTime getDatum();
    void setDatum(QDateTime d);
    bool  getIsAt();
    bool getIsKlausur();
    void setIsKlausur(bool kl);
    void setIsAt(bool at);

	string getName();

private:
	schueler *s;
	int punkte;
	string bem;
	QDateTime date;
	bool is_kl, is_at;

};

#endif
