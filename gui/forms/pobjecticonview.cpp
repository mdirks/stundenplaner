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
#include <krun.h>
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

void PObjectIconView::changeCurrent(QListWidgetItem *current, QListWidgetItem *previous)
{
    PObjectIconViewItemE *pitem = dynamic_cast<PObjectIconViewItemE*>(previous);
    PObjectIconViewItemE *citem = dynamic_cast<PObjectIconViewItemE*>(current);
    if(pitem) pitem->showFull(false);
    if(citem){
        citem->showFull(true);
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
    /*
    if(mapper){
		load( mapper->find_gen() );
	} else if (prop && prop->isCollection() && parentObject){
		load( prop->asCollection( parentObject ) );
	} else if (olist){
		load(olist);
	}

	isLoaded=true;
    */
}

void PObjectIconView::reload()
{
	clear();
    load();
    /*
    if(mapper){
		mapper->reset();
	}

	load();
    */
}

void PObjectIconView::load(list<PObject*>* olist){
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

void PObjectIconView::setTableView(PObjectTable *table)
{
    this->tableView=table;
}

PObjectTable* PObjectIconView::getTableView()
{
    return this->tableView;
}

PObjectIconViewItemBase* PObjectIconView::createItem(PObject *o)
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


/*!
    \fn PObjectIconView::activateItem(PObjectIconViewItem *item)
 */
void PObjectIconView::activateItem(QListWidgetItem *item)
{
	PObjectIconViewItem *pitem = dynamic_cast<PObjectIconViewItem*>(item);
	if(pitem){
		PObject *o = pitem->getObject();
		material *m=0;
		if(o->getClassName() == "material" && (m = dynamic_cast<material*>(o))){
            QString fileName = m->getFile()->fileName();
            QDesktopServices::openUrl(fileName);
            /*
			if(fileName.contains(".tex")){ // hack to handel tex-files
                KRun::runCommand(QString("kile %1").arg(fileName),this);
			} else {	
                new KRun(fileName,this);
			}
            */
		} else {
			GuiRepository::getInstance()->showFormForObject(o);
		}
	} else {qDebug("PObjectIconView: Activation failed - could not get valid item");}
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

    if(e->mimeData()->hasFormat("application/pobject"))
    {
        e->accept();
    } else {
        e->ignore();
    }
	
}

void PObjectIconView::dragMoveEvent(QDragMoveEvent *e)
{

    if(e->mimeData()->hasFormat("application/pobject"))
    {
        e->accept();
    } else {
        e->ignore();
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

     } /* else if (e->button() == Qt::LeftButton) {
        PObject *o=getSelected();
        QDrag *drag = new QDrag(this);
        PObjectData *mimeData = new PObjectData(o,this);
        drag->setMimeData(mimeData);
        Qt::DropAction dropAction = drag->exec(Qt::CopyAction);
        e->accept();

    }*/


    //QListWidget::mousePressEvent(e);
}

void PObjectIconView::keyPressEvent(QKeyEvent *e)
{
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
    } else {
        QListWidget::keyPressEvent(e);
    }
}




void PObjectIconView::dropEvent(QDropEvent *e)
{
    PObject *o=handlePObjectDrop(e);
    if(o){
        if(provider){
            provider->addObject(o);
        }
        addObject(o);
    } else {
        qDebug() << "Drop: Cannot handle object";
    }

}



void PObjectIconView::paste()
{
    const QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *md = clipboard->mimeData();

    PObject *o=recoverPObject(md);
    if(o){
        if(provider){
            provider->addObject(o);
        }
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
    createItem(o);


    /*
	if(prop && parentObject)
	{
		if(CollectionProperty *cp = dynamic_cast<CollectionProperty*>(prop)){
			startEdit();
			cp->add(o,parentObject);
            qDebug() << QString("Added object %1").arg(o->getID());
			
		} else {
            qDebug() << "PObjectIconView::addObject : Strange - non-collection property!??";
		}
	}

	
	createItem(o);
    */
	/*
	QPixmap pixm = GuiRepository::getInstance()->getIcon(o);
	new PObjectIconViewItem(o,this,o->getName(),pixm);
	*/
}


void PObjectIconView::deleteObject(PObjectIconViewItem *item)
{
	
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



/*!
    \fn PObjectIconView::deleteSelected()
	
	Removes the selected Item from the collection. This is delegated to  the RepositoryProperty (CollectionProperty).

 */
/*
void PObjectIconView::deleteSelected()
{
	if(prop && parentObject && prop->isCollection()){
		PObjectIconViewItem *item = static_cast<PObjectIconViewItem*>(currentItem());
		if(item){
			PObject *o = item->getObject();
			CollectionProperty *colProp = dynamic_cast<CollectionProperty*>(prop);
			if(colProp){
				colProp->remove( o,parentObject);
			}
			delete item;
		}
	}
}
*/
/*
QPopupMenu*  PObjectIconView::getDatenPopupForSelected()
{
	PObjectIconViewItem *item = static_cast<PObjectIconViewItem*>(currentItem());
	if(item){
		PObject *o = item->getObject();
		if(o){
			return new DatenPopup(o,this);
		}
	}
	return 0;
}
*/

/*
void PObjectIconView::insertNew()
{
	PObject *o;
	if(prop && parentObject){
		//string className = prop->getType();
		o = CreateAction::getInstance()->create(prop->getType());
		
	} else if(mapper) {
		 o = CreateAction::getInstance()->create(mapper->getClassName());
	}
	addObject(o);
}
*/


/*!  Defines the Actions available via the Popup
 
    \fn PObjectIconView::initActions()
 */
/*
list<QAction*>* PObjectIconView::initActions(QActionCollection *actionCollection)
{
	list<QAction*> *actionList = new list<QAction*>();
	
	actionList->push_back( new QAction("Neu laden", KStdAccel::shortcut(KStdAccel::New), this, SLOT(reload()), actionCollection,"reload"));
	
	actionList->push_back( new QAction("Neues Element", KStdAccel::shortcut(KStdAccel::New), this, SLOT(insertNew()), actionCollection,"new"));

	actionList->push_back( new QAction("Filter setzen", KStdAccel::shortcut(KStdAccel::New), this, SLOT(chooseFilter()), actionCollection,"new browser"));

	actionList->push_back( new QAction("Neuer Objectbrowser", KStdAccel::shortcut(KStdAccel::New), this, SLOT(newIconView()), actionCollection,"new browser"));
	
	actionList->push_back( new QAction("Konfigurieren", KStdAccel::shortcut(KStdAccel::New), this, SLOT(configureView()), actionCollection,"configure"));
	
	actionList->push_back( new QAction("Icon wählen", KStdAccel::shortcut(KStdAccel::New), this, SLOT(selectIcon()), actionCollection,"icon"));

	QAction *a = new QAction("Delete Item", KStdAccel::shortcut(KStdAccel::New), this,SLOT(deleteSelected()), actionCollection, "del");
	actionList->push_back(a);

	if(mapper && mapper->getClassName() == "material"){
		actionList->push_back( new QAction("File wählen", KStdAccel::shortcut(KStdAccel::New), this, SLOT(selectFile()), actionCollection,"icon"));
	} else if (prop &&  prop->getType() == "material"){
		actionList->push_back( new QAction("File wählen", KStdAccel::shortcut(KStdAccel::New), this, SLOT(selectFile()), actionCollection,"icon"));
	}
	
	return actionList;
}*/

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

	/*
		pmenu = new QPopupMenu(this);
		list<QAction*> *actionList = initActions();
		for(list<QAction*>::iterator it = actionList->begin(); it != actionList->end(); it++){
			(*it)->plug(pmenu);
		}

		if(QPopupMenu *sub = getDatenPopupForSelected()){
			pmenu->insertItem("Daten",sub);
		}


	return pmenu;
	*/
}


/*!
    \fn PObjectIconView::newIconView()
 */
/*
void PObjectIconView::newIconView()
{
	PObjectIconView *iconView = new PObjectIconView();
	GuiRepository::getInstance()->addTool(iconView, "Unbekannt", "Unbekannt");
}
*/


/*!
    \fn PObjectIconView::configureView()
 */
/*
void PObjectIconView::configureView()
{
		

	setMapper(CreateAction::chooseMapper());
	
}
*/

/*
void PObjectIconView::setMapper(AbstractMapper *mapper)
{
	if(mapper){
		prop=0;
		parentObject=0;

		clear();
		this->mapper = mapper;
        this->icon = GuiConfig::getInstance()->getIcon( mapper->getClassName().c_str() );
        //setIcon(icon);
		typed = true;
        clName = mapper->getClassName().c_str();
		typedMimeType = QString("application/pobject/").append(clName);

		load();
	}

}
*/

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


/*!
    \fn PObjectIconView::selectIcon()
 */
/*
void PObjectIconView::selectIcon()
{
	PObjectIconViewItem *item = dynamic_cast<PObjectIconViewItem*>(currentItem());
	if(item){
		GuiConfig::getInstance()->selectIcon(item->getObject());
	}
}
*/

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




