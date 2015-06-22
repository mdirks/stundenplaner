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
 // Written on Mo. Jun 22 20:23:46 2015
// 
 #ifndef SStundenplanMAPPER_H 
 #define SStundenplanMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "sstundenplan.h" 
#include "datamodel/stundenplantemplateeintrag.h" 
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
 class SStundenplanmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static SStundenplanmapper* getInstance();
     ~SStundenplanmapper();
     static SStundenplan* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<SStundenplan*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<stundenplantemplateeintrag*> * findTemplateEintraege(int pri_id);
  list<stundenplantemplateeintrag*> * findTemplateEintraege(int pri_id,string prop,string value);

protected:
     SStundenplanmapper();
 
 private:
    static SStundenplanmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<SStundenplan, stundenplantemplateeintrag> *asc_TemplateEintraege;
  
 
 };
 
 #endif
 