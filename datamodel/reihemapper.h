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
 // Written on Sa. Mai 15 17:03:12 2021
// 
 #ifndef reiheMAPPER_H 
 #define reiheMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "reihe.h" 
#include "stunde.h" 
#include "orm/mapping/abstractmapper.h"
 #include "orm/persistence/variant.h"
 #include "orm/repository/repositoryentryimpl.h"
 #include "orm/repository/stringproperty.h"
 #include "orm/repository/integerproperty.h"
 #include "orm/repository/pobjectproperty.h"
 #include "orm/repository/collectionpropertyimpl.h"
 #include "orm/repository/numericproperty.h"
 #include "orm/repository/dateproperty.h"
 #include "orm/repository/booleanproperty.h"
 #include "orm/repository/datetimeproperty.h"
 #include "orm/repository/repositoryenabled.h"
 #include "notizholdermapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class reihemapper : public notizholdermapper 
{
 public:
     static reihemapper* getInstance();
     ~reihemapper();
     static reihe* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<reihe*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<stunde*> * findStunden(int pri_id);
  list<stunde*> * findStunden(int pri_id,string prop,string value);

protected:
     reihemapper();
 
 private:
    static reihemapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<reihe, stunde> *asc_Stunden;
  
 
 };
 
 #endif
 