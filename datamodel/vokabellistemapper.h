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
 #ifndef vokabellisteMAPPER_H 
 #define vokabellisteMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "vokabelliste.h" 
#include "vokabel.h" 
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
 class vokabellistemapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static vokabellistemapper* getInstance();
     ~vokabellistemapper();
     static vokabelliste* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<vokabelliste*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<vokabel*> * findVokabeln(int pri_id);
  list<vokabel*> * findVokabeln(int pri_id,string prop,string value);

protected:
     vokabellistemapper();
 
 private:
    static vokabellistemapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<vokabelliste, vokabel> *asc_Vokabeln;
  
 
 };
 
 #endif
 