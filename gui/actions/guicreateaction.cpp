//
// C++ Implementation: createaction
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "guicreateaction.h"
#include "gui/forms/mapperview.h"
#include "gui/guirepository.h"
#include "datamodel/datamodelrepository.h"
#include "datamodel/material.h"
#include "datamodel/lektuere.h"
#include "datamodel/stundenplan.h"
#include "gui/data/weekmap.h"
#include "gui/forms/pobjectdialog.h"
#include "services/utils/datedialog.h"
#include "orm/mapping/mappingcontroler.h"
#include "datamodel/stundenplaneintrag.h"
#include "services/sstundenplan.h"
#include "services/skalender.h"
#include "gui/base/guiconfig.h"


#include <QFile>
#include <QDebug>

#include <KDialog>
#include <kinputdialog.h>
#include <kfiledialog.h>

GuiCreateAction* GuiCreateAction::instance=0;

GuiCreateAction::GuiCreateAction()
{
    mapper=0;
}


GuiCreateAction::~GuiCreateAction()
{
}




/*!
    \fn GuiCreateAction::getInstance()
 */
GuiCreateAction* GuiCreateAction::getInstance()
{
    	if(! instance){
		instance = new GuiCreateAction();

   	}
	return instance;
}


/*!
    \fn GuiCreateAction::create()
 */

PObject*  GuiCreateAction::createObject()
{
	PObject *res=0;
    	if( ! mapper){
		mapper = chooseMapper();
    	}

	if(mapper){
		//res = mapper->create();
		res = create(mapper->getClassName());
	}

	mapper=0;
	return res;
}


PObject*  GuiCreateAction::createObject(QStringList classList)
{
	PObject *res=0;
	mapper = chooseMapper(classList);
    	

	if(mapper){
		//res = mapper->create();
		res = create(mapper->getClassName());
	}

	mapper=0;
	return res;
}

AbstractMapper* GuiCreateAction::chooseMapper()
{
	return MapperDialog::chooseMapper();
}


AbstractMapper* GuiCreateAction::chooseMapper(QStringList classList)
{
	return MapperDialog::chooseMapper(classList);
}


void GuiCreateAction::addStundenplaneintrag()
{

    int tag = KInputDialog::getInteger("Tag","Tag der Stunde",1,1,7,1,10);
    if(tag>0){
        int stunde = KInputDialog::getInteger("StundenNr.", "Nr. der Stunde",1,1,10,1,10);
        if(stunde>0){
            schuljahr *sj = GuiConfig::getInstance()->getActiveSchuljahr();
            if(!sj){qDebug("Strange: no active Schuljahr"); return;}
            klasse *kl=(klasse*) PObjectDialog::choosePObject((list<PObject*>*)sj->getKlassen());
            if(kl){
                stundenplantemplateeintrag *te=SStundenplan::getInstance()->
                        createTemplateEintrag(tag,stunde,kl);
            }
        }
    }
}


/*!
    \fn CreateAction::create(string className)
 */
PObject* GuiCreateAction::create(string className)
{
    PObject *o=0;

	if(className == "stundenplantemplateeintrag"){

        qDebug() << "Stundenplaneintraege should be added via addStundenplaneintrag";
        /*
        schuljahr *sj = GuiConfig::getInstance()->getActiveSchuljahr();

		int tag = KInputDialog::getInteger("Tag","Tag der Stunde",1,1,7,1,10);
		int stunde = KInputDialog::getInteger("StundenNr.", "Nr. der Stunde",1,1,10,1,10);
		
        klasse *kl;
        if(sj){
            kl=(klasse*) PObjectDialog::choosePObject((list<PObject*>*)sj->getKlassen());
		} else {
            kl=(klasse*) PObjectDialog::choosePObject(MappingControler::getInstance()->getMapperByName( "klasse" ) );
		}
        //klasse *kl = dynamic_cast<klasse*>(oo);


        AbstractMapper *mapper = MappingControler::getInstance()->getMapperByName("stundenplantemplateeintrag");

        stundenplantemplateeintrag *te = (stundenplantemplateeintrag*) mapper->create();
        te->setTag(tag);
        te->setNrStunde(stunde);
        te->setKlasse(kl);
        te->setName(QString("%1 / %2").arg(tag).arg(stunde).toStdString());



        o=te;
        */
	} else if (className == "WeekMap"){
		QDate date = DateDialog::getDate();
		WeekMap *wm = SKalender::getInstance()->getWeek(date);
		
		/*
		date = wm->getStartDate();
		SStundenplan* ss = SStundenplan::getInstance();
		for(int i=0; i<6;i++){
			schultag *st = ss->getSchultag(  date.addDays(i) );
			wm->addItem( st );
		}
		*/
		
		o=wm;
		
	} else {
		AbstractMapper *mapper = MappingControler::getInstance()->getMapperByName(className);
		if(mapper){
			o=mapper->create();
		} else {
            qDebug() << QString("Could not get mapper for %1").arg(className.c_str());
			return 0;
		}

		if(className=="material"){
            QString filename = KFileDialog::getSaveFileName();
			QFile file(filename);
			if(! file.exists()){
                file.open(QIODevice::ReadWrite);
				file.close();
			}
			material *m = dynamic_cast<material*>(o);
			if(m){
                m->setFileName(file.fileName().toStdString());
			}
        } else if (className=="lektuere"){
            QString filename = KFileDialog::getOpenFileName();
            QFile file(filename);
            lektuere *l = dynamic_cast<lektuere*>(o);
            if(l){
                l->setFileName(file.fileName().toStdString());
            }
        }
		/* 
		else if (className == "teilleistung" || className == "teilleistungberechnet" || className == "klausur"){
			QString name = KInputDialog::getText("Teilleistung","Bezeichnung");
			o->setName(name);
		} 
		*/
		/*else if(className == "WeekMap"){
			WeekMap *wm = dynamic_cast<WeekMap*>(o);
			if(wm){
				QDate date = DateDialog::getDate();
				wm->setStartDate( date );
				qDebug("Set date to WeekMap");
	
				SStundenplan* ss = SStundenplan::getInstance();
				for(int i=0; i<6;i++){
					schultag *st = ss->getSchultag(  date.addDays(i) );
					wm->addItem( st );
				}

			
				/*
				stundenplan* activeplan = GuiRepository::getInstance()->getActiveStundenplan();
				stundenplaneintrag *se = (stundenplaneintrag*) create("stundenplaneintrag");
				wm->addItem(se,QPoint(20,10));
				
			}
			
		} */
	}
	return o;	
}
