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
 // Written on Mo. Jun 22 20:24:34 2015
// 
 #ifndef notizholderMAPPER_H 
 #define notizholderMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "notizholder.h" 
#include "notiz.h" 
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
 class notizholdermapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static notizholdermapper* getInstance();
     ~notizholdermapper();
     static notizholder* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<notizholder*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<notiz*> * findNotizen(int pri_id);
  list<notiz*> * findNotizen(int pri_id,string prop,string value);
  list<material*> * findMaterialien(int pri_id);
  list<material*> * findMaterialien(int pri_id,string prop,string value);

protected:
     notizholdermapper();
 
 private:
    static notizholdermapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<notizholder, notiz> *asc_Notizen;
 Association<notizholder, material> *asc_Materialien;
  
 
 };
 
 #endif
 