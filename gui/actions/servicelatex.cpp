#include "servicelatex.h"
#include "services/reports/latexoutput.h"
#include "gui/base/guiconfig.h"
#include <QDebug>
#include <QFileDialog>

ServiceLatex *ServiceLatex::instance =0;

ServiceLatex::ServiceLatex()
    : GuiService("Latex")
{
    QPixmap pm = GuiConfig::getInstance()->getIcon("ServiceLatex");

    /*
    if(pm.isNull()){
        GuiConfig::getInstance()->selectIcon("ModeLesen");
        pm = GuiConfig::getInstance()->getIcon("ModeLesen");
    }
    */
    setIcon(pm);
}

ServiceLatex* ServiceLatex::getInstance()
{
    if(instance==0)
    {
        instance= new ServiceLatex();

    }
    return instance;
}

void ServiceLatex::setupMode()
{
    //nothing to be done
}


void ServiceLatex::handleObject(PObject *o)
{
    qDebug() << "ServiceLatex : handling object ...";
    if(o){
        QString name = o->getName().c_str();
        //QString filename = QString("/home/mopp/tex/%1.tex").arg(name);
        QString filename = QFileDialog::getSaveFileName();
        LatexOutput *lout = new LatexOutput(name,filename);
        lout->write(o);
        lout->close();
        lout->edit();
    } else {
        qDebug() << "ServiceLatex: WARNING - got invalid object to handle";
    }
}
