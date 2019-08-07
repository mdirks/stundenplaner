#include "lektuerenotiz.h"

#include "lektuerenotizmapper.h"

lektuerenotiz::lektuerenotiz()
    : notiz()
{
    setMapper(lektuerenotizmapper::getInstance());
    seite=0;
}


void lektuerenotiz::setSeite(int s)
{
    seite = s;
}

int lektuerenotiz::getSeite()
{
    return seite;
}
