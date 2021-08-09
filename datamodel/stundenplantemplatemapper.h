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
 #ifndef stundenplantemplateMAPPER_H 
 #define stundenplantemplateMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "stundenplantemplate.h" 
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
 
 /** 
 @author Marcus Dirks 
 */ 
 class stundenplantemplatemapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static stundenplantemplatemapper* getInstance();
     ~stundenplantemplatemapper();
     static stundenplantemplate* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<stundenplantemplate*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<stundenplantemplateeintrag*> * findEintraege(int pri_id);
  list<stundenplantemplateeintrag*> * findEintraege(int pri_id,string prop,string value);

protected:
     stundenplantemplatemapper();
 
 private:
    static stundenplantemplatemapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<stundenplantemplate, stundenplantemplateeintrag> *asc_Eintraege;
  
 
 };
 
 #endif
 