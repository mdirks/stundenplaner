#ifndef MATERIALSATZ_H
#define MATERIALSATZ_H

#include "material.h"

#include <list>

using namespace std;


class materialsatz : public TransactionObject
{
public:
    materialsatz();

    list<material*> *getMaterialien();
    void addToMaterialien(material *n);
    void deleteFromMaterialien(material *n);

private:
    list<material*> *list_materialien;
};



#endif // MATERIALSATZ_H
