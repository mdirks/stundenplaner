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

//#include <qwmatrix.h>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>




SitzplanMapView::SitzplanMapView(SitzplanMap *spm, QWidget * parent, const char * name)
	: GenericMapView(parent,name)
{
    //QWMatrix wm = worldMatrix(); // set to convenient initial size
    //wm.scale(.7,.7);
    //setWorldMatrix(wm);

    if(spm){
        setSitzplanMap(spm);
    }
    /*
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
    */
}

void SitzplanMapView::setSitzplanMap(SitzplanMap *spm){
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
    std::map<schueler*,fehlzeit*> mf;
    list<fehlzeit*> *lf = se->getFehlzeiten();
    for(list<fehlzeit*>::iterator it=lf->begin(); it!=lf->end(); it++){
        fehlzeit *f =*it;
        schueler* s = f->getSchueler();
        mf[s]=f;
    }
    QGraphicsScene *c = scene();
    if(SitzplanMap *sm = dynamic_cast<SitzplanMap*>(c)){
        list<PObjectGraphicsItem*> *lgi = sm->getGraphicsItems();
        for(list<PObjectGraphicsItem*>::iterator it=lgi->begin(); it!=lgi->end(); it++){
            if(PlatzGraphicsItem *pgi = dynamic_cast<PlatzGraphicsItem*>(*it)){
                if(mf[pgi->getPlatz()->getSchueler()]){
                    pgi->setFehlend(true);
               } else {
                    pgi->setFehlend(false);
                }
                pgi->update();
            }
        }
    }
    update();
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
    kl=0;


    if(spmv){
        mapView = spmv;
    } else {
        mapView = new SitzplanMapView(0,this);
    }

    QToolBar *tb = new QToolBar(this);
    tb->addAction("Config",mapView,SLOT(configure()));

    QVBoxLayout *l=new QVBoxLayout(this);
    l->setSpacing(0);
    l->addWidget(tb);
    l->addWidget(mapView);

}

SitzplanMapView* SitzplanMapViewDialog::getMapView()
{
    return mapView;
}

void SitzplanMapViewDialog::setStundenplaneintrag(stundenplaneintrag *se)
{
    if(kl != se->getKlasse()){ // if klasse changed fetch sitzplan
        kl=se->getKlasse();
        sitzplan *sp = kl->getSitzplan();
        if(sp){
            SitzplanMap *spm = GuiRepository::getInstance()->getMapForSitzplan(sp);
            if(spm){
                mapView->setSitzplanMap(spm);
            }
        }
    }
    mapView->setStundenplaneintrag(se);
}

void SitzplanMapViewDialog::setParentObject(PObject *o)
{
    if(stundenplaneintrag *se = dynamic_cast<stundenplaneintrag*>(o)){
        setStundenplaneintrag(se);
    } else {
        qDebug() << "WARNING: SitzplanMapViewDialog::setParentObject: can handle stundenplaneintrag only";
    }
}
