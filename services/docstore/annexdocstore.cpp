#include "annexdocstore.h"

#include <QProcess>
#include <QFile>
#include <QDebug>
#include <QDir>

AnnexDocStore::AnnexDocStore(QString name, QString dir)
{
    storeName = name;
    baseDir = dir;
}


AnnexDocStore *AnnexDocStore::getAnnexDocStore(QString name, QString dir)
{
    AnnexDocStore *store=new AnnexDocStore(name,dir);


    QDir("/").mkpath(DocStore::getDirectory());

    QProcess p;
    p.setWorkingDirectory(DocStore::getDirectory());
    p.start("/usr/bin/git", QStringList()<<"init");
    if(!p.waitForFinished()){
        qDebug() << "Git FAILED";
        return 0;
    }

    p.start("/usr/bin/git", QStringList()<<"annex init");
    if(!p.waitForFinished()){
        qDebug() << "Git annex FAILED";
        return 0;
    }


    return store;
}


bool AnnexDocStore::addDocument(material *m) //m should have been added to transaction by client
{
    QFile *file=m->getFile();

    QString fn = QFileInfo(*file).fileName();
    QString newName(DocStore::getDirectory().append("/").append(fn));


    if(file->copy(newName)){
        qDebug() << "renamed file to" << newName;
        m->setFileName(newName.toStdString()); //m should have been added to transaction by client
    } else {
        qDebug()<<"FAILED to rename file";
        return false;
    }

    /*
    QProcess::execute("cd",QStringList() << baseDir);
    QProcess::execute("cp",QStringList() << file.fileName() << " . ");
    QProcess::execute("git",QStringList() << "annex add " << ". ");
    QProcess::execute("git",QStringList() << "commit -a -m added");
    */

    QProcess p;
    p.setWorkingDirectory(DocStore::getDirectory());
    p.start("/usr/bin/git", QStringList()<<"annex add " << ". ");
    if(!p.waitForFinished()){
        qDebug() << "git annex add FAILED";
        return false;
    }

    p.start("/usr/bin/git", QStringList()<<"commit -a -m added");
    if(!p.waitForFinished()){
        qDebug() << "git commit FAILED";
        return false;
    }

    return true;
}


