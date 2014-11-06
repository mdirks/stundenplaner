#ifndef LEKTUERENOTIZ_H
#define LEKTUERENOTIZ_H

#include "notiz.h"

class lektuerenotiz : public notiz
{
public:
    lektuerenotiz();

    int getSeite();
    void setSeite(int s);

private:
    int seite;
};

#endif // LEKTUERENOTIZ_H
