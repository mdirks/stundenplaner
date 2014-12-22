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
 #ifndef fehlzeitMAPPER_H 
 #define fehlzeitMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "fehlzeit.h" 
#include "datamodel/schueler.h" 
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
 #include "notizholdermapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class fehlzeitmapper : public notizholdermapper 
{
 public:
     static fehlzeitmapper* getInstance();
     ~fehlzeitmapper();
     static fehlzeit* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<fehlzeit*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

schueler * findSchueler(int pri_id);
stundenplaneintrag * findStundenplaneintrag(int pri_id);

protected:
     fehlzeitmapper();
 
 private:
    static fehlzeitmapper* instance;
 

   string *columnTypes;
    string *columns;
   
 
 };
 
 #endif
 