#ifndef SERVICEPDF_H
#define SERVICEPDF_H

#include "gui/guiservice.h"

class ServicePdf : public GuiService
{
public:
    ServicePdf();
    ~ServicePdf();
    void handleObject(PObject *o);
    void setupMode();

    static ServicePdf* getInstance();

private:
    static ServicePdf *instance;
};

#endif // SERVICEPDF_H
