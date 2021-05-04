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
 #ifndef stundenplaneintragMAPPER_H 
 #define stundenplaneintragMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/mapping/murl.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "stundenplaneintrag.h" 
#include "stundenbewertung.h" 
#include "fehlzeit.h" 
#include "datamodel/klasse.h" 
#include "datamodel/stunde.h" 
#include "datamodel/stundenplantemplateeintrag.h" 
#include "datamodel/krusbucheintrag.h" 
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
 class stundenplaneintragmapper : public notizholdermapper 
{
 public:
     static stundenplaneintragmapper* getInstance();
     ~stundenplaneintragmapper();
     static stundenplaneintrag* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<stundenplaneintrag*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<stundenbewertung*> * findBewertungen(int pri_id);
  list<stundenbewertung*> * findBewertungen(int pri_id,string prop,string value);
  list<fehlzeit*> * findFehlzeiten(int pri_id);
  list<fehlzeit*> * findFehlzeiten(int pri_id,string prop,string value);
klasse * findKlasse(int pri_id);
stunde * findStunde(int pri_id);
stundenplantemplateeintrag * findTemplate(int pri_id);
krusbucheintrag * findKursbuchEintrag(int pri_id);

protected:
     stundenplaneintragmapper();
 
 private:
    static stundenplaneintragmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<stundenplaneintrag, stundenbewertung> *asc_Bewertungen;
 Association<stundenplaneintrag, fehlzeit> *asc_Fehlzeiten;
  
 
 };
 
 #endif
 