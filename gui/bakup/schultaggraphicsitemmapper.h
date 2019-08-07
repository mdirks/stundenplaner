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
 // Written on Mon Aug 25 12:04:51 2014
// 
 #ifndef SchultagGraphicsItemMAPPER_H 
 #define SchultagGraphicsItemMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "schultaggraphicsitem.h" 
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
 #include "pobjectgraphicsitemmapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class SchultagGraphicsItemmapper : public PObjectGraphicsItemmapper 
{
 public:
     static SchultagGraphicsItemmapper* getInstance();
     ~SchultagGraphicsItemmapper();
     static SchultagGraphicsItem* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<SchultagGraphicsItem*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();


protected:
     SchultagGraphicsItemmapper();
 
 private:
    static SchultagGraphicsItemmapper* instance;
 

   string *columnTypes;
    string *columns;
   
 
 };
 
 #endif
 