//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "notizholder.h"
#include "notizholdermapper.h"

notizholder::notizholder()
{
	setMapper( notizholdermapper::getInstance() );
	list_notizen = 0;
        list_materialien = 0;
        list_bookmarks = 0;
}


notizholder::~notizholder()
{
}


list<notiz*>* notizholder::getNotizen()
{
    if(list_notizen == 0){
	list_notizen = notizholdermapper::getInstance()->findNotizen( getID() );
   }

   return list_notizen;
}


void notizholder::addToNotizen(notiz *n)
{
    getNotizen()->push_back(n);
}


void notizholder::deleteFromNotizen(notiz *n)
{
    getNotizen()->remove(n);
}

list<bookmark*>* notizholder::getBookmarks()
{
    if(list_bookmarks == 0){
    list_bookmarks = notizholdermapper::getInstance()->findBookmarks( getID() );
   }

   return list_bookmarks;
}


void notizholder::addToBookmarks(bookmark *b)
{
    getBookmarks()->push_back(b);
}


void notizholder::deleteFromBookmarks(bookmark *b)
{
    getBookmarks()->remove(b);
}

/*!
    \fn notizholder::getMaterialien()
 */
list<material*>* notizholder::getMaterialien()
{
    if(list_materialien == 0){
	list_materialien = notizholdermapper::getInstance()->findMaterialien( getID() );
   }

   if(list_materialien == 0){
    qDebug() << "!!! Failed to get Materialien from Mapper !!!!";
   }
   return list_materialien;
}


/*!
    \fn notizholder::addToMaterialien(notiz *n)
 */
void notizholder::addToMaterialien(material *m)
{
    	if(getMaterialien()){
		getMaterialien()->push_back(m);
	} else {
        qDebug() << "!!!! could not get the materialien list";
	}
}


/*!
    \fn notizholder::deleteFromMaterialien(notiz *n)
 */
void notizholder::deleteFromMaterialien(material *m)
{
    getMaterialien()->remove(m);
}
