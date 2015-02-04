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
 #ifndef stundenbewertungMAPPER_H 
 #define stundenbewertungMAPPER_H 
 
 #include "orm/persistence/pobject.h" 
 #include "orm/mapping/mappedobject.h" 
#include "orm/mapping/association.h" 
#include "orm/persistence/persistenceclass.h" 
 #include "stundenbewertung.h" 
#include "datamodel/stundenplaneintrag.h" 
#include "datamodel/schueler.h" 
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
 class stundenbewertungmapper : public AbstractMapper, public RepositoryEnabled
{
 public:
     static stundenbewertungmapper* getInstance();
     ~stundenbewertungmapper();
     static stundenbewertung* create();

     string getTableName();
     string getClassName();
     string* getColumnTypes();
     string* getColumns();
     string* getValues(PObject* realSubject);
     int getColumnCount();
     void save();
     void save(PObject *realSubject);
     PObject* createNewObject();
     list<stundenbewertung*>* find();
    void init(PObject* o, Variant* res);
    RepositoryEntry *getRepositoryEntry();

stundenplaneintrag * findStundenplaneintrag(int pri_id);
schueler * findSchueler(int pri_id);

protected:
     stundenbewertungmapper();
 
 private:
    static stundenbewertungmapper* instance;
 

   string *columnTypes;
    string *columns;
   
 
 };
 
 #endif
 