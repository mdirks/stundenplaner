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
#ifndef GUIPOPUPFACTORY_H
#define GUIPOPUPFACTORY_H

#include "gui/forms/formspopupfactory.h"
#include "gui/forms/pobjectmultiview.h"
#include "gui/mapviews/mapviewspopupfactory.h"
#include "gui/mapviews/genericmapview.h"
#include "gui/mapviews/weekmapview.h"
#include "gui/forms/mtreewidget.h"
#include "orm/persistence/pobject.h"

#include "actionpopup.h"
#include "pobjectaction.h"
/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class GuiPopupFactory : public FormsPopupFactory, public MapviewsPopupFactory {
public:
    GuiPopupFactory();
    ~GuiPopupFactory();

    static GuiPopupFactory* getInstance();
	
    QMenu* getPopupFor(PObjectIconView *iconView);
    QMenu* getPopupFor(PObjectMultiView *multiView);
    QMenu* getPopupFor(PObjectTable *table);
    QMenu* getPopupFor(MTreeWidgetItem *treeWidgetItem);
    QMenu* getPopupForGenericMapView(GenericMapView *mapView, QPoint pos);
    QMenu* getPopupForWeekMapView(WeekMapView *mapView, QPoint pos);
    QMenu* getActionPopupForObject(PObject *o);

private:
    list<PObjectAction*>* getActionsForObject(PObject *o);


private:
	static GuiPopupFactory* instance;
    map<QString,ActionPopup*> mapActionMenu;
    map<QString,list<PObjectAction*>*> mapActions;

};

#endif
