//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "repositoryentryimpl.h"
#include "services/utils/utils.h"
#include "indirectrepositoryproperty.h"

#include <QString>
#include <QDebug>

RepositoryEntryImpl::RepositoryEntryImpl(const string &className)
{
	this->className = className;
	hasBase = false;
	allProperties_withBase = 0;
	allProperties = new list<RepositoryProperty*>();
	mprop = 0;
}


RepositoryEntryImpl::~RepositoryEntryImpl()
{
}




/*!
    \fn RepositoryEntryImpl::addProperty(RepositoryProperty *p)
 */
void RepositoryEntryImpl::addProperty(RepositoryProperty *p)
{
    nameToFunc[p->getName()] = p;
    allProperties->push_back(p);
    if(p->isText()){
	mprop = p;
   }
}


RepositoryProperty* RepositoryEntryImpl::getProperty(string name){
	RepositoryProperty *rp=0;
	if(name.find("/") != string::npos){
        qDebug() << "Looking for indirect property";
        QStringList nameList = QString(name.c_str()).split("/");
		QString baseName = nameList.front();
		
        qDebug() << QString("baseName=%1").arg(baseName);
        RepositoryProperty *rp_base= getProperty(baseName.toStdString());
		if(rp_base){
            qDebug() << "Got base property";
			list<RepositoryProperty*> *list_properties = new list<RepositoryProperty*>();
			list_properties->push_back(rp_base);
            string baseType = rp_base->getType();
			RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry(baseType);
			if(re){
                qDebug() << QString("Got re for %1").arg(baseType.c_str());
				nameList.pop_front();
				for(QStringList::iterator it = nameList.begin(); it != nameList.end(); it++){
                    string propName = (*it).toStdString();
					RepositoryProperty *rp = re->getProperty(propName);
					if(rp){
						list_properties->push_back(rp);
						re = Repository::getInstance()->getRepositoryEntry(rp->getType());
					} else {
                        qDebug() << QString("Could not get property %1 on %2").arg(propName.c_str()).arg(baseType.c_str());
						return 0;
					}
				}
			} else {
                qDebug() << QString("Could not get RepositoryEntry for %1").arg(baseType.c_str());
				return 0;
			}
            qDebug() << "Creating indirect property";
			rp = new IndirectRepositoryProperty(list_properties,name);
		} else {
            qDebug() << QString("Could not get Property for %1").arg(name.c_str());
			return 0;
		}
			
	} else {
        propertymap::iterator it = nameToFunc.find(name);
		if(it != nameToFunc.end()){
			rp = it->second;
		}  else {
            qDebug() << QString("RepositoryEntryImpl: Could not find ").append(to_qstring(name))
                     << " in " <<  getClassName().c_str();
			return 0;
		}
	}
	return rp;
}



/*!
    \fn RepositoryEntryImpl::getClassName()
 */
string RepositoryEntryImpl::getClassName()
{
    return this->className;
}


/*!
    \fn RepositoryEntryImpl::getAllProperties()
 */
list<RepositoryProperty*> * RepositoryEntryImpl::getAllProperties(bool includeBaseProperties)
{
    if(includeBaseProperties && hasBase){
	return allProperties_withBase;
    } else {
	return allProperties;
   }
}

string RepositoryEntryImpl::getBaseClassName()
{
	return this->baseClassName;
}



/*!
    \fn RepositoryEntryImpl::registerBase(string baseClassName)
 */
void RepositoryEntryImpl::registerBase(string baseClassName)
{
    hasBase = true;
    this->baseClassName = baseClassName;
    if(! allProperties_withBase){
	allProperties_withBase = new list<RepositoryProperty*>();
	for(list<RepositoryProperty*>::iterator it = allProperties->begin(); it != allProperties->end(); it++){
		allProperties_withBase->push_back( (*it) );
	}
    }
    RepositoryEntry *entry = Repository::getInstance()->getRepositoryEntry( baseClassName );
    if(entry){
	list<RepositoryProperty*>  *baseProperties = entry->getAllProperties();
	if(baseProperties){
		for(list<RepositoryProperty*>::iterator it = baseProperties->begin(); it != baseProperties->end(); it++){
			allProperties_withBase->push_back( (*it) );
            nameToFunc[(*it)->getName()] = (*it); //add baseclass properies to map for retrieval
		}
	} else {
        qDebug() << QString("Warning: BaseClass %1 has no property list").arg(baseClassName.c_str());
	}
    } else {
        qDebug() << QString("Trouble: Could not get entry for base class ").append(baseClassName.c_str());
    }
}


/*!
    \fn RepositoryEntryImpl::getMainProperty()
 */
RepositoryProperty* RepositoryEntryImpl::getMainProperty()
{
     return mprop;
}
