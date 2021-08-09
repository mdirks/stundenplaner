#include "rmdevice.h"


#include <QDebug>
#include <QFileInfo>
#include <QRegularExpression>
RmDevice* RmDevice::inst=0;

RmDevice* RmDevice::getInstance()
{
    if(inst==0){
        inst=new RmDevice();
    }
    return inst;
}

RmDevice::RmDevice()
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("RMAPI_AUTH", "http://192.168.0.201:3000");
    env.insert("RMAPI_DOC", "http://192.168.0.201:3000");
    env.insert("RMAPI_CONFIG", "/home/mopp/.rmapi.fake");
    rmapi.setProcessEnvironment(env);
    rmapi.setWorkingDirectory("/home/mopp/dev/remarkable");

    connect(&rmapi,SIGNAL(readyReadStandardError()),this,SLOT(readRmapiErr()));
    connect(&rmapi,SIGNAL(readyReadStandardOutput()),this,SLOT(readRmapiOut()));

    rmapi.start("rmapi",QStringList());

    rmapi.write("cd Stundenplaner\n");
    rmapi.write("ls\n");

    connect(&rmssh,SIGNAL(readyReadStandardError()),this,SLOT(readRmsshErr()));
    //connect(&rmssh,SIGNAL(readyReadStandardOutput()),this,SLOT(readStandardOut()));

    connect(&rmssh, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exitCode, QProcess::ExitStatus exitStatus){ qDebug() << "Rmssh restarting ...";
        rmssh.start("ssh", QStringList() << "root@remarkable");
        rmssh.write("cd .local/share/remarkable/xochitl \n");});

    rmssh.start("ssh", QStringList() << "root@remarkable");
    rmssh.write("cd .local/share/remarkable/xochitl \n");


}

void RmDevice::addCollection(QString name, QString parent)
{
    /* add required files to FS
     * writeMeta
     * writeXX
     */
}

void RmDevice::readRmapiErr()
{
    qDebug() << rmapi.readAllStandardError();
}

void RmDevice::readRmapiOut()
{
    qDebug() << rmapi.readAllStandardOutput();
}

void RmDevice::readRmsshErr()
{
    qDebug() << rmapi.readAllStandardError();
}

void RmDevice::readRmsshOut()
{
    qDebug() << rmapi.readAllStandardOutput();
}


void RmDevice::addDocument(lektuere *l, lektueresatz *ls)
{
    QString fileName = l->getFileName().c_str();
    fileName=fileName.replace(" ","\\ ");
    QString cpString = QString("put %1 \n").arg(fileName);

    qDebug() << cpString;
    rmapi.write(cpString.toUtf8());
}

void RmDevice::addBookmark(bookmark *b)
{
    lektuere *l=dynamic_cast<lektuere*>(b->getZiel());
    if(l){
        RmDocument *rmd = getDocument(l);
        if(rmd){
            QString pagen = QString("%1").arg(b->getPosition());
            QString name = b->getName().c_str();
            rmd->addToBookmarks(pagen,name);
            writeBookmarkList(rmd);
        }
    }
}

RmDocument* RmDevice::getDocument(lektuere *l)
{
    RmDocument *res=0;
    QString h = findHash(l);
    if(h!=""){
        res=new RmDocument(h);
    }
    return res;
}

list<RmBookmark*>* RmDevice::readBookmarkList(RmDocument *rmd)
{
    QString hash = rmd->getHash();
    QString cmd=QString("less %1.bookm \n").arg(hash);

    qDebug() << cmd;
    rmssh.write(cmd.toUtf8());

    rmssh.waitForReadyRead();

    QString res = rmssh.readAllStandardOutput();

    qDebug() << res;

    //QStringList resl=res.split(",");

    //QRegularExpression re("\"(\\d+)\":{(\"\\w+\":\"[\\w,\\d,\\s]+\")}");
    QRegularExpression re("\"(\\d+)\":({[^}]+})");
    QRegularExpressionMatchIterator mai=re.globalMatch(res);
    list<RmBookmark*> *bmList=new list<RmBookmark*>();
    while(mai.hasNext()){
        QRegularExpressionMatch ma=mai.next();
        qDebug() << ma.captured(1) << ma.captured(2);
        RmBookmark *bm=new RmBookmark();
        bm->setPageNumber(ma.captured(1));
        bm->setDescription(ma.captured(2));
        bmList->push_back(bm);
    }

    return bmList;

}

void RmDevice::writeBookmarkList(RmDocument *rmd)
{
    list<RmBookmark*> *bml = rmd->getBookmarks();
    QString hash=rmd->getHash();
    QString entryList("{");
    for(list<RmBookmark*>::iterator it=bml->begin(); it != bml->end(); ){
        RmBookmark *rmb = *it;
        QString entry=QString("\"%1\":%2").arg(rmb->getPageNumber()).arg(rmb->getDescription());
        it++;
        if(it != bml->end()) entry=entry.append(",");
        entryList=entryList.append(entry);
    }
    entryList=entryList.append("}");

    qDebug() << "new Bookmarklist: " << entryList;

    QString cmd=QString("echo '%1' > %2.bookm \n").arg(entryList).arg(hash);
    //cmd=cmd.replace("\"","""");

    qDebug() << cmd;

    rmssh.write(cmd.toUtf8());
}

QString RmDevice::findHash(lektuere *l)
{
    QString fileName = l->getFileName().c_str();
    QFileInfo info(fileName);
    fileName = info.baseName();
    //fileName=fileName.replace(" ","\ ");
    QString cpString = QString("grep \"%1\" *.metadata\n").arg(fileName);

    qDebug() << cpString;
    rmssh.write(cpString.toUtf8());

    rmssh.waitForReadyRead();

    QString res = rmssh.readAllStandardOutput();
    res = res.remove(QRegExp("\.metadata.+"));

    return res;
}

void RmDevice::writeMeta()
{

}

void RmDevice::writeXX()
{

}
