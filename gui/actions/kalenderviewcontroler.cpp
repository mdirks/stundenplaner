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
#include "kalenderviewcontroler.h"

#include "datamodel/stundenplaneintrag.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/repository.h"
#include "gui/forms/textpropertyviewer.h"

#include <QDebug>

KalenderViewControler::KalenderViewControler(KalenderView *kview)
	: WeekMapViewControler(kview->mapView)
{
	isPlanning = false;
	
}


KalenderViewControler::~KalenderViewControler()
{
}




/*!
    \fn KalenderViewControler::togglePlanning()
 */
void KalenderViewControler::togglePlanning()
{
    isPlanning = (! isPlanning);
    qDebug() << QString("Planning set to %1").arg(isPlanning);
}


QMenu* KalenderViewControler::getPopupMenu()
{
    QMenu *pmenu = WeekMapViewControler::getPopupMenu();

    //	( new QAction("Toggle Planung", KStdAccel::shortcut(KStdAccel::New), this,SLOT(togglePlanning()), mapView, "activate") )->plug(pmenu);

	return pmenu;
}

void KalenderViewControler::activateSelected(PObjectGraphicsItemNP *selectedItem)
{
	if(selectedItem){
		if(PObjectGraphicsItemNP* pitem = dynamic_cast<PObjectGraphicsItemNP*>(selectedItem)){
			if(PObject *o = pitem->getObject()){
				stundenplaneintrag *se = dynamic_cast<stundenplaneintrag*>(o);
				if ( se ){
					if( isPlanning ){
						RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry(se);
						if(re){
							RepositoryProperty *rp = re->getProperty("Verlauf");
							TextPropertyEditorDialog::edit(rp,se);
						} else {
                            qDebug() << "GenericMapViewControler::activateSelected : strange : could not get stundenplaneintrag";
						}

					} else {
						krusbucheintrag *ke = se->getKursbuchEintrag();
						RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry(ke);
						if(re){
							RepositoryProperty *rp = re->getProperty("Eintrag");
							TextPropertyEditorDialog::edit(rp,ke);
						} else {
                            qDebug() << "GenericMapViewControler::activateSelected : strange : could not get kursbucheintrag";
						}
					}
				} else {
					GenericMapViewControler::activateSelected(selectedItem);
				}
			}
		}
	}
}
