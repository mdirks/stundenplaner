#ifndef STUNDENPLANERMAINWINDOW_H
#define STUNDENPLANERMAINWINDOW_H

#include <QMainWindow>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// include files for Qt
#include "qprocess.h"
// include files for KDE
#include <QApplication>
//#include <kmainwindow.h>
//#include <kaccel.h>
#include <QAction>
#include <QUrl>
//#include <kmdimainfrm.h>
//#include <KXmlGui/KXmlGuiWindow>
//#include <KRun>
#include <QMdiArea>
#include <QToolBar>
#include <QStackedWidget>
#include <QComboBox>
#include <QListWidget>
#include "mapviews/themamapview.h"
#include "base/myactionlist.h"
#include "guimode.h"
// forward declaration of the StundePlaner classes
class StundePlanerDoc;
class StundePlanerView;
class MyPane;
class MySideBar;

class StundenPlanerMainWindow : public QMainWindow
{
    Q_OBJECT
    
    friend class StundePlanerView;
  
public:
    explicit StundenPlanerMainWindow(QWidget *parent = nullptr);
    
    public:
      ~StundenPlanerMainWindow();
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
      MyActionList *actionCollection();
  
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
      void slotCheckDatamodel();
  
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
      //KConfig *config;
  
      StundePlanerView *view;
      StundePlanerDoc *doc;

      MyActionList *actionList;
  
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

/*
    friend class StundePlanerView;

    public:
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
      void slotCheckDatamodel();
      void slotCreateAppmodel();

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
      //KConfig *config;

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
      */
  };

 /*
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
*/



/*
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
*/


#endif // STUNDENPLANERMAINWINDOW_H
