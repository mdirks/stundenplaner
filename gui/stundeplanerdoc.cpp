/***************************************************************************
                          stundeplanerdoc.cpp  -  description
                             -------------------
    begin                : Sam Feb 28 13:37:40 CET 2004
    copyright            : (C) 2004 by Marcus Dirks
    email                : marcus.dirks@web.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// include files for Qt
#include <qdir.h>
#include <qwidget.h>
#include <QMessageBox>
// include files for KDE
//#include <klocale.h>

// application specific includes
#include "stundeplanerdoc.h"
#include "stundeplanerview.h"
//#include "./persistence/database.h"
#include "../datamodel/stundemapper.h"

QList<StundePlanerView*> *StundePlanerDoc::pViewList = 0L;
QList<stunde> *StundePlanerDoc::stundeList = 0L;

StundePlanerDoc::StundePlanerDoc(QWidget *parent, const char *name) : QObject(parent)
{
  if(!pViewList)
  {
    pViewList = new QList<StundePlanerView*>();
  }
  
  if(!stundeList){
    stundeList = new QList<stunde>();
  }


  //pViewList->setAutoDelete(true);
  //stundeList->setAutoDelete(true);

}

StundePlanerDoc::~StundePlanerDoc()
{
}

/**
	Adds a view to the window
*/
void StundePlanerDoc::addView(StundePlanerView *view)
{
   /*
   stunde *st;
   for(st=stundeList->first();st!=0;st=stundeList->next()){
     	view->addStunde(st);
	}
    */
  pViewList->append(view);

}

void StundePlanerDoc::removeView(StundePlanerView *view)
{
  pViewList->removeOne(view);
}
void StundePlanerDoc::setURL(const QUrl &url)
{
  doc_url=url;
}

/*
const QUrl& StundePlanerDoc::URL() const
{
  return doc_url;
}
*/

void StundePlanerDoc::slotUpdateAllViews(StundePlanerView *sender)
{
  StundePlanerView *w;
  if(pViewList)
  {
      for(QList<StundePlanerView*>::iterator it=pViewList->begin(); it!=pViewList->end(); it++)
    {
          if((*it)!=sender)	(*it)->repaint();

    }
  }

}

bool StundePlanerDoc::saveModified()
{
  bool completed=true;

  if(modified)
  {
    QMessageBox::warning(0,"Todo","StundePlanerDoc::saveModified() : Not implemented");
  }

  return completed;
}

void StundePlanerDoc::closeDocument()
{
  deleteContents();
}

bool StundePlanerDoc::newDocument()
{
  QMessageBox::warning(0,"Todo","Not implemented");
  /*
  stunde *st = (stunde*) stundemapper::getInstance()->create();
  if(!st){
  	qWarning("Failed to create new stunde");
	return false;
  }

  stundeList->append(st);

  StundePlanerView *w;
  if(pViewList)
  {
    for(w=pViewList->first(); w!=0; w=pViewList->next())
    {
	w->addStunde(st);
	qDebug("added Stunde to view");
	//w->repaint();
    }
  }
  /////////////////////////////////////////////////
  modified=false;
  doc_url.setFileName(i18n("Untitled"));

  return true;
 */
}

bool StundePlanerDoc::openDocument(const QUrl& url, const char *format /*=0*/)
{
    qDebug() << "Warning: StundePlanerDoc::openDocument not implemented";
  /*
  QString tmpfile;
  KIO::NetAccess::download( url, tmpfile );
  /////////////////////////////////////////////////
  // TODO: Add your document opening code here
  /////////////////////////////////////////////////

  KIO::NetAccess::removeTempFile( tmpfile );

  modified=false;
  return true;
  */
    return false;
}

bool StundePlanerDoc::saveDocument(const QUrl& url, const char *format /*=0*/)
{
  /////////////////////////////////////////////////
  // TODO: Add your document saving code here
  /////////////////////////////////////////////////

  modified=false;
  return true;
}

void StundePlanerDoc::deleteContents()
{
  /////////////////////////////////////////////////
  // TODO: Add implementation to delete the document contents
  /////////////////////////////////////////////////

}
