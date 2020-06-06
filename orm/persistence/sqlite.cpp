#include "sqlite.h"

#include <string>
#include <algorithm>

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

//#include "qapplication.h"
//#include "qmessagebox.h"


#include "qobject.h"
#include "services/utils/utils.h"
#include "orm/persistence/database.h"
#include "pcollectionpersistence.h"

#include <QStringList>

using namespace std;

SQLite::SQLite(){
    connection=QSqlDatabase(); // invalid dummy
}
SQLite::~SQLite(){
    connection.close();
    cache.clear();
    tables.clear();
    mapPersistentClasses.clear();
}

QSqlDatabase SQLite::getConnection(){
    if( ! connection.isOpen() ){
        if( ! connection.isValid()){
            if(Database::databasename == ""){
                qDebug() << "SQLite::getConnection() : Could not get Connection: empty databasename";
                return connection;
            }
            qDebug() << "Trying to get connections";

            qDebug() << QString("Setting database Name to %1").arg(Database::databasename);
            QStringList args = databasename.split(":");
            //connection = QSqlDatabase::addDatabase("QMYSQL3");
            connection = QSqlDatabase::addDatabase(args.at(0));
            connection.setDatabaseName(args.at(1));
            if(args.size()>3){
                connection.setHostName(args.at(2));
                if(args.size()>4){
                    connection.setUserName(args.at(3));
                    connection.setPassword(args.at(4));
                } else {

                }
            } else {
                connection.setHostName("");
                connection.setUserName(USER);
                connection.setPassword("");
            }



            if(! connection.isValid()){
                    qWarning() << QString("Failed to connect to database %1").arg(Database::databasename);
                    return connection;
            } else {
                qDebug() << "Connection ok";
            }

        }


        if(! connection.open()){
            qWarning() << QString("Failed to open database (%1), trying to create").arg(connection.lastError().text());
            QString qs = QString("create database %1").arg(Database::databasename);
            QSqlQuery q1(qs);
            if(q1.isActive()){
               qDebug() << QString("New database created ");
            } else {
               qWarning() << QString("Query failed: %1").arg(connection.lastError().text());
            }
            if( !connection.isOpen() ){
               qWarning() << "Failed to open database";
            }


            if(connection.isOpen()){
                QString mesg1("Found existing table %1");
                QSqlQuery q("show tables");
                if(q.isActive()){
                    while(q.next()){
                        string tname = q.value(0).toString().toStdString();
                        tables.push_back( tname );
                        //qDebug(mesg1.arg(tname));
                    }
                }


            }
        }

        //registerPersistentClass(PCollectionPersistence::getInstance());
        checkForOldstyleDb();
      }


      return connection;

}

void SQLite::checkForOldstyleDb()
{
    QSqlQuery q("select * from idtoname where name LIKE 'PlatzCanvasItem'");
    if(q.isActive() && q.isValid())
    {
        qDebug() << "Found old style DB -- correcting";

        QSqlQuery q1("update idtoname set name='PlatzGraphicsItem' where name LIKE 'PlatzCanvasItem'");
        if(!q1.isActive()) qDebug() << "WARNING: Failed to correct PlatzCanvasItem";

        QSqlQuery q2("update idtoname set name='PObjectGraphicsItem' where name LIKE 'PObjectCanvasItem'");
        if(!q2.isActive()) qDebug() << "WARNING: Failed to correct PObjectCanvasItem";

        QSqlQuery q3("rename table pobjectcanvasitem to pobjectgraphicsitem");
        if(!q3.isActive()) qDebug() << "WARNING: Failed to rename table pobjectcanvasitem";

        QSqlQuery q4("rename table platzcanvasitem to platzgraphicsitem");
        if(!q4.isActive()) qDebug() << "WARNING: Failed to rename table platzcanvasitem";

        QSqlQuery q5("rename table PObjectCanvasItem_PObject to PObjectGraphicsItem_PObject");
        if(!q5.isActive()) qDebug() << "WARNING: Failed to rename table platzcanvasitem";

        QSqlQuery q6("rename table PlatzCanvasItem_platz to PlatGraphicsItem_platz");
        if(!q6.isActive()) qDebug() << "WARNING: Failed to rename table platzcanvasitem";

        QSqlQuery q7("rename table schultagcanvasitem to schultaggraphicsitem");
        if(!q7.isActive()) qDebug() << "WARNING: Failed to rename table platzcanvasitem";

        QSqlQuery q8("ALTER TABLE PObjectGraphicsItem_PObject CHANGE PObjectCanvasItem_id PObjectGraphicsItem_id int(11)");
        if(!q8.isActive()) qDebug() << "WARNING: Failed to rename table platzcanvasitem";

    }

}

bool SQLite::isOpen()
{
    if(connection.isValid() & connection.isOpen()){
        return true;
    } else {
        getConnection();
        return connection.isValid() & connection.isOpen();
    }
}

/*!
    \fn SQLite::close()
 */

void SQLite::deleteObject(PObject *object){
    if(isOpen()){

        int id = object->getID();
        PersistenceClass *persistenceObject = object->getPersistenceObject();
        QString tableName = getTableName(persistenceObject).c_str();

        QString qs = QString("delete from %1 where id=%2;").arg(tableName).arg(id);
        QSqlQuery q(qs);
        if(! q.isActive() ) qDebug("Failed to delete table entry for object");

        QString qs2 = QString("delete from idtoname where id=%1;").arg(id);
        QSqlQuery q2(qs2);

        if(! q2.isActive() ) qDebug("Failed to delete table entry for object");
    }
}


void SQLite::save(PObject *object){
    if(isOpen()){

        qDebug() << QString("Saving object with id %1").arg(object->getID());
        PersistenceClass *persistenceObject = object->getPersistenceObject();
        QString table = getTableName(persistenceObject).c_str();
        int id = object->getID();
        if(object->getRemoved()){
            QString qs = QString("delete from %1 where id = %2;").arg(table).arg(id);
            QSqlQuery q1(qs);
            if(! q1.isActive() ){ qDebug("DatabaseImpl::save: Failed to delete object (Ph 1)"); return;}
            qs = QString("delete from idtoname where id = %1;").arg(id);
            QSqlQuery q2(qs);
            if(! q2.isActive() ){ qDebug("DatabaseImpl::save: Failed to delete object (Ph 2)");return;}
        } else {

            QString qs = QString("update  ").append(getTableName(persistenceObject).c_str() )
                    .append(  "  set name=\"" ).append(object->getName().c_str()).append("\"") ;

            std::locale::global(std::locale("en_US")); // Hack to have a decimal point in Data

            string *columns = persistenceObject->getColumns();
            string *values = persistenceObject->getValues(object);

            std::locale::global(std::locale("")); //Reset from previous Hack

            int cc = persistenceObject->getColumnCount();
            for(int i=0; i <cc; i++){
                qs.append(",").append(columns[i].c_str()).
                        append( " = \"").append(mask(values[i].c_str())).append( "\" " );
                /*
                if(i<cc-1){
                    qs.append( ", ");
                }
                */

            }

            qs=qs.append(" where id = %1").arg(id);

            //qs=mask(qs);
            QSqlQuery q(qs);
            if(!q.isActive()){
                qWarning() << QString("query failed > ").append(qs);
            } else {
                //qDebug(QString("update ok > ").append(qs));
            }
        }
    }
}

/* Why is this needed ?
    Seems to be an sql-problem: SQL treats \ as escape-ch meaning the following one should be
    understood literally
*/
QString SQLite::mask(QString qs)
{
   /* The masking of \ is required for MySql but not for SQLite it seems.
     * Moreover with MySql the additional \ is automatically removed upon insertion
     */
    //return qs.replace("\\","\\\\").replace("\"", "\\\"");
    return qs;

}

QString SQLite::unmask(QString qs)
{
    return qs.replace("\\\\","\\").replace("\\\"", "\"");
}

void SQLite::save(PCollection* collection)
{
    qDebug() << QString("Saving collection %1").arg(collection->getID());

    if(isOpen()){
        //PersistenceClass *persistenceObject = collection.getPersistenceObject();
        int collId = collection->getID();
        string name = collection->getName();

        string qs = "update collections set name=\"" + name + "\" where id=" + to_string(collId) + ";";
        QSqlQuery q(qs.c_str());

        for(PCollection::iterator it=collection->begin(); it!=collection->end(); it++)
        {
            PObject *o = *it;
            int id = o->getID();

            QString select_string("select * from collections_contents where collid=%1 and id=%2;");
            QSqlQuery qq(select_string.arg(collId).arg(id));
            if(qq.size()==0){
                qDebug("Insert into collections_contents ...");
                QString insert_string = QString("insert into collections_contents values (%1,%2);");
                QSqlQuery qqq(insert_string.arg(collId).arg(id));
                if(qqq.isActive()){
                    qDebug(" OK !! ");
                } else {
                    qDebug() << QString(" Error !! > ").append(qqq.lastQuery());
                }
            } else if(qq.size() > 1){
                qWarning() << QString("Dublicated entries for collection %1 in collections_contents").arg(collId);
            } else {
                qDebug() << QString("Query on collectons_contents returned %1 elements").arg(qq.size());
            }

            save(o);
        }
    }
}

void SQLite::save(PTree* tree)
{
    qDebug() << QString("Saving ptree %1").arg(tree->getID());

    if(isOpen()){
        //PersistenceClass *persistenceObject = collection.getPersistenceObject();
        int collId = tree->getID();
        string name = tree->getName();
        int pId = 0;
        int cId=0;

        if(PTree *pt = tree->getParent()){
                pId = pt->getID();
        }
        if(PCollection *cc = tree->getChildren()){
            save(cc);
            cId = tree->getChildren()->getID();
        }
        string qs = "update trees set (name,parent,children) =\"" + name + "\"," + to_string(pId) + "," + to_string(cId) +") where id=" + to_string(collId) + ";";
        QSqlQuery q(qs.c_str());
    }
}



string SQLite::getTableName(PersistenceClass *persOb){
     return persOb->getTableName();
}



bool SQLite::tableExists(string tname){
       list<string>::iterator res = std::find(tables.begin(), tables.end(), tname);
       if(res == tables.end()){
            return false;
        }  else {
            return true;
        }
}

/*
void SQLite::createTable(PersistenceClass *persOb){
    string tname = persOb->getTableName();

    string qs = "create table " + tname + " ( ";
    qs += "id int, ";

    string *cols = persOb->getColumns();
    string *coltypes = persOb->getColumnTypes();

    int colcount = persOb->getColumnCount();
    for(int i=0;i<colcount;i++){
               qs += cols[i] + " " + coltypes[i];
             if(i<colcount-1){
                       qs += ", ";
             }

    }

    qs += " );";

    qDebug(QString("Creating table with > ").append(QString(qs.c_str()) ));

    if( !connection) getConnection();
    QSqlQuery query(qs.c_str());

    tables.push_back(tname);
    qDebug(QString("Done create"));
}
*/



PObject* SQLite::create(string className){

        PersistenceClass *persObj = mapPersistentClasses[className];
    if(!persObj){
        qWarning() << QString("Class %1 not registered: Failed to create").arg(to_qstring(className));
        return 0;
    }

    return create(persObj);
}

PObject* SQLite::create(PersistenceClass *persObj){
    PObject *o=0;

    if(isOpen()){
        o = persObj->createNewObject();
        QString className = QString::fromStdString(persObj->getClassName());

        int id = getNewId();
        o->setID(id);
        string name=persObj->getClassName().substr(0,10) + "(" + to_string(id) + ")";
        o->setName(name);

        QString insert_query_string("insert into %1 (id,name) values (%2,\"%3\");");
        QSqlQuery q(insert_query_string.arg(getTableName(persObj).c_str()).arg(id).arg(name.c_str()));
        if(q.isActive()){
        qDebug() << QString("Added object: ") + q.lastQuery();
        } else {
            qWarning() << QString("Query failed: ") + q.lastQuery();
            return 0;
        }

        QString idtoname_query_string("insert into idtoname values (%1,\"%2\");");
        QSqlQuery qq(idtoname_query_string.arg(id).arg(className));
        if(!qq.isActive()){
            qWarning() << QString("Failed to insert into idtoname >").append(idtoname_query_string);
            return 0;
        }
        qDebug() << QString("Inserted %1,%2  into idtoname").arg(id).arg(className);

        //qDebug(QString("Saving object with id ") + QString(to_string(id).c_str()));

        cache[id]=o;
        //o= load(className, id);
        //save(o);
    }
    return o;
}






PObject * SQLite:: load(string className, int id) {
     PObject *o=0;

     if(isOpen()){
        o = cache[id];
        if(!o)
        {
            PersistenceClass *persObj = mapPersistentClasses[className];
            if(!persObj){
                qWarning() << QString("SQLite: Class ").append(className.c_str()).append(" not registered: Failed to load object");
                return 0;
            }

            QString qs("select id, name ");

            string *cols = persObj->getColumns();
            int colcount = persObj->getColumnCount();
            for(int i=0; i<colcount; i++){
                qs.append(",").append(cols[i].c_str());

            }
            qs = qs.append(" from ").append(getTableName(persObj).c_str())
                    .append(" where id = %1;").arg(id);

            /* use the query result to init object */
            QSqlQuery q(qs);
            if(q.isActive()){
                q.next();
                if(q.isValid()){
                    o = persObj->createNewObject(); //only create if valid entry found;
                    o->setID(id);
                    if(q.value(1).isValid()){
                        o->setName(q.value(1).toString().toStdString());
                    } else {
                        o->setName("Invalid");
                    }
                    Variant *res =  new Variant[colcount];
                    for(int i=0; i<colcount ; i++){
                        res[i] = q.value(i+2);
                        if(! res[i].isValid())  qWarning() << QString("DatabseImpl_Q: Invalid value from query > ").append(qs);
                    }
                    persObj->init(o,res);
                    delete[] res;
                    //qDebug() << QString("DatabseImpl_Q: Loading ok: %1, %2").arg(className.c_str()).arg(id);
                } else {
                    qDebug() << QString("DatabseImpl_Q: found invalid entry %1, %2 -- deleting").arg(className.c_str()).arg(id);
                    QString qs = QString("delete from idtoname where id = %1;").arg(id);
                    QSqlQuery q2(qs);
                    if(! q2.isActive() ){ qDebug() << "DatabaseImpl::save: Failed to delete object (Ph 2)";}
                }
            }  else {
                qWarning() << QString("DatabseImpl_Q: Query failed > ")+QString(qs);
                return 0;
            }



            cache[id]=o;

        } else {
            //qDebug() << QString("SQLite::load(): Found object in cache: %1, %2").arg(className.c_str()).arg(id);
        }
    }

    return o;
}



/*
list<PObject*>* SQLite::getAll(string className){

    PersistenceClass *pc = mapPersistentClasses[className];
    if(!pc)
    {
        qWarning(QString("Class %1 not registered: getAll failed").arg(to_qstring(className)));
        return  res;
    }
}
*/

list<PObject*>* SQLite::getAll(PersistenceClass *persObj){
    list<PObject*>  *res=new list<PObject*>();

    if(isOpen()){
        string tname = getTableName(persObj);
        string className = persObj->getClassName();

        QSqlQuery q(QString("select id from ") + QString(tname.c_str()) );
        if(q.isActive())
        {
            while(q.next()){
                int id = q.value(0).toInt();
                PObject *o = load(className,id);

                if(o){
                    res->push_back(o);
                } else {
                    qDebug() << QString("SQLite::getAll: Load failed for id %1").arg(id);
                }
                //qDebug(QString("DatabseImpl_Q::getAll: Added object with id %1").arg(id));
            }
        } else {
            qWarning() << QString("DatabseImpl_Q::getAll(%1): Querry failed").arg(className.c_str());
        }
    }


    return res;
}

int SQLite::getNewId(){
     int result;

     QSqlQuery q1("select current_id from admin");
     if(q1.isActive()){
       q1.next();
       result = q1.value(0).toInt();
     } else {
              qWarning() << "Could not get current id";
     }

     result +=1;
     QString result_string(to_string(result).c_str());

     QSqlQuery q2(QString("update admin set current_id = ") + result_string);
     qDebug() << QString("reset current id to ").append(result_string);

     return result;
}


void SQLite::createTable(QString tableName, QStringList columns)
{
     QString qs = QString("show tables like '%1';").arg(tableName);
     QSqlQuery query0(qs);
     if(query0.isActive() && query0.next()){
         qDebug() << QString("Table %1 already exists, not creating!").arg(tableName);
         return;
     }

     qs = QString("create table %1 ( ").arg(tableName);


     for(int i=0; i< columns.size(); i++)
     {
         qs = qs.append(",").append(columns.at(i));
     }
     qs = qs.append(" );");

     qDebug() << QString("Creating table with > ").append(qs);
     QSqlQuery query(qs);
     if(query.isActive()){
        qDebug() << QString("Done create");
     } else {
         qDebug() << QString("Create failed");
     }
     //tables.push_back(tname);


}



void SQLite::registerPersistentClass(PersistenceClass *po, string version)
{
    if(isOpen()){
    mapPersistentClasses[po->getClassName()]=po;
    //mapVersions[po->getClassName()] = version;
    }else {
    qWarning() << QString("Could not register class %1 - getConnection() failed").arg(po->getClassName().c_str());
    }
}

void SQLite::registerVersion(PersistenceClass *po, string version){
    if(isOpen()){
    QString qs1(QString("update versions set version=\"%1\" where class=\"%2\";").arg(version.c_str()).arg(po->getClassName().c_str()));
    QSqlQuery q1(qs1);
    if(!q1.isActive() || !q1.isValid())
    {
        qs1= QString("insert into versions (class,version) values (\"%1\", \"%2\");").arg(po->getClassName().c_str()).arg(version.c_str());
        q1 = QSqlQuery(qs1);
        if(!q1.isActive()){
            qWarning() << QString("Failed to write version: %1").arg(connection.lastError().text());
        } else {
            qDebug() << QString("Database_impl: inserted version for %1").arg(po->getClassName().c_str());
        }
    } else {
        qDebug() << QString("Database_impl: updated version for %1").arg(po->getClassName().c_str());
    }
    }else {
    qWarning() << QString("Could not register version for %1 - getConnection() failed").arg(po->getClassName().c_str());
    }


}

/*
void SQLite::writeVersions()
{
    QString qs("delete from versions;");
    QSqlQuery q(qs);
    if(!q.isActive()){qDebug("Criticla","Could not delete from versions");}

    QString qs2("insert into versions values (\"%1\",\"%2\");");
    map<QString,QString>::iterator it;
    for(it = mapVersions.begin(); it != mapVersions.end(); it++){
        QString qs2p = qs2.arg(it->first).arg(it->second);
        QSqlQuery q2(qs2p);
        if(!q2.isActive()){qDebug(QString("Critical: Could not insert into versions : %1").arg(qs2p));}
    }

}
*/

/*!
    \fn SQLite::tableExists(PersistenceClass *persObj)
 */
bool SQLite::tableExists(PersistenceClass *persObj)
{
      return tableExists(persObj->getTableName());
}


/*!
    \fn SQLite::loadCollection(PCollection *col)
 */
void SQLite::loadCollection(PCollection *col)
{
       if(isOpen()){
    int id = col->getID();
    int idd=0;
    QSqlQuery q1(QString("select * from collections_contents where collid=%1;").arg(id));
    if(q1.isActive()){
            while(q1.next()){
                    idd=q1.value(1).toInt();
                    PObject *o=loadObjectById(idd);
                    col->push_back(o);
                    qDebug() << QString("Added object to collection: id=").append(idd);
    }
    }else {
        qWarning() << QString("Collection %1 empty !?").arg(id);
    }
       }
}




/*!
    \fn SQLite::loadObjectById(int id)
 */
PObject* SQLite::loadObjectById(int id)
{
    PObject *o=0;
    if(isOpen()){
        //qDebug(QString("SQLite::loadObjectById(): Trying to load by id %1").arg(id));

        QString qs = QString("select * from idtoname where id=%1").arg(id);
        QSqlQuery q1(qs);
        if(q1.isActive()){
            q1.next();
            if(q1.isValid() && q1.value(1).isValid()){
                QString className = q1.value(1).toString();
                //qDebug(QString("SQLite::loadObjectById(): Found for id : ").append(className));
                o=load(className.toStdString(), id);
            }else{
                qWarning() << QString("SQLite::loadObjectById : \
                                      failed, could not get valid classname for id %1").arg(id);
            }
        } else {
            qWarning() << QString("SQLite::loadObjectById : Failed to load > ").append(qs);
        }
    }

    return o;
}





/*!
    \fn SQLite::executeSql(string sql)
 */
void SQLite::executeSql(string sql)
{
    /// @todo implement me
}





/*!
    \fn SQLite::getCurrentVersion()
 */
string SQLite::getCurrentVersion(string className)
{
    if(isOpen()){
            QString qs = QString("select * from versions where class=\"%1\"").arg(className.c_str());
        QSqlQuery q1(qs);
        if(q1.isActive()){
            q1.next();
            if(q1.isValid() && q1.value(1).isValid()){
                return q1.value(1).toString().toStdString();
            } else {
                qWarning() << QString("Could not read version for %1: %2").arg(className.c_str()).arg(connection.lastError().text());
                return string();
            }
        } else {
            qWarning() << QString("Could not read version for %1: %2").arg(className.c_str()).arg(connection.lastError().text());
            return string();
        }
    } else {
        qDebug() << QString("DatabaseImpl::getCurrentVersion : not open, could not read version");
        return  string();
    }
}

