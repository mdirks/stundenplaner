#ifndef REIHEMAP_H
#define REIHEMAP_H

#include "genericmap.h"
#include "datamodel/reihe.h"


class ReiheMap : public GenericMap
{
public:
    ReiheMap();
    void setReihe(reihe *r);

private:
    reihe *m_r;
};

#endif // REIHEMAP_H
