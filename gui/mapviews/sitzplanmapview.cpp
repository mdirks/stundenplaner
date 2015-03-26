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
#include "sitzplanmapview.h"
#include "datamodel/klasse.h"
#include "gui/dialogs/collectionselectiondialog.h"
#include "guirepository.h"
#include "gui/base/guiconfig.h"

#include "orm/repository/repository.h"
#include "orm/repository/repositoryproperty.h"

#include <qwmatrix.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>

SitzplanMapView::SitzplanMapView(SitzplanMap *spm, QWidget * parent, const char * name)
	: GenericMapView(parent,name)
{
    //QWMatrix wm = worldMatrix(); // set to convenient initial size
    //wm.scale(.7,.7);
    //setWorldMatrix(wm);
    setMap(spm);
    if(sitzplan *sp=spm->getSitzplan()){
        if(klasse *kl=sp->getKlasse()){
            QStringList displayList = GuiConfig::getInstance()->getDisplayProperties(
                    QString("SitzplanMapView::%1").arg(kl->getName().c_str()));
            list<teilleistung*> *listAlle = kl->getTeilleistungen();
            list<teilleistung*> *listDisplay = new list<teilleistung*>();
            for(int i=0;i<displayList.size(); i++){
                for(list<teilleistung*>::iterator it = listAlle->begin(); it != listAlle->end(); it++){
                    if(displayList.at(i) == (*it)->getName().c_str()){
                        listDisplay->push_back((*it));
                        break;
                    }
                }

            }
            spm->setDisplay(listDisplay);
        }
    }
}


SitzplanMapView::~SitzplanMapView()
{
}

void SitzplanMapView::configure()
{
    RepositoryProperty *rp = Repository::getInstance()->getRepositoryEntry("klasse")->
            getProperty("Teilleistungen");
    klasse *kl=getSitzplan()->getKlasse();
    CollectionSelectionDialog  *ce = new CollectionSelectionDialog(kl,rp,this);
    GuiRepository::getInstance()->showDialog(ce);

    list<teilleistung*> *listLeistungen = (list<teilleistung*>*) ce->getSelection();
    QStringList nameList;
    for(list<teilleistung*>::iterator it=listLeistungen->begin(); it!=listLeistungen->end(); it++){
        nameList.append((*it)->getName().c_str());
    }

    GuiConfig::getInstance()->setDisplayProperties(QString("SitzplanMapView::%1").arg(kl->getName().c_str()),
                                                   nameList);

    getSitzplanMap()->setDisplay(listLeistungen);
}


/*!
    \fn SitzplanMapView::setStundenplaneintrag(stundenplaneintrag *se)
 */
void SitzplanMapView::setStundenplaneintrag(stundenplaneintrag *se)
{
    this->se = se;
}


/*!
    \fn SitzplanMapView::getStundenplaneintrag()
 */
stundenplaneintrag* SitzplanMapView::getStundenplaneintrag()
{
    return this->se;
}

sitzplan* SitzplanMapView::getSitzplan()
{
	sitzplan *result=0;

    QGraphicsScene *c = scene();
	if(SitzplanMap *sm = dynamic_cast<SitzplanMap*>(c)){
		result = sm->getSitzplan();		
	}
	return result;
}


/*!
    \fn SitzplanMapView::getSitzplanMap()
 */
SitzplanMap* SitzplanMapView::getSitzplanMap()
{
    QGraphicsScene *c = scene();
    return dynamic_cast<SitzplanMap*>(c);
}


SitzplanMapViewDialog::SitzplanMapViewDialog(SitzplanMapView *spmv)
{
    QVBoxLayout *l =new QVBoxLayout(this);
    l->setSpacing(0);

    mapView = spmv;

    QToolBar *tb = new QToolBar(this);
    tb->addAction("Config",mapView,SLOT(configure()));


    l->addWidget(tb);
    l->addWidget(mapView);
}

SitzplanMapView* SitzplanMapViewDialog::getMapView()
{
    return mapView;
}

void SitzplanMapViewDialog::setStundenplaneintrag(stundenplaneintrag *se)
{
    mapView->setStundenplaneintrag(se);
}
