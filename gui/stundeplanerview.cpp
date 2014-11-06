/***************************************************************************
                          stundeplanerview.cpp  -  description
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
#include <qprinter.h>
#include <qpainter.h>

// application specific includes
#include "stundeplanerview.h"
#include "stundeplanerdoc.h"
#include "stundeplaner.h"
#include "guirepository.h"
#include "guirepositoryimpl.h"
#include "../datamodel/opomapper.h"
#include "../datamodel/datamodelrepository.h"
//#include "gui/treetab.h"

#include "qtabwidget.h"

StundePlanerView::StundePlanerView(QWidget *parent, const char *name) : QWidget(parent)
{
  QBoxLayout * l = new QHBoxLayout( this );
  //l->setAutoAdd( TRUE );
  
  /*
  treeTab =  new TreeTab(this);
  treeTab->setMinimumWidth(200);
  treeTab->setMinimumHeight(400);
  l->addWidget(treeTab);
  
  tree = new doctree_stunden(this);
  //tree->setMinimumWidth(200);
  //tree->setMinimumHeight(400);
  //l->addWidget(tree);
  treeTab->mainTab->addTab(tree,"Stunden");
  tree->readStunden();
  
  listBoxOpos = new PObjectListBox(this);
  treeTab->mainTab->addTab(listBoxOpos, "Opos");
  list<opo*> *lopos = opomapper::getInstance()->find();
  listBoxOpos->addObjects((list<PObject*>*) lopos);
    */

  displayTab = new QTabWidget(this);
  l->addWidget(displayTab);
 
  workspace = new QWorkspace(this);
  displayTab->addTab(workspace,"Formulare");
  //setBackgroundMode(PaletteBase);
  GuiRepositoryImpl::getInstance()->setFormWorkspace(workspace);

   /*
  GraphicsView = new QGraphicsView(this);
  displayTab->addTab(GraphicsView,"Reihe");
  */
  

}

StundePlanerView::~StundePlanerView()
{
}

/*
doctree_stunden* StundePlanerView::getTree(){
 return this->tree;
}
*/


StundePlanerDoc *StundePlanerView::getDocument() const
{
  StundePlanerApp *theApp=(StundePlanerApp *) parentWidget();

  return theApp->getDocument();
}

void StundePlanerView::print(QPrinter *pPrinter)
{
  QPainter printpainter;
  printpainter.begin(pPrinter);
	
  // TODO: add your printing code here

  printpainter.end();
}
/** No descriptions */

//void StundePlanerView::addStunde(stunde *st){
//	GuiRepository::getInstance()->showFormForObject(st);
	/*
	form_stunde_rt_impl *form = new form_stunde_rt_impl(workspace);
	form->setStunde(st);
	form->show();
	qDebug("New form created");
	*/
//}

/*
void StundePlanerView::keyPressEvent( QKeyEvent *k )
{
	qDebug(QString("StundePlanerView: " )+ k->text());
}
*/
