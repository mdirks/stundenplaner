//
// C++ Implementation: pobjecticonview
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pobjecticonview.h"
#include "pobjecticonviewitem.h"
#include "orm/persistence/pobject.h"
#include "gui/guirepository.h"
#include "gui/base/guiconfig.h"
//#include "gui/draganddrop/pobjectdrag.h"
#include "orm/persistence/database.h"
//#include "gui/guirepository.h"
#include "gui/base/guicontroler.h"
#include "gui/base/guiconfig.h"
#include "orm/repository/collectionproperty.h"
#include "formspopupfactory.h"
#include "orm/transactions/transactions.h"
#include "datamodel/material.h"
#include "gui/actions/datenpopup.h"
#include <QMenu>
//#include <kmultipledrag.h>
//#include <kaction.h>
#include <qfiledialog.h>
#include <qstring.h>

#include <list>
//#include <krun.h>
//#include <kurl.h>

#include <QDragEnterEvent>
#include <QDebug>
#include <QLabel>
#include <QClipboard>
#include <QApplication>
#include <QDesktopServices>

#define GRIDX 100
#define GRIDY 40

using namespace std;

PObjectIconView::PObjectIconView(QWidget *parent)
 : QListWidget(parent)/*, KXMLGUIClient()*/
{

    provider=0;
    doCommonSetup();
}

PObjectIconView::PObjectIconView(PObjectListProvider *prov, QWidget *parent)
 : QListWidget(parent)/*, KXMLGUIClient()*/
{

    provider=prov;
    doCommonSetup();
}


PObjectIconView::PObjectIconView(list<PObject*> *olist, QWidget *parent)
 : QListWidget(parent)/*, KXMLGUIClient()*/
{
    provider = new PoLListProvider(olist);

    doCommonSetup();
}


PObjectIconView::PObjectIconView(QString className, QWidget *parent)
 : QListWidget(parent)/*, KXMLGUIClient()*/
{
    provider = new MapperListProvider(className);


    if(!className.isEmpty()){
        this->icon = GuiConfig::getInstance()->getIcon( className );
        typed = true;
        clName = className;
        typedMimeType = QString("application/pobject/").append(clName);
    }

    doCommonSetup();

}



PObjectIconView::PObjectIconView(AbstractMapper *mapper, QWidget *parent)
 : QListWidget(parent)/*, KXMLGUIClient()*/
{
    provider = new MapperListProvider(mapper);


    if(mapper){
        this->icon = GuiConfig::getInstance()->getIcon( mapper->getClassName().c_str() );
        typed = true;
        clName = mapper->getClassName().c_str();
		typedMimeType = QString("application/pobject/").append(clName);
	}

    doCommonSetup();

}



PObjectIconView::PObjectIconView(RepositoryProperty *prop, PObject *parentObject, QWidget *parent)
    : QListWidget(parent)/*, KXMLGUIClient()*/
{
    provider = new RpListProvider(prop,parentObject);


    this->clName = prop->getType().c_str();
	this->icon = GuiConfig::getInstance()->getIcon( prop );

    doCommonSetup();
}



void PObjectIconView::doCommonSetup()
{
    this->filter = 0;
    this->pmenu = 0;
    this->tableView=0;
    this->prevWidget=0;
    this->displayPropList=0;
    this->m_listDropHandler = new list<PObjectIconViewDropHandler*>();
    this->m_activationHandler=0;

    isLoaded=false;

    load();

    connect(this,SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(activateItem(QListWidgetItem *)));
    connect(this,SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT( renameObject(QListWidgetItem *)) );
    connect(this,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this,SLOT(changeCurrent(QListWidgetItem*,QListWidgetItem*)));
    setAcceptDrops(true);
    setDragEnabled(true);

}

PObjectIconView::~PObjectIconView()
{
}


void PObjectIconView::setParentObject(PObject *o)
{
    if(provider) provider->setParentObject(o);
    reload();
}

void PObjectIconView::changeCurrent(QListWidgetItem *current, QListWidgetItem *previous)
{
    PObjectIconViewItemE *pitem = dynamic_cast<PObjectIconViewItemE*>(previous);
    PObjectIconViewItemE *citem = dynamic_cast<PObjectIconViewItemE*>(current);
    if(pitem) pitem->showFull(false);
    if(citem){
        citem->showFull(true);
        citem->grepFocus();
    }
    emit currentChanged();
}


/*!
    \fn PObjectIconView::load()
 */
void PObjectIconView::load()
{
    if(provider){
        load(provider->objectList());
        isLoaded=true;
    }

}

void PObjectIconView::reload()
{
	clear();
    load();

}

void PObjectIconView::load(list<PObject*>* olist){
    if(olist){
        for( list<PObject*>::iterator it = olist->begin(); it != olist->end(); it++){
            if(filter){
                if(filter->apply(*it)){
                    createItem(*it);
                } else {
                    qDebug() << "PObjectIconView::load : Item dropped by filter";
                }
            } else { //no filter set
                createItem(*it);
            }
        }
    }
    update();
}

void PObjectIconView::setTableView(PObjectTable *table)
{
    this->tableView=table;
}

PObjectTable* PObjectIconView::getTableView()
{
    return this->tableView;
}

PObjectIconViewItemBase* PObjectIconView::doCreateItem(PObject *o)
{
    PObjectIconViewItemBase *item=0;

	if(o){
        icon = GuiConfig::getInstance()->getIcon(o);
        if(displayPropList){
            if(displayPropList->size()==1){
                item=new PObjectIconViewItem(
                            o,this,icon,displayPropList->front());
            } else {
                item = new PObjectIconViewItemE(o,displayPropList,this,icon);
            }
        } else {
            item = new PObjectIconViewItem(o,this,icon);
        }
        addItem(item);
	}

    return item;
}

PObjectIconViewItemBase* PObjectIconView::createItem(PObject *o)
{
    return this->doCreateItem(o);
}

PObject* PObjectIconView::getSelected()
{
	PObject *o = 0;
    QList<QListWidgetItem*> litems = QListWidget::selectedItems();
    if(!litems.isEmpty()){
        PObjectIconViewItem *item = dynamic_cast<PObjectIconViewItem*>(litems.first());
        if(item){
            o = item -> getObject();
        }
    }
	return o;
}

PObject* PObjectIconView::getObject(int index)
{
    PObjectIconViewItem *it = dynamic_cast<PObjectIconViewItem*>(this->item(index));
    if(it){
        return it->getObject();
    } else {
        return 0;
    }


}

PObject* PObjectIconView::getCurrent()
{
    PObject *o = 0;
    QListWidgetItem *item = QListWidget::currentItem();
    if(item){
        PObjectIconViewItem *pitem = dynamic_cast<PObjectIconViewItem*>(item);
        if(pitem){
            o = pitem -> getObject();
        }
    }
    return o;
}

void PObjectIconView::setActivationHandler(PObjectIconViewActivationHandler *h)
{
    m_activationHandler=h;
}


/*!
    \fn PObjectIconView::activateItem(PObjectIconViewItem *item)
 */
void PObjectIconView::activateItem(QListWidgetItem *item)
{
    PObjectIconViewItemBase *pitem = dynamic_cast<PObjectIconViewItemBase*>(item);
	if(pitem){
        handleActivation(pitem->getObject());
    }
}
void PObjectIconView::handleActivation(PObject *o)
{
        if(!o) return;

        if(!m_activationHandler){
            m_activationHandler = new PObjectIconViewActivationHandler();
        }

        m_activationHandler->handleActivation(o);

}

void PObjectIconViewActivationHandler::handleActivation(PObject *o)
{
        material *m=0;
		if(o->getClassName() == "material" && (m = dynamic_cast<material*>(o))){
            QString fileName = m->getFile()->fileName();
            QDesktopServices::openUrl(fileName);
		} else {
			GuiRepository::getInstance()->showFormForObject(o);
		}

}


/*!
    \fn PObjectIconView::contentsDragLeaveEvent(QDragLeaveEvent *e)
 */
void PObjectIconView::dragLeaveEvent(QDragLeaveEvent *e)
{
    	qDebug("Drag Leave");
}

void PObjectIconView::dragEnterEvent(QDragEnterEvent *e)
{
    qDebug() << e->mimeData()->formats();
    if(e->mimeData()->hasFormat("application/pobject"))
    {
        e->accept();
    } else {
        list<PObjectIconViewDropHandler*>::iterator it=m_listDropHandler->begin();
        bool acc = false;
        while(!acc && it != m_listDropHandler->end())
        {
            if( (*it)->canHandle(e) )
            {
                e->accept();
                acc=true;
            }

        }
        if(! acc) e->ignore();
    }
	
}

void PObjectIconView::addDropHandler(PObjectIconViewDropHandler *dh)
{
    m_listDropHandler->push_back(dh);
    dh->setIconView(this);
}






void PObjectIconView::dragMoveEvent(QDragMoveEvent *e)
{
    qDebug() << e->mimeData()->formats();
    if(e->mimeData()->hasFormat("application/pobject"))
    {
        e->accept();
    } else {
        list<PObjectIconViewDropHandler*>::iterator it=m_listDropHandler->begin();
        bool acc = false;
        while(!acc && it != m_listDropHandler->end())
        {
            if( (*it)->canHandle(e) )
            {
                e->accept();
                acc=true;
            }

        }
        if(! acc) e->ignore();
    }

}


void PObjectIconView::setDisplayProperty(RepositoryProperty *p)
{
    this->displayPropList = new list<RepositoryProperty*>();
    displayPropList->push_back(p);
    reload();
}

void PObjectIconView::setDisplayProperties(list<RepositoryProperty*> *listRp)
{
    this->displayPropList = listRp;
    reload();
}

void PObjectIconView::startDrag ( Qt::DropActions supportedActions ){
    PObject *o=getSelected();
    if(o){
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData();
        QByteArray data;
        QDataStream stream(&data,QIODevice::WriteOnly);
        stream <<  QString(o->getPersistenceObject()->getClassName().c_str()) << o->getID();
        mimeData->setData("application/pobject",data);
        drag->setMimeData(mimeData);
        drag->setPixmap(this->icon);
        drag->start();
    } else {
        qDebug() << "WARNING: PObjectIconView::startDrag : empty object";
    }
}

/*!
    \fn PObjectIconView::contentsMousePressEvent(QMouseEvent *e)
 */
void PObjectIconView::mousePressEvent(QMouseEvent *e)
{
     QListWidget::mousePressEvent(e);

     if(e->button()==Qt::RightButton){
        QMenu *popup = getPopupMenu();
        if(popup){
            popup->popup(e->globalPos());
        } else {
            qWarning("Failed to get Popupmenu");
        }

     }


    //QListWidget::mousePressEvent(e);
}

void PObjectIconView::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "PObjectIconView::keyPressEvent";
    if( e == QKeySequence::Copy) {
        PObject *o=getSelected();

        if(o){
            QMimeData *md = createMimeData(o);
            if(md){
                QClipboard *clipboard = QApplication::clipboard();
                clipboard->setMimeData(md);
            }
        } else {
            qDebug() << "PObjectIconView::keyPressEvent: cannot paste: no selection";
        }

    } else if (e==QKeySequence::Paste){
        paste();
    }
    /* else if(e->key() == Qt::Key_F2) {
        PObjectIconViewItemE *pitem = dynamic_cast<PObjectIconViewItemE*>(getSelected());
        if(pitem){
            pitem->editRequested();
        } else {
            QListWidget::keyPressEvent(e);
        }
    }*/
    else {
        QListWidget::keyPressEvent(e);

    }
}




void PObjectIconView::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasFormat("application/pobject"))
    {
        PObject *o=handlePObjectDrop(e);
        if(o){
            addObject(o);
        } else {
            qDebug() << "Drop: Cannot handle object";
        }
        e->accept();
    } else {
        list<PObjectIconViewDropHandler*>::iterator it=m_listDropHandler->begin();
        bool acc = false;
        while(!acc && it != m_listDropHandler->end())
        {
            if( (*it)->dropEvent(e) )
            {
                e->accept();
                acc=true;
            }

        }
        if(! acc) e->ignore();
}

}



void PObjectIconView::paste()
{
    const QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *md = clipboard->mimeData();

    PObject *o=recoverPObject(md);
    if(o){

        addObject(o);
    } else {
        qDebug() << "Paste: Cannot handle object";
    }
}


/*!
    \fn PObjectIconView::addObject(PObject *o)
 */
void PObjectIconView::addObject(PObject *o)
{
    if(!o) return;
    startEdit();
    if(provider){
        provider->addObject(o);
    }
    createItem(o);



}


void PObjectIconView::deleteObject(PObjectIconViewItem *item)
{
    qDebug() << "WARNING: Do-Nothing-Impl - PObjectIconView::deleteObject() ";
}


void PObjectIconView::stopEdit()
{
	editing = false;
}
 
void PObjectIconView::startEdit(RepositoryProperty *rp, PObject *parent)
{
	qDebug("Warnign: PObjectIconView::startEdit not implemented (do nothing !)");
}

void PObjectIconView::startEdit()
{
	if(!editing){
        //Transactions::getCurrentTransaction()->add(parentObject);
		GuiControler::getInstance()->addActiveEditor(this);
		editing=true;
   	}
}











/**
 * Creates the Popup for this IconView (lazy)
 * @return 
 */
QMenu* PObjectIconView::getPopupMenu()
{
	
	FormsPopupFactory *factory = FormsPopupFactory::getInstance();
	if(factory){
		return factory->getPopupFor(this);
	} else {
		return 0;
	}
}



/*!
    \fn PObjectIconView::renameObject(QIconViewItem* item, QString & name)
 */
void PObjectIconView::renameObject(QListWidgetItem* item)
{
	qDebug("PObjectIconView: renameObject called");
	PObjectIconViewItem *pitem = dynamic_cast<PObjectIconViewItem*>(item);
	if(pitem){
		PObject *o = pitem -> getObject();
		Transactions::getCurrentTransaction()->add(o);
        o->setName(  item->text().toStdString() );
	}
}



void PObjectIconView::selectFile()
{
	PObjectIconViewItem *item = dynamic_cast<PObjectIconViewItem*>(currentItem());
	if(item){
		PObject *o = item->getObject();
		if(material *m = dynamic_cast<material*>(o)){
            QString filename=QFileDialog::getSaveFileName();
			Transactions::getCurrentTransaction()->add(m);
            m->setFileName(  filename.toStdString() );
		}
	}
}

/*!
    \fn PObjectIconView::getObjectList()
 */
list<PObject*>* PObjectIconView::getObjectList()
{
    
    list<PObject*> *objectList = new list<PObject*>();
    
    for(int i=0; i< count(); i++){
        PObjectIconViewItem *itm = dynamic_cast<PObjectIconViewItem*>(item(i));
        if(itm){
            objectList->push_back( itm -> getObject() );
        }
    }

    return objectList;
}

void PObjectIconView::show()
{
	if(!isLoaded){
		load();
	}
	QWidget::show();
}


/*!
    \fn PObjectIconView::chooseFilter
 */
void PObjectIconView::chooseFilter()
{
    if(filter){

    }
}


void PObjectIconView::setFilter(Filter *f)
{
    this->filter=f;
    reload();
}

void PObjectIconView::clearFilter()
{
    this->filter=0;
    reload();
}


void PObjectIconView::setObjectListProvider(PObjectListProvider *prov)
{
    this->provider=prov;
    reload();
}

PObjectListProvider* PObjectIconView::getProvider()
{
    return this->provider;
}




