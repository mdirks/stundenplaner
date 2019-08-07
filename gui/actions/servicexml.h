#ifndef SERVICEXML_H
#define SERVICEXML_H

#include "orm/persistence/pobject.h"
#include "gui/guiservice.h"

class ServiceXml : public GuiService
{
public:
    ServiceXml();
    void handleObject(PObject *o);
    void setupMode();
};

#endif // SERVICEXML_H
