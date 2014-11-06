/***************************************************************************
                          stundeplanerview.h  -  description
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

#ifndef STUNDEPLANERVIEW_H
#define STUNDEPLANERVIEW_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif 

// include files for Qt
#include <qwidget.h>
#include <qworkspace.h>
#include <qlayout.h>
#include <qtabwidget.h>
#include <QGraphicsScene>

//#include "form_stunde_rt_impl.h"
//#include "doctree_stunden.h"
//#include "treetab.h"
//#include "pobjectlistbox.h"


class StundePlanerDoc;


class StundePlanerView : public QWidget
{
  Q_OBJECT
  public:
    StundePlanerView(QWidget *parent = 0, const char *name=0);
    ~StundePlanerView();

    StundePlanerDoc *getDocument() const;

    void print(QPrinter *pPrinter);
// void addStunde(stunde *st);

   //void keyPressEvent( QKeyEvent *k ) ;
   //doctree_stunden* getTree();

	
  private:
  QWorkspace *workspace;
  //form_stunde_rt_impl *form;
  //doctree_stunden *tree;
  //PObjectListBox *listBoxOpos;
  //TreeTab *treeTab;
  QTabWidget *displayTab;
	
protected:
    QGraphicsView *GraphicsView;
};

#endif // STUNDEPLANERVIEW_H
