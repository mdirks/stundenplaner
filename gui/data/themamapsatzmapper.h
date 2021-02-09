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
 // Written on Do. Jan. 28 15:05:59 2021
// 
 #ifndef ThemaMapSatzMAPPER_H 
 #define ThemaMapSatzMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "themamapsatz.h" 
#include "themamap.h" 
#include "themamapsatz.h" 
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
 class ThemaMapSatzmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static ThemaMapSatzmapper* getInstance();
     ~ThemaMapSatzmapper();
     static ThemaMapSatz* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<ThemaMapSatz*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<ThemaMap*> * findThemaMaps(int pri_id);
  list<ThemaMap*> * findThemaMaps(int pri_id,string prop,string value);
  list<ThemaMapSatz*> * findChildren(int pri_id);
  list<ThemaMapSatz*> * findChildren(int pri_id,string prop,string value);

protected:
     ThemaMapSatzmapper();
 
 private:
    static ThemaMapSatzmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<ThemaMapSatz, ThemaMap> *asc_ThemaMaps;
 Association<ThemaMapSatz, ThemaMapSatz> *asc_Children;
  
 
 };
 
 #endif
 