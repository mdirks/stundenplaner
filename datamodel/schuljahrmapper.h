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
 #ifndef schuljahrMAPPER_H 
 #define schuljahrMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "schuljahr.h" 
#include "klasse.h" 
#include "ferien.h" 
#include "datamodel/stundenplan.h" 
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
 class schuljahrmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static schuljahrmapper* getInstance();
     ~schuljahrmapper();
     static schuljahr* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<schuljahr*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<klasse*> * findKlassen(int pri_id);
  list<ferien*> * findFerien(int pri_id);
stundenplan * findStundenplana(int pri_id);

protected:
     schuljahrmapper();
 
 private:
    static schuljahrmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<schuljahr, klasse> *asc_Klassen;
 Association<schuljahr, ferien> *asc_Ferien;
  
 
 };
 
 #endif
 