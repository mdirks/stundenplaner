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
 // Written on Fri Dec 5 20:09:53 2014
// 
 #ifndef SitzplanMapMAPPER_H 
 #define SitzplanMapMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "sitzplanmap.h" 
#include "pobjectgraphicsitem.h" 
#include "datamodel/sitzplan.h" 
#include "datamodel/teilleistung.h" 
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
 #include "genericmapmapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class SitzplanMapmapper : public GenericMapmapper 
{
 public:
     static SitzplanMapmapper* getInstance();
     ~SitzplanMapmapper();
     static SitzplanMap* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<SitzplanMap*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<PObjectGraphicsItem*> * findGraphicsItems(int pri_id);
sitzplan * findSitzplan(int pri_id);
teilleistung * findActiveTeilleistung(int pri_id);

protected:
     SitzplanMapmapper();
 
 private:
    static SitzplanMapmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<SitzplanMap, PObjectGraphicsItem> *asc_GraphicsItems;
  
 
 };
 
 #endif
 