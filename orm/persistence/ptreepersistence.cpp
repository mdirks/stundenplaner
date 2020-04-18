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
//#include "ptree.h"

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
    columns = new string[3];
    columns[0] = "name";
    columns[1] = "pid";
    columns[2] = "cid";

    columnTypes = new string[3];
    columnTypes[0] = "char(20)";
    columnTypes[1] = "int";
    columnTypes[2] = "int";
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

string* PTreePersistence::getColumnTypes()
{
    return columnTypes;
}

string* PTreePersistence::getColumns()
{
    return columns;
}

string* PTreePersistence::getValues(PObject* realSubject)
{
    string* values = new string[3];

    PTree *tr = (PTree*)realSubject;
    if(tr){
        values[0] = realSubject->getName();
        values[1] = "0";
        if(PTree *pt = tr->getParent()){
            values[2] = pt->getID();
        }
        values[2] = "0";
        if(PCollection *cc = tr->getChildren()){
                values[1] = cc->getID();
        }


    }

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
    int pId = res[0].asint();
    PTree *ptr = (PTree*) Database::getInstance()->loadObjectById(pId);
    tr->setParent(ptr);
    int cId = res[1].asint();
    PCollection *cc = (PCollection*) Database::getInstance()->loadObjectById(cId);
    tr->setChildren(cc);

}
