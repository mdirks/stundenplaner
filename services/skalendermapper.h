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
 // Written on Mo. Jun 22 20:23:46 2015
// 
 #ifndef SKalenderMAPPER_H 
 #define SKalenderMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "skalender.h" 
#include "gui/data/weekmap.h" 
#include "gui/data/daymap.h" 
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
 class SKalendermapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static SKalendermapper* getInstance();
     ~SKalendermapper();
     static SKalender* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<SKalender*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<WeekMap*> * findWeeks(int pri_id);
  list<WeekMap*> * findWeeks(int pri_id,string prop,string value);
  list<DayMap*> * findDays(int pri_id);
  list<DayMap*> * findDays(int pri_id,string prop,string value);

protected:
     SKalendermapper();
 
 private:
    static SKalendermapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<SKalender, WeekMap> *asc_Weeks;
 Association<SKalender, DayMap> *asc_Days;
  
 
 };
 
 #endif
 