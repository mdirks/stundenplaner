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
#include "abstractmapper.h"

#include <QString>
#include <QSqlQuery>
#include <QDebug>

//#include "../datamodel/opo.h"
#include "../persistence/database.h"
#include "../transactions/transactions.h"
#include "objectfactory.h"

#include <map>

using namespace std;

AbstractMapper::AbstractMapper() : PersistenceClass()
{
	list_all = 0;
}


AbstractMapper::~AbstractMapper()
{
}

void AbstractMapper::reset()
{
	list_all =0;
}


/*!
    \fn AbstractMapper::findReference(string ref_name, int pri_id)
 */
PObject* AbstractMapper::findReference(string ref_name, int pri_id)
{
    PObject *ob = 0;
    
    Reference *ref = mapReferences[ref_name];
    if(ref){
    	ob = ref->findReferee(pri_id);
        if(!ob){
            qWarning() << QString("AbstractMapper::findReference FAILED for \
                                  %1,%2,%3").arg(getClassName().c_str()).arg(pri_id).arg(ref_name.c_str());
        }
    } else {
       qWarning() << QString("AbstractMapper::findReference : Could not find reference : ").append(ref_name.c_str());
    }
    
    return ob;
}

void AbstractMapper::deleteReference(string ref_name, int pri_id)
{
    Reference *ref = mapReferences[ref_name];
    if(ref){
    	ref->deleteReferee(pri_id);
    } else {
       qWarning() << QString("AbstractMapper::findReference : Could not delete reference : ").append(ref_name.c_str());
    }
 
}



bool AbstractMapper::checkAndAdjustTable(){
	Database::getInstance();

	map<string,string> column_map;
	string *cols = getColumns();
	string *coltypes = getColumnTypes();

	int colcount = getColumnCount();
	for(int i=0;i<colcount;i++){
			string c = cols[i];
			string t = coltypes[i];
			column_map[c] = t;
	}

    QString qs1 = QString("describe %1").arg(getTableName().c_str());
	QSqlQuery q(qs1);
	if(q.isActive()){
		while(q.next()){
			if(q.isValid()){
				if(q.value(1).isValid()){
                    string cn = q.value(0).toString().toStdString();
                    //qDebug() << QString("Erasing column %1").arg(cn.c_str());
                    map<string,string>::iterator it = column_map.find(cn);
					if(it != column_map.end()){
						column_map.erase(it);
                        //qDebug() << "Erase done";
					} else {
                        //qDebug() << QString("Strange column %1 not in list").arg(cn.c_str());
					}
				}
			}
		}
		if(!column_map.empty()){
            qDebug() << QString("Found %1 non-exiting columns: creating").arg(column_map.size());

			for(map<string, string>::iterator it = column_map.begin(); it != column_map.end(); it++){
                QString qs2 = QString("alter table %1 add %2 %3").arg(getTableName().c_str()).arg((it->first).c_str()).arg((it->second).c_str());
                qDebug() << QString("Adding column %1").arg(qs2);
				QSqlQuery q2(qs2);
				if(! q.isActive()){
                    qWarning() << QString("Query failed: %1").arg(qs2);
                    return false;
				}
			}
		}
	} else {
        qDebug() << QString("WARNING: CHECK FAILED FOR TABLE: %2 \n (%1)\n NOT IDEE WHAT IS SAVE TO DO???").arg(qs1).arg(getTableName().c_str());
        return false;
        /*
        dropMainTable();
		createMainTable();
        */
	}

}

void AbstractMapper::dropMainTable(){
    Database::getInstance();

    //string tname = persOb->getTableName();
    QString qs = QString("drop table %1").arg(getTableName().c_str());
    QSqlQuery q(qs);
    if(!q.isActive()) qDebug("Could not drop table");
}


void AbstractMapper::createMainTable(){
	Database::getInstance();

	//string tname = persOb->getTableName();	

    /*
    QString qs = QString("drop table %1").arg(getTableName().c_str());
	QSqlQuery q(qs);
	if(!q.isActive()) qDebug("Could not drop table");
    */
	
    QString qs2 = QString("create table %1 ( id int, name varchar(30) ").arg(getTableName().c_str());

	string *cols = getColumns();
	string *coltypes = getColumnTypes();

	int colcount = getColumnCount();
	for(int i=0;i<colcount;i++){
               qs2 = qs2.append(",").append(cols[i].c_str()).append(" ").append(coltypes[i].c_str());
	}

	qs2 = qs2.append(" );");

    qDebug() << QString("Creating table with > ").append(qs2);
	QSqlQuery query(qs2);
    if(query.isActive()){
        qDebug() << QString("Done create");
    } else {
        qDebug() << QString("WARNING: FAILED TO CREATE MAINTABLE");
    }


}
void AbstractMapper::createTable(){
    checkAndAdjustTable();
	
	map<string,AbstractAssociation*>::iterator it;
	for(it=mapAssociations.begin(); it!=mapAssociations.end(); it++){
		it->second->createTable();
	}
	
	map<string,Reference*>::iterator ref_it;
	for(ref_it=mapReferences.begin();ref_it!=mapReferences.end(); ref_it++){
		ref_it->second->createTable();
	}
}

/*!
    \fn AbstractMapper::getVersion()
 */
/*
string AbstractMapper::getVersion()
{
    return this->version;
}
*/


/*!
    \fn AbstractMapper::create()
 */
MappedObject*  AbstractMapper::create(AbstractMapper *mapper)
{
      MappedObject *res = (MappedObject*) Database::getInstance()->create(mapper);
      Transactions::getCurrentTransaction()->add(res);
      
      return res;
}


void AbstractMapper::remove(PObject *mo)
{
	find_gen()->remove(mo);
	mo->setRemoved(true);
}


MappedObject*  AbstractMapper::create()
{
      MappedObject *res = (MappedObject*) Database::getInstance()->create(this);
      Transactions::getCurrentTransaction()->add(res);
      if(list_all) list_all->push_back(res);
      return res;
}


/*!
    \fn AbstractMapper::find_gen()
 */
list<PObject*>* AbstractMapper::find_gen()
{
    if(list_all==0){
	list_all = Database::getInstance()->getAll(this);
    }
    return list_all;
}


/*!
    \fn AbstractMapper::getAssociations()
 */
/*
list<Association*> AbstractMapper::getAssociations()
{
    /// @todo implement me
}
*/

/*!
    \fn AbstractMapper::getReferences()
 */
list<Reference*> AbstractMapper::getReferences()
{
    /// @todo implement me
}

/*!
    \fn AbstractMapper::getAssociations()
 */
list<AbstractAssociation*>* AbstractMapper::getAssociations()
{
    /// @todo implement me
}

/*1!
    \fn AbstractMapper::getProperties()
 */
list<Property*> AbstractMapper::getProperties()
{
    /// @todo implement me
}


/*!
    \fn AbstractMapper::registerAssociation(Association *asc)
 */
void AbstractMapper::registerAssociation(AbstractAssociation *asc)
{
    ObjectFactory::getInstance()->registerAssociation(asc);
}






/*!
    \fn AbstractMapper::getName()
 */
string AbstractMapper::getName()
{
    return getClassName()+"mapper";
}








/*!
    \fn AbstractMapper::method_1()
 */
MappedObject* AbstractMapper::getSingletonInstance()
{
	MappedObject *result=0;
	if(!find_gen()->empty()){
		result = (MappedObject*) find_gen()->front();
	} else {
		result = create();
	}
	return result;
}
