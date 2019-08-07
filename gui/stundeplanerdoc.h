/***************************************************************************
                          stundeplanerdoc.h  -  description
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

#ifndef STUNDEPLANERDOC_H
#define STUNDEPLANERDOC_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif 

// include files for QT
#include <qobject.h>
#include <qstring.h>
#include <qlist.h>

// include files for KDE
//#include <kurl.h>

#include "../datamodel/stunde.h"

// forward declaration of the StundePlaner classes
class StundePlanerView;


class StundePlanerDoc : public QObject
{
  Q_OBJECT
  public:
    StundePlanerDoc(QWidget *parent, const char *name=0);
    ~StundePlanerDoc();

    void addView(StundePlanerView *view);
    void removeView(StundePlanerView *view);
    void setModified(bool _m=true){ modified=_m; };
    bool isModified(){ return modified; };
    bool saveModified();	
    void deleteContents();
    bool newDocument();
    void closeDocument();
    bool openDocument(const QUrl& url, const char *format=0);
    bool saveDocument(const QUrl& url, const char *format=0);
    void setURL(const QUrl& url);
	
  public slots:
    /** calls repaint() on all views connected to the document object and is called by the view by which the document has been changed.
     * As this view normally repaints itself, it is excluded from the paintEvent.
     */
    void slotUpdateAllViews(StundePlanerView *sender);
 	
  public:	
    /** the list of the views currently connected to the document */
    static QList<StundePlanerView*> *pViewList;
    static QList<stunde> *stundeList;

  private:
    /** the modified flag of the current document */
    bool modified;
    QUrl doc_url;

};

#endif // STUNDEPLANERDOC_H
