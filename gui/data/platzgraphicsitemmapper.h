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
 // Written on Mo. Apr. 20 13:52:16 2020
// 
 #ifndef PlatzGraphicsItemMAPPER_H 
 #define PlatzGraphicsItemMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "platzgraphicsitem.h" 
#include "datamodel/platz.h" 
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
 class PlatzGraphicsItemmapper : public PObjectGraphicsItemmapper 
{
 public:
     static PlatzGraphicsItemmapper* getInstance();
     ~PlatzGraphicsItemmapper();
     static PlatzGraphicsItem* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<PlatzGraphicsItem*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

platz * findPlatz(int pri_id);

protected:
     PlatzGraphicsItemmapper();
 
 private:
    static PlatzGraphicsItemmapper* instance;
 

   string *columnTypes;
    string *columns;
   
 
 };
 
 #endif
 