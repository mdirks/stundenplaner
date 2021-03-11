#include "pobjectaction.h"
#include "gui/forms/pobjectdialog.h"
#include "datamodel/thema.h"
#include "datamodel/lektuerenotiz.h"
#include "datamodel/kopie.h"
#include "datamodel/vokabelliste.h"
#include "orm/transactions/transactions.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "guicreateaction.h"

PObjectAction::PObjectAction(const QString &text)
    : QAction(text)
{
    this->po=0;
}

void PObjectAction::setPObject(PObject *o)
{
    this->po=o;
}

PObject* PObjectAction::getPObject()
{
    return this->po;
}


AddToThemaAction::AddToThemaAction(const QString &text)
    : PObjectAction(text)
{
    connect(this, &QAction::triggered, this, &AddToThemaAction::addToThema);
}

void AddToThemaAction::addToThema()
{
    if(PObject *o = getPObject()){
        thema *t= (thema*) PObjectDialog::choosePObject("thema");
        string ocl = o->getClassName();
        if(ocl == "notiz"){
            t->addToNotizen((notiz*) o);
        } else if (ocl == "lektuerenotiz"){
            t->addToNotizen((lektuerenotiz*) o);
        } else if (ocl == "material"){
            t->addToMaterialien((material*) o);
        } else if (ocl == "kopie"){
            t->addToMaterialien((kopie*) o);
        } else if (ocl == "bookmark"){
            t->addToBookmarks((bookmark*) o);
        }
        qDebug() << QString("AddToThemaAction: added %1 (%2) to %3").arg(o->getName().c_str()).arg(ocl.c_str()).arg(t->getName().c_str());
    }
}

VocImportAction::VocImportAction(const QString &text)
    : PObjectAction(text)
{
    connect(this,&QAction::triggered, this, &VocImportAction::importFromFile);
}

void VocImportAction::importFromFile()
{
    if(vokabelliste* vlist = dynamic_cast<vokabelliste*>(getPObject())){
        QString filename = QFileDialog::getOpenFileName();
        bool con = true;
        while(con){
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
            return;
        }
        QTextStream in(&file);
        QString line = in.readLine();
        QRegExp reg(line);
        qDebug() << QString("Using pattern: ") << line;
        int n=0;
        bool stop=false;
        while(!in.atEnd() & !stop) {
             line = in.readLine();
             if(reg.indexIn(line)!=-1){
                vokabel *v=(vokabel*) GuiCreateAction::getInstance()->create("vokabel");

                v->setKanji(reg.cap(1).toStdString());
                v->setReading(reg.cap(2).toStdString());
                v->setTranslation(reg.cap(3).toStdString());

                Transactions::getCurrentTransaction()->add(vlist);
                vlist->addToVokabeln(v);
                n++;
            } else {
                if(QMessageBox::question(0,"Invalid entry:",QString(line)+"\n continue?")==QMessageBox::No){
                    stop=true;
                }
                //qDebug() << QString("invalid entry: ") << line;
            }
        }

        file.close();
        QString res("Found %1 entries. - Retry with new pattern?");
        res=res.arg(n);
        if(QMessageBox::question(0,"Weiter ?", res)==QMessageBox::Yes){
            con=true;
        } else {
            con=false;
        }
        }
    }
}
