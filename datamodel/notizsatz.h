#ifndef NOTIZSATZ_H
#define NOTIZSATZ_H

#include "notiz.h"
#include "orm/transactions/transactionobject.h"

#include <list>

using namespace std;


class notizsatz : public TransactionObject
{
public:
    notizsatz();

    list<notiz*> *getNotizen();
    void addToNotizen(notiz *n);
    void deleteFromNotizen(notiz *n);

private:
    list<notiz*> *list_notizen;
};

#endif // NOTIZSATZ_H
