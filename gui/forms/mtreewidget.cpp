#include "mtreewidget.h"
#include "gui/base/guiconfig.h"
#include "gui/actions/guipopupfactory.h"
#include "gui/actions/guicreateaction.h"
#include "orm/transactions/transactions.h"

#include <QDebug>

MTreeWidget::MTreeWidget(MTree *tr, QWidget *parent)
    : QTreeWidget(parent)
{
    topLevelItems=new list<MTreeWidgetItem*>();
    addTopLevelItem(tr);
    setAcceptDrops(true);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));


}


void MTreeWidget::addTopLevelItem(MTree *tr)
{
    topLevelItems->push_back(new MTreeWidgetItem(tr,this));
}

void MTreeWidget::onCustomContextMenu(const QPoint &p)
{
        MTreeWidgetItem *item = dynamic_cast<MTreeWidgetItem*>(itemAt(p));
        if (item) {
            QMenu *popup = GuiPopupFactory::getInstance()->getPopupFor(item);
            popup->exec(viewport()->mapToGlobal(p));
        }
}


void MTreeWidget::dropEvent(QDropEvent *e)
{
    PObject *o=handlePObjectDrop(e);
    if(TransactionObject *to = dynamic_cast<TransactionObject *>(o)){
        QTreeWidgetItem *item = currentItem();
        if(MTreeWidgetItem *mitem=dynamic_cast<MTreeWidgetItem*>(item))
        {
            if(mitem->getContents()){
                mitem->addChildItem(to);
            } else {
                mitem->setContents(to);
            }
        }
    } else {
        qDebug() << "Drop: Cannot handle object";
    }

}

void MTreeWidget::dragEnterEvent(QDragEnterEvent *e)
{

    if(e->mimeData()->hasFormat("application/pobject"))
    {
        e->accept();
    } else {
        e->ignore();
    }

}

void MTreeWidget::dragMoveEvent(QDragMoveEvent *e)
{

    if(e->mimeData()->hasFormat("application/pobject"))
    {
        e->accept();
    } else {
        e->ignore();
    }

}





























MTreeWidgetItem::MTreeWidgetItem(MTree *tr, QTreeWidgetItem *parentItem)
    : QTreeWidgetItem(parentItem)
{
    node=tr;
    if(node){
        if(TransactionObject *to = node->getContents()){
            setText(0,to->getName().c_str());
            setIcon(0,GuiConfig::getInstance()->getIcon(to));
        } else {
            setText(0,"Empty 0");
            setText(1,"Empty 1");
        }
        list<MTree*> *listChildren = node->getChildren();
        for(list<MTree*>::iterator it=listChildren->begin(); it!=listChildren->end(); it++){
            new MTreeWidgetItem((*it),this);
        }
    }
}

MTreeWidgetItem::MTreeWidgetItem(MTree *tr, QTreeWidget *parentWidget)
    : QTreeWidgetItem(parentWidget)
{
    node=tr;
    if(node){
        if(TransactionObject *to = node->getContents()){
            setText(0,to->getName().c_str());
            setIcon(0,GuiConfig::getInstance()->getIcon(to));
        }else {
            setText(0,"Empty 0");
            setText(1,"Empty 1");
        }

        list<MTree*> *listChildren = node->getChildren();
        for(list<MTree*>::iterator it=listChildren->begin(); it!=listChildren->end(); it++){
            new MTreeWidgetItem((*it),this);
        }
    }
}

void MTreeWidgetItem::addChildItem(TransactionObject *to)
{
    MTree *tr = (MTree*) GuiCreateAction::getInstance()->create("MTree");
    tr->setContents(to);
    Transactions::getCurrentTransaction()->add(node);
    node->addToChildren(tr);
    new MTreeWidgetItem(tr,this);
}


void MTreeWidgetItem::setContents(TransactionObject *to)
{
    Transactions::getCurrentTransaction()->add(node);
    node->setContents(to);
    if(TransactionObject *to = node->getContents()){
        setText(0,to->getName().c_str());
        setIcon(0,GuiConfig::getInstance()->getIcon(to));
    }
}

TransactionObject* MTreeWidgetItem::getContents()
{
    return node->getContents();
}


























MTreeWidgetItemAction::MTreeWidgetItemAction(MTreeWidgetItem *treeWidgetItem)
{

}

MTreeWidgetItemAction::~MTreeWidgetItemAction()
{

}

void MTreeWidgetItemAction::addChild()
{

}
void MTreeWidgetItemAction::removeFromParent()
{

}
void MTreeWidgetItemAction::newContentsObject()
{

}
