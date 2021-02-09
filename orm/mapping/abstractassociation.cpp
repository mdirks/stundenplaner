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
#include "abstractassociation.h"

#include <QString>
#include <QSqlQuery>
#include <QDebug>

#include "mappingcontroler.h"
#include "../persistence/database.h"


AbstractAssociation::AbstractAssociation(const AbstractAssociation& asc)
{
	this->table = asc.table;
	this->pri_col = pri_col;
	this->asc_col = asc_col;
	this->asc_class  = asc_class;
    //typeMapper=MappingControler::getInstance()->getMapperByName(asc_class);

}
AbstractAssociation::AbstractAssociation(string table,  string pri_col, string asc_col, string asc_class)
{
	this->table=table;
	this->pri_col = pri_col;
	this->asc_col = asc_col;
	this->asc_class = asc_class;
    //typeMapper=MappingControler::getInstance()->getMapperByName(asc_class);
}



void AbstractAssociation::createTable(){
    bool suc;
    Database *db = Database::getInstance();
	
	/*QString qs = QString("drop table %1;").arg(table);
	QSqlQuery q(qs);
	if(!q.isActive()) qDebug("Failed to drop table");
	*/
	
    QString qs2 = QString("create table %1 (%2 int, %3 int);").arg(table.c_str()).arg(pri_col.c_str()).arg(asc_col.c_str());
	QSqlQuery q2(qs2);
    if(!q2.isActive()){
        suc=false;
        qDebug() << QString("Failed to create association table : ").append(qs2);
    }
}
