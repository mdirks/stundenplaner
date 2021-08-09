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

    list<bookmark*> *getToc();
    void addToToc(bookmark *bm);
    void deleteFromToc(bookmark *bm);

private:
     static bool toc_compare(bookmark *bm1, bookmark *bm2);
private:
    list<lektuerenotiz*> *list_notizen;
    list<bookmark*> *list_bookmarks;
    list<bookmark*> *list_toc;

    lernkartensatz *lks;
    materialsatz *kop;

};

#endif // LEKTUERE_H
