#include "rmentry.h"
#include "rmdevice.h"

RmEntry::RmEntry(QString hash)
    : m_hash(hash)
{

}


RmCollection::RmCollection(QString hash)
    : RmEntry(hash)
{

}

RmDocument::RmDocument(QString hash)
    : RmEntry(hash)
{
    list_bm=0;

}

void RmDocument::addToBookmarks(RmBookmark *bm)
{
    getBookmarks()->push_back(bm);
}

list<RmBookmark*>* RmDocument::getBookmarks()
{
    if(!list_bm){
        list_bm=RmDevice::getInstance()->readBookmarkList(this);
    }
    return list_bm;
}

void RmDocument::addToBookmarks(QString pagen, QString name)
{
    RmBookmark *bm =new RmBookmark();
    bm->setPageNumber(pagen);
    bm->setName(name);
    getBookmarks()->push_back(bm);

}


void RmDocument::deleteFromBookmarks(RmBookmark *bm)
{
    getBookmarks()->remove(bm);
}

void RmDocument::deleteFromBookmarks(QString pagen, QString descr)
{
    getBookmarks();
    for(list<RmBookmark*>::iterator it=list_bm->begin();it!=list_bm->end(); it++)
    {
        RmBookmark *bm=*it;
        if(bm->getPageNumber() == pagen && bm->getDescription() == descr){
            list_bm->remove(bm);
        }
    }
}

void RmDocument::setBookmarks(list<RmBookmark *> *list_rmbm)
{
    list_bm=list_rmbm;
}

void RmDocument::setBookmarks(list<bookmark *> *list_bm)
{
    list<RmBookmark*> *list_rmbm=new list<RmBookmark*>();
    for(list<bookmark*>::iterator it=list_bm->begin(); it!=list_bm->end(); it++){
        bookmark *bm=*it;
        RmBookmark *rmbm = new RmBookmark();
        rmbm->setName(bm->getName().c_str());
        rmbm->setPageNumber(bm->getPosition());
        list_rmbm->push_back(rmbm);
    }
    setBookmarks(list_rmbm);
}
