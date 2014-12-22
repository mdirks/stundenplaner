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
 // Written on Fri Nov 7 15:38:32 2014
// 
 #ifndef schuelerMAPPER_H 
 #define schuelerMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "schueler.h" 
#include "note.h" 
#include "fehlzeit.h" 
#include "stundenbewertung.h" 
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
 #include "notizholdermapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class schuelermapper : public notizholdermapper 
{
 public:
     static schuelermapper* getInstance();
     ~schuelermapper();
     static schueler* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<schueler*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<note*> * findNoten(int pri_id);
  list<fehlzeit*> * findFehlzeiten(int pri_id);
  list<stundenbewertung*> * findStundenbewertungen(int pri_id);
klasse * findKlasse(int pri_id);

protected:
     schuelermapper();
 
 private:
    static schuelermapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<schueler, note> *asc_Noten;
 Association<schueler, fehlzeit> *asc_Fehlzeiten;
 Association<schueler, stundenbewertung> *asc_Stundenbewertungen;
  
 
 };
 
 #endif
 