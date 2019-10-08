//
// C++ Implementation: mapperview
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "mapperview.h"

#include <QVBoxLayout>

#include "gui/guirepository.h"
#include "gui/base/guiconfig.h"
#include "datamodel/datamodelrepository.h"
#include "orm/mapping/mappingcontroler.h"
#include "services/utils/namedobjectptrcomp.h"

MapperView::MapperView(QWidget *parent, QStringList classList)
 : QListWidget(parent)
{
	/*
	list<AbstractMapper*> *listMappers = DataModelRepository::getInstance()->getPersistentClasses();
	for(list<AbstractMapper*>::iterator it = listMappers->begin(); it != listMappers->end(); it++)
	{
		new MapperViewItem((*it),this);
	}


	listMappers = GuiRepository::getInstance()->getPersistentClasses();
	for(list<AbstractMapper*>::iterator it = listMappers->begin(); it != listMappers->end(); it++)
	{
		new MapperViewItem((*it),this);
	}
	*/

	if( classList.empty() ){
		list<AbstractMapper*> *listMappers = MappingControler::getInstance()->getRegisteredClasses();
		listMappers->sort(NamedObjectPtrComp<AbstractMapper>());
		for(list<AbstractMapper*>::iterator it = listMappers->begin(); it != listMappers->end(); it++)
		{
			new MapperViewItem((*it),this);
		}
	} else {
		for ( QStringList::Iterator it = classList.begin(); it != classList.end(); ++it ) {
            AbstractMapper *mapper = MappingControler::getInstance()->getMapperByName((*it).toStdString());
			new MapperViewItem(mapper,this);
		}
	}

    //resize(600,800);
	
}




MapperView::~MapperView()
{
}


MapperViewItem::MapperViewItem(AbstractMapper *mapper, MapperView *parent) : QListWidgetItem(parent)
{
	this->mapper = mapper;
    setIcon(GuiConfig::getInstance()->getIcon(mapper->getClassName().c_str()));
    setText(mapper->getClassName().c_str());
};

AbstractMapper* MapperViewItem::getMapper()
{
	return this->mapper;
}

MapperDialog::MapperDialog(QWidget *parent, QStringList classList) : QDialog(parent)
{
    QVBoxLayout *la=new QVBoxLayout(this);
    QScrollArea *sa=new QScrollArea();
    sa->setWidgetResizable(true);
    mapperView = new MapperView(sa, classList);
    sa->setWidget(mapperView);
    la->addWidget(sa);
    setLayout(la);
    //ToDo: does chooser show up, add to layout ?
    //setMainWidget(mapperView);
    resize(400,400);
	
}

AbstractMapper* MapperDialog::getSelectedMapper()
{
	MapperViewItem *item = static_cast<MapperViewItem*>(mapperView ->currentItem());
	if(item){
		return item->getMapper();
	} else {
		qDebug("No item selected");
		return 0;
	}
}

AbstractMapper* MapperDialog::chooseMapper(QStringList classList)
{
	MapperDialog *instance = new MapperDialog(0,classList);
	instance->exec();
	return instance->getSelectedMapper();
}
