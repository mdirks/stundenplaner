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
 #ifndef stundenplanMAPPER_H 
 #define stundenplanMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "stundenplan.h" 
#include "stundenplantemplateeintrag.h" 
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
 class stundenplanmapper : public notizholdermapper 
{
 public:
     static stundenplanmapper* getInstance();
     ~stundenplanmapper();
     static stundenplan* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<stundenplan*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<stundenplantemplateeintrag*> * findTemplateEintraege(int pri_id);

protected:
     stundenplanmapper();
 
 private:
    static stundenplanmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<stundenplan, stundenplantemplateeintrag> *asc_TemplateEintraege;
  
 
 };
 
 #endif
 