#ifndef POBJECTDISPLAY_H
#define POBJECTDISPLAY_H

#include "datamodel/lernkarte.h"
#include "orm/persistence/pobject.h"
#include "lernkarteviewer.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsWidget>

#include <list>


class PObjectDisplayItem : public QWidget
{
public:
    virtual PObjectDisplayItem* createInstance(PObject *o)=0;
};




class PObjectDisplayScene : public QGraphicsScene
{
public:
    PObjectDisplayScene(list<PObject*> *olist=0,int numRow=-1, int numCol=-1);
    ~PObjectDisplayScene();

    void setPrototype(PObjectDisplayItem *protoItem);
    void load(list<PObject*> *olist);
    void setLayout(int ncol,int nrow);


private:
    void reload();

private:
    list<PObject*> *olist;


    PObjectDisplayItem* protoItem;
    int itemWidth,itemHeight;
    int numRow, numCol;

};

class PObjectDisplay : public QGraphicsView
{
Q_OBJECT

public:
    PObjectDisplay(QWidget *parent=0, int ncol=-1,int nrow=-1,bool addable=false);
    PObjectDisplay(list<PObject*> *olist, QWidget *parent=0, int ncol=-1,int nrow=-1,bool addable=false);
    PObjectDisplay(string className,QWidget *parent=0,int ncol=-1,int nrow=-1,bool addable=false);
    PObjectDisplay(AbstractMapper *mapper, QWidget *parent=0,int ncol=-1,int nrow=-1, bool addable=true);
    PObjectDisplay(RepositoryProperty *prop, PObject *parentObject=0, QWidget *parent=0,int ncol=-1,int nrow=-1,bool addable=true);

    void setObjectList(list<PObject*> *olist);
    void setParentObject(PObject *po);

    void setPrototype(PObjectDisplayItem *protoItem);
    void setLayout(int ncol,int nrow);

public slots:
    void addElement();

private:
    list<PObject*> *olist;
    RepositoryProperty *prop;
    PObject *parentObject;
    AbstractMapper *mapper;
    string typeName;

    PObjectDisplayScene *scene;
};



class LernkarteDisplayItem : public PObjectDisplayItem
{
public:
    LernkarteDisplayItem(lernkarte *lk=0);
    PObjectDisplayItem* createInstance(PObject *o);

private:
    lernkarte *lk;
    LernkarteViewer *viewer;
};



#endif // POBJECTDISPLAY_H
