#include "servicexml.h"
#include "gui/base/guiconfig.h"
#include "services/xml-export/xmlfactory.h"

#include <QDebug>
#include <QFileDialog>
#include <QProcess>
//#include <KRun>

ServiceXml::ServiceXml()
    : GuiService("XML")
{
     QPixmap pm = GuiConfig::getInstance()->getIcon("ServiceXml");
     setIcon(pm);
}


void ServiceXml::handleObject(PObject *o)
{
    qDebug() << "ServiceXml: handling object ...";
    if(o){
        list<PObject*> *olist = new list<PObject*>();
        olist->push_back(o);

        QString filename = QFileDialog::getSaveFileName();

        XmlFactory *fact = XmlFactory::getInstance();
        fact->exportObjectList(filename,olist);

        qDebug() << "ServiceXml: done exporting!";
        QProcess *p = new QProcess(this);
        p->start(QString("kate %1").arg(filename));
    } else {
        qDebug() << "ServiceXml: WARNING - got invalid object to handle";
    }
}

void ServiceXml::setupMode()
{
    qDebug() << "ServiceXml::setupMode() ...";

    QString filename = QFileDialog::getOpenFileName();
    list<PObject*> *olist=new list<PObject*>();

    XmlFactory *fact = XmlFactory::getInstance();
    fact->processFile(filename,olist);

    qDebug() << "ServiceXml::setupMode() -- DONE !";
}
