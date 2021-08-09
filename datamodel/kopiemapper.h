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
 // Written on Sa. Mai 15 17:03:12 2021
// 
 #ifndef kopieMAPPER_H 
 #define kopieMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "kopie.h" 
#include "datamodel/lektuere.h" 
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
 #include "materialmapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class kopiemapper : public materialmapper 
{
 public:
     static kopiemapper* getInstance();
     ~kopiemapper();
     static kopie* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<kopie*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

lektuere * findLektuere(int pri_id);

protected:
     kopiemapper();
 
 private:
    static kopiemapper* instance;
 

   string *columnTypes;
    string *columns;
   
 
 };
 
 #endif
 