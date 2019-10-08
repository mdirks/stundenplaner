//
// C++ Implementation: config
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "guiconfig.h"

#include "orm/persistence/database.h"
#include "services/sstundenplan.h"
#include "services/skalender.h"
#include "datamodel/tutoriummapper.h"

#include <QFileDialog>
#include <QSettings>



GuiConfig* GuiConfig::instance=0;

GuiConfig* GuiConfig::getInstance()
{
	if(! instance){
		instance = new GuiConfig();
	}
	return instance;
}

GuiConfig::GuiConfig() :
	termStart(2009,2,1),termEnd(2009,7,30)
{

    //KConfig *config = KGlobal::config();
    //config->setGroup("Gui");



    activesj=0;
	activetut=0;
}


GuiConfig::~GuiConfig()
{
}

QString GuiConfig::readEntry(QString group, QString name)
{	
    QString valueString=group + "/" + name;
    QSettings settings("MD","Stundenplaner");
    return settings.value(valueString).toString();

}
   
void GuiConfig::writeEntry(QString group, QString name, QString entry)
{
    /*
    KConfig *config = KGlobal::config();
	config->setGroup(group);
	config->writeEntry(name, entry);
    */
    QString valueString=group + "/" + name;
    QSettings settings("MD","Stundenplaner");
    settings.setValue(valueString, entry);

}


QPixmap GuiConfig::loadIcon(QString iconFileName)
{
    return QPixmap(iconFileName);
}




QPixmap GuiConfig::getIcon(QString name)
{
    QPixmap pm;
	map<QString,QString>::iterator it = mapIcons.find(name);
	if(it != mapIcons.end()){
		QString iconName = it->second;
        pm= QPixmap(iconName);
    } else {
        QString iconName = GuiConfig::getInstance()->readEntry("Icon",name + "_icon");
		mapIcons[name]=iconName;
        pm= QPixmap(iconName);
	}
    if(pm.isNull()){
        selectIcon(name);
        it = mapIcons.find(name);
        if(it != mapIcons.end()){
            QString iconName = it->second;
            pm= QPixmap(iconName);
        }
    }
    return pm;

}
/*!
    \fn GuiRepositoryImpl::getIconForObject(PObject *o)
 */
QPixmap GuiConfig::getIcon(PObject *o)
{
    if(o && o->getPersistenceObject()){
    QString className(o->getPersistenceObject()->getClassName().c_str());
	return getIcon(className);
    } else {
        qDebug("GuiConfig::getIcon: Warning: getPersistenceObject failed for object");
    	return getIcon("kfind");//loader->loadIcon("kfind",group);
    }
}

QPixmap GuiConfig::getIcon(RepositoryProperty *rp)
{
	if(rp->isCollection()){
		return getIcon("Collection");
	} else if (rp->isString()){
		return getIcon("String");
	} else if (rp->isText()){
		return getIcon("Text");
	} else {
		return getIcon("Unknown");
	}
}



void GuiConfig::selectIcon(PObject *o)
{
    QString className(o->getPersistenceObject()->getClassName().c_str());
	selectIcon(className);
}

void GuiConfig::selectIcon(QString name)
{
    QString iconName = QFileDialog::getOpenFileName(nullptr,QString("Choose Icon"),QString(),QString("Images (*.png *.xpm *.jpg)"));
	mapIcons[name] = iconName;
	
    writeEntry("Icon",name+"_icon", iconName);
}

QStringList GuiConfig::getRegisteredIconObjects()
{
    QStringList result;
    for(map<QString,QString>::iterator it=mapIcons.begin(); it!=mapIcons.end(); it++)
    {
        result.append(it->first);
    }
    return result;
}

void GuiConfig::selectIcon(RepositoryProperty *rp)
{
	QString type;
	if(rp->isCollection()){
		type = "Collection";
	} else if (rp->isString()){
		type = "String";
	} else if (rp->isText()){
		type = "Text";
	} else {
		type = "Unknown";
	}
	
	selectIcon(type);
}

/*
QWidget* GuiRepositoryImpl::getEditor(PObject *mo, RepositoryProperty *prop, QWidget *mainTab)
{
	QWidget *w = 0;
	if(prop->isString()){
		w= new StringEditor(mo,prop,mainTab);
	} else if(prop->isText()){
					

					w =  new TextPropertyEditor(mo,prop,mainTab);
					//w->setPaletteBackgroundColor(QColor(220,220,250));
			} else if(prop->isCollection()){
					if(prop->getName() == "Eintraege"){
						PObjectTable *table = new PObjectTable(prop,mo,mainTab);
						table->load();
						w=table;
					} else {
						PObjectIconView *iconView = new PObjectIconView(prop,mo,mainTab);
						iconView->load();
						//iconView -> load(prop->asCollection( mo ) );
						w = iconView;
					}
			} else if(prop->isDate()){
					w=new DateEditor(mo,prop,mainTab) ;
			} else if(prop->isPObject()){
					w= new PObjectLabel(prop,mo,mainTab);
			} else if(prop->isNumeric()){
					w= new StringEditor(mo,prop,mainTab);
			}	
			return w;
}
*/



/*!
    \fn GuiConfig::getCurrentTermEnd()
 */
QDate GuiConfig::getCurrentTermEnd()
{
    return termEnd;
}


/*!
    \fn GuiConfig::getCurrentTermStart()
 */
QDate GuiConfig::getCurrentTermStart()
{
    return termStart;
}


/*!
    \fn GuiConfig::setCurrentTermEnd(QDate date)
 */
void GuiConfig::setCurrentTermEnd(QDate date)
{
    this->termEnd=date;
}


/*!
    \fn GuiConfig::setCurrentTermStart(QDate date)
 */
void GuiConfig::setCurrentTermStart(QDate date)
{
    this->termStart=date;
}


/*!
    \fn GuiConfig::getDatabaseName()
 */
QString GuiConfig::getDatabaseName()
{
    return readEntry("persistence", "databasename");
}


/*!
    \fn GuiConfig::setDatabaseName(QString dbName)
 */
void GuiConfig::setDatabaseName(QString dbName)
{
    writeEntry("persistence","databasename",dbName);
}


/*!
    \fn GuiConfig::setDisplayProperties(QString guiObjectIdentifier, QStringList properties)
 */
void GuiConfig::setDisplayProperties(QString guiObjectIdentifier, QStringList properties)
{
    writeEntry("displayproperties",guiObjectIdentifier, properties.join(","));
}


/*!
    \fn GuiConfig::getDisplayProperties(QString guiObjectIdentifier)
 */
QStringList GuiConfig::getDisplayProperties(QString guiObjectIdentifier)
{
    QString propertiesString = readEntry("displayproperties",guiObjectIdentifier);
    if(propertiesString==""){
        return QStringList();
    } else {
        return propertiesString.split(",");
    }
}


/*!
    \fn GuiConfig::getActiveSchuljahr()
 */
schuljahr* GuiConfig::getActiveSchuljahr()
{
    if(activesj==0){
	QString id_str = readEntry("GUI","AktiverStundenplan");
	int id = id_str.toInt();
	activesj = dynamic_cast<schuljahr*>(Database::getInstance()->loadObjectById(id));
	if(activesj){
        SKalender::getInstance()->setActiveSchuljahr(activesj);
		SStundenplan::setActiveStundenplan(activesj->getStundenplana());
    } else { qDebug() << "WARNING !!: uiConfig::getActiveSchuljahr : FAILED TO LOAD";}
	
    }
    return activesj;
}

tutorium* GuiConfig::getActiveTutorium()
{
	if(activetut == 0){
		QString id_str = readEntry("GUI","AktivesTutorium");
		int id = id_str.toInt();
		activetut = dynamic_cast<tutorium*>(Database::getInstance()->loadObjectById(id));
		if(!activetut){
             qDebug() << "WARNING !!: uiConfig::getActiveTutorium : FAILED TO LOAD";
			 list<tutorium*> *list_all = (list<tutorium*> *) tutoriummapper::getInstance()->find_gen();
			 if(list_all->size()>0){
				activetut = *list_all->begin();
				setActiveTutorium(activetut);
			}
			if(!activetut){
                 qDebug() << "WARNING !!: uiConfig::getActiveTutorium : FAILED TO FIND A TUTORIUM";
			}
		}
	} 
	return activetut;
}


/*!
    \fn GuiConfig::setActiveSchuljahr(schuljahr *sj)
 */
void GuiConfig::setActiveSchuljahr(schuljahr *sj)
{
    activesj = sj;
    writeEntry("GUI","AktiverStundenplan",QString("%1").arg(sj->getID()));
}

void GuiConfig::setActiveTutorium(tutorium *tu)
{
    activetut = tu;
    writeEntry("GUI","AktivesTutorium",QString("%1").arg(tu->getID()));
}
