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
#include "sitzplanmapviewcontroler.h"

#include "datamodel/schueler.h"
#include "datamodel/platz.h"
#include "datamodel/teilleistungmapper.h"
#include "guicreateaction.h"
#include "gui/guirepository.h"
#include "gui/forms/pobjectdialog.h"
#include "orm/transactions/transactions.h"
#include "gui/forms/pobjecttable.h"
#include "services/reports/latexoutput.h"

#include <kfiledialog.h>
#include <kinputdialog.h>

SitzplanMapViewControler::SitzplanMapViewControler(SitzplanMapView *smapView)
	: GenericMapViewControler(smapView)
{
	this->smapView = smapView;
}


SitzplanMapViewControler::~SitzplanMapViewControler()
{
}


QMenu* SitzplanMapViewControler::getPopupMenu()
{
    QMenu *pmenu = GenericMapViewControler::getPopupMenu();


    pmenu->addAction("Stundenbewertung",  this,SLOT(addStundenbewertung()));
    pmenu->addAction("Fehlzeit",this,SLOT(addFehlzeit()));
    pmenu->addAction("Schüler", this,SLOT(addSchueler()));
    pmenu->addAction("Add Plaetze",this,SLOT(addPlaetze()));
    pmenu->addAction("Add Teilleistung", this,SLOT(addTeilleistung()));
    pmenu->addAction("Fehlzeiten", this,SLOT(showFehlzeitenForSchueler()));
    pmenu->addAction("Fehlzeiten (Latex)", this,SLOT(writeFehlzeitenForSchueler()));
    pmenu->addAction("Bewertungen", this,SLOT(showStundenbewertungenForSchueler()));



	return pmenu;
}

void SitzplanMapViewControler::showFehlzeitenForSchueler()
{
	list<PObject*> *lf = (list<PObject*>*) getFehlzeitenForSchueler();
	if(lf){
        qDebug() << QString("Found %1 Fehlzeiten").arg(lf->size());
		PObjectTableDialog::edit(lf,"fehlzeit");
    } else {qDebug() << "No schueler selected";}
}

void SitzplanMapViewControler::writeFehlzeitenForSchueler()
{
	list<fehlzeit*> *l_f = getFehlzeitenForSchueler();
	QString fileName = KFileDialog::getSaveFileName();

	LatexOutput *lout = new LatexOutput(QString("Testoutput"),fileName);
	if(lout){
		lout -> write(l_f);
		lout -> close();
		lout -> edit();
	}	

	delete lout;
}

void SitzplanMapViewControler::toggleFehlzeitenBewertung()
{
	if(fehlzeitmode=true) fehlzeitmode=false;
	else fehlzeitmode=true;
}

void SitzplanMapViewControler::showStundenbewertungenForSchueler()
{
	PObject *o = smapView->getSelectedObject();
	if(platz *pl = dynamic_cast<platz*>(o)){
		if(schueler *s = pl->getSchueler()){
			list<PObject*> *lf = (list<PObject*>*) s->getStundenbewertungen();
			if(lf){
				PObjectTableDialog::edit(lf,"stundenbewertung");
			} 
        }else {qDebug() << "No schueler selected";}
    }else {qDebug() << "No platze selected";}
}

void SitzplanMapViewControler::addStundenbewertung()
{
	PObject *o = smapView->getSelectedObject();
	if(platz *pl = dynamic_cast<platz*>(o)){
		if(schueler *s = pl->getSchueler()){
			stundenbewertung *sb = (stundenbewertung*) GuiCreateAction::getInstance()->create("stundenbewertung");
			sb->setStundenplaneintrag(smapView->getStundenplaneintrag());
			sb->setSchueler(s);
			s->addToStundenbewertungen(sb);
			stundenplaneintrag *se = smapView->getStundenplaneintrag();
			se->addToBewertungen(sb);

			RepositoryEntry  *re = Repository::getInstance()->getRepositoryEntry("stundenbewertung");
			list<RepositoryProperty*> *list_prop = new list<RepositoryProperty*>();
			list_prop->push_back(re->getProperty("Bewertung"));
			list_prop->push_back(re->getProperty("Bemerkung"));
			GuiRepository::getInstance()->showDialogForObject(sb, list_prop);
		}
	}
}

void SitzplanMapViewControler::addFehlzeit()
{
	PObject *o = smapView->getSelectedObject();
	if(platz *pl = dynamic_cast<platz*>(o)){
		if(schueler *s = pl->getSchueler()){
			fehlzeit *fz = (fehlzeit*) GuiCreateAction::getInstance()->create("fehlzeit");
			stundenplaneintrag *se = smapView->getStundenplaneintrag();
			fz->setStundenplaneintrag(se);
			fz->setSchueler(s);

            fz->setVon(QDateTime(se->getDatum()));
            fz->setBis(QDateTime(se->getDatum()));
			s->addToFehlzeiten(fz);
			se->addToFehlzeiten(fz);
			Transactions::getCurrentTransaction()->add(s);
			Transactions::getCurrentTransaction()->add(se);
	
			/* If edit after create required uncoment here*/
			//GuiRepository::getInstance()->showDialogForObject(fz);
        } else {qDebug() << "SitzplanMapViewControler::addFehlzeit : could not get Schueler";}
    } else {qDebug() << "SitzplanMapViewControler::addFehlzeit : could not get platz";}
}

void SitzplanMapViewControler::addSchueler()
{
   if(sitzplan *sp = smapView->getSitzplan()){
	if( sp->getKlasse()){
		PObjectDialog::choosePObject((list<PObject*>*)sp->getKlasse()->getSchueler());
	}
   } else {
    qDebug() << "SeatMap::zeigeSchueler(): invalid sitzplan or klasse, could not get schueler";
   }

}

void SitzplanMapViewControler::addPlaetze()
{
	int n = KInputDialog::getInteger("Wieviele ?","Anzahl",1,1,30,1,10);
    qDebug() << QString("Adding %1 plaetze").arg(n);
    QPointF where = smapView->mapToScene(GenericMapViewControler::pos);
    for(int i=0; i<n; i++){
		platz *pl = (platz*) GuiCreateAction::getInstance()->create("platz");
        qDebug() << QString("Created platz %1").arg(i);
		if(SitzplanMap *sm = smapView->getSitzplanMap()){
            sm->addPlatzItem(pl, where.toPoint()+ QPoint(i*120,0));
			Transactions::getCurrentTransaction()->add(sm);
            qDebug() << "Added to SitzplanMap";
		}
	
		if(sitzplan *sp = smapView->getSitzplan()){
			sp->addToPlaetze(pl);
			Transactions::getCurrentTransaction()->add(sp);
            qDebug() << "Added to sitzplan";
		}
	}	
}

void SitzplanMapViewControler::activateSelected(PObjectGraphicsItemNP *selectedItem){
	bool done=false;
	if(selectedItem){
		if(PObjectGraphicsItemNP* pitem = dynamic_cast<PObjectGraphicsItemNP*>(selectedItem)){
			if(PObject *o = pitem->getObject()){
				if (platz *pl = dynamic_cast<platz*>(o) ){
					if(schueler *s=pl->getSchueler()){
						GuiRepository::getInstance()->showFormForObject(s);				
					} 
					done = true;
				}
			} 
		}
	}
	if(!done){
		GenericMapViewControler::activateSelected(selectedItem);
	}
}

void SitzplanMapViewControler::addTeilleistung()
{
	 if(sitzplan *sp = smapView->getSitzplan()){
		if( klasse *kl = sp->getKlasse()){
			teilleistung *tl = (teilleistung*) teilleistungmapper::getInstance()->create();
			QString name = KInputDialog::getText("Name der Teilleistung","Name");
            tl->setName(name.toStdString());
			kl->addToTeilleistungen(tl);

			
		}
	}
	
}

/*!
    \fn SitzplanMapViewControler::getFehlzeitenForSchueler()
 */
list<fehlzeit*>* SitzplanMapViewControler::getFehlzeitenForSchueler()
{
	PObject *o = smapView->getSelectedObject();
	if(platz *pl = dynamic_cast<platz*>(o)){
		if(schueler *s = pl->getSchueler()){
			return s->getFehlzeiten();
        } else {qDebug() << "SitzplanMapViewControler::getFehlzeitenForSchueler:  no schueler";}
    } else {qDebug() << "SitzplanMapViewControler::getFehlzeitenForSchueler:  no platz";}

    qDebug() << "SitzplanMapViewControler::getFehlzeitenForSchueler:  no schueler";
	return 0;
}
