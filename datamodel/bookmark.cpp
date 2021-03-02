#include "bookmark.h"
#include "bookmarkmapper.h"

bookmark::bookmark()
{
    setMapper(bookmarkmapper::getInstance());
    m_ziel=0;
    m_verw=0;
    m_pos=-1;
}

void bookmark::setZiel(TransactionObject *z)
{
    m_ziel=z;
}

TransactionObject* bookmark::getZiel()
{
    if(!m_ziel){
        m_ziel = (TransactionObject*) bookmarkmapper::getInstance()->findReference("Ziel",getID());
    }
    return m_ziel;
}

void bookmark::setVerweis(TransactionObject *v)
{
    m_verw=v;
}

TransactionObject* bookmark::getVerweis()
{
    if(!m_verw){
        m_verw = (TransactionObject*) bookmarkmapper::getInstance()->findReference("Verweis",getID());
    }
    return m_verw;
}

void bookmark::setPosition(int pos)
{
    m_pos=pos;
}

int bookmark::getPosition()
{
    return m_pos;
}

void bookmark::setBeschreibung(string desc)
{
    m_desc=desc;
}

string bookmark::getBeschreibung()
{
    return m_desc;
}
