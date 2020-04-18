//
// C++ Implementation: pcollectionpersistence
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pcollectionpersistence.h"
#include "database.h"

PCollectionPersistence* PCollectionPersistence::instance = 0;

PCollectionPersistence* PCollectionPersistence::getInstance()
{
	if(!instance)
	{
		instance = new PCollectionPersistence();
        instance->checkTable();
	}
	return instance;
}

void PCollectionPersistence::checkTable()
{
    QStringList columns;
    //columns << "id int" << "name varchar(30)";
    string *cols = getColumns();
    string *coltypes = getColumnTypes();

    int colcount = getColumnCount();
    for(int i=0;i<colcount;i++){
               QString col = QString("%1 %2").arg(cols[i].c_str()).arg(coltypes[i].c_str());
               columns << col;
    }
    Database::getInstance()->createTable(getTableName().c_str(),columns);
}

PCollectionPersistence::PCollectionPersistence()
 : PersistenceClass()
{
	columns = new string[1];
	columns[0] = "name";
	
	columnTypes = new string[1];
    columnTypes[0] = "varchar(30)";
}


PCollectionPersistence::~PCollectionPersistence()
{
}

string PCollectionPersistence::getTableName()
{
	return string("PCollection");
}

string PCollectionPersistence::getClassName()
{
	return string("PCollection");
}

string* PCollectionPersistence::getColumnTypes()
{
	return columnTypes;
}

string* PCollectionPersistence::getColumns()
{
	return columns;
}

string* PCollectionPersistence::getValues(PObject* realSubject)
{
	string* values = new string[1];
	values[0] = realSubject->getName();
	
	return values;
}

int PCollectionPersistence::getColumnCount()
{
	return 1;
}


void PCollectionPersistence::save(PCollection *realSubject)
{
      Database::getInstance()->save(realSubject);
}

PObject* PCollectionPersistence::createNewObject()
{
	return new PCollection();
}


/*!
    \fn PCollectionPersistence::init(PObject* o,QVariant[] res)
 */
void PCollectionPersistence::init(PObject* o, Variant *res)
{
	qDebug("Init PCollection ...");
	PCollection *col = (PCollection*) o;
	Database::getInstance()->loadCollection(col);
}
