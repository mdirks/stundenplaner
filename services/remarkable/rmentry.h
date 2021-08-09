#ifndef RMENTRY_H
#define RMENTRY_H

#include "rmbookmark.h"
#include "datamodel/bookmark.h"

#include <QString>
#include <list>

using namespace std;

class RmEntry
{
public:
    RmEntry(QString hash);
    QString getHash(){return m_hash;};

private:
    QString m_hash;
};

class RmCollection : public RmEntry
{

public:
    RmCollection(QString hash);

};

class RmDocument : public RmEntry
{
public:
    RmDocument(QString hash);

    list<RmBookmark*>* getBookmarks();
    void setBookmarks(list<RmBookmark*> *list_rmbm);
    void setBookmarks(list<bookmark*> *list_bm);

    void addToBookmarks(QString pagen, QString descr);
    void addToBookmarks(RmBookmark *bm);

    void deleteFromBookmarks(QString pagen, QString descr);
    void deleteFromBookmarks(RmBookmark *bm);


private:
    list<RmBookmark*> *list_bm;

};

#endif // RMENTRY_H
