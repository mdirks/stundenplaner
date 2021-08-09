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
 #ifndef materialsatzMAPPER_H 
 #define materialsatzMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "materialsatz.h" 
#include "material.h" 
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
 class materialsatzmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static materialsatzmapper* getInstance();
     ~materialsatzmapper();
     static materialsatz* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<materialsatz*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<material*> * findMaterialien(int pri_id);
  list<material*> * findMaterialien(int pri_id,string prop,string value);

protected:
     materialsatzmapper();
 
 private:
    static materialsatzmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<materialsatz, material> *asc_Materialien;
  
 
 };
 
 #endif
 