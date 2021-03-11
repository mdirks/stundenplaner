#ifndef VOKABEL_H
#define VOKABEL_H


#include "orm/transactions/transactionobject.h"
class bspsatz;

class vokabel : public TransactionObject
{
public:
    vokabel();

    string getKanji();
    void setKanji(string k);
    string getReading();
    void setReading(string r);
    string getTranslation();
    void setTranslation(string t);

    list<bspsatz*>* getBeispiele();
    void addToBeispiele(bspsatz *s);
    void deleteFromBeispiele(bspsatz *s);

private:
    string m_kanji, m_read, m_trans;
    list<bspsatz*> *m_listBsp;
};

#endif // VOKABEL_H
