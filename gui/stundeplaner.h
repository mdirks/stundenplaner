/***************************************************************************
                          stundeplaner.h  -  description
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

#ifndef STUNDEPLANER_H
#define STUNDEPLANER_H
 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// include files for Qt
#include "qprocess.h"
// include files for KDE 
#include <QApplication>
#include <kmainwindow.h>
//#include <kaccel.h>
#include <QAction>
#include <QUrl>
//#include <kmdimainfrm.h>
#include <KXmlGuiWindow>
#include <QMdiArea>
#include <QToolBar>
#include <QStackedWidget>
#include <QComboBox>
#include <QListWidget>
#include <QMainWindow>

//#include "doctree_stunden.h"
//#include "pobjectlistbox.h"
#include "mapviews/themamapview.h"
#include "guimode.h"
// forward declaration of the StundePlaner classes
class StundePlanerDoc;
class StundePlanerView;
class MyPane;
class MySideBar;



class StundePlanerApp : /*public QMainWindow*/ public KXmlGuiWindow /* public KMdiMainFrm*/
{
  Q_OBJECT



  friend class StundePlanerView;

  public:
    StundePlanerApp(QWidget* parent=0, const char* name=0);
    ~StundePlanerApp();
    void openDocumentFile(const QUrl& url);
    StundePlanerDoc *getDocument() const; 	
    //void addSubWindow(QWidget *w, bool top=true);
    void addDockWindow(QWidget *w, QString name,Qt::DockWidgetArea area = Qt::RightDockWidgetArea);
    QStackedWidget* getCentralWidget();

  protected:
    void saveOptions();
    void readOptions();
    void initActions();
    void initStatusBar();
    void initDocument();
    void initView();
    virtual bool queryClose();
    virtual bool queryExit();
    //virtual void saveProperties(KConfig *_cfg);
    //virtual void readProperties(KConfig *_cfg);

    void dumpDatabase(QString fileName);

private:
	int getNewIconViewNumber();


  public slots:
    void slotChangeSchuljahr();
    void slotShowStundenplan();
    void slotChangeDatabase();
    void slotDumpDatabase();
    void slotReadDatabase();
    void slotNewObjectIconView();
    void slotShowKalender();
    void slotDatabaseReadFinished();
    void slotAddFehlzeitmeldung();
    void slotAddStundenplaneintrag();

    void slotFileNewWindow();
    void slotFileNew();
    void slotFileOpen();
    void slotFileOpenRecent(const QUrl& url);
    void slotFileSave();
    void slotFileSaveAs();
    void slotFileClose();
    void slotFilePrint();
    void slotFileQuit();
    void slotEditCut();
    void slotEditCopy();
    void slotEditPaste();
    void slotViewToolBar();
    void slotViewStatusBar();
    void slotStatusMsg(const QString &text);


    void keyPressEvent( QKeyEvent *k ) ;

  private:
    KConfig *config;

    StundePlanerView *view;
    StundePlanerDoc *doc;

    // QAction pointers to enable/disable actions
    QAction* changeSchuljahrAction;
    QAction* changeDatabaseAction;
    QAction* newObjectIconViewAction;
    QAction* addStundenplaneintragAction;


    QAction* fileNewWindow;
    QAction* fileNew;
    QAction* fileOpen;
    //KRecentFilesAction* fileOpenRecent;
    QAction* fileSave;
    QAction* fileSaveAs;
    QAction* fileClose;
    QAction* filePrint;
    QAction* fileQuit;
    QAction* editCut;
    QAction* editCopy;
    QAction* editPaste;
    QAction* viewToolBar;
    QAction* viewStatusBar;
    
    //doctree_stunden *tree;
    //PObjectListBox *listBoxOpos;
    //PObjectListBox *listBoxStunden;
    
    ThemaMapView *mapView;
	int iv_nr;
	QProcess *p;
    //MyPane *mdiArea, *mdiAreaBottom;
    //QMdiArea *mdiAreaBottom;
    //QToolBar *modeBar;
    //MySideBar *sideBar;
    QStackedWidget *centralWidget;
    QToolBar *rightToolBar;
};
 

class MySideBar : public QListWidget
{
Q_OBJECT

public:
    MySideBar(QWidget *parent);

public slots:
    void activateItem(QListWidgetItem *item);

private:
    GuiMode *activeMode;
};


#endif // STUNDEPLANER_H
