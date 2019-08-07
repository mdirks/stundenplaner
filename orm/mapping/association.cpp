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
#include "association.h"

#include "qstring.h"
#include "qsqlquery.h"

#include "../persistence/database.h"

/*
export template<class AssocieType>
Association<AssocieType>::Association(const Association& asc) : AbstractAssociation(asc)
{
}


export template<class AssocieType>
Association<AssocieType>::Association(string table,  string pri_col, string asc_col, string asc_class)
	: AbstractAssociation(table,pri_col,asc_col,asc_class)
{
}

export template<class AssocieType>
Association<AssocieType>::~Association()
{
}



/*!
    \fn Association::findAssociates()
 */
 /*
 export template<class AssocieType>
list<AssocieType*> * Association<AssocieType>::findAssociates(int pri_id)
{
   
     list<PObject*> *result = new list<PObject*>();
       
       Database *db = Database::getInstance();
       QString qs = QString("select %1 from %2 where %3=%4").arg(asc_col).arg(table).arg(pri_col).arg(pri_id);
       QSqlQuery q(qs);
       while(q.next()){
             int asc_id = q.value(0).asInt();
	     PObject *o = db->loadObjectById(asc_id);
	     if(o){
		     result->push_back( o   );
	     } else {
	     	qDebug(QString("Association::findAssociates: could not get object from Database: id=%1").arg(asc_id));
	     }
	     //result->push_back(  db->load(asc_class, asc_id) );
       }
       return result;
}

export template<class AssocieType>
void Association<AssocieType>::save(PObject *realSubject, list<AssocieType*> *list_asc)
{
	qDebug("Association::save()");
	Database::getInstance();
	
	int pri_id = realSubject->getID();
	QString qs1 = QString("delete from %1 where %2 = %3;").arg(table).arg(pri_col).arg(pri_id);
	QSqlQuery q1(qs1);
	if(! q1.isActive() ) qDebug("stundepersistence::saveAssociation: Failed to delete old associations");
	
	QString qs2 = QString("insert into  %1 (%2,%3) values (%4,%5);").arg(table).arg(pri_col).arg(asc_col).arg(pri_id);
	//list<opo*>  *list_opos = st->getOpos();
	for(list<PObject*>::iterator it = list_asc->begin(); it != list_asc->end(); it++){
		int asc_id = (*it)->getID();
		qDebug(qs2.arg(asc_id));
		QSqlQuery q2(qs2.arg(asc_id));
		if( !q2.isActive() ) qDebug("stundepersistence::saveAssociation : Failed to insert new association");
	}
}
*/