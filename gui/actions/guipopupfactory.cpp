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
#include "guipopupfactory.h"
#include "datenpopup.h"
#include "configurepobjecticonviewaction.h"
#include "genericmapviewcontroler.h"
#include "weekmapviewcontroler.h"

#include "gui/mapviews/genericmapview.h"
#include "gui/forms/pobjecticonviewitem.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/repository/repositoryentry.h"


#include <QAction>
#include <QDebug>
#include <KAction>

GuiPopupFactory* GuiPopupFactory::instance = 0;

GuiPopupFactory* GuiPopupFactory::getInstance()
{
	if(!instance){
		instance = new GuiPopupFactory();
	}	
	return instance;
}

QMenu* GuiPopupFactory::getPopupForWeekMapView(WeekMapView *mapView, QPoint pos)
{
	WeekMapViewControler *controler = new WeekMapViewControler(mapView);

    QMenu *pmenu = getPopupForGenericMapView(mapView,pos);

    pmenu->addAction("Stundenplan",  controler, SLOT(readStundenplan()));
    //(new KAction("Stundenplan", KStdAccel::shortcut(KStdAccel::New), controler,SLOT(readStundenplan()), mapView, "zoomout"))->plug(pmenu);
	
	return pmenu;
}

QMenu* GuiPopupFactory::getPopupForGenericMapView(GenericMapView *mapView, QPoint pos)
{
    qDebug() << "Warning : GuiPopupFactory::getPopupForGenericMapView : do nothing implementation";
    /*
	GenericMapViewControler *controler = new GenericMapViewControler(mapView,pos);
	
	QPopupMenu *pmenu = new QPopupMenu(mapView);


	PObjectGraphicsItemNP *selectedItem =mapView->getSelected();
	if(selectedItem){
		if(PObject *o = selectedItem->getObject()){
			if(stundenplaneintrag *se = dynamic_cast<stundenplaneintrag*>(o)){
				(new ShowSitzplanAction(se,mapView))->plug(pmenu);
				krusbucheintrag *ke = se->getKursbuchEintrag();
				if(ke){
					RepositoryProperty *rp=Repository::getInstance()->getRepositoryEntry("krusbucheintrag")->getProperty("Eintrag");
					(new ShowPropertyAction(ke,rp,mapView))->addTo(pmenu);
				}

				klasse *kl = se->getKlasse();
				if(kl){
					RepositoryProperty *rp=Repository::getInstance()->getRepositoryEntry("klasse")->getProperty("Kursbuch");
					(new ShowPropertyAction(kl,rp,mapView))->addTo(pmenu);
				}
			}
		}
		
		
		(new KAction("Rauf", KStdAccel::shortcut(KStdAccel::New), controler,SLOT(itemUp()), mapView, "activate"))->plug(pmenu);
		
		( new KAction("Runter", KStdAccel::shortcut(KStdAccel::New), controler,SLOT(itemDown()), mapView, "activate") )->plug(pmenu);

		( new KAction("Anzeigen", KStdAccel::shortcut(KStdAccel::New), controler,SLOT(activateSelected()), mapView, "activate") )->plug(pmenu);

		( new KAction("Formular", KStdAccel::shortcut(KStdAccel::New), controler,SLOT(showFormForSelected()), mapView, "activate") )->plug(pmenu);

		( new KAction("Löschen", KStdAccel::shortcut(KStdAccel::New), controler,SLOT(deleteSelected()), mapView, "activate") )->plug(pmenu);
	
		( new KAction("Latex", KStdAccel::shortcut(KStdAccel::New), controler,SLOT(writeLatex()), mapView, "activate") )->plug(pmenu);

		if(PObject *o = selectedItem->getObject()){
			pmenu->insertItem("Daten",new DatenPopup(o,mapView));
		}

	} else {
		( new KAction("Vergrößern", KStdAccel::shortcut(KStdAccel::New), controler,SLOT(zoomIn()), mapView, "zoomin") )->plug(pmenu);
	
		
		( new KAction("Verkleinern", KStdAccel::shortcut(KStdAccel::New), controler,SLOT(zoomOut()), mapView, "zoomout") )->plug(pmenu);

	
		( new KAction("Neues Element", KStdAccel::shortcut(KStdAccel::New), controler,SLOT(createNewItem()), mapView, "create_new") )->plug(pmenu);
		
	}

	return pmenu;
	*/

}
QMenu* GuiPopupFactory::getPopupFor(PObjectMultiView *multiView)
{
    QMenu *pmenu=0;
    if(multiView->isIconView())
    {
        PObjectIconView *iconView = multiView->getIconView();
        pmenu=getPopupFor(iconView);
    } else {
        PObjectTable *table=multiView->getTable();
        pmenu=getPopupFor(table);
    }
    pmenu->addAction("Tabellenansicht", multiView, SLOT(switchView()));

    return pmenu;

}

QMenu* GuiPopupFactory::getPopupFor(PObjectTable *table)
{
    return table->getControler()->getContextMenu(QPoint(0,0));
}

/*!
    \fn GuiPopupFactory::getPopupFor(PObjectIconView *iconView)
 */
QMenu* GuiPopupFactory::getPopupFor(PObjectIconView *iconView)
{
		ConfigurePObjectIconViewAction *confAction = new ConfigurePObjectIconViewAction(iconView);

        QMenu* pmenu = new QMenu(iconView);
		
        pmenu->addAction("Neu laden",iconView,SLOT(reload()));
        pmenu->addAction("Neues Element",  confAction, SLOT(addNewObject()));

        pmenu->addAction("Filter setzen",  iconView, SLOT(chooseFilter()));
        pmenu->addAction("Neuer Objectbrowser", confAction, SLOT(newIconView()));
        pmenu->addAction("Konfigurieren", confAction, SLOT(configure()));
        pmenu->addAction("Icon wählen", confAction, SLOT(selectIcon()));

        /*
		action = new KAction("Delete Item", KStdAccel::shortcut(KStdAccel::New), confAction,SLOT(deleteSelected()), iconView, "del");
		action->plug(pmenu);
	
		action = new KAction("Choose Property", KStdAccel::shortcut(KStdAccel::New), confAction,SLOT(chooseProperty()), iconView, "del");
		action->plug(pmenu);
	
		action = new KAction("CreateFilter", KStdAccel::shortcut(KStdAccel::New), confAction,SLOT(createFilter()), iconView, "del");
		action->plug(pmenu);
        */

		PObjectIconViewItem *item = dynamic_cast<PObjectIconViewItem*>(iconView->currentItem());
		if(item){
			PObject *o = item->getObject();
			if(o){
                pmenu->addMenu(new DatenPopup(o,iconView));
			}
		}


		return pmenu;
}
