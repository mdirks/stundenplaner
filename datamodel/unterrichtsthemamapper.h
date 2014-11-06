 //  
 // C++ Interface: stundepersistence 
 //   
 // Description:  
 // 
 // 
 // Author: Marcus Dirks <mopp@suse>, (C) 2005 
 //  
 // Copyright: See COPYING file that comes with this distribution 
 // 
 // 
 #ifndef unterrichtsthemaMAPPER_H 
 #define unterrichtsthemaMAPPER_H 
 
 #include "../orm/persistence/pobject.h"
 #include "../orm/mapping/mappedobject.h"
#include "../orm/mapping/association.h"
#include "../orm/persistence/persistenceclass.h"
 #include "../datamodel/unterrichtsthema.h" 
#include "../datamodel/stunde.h" 
#include "../datamodel/reihe.h" 
#include "../orm/mapping/abstractmapper.h"
 #include "../orm/persistence/variant.h"
 #include "../orm/repository/repositoryentryimpl.h"
 #include "../orm/repository/stringproperty.h"
 #include "../orm/repository/integerproperty.h"
 #include "../orm/repository/pobjectproperty.h"
 #include "../orm/repository/collectionpropertyimpl.h"
 #include "../orm/repository/numericproperty.h"
 #include "../orm/repository/dateproperty.h"
 #include "../orm/repository/datetimeproperty.h"
 #include "../orm/repository/repositoryenabled.h"
 #include "notizholdermapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class unterrichtsthemamapper : public notizholdermapper 
{
 public:
     static unterrichtsthemamapper* getInstance();
     ~unterrichtsthemamapper();
 
     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     unterrichtsthema* create();
    list<unterrichtsthema*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<stunde*> * findStunden(int pri_id);
  list<reihe*> * findReihen(int pri_id);

protected:
     unterrichtsthemamapper();
 
 private:
    static unterrichtsthemamapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<unterrichtsthema, stunde> *asc_Stunden;
 Association<unterrichtsthema, reihe> *asc_Reihen;
  
 
 };
 
 #endif;
 
