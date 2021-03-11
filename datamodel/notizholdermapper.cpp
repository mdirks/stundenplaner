// 
 // C++ Implementation: notizholdermapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "notizholdermapper.h"
 #include "services/utils/utils.h"
 #include "notizholder.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 notizholdermapper* notizholdermapper::instance=0;
 
 notizholdermapper* notizholdermapper::getInstance()
 {
 	if(!instance){
 		instance=new notizholdermapper();
 	}
 	return instance;
 }


 notizholdermapper::notizholdermapper()
  {
 	version = "0.5";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Notizen = new Association<notizholder, notiz>("notizholder_notiz","nh_id","notiz_id","notiz", &notizholder::addToNotizen, &notizholder::deleteFromNotizen);
mapAssociations["Notizen"] = asc_Notizen;
registerAssociation( asc_Notizen);
asc_Materialien = new Association<notizholder, material>("notizholder_material","nh_id","material_id","material", &notizholder::addToMaterialien, &notizholder::deleteFromMaterialien);
mapAssociations["Materialien"] = asc_Materialien;
registerAssociation( asc_Materialien);
asc_Bookmarks = new Association<notizholder, bookmark>("notizholder_bookmark","nh_id","bookmark_id","bookmark", &notizholder::addToBookmarks, &notizholder::deleteFromBookmarks);
mapAssociations["Bookmarks"] = asc_Bookmarks;
registerAssociation( asc_Bookmarks);
}


notizholdermapper::~notizholdermapper(){}


 PObject* notizholdermapper::createNewObject()
 {
     return new notizholder();
 }


 notizholder* notizholdermapper::create()
 {
     return  (notizholder*) AbstractMapper::create( notizholdermapper::getInstance() );
 }


 string notizholdermapper::getTableName()
 {
     return string("notizholder");
 }
 
 string notizholdermapper::getClassName()
 {
 	return string("notizholder");
 }
 
 string* notizholdermapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* notizholdermapper::getColumns()
 {
 	return columns;
 }
 
 int notizholdermapper::getColumnCount()
 {
     return 0;
 }


 string* notizholdermapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	notizholder *o = (notizholder*) realSubject;
return values;
 }


 void notizholdermapper::save(){
qWarning("notizholder: save() not implemented");
}

void notizholdermapper::save(PObject *realSubject)
{
 	notizholder *o = (notizholder*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Notizen -> save(realSubject, o->getNotizen() );

	asc_Materialien -> save(realSubject, o->getMaterialien() );

	asc_Bookmarks -> save(realSubject, o->getBookmarks() );

}


void notizholdermapper::init(PObject* inito, Variant *res)
 {
 	notizholder *o = (notizholder*) inito;
	inito->init();
}


 list<notizholder *>*notizholdermapper::find() 
 {
 	return (list <notizholder*>*) Database::getInstance()->getAll(this); 
}


list<notiz*> * notizholdermapper::findNotizen(int pri_id) 
 { 
 	return asc_Notizen ->  findAssociates( pri_id );
     }


list<notiz*> * notizholdermapper::findNotizen(int pri_id,string prop,string value) 
         { 
             return asc_Notizen ->  findAssociates( pri_id,prop,value);
             }


list<material*> * notizholdermapper::findMaterialien(int pri_id) 
 { 
 	return asc_Materialien ->  findAssociates( pri_id );
     }


list<material*> * notizholdermapper::findMaterialien(int pri_id,string prop,string value) 
         { 
             return asc_Materialien ->  findAssociates( pri_id,prop,value);
             }


list<bookmark*> * notizholdermapper::findBookmarks(int pri_id) 
 { 
 	return asc_Bookmarks ->  findAssociates( pri_id );
     }


list<bookmark*> * notizholdermapper::findBookmarks(int pri_id,string prop,string value) 
         { 
             return asc_Bookmarks ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* notizholdermapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "notizholder" ); 
	entry->addProperty( new StringProperty<notizholder>("Name", "string", &notizholder::getName, &notizholder::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<notiz,notizholder>( "Notizen" , "notiz", &notizholder::getNotizen, &notizholder::addToNotizen, &notizholder::deleteFromNotizen  ) ); 
	entry->addProperty( new CollectionPropertyImpl<material,notizholder>( "Materialien" , "material", &notizholder::getMaterialien, &notizholder::addToMaterialien, &notizholder::deleteFromMaterialien  ) ); 
	entry->addProperty( new CollectionPropertyImpl<bookmark,notizholder>( "Bookmarks" , "bookmark", &notizholder::getBookmarks, &notizholder::addToBookmarks, &notizholder::deleteFromBookmarks  ) ); 
	return entry;
 }
