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
 #ifndef PObjectGraphicsItemMAPPER_H 
 #define PObjectGraphicsItemMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "pobjectgraphicsitem.h" 
#include "orm/persistence/pobject.h" 
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
 class PObjectGraphicsItemmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static PObjectGraphicsItemmapper* getInstance();
     ~PObjectGraphicsItemmapper();
     static PObjectGraphicsItem* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<PObjectGraphicsItem*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

PObject * findObject(int pri_id);

protected:
     PObjectGraphicsItemmapper();
 
 private:
    static PObjectGraphicsItemmapper* instance;
 

   string *columnTypes;
    string *columns;
   
 
 };
 
 #endif
 