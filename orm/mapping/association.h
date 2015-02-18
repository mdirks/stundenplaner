//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include <QString>
#include <QSqlQuery>
#include <QDebug>


#include <string>
#include <list>

#include "../persistence/database.h"
#include "../persistence/pobject.h"
#include "mappedobject.h"
#include "abstractassociation.h"

using namespace std;

/**
@author Marcus Dirks
*/
template<class PrimaryType, class AssocieType> class Association : public AbstractAssociation {

typedef void (PrimaryType::*deleter)(AssocieType*);
typedef void (PrimaryType::*adder)(AssocieType*);

public:
    Association(const Association& asc) : AbstractAssociation(asc) {};
    Association(string table,  string pri_col, string asc_col, string asc_class, adder f_a, deleter f_d) 
    	:  AbstractAssociation(table,pri_col,asc_col,asc_class), f_del(f_d), f_add(f_a) {}
   ~Association();
   
    
    list<AssocieType*> * findAssociates(int pri_id);
    void save(PObject *realSubject, list<AssocieType*> *list_asc);
    list<PrimaryType*>* findPrimaries(AssocieType* asc);
    void deleteObject(PObject *o);
    void deletePrimary(PrimaryType *p);
    
    
    
private:
	deleter f_del;
	adder f_add;
};


template<class PrimaryType, class AssocieType>
list<AssocieType*> * Association<PrimaryType, AssocieType>::findAssociates(int pri_id)
{
   
     list<AssocieType*> *result = new list<AssocieType*>();
       
       Database *db = Database::getInstance();
       if(db->isOpen()){
           QString qs = QString("select %1 from %2 where %3=%4").arg(asc_col.c_str()).arg(table.c_str()).arg(pri_col.c_str()).arg(pri_id);
		QSqlQuery q(qs);
		string clname = getAscClassName();
		while(q.next()){
            int asc_id = q.value(0).toInt();
			PObject *o = db->loadObjectById(asc_id); //load by id only to allow polymorphic content
            //PObject *o = db->load(clname, asc_id);
			if(o){
				AssocieType *at = dynamic_cast<AssocieType*>(o);
				if(at){
					result->push_back( at  );
				} else {
                    qDebug() << QString("Association::findAssociates: object from Database with wrong type");
				}
			} else {
                qDebug() << QString("Association::findAssociates: \
                                    FAILED to get object (%1) from Database").arg(clname.c_str());
			}
			//result->push_back(  db->load(asc_class, asc_id) );
		}
	}
       return result;
}

template<class PrimaryType, class AssocieType>
void Association<PrimaryType, AssocieType>::save(PObject *realSubject, list<AssocieType*> *list_asc)
{
	qDebug("Association::save()");
	Database::getInstance();
	
	int pri_id = realSubject->getID();
    QString qs1 = QString("delete from %1 where %2 = %3;").arg(table.c_str()).arg(pri_col.c_str()).arg(pri_id);
	QSqlQuery q1(qs1);
	if(! q1.isActive() ) qDebug("stundepersistence::saveAssociation: Failed to delete old associations");
	

    QString qs2 = QString("insert into  %1 (%2,%3) values (%4,%5);").arg(table.c_str()).arg(pri_col.c_str()).arg(asc_col.c_str()).arg(pri_id);

	
        for( typename list<AssocieType*>::iterator it = list_asc->begin(); it != list_asc->end(); it++){
		if(*it && (! (*it)->getRemoved())){
			int asc_id = (*it)->getID();
            qDebug()<< qs2.arg(asc_id);
			QSqlQuery q2(qs2.arg(asc_id));
            if( !q2.isActive() ) qDebug() << "stundepersistence::saveAssociation : Failed to insert new association";
		} else {
            qDebug() << "Invalid object in associe list";
		}
	}
	
	
}

template<class PrimaryType, class AssocieType>
/**
 * 
 * @param asc 
 * @return 
 */
list<PrimaryType*>* Association<PrimaryType, AssocieType>::findPrimaries(AssocieType* asc)
{
	//int pri_id = realSubject->getID();
	int asc_id = asc->getID();
	
	list<PrimaryType*> *list_pri = new list<PrimaryType*>();
	
    QString qs = QString("select %1 from %2 where %3 = %4;").arg(pri_col.c_str()).arg(table.c_str()).arg(asc_col.c_str()).arg(asc_id);
	QSqlQuery q(qs);
        while(q.next()){
         int asc_id = q.value(0).toInt();
		 
	    	 PObject *o = Database::getInstance()->loadObjectById(asc_id);
	         if(PrimaryType *pt = dynamic_cast<PrimaryType*>(o)){
		 	list_pri -> push_back(pt);
		 }
	}
	
	return list_pri;
}

template<class PrimaryType, class AssocieType>
/**
 * 
 * @param o 
 */
void Association<PrimaryType, AssocieType>::deleteObject(PObject* o)
{
        if( AssocieType *asc = dynamic_cast<AssocieType*>(o) )
	{
		list<PrimaryType*> *list_pri = findPrimaries(asc);
		
		for(typename list<PrimaryType*>::iterator it = list_pri->begin(); it != list_pri->end(); ++it)
		{
			PrimaryType *pri = (*it);
			(pri->*f_del)(asc);
			pri->save();
		}
		
	}
}

template<class PrimaryType, class AssocieType>
void Association<PrimaryType, AssocieType>::deletePrimary(PrimaryType* p)
{
	int pri_id = p->getId();
	
	Database *db = Database::getInstance();
        QString qs = QString("delete from %1 where %2=%3").arg(table.c_str()).arg(pri_col.c_str()).arg(pri_id);
        QSqlQuery q(qs);
        if( !q.isActive() ){ qDebug("Failed to delete primary from Association table"); }
}
#endif
