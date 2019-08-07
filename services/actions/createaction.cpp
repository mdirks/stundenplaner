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
#include "createaction.h"
//#include "gui/forms/mapperview.h"
#include "gui/guirepository.h"
#include "datamodel/datamodelrepository.h"
#include "datamodel/material.h"
#include "datamodel/stundenplan.h"
#include "gui/data/weekmap.h"
#include "gui/forms/pobjectdialog.h"
#include "services/utils/datedialog.h"
#include "orm/mapping/mappingcontroler.h"
#include "datamodel/stundenplaneintrag.h"
#include "services/sstundenplan.h"
#include "services/skalender.h"


#include <qfile.h>
#include <QDebug>

#include <QDialog>
#include <qinputdialog.h>
#include <qfiledialog.h>

CreateAction* CreateAction::instance=0;

CreateAction::CreateAction()
{
}


CreateAction::~CreateAction()
{
}




/*!
    \fn CreateAction::getInstance()
 */
CreateAction* CreateAction::getInstance()
{
    	if(! instance){
		instance = new CreateAction();

   	}
	return instance;
}


/*!
    \fn CreateAction::create()
 */
/*
PObject*  CreateAction::createObject()
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

AbstractMapper* CreateAction::chooseMapper()
{
	return MapperDialog::chooseMapper();
}
*/


/*!
    \fn CreateAction::create(string className)
 */
PObject* CreateAction::create(string className)
{
	PObject *o;

	if(className == "stundenplantemplateeintrag"){
		SStundenplan *ss = SStundenplan::getInstance();
		
        int tag = QInputDialog::getInt(0,"Tag","Tag der Stunde",1,1,7,1);
        int stunde = QInputDialog::getInt(0,"StundenNr.", "Nr. der Stunde",1,1,10,1);
		
		PObject *oo = PObjectDialog::choosePObject(MappingControler::getInstance()->getMapperByName( "klasse" ) );
		o = ss->createTemplateEintrag(tag,stunde,dynamic_cast<klasse*>(oo));
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
			o = mapper->create();
		} else {
            qDebug() << QString("Could not get mapper for %1").arg(className.c_str());
			return 0;
		}

		if(className=="material"){
            QString filename = QFileDialog::getOpenFileName();
			QFile file(filename);
			if(! file.exists()){
                file.open(QIODevice::ReadWrite);
				file.close();
			}
			material *m = dynamic_cast<material*>(o);
			if(m){
                m->setFileName(file.fileName().toStdString());
			}
		} /*else if(className == "WeekMap"){
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
