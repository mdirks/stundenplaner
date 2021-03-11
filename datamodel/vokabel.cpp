#include "vokabel.h"
#include "vokabelmapper.h"


vokabel::vokabel()
{
    setMapper(vokabelmapper::getInstance());
    m_listBsp=0;
}

string vokabel::getKanji()
{
    return m_kanji;
}

void vokabel::setKanji(string k)
{
    m_kanji=k;
}

string vokabel::getReading()
{
    return m_read;
}

void vokabel::setReading(string r)
{
    m_read=r;
}

string vokabel::getTranslation()
{
    return m_trans;
};

void vokabel::setTranslation(string t)
{
    m_trans=t;
}

list<bspsatz*>* vokabel::getBeispiele()
{
    if(m_listBsp==0){
        m_listBsp = vokabelmapper::getInstance()->findBeispiele(getID());
    }
    return m_listBsp;
}

void vokabel::addToBeispiele(bspsatz *s)
{
    getBeispiele()->push_back(s);
}

void vokabel::deleteFromBeispiele(bspsatz *s)
{
    getBeispiele()->remove(s);
}
