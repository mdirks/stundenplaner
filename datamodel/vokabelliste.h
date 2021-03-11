#ifndef VOKABELLISTE_H
#define VOKABELLISTE_H

#include "orm/transactions/transactionobject.h"
#include "vokabel.h"

class vokabelliste : public TransactionObject
{
public:
    vokabelliste();

    list<vokabel*>* getVokabeln();
    void addToVokabeln(vokabel *v);
    void deleteFromVokabeln(vokabel *v);

private:
    list<vokabel*> *m_listVokabeln;
};

#endif // VOKABELLISTE_H
