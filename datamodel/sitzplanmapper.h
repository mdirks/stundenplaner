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
 // Written on Mi. Jan. 27 10:46:20 2021
// 
 #ifndef sitzplanMAPPER_H 
 #define sitzplanMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "sitzplan.h" 
#include "platz.h" 
#include "datamodel/klasse.h" 
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
 class sitzplanmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static sitzplanmapper* getInstance();
     ~sitzplanmapper();
     static sitzplan* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<sitzplan*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<platz*> * findPlaetze(int pri_id);
  list<platz*> * findPlaetze(int pri_id,string prop,string value);
klasse * findKlasse(int pri_id);

protected:
     sitzplanmapper();
 
 private:
    static sitzplanmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<sitzplan, platz> *asc_Plaetze;
  
 
 };
 
 #endif
 