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
    store->init();
    return store;
}

void AnnexDocStore::init(){
    QDir("/").mkpath(baseDir);

    QProcess p;
    p.setWorkingDirectory(baseDir);
    p.start("/usr/bin/git", QStringList()<<"init");
    if(!p.waitForFinished()){
        qDebug() << "Git FAILED";
    }

    p.start("/usr/bin/git-annex", QStringList()<<"init");
    if(!p.waitForFinished()){
        qDebug() << "Git annex FAILED";
    }

}

void AnnexDocStore::setLocation(QString locationDirName)
{
    baseDir=locationDirName;
    init();
}


bool AnnexDocStore::addDocument(material *m) //m should have been added to transaction by client
{
    QFile *file=m->getFile();

    QString fn = QFileInfo(*file).fileName();
    QString newName;
    newName=newName.append(baseDir).append("/").append(fn);


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
    p.setWorkingDirectory(baseDir);
    p.start("/usr/bin/git-annex", QStringList()<<"add"<<".");
    if(!p.waitForFinished()){
        qDebug() << "git annex add FAILED in " << baseDir
                    ;
        return false;
    }


    p.start("/usr/bin/git", QStringList()<<"commit"<<"-a"<<"-m"<<"added");
    if(!p.waitForFinished()){
        qDebug() << "git commit FAILED";
        return false;
    }

    return true;
}


