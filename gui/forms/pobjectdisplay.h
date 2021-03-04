#ifndef POBJECTDISPLAY_H
#define POBJECTDISPLAY_H

#include "datamodel/lernkarte.h"
#include "datamodel/material.h"
#include "orm/persistence/pobject.h"
#include "lernkarteviewer.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsWidget>

#include <list>


class PObjectDisplayItem
{
public:
    PObjectDisplayItem(PObject *o){m_o=o;};

    virtual QGraphicsItem* createInstance(PObject *o,QGraphicsScene *s, int px, int py)=0;
    QSizeF getIdealSize(){return idealSize;};
    void setIdealSize(QSizeF iS){idealSize=iS;};
    QSizeF getActualSize(){return actualSize;};
    void setActualSize(QSizeF aS){actualSize=aS;};

    PObject* getObject(){return m_o;};


private:
    QSizeF idealSize, actualSize;
    PObject *m_o;
};




class PObjectDisplayScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PObjectDisplayScene(list<PObject*> *olist=0,int numRow=-1, int numCol=-1);
    ~PObjectDisplayScene();

    void setPrototype(PObjectDisplayItem *protoItem);
    void load(list<PObject*> *olist);
    void setLayout(int ncol,int nrow);

    void deleteItem(PObjectDisplayItem *item);



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

    PObjectDisplayItem* currentItem();

public slots:
    void addElement();
    void removeClickedItem();

protected:
    void contextMenuEvent(QContextMenuEvent *ev);
    QMenu* getPopupMenu();

private:
    list<PObject*> *olist;
    RepositoryProperty *prop;
    PObject *parentObject;
    AbstractMapper *mapper;
    string typeName;

    PObjectDisplayScene *scene;
    PObjectDisplayItem *clickedItem;
};



class LernkarteDisplayItem : public PObjectDisplayItem, public QWidget
{
public:
    LernkarteDisplayItem(lernkarte *lk=0);
    QGraphicsItem* createInstance(PObject *o, QGraphicsScene *s, int px, int py);

private:
    lernkarte *lk;
    LernkarteViewer *viewer;
};

class MaterialDisplayItem : public PObjectDisplayItem, public QGraphicsPixmapItem
{

public:
    MaterialDisplayItem(material *m=0);
    QGraphicsItem* createInstance(PObject *o, QGraphicsScene *s, int px, int py);


private:
    material *m;

};

#endif // POBJECTDISPLAY_H
