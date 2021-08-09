#include "pobjectaction.h"

#include "guicreateaction.h"

#include "datamodel/thema.h"
#include "datamodel/lektuerenotiz.h"
#include "datamodel/kopie.h"
#include "datamodel/vokabelliste.h"
#include "datamodel/material.h"

#include "orm/transactions/transactions.h"

#include "services/docstore/docstore.h"
#include "services/remarkable/rmdevice.h"

#include "gui/forms/pobjectdialog.h"


#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

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


ImportToDocStoreAction::ImportToDocStoreAction()
    : PObjectAction("Import to Objectstore")
{

    connect(this,SIGNAL(triggered()),this,SLOT(importToDocStore()));
}

void ImportToDocStoreAction::importToDocStore()
{
    if(PObject *po = getPObject()){
        if(material *m=dynamic_cast<material*>(po)){
            Transactions::getCurrentTransaction()->add(m);

            DocStore *ds = DocStore::getInstance();
            ds->addDocument(m);
        }
    } else {
        qDebug() << "ImportToObjectStoreAction ERROR: object was not set";
    }
}

AddToRemarkableAction::AddToRemarkableAction()
    : PObjectAction("Add to RM")
{
    connect(this,SIGNAL(triggered()),this,SLOT(addToRm()));
}

void AddToRemarkableAction::addToRm()
{
    if(PObject *po = getPObject()){
        if(lektuere *l=dynamic_cast<lektuere*>(po)){
            RmDevice::getInstance()->addDocument(l);
        } else if(bookmark *b=dynamic_cast<bookmark*>(po)){
            RmDevice::getInstance()->addBookmark(b);
        } else {
            qDebug() << QString("AddToRemarkableAction::addToRm(): could not add %1").arg(po->getClassName().c_str());
        }
    } else {
        qDebug() << "ImportToObjectStoreAction ERROR: object was not set";
    }
}

WriteBookmarksToRmAction::WriteBookmarksToRmAction()
    : PObjectAction("Write Bookmarks to RM")
{
    connect(this,SIGNAL(triggered()),this,SLOT(writeToRm()));
}

void WriteBookmarksToRmAction::writeToRm()
{
    if(lektuere *l = dynamic_cast<lektuere*>(getPObject())){
        RmDocument *rmd=RmDevice::getInstance()->getDocument(l);
        list<bookmark*> *list_bm=l->getBookmarks();
        if(rmd && list_bm){
            rmd->setBookmarks(list_bm);
            RmDevice::getInstance()->writeBookmarkList(rmd);
        }

    }
}


FindRmObjectAction::FindRmObjectAction()
    : PObjectAction("Find RMObject")
{
    connect(this,SIGNAL(triggered()),this,SLOT(findRmObject()));
}

void FindRmObjectAction::findRmObject()
{
    if(PObject *po = getPObject()){
        if(lektuere *l=dynamic_cast<lektuere*>(po)){
            RmDocument *rmd = RmDevice::getInstance()->getDocument(l);
            qDebug() << rmd->getHash();

        }
    } else {
        qDebug() << "ImportToObjectStoreAction ERROR: object was not set";
    }
}
