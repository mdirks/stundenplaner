#include "kopie.h"

#include "kopiemapper.h"

kopie::kopie()
    : material()
{
    setMapper(kopiemapper::getInstance());
    m_l=0;
    m_p=0;
}

void kopie::setLektuere(lektuere *l)
{
    this->m_l=l;
}

lektuere* kopie::getLektuere()
{
    if(m_l==0){
        m_l = (lektuere*) kopiemapper::getInstance()->findReference("Lektuere",getID());
    }
    return m_l;
}

void kopie::setPosition(int p)
{
    this->m_p=p;
}

int kopie::getPosition()
{
    return m_p;
}
