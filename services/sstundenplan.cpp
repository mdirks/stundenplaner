//
// C++ Implementation: sstundenplan
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "sstundenplan.h"
#include "sstundenplanmapper.h"
#include "actions/createaction.h"
#include "datamodel/stundenplaneintrag.h"
#include "datamodel/kursbuch.h"
#include "orm/mapping/mappingcontroler.h"
#include "orm/transactions/transactions.h"
#include "skalender.h"

#include "qstring.h"

SStundenplan* SStundenplan::instance = 0;
stundenplan* SStundenplan::active_sp=0;

SStundenplan::SStundenplan()
{
	setMapper(SStundenplanmapper::getInstance());
	list_te = 0;
	//map_eintraege = new map<QDate , list<stundenplaneintrag*>*>();
}


SStundenplan::~SStundenplan()
{
}

 void SStundenplan::setActiveStundenplan(stundenplan *sp)
 {
 	active_sp=sp;
 	getInstance()->init();
 }

stundenplan* SStundenplan::getActiveStundenplan()
{
    return active_sp;
}

SStundenplan* SStundenplan::getInstance()
{
	if(! instance){
			
			instance=new SStundenplan();
			instance->init();
	}
	return instance;
}



void SStundenplan::init()
{		
		for(int i=0; i<8; i++){
			map_templates[i] = new set<stundenplantemplateeintrag*>();
		}

		list<stundenplantemplateeintrag*> *list_ae = getTemplateEintraege();
		for(list<stundenplantemplateeintrag*>::iterator it = list_ae->begin(); it != list_ae->end(); it++){		
			initForTemplate(*it);
		}

		if(active_sp){
            qDebug() << QString("SStundenplan::init : DONE !!!!");
		} else {
            qDebug() << QString("SStundenplan::init : DONE but Stundenplan NOT SET");
		}
}

void SStundenplan::initForTemplate(stundenplantemplateeintrag *teintrag)
{

			// fill template map by dow
			int dow=teintrag->getTag();
			set<stundenplantemplateeintrag*> *result = map_templates[dow];
			if(! result){
				qDebug("SStundenplan: missing list !!?");
					//result = new list<stundenplaneintrag*>();
					//map_eintraege[dow] = result;
			}
			result->insert(teintrag);

			// fill template map by klasse
			klasse *kl = teintrag->getKlasse();
			result = mapTemplatesKlassen[kl];
			if(! result){
				result = new set<stundenplantemplateeintrag*>();
				mapTemplatesKlassen[kl] = result;
			}
			result->insert(teintrag);

			//fill eintrag map by klasse

			//fill eintrag map by date
            /*
			list<stundenplaneintrag*>* list_eintraege = teintrag->getEintraege();
			for(list<stundenplaneintrag*>::iterator it = list_eintraege->begin(); it != list_eintraege->end(); it++){
				stundenplaneintrag* eintrag = *it; 
				initForEintrag(eintrag);
				
			}
            */
}

void SStundenplan::initForEintrag(stundenplaneintrag *eintrag)
{
				//QDate dt = eintrag->getDatum();
				/*
				list<stundenplaneintrag*> *result = mapEintraege[dt];
				if( ! result){
					result = new list<stundenplaneintrag*>();
					mapEintraege[dt]=result;
				}
				result->push_back(eintrag);
				*/

				/*
				klasse *kl = eintrag->getKlasse();
				map<QDate, list<stundenplaneintrag*> *> map_result = mapEintraegeKlassen[kl];
				
				list<stundenplaneintrag*> *result =  map_result[dt];
				if( ! result){
					result = new list<stundenplaneintrag*>();
					map_result[dt]=result;
				}
				result->push_back(eintrag);
				*/
}

void SStundenplan::close()
{
	instance=0;
}


void SStundenplan::getStunden(QDate date, list<stundenplaneintrag*> *result)
{
    result = getEintraege(date);
    /*
    set<stundenplantemplateeintrag*> *templates = map_templates[date.dayOfWeek()];
	if(templates){
		for(set<stundenplantemplateeintrag*>::iterator it = templates->begin(); it != templates->end(); it++){
			stundenplantemplateeintrag* te = *it;
			result->push_back( createEintrag(te, date));
		}
    } else { qDebug() << QString("SStundenplan: could not get entry for dow %1").arg(date.dayOfWeek());}
    */
}




stundenplaneintrag* SStundenplan::createEintrag(stundenplantemplateeintrag *te, QDate date)
{
	
	stundenplaneintrag *eintrag=0;
	list<stundenplaneintrag*> *list_ein=0;
	//Transactions::getCurrentTransaction()->add( eintrag );
	if(te->getTag() == date.dayOfWeek()){
		eintrag = te->getEintrag(date);
		if(!eintrag){
			qDebug("Could not find Eintrag !?");
			if(SKalender::getInstance()->isSchultag(date)){
				//qDebug(QString("SStundenplan: Did not find stundenplaneintrag %1, %2: creating new one").arg(date.toString()).arg(te->getKlasse()->getName()));
				AbstractMapper *mapper = MappingControler::getInstance()->getMapperByName("stundenplaneintrag");
				eintrag = (stundenplaneintrag*) mapper->create();
				
				te->addToEintraege(eintrag);
				eintrag->setDatum(date);
				/* done by the above
				eintrag->setTemplate(te);
				eintrag->setKlasse(te->getKlasse());
				eintrag->setDatum(  QDateTime( date, QTime(7,50).addSecs((te->getNrStunde())*60*45) ) );
				eintrag->setName( te->getName() );
				*/
				Transactions::getCurrentTransaction()->add(eintrag);
				Transactions::getCurrentTransaction()->add(te);
				initForEintrag(eintrag);
				//list_ein->push_back(eintrag);
			} else {
                qDebug() << QString("SStundenplan::createEintrag : did not create since Ferientag %1").arg(date.toString());
			}
		} else {
            qDebug() << QString("SStundenplan: FOUND stundenplaneintrag %1,%2").arg(date.toString()).arg(eintrag->getID());
		}

		if( (! SKalender::getInstance()->isSchultag(date)) && eintrag){
			if(!SKalender::getInstance()->isSchuljahr(date)){
				te->deleteFromEintraege(eintrag);
				qDebug("SStundenplan::createEintrag : removed Eintrag with wrong schuljahr");
			} else if(SKalender::getInstance()->isFerientag(date)){
				if(klasse *kl=eintrag->getKlasse()){
					if(krusbucheintrag *ke = kl->getKursbuch()->getEintrag(date)){
                        ke->setEintrag(SKalender::getInstance()->getDescription(date).toStdString());
					}
				}
                qDebug() << "SStundenplan::createEintrag : handled Ferieneintrag";
			}
		}
	} else {
		QString("SStundenplan::createEintrag : strange : tag im template passt nicht zum Wochentag : %1 / %2").arg(te->getTag()).arg( date.dayOfWeek() );
	}
	//initForTemplate(te);

	return eintrag;
}


list<stundenplaneintrag*>* SStundenplan::getEintraege(QDate date)
{
    list<stundenplaneintrag*> *result = map_eintraege[date];
    if(!result){
        result =new list<stundenplaneintrag*>();
        map_eintraege[date]=result;

        set<stundenplantemplateeintrag*> *templates = map_templates[date.dayOfWeek()];
        if(templates){
            int count=0;
            for(set<stundenplantemplateeintrag*>::iterator it = templates->begin(); it != templates->end(); it++){
                ++count;
                stundenplantemplateeintrag* te = *it;
                qDebug() << QString("Asking to create Eintrag nr. %1 to schultag").arg(count);
                stundenplaneintrag *eintr = createEintrag(te, date);
                if(eintr){
                    if(SKalender::getInstance()->isSchultag(date)){
                        result->push_back( eintr );
                    } else {
                        qDebug("SStundenplan::getEintraege : SKIPPING Eintrag (Ferien)");
                    }
                } else {
                    qDebug("Failed to create eintrag");
                }

            }
        } else {
            qDebug() << QString("SStundenplan: could not get entry for dow %1").arg(date.dayOfWeek());
        }
    }
	
	return result;
}

list<stundenplaneintrag*>* SStundenplan::getEintraegeForWeek(QDate date)
{
	QDate day = date.addDays(1); //date.addDays((-1)*date.dayOfWeek()+3);
	while(day.dayOfWeek() > 1) day=day.addDays(-1);
	list<stundenplaneintrag*> *result = new list<stundenplaneintrag*>();
	while(day.dayOfWeek()<6){
		list<stundenplaneintrag*> *append= getEintraege(day);
        qDebug() << QString("SStundenplan::getEintraegeForWeek : found %1 eintraege").arg(append->size());
		result->splice(result->end(), *append);
		day=day.addDays(1);
	}
	return result;
	
}

stundenplaneintrag* SStundenplan::getPrevious(stundenplaneintrag *se)
{
	QDate date = se->getDatum();
	klasse *kl = se->getKlasse();

	stundenplaneintrag *result=0;
	int count = 0;
	while(result == 0 && count < 8){
		date = date.addDays(-1);
		list<stundenplaneintrag*> *le = getEintraege(date);
		list<stundenplaneintrag*>::iterator it = le->begin(); 
		while(result == 0 && it != le->end()){
			stundenplaneintrag *e = (*it);
			if(e->getKlasse() == kl){
				result = e;
			}	 
			it++;
		}
		count++;
	}
	return result;
	
}

/*
schultag*  SStundenplan::getSchultag(QDate date)
{
     AbstractMapper *mapper = MappingControler::getInstance()->getMapperByName("schultag");
     schultag *result = (schultag*) mapper->create();
    
	
	if(result){
		set<stundenplantemplateeintrag*> *templates = map_templates[date.dayOfWeek()];
		if(templates){
			int count=0;
			for(set<stundenplantemplateeintrag*>::iterator it = templates->begin(); it != templates->end(); it++){
				++count;
				stundenplantemplateeintrag* te = *it;
				qDebug(QString("Asking to create Eintrag nr. %1 to schultag").arg(count));
				stundenplaneintrag *eintr = createEintrag(te, date);
				if(eintr){
					if(SKalender::getInstance()->isSchultag(date)){
						qDebug(QString("Adding Eintrag nr. %1 to schultag").arg(count));
						result->addToEintraege( eintr );
						qDebug(QString("Added Eintrag nr. %1 to schultag").arg(count));
					} 
				} else {
					qDebug("Failed to create eintrag");
				}
				
			}
		} else { qDebug(QString("SStundenplan: could not get entry for dow %1").arg(date.dayOfWeek()));}
		result->setDatum( QDateTime(date,QTime(7,50)) );
	} else {
		qDebug("SStundenplan::getSchultag : failed to create Schultag");
	}
	return result;
}
*/

list<stundenplaneintrag*>* SStundenplan::getEintraegeForWeek(klasse *kl, QDate date)
{
	list<stundenplaneintrag*>* result = new list<stundenplaneintrag*>();
	if(kl){
		 //return mapEintraegeKlassen[kl][date];
			
			set<stundenplantemplateeintrag*> *list_templates = mapTemplatesKlassen[kl];
			if(list_templates){
				
				
				for(set<stundenplantemplateeintrag*>::iterator it = list_templates->begin(); it != list_templates->end(); it++)
				{
					stundenplantemplateeintrag *te = (*it);
					for(int i=0; i<7; i++){
						stundenplaneintrag *e = 	createEintrag(te,date.addDays(i));
						if(e){
                            qDebug() << QString("SStundenplan: GOT stundenplaneintrag %1, %2").arg((e->getDatum()).toString()).arg(te->getKlasse()->getName().c_str());
							result ->push_back(e);
							/*
							if(e->getKlasse() == kl){
								result->push_back(e);
								qDebug("ADDING");
							}
							*/
						}
					}
				}
			}
	} else {
		qDebug("SStundenplan::getEintraegeForWeek : Klasse invalid, could not get Eintraeg");
	}	
	return result;
	
}
/*!
    \fn SStundenplan::createTemplateEintrag(int tag, int stunde)
 */
stundenplantemplateeintrag* SStundenplan::createTemplateEintrag(int tag, int stunde, klasse *kl)
{
    stundenplantemplateeintrag *te = 0;
	
	set<stundenplantemplateeintrag*> *templates = map_templates[tag];
	if(templates){
		for(set<stundenplantemplateeintrag*>::iterator it = templates->begin(); it != templates->end(); it++){
			if((*it)->getNrStunde() == stunde){
				te = (*it);
			}
			
		}
	

		if(!te){
			AbstractMapper *mapper = MappingControler::getInstance()->getMapperByName("stundenplantemplateeintrag");
			
			te = (stundenplantemplateeintrag*) mapper->create();
			te->setTag(tag);
			te->setNrStunde(stunde);
			te->setKlasse(kl);
            te->setName(QString("%1 / %2").arg(tag).arg(stunde).toStdString());
			templates->insert(te);
		}

        if(active_sp){
            Transactions::getCurrentTransaction()->add(active_sp);
            active_sp->addToTemplateEintraege(te);
        }
	
	} else {
		qDebug("SStundenplaner: template map not properly initialized");
	}
	
	return te;
}


/*!
    \fn SStundenplan::getTemplateEintraege()
 */
list<stundenplantemplateeintrag*>* SStundenplan::getTemplateEintraege()
{
	
//     if(!list_te){
// 	list_te = SStundenplanmapper::getInstance()->findTemplateEintraege(getID());
//     }
//     return list_te;
	if(active_sp){
		return active_sp->getTemplateEintraege();
	} else {
		return new list<stundenplantemplateeintrag*>();
		qDebug("!! WARNING !! SStundenplan : no stundenplan set : returning empty list");
	}
}


/*!
    \fn SStundenplan::addToTemplateEintraege(stundenplantemplateeintrag* ste)
 */
void SStundenplan::addToTemplateEintraege(stundenplantemplateeintrag* ste)
{
        active_sp->getTemplateEintraege()->push_back(ste);
	initForTemplate(ste);
	
}


/*!
    \fn SStundenplan::deleteFromTemplateEintraege(stundenplantemplateeintrag* ste)
 */
void SStundenplan::deleteFromTemplateEintraege(stundenplantemplateeintrag* ste)
{
    active_sp->getTemplateEintraege()->remove(ste);
    
}


/*!
    \fn SStundenplan::getEintraege(stundenplantemplateeintrag *te)
 */
list<stundenplaneintrag*>* SStundenplan::getEintraege(stundenplantemplateeintrag *te)
{
    return te->getEintraege();
}
