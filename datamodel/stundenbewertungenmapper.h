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
 // Written on Do Jun 30 16:19:55 2011
// 
 #ifndef stundenbewertungenMAPPER_H 
 #define stundenbewertungenMAPPER_H 
 
 #include "orm/persistence/pobject.h"
 #include "orm/mapping/mappedobject.h"
#include "orm/mapping/association.h"
#include "orm/persistence/persistenceclass.h"
 #include "stundenbewertungen.h" 
#include "stundenbewertung.h" 
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
 class stundenbewertungenmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static stundenbewertungenmapper* getInstance();
     ~stundenbewertungenmapper();
     static stundenbewertungen* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<stundenbewertungen*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<stundenbewertung*> * findStundenbewertungen(int pri_id);

protected:
     stundenbewertungenmapper();
 
 private:
    static stundenbewertungenmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<stundenbewertungen, stundenbewertung> *asc_Stundenbewertungen;
  
 
 };
 
 #endif
 
