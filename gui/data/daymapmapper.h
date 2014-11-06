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
 // Written on Wed Oct 1 14:16:29 2014
// 
 #ifndef DayMapMAPPER_H 
 #define DayMapMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "daymap.h" 
#include "pobjectgraphicsitem.h" 
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
 class DayMapmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static DayMapmapper* getInstance();
     ~DayMapmapper();
     static DayMap* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<DayMap*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<PObjectGraphicsItem*> * findGraphicsItems(int pri_id);

protected:
     DayMapmapper();
 
 private:
    static DayMapmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<DayMap, PObjectGraphicsItem> *asc_GraphicsItems;
  
 
 };
 
 #endif
 