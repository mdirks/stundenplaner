#include "pobjectdisplay.h"

#include <QHBoxLayout>
#include <QGraphicsProxyWidget>
#include <QPushButton>

#include "orm/mapping/mappingcontroler.h"
#include "orm/transactions/transactions.h"
#include "orm/repository/collectionproperty.h"

#include "gui/actions/guicreateaction.h"

//Jup funktioniert auch mobil



PObjectDisplay::PObjectDisplay(QWidget *parent,  int ncol, int nrow,bool addable)
    : QGraphicsView(parent)
{
    olist=0;
    prop=0;
    parentObject=0;
    mapper=0;

    this->scene = new PObjectDisplayScene(olist,ncol,nrow);
    if(addable){
        QPushButton *addButton = new QPushButton("Add",this);
        connect(addButton,SIGNAL(clicked()),this,SLOT(addElement()));
        scene->addWidget(addButton);
    }

    setScene(scene);
    //setSceneRect(0,0,0,0);
}


PObjectDisplay::PObjectDisplay(list<PObject*> *ol, QWidget *parent, int ncol, int nrow,bool addable)
    : QGraphicsView(parent)
{
    olist=ol;
    prop=0;
    parentObject=0;
    mapper=0;

    this->scene = new PObjectDisplayScene(olist,ncol,nrow);

    setScene(scene);
    //setSceneRect(0,0,0,0);
}

PObjectDisplay::PObjectDisplay(string className, QWidget *parent,int ncol,int nrow,bool addable)
    :QGraphicsView(parent)
{
    olist=0;
    prop=0;
    parentObject=0;
    mapper = MappingControler::getInstance()->getMapperByName(className);
    if(mapper){
        typeName=mapper->getClassName();
        olist=mapper->find_gen();
        this->scene = new PObjectDisplayScene(olist,ncol,nrow);
        setScene(scene);
    } else {
        qDebug() << "PObjectDisplay : Failed to load, given className invalid";
    }


}

PObjectDisplay::PObjectDisplay(AbstractMapper *mapper, QWidget *parent,int ncol,int nrow, bool addable)
    :QGraphicsView(parent)
{
    olist=0;
    prop=0;
    parentObject=0;
    if(mapper){
        typeName=mapper->getClassName();
        olist=mapper->find_gen();
        this->scene = new PObjectDisplayScene(olist,ncol,nrow);
        setScene(scene);
    } else {
        qDebug() << "PObjectDisplay : Failed to load, given className invalid";
    }
}
PObjectDisplay::PObjectDisplay(RepositoryProperty *pr, PObject *po, QWidget *parent,int ncol,int nrow,bool addable)
    :QGraphicsView(parent)
{
    olist=0;
    mapper=0;
    prop=pr;
    parentObject=po;
    if(prop && parentObject){
        olist = prop->asCollection( parentObject );
    }
    this->scene = new PObjectDisplayScene(olist,ncol,nrow);
    if(addable){
                QPushButton *addButton = new QPushButton("Add",this);
                connect(addButton,SIGNAL(clicked()),this,SLOT(addElement()));
                scene->addWidget(addButton);
    }
    setScene(scene);
}

void PObjectDisplay::setPrototype(PObjectDisplayItem *protoItem)
{
    scene->setPrototype(protoItem);
}

void PObjectDisplay::setLayout(int ncol, int nrow)
{
    if(scene){
        scene->setLayout(ncol,nrow);
    }
}

void PObjectDisplay::setParentObject(PObject *po)
{
    parentObject=po;
    if(po && prop){
        setObjectList(prop->asCollection( parentObject ));
    }
}

void PObjectDisplay::setObjectList(list<PObject*> *olist)
{
    scene->clear();
    this->olist=olist;
    if(olist){
        scene->load(olist);
    }
}


void PObjectDisplay::addElement()
{
    Transaction *t=Transactions::getCurrentTransaction();
    if(prop && parentObject){
        t->add(parentObject);
        //string className = prop->getType();
        PObject *o = GuiCreateAction::getInstance()->create(prop->getType());
        if(CollectionProperty *cp = dynamic_cast<CollectionProperty*>(prop)){
            //table->startEdit();
            cp->add(o,parentObject);

        }
        setParentObject(parentObject);
    }
}


PObjectDisplayScene::PObjectDisplayScene(list<PObject*> *olist,int nr, int nc)
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
    if(numRow<0) numRow = this->height()/itemHeight;
    if(numCol<0) numCol = this->width()/itemWidth;
    removeItem(pitem);
}

void PObjectDisplayScene::setLayout(int ncol, int nrow)
{
    numCol=ncol;
    numRow=nrow;
    reload();
}

void PObjectDisplayScene::reload()
{
    if(olist){
        load(olist);
    }

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

    setSceneRect(QRectF(itemWidth/2,0,c*itemWidth,r*itemHeight));
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
    this->setFixedSize(400,250);

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
