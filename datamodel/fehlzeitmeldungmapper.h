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
 // Written on Do. Mär 12 19:25:30 2015
// 
 #ifndef fehlzeitmeldungMAPPER_H 
 #define fehlzeitmeldungMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "fehlzeitmeldung.h" 
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
 #include "meldungmapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class fehlzeitmeldungmapper : public meldungmapper 
{
 public:
     static fehlzeitmeldungmapper* getInstance();
     ~fehlzeitmeldungmapper();
     static fehlzeitmeldung* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<fehlzeitmeldung*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();


protected:
     fehlzeitmeldungmapper();
 
 private:
    static fehlzeitmeldungmapper* instance;
 

   string *columnTypes;
    string *columns;
   
 
 };
 
 #endif
 