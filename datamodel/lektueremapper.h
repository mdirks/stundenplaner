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
 // Written on Sa. Feb 7 17:49:10 2015
// 
 #ifndef lektuereMAPPER_H 
 #define lektuereMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "lektuere.h" 
#include "lektuerenotiz.h" 
#include "datamodel/lernkartensatz.h" 
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
 class lektueremapper : public materialmapper 
{
 public:
     static lektueremapper* getInstance();
     ~lektueremapper();
     static lektuere* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<lektuere*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<lektuerenotiz*> * findNotizen(int pri_id);
lernkartensatz * findLernkartensatz(int pri_id);

protected:
     lektueremapper();
 
 private:
    static lektueremapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<lektuere, lektuerenotiz> *asc_Notizen;
  
 
 };
 
 #endif
 