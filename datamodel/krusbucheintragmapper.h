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
 #ifndef krusbucheintragMAPPER_H 
 #define krusbucheintragMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "krusbucheintrag.h" 
#include "datamodel/kursbuch.h" 
#include "datamodel/stundenplaneintrag.h" 
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
 class krusbucheintragmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static krusbucheintragmapper* getInstance();
     ~krusbucheintragmapper();
     static krusbucheintrag* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<krusbucheintrag*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

kursbuch * findKursbuch(int pri_id);
stundenplaneintrag * findStundenplanEintrag(int pri_id);

protected:
     krusbucheintragmapper();
 
 private:
    static krusbucheintragmapper* instance;
 

   string *columnTypes;
    string *columns;
   
 
 };
 
 #endif
 