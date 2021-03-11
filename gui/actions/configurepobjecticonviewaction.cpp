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
#include "gui/forms/pobjectlistprovider.h"
#include "orm/mapping/mappingcontroler.h"

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
    iconView->setObjectListProvider(new MapperListProvider(GuiCreateAction::chooseMapper()));
}

void ConfigurePObjectIconViewAction::newIconView()
{
	PObjectIconView *iconView = new PObjectIconView();
	GuiRepository::getInstance()->addTool(iconView, "Unbekannt", "Unbekannt");
}
void ConfigurePObjectIconViewAction::chooseProperty()
{
    PObjectListProvider *prov = iconView->getProvider();
    QString className = prov->getClassName();
    AbstractMapper *mapper = MappingControler::getInstance()->getMapperByName(className.toStdString());
	if(mapper){
		RepositoryProperty *rp = PropertyChooserDialog::chooseProperty(mapper);
		if(rp){
            qDebug() << QString("Chosen property: %1").arg(rp->getName().c_str());
		}
	}

}
void ConfigurePObjectIconViewAction::addNewObject()
{
    PObjectListProvider *prov = iconView->getProvider();
    if(prov){
        PObject *o = prov->addNewObject();
        if(o) iconView->reload();
    }
}

void ConfigurePObjectIconViewAction::deleteSelected()
{
	PObjectIconViewItem *item = static_cast<PObjectIconViewItem*>(iconView->currentItem());
	if(item){
		PObject *o = item->getObject();
        PObjectListProvider *prov = iconView->getProvider();
        prov->deleteObject(o);
        delete item;

	}
}

void ConfigurePObjectIconViewAction::showForm()
{
    PObjectIconViewItem *item = static_cast<PObjectIconViewItem*>(iconView->currentItem());
    if(item){
        PObject *o = item->getObject();
        GuiRepository::getInstance()->showFormForObject(o);

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
    PObjectListProvider *prov = iconView->getProvider();
    if(RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry(prov->getClassName().toStdString())){
            AbstractFilter *f = FilterEditorDialog::createFilter(re);
            iconView->setFilter(f);
            iconView->reload();
	} else {
        qDebug() << "ConfigurePObjectIconViewAction::createFilter : mapper not set, aborting";
	}
}

void ConfigurePObjectIconViewAction::clearFilter()
{
    iconView->clearFilter();
}
