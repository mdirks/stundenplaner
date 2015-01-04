#include "pobjectdisplay.h"

#include <QHBoxLayout>
#include <QGraphicsProxyWidget>

//Jup funktioniert auch mobil

PObjectDisplay::PObjectDisplay(QWidget *parent,list<PObject*> *olist)
    : QGraphicsView(parent)
{
    this->olist=olist;
    this->scene = new PObjectDisplayScene(5,4,olist);
    setScene(scene);
}

void PObjectDisplay::setPrototype(PObjectDisplayItem *protoItem)
{
    scene->setPrototype(protoItem);
}

void PObjectDisplay::setObjectList(list<PObject*> *olist)
{
    scene->clear();
    this->olist=olist;
    if(olist){
        scene->load(olist);
    }
}



PObjectDisplayScene::PObjectDisplayScene(int nr, int nc, list<PObject*> *olist)
    : numRow(nr), numCol(nc), QGraphicsScene(0,0,1200,800)
{

    if(olist){
        load(olist);
    }
}

PObjectDisplayScene::~PObjectDisplayScene()
{
}


void PObjectDisplayScene::setPrototype(PObjectDisplayItem *protoItem)
{
    this->protoItem = protoItem;
    QGraphicsProxyWidget *pitem= addWidget(protoItem);
    itemWidth=pitem->size().width();
    itemHeight = pitem->size().height();
    numRow = this->height()/itemHeight;
    numCol = this->width()/itemWidth;
    removeItem(pitem);
}


void PObjectDisplayScene::load(list<PObject*> *olist)
{
    int r=0;
    int c=0;

    for(list<PObject*>::iterator it = olist->begin(); it!=olist->end(); it++){
            PObject *o=*it;
            if(o){
                PObjectDisplayItem *item = protoItem->createInstance(o);
                if(item){
                    item->setContentsMargins(0,0,0,0);
                    QGraphicsProxyWidget *pitem= addWidget(item);
                    //pitem->prepareGeometryChange();
                    pitem->setPos(c*(itemWidth),r*(itemHeight));
                    c+=1;
                    if(c>=numCol){
                        r+=1;
                        c=0;
                    }
                }
            }

    }
}


LernkarteDisplayItem::LernkarteDisplayItem(lernkarte *lk)
    : PObjectDisplayItem()
{
    this->lk = lk;
    viewer = new LernkarteViewer(this,LernkarteViewer::Stacked);
    viewer->setStyleSheet("background-color:blue;");
    viewer->setContentsMargins(0,0,0,0);
    viewer->setLernkarte(lk);
    QHBoxLayout *l = new QHBoxLayout(this);
    l->addWidget(viewer);
    l->setSpacing(0);
    l->setContentsMargins(0,0,0,0);

    this->setLayout(l);


}

PObjectDisplayItem* LernkarteDisplayItem::createInstance(PObject *o)
{
    PObjectDisplayItem *item=0;
    lernkarte *lk = dynamic_cast<lernkarte*>(o);
    if(lk){
        item = new LernkarteDisplayItem(lk);
    }
    return item;
}
