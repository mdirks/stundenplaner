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
    PObjectDisplayScene(int numRow, int numCol, list<PObject*> *olist=0);
    ~PObjectDisplayScene();

    void setPrototype(PObjectDisplayItem *protoItem);
    void load(list<PObject*> *olist);

private:
    PObjectDisplayItem* protoItem;
    list<PObject*> *olist;
    int itemWidth,itemHeight;
    int numRow, numCol;
};

class PObjectDisplay : public QGraphicsView
{
public:
    PObjectDisplay(QWidget *parent=0, list<PObject*> *olist=0);
    void setObjectList(list<PObject*> *olist);
    void setPrototype(PObjectDisplayItem *protoItem);

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
