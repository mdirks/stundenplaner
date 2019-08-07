#include "materialsatz.h"
#include "materialsatzmapper.h"

materialsatz::materialsatz()
{
    setMapper(materialsatzmapper::getInstance());
    list_materialien=0;
}

list<material*> *materialsatz::getMaterialien()
{
    if(list_materialien==0){
        list_materialien=materialsatzmapper::getInstance()->findMaterialien(getID());
    }
    return list_materialien;
}

void materialsatz::addToMaterialien(material *n)
{
    getMaterialien()->push_back(n);
}

void materialsatz::deleteFromMaterialien(material *n)
{
    getMaterialien()->remove(n);
}
