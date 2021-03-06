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
 // Written on Mon Aug 25 11:59:38 2014
// 
 #ifndef SchultagCanvasItemMAPPER_H 
 #define SchultagCanvasItemMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "schultagcanvasitem.h" 
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
 #include "pobjectcanvasitemmapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class SchultagCanvasItemmapper : public PObjectCanvasItemmapper 
{
 public:
     static SchultagCanvasItemmapper* getInstance();
     ~SchultagCanvasItemmapper();
     static SchultagCanvasItem* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<SchultagCanvasItem*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();


protected:
     SchultagCanvasItemmapper();
 
 private:
    static SchultagCanvasItemmapper* instance;
 

   string *columnTypes;
    string *columns;
   
 
 };
 
 #endif
 