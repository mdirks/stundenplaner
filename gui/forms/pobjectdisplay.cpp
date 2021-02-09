#include "pobjectdisplay.h"

#include <QHBoxLayout>
#include <QGraphicsProxyWidget>
#include <QPushButton>

#include "orm/mapping/mappingcontroler.h"
#include "orm/transactions/transactions.h"
#include "orm/repository/collectionproperty.h"

#include "gui/actions/guicreateaction.h"

#include <QGraphicsSceneContextMenuEvent>
//Jup funktioniert auch mobil



PObjectDisplay::PObjectDisplay(QWidget *parent,  int ncol, int nrow,bool addable)
    : QGraphicsView(parent)
{
    olist=0;
    prop=0;
    parentObject=0;
    mapper=0;
    clickedItem=0;

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
    clickedItem=0;


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
    clickedItem=0;

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
    clickedItem=0;

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
    clickedItem=0;

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

void PObjectDisplay::contextMenuEvent(QContextMenuEvent *ev)
{
    QGraphicsItem *item=itemAt(ev->pos());
    if(clickedItem = dynamic_cast<PObjectDisplayItem*>(item)){
        QMenu *menu=new QMenu();
        QAction *removeAction = menu->addAction("Remove",this,SLOT(removeClickedItem()));

        menu->popup(mapToGlobal(ev->pos()));
    }
}

void PObjectDisplay::removeClickedItem()
{
    PObject *o;
    if(clickedItem && (o=clickedItem->getObject())){

        Transaction *t=Transactions::getCurrentTransaction();
        if(prop && parentObject){
            t->add(parentObject);
        }
        if(CollectionProperty *cp = dynamic_cast<CollectionProperty*>(prop)){
            //table->startEdit();
            cp->remove(o,parentObject);

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

    //calculate layout if not set
    if(numRow<0) numRow = this->height()/protoItem->getIdealSize().width();
    if(numCol<0) numCol = this->width()/protoItem->getIdealSize().height();
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

void PObjectDisplayScene::deleteItem(PObjectDisplayItem *item)
{
    PObject *o = item->getObject();
    if(o && olist){
        olist->remove(o);
    }
    delete item;
    reload();
}

void PObjectDisplayScene::load(list<PObject*> *olist)
{
    int c=0, r=0, pw_max=0, ph_max=0;

    int pw=0, ph=0;

    for(list<PObject*>::iterator it = olist->begin(); it!=olist->end(); it++){
            PObject *o=*it;
            if(o){

                QGraphicsItem *item = protoItem->createInstance(o,this, pw, ph);


                if(item){
                    //QGraphicsProxyWidget *pitem= addWidget(item);
                    //pitem->prepareGeometryChange();

                    pw += item->boundingRect().width();
                    if(pw>pw_max) pw_max=pw;
                    c+=1;
                    if(c>=numCol){
                        r+=1;
                        ph+=item->boundingRect().height();
                        if(ph>ph_max) ph_max=ph;
                        c=0;
                        pw=0;
                    }
                }
            }

    }

    setSceneRect(QRectF(0,0,pw_max,ph_max));
}



LernkarteDisplayItem::LernkarteDisplayItem(lernkarte *lk)
    : PObjectDisplayItem(lk),
      QWidget()
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
    setIdealSize(size());
}

QGraphicsItem* LernkarteDisplayItem::createInstance(PObject *o, QGraphicsScene *s,int px,int py)
{
    QGraphicsItem *item=0;
    lernkarte *lk = dynamic_cast<lernkarte*>(o);
    if(lk){
        item = s->addWidget(new LernkarteDisplayItem(lk));
    } else {
        item = s->addText("Unknown\\Itemtype");
    }
    item->setPos(px,py);
    return item;
}


MaterialDisplayItem::MaterialDisplayItem(material *m)
    : PObjectDisplayItem(m),
      QGraphicsPixmapItem()
{
    this->m = m;
    setIdealSize(QSizeF(200,100));
}

QGraphicsItem* MaterialDisplayItem::createInstance(PObject *o, QGraphicsScene *s,int px, int py)
{
    QGraphicsItem *item=0;
    material *m = dynamic_cast<material*>(o);
    if(m){
        QPixmap pm;
        if(pm.load(m->getFileName().c_str())){
            //item = s->addPixmap(pm);
            MaterialDisplayItem *mitem = new MaterialDisplayItem(m);
            mitem -> setPixmap(pm);
            item=mitem;
            s->addItem(item);
        } else {
            item = s->addText("Image \\ failed to load");
        }
    } else {
        item = s->addText("Unknown\\Itemtype");
    }
    item->setPos(px,py);
    return item;
}


