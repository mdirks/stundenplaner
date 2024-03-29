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
#include <QAction>

GuiPopupFactory* GuiPopupFactory::instance = 0;

GuiPopupFactory* GuiPopupFactory::getInstance()
{
	if(!instance){
		instance = new GuiPopupFactory();
	}	
	return instance;
}

GuiPopupFactory::GuiPopupFactory()
{
    PObjectAction *a= new AddToRemarkableAction();
    addToActionMenu("lektuere",a);
    addToActionMenu("bookmark",a);

    addToActionMenu("lektuere",new ImportToDocStoreAction());
    addToActionMenu("lektuere", new WriteBookmarksToRmAction());



    a = new AddToThemaAction("To Thema");
    addToActionMenu("notiz", a);
    addToActionMenu("tweet", a);
    addToActionMenu("kopie", a);
    addToActionMenu("material",a);
    addToActionMenu("lektuerenotiz",a);
    addToActionMenu("bookmark",a);

    a=new VocImportAction("Import");
    addToActionMenu("vokabelliste",a);



}

void GuiPopupFactory::addToActionMenu(const QString className, PObjectAction *a )
{
    list<PObjectAction*> *la = mapActions[className];
    if(la ==0){
        la = new list<PObjectAction*>();
        mapActions[className] = la;
    }
    la->push_back(a);
}

QMenu* GuiPopupFactory::getPopupForThemaMapView(ThemaMapView *mapView, QPoint pos)
{
    //WeekMapViewControler *controler = new WeekMapViewControler(mapView);

    QMenu *pmenu = getPopupForGenericMapView(mapView,pos);

    //pmenu->addAction("Stundenplan",  controler, SLOT(readStundenplan()));
    //(new QAction("Stundenplan", KStdAccel::shortcut(KStdAccel::New), controler,SLOT(readStundenplan()), mapView, "zoomout"))->plug(pmenu);

    return pmenu;
}



QMenu* GuiPopupFactory::getPopupForWeekMapView(WeekMapView *mapView, QPoint pos)
{
	WeekMapViewControler *controler = new WeekMapViewControler(mapView);

    QMenu *pmenu = getPopupForGenericMapView(mapView,pos);

    pmenu->addAction("Stundenplan",  controler, SLOT(readStundenplan()));
    //(new QAction("Stundenplan", KStdAccel::shortcut(KStdAccel::New), controler,SLOT(readStundenplan()), mapView, "zoomout"))->plug(pmenu);
	
	return pmenu;
}

QMenu* GuiPopupFactory::getPopupForGenericMapView(GenericMapView *mapView, QPoint pos)
{
    qDebug() << "Warning : GuiPopupFactory::getPopupForGenericMapView : do nothing implementation";

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

QMenu* GuiPopupFactory::getPopupFor(PObjectDisplay *objectDisplay)
{
    QMenu* pmenu = new QMenu(objectDisplay);
    pmenu->addAction("Neu laden",objectDisplay,SLOT(removeClickedItem()));
    PObjectDisplayItem *item = dynamic_cast<PObjectDisplayItem*>(objectDisplay->currentItem());
    if(item){
        PObject *o = item->getObject();
        if(o){
            pmenu->addMenu(new DatenPopup(o,objectDisplay));
            QMenu *am = getActionPopupForObject(o);
            if(am){
                pmenu->addMenu(am);
            }


        }
    }
    return pmenu;
}

QMenu* GuiPopupFactory::getPopupFor(PObjectIconView *iconView)
{
		ConfigurePObjectIconViewAction *confAction = new ConfigurePObjectIconViewAction(iconView);

        QMenu* pmenu = new QMenu(iconView);
		
        pmenu->addAction("Neu laden",iconView,SLOT(reload()));
        pmenu->addAction("Neues Element",  confAction, SLOT(addNewObject()));
        pmenu->addAction("Formular", confAction, SLOT(showForm()));
        pmenu->addAction("Löschen",  confAction,SLOT(deleteSelected()));

        pmenu->addAction("Filter setzen",  confAction, SLOT(createFilter()));
        pmenu->addAction("Filter loeschen",  confAction, SLOT(clearFilter()));
        pmenu->addAction("Neuer Objectbrowser", confAction, SLOT(newIconView()));
        pmenu->addAction("Konfigurieren", confAction, SLOT(configure()));
        pmenu->addAction("Icon wählen", confAction, SLOT(selectIcon()));


	
        /*
		action = new QAction("Choose Property", KStdAccel::shortcut(KStdAccel::New), confAction,SLOT(chooseProperty()), iconView, "del");
		action->plug(pmenu);
	
		action = new QAction("CreateFilter", KStdAccel::shortcut(KStdAccel::New), confAction,SLOT(createFilter()), iconView, "del");
		action->plug(pmenu);
        */

        QListWidgetItem *witem=iconView->currentItem();
        if(PObjectIconViewItemBase *item = dynamic_cast<PObjectIconViewItemBase*>(witem)){
			PObject *o = item->getObject();
			if(o){
                pmenu->addMenu(new DatenPopup(o,iconView));
                QMenu *am = getActionPopupForObject(o);
                if(am){
                    pmenu->addMenu(am);
                }


			}
		}


		return pmenu;
}

QMenu* GuiPopupFactory::getActionPopupForObject(PObject *o)
{

    if(o==0)
    {
        qWarning("GuiRepositoryImp::getFormForObject: Null objet given given");
        return 0;
    }


    ActionPopup *am=0;
    QString className(o->getPersistenceObject()->getClassName().c_str());

    map<QString,ActionPopup*>::iterator it = mapActionMenu.find(className);
    if(it != mapActionMenu.end()){
        am = it->second;
        if(am){
            am->setPObject(o);
        }
    } else {
            list<PObjectAction*> *la=getActionsForObject(o);
            if(la){
                am = new ActionPopup();
                for(list<PObjectAction*>::iterator it=la->begin();it!=la->end();it++){
                    am->addAction(*it);
                }
                am->setPObject(o);
            }
    }
    return am;
}

list<PObjectAction*>* GuiPopupFactory::getActionsForObject(PObject *o)
{
    if(o==0)
    {
        qWarning("GuiRepositoryImp::getFormForObject: Null objet given given");
        return 0;
    }



    QString className = QString(o->getPersistenceObject()->getClassName().c_str());

    list<PObjectAction*> *al=0;
    map<QString,list<PObjectAction*>*>::iterator it = mapActions.find(className);
    if(it != mapActions.end()){
        al = it->second;
    }
    return al;
}
