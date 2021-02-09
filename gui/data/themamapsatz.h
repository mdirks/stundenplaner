#ifndef THEMAMAPSATZ_H
#define THEMAMAPSATZ_H

#include "themamap.h"

#include <list>

using namespace std;

class ThemaMapSatz : public TransactionObject
{
public:
    ThemaMapSatz();

    list<ThemaMap*> *getThemaMaps();
    void addToThemaMaps(ThemaMap *tm);
    void deleteFromThemaMaps(ThemaMap *tm);

    list<ThemaMapSatz*> *getChildren();
    void addToChildren(ThemaMapSatz *tms);
    void deleteFromChildren(ThemaMapSatz *tms);

private:
    list<ThemaMap*> *list_themamaps;
    list<ThemaMapSatz*> *list_children;
};




#endif // THEMAMAPSATZ_H
