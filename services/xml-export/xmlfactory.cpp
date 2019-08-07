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
#include "xmlfactory.h"

#include "qfile.h"
#include "qmessagebox.h"
#include <QDebug>

#include "orm/mapping/abstractmapper.h"
#include "orm/mapping/mappingcontroler.h"
#include "orm/persistence/pobject.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/repositoryproperty.h"
#include "services/sstundenplan.h"

XmlFactory* XmlFactory::instance=0;

XmlFactory::XmlFactory()
{
}


XmlFactory::~XmlFactory()
{
}

XmlFactory* XmlFactory::getInstance()
{
	if(!instance){
		instance=new XmlFactory();
	}
	return instance;
}


void XmlFactory::processFile(const QString fileName, list<PObject*>* results)
{
    
    QFile file( fileName );
    if ( !file.open(QIODevice::ReadOnly ) ) {
        QMessageBox::critical( 0, "Critical Error",
                QString( "Cannot open file %1" ).arg( fileName ) );
        return;
    }
    if ( !domDoc.setContent( &file ) ) {
        QMessageBox::critical( 0,  "Critiical Error" ,
                QString( "Parsing error for file %1" ).arg( fileName ) );
       file.close();
        return;
    }
    file.close();

    importMap.clear();
    QDomNodeList mainList = domDoc.documentElement().childNodes();
    for(int i=0; i<mainList.count(); i++){
    	QDomElement objectElement = mainList.item(i).toElement();
    qDebug() << QString("Found class ").append(objectElement.attribute("name"));
	results->push_back(readObjectElement(objectElement));
    }

}


PObject*  XmlFactory::readObjectElement(QDomElement objectElement)
{
	QString className = objectElement.tagName();
	QString id_s = objectElement.attribute("ID");
 
	PObject *o=0;
	map<QString,PObject*>::iterator it = importMap.find(id_s);
	if(it != importMap.end()){ // get it if already created
		o = it->second;
	} else {
		if(className == "SStundenplan"){
			o = SStundenplan::getInstance();
		} else {
            AbstractMapper *mapper = MappingControler::getInstance()->getMapperByName(className.toStdString());
			if(mapper){
				o = mapper->create();
				
				
			} else {
                qDebug() << QString("Could not get mapper for %1").arg(className);
				return 0;
			}
		}	
		importMap[id_s] = o;
	
        RepositoryEntry *re = Repository::getInstance()-> getRepositoryEntry(className.toStdString());
		if(re){
			QDomNamedNodeMap attrMap = objectElement.attributes();
			for(int i=0; i<attrMap.length(); i++){
				QDomNode an = attrMap.item(i);
				if (an.isAttr()){
					QDomAttr attr = an.toAttr();
                    RepositoryProperty *rp = re->getProperty(attr.name().toStdString());
					if(rp){
                        rp->fromString(attr.value().toStdString(),o);
                        qDebug() << QString("Set attribute %1 from string %2").arg(attr.name()).arg(attr.value());
					} else {
                        qDebug() << QString("XmlFactory::readObjectElement : Could not get property %1").arg(attr.name());
					}
				}
			}
			
			QDomNode n = objectElement.firstChild();
			while ( !n.isNull() ) {
				if ( n.isElement() ) {
					QDomElement e = n.toElement();
					if(e.tagName() == "property"){
						QString propertyName = e.attributeNode("Name").value();
                        RepositoryProperty *rp = re->getProperty(propertyName.toStdString());
						if(rp){
							if(rp->isPObject()){
								QDomNode nn = n.firstChild();
								if(nn.isElement() ){
									PObject *oo = readObjectElement(nn.toElement());
									if(o){
										rp->set(oo,o);
                                        qDebug() << QString("Set property %1 from object %2 on %3").arg(propertyName).arg(oo->getID()).arg(o->getID());
									} else {
                                        qDebug() << QString("XmlFactory::readObjectElement: WARNING could not get object for %1").arg(propertyName);
									}
								}
							} else if(rp->isCollection()){
								QDomNode nn = e.firstChild();
								while( !nn.isNull() ){
									if( nn.isElement() ){
										QDomElement ee = nn.toElement();
										PObject *oo = readObjectElement(ee);
										if(oo){
										rp->add(oo,o);
										} else {
                                        qDebug() << QString("XmlFactory::readObjectElement: WARNING could not create object in collection for %1").arg(propertyName);
										}
									}
									nn = nn.nextSibling();
	
								}
							} else {
                                rp->fromString(e.text().toStdString(),o);
							}
				
						} else {
                            qDebug() << QString("WARNING: XmlExport:Could not get RP %1").arg(propertyName);
						}
					} 
				} else if (n.isAttr()){
					QDomAttr attr = n.toAttr();
                    RepositoryProperty *rp = re->getProperty(attr.name().toStdString());
					if(rp){
                        rp->fromString(attr.value().toStdString(),o);
                        qDebug() << QString("Set attribute %1 from string %2").arg(attr.name()).arg(attr.value());
					} else {
                        qDebug() << QString("XmlFactory::readObjectElement : Could not get property %1").arg(attr.name());
					}
	
				} else {
                    qDebug() << QString("XmlFactory::readObjectElement : Skipping node %1").arg(n.nodeName());
				}
				n = n.nextSibling();
			}
		} else {
            qDebug() << QString("XmlFactory::readObjectElement: Could not get Repository Entry for %1").arg(className);
		}
	}
	return o;
}


/*!
    \fn XmlFactory::exportObjectList(list<PObject*> *objectList, QString filename)
 */
void XmlFactory::exportObjectList(QString fileName, list<PObject*> *objectList)
{
    QFile file( fileName );
    if ( !file.open(QIODevice::ReadWrite ) ) {
        QMessageBox::critical( 0, "Critical Error",
                QString( "Cannot open file %1" ).arg( fileName ) );
        return;
    }

    domDoc = QDomDocument( "import" );
    QDomElement root = domDoc.createElement( "import" );
    domDoc.appendChild( root );

    exportMap.clear();
    exportObjectList(root,objectList);

    QTextStream stream(&file);
    stream << domDoc.toString() << "\n";
    file.close();
    	
}

void XmlFactory::exportObjectList(QDomElement &parent, list<PObject*> *objectList )
{

    for(list<PObject*>::iterator it=objectList->begin(); it != objectList->end(); it++)
    {
    	exportObject(parent,(*it)); 
	
    }

}



void XmlFactory::exportObject(QDomElement &parent, PObject* ob)
{
	QDomElement tag = getTagForObject(ob);
    	parent.appendChild( tag );
}

QDomElement XmlFactory::getTagForObject(PObject *o)
{
	if(!o){
		qDebug("XmlFactory::getTagForObject: FATAL: Could not get Persistence Object ");
		return domDoc.createElement("Null Object");
	}


	PersistenceClass *pc = o->getPersistenceObject();
	if(!pc){
		qDebug("XmlFactory::getTagForObject: FATAL: Could not get Persistence Object ");
		return domDoc.createElement("Invalid Object");
	}
    QString className = pc->getClassName().c_str();
    qDebug() << QString("Exporting %1, %2").arg(className).arg(o->getID());
	QDomElement e = domDoc.createElement(className);
    e.setAttribute("Name",o->getName().c_str());
    e.setAttribute("ID", o->getID());

	map<int,int>::iterator it = exportMap.find(o->getID());
	if(it != exportMap.end()){
		qDebug("Skipping properties");
	} else { //recursive if not already treated
		qDebug("Handling properties");
		exportMap[o->getID()] = o->getID();
        RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry(className.toStdString());
		if(re){
		list<RepositoryProperty*> *list_prop = re->getAllProperties(true);
		for(list<RepositoryProperty*>::iterator it = list_prop->begin(); it != list_prop->end();it++){
			RepositoryProperty *rp = *it;
			if(rp->isPObject()){
				PObject *oo = rp->asPObject(o);
				if(oo){
					QDomElement le = domDoc.createElement("property");
                    le.setAttribute("Name",rp->getName().c_str());
					le.setAttribute("Type","PObject");
					e.appendChild(le);
					exportObject(le,oo);
				} else {
                    qDebug() << QString("WARNING: XmlExport: could not get child-object %1").arg(rp->getName().c_str());
				}
			} else if(rp-> isCollection()){
				QDomElement le = domDoc.createElement("property");
                le.setAttribute("Name",rp->getName().c_str());
				le.setAttribute("Type","Collection");
				e.appendChild(le);
				list<PObject*> *ol = rp->asCollection(o);
				if(ol){
					exportObjectList(le,ol);
				} else {
                    qDebug() << QString("WARNING: XmlExport: could not get child-list %1").arg(rp->getName().c_str());
				}
			} else if(rp-> isText()){
			QDomElement ee= domDoc.createElement("property");
            ee.setAttribute("Name",rp->getName().c_str());
            QDomText te=domDoc.createTextNode(rp->asString(o).c_str());
			ee.appendChild(te);
			e.appendChild(ee);
			} else {
			/*
			QDomElement ee= domDoc.createElement("property");
			ee.setAttribute("Name",rp->getName());
			QDomText te=domDoc.createTextNode(rp->asString(o));
			ee.appendChild(te);
			e.appendChild(ee);
			*/
            e.setAttribute(rp->getName().c_str(),rp->asString(o).c_str());
			}
		}
	     
		} else {
            qDebug() << QString("XmlFactory::getTagForObject(): Could not get RepositoryEntry for %1").arg(className);
		}
	}

	
	return e;
}
