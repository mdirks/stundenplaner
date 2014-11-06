//
// C++ Implementation: pobjecttable
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pobjecttable.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/collectionproperty.h"
//#include "actions/createaction.h"
#include "orm/transactions/transactions.h"
#include "dateeditor.h"
#include "pobjectlabel.h"
#include "gui/base/guiconfig.h"
#include "orm/mapping/mappingcontroler.h"
#include "services/utils/datecompare.h"
#include "services/utils/namedobjectptrcomp.h"

#include "qmessagebox.h"
#include <QDebug>

#define ROW_HEIGHT 40

PObjectTableControlerFactory* PObjectTableControlerFactory::instance=0;

PObjectTableControlerFactory* PObjectTableControlerFactory::getInstance()
{
	return instance;
}
void PObjectTableControlerFactory::setInstance(PObjectTableControlerFactory* factory)
{
	instance=factory;
}


PObjectTable::PObjectTable(string className, QWidget *parent, bool addable) 
    :  QTableWidget(parent)
{
	this->olist=0;
	this->addable = addable;
	this->pmenu=0;
	this->mapper = MappingControler::getInstance()->getMapperByName(className);
	if(mapper){
		typeName=mapper->getClassName();
	}
	this->prop = 0;
	//this->propList = 0;
	this->controler=0;

    //setSorting(true);

	connect(this, SIGNAL(currentChanged(int,int)), this, SLOT(currentChanged(int,int)));
	connect(this, SIGNAL(valueChanged(int,int)), this, SLOT(valueChanged(int,int)));
    //connect((QTable*) this, SIGNAL(contextMenuRequested( int, int, const QPoint &)),(QTable*)this,SLOT(showContextMenu( int, int, const QPoint &)));
}

PObjectTable::PObjectTable(list<PObject*> *olist, QString type, QWidget *parent, bool addable) 
    :  QTableWidget(parent)
{
	this->olist = olist;

	this->addable = addable;
	this->pmenu=0;
	this->mapper = 0;
	this->prop = 0;
	//this->propList = 0;
	this->controler=0;

    loadType(type.toStdString());
    //setSorting(true);

	connect(this, SIGNAL(currentChanged(int,int)), this, SLOT(currentChanged(int,int)));
    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(valueChanged(int,int)));
    //connect((QTable*) this, SIGNAL(contextMenuRequested( int, int, const QPoint &)),(QTable*)this,SLOT(showContextMenu( int, int, const QPoint &)));
}
PObjectTable::~PObjectTable()
{

}

PObjectTable::PObjectTable(AbstractMapper *mapper, QWidget *parent, bool addable)
    : QTableWidget(parent)
{
	this->olist=0;
	this->addable = addable;

	this->pmenu = 0;
	this->prop =0;
	this->controler=0;
	this->mapper = mapper;
	

	if(mapper){
		typeName=mapper->getClassName();
		loadType(typeName);
	}
	
	/*
	if(mapper){
		this->icon = GuiRepository::getInstance()->getIcon( mapper->getClassName() );
		setIcon(icon);
		typed = true;
		clName = mapper->getClassName();
		typedMimeType = QString("application/pobject/").append(clName);
	}
	*/

	connect(this, SIGNAL(currentChanged(int,int)), this, SLOT(currentChanged(int,int)));
	connect(this, SIGNAL(valueChanged(int,int)), this, SLOT(valueChanged(int,int)));
    //connect((QTable*)this,SIGNAL(QTable::contextMenuRequested( int, int, const QPoint &)),this,SLOT(showContextMenu( int, int, const QPoint &)));
	/*
	setXMLFile("/home/mopp/dev/c++/1304/stundenplaner/stundeplanerui.rc");
	connect(this,SIGNAL(doubleClicked(QIconViewItem *)), this, SLOT(activateItem(QIconViewItem *)));
	connect(this,SIGNAL(dropped( QDropEvent *, const QValueList<QIconDragItem> & )), this, SLOT( handleDrop(QDropEvent *)));
	connect(this,SIGNAL(itemRenamed(QIconViewItem * , const QString & )), this, SLOT( renameObject(QIconViewItem *, const QString &)) );
	*/
    //setSorting(true);
}


PObjectTable::PObjectTable(RepositoryProperty *prop, PObject *parentObject, QWidget *parent, bool addable)
    : QTableWidget(parent)
{
	this->olist=0;
	this->addable = addable;

	this->pmenu = 0;	
	//this->objectList = 0;
	this->controler=0;
	this->mapper = 0;
	this->prop = prop;
	this->typeName = prop->getType();
	this->parentObject = parentObject;
	
	loadType(prop->getType());
    connect(this, SIGNAL(cellClicked(int,int)), this, SLOT(currentChanged(int,int)));
    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(valueChanged(int,int)));
    connect((QWidget*) this, SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(showContextMenu( const QPoint &)));
    setContextMenuPolicy(Qt::CustomContextMenu);
    //this->icon = GuiConfig::getInstance()->getIcon( prop );
    //setIcon(icon);


    //setColumnStretchable(map_prop.size()-1, true);
    //setSorting(true);
}



void PObjectTable::readPropertiesForType(string className)
{
	RepositoryEntry *entry = Repository::getInstance()->getRepositoryEntry( className );
	if(entry){
		list<RepositoryProperty*> *prop_list = new list<RepositoryProperty*>();

        QStringList displayProperties = GuiConfig::getInstance()->getDisplayProperties(
                    QString("PObjectTable-%1").arg(className.c_str()));
		if(displayProperties.size()!=0){
            for(int i=0; i<displayProperties.size(); i++)
			{
                RepositoryProperty *rp = entry->getProperty(displayProperties.at(i).toStdString());
				if(rp){
					prop_list->push_back(rp);
				}else {
                    qDebug() << QString("PObjectTable::readPropertiesForType: could not get property for %1").arg(displayProperties.at(i));
				}
			}
		} else { 
			prop_list = entry->getAllProperties( false );
			
		}
		
		setDisplayProperties(prop_list);
	} else { qDebug("PObjectTable::readPropertiesForType : could not get type");}
}


void PObjectTable::setDisplayProperties(list<RepositoryProperty*>* list_prop)
{
	if(list_prop){
		map_prop.clear();
		QStringList propertyNameList;
	
        int col=1; // col 0 is icon
		for(list<RepositoryProperty*>::iterator it = list_prop->begin(); it != list_prop->end(); it++){
			RepositoryProperty *prop = (*it);
			//if(prop->isString() || prop->isText() || prop->isDate() || prop->isPObject()){
				map_prop[col] = prop;
                propertyNameList.append(prop->getName().c_str());
				col++;
			//} 
		}
        setColumnCount(map_prop.size() + 1);
		int count =1;
        QStringList headerLabels;
        headerLabels << "";
		for(map<int,RepositoryProperty*>::iterator it = map_prop.begin(); it != map_prop.end(); it++){
			RepositoryProperty *prop = it->second;
            headerLabels.append(prop->getName().c_str());
            // todo : horizontalHeader()->setLabel(count, prop->getName());
			++count;
		}
        setHorizontalHeaderLabels(headerLabels);

		
		
        GuiConfig::getInstance()->setDisplayProperties(QString("PObjectTable-%1").arg(typeName.c_str()),propertyNameList);
		load();
	} else {
		qDebug("PObjectTable::setDisplayProperties : given property list was empty, could not set");
	}
}

void PObjectTable::loadType(string className){
    this->icon = GuiConfig::getInstance()->getIcon(className.c_str());
    readPropertiesForType(className); //read new map_prop;

}




void PObjectTable::startEdit()
{
	AbstractPropertyEditor::startEdit();
}

/*!
    \fn PObjectTable::startEdit(int row)
 */
void PObjectTable::startEdit(int row)
{
        set_editing.insert(row);
	Transactions::getCurrentTransaction()->add( getObject(row) );
}

PObject* PObjectTable::getObject(int row)
{
	return map_obj[row];
}

void PObjectTable::stopEdit()
{
	for(set<int>::iterator it = set_editing.begin(); it != set_editing.end(); it++){
		readRow((*it));
	}
	set_editing.clear();	
	AbstractPropertyEditor::stopEdit();
}



void PObjectTable::load()
{
	if (olist){
		load( olist );
		update();
	} else if(mapper){
		load( mapper->find_gen() );
	} else if (prop && prop->isCollection() && parentObject){
		list<PObject*>* olist = prop->asCollection( parentObject );
		if(prop->getName() == "Eintraege"){
			RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry("krusbucheintrag");
			RepositoryProperty *r= re->getProperty("Datum");
			olist->sort(DateCompare<PObject>(r));
		}
		load( olist );
        resizeColumnToContents(0);
		update();
	} 
	//adjustColumn(0);
}

void PObjectTable::load(list<PObject*>* olist){
	if(olist){
        isloading=true;
		this->olist = olist;
		int row=0;
		if(addable){
             setRowCount(olist->size()+1 );
		} else {
            setRowCount(olist->size() );
		}
		olist->sort(NamedObjectPtrComp<PObject>());
        for( list<PObject*>::iterator it = olist->begin(); it != olist->end(); it++){
			createRow(row,*it);
			row++;
		}
        if(addable){
            createRow(row,0);
        }
        update();
        isloading=false;
	} else {qDebug("PObjectTable::load : given list was null, cannot load");}

}

void PObjectTable::currentChanged(int row, int col)
{
    qDebug() << "PObjectTable::currentChanged";
    if(addable && row == rowCount()-1){
        qDebug() << "Adding element";
        setRowCount(row+2);
        addElement(row);
	} else {
        qDebug() << QString("Do nothing Current changed: %1, %2").arg(row).arg(col);
	}
}

void PObjectTable::removeRow(int row)
{
	PObject *o=0;
	Transaction *t=Transactions::getCurrentTransaction();
	RepositoryProperty *prop = getProperty();
	PObject *parentObject = getParentObject();
	//int row = table->currentRow();
	if(prop && parentObject){
		t->add(parentObject);
		if(CollectionProperty *cp = dynamic_cast<CollectionProperty*>(prop)){
			startEdit();
			o=getObject(row);
            qDebug() << QString("PObjectTableControlerImpl::deleteSelected : deleting %1").arg(o->getName().c_str());
			cp->remove(o,parentObject);
            // todo : QTableWidget::removeRow(row);
            for(int i=row; i<rowCount(); i++) map_obj[i] = map_obj[i+1];
		}
	} else if(AbstractMapper *mapper=getMapper()) {
		 //o = mapper->create();
		qDebug("PObjectTable::removeRow : not implemented for basic collection");
		/*
		o = GuiCreateAction::getInstance()->create(mapper->getClassName());
		t->add(o);
		*/
	}
	
	update();
	
}

void PObjectTable::valueChanged(int row, int col)
{
	qDebug("PObjectTable::valueChanged");
    if(!isloading){
    this->startEdit(row);
	if(PObject *o= getObject(row)){
			RepositoryProperty *rp = map_prop[col];
			if(rp){
                rp->fromString(item(row,col)->text().toStdString(),o);
			} else {
                qDebug() << QString("PObjectTable::valueChanged: invalid property in map at %1").arg(col);
			}	
	} else {
        qDebug() << QString("PObjectTable::valueChanged: invalid object in list at %1").arg(row);
	}
     }
}

void PObjectTable::readRow(int row)
{
	if(PObject *o= getObject(row)){
			map<int,RepositoryProperty*>::iterator itp;
			for(itp=map_prop.begin(); itp != map_prop.end(); itp++){
				RepositoryProperty *rp = itp->second;
				int col = itp->first;
				if(rp){
                    rp->fromString(item(row,col)->text().toStdString(),o);
				} else {
                    qDebug() << QString("PObjectTable::readRow: invalid prop in list at %1").arg(col);
				}
			}
	} else {
        qDebug() << QString("PObjectTable::valueChanged: invalid object in list at %1").arg(row);
	}

}


void PObjectTable::addElement(int row)
{
	if(getControler()){
		getControler()->addElement(row);
	} else {
		qDebug("PObjectTable::addElement : controler not installed, could not add");
	}
}


void PObjectTable::createRow(int row, PObject *o)
{
	if(o){
		map_obj[row]=o;

		QString t;
        //setCellWidget(row,0, new PObjectLabel(0,o,this,true,false,false));
        setItem(row,0,new QTableWidgetItem(icon,""));

        for(int col=1; col<columnCount(); col++){
            RepositoryProperty *prop = map_prop[col];
            if(prop -> isPObject()){
                QPixmap i=GuiConfig::getInstance()->getIcon(prop->getType().c_str());
                QString t=QString::fromStdString(prop->asString(o));
                setItem(row,col,new QTableWidgetItem(icon,t));
                /*
				PObjectLabel *label = new PObjectLabel(prop,o ,this,false,false);
                setCellWidget(row,col,label);
                */
			} else if(prop -> isDate()){
				DateEditor *dateEditor = new DateEditor(o,prop,this);
				setCellWidget(row,col,dateEditor);
			} else {
                t = QString::fromStdString(prop->asString( o ));
                setItem(row, col, new QTableWidgetItem(t));
			}
		}
        setRowHeight( row, ROW_HEIGHT);


        //adjustRow(row);
    }/* else {
        for(int i=0; i<map_prop.size();i++){
            QTableWidgetItem *item=new QTableWidgetItem("+");
            setItem(row,i,item);
        }
    }*/
}


void PObjectTable::startEdit(RepositoryProperty *rp, PObject *parent)
{
	AbstractPropertyEditor::startEdit();
}

void PObjectTable::deleteSelected()
{
	int row = currentRow();
	removeRow(row);
}


/*!
    \fn PObjectTable::setControler(PObjectTableControler *controler)
 */
/*
void PObjectTable::setControler(PObjectTableControler *controler)
{
    this->controler = controler;
}
*/


/*!
    \fn PObjectTable::getMapper()
 */
AbstractMapper* PObjectTable::getMapper()
{
    	if(mapper){
		return mapper;
	} else if(prop){
		return MappingControler::getInstance()->getMapperByName(prop->getType());
	}
}


/*!
    \fn PObjectTable::getProperty()
 */
RepositoryProperty* PObjectTable::getProperty()
{
    return prop;
}


/*!
    \fn PObjectTable::getParentObject()
 */
PObject* PObjectTable::getParentObject()
{
    return parentObject;
}

void PObjectTable::showContextMenu( const QPoint & pos )
{	
    qDebug() << "Show context menu";
	if(getControler()){
        QMenu *popup = getControler()->getContextMenu(pos);
		if(popup){
            popup->popup(mapToGlobal(pos));
		} else {
            qDebug() << "PObjectTable::showContextMenu : WARNING : no popup from controler";
		}
	} else {
        qDebug() << "PObjectTable::showContextMenu : WARNING : no controler";
	}
}

PObjectTableControler* PObjectTable::getControler()
{
	if(!controler){
		if(PObjectTableControlerFactory* factory =PObjectTableControlerFactory::getInstance()){
			controler = factory->getControler(this);
			
		}
	}
	return controler;
}


PObjectTableItem::PObjectTableItem(QTableWidget * table)
    : QTableWidgetItem()
{

}
PObjectTableItem::PObjectTableItem(PObject *o, QTableWidget * table)
    : QTableWidgetItem()
{

}

QWidget* PObjectTableItem::createEditor() const
{
	/* create an editor - a combobox in our case
        ( (ComboItem*)this )->cb = new QComboBox( table()->viewport() );
        QObject::connect( cb, SIGNAL( activated( int ) ), table(), SLOT( doValueChanged() ) );
        cb->insertItem( "Yes" );
        cb->insertItem( "No" );
        // and initialize it
        cb->setCurrentItem( text() == "No" ? 1 : 0 );
        return cb;
	*/

}

void PObjectTableItem::setContentFromEditor(QWidget *w)
{
	/* the user changed the value of the combobox, so synchronize the
        // value of the item (its text), with the value of the combobox
        if ( w->inherits( "QComboBox" ) )
            setText( ( (QComboBox*)w )->currentText() );
        else
            QTableItem::setContentFromEditor( w );
	*/
}


PObjectTableDialog::PObjectTableDialog(list<PObject*> *data, string className, QWidget *parent, bool addable)
    : KDialog(parent)
{
    setButtons(Apply|Close);
	table = new PObjectTable(className, this); 
	table -> loadType(className);
	table -> load(data);
	setMainWidget(table);
}

void PObjectTableDialog::edit(list<PObject*> *data, string className, bool addable)
{
	PObjectTableDialog *instance = new PObjectTableDialog(data,className,0,addable);
	instance->exec();
}


