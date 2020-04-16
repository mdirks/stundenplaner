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
#include "ptreepersistence.h"
#include "database.h"

PTreePersistence* PTreePersistence::instance = 0;

PTreePersistence* PTreePersistence::getInstance()
{
    if(!instance)
    {
        instance = new PTreePersistence();
    }
    return instance;
}

PTreePersistence::PTreePersistence()
 : PersistenceClass()
{
    columns = new string[1];
    columns[0] = "name";

    columnTypes = new string[1];
    columnTypes[0] = "char(20)";
}


PTreePersistence::~PTreePersistence()
{
}

string PTreePersistence::getTableName()
{
    return string("PTree");
}

string PTreePersistence::getClassName()
{
    return string("PTree");
}

string* TreePersistence::getColumnTypes()
{
    return columnTypes;
}

string* PTreePersistence::getColumns()
{
    return columns;
}

string* PTreePersistence::getValues(PObject* realSubject)
{
    string* values = new string[1];
    values[0] = realSubject->getName();

    return values;
}

int PTreePersistence::getColumnCount()
{
    return 1;
}


void PTreePersistence::save(PTree *realSubject)
{
      Database::getInstance()->save(realSubject);
}

PObject* PTreePersistence::createNewObject()
{
    return new PTree();
}


/*!
    \fn PTreePersistence::init(PObject* o,QVariant[] res)
 */
void PTreePersistence::init(PObject* o, Variant *res)
{
    qDebug("Init PTree ...");
    PTree *tr = (PTree*) o;
    Database::getInstance()->loadTree(tr);
}
