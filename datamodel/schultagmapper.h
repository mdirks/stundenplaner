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
 // Written on So. Jul 5 14:38:39 2015
// 
 #ifndef schultagMAPPER_H 
 #define schultagMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "schultag.h" 
#include "stundenplaneintrag.h" 
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
 class schultagmapper : public notizholdermapper 
{
 public:
     static schultagmapper* getInstance();
     ~schultagmapper();
     static schultag* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<schultag*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<stundenplaneintrag*> * findEintraege(int pri_id);
  list<stundenplaneintrag*> * findEintraege(int pri_id,string prop,string value);

protected:
     schultagmapper();
 
 private:
    static schultagmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<schultag, stundenplaneintrag> *asc_Eintraege;
  
 
 };
 
 #endif
 