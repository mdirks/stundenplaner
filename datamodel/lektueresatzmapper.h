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
 // Written on Mi. Jan. 27 10:46:20 2021
// 
 #ifndef lektueresatzMAPPER_H 
 #define lektueresatzMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "lektueresatz.h" 
#include "lektuere.h" 
#include "lektueresatz.h" 
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
 
 /** 
 @author Marcus Dirks 
 */ 
 class lektueresatzmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static lektueresatzmapper* getInstance();
     ~lektueresatzmapper();
     static lektueresatz* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<lektueresatz*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<lektuere*> * findLektueren(int pri_id);
  list<lektuere*> * findLektueren(int pri_id,string prop,string value);
  list<lektueresatz*> * findChildren(int pri_id);
  list<lektueresatz*> * findChildren(int pri_id,string prop,string value);

protected:
     lektueresatzmapper();
 
 private:
    static lektueresatzmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<lektueresatz, lektuere> *asc_Lektueren;
 Association<lektueresatz, lektueresatz> *asc_Children;
  
 
 };
 
 #endif
 