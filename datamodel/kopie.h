#ifndef KOPIE_H
#define KOPIE_H

#include "material.h"
#include "lektuere.h"


class kopie : public material
{
public:
    kopie();

    lektuere* getLektuere();
    void setLektuere(lektuere *l);

    int getPosition();
    void setPosition(int p);

private:
    lektuere* m_l;
    int m_p;
};

#endif // KOPIE_H
