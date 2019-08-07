#include "servicepdf.h"

#include "gui/base/guiconfig.h"
#include "services/reports/latexoutput.h"

#include <QString>
#include <QPixmap>
#include <QFileDialog>


ServicePdf* ServicePdf::instance=0;

ServicePdf::ServicePdf()
    : GuiService("Pdf")
{
    QPixmap pm = GuiConfig::getInstance()->getIcon("ServicePdf");

    setIcon(pm);
}

ServicePdf::~ServicePdf()
{

}

ServicePdf* ServicePdf::getInstance()
{
    if(!instance){
        instance = new ServicePdf();
    }
    return instance;
}


void ServicePdf::handleObject(PObject *o)
{
    qDebug() << "ServicePdf : handling object ...";
    if(teilleistung *tl=dynamic_cast<teilleistung*>(o)){
        QString name = tl->getName().c_str();
        //QString filename = QString("/home/mopp/tex/%1.tex").arg(name);
        QString filename = QFileDialog::getSaveFileName();
        LatexOutput *lout = new LatexOutput(name,filename);
        lout->write_report(tl);
        lout->close();
        lout->edit();
    } else {
        qDebug() << "ServicePdf: WARNING - got invalid object to handle";
    }
}
