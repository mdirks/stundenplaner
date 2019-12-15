#include "annexdocstore.h"

#include <QProcess>

AnnexDocStore::AnnexDocStore()
{

}


AnnexDocStore *AnnexDocStore::createStore(QString name, QString dir)
{
    AnnexDocStore *store=new AnnexDocStore();

    QProcess::execute("cd",QStringList() << dir);
    QProcess::execute("mkdir",QStringList() << name);
    QProcess::execute("cd",QStringList() << name);

    QProcess::execute("git init", QStringList() << "");
    QProcess::execute("git annex init", QStringList() << "");


}


void AnnexDocStore::addDocument()
{

}
