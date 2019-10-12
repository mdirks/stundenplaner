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
    PObjectDisplayItem* protoItem;
    list<PObject*> *olist;
    int itemWidth,itemHeight;
    int numRow, numCol;
};

class PObjectDisplay : public QGraphicsView
{
public:
    PObjectDisplay(QWidget *parent=0, list<PObject*> *olist=0,int ncol=-1,int nrow=-1);
    void setObjectList(list<PObject*> *olist);
    void setPrototype(PObjectDisplayItem *protoItem);
    void setLayout(int ncol,int nrow);

private:
    list<PObject*> *olist;
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
