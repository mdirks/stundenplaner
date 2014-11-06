/***************************************************************************
 *   Copyright (C) 2008 by Marcus Dirks   *
 *   m-dirks@web.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "configurepobjecticonviewaction.h"
#include "guicreateaction.h"
#include "gui/guirepository.h"
#include "gui/base/guiconfig.h"
#include "gui/dialogs/propertychooser.h"
#include "gui/dialogs/filtereditor.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/repository/collectionproperty.h"
#include "orm/transactions/transactions.h"

#include <QDebug>

ConfigurePObjectIconViewAction::ConfigurePObjectIconViewAction(PObjectIconView *iconView)
{
	this->iconView = iconView;

}


ConfigurePObjectIconViewAction::~ConfigurePObjectIconViewAction()
{
}




/*!
    \fn ConfigurePObjectIconViewAction::configure()
 */
void ConfigurePObjectIconViewAction::configure()
{
    iconView->setMapper(GuiCreateAction::chooseMapper());
}

void ConfigurePObjectIconViewAction::newIconView()
{
	PObjectIconView *iconView = new PObjectIconView();
	GuiRepository::getInstance()->addTool(iconView, "Unbekannt", "Unbekannt");
}
void ConfigurePObjectIconViewAction::chooseProperty()
{
	AbstractMapper *mapper = iconView->getMapper();
	if(mapper){
		RepositoryProperty *rp = PropertyChooserDialog::chooseProperty(mapper);
		if(rp){
            qDebug() << QString("Chosen property: %1").arg(rp->getName().c_str());
		}
	}

}
void ConfigurePObjectIconViewAction::addNewObject()
{
	PObject *o;
	RepositoryProperty *prop = iconView->getProperty();
	PObject *parentObject = iconView->getParentObject();
	if(prop && parentObject){
		//string className = prop->getType();
		o = GuiCreateAction::getInstance()->create(prop->getType());
		
	} else if(AbstractMapper *mapper=iconView->getMapper()) {
		 o = GuiCreateAction::getInstance()->create(mapper->getClassName());
	}
	iconView->addObject(o);
}

void ConfigurePObjectIconViewAction::deleteSelected()
{
	PObjectIconViewItem *item = static_cast<PObjectIconViewItem*>(iconView->currentItem());
	if(item){
		PObject *o = item->getObject();
		RepositoryProperty *prop=iconView->getProperty();
		PObject *parentObject = iconView->getParentObject();
		if(prop && parentObject && prop->isCollection()){
			CollectionProperty *colProp = dynamic_cast<CollectionProperty*>(prop);
			if(colProp){
				colProp->remove( o,parentObject);
			}
			delete item;
		} else if (AbstractMapper *mapper = iconView->getMapper()){
			mapper->remove(o);
			Transactions::getCurrentTransaction()->add(o);
			delete item;
		}
	}
}

void ConfigurePObjectIconViewAction::switchView()
{
    if(iconView->getTableView())
    {
        iconView->hide();
        iconView->getTableView()->show();
    }
}
void ConfigurePObjectIconViewAction::selectIcon()
{
	PObjectIconViewItem *item = dynamic_cast<PObjectIconViewItem*>(iconView->currentItem());
	if(item){
		GuiConfig::getInstance()->selectIcon(item->getObject());
	}
}

void ConfigurePObjectIconViewAction::createFilter()
{
	if(AbstractMapper *mapper = iconView->getMapper()){
		if(RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry(mapper->getClassName())){
			FilterEditorDialog::createFilter(re);
		}
	} else {
        qDebug() << "ConfigurePObjectIconViewAction::createFilter : mapper not set, aborting";
	}
}
