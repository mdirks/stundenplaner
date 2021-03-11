#include "vokabelliste.h"
#include "vokabellistemapper.h"

vokabelliste::vokabelliste()
{
    setMapper(vokabellistemapper::getInstance());
    m_listVokabeln=0;
}

list<vokabel*>* vokabelliste::getVokabeln()
{
    if(m_listVokabeln==0){
        m_listVokabeln = vokabellistemapper::getInstance()->findVokabeln(getID());
    }
    return m_listVokabeln;
}

void vokabelliste::addToVokabeln(vokabel *v)
{
    getVokabeln()->push_back(v);
}

void vokabelliste::deleteFromVokabeln(vokabel *v)
{
    getVokabeln()->remove(v);
}
