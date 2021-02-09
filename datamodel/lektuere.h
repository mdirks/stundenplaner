#ifndef LEKTUERE_H
#define LEKTUERE_H

#include "material.h"
#include "lektuerenotiz.h"
#include "lernkartensatz.h"
#include "materialsatz.h"

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

private:
    list<lektuerenotiz*> *list_notizen;

    lernkartensatz *lks;
    materialsatz *kop;
};

#endif // LEKTUERE_H
