#ifndef LEKTUERE_H
#define LEKTUERE_H

#include "material.h"
#include "lektuerenotiz.h"
#include "lernkartensatz.h"
#include "materialsatz.h"
#include "bookmark.h"

#include <list>

class lektuere : public material
{
public:
    lektuere();

    list<lektuerenotiz*> *getNotizen();
    void addToNotizen(lektuerenotiz *n);
    void deleteFromNotizen(lektuerenotiz *n);

    void setLernkartensatz(lernkartensatz *ls);
    lernkartensatz* getLernkartensatz();

    void setKopien(materialsatz *ms);
    materialsatz* getKopien();

    list<bookmark*> *getBookmarks();
    void addToBookmarks(bookmark *bm);
    void deleteFromBookmarks(bookmark *bm);

private:
    list<lektuerenotiz*> *list_notizen;
    list<bookmark*> *list_bookmarks;

    lernkartensatz *lks;
    materialsatz *kop;

};

#endif // LEKTUERE_H
