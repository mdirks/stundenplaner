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
 // Written on Fr. März 5 14:14:42 2021
// 
 #ifndef vokabelMAPPER_H 
 #define vokabelMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "vokabel.h" 
#include "bspsatz.h" 
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
 class vokabelmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static vokabelmapper* getInstance();
     ~vokabelmapper();
     static vokabel* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<vokabel*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<bspsatz*> * findBeispiele(int pri_id);
  list<bspsatz*> * findBeispiele(int pri_id,string prop,string value);

protected:
     vokabelmapper();
 
 private:
    static vokabelmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<vokabel, bspsatz> *asc_Beispiele;
  
 
 };
 
 #endif
 