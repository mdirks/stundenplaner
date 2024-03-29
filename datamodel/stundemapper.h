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
 #ifndef stundeMAPPER_H 
 #define stundeMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "stunde.h" 
#include "opo.h" 
#include "material.h" 
#include "datamodel/thema.h" 
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
 class stundemapper : public notizholdermapper 
{
 public:
     static stundemapper* getInstance();
     ~stundemapper();
     static stunde* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<stunde*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<opo*> * findOpos(int pri_id);
  list<opo*> * findOpos(int pri_id,string prop,string value);
  list<material*> * findMaterialien(int pri_id);
  list<material*> * findMaterialien(int pri_id,string prop,string value);
thema * findThema(int pri_id);

protected:
     stundemapper();
 
 private:
    static stundemapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<stunde, opo> *asc_Opos;
 Association<stunde, material> *asc_Materialien;
  
 
 };
 
 #endif
 