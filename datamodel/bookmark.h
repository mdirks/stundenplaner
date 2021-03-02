#ifndef BOOKMARK_H
#define BOOKMARK_H

#include "orm/transactions/transactionobject.h"

class bookmark : public TransactionObject
{
public:
    bookmark();

    void setZiel(TransactionObject *ref);
    TransactionObject* getZiel();


    void setVerweis(TransactionObject *ref);
    TransactionObject* getVerweis();

    void setPosition(int pos);
    int getPosition();

    void setBeschreibung(string desc);
    string getBeschreibung();

private:
    int m_pos;
    string m_desc;
    TransactionObject *m_ziel;
    TransactionObject *m_verw;
};

#endif // BOOKMARK_H
