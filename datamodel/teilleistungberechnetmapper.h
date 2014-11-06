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
 // Written on Thu Oct 23 20:53:55 2014
// 
 #ifndef teilleistungberechnetMAPPER_H 
 #define teilleistungberechnetMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "teilleistungberechnet.h" 
#include "teilleistung.h" 
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
 #include "teilleistungmapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class teilleistungberechnetmapper : public teilleistungmapper 
{
 public:
     static teilleistungberechnetmapper* getInstance();
     ~teilleistungberechnetmapper();
     static teilleistungberechnet* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<teilleistungberechnet*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<teilleistung*> * findTeilleistungen(int pri_id);
klasse * findKlasse(int pri_id);

protected:
     teilleistungberechnetmapper();
 
 private:
    static teilleistungberechnetmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<teilleistungberechnet, teilleistung> *asc_Teilleistungen;
  
 
 };
 
 #endif
 