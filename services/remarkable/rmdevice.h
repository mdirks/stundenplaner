#ifndef RMDEVICE_H
#define RMDEVICE_H

#include "datamodel/lektuere.h"
#include "datamodel/lektueresatz.h"
#include "rmentry.h"
#include "rmbookmark.h"


#include <QString>
#include <QFile>
#include <QProcess>

#include <list>

using namespace std;

class RmDevice : public QObject
{
Q_OBJECT

public:
    static RmDevice* getInstance();

    void addCollection(QString name, QString parent);
    void addDocument(lektuere *l, lektueresatz *ls=0);
    void addBookmark(bookmark *b);

    list<RmBookmark*>* readBookmarkList(RmDocument *rmd);
    void writeBookmarkList(RmDocument *rmd);

    RmDocument *getDocument(lektuere *l);

private:
    QString findHash(lektuere *l);


private:
    RmDevice();
    void writeMeta();
    void writeXX();

public slots:
    void readRmapiOut();
    void readRmapiErr();
    void readRmsshOut();
    void readRmsshErr();


private:
    static RmDevice* inst;

    QProcess rmapi;
    QProcess rmssh;
};

#endif // RMDEVICE_H
