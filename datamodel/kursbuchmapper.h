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
 #ifndef kursbuchMAPPER_H 
 #define kursbuchMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "kursbuch.h" 
#include "krusbucheintrag.h" 
#include "datamodel/klasse.h" 
#include "datamodel/teilleistung.h" 
#include "datamodel/teilleistung.h" 
#include "datamodel/teilleistung.h" 
#include "datamodel/teilleistung.h" 
#include "datamodel/teilleistung.h" 
#include "datamodel/teilleistung.h" 
#include "datamodel/teilleistung.h" 
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
 
 /** 
 @author Marcus Dirks 
 */ 
 class kursbuchmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static kursbuchmapper* getInstance();
     ~kursbuchmapper();
     static kursbuch* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<kursbuch*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<krusbucheintrag*> * findEintraege(int pri_id);
klasse * findKlasse(int pri_id);
teilleistung * findKlausur1a(int pri_id);
teilleistung * findKlausur1b(int pri_id);
teilleistung * findKlausur2a(int pri_id);
teilleistung * findKlausur2b(int pri_id);
teilleistung * findAt1(int pri_id);
teilleistung * findAt2(int pri_id);
teilleistung * findG1(int pri_id);
teilleistung * findG2(int pri_id);

protected:
     kursbuchmapper();
 
 private:
    static kursbuchmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<kursbuch, krusbucheintrag> *asc_Eintraege;
  
 
 };
 
 #endif
 