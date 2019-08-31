/***************************************************************************
                          stundeplaner.cpp  -  description
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

// include files for QT
#include <QDockWidget>
#include <QDebug>
#include <QList>
#include <QKeyEvent>
#include <qdir.h>
#include <QPrinter>
#include <qpainter.h>
#include <qprogressdialog.h>
#include <qprocess.h>
//#include <QStackedWidget>
#include <QStatusBar>


// include files for KDE
//#include <QActionCollection>
//#include <kcmdlineargs.h>
//#include <kaboutdata.h>
//#include <klocale.h>
//#include <kapp.h>
//#include <kiconloader.h>
//#include <kmessagebox.h>
//#include <kfiledialog.h>
//#include <kmenubar.h>
//#include <kstatusbar.h>
//#include <klocale.h>
//#include <kconfig.h>
//#include <kstdaction.h>
//#include <krun.h>
#include <qlayout.h>
//#include <kdockwidget.h>
//#include <kglobal.h>
//#include <kinputdialog.h>
#include <KXmlGui/KActionCollection>
#include <QInputDialog>
#include <QFileDialog>


// application specific includes
#include "stundeplaner.h"
#include "stundeplanerview.h"
#include "stundeplanerdoc.h"


#include "gui/guirepository.h"
#include "gui/base/guicontroler.h"
#include "gui/base/guiconfig.h"
#include "gui/dialogs/xmlimportdialog.h"
#include "gui/dialogs/xmlexportdialog.h"
//#include "gui/dialogs/fehlzeitdialog.h"
#include "gui/forms/pobjecticonview.h"
#include "gui/forms/pobjectdialog.h"
#include "services/skalender.h"
#include "services/sstundenplan.h"
#include "orm/transactions/transactions.h"
#include "gui/actions/guicreateaction.h"
#include "orm/mapping/mappingcontroler.h"
#include "datamodel/schuljahrmapper.h" 
#include "datamodel/fehlzeitmeldung.h"


#define ID_STATUS_MSG 1


/*
static const char *description =
	I18N_NOOP("StundePlaner");
// INSERT A DESCRIPTION FOR YOUR APPLICATION HERE
	
	
static KCmdLineOptions options[] =
{
  { "+[File]", I18N_NOOP("file to open"), 0 },
  { 0, 0, 0 }
  // INSERT YOUR COMMANDLINE OPTIONS HERE
};
*/

StundePlanerApp::StundePlanerApp(QWidget* , const char* name): KXmlGuiWindow() /*QMainWindow()*/
{
  initStatusBar();
  initActions();
  
  //setupGUI();
  setupGUI(Default,"/data3/mopp/dev/stundenplaner/gui/stundenplanerui.rc");
  qDebug() << QString("Build gui from local xml file %1").arg(localXMLFile());
  qDebug() << QString("Build gui from local xml file %1").arg(xmlFile());
  initDocument();
  initView();
  


  readOptions();
  //createTaskBar();

  fileSave->setEnabled(true);
  fileSaveAs->setEnabled(true);
  filePrint->setEnabled(false);
  editCut->setEnabled(false);
  editCopy->setEnabled(false);
  editPaste->setEnabled(false);

  GuiRepository::getInstance()->setMainFrame(this);

}

StundePlanerApp::~StundePlanerApp()
{

}

void StundePlanerApp::initActions()
{
  QAction *action;


  changeSchuljahrAction = actionCollection()->addAction("schuljahr_waehlen", this, SLOT(slotChangeSchuljahr()));
  changeSchuljahrAction->setIcon(GuiConfig::getInstance()->getIcon("action_schuljahr"));
  changeSchuljahrAction->setText("Schuljahr wählen");

  changeDatabaseAction = actionCollection()->addAction("change_database", this, SLOT(slotChangeDatabase()));
  changeDatabaseAction->setIcon(GuiConfig::getInstance()->getIcon("action_database"));
  changeDatabaseAction->setText("Datenbank wechseln");

  addStundenplaneintragAction = actionCollection()->addAction("add_stundenplaneintrag", this,
                                                                 SLOT(slotAddStundenplaneintrag()));
  addStundenplaneintragAction->setIcon(GuiConfig::getInstance()->getIcon("add_stundenplaneintrag"));
  addStundenplaneintragAction->setText("Neuer Stundenplaneintrag");

  action=actionCollection()->addAction("fehlzeitmeldung", this, SLOT(slotAddFehlzeitmeldung()));
  action->setIcon(GuiConfig::getInstance()->getIcon("fehlzeitmeldung"));
  action->setText("Fehlzeitmeldung");

  action=actionCollection()->addAction("dump_database", this, SLOT(slotDumpDatabase()));
  action->setIcon(GuiConfig::getInstance()->getIcon("DumpDB"));
  action->setText("DB sichern");

  action=actionCollection()->addAction("read_database", this, SLOT(slotReadDatabase()));
  action->setIcon(GuiConfig::getInstance()->getIcon("ReadDB"));
  action->setText("DB lesen");

  action= actionCollection()->addAction("add_objectview", this, SLOT(slotNewObjectIconView()));
  action->setIcon(GuiConfig::getInstance()->getIcon("objectview"));
  action->setText("Objektbrowser");

  action= actionCollection()->addAction("check_dm", this, SLOT(slotCheckDatamodel()));
  action->setIcon(GuiConfig::getInstance()->getIcon("checkdm"));
  action->setText("Check Datamodel");


  actionCollection()->addAction("kalender",  this, SLOT(slotShowKalender()));
  actionCollection()->addAction("stundenplan",  this, SLOT(slotShowStundenplan()));
  fileNewWindow = actionCollection()->addAction("new_window", this, SLOT(slotFileNewWindow()));
  fileNew = KStandardAction::openNew(GuiCreateAction::getInstance(), SLOT(createObject()), actionCollection());
  fileOpen = KStandardAction::open(this, SLOT(slotFileOpen()), actionCollection());
  //fileOpenRecent = KStandardAction::openRecent(this, SLOT(slotFileOpenRecent(const KURL&)), actionCollection());
  fileSave = KStandardAction::save(this, SLOT(slotFileSave()), actionCollection());
  fileSaveAs = KStandardAction::saveAs(this, SLOT(slotFileSaveAs()), actionCollection());
  fileClose = KStandardAction::close(this, SLOT(slotFileClose()), actionCollection());
  filePrint = KStandardAction::print(this, SLOT(slotFilePrint()), actionCollection());
  fileQuit = KStandardAction::quit(this, SLOT(slotFileQuit()), actionCollection());
  editCut = KStandardAction::cut(this, SLOT(slotEditCut()), actionCollection());
  editCopy = KStandardAction::copy(this, SLOT(slotEditCopy()), actionCollection());
  editPaste = KStandardAction::paste(this, SLOT(slotEditPaste()), actionCollection());

}


void StundePlanerApp::initStatusBar()
{
  //statusBar()->insertItem(i18n("Ready."), ID_STATUS_MSG);
}

void StundePlanerApp::initDocument()
{
  doc = new StundePlanerDoc(this);
 }

QStackedWidget* StundePlanerApp::getCentralWidget()
{
    return centralWidget;
}

void StundePlanerApp::initView()
{ 
  centralWidget = new QStackedWidget(this);
  setCentralWidget(centralWidget);
  //GuiRepository::getInstance()->setCentralWidget(centralWidget);

  //sideBar = new MySideBar(this);
  //addDockWindow(sideBar, "sidebar", Qt::LeftDockWidgetArea);


}





void StundePlanerApp::addDockWindow(QWidget *w, QString name, Qt::DockWidgetArea area)
{

    QDockWidget *dock = new QDockWidget(name,this);
    //dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(w);
    addDockWidget(area, dock);

}

void StundePlanerApp::openDocumentFile(const QUrl& url)
{
    qDebug()<<"Warning StundePlanerApp::openDocumentFile not implemented";
}


StundePlanerDoc *StundePlanerApp::getDocument() const
{
  return doc;
}

void StundePlanerApp::saveOptions()
{	
  qDebug() << "Warning: StundePlanerApp::saveOptions() not implemented" ;
  /*
  config->setGroup("General Options");
  config->writeEntry("Geometry", size());
  config->writeEntry("Show Toolbar", viewToolBar->isChecked());
  config->writeEntry("Show Statusbar",viewStatusBar->isChecked());
  config->writeEntry("ToolBarPos", (int) toolBar("mainToolBar")->barPos());
  fileOpenRecent->saveEntries(config,"Recent Files");
  */
}


void StundePlanerApp::readOptions()
{
  qDebug()<< "Warning: StundePlanerApp::readOptions() not implemented" ;
  /*
  config->setGroup("General Options");

  // bar status settings
  bool bViewToolbar = config->readBoolEntry("Show Toolbar", true);
  viewToolBar->setChecked(bViewToolbar);
  slotViewToolBar();

  bool bViewStatusbar = config->readBoolEntry("Show Statusbar", true);
  viewStatusBar->setChecked(bViewStatusbar);
  slotViewStatusBar();


  // bar position settings
  KToolBar::BarPosition toolBarPos;
  toolBarPos=(KToolBar::BarPosition) config->readNumEntry("ToolBarPos", KToolBar::Top);
  toolBar("mainToolBar")->setBarPos(toolBarPos);
	
  // initialize the recent file list
  fileOpenRecent->loadEntries(config,"Recent Files");

  QSize size=config->readSizeEntry("Geometry");
  if(!size.isEmpty())
  {
    resize(size);
  }
  */
}


/*
void StundePlanerApp::saveProperties(KConfig *_cfg)
{
  if(doc->URL().fileName()!=i18n("Untitled") && !doc->isModified())
  {
    // saving to tempfile not necessary

  }
  else
  {
    KURL url=doc->URL();	
    _cfg->writeEntry("filename", url.url());
    _cfg->writeEntry("modified", doc->isModified());
    QString tempname = kapp->tempSaveName(url.url());
    QString tempurl= KURL::encode_string(tempname);
    KURL _url(tempurl);
    doc->saveDocument(_url);
  }
}
*/


/*
void StundePlanerApp::readProperties(KConfig* _cfg)
{
  QString filename = _cfg->readEntry("filename", "");
  KURL url(filename);
  bool modified = _cfg->readBoolEntry("modified", false);
  if(modified)
  {
    bool canRecover;
    QString tempname = kapp->checkRecoverFile(filename, canRecover);
    KURL _url(tempname);
  	
    if(canRecover)
    {
      doc->openDocument(_url);
      doc->setModified();
      setCaption(_url.fileName(),true);
      QFile::remove(tempname);
    }
  }
  else
  {
    if(!filename.isEmpty())
    {
      doc->openDocument(url);
      setCaption(url.fileName(),false);
    }
  }
}		
*/

bool StundePlanerApp::queryClose()
{
  return doc->saveModified();
}

bool StundePlanerApp::queryExit()
{
  saveOptions();
  return true;
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////
void StundePlanerApp::slotAddStundenplaneintrag()
{
    GuiCreateAction::getInstance()->addStundenplaneintrag();
}

void StundePlanerApp::slotAddFehlzeitmeldung()
{
	/*
	fehlzeitmeldung *fzm = (fehlzeitmeldung*) GuiCreateAction::getInstance()->create("fehlzeitmeldung");
	GuiRepository::getInstance()->showDialogForObject(fzm);
	*/

    qDebug() << "Warning: StundePlanerApp::slotAddFehlzeitmeldung() not implemented";
    //FehlzeitDialog::createFehlzeitmeldung();
}

void StundePlanerApp::slotChangeSchuljahr()
{
	schuljahr *sj = (schuljahr*) PObjectDialog::choosePObject(schuljahrmapper::getInstance());
	if(sj){
		GuiConfig::getInstance()->setActiveSchuljahr(sj);
        SKalender::getInstance()->setActiveSchuljahr(sj);
		SStundenplan::setActiveStundenplan(sj->getStundenplana());
        qDebug() << QString("Schuljahr set to %1").arg(sj->getName().c_str());
	} else {
		qDebug("StundePlanerApp::slotChangeSchuljahr() : selection of schuljahr failed");
	}
}

void StundePlanerApp::slotShowStundenplan()
{
	GuiRepository::getInstance()->showFormForObject(SStundenplan::getInstance());
}
void StundePlanerApp::slotChangeDatabase()
{
    QString db_name = QInputDialog::getText(this,"Datenbank wechseln","Neue Datenbank",QLineEdit::Normal,Database::getDatabaseName());

	GuiRepository::getInstance()->closeGui();
    if(MappingControler::getInstance()->initNewDatabase(db_name.toStdString())){
		SStundenplan::getInstance()->close();
		SKalender::getInstance()->close;
		GuiConfig::getInstance()->setDatabaseName(db_name);
		
	} else {
		GuiRepository::getInstance()->showInfo("Ungueltige Datenbank",QString("Konnte Datenbank %1 nicht oeffnen").arg(db_name));
		
	}
	GuiRepository::getInstance()->reloadGui();
}


void StundePlanerApp::slotDumpDatabase()
{
    QString fileName = QFileDialog::getSaveFileName();
	dumpDatabase(fileName);
}

void StundePlanerApp::dumpDatabase(QString fileName)
{
    QString databasename = GuiConfig::getInstance()->getDatabaseName();
    QStringList args = databasename.split(":");
    QString dbName=args.at(0);
    QString com;
    if(args.size()>1){
        com = QString("mysqldump -h%1 -u%2 -p%3 %4 > %5").arg(args.at(1),args.at(2),args.at(3),dbName,fileName);
    } else {
        com = QString("mysqldump -user=root %1 > %2").arg(dbName).arg(fileName);
    }
    qDebug() << com;
    KRun::runCommand(com,this);
}

void StundePlanerApp::slotReadDatabase()
{
    QString fileName = QFileDialog::getOpenFileName();
    QString dbName = QInputDialog::getText(this,"Datenbank einlesen","Datenbankname",QLineEdit::Normal,Database::getDatabaseName());

	QString pstring = QString("mysql");
    QString astring = QString("--user=root  %1 < %2").arg(dbName).arg(fileName);
    qDebug() << QString("Creating process %1 with %2").arg(pstring).arg(astring);
	p = new QProcess(this);
	//p->addArgument(astring);
	
    QString program = "mysql";
    QStringList arguments;
    arguments << "--user=root"  << dbName << fileName;
    p->start(program,arguments);
    connect(p,SIGNAL(processExited()),this,SLOT(slotDatabaseReadFinished()));
    GuiConfig::getInstance()->setDatabaseName(dbName);
}

void StundePlanerApp::slotDatabaseReadFinished(){
    if(p && p->exitStatus() == QProcess::NormalExit){
		QString dbName = GuiConfig::getInstance()->getDatabaseName();
		GuiRepository::getInstance()->closeGui();
        if(MappingControler::getInstance()->initNewDatabase(dbName.toStdString())){
			SStundenplan::getInstance()->close();
            SKalender::getInstance()->close;
            //GuiConfig::getInstance()->setDatab<< "--password=duodisc"aseName(dbName);
			GuiRepository::getInstance()->showInfo("Datenbank gelesen",QString("Datenbank %1 wurde geoeffnet").arg(dbName));
		} else {
			GuiRepository::getInstance()->showInfo("Ungueltige Datenbank",QString("Konnte Datenbank %1 nicht oeffnen").arg(dbName));
			
		}
		GuiRepository::getInstance()->reloadGui();
		p=0;
	} else {
		GuiRepository::getInstance()->showInfo("Einlesen fehlgeschlagen",QString("Konnte Datenbankfile  nicht oeffnen"));
	}
}


void StundePlanerApp::slotNewObjectIconView()
{
	PObjectIconView *iconView = new PObjectIconView(GuiCreateAction::chooseMapper());
	GuiRepository::getInstance()->addIconView(iconView, QString("Leer %1").arg(getNewIconViewNumber()),"Leer");
}


void StundePlanerApp::slotCheckDatamodel()
{
    AbstractMapper *m=MappingControler::getInstance()->getMapperByName("klasse");
    if(m){
        list<PObject*> *l_o=m->find_gen();
        for(list<PObject*>::iterator it=l_o->begin(); it!=l_o->end(); it++)
        {
            klasse *kl = dynamic_cast<klasse*>(*it);
            if(kl){
                Transactions::getCurrentTransaction()->add(kl);
                list<schueler*> *l_s=kl->getSchueler();
                for(list<schueler*>::iterator itt=l_s->begin(); itt!=l_s->end(); itt++)
                {
                    schueler *s=(*itt);
                    s->setKlasse(kl);
                    Transactions::getCurrentTransaction()->add(s);
                }

            }
        }
    }
}


void StundePlanerApp::slotShowKalender()
{
	GuiRepository::getInstance()->showFormForObject(SKalender::getInstance());
}


int StundePlanerApp::getNewIconViewNumber()
{
	return iv_nr++;
}



void StundePlanerApp::slotFileNewWindow()
{

  StundePlanerApp *new_window= new StundePlanerApp();
  new_window->show();


}

void StundePlanerApp::slotFileNew()
{

  if(!doc->saveModified())
  {
     // here saving wasn't successful

  }
  else
  {	
    doc->newDocument();		
    //setCaption(doc->URL().fileName(), false);
  }

}

void StundePlanerApp::slotFileOpen()
{
	
  XmlImportDialog *dialog = new XmlImportDialog(this);
  dialog->exec();
}

void StundePlanerApp::slotFileOpenRecent(const QUrl& url)
{
	
  if(!doc->saveModified())
  {
     // here saving wasn't successful
  }
  else
  {
    doc->openDocument(url);
    //setCaption(url.fileName(), false);
  }

}

void StundePlanerApp::slotFileSave()
{
	
  GuiControler::getInstance()->stopEdit();
  Transactions::getCurrentTransaction()->commit();

}

void StundePlanerApp::slotFileSaveAs()
{
  XmlExportDialog *dialog = new XmlExportDialog(this);
  dialog->show();

}

void StundePlanerApp::slotFileClose()
{
	
  close();

}

void StundePlanerApp::slotFilePrint()
{
    qDebug()<< "Warning: StundePlanerApp::slotFilePrint() not implemented";

}

void StundePlanerApp::slotFileQuit()
{
  dumpDatabase(QString("/home/mopp/schule/stundenplaner/stundenplaner-%1.sql").arg(QDate::currentDate().toString("yy-MM-dd")));

  saveOptions();

}

void StundePlanerApp::slotEditCut()
{
}

void StundePlanerApp::slotEditCopy()
{

}

void StundePlanerApp::slotEditPaste()
{
}

void StundePlanerApp::slotViewToolBar()
{
    qDebug() << "Warning: StundePlanerApp::slotViewToolBar() not implemented";

}

void StundePlanerApp::slotViewStatusBar()
{
  //turn Statusbar on or off
  if(!viewStatusBar->isChecked())
  {
    statusBar()->hide();
  }
  else
  {
    statusBar()->show();
  }

}


void StundePlanerApp::slotStatusMsg(const QString &text)
{
   qDebug() << "Warning: StundePlanerApp::slotStatusMsg() not implemented";

}


void StundePlanerApp::keyPressEvent( QKeyEvent *k )
{
    qDebug() << QString("StundePlanerApp: ") + k->text();
}



/*!
    \fn StundePlanerApp::getTree
 */
/*
doctree_stunden* StundePlanerApp::getTree()
{
    return view->getTree(); 
}
*/



MySideBar::MySideBar(QWidget *parent)
    : QListWidget(parent)
{

    setViewMode(QListView::IconMode);
    setSelectionRectVisible(false);
    setStyleSheet("QListWidget { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(100, 100, 100, 255), stop:1 rgba(150, 150, 150, 255)); border-right: 2px groove gray; }"
           "QListWidget::item:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(150, 150, 150, 255), stop:1 rgba(200, 200, 200, 255)); }"
                  "QListWidget::item:selected { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(200, 200, 200, 200), stop:1 rgba(220, 220, 220, 255));}"
                  "QListWidget::item {border-bottom: 2px groove gray; padding: 10px; color: white;}");

    setIconSize(QSize(48,48));
    connect(this,SIGNAL(itemActivated(QListWidgetItem*)),this,SLOT(activateItem(QListWidgetItem*)));
}

void MySideBar::activateItem(QListWidgetItem *item)
{
    GuiMode *mode = dynamic_cast<GuiMode*>(item);
    if(mode){
        GuiRepository::getInstance()->setActiveMode(mode);
    }
}
