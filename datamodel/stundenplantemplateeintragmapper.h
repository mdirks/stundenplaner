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
 #ifndef stundenplantemplateeintragMAPPER_H 
 #define stundenplantemplateeintragMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "stundenplantemplateeintrag.h" 
#include "stundenplaneintrag.h" 
#include "reihe.h" 
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
 class stundenplantemplateeintragmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static stundenplantemplateeintragmapper* getInstance();
     ~stundenplantemplateeintragmapper();
     static stundenplantemplateeintrag* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<stundenplantemplateeintrag*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<stundenplaneintrag*> * findEintraege(int pri_id);
  list<reihe*> * findReihen(int pri_id);
klasse * findKlasse(int pri_id);

protected:
     stundenplantemplateeintragmapper();
 
 private:
    static stundenplantemplateeintragmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<stundenplantemplateeintrag, stundenplaneintrag> *asc_Eintraege;
 Association<stundenplantemplateeintrag, reihe> *asc_Reihen;
  
 
 };
 
 #endif
 