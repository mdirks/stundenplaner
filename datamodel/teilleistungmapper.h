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
 // Written on Mo. März 15 13:58:08 2021
// 
 #ifndef teilleistungMAPPER_H 
 #define teilleistungMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "teilleistung.h" 
#include "note.h" 
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
 class teilleistungmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static teilleistungmapper* getInstance();
     ~teilleistungmapper();
     static teilleistung* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<teilleistung*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<note*> * findNoten(int pri_id);
  list<note*> * findNoten(int pri_id,string prop,string value);
klasse * findKlasse(int pri_id);

protected:
     teilleistungmapper();
 
 private:
    static teilleistungmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<teilleistung, note> *asc_Noten;
  
 
 };
 
 #endif
 