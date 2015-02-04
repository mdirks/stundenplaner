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
 // Written on Mo. Feb 2 20:21:15 2015
// 
 #ifndef klasseMAPPER_H 
 #define klasseMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "klasse.h" 
#include "stunde.h" 
#include "schueler.h" 
#include "teilleistung.h" 
#include "stundenplantemplateeintrag.h" 
#include "datamodel/sitzplan.h" 
#include "datamodel/kursbuch.h" 
#include "datamodel/schuljahr.h" 
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
 #include "notizholdermapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class klassemapper : public notizholdermapper 
{
 public:
     static klassemapper* getInstance();
     ~klassemapper();
     static klasse* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<klasse*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<stunde*> * findStunden(int pri_id);
  list<schueler*> * findSchueler(int pri_id);
  list<teilleistung*> * findTeilleistungen(int pri_id);
  list<stundenplantemplateeintrag*> * findStundenplanTemplates(int pri_id);
sitzplan * findSitzplan(int pri_id);
kursbuch * findKursbuch(int pri_id);
schuljahr * findSchuljahr(int pri_id);

protected:
     klassemapper();
 
 private:
    static klassemapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<klasse, stunde> *asc_Stunden;
 Association<klasse, schueler> *asc_Schueler;
 Association<klasse, teilleistung> *asc_Teilleistungen;
 Association<klasse, stundenplantemplateeintrag> *asc_StundenplanTemplates;
  
 
 };
 
 #endif
 