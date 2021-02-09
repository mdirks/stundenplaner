#ifndef SERVICELATEX_H
#define SERVICELATEX_H

#include "gui/guiservice.h"

class ServiceLatex : public GuiService
{
public:
    ServiceLatex();
    void handleObject(PObject *o);
    static ServiceLatex* getInstance();
    void setupMode();

private:
    static ServiceLatex* instance;
};

#endif // SERVICELATEX_H
