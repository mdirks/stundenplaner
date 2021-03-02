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
 // Written on Di. Feb. 23 18:53:05 2021
// 
 #ifndef bookmarkMAPPER_H 
 #define bookmarkMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "bookmark.h" 
#include "orm/transactions/transactionobject.h" 
#include "orm/transactions/transactionobject.h" 
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
 class bookmarkmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static bookmarkmapper* getInstance();
     ~bookmarkmapper();
     static bookmark* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<bookmark*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

TransactionObject * findZiel(int pri_id);
TransactionObject * findVerweis(int pri_id);

protected:
     bookmarkmapper();
 
 private:
    static bookmarkmapper* instance;
 

   string *columnTypes;
    string *columns;
   
 
 };
 
 #endif
 