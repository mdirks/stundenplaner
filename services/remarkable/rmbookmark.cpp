#include "rmbookmark.h"

RmBookmark::RmBookmark()
{

}

RmBookmark::RmBookmark(QString pn, QString de)
    : pagen(pn), descr(de)
{

}

void RmBookmark::setPageNumber(QString pn)
{
    pagen=pn;
}

void RmBookmark::setPageNumber(int pn)
{
    pagen=QString("%1").arg(pn);
}

QString RmBookmark::getPageNumber()
{
    return pagen;
}

void RmBookmark::setName(QString d)
{
    descr=QString("{\"name\":\"%1\"}").arg(d);
}


void RmBookmark::setDescription(QString de)
{
    descr=de;
}

QString RmBookmark::getDescription()
{
    return descr;
}
