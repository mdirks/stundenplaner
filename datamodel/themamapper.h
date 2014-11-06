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
 // Written on Thu Oct 23 20:53:55 2014
// 
 #ifndef themaMAPPER_H 
 #define themaMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "thema.h" 
#include "thema.h" 
#include "thema.h" 
#include "lernkarte.h" 
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
 #include "notizholdermapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class themamapper : public notizholdermapper 
{
 public:
     static themamapper* getInstance();
     ~themamapper();
     static thema* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<thema*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<thema*> * findRelated(int pri_id);
  list<thema*> * findSub(int pri_id);
  list<lernkarte*> * findLernkarten(int pri_id);
lernkartensatz * findLernkartensatz(int pri_id);

protected:
     themamapper();
 
 private:
    static themamapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<thema, thema> *asc_Related;
 Association<thema, thema> *asc_Sub;
 Association<thema, lernkarte> *asc_Lernkarten;
  
 
 };
 
 #endif
 