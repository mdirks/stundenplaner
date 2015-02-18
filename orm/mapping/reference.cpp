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
#include <QSqlQuery>
#include <QDebug>

#include "reference.h"
#include "../persistence/database.h"


Reference::Reference(const Reference &ref)
{
	this->table = ref.table;
	this->pri_col = ref.pri_col;
	this->ref_col = ref.ref_col;
	this->ref_class = ref.ref_class;
}

Reference::Reference(string table, string pri_col, string ref_col, string ref_class){
	this->table = table;
	this->pri_col = pri_col;
	this->ref_col = ref_col;
	this->ref_class = ref_class;
}


Reference::Reference(string pri_class, string ref_class, string ref_name){
	this->table = /*string("ref") +*/ pri_class.erase(0,pri_class.find_last_of("/")+1) + string("_")+ ref_class.erase(0,ref_class.find_last_of("/")+1)+string("_")+ref_name;
	this->ref_class = ref_class.erase(0,ref_class.find_last_of("/")+1);
	this->pri_col = pri_class.erase(0,pri_class.find_last_of("/")+1) + string("_id");
	this->ref_col = ref_class.erase(0,ref_class.find_last_of("/")+1) + string("_id");
}



Reference::Reference(string pri_class, string ref_class){
	this->table = /*string("ref") +*/ pri_class.erase(0,pri_class.find_last_of("/")+1) + string("_")+ ref_class.erase(0,ref_class.find_last_of("/")+1);
	this->ref_class = ref_class.erase(0,ref_class.find_last_of("/")+1);
	this->pri_col = pri_class.erase(0,pri_class.find_last_of("/")+1) + string("_id");
	this->ref_col = ref_class.erase(0,ref_class.find_last_of("/")+1) + string("_id");
}


Reference::~Reference()
{
}

PObject* Reference::findReferee(int pri_id)
{
	PObject *res=0;
	
	Database *db = Database::getInstance();
	if(db->isOpen()){
        QString qs = QString("select %1 from %2 where %3=%4").arg(ref_col.c_str()).arg(table.c_str()).arg(pri_col.c_str()).arg(pri_id);
		QSqlQuery q(qs);
		if(q.isActive()){
			q.next();
			if(q.isValid() && q.value(0).isValid()){
                int ref_id = q.value(0).toInt();
				res = db->loadObjectById(ref_id);
                if(!res){
                    qDebug() << QString("Reference::findReferee FAILED  for %1,%2").arg(table.c_str()).arg(pri_id);
                }
				//res = db->load(ref_class,ref_id);
			} else {
				//qWarning(QString("Reference::findReferee: could not get referee %1, invalid entry for id %2").arg(ref_class).arg(pri_id)); 
			}
		}
	}	
	return res;
	
}

void Reference::deleteReferee(int pri_id)
{
		Database::getInstance();
		
        QString qs1 = QString("delete from %1 where %2 = %3;").arg(table.c_str()).arg(pri_col.c_str()).arg(pri_id);
		QSqlQuery q1(qs1);
        if(! q1.isActive() ) qDebug() << "Reference::save: Failed to delete reference";

}

void Reference::createTable()
{
	Database *db = Database::getInstance();
	
	/*
	QString qs = QString("drop table %1;").arg(table);
	QSqlQuery q(qs);
	if(!q.isActive()) qDebug("Failed to drop table");
	*/	

    QString qs2 = QString("create table %1 (%2 int, %3 int);").arg(table.c_str()).arg(pri_col.c_str()).arg(ref_col.c_str());
	QSqlQuery q2(qs2);
    if(!q2.isActive()) qDebug() << QString("Failed to create reference table : ").append(qs2);

}


void Reference::save(PObject *realSubject, PObject *refObject)
{
	qDebug("Reference::save !!");
	if(realSubject !=0){
	//if(refObject != 0){
		Database::getInstance();
		
		int pri_id = realSubject->getID();
        QString qs1 = QString("delete from %1 where %2 = %3;").arg(table.c_str()).arg(pri_col.c_str()).arg(pri_id);
		QSqlQuery q1(qs1);
        if(! q1.isActive() ) qDebug() << "Reference::save: Failed to delete old associations";
		
		if(refObject != 0){
            QString qs2 = QString("insert into  %1 (%2,%3) values (%4,%5);").arg(table.c_str()).arg(pri_col.c_str()).arg(ref_col.c_str()).arg(pri_id);
			int ref_id = refObject->getID();
			QSqlQuery q2(qs2.arg(ref_id));
            if( !q2.isActive() ) qDebug() << "Reference::save : Failed to insert new association";
		} else {
            qDebug() << "Reference::save : Given refObject was null, did not save";
		}
	} else {
        qDebug() << "Reference::save : Given realSubject was null, did not save";
	}
}









