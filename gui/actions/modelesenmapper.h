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
 // Written on Tue Oct 21 23:54:59 2014
// 
 #ifndef ModeLesenMAPPER_H 
 #define ModeLesenMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "modelesen.h" 
#include "datamodel/lektuere.h" 
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
 #include "datamodel/notizholdermapper.h"

 /** 
 @author Marcus Dirks 
 */ 
 class ModeLesenmapper : public notizholdermapper 
{
 public:
     static ModeLesenmapper* getInstance();
     ~ModeLesenmapper();
     static ModeLesen* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<ModeLesen*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

  list<lektuere*> * findTexte(int pri_id);

protected:
     ModeLesenmapper();
 
 private:
    static ModeLesenmapper* instance;
 

   string *columnTypes;
    string *columns;
  Association<ModeLesen, lektuere> *asc_Texte;
  
 
 };
 
 #endif
 