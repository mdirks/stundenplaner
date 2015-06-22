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
 // Written on Mo. Jun 22 20:24:34 2015
// 
 #ifndef notizsatzMAPPER_H 
 #define notizsatzMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "notizsatz.h" 
#include "notiz.h" 
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
 class notizsatzmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static notizsatzmapper* getInstance();
     ~notizsatzmapper();
     static notizsatz* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<notizsatz*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<notiz*> * findNotizen(int pri_id);
  list<notiz*> * findNotizen(int pri_id,string prop,string value);

protected:
     notizsatzmapper();
 
 private:
    static notizsatzmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<notizsatz, notiz> *asc_Notizen;
  
 
 };
 
 #endif
 