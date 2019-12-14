#include "stundenplanermainwindow.h"

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
#include <QMenuBar>


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

#include <QInputDialog>
#include <QFileDialog>


// application specific includes
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
#include "services/xml-export/xmlfactory.h"
#include "gui/data/sitzplanmap.h"
#include "gui/data/sitzplanmapmapper.h"
#include "gui/dialogs/iconchooser.h"

#define ID_STATUS_MSG 1



StundenPlanerMainWindow::StundenPlanerMainWindow(QWidget *parent) : QMainWindow(parent)
{
actionList = new MyActionList();
mainToolBar= new QToolBar("MainToolBar", this);
mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
addToolBar(Qt::TopToolBarArea,mainToolBar);
initActions();


initDocument();
initView();



readOptions();
//createTaskBar();

/*
fileSave->setEnabled(true);
fileSaveAs->setEnabled(true);
filePrint->setEnabled(false);
editCut->setEnabled(false);
editCopy->setEnabled(false);
editPaste->setEnabled(false);
*/

GuiRepository::getInstance()->setMainFrame(this);

}

StundenPlanerMainWindow::~StundenPlanerMainWindow()
{

}

void StundenPlanerMainWindow::initActions()
{
QAction *action;

QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
QMenu *extraMenu = menuBar() ->addMenu(tr("&Extra"));
changeSchuljahrAction = actionCollection()->addAction("schuljahr_waehlen", this);
connect(changeSchuljahrAction,&QAction::triggered,this,&StundenPlanerMainWindow::slotChangeSchuljahr);
changeSchuljahrAction->setIcon(GuiConfig::getInstance()->getIcon("action_schuljahr"));
changeSchuljahrAction->setText("Schuljahr wählen");
extraMenu->addAction(changeSchuljahrAction);

changeDatabaseAction = actionCollection()->addAction("change_database", this);
connect(changeDatabaseAction, &QAction::triggered,this,&StundenPlanerMainWindow::slotChangeDatabase);
changeDatabaseAction->setIcon(GuiConfig::getInstance()->getIcon("action_database"));
changeDatabaseAction->setText("Datenbank wechseln");
extraMenu->addAction(changeDatabaseAction);

addStundenplaneintragAction = actionCollection()->addAction("add_stundenplaneintrag", this);
connect(addStundenplaneintragAction,&QAction::triggered,this,&StundenPlanerMainWindow::slotAddStundenplaneintrag);
addStundenplaneintragAction->setIcon(GuiConfig::getInstance()->getIcon("add_stundenplaneintrag"));
addStundenplaneintragAction->setText("Neuer Stundenplaneintrag");
extraMenu->addAction(addStundenplaneintragAction);

action=actionCollection()->addAction("fehlzeitmeldung", this);
connect(action,&QAction::triggered,this,&StundenPlanerMainWindow::slotAddFehlzeitmeldung);
action->setIcon(GuiConfig::getInstance()->getIcon("fehlzeitmeldung"));
action->setText("Fehlzeitmeldung");
extraMenu->addAction(action);

action=actionCollection()->addAction("dump_database", this);
connect(action,&QAction::triggered,this,&StundenPlanerMainWindow::slotDumpDatabase);
action->setIcon(GuiConfig::getInstance()->getIcon("DumpDB"));
action->setText("DB sichern");
extraMenu->addAction(action);

action=actionCollection()->addAction("read_database", this);
connect(action,&QAction::triggered,this,&StundenPlanerMainWindow::slotReadDatabase);
action->setIcon(GuiConfig::getInstance()->getIcon("ReadDB"));
action->setText("DB lesen");
extraMenu->addAction(action);

action= actionCollection()->addAction("add_objectview", this);
connect(action,&QAction::triggered,this,&StundenPlanerMainWindow::slotNewObjectIconView);
action->setIcon(GuiConfig::getInstance()->getIcon("objectview"));
action->setText("Objektbrowser");
extraMenu->addAction(action);

action= actionCollection()->addAction("check_dm", this);
connect(action,&QAction::triggered,this,&StundenPlanerMainWindow::slotCheckDatamodel);
action->setIcon(GuiConfig::getInstance()->getIcon("checkdm"));
action->setText("Check Datamodel");
extraMenu->addAction(action);


action=actionCollection()->addAction("kalender",  this);
connect(action,&QAction::triggered,this,&StundenPlanerMainWindow::slotShowKalender);
extraMenu->addAction(action);

action=actionCollection()->addAction("stundenplan",  this);
connect(action,&QAction::triggered,this,&StundenPlanerMainWindow::slotShowStundenplan);
extraMenu->addAction(action);


action=actionCollection()->addAction("editIcons", this);
connect(action,&QAction::triggered,this,&StundenPlanerMainWindow::editIcons);
extraMenu->addAction(action);



fileSave = actionCollection()->addAction("Save",this);
connect(fileSave,&QAction::triggered,this,&StundenPlanerMainWindow::slotFileSave);
fileMenu->addAction(fileSave);
mainToolBar->addAction(fileSave);

//fileSaveAs = KStandardAction::saveAs(this, SLOT(slotFileSaveAs()), actionCollection());
//fileClose = KStandardAction::close(this, SLOT(slotFileClose()), actionCollection());
//filePrint = KStandardAction::print(this, SLOT(slotFilePrint()), actionCollection());
//fileQuit = KStandardAction::quit(this, SLOT(slotFileQuit()), actionCollection());
action = actionCollection()->addAction("Quit",this);
connect(action,&QAction::triggered,this,&StundenPlanerMainWindow::slotFileQuit);
fileMenu->addAction(action);
//editCut = KStandardAction::cut(this, SLOT(slotEditCut()), actionCollection());
//editCopy = KStandardAction::copy(this, SLOT(slotEditCopy()), actionCollection());
//editPaste = KStandardAction::paste(this, SLOT(slotEditPaste()), actionCollection());

}

MyActionList* StundenPlanerMainWindow::actionCollection()
{
    if(!actionList)
        actionList=new MyActionList();
    return actionList;
}

void StundenPlanerMainWindow::initDocument()
{
doc = new StundePlanerDoc(this);
}

QStackedWidget* StundenPlanerMainWindow::getCentralWidget()
{
  return centralWidget;
}

void StundenPlanerMainWindow::initView()
{
centralWidget = new QStackedWidget(this);
setCentralWidget(centralWidget);





//GuiRepository::getInstance()->setCentralWidget(centralWidget);

//sideBar = new MySideBar(this);
//addDockWindow(sideBar, "sidebar", Qt::LeftDockWidgetArea);


}





void StundenPlanerMainWindow::addDockWindow(QWidget *w, QString name, Qt::DockWidgetArea area)
{

  QDockWidget *dock = new QDockWidget(name,this);
  //dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dock->setWidget(w);
  addDockWidget(area, dock);

}

void StundenPlanerMainWindow::openDocumentFile(const QUrl& url)
{
  qDebug()<<"Warning StundenPlanerMainWindow::openDocumentFile not implemented";
}


StundePlanerDoc *StundenPlanerMainWindow::getDocument() const
{
return doc;
}

void StundenPlanerMainWindow::saveOptions()
{
qDebug() << "Warning: StundenPlanerMainWindow::saveOptions() not implemented" ;
/*
config->setGroup("General Options");
config->writeEntry("Geometry", size());
config->writeEntry("Show Toolbar", viewToolBar->isChecked());
config->writeEntry("Show Statusbar",viewStatusBar->isChecked());
config->writeEntry("ToolBarPos", (int) toolBar("mainToolBar")->barPos());
fileOpenRecent->saveEntries(config,"Recent Files");
*/
}


void StundenPlanerMainWindow::readOptions()
{
qDebug()<< "Warning: StundenPlanerMainWindow::readOptions() not implemented" ;
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
void StundenPlanerMainWindow::saveProperties(KConfig *_cfg)
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
void StundenPlanerMainWindow::readProperties(KConfig* _cfg)
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

bool StundenPlanerMainWindow::queryClose()
{
return doc->saveModified();
}

bool StundenPlanerMainWindow::queryExit()
{
saveOptions();
return true;
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////
void StundenPlanerMainWindow::slotAddStundenplaneintrag()
{
  GuiCreateAction::getInstance()->addStundenplaneintrag();
}

void StundenPlanerMainWindow::slotAddFehlzeitmeldung()
{
  /*
  fehlzeitmeldung *fzm = (fehlzeitmeldung*) GuiCreateAction::getInstance()->create("fehlzeitmeldung");
  GuiRepository::getInstance()->showDialogForObject(fzm);
  */

  qDebug() << "Warning: StundenPlanerMainWindow::slotAddFehlzeitmeldung() not implemented";
  //FehlzeitDialog::createFehlzeitmeldung();
}

void StundenPlanerMainWindow::slotChangeSchuljahr()
{
  schuljahr *sj = (schuljahr*) PObjectDialog::choosePObject(schuljahrmapper::getInstance());
  if(sj){
      GuiConfig::getInstance()->setActiveSchuljahr(sj);
      SKalender::getInstance()->setActiveSchuljahr(sj);
      SStundenplan::setActiveStundenplan(sj->getStundenplana());
      qDebug() << QString("Schuljahr set to %1").arg(sj->getName().c_str());
  } else {
      qDebug("StundenPlanerMainWindow::slotChangeSchuljahr() : selection of schuljahr failed");
  }
}

void StundenPlanerMainWindow::slotShowStundenplan()
{
  GuiRepository::getInstance()->showFormForObject(SStundenplan::getInstance());
}
void StundenPlanerMainWindow::slotChangeDatabase()
{
  QString db_name = QInputDialog::getText(this,"Datenbank wechseln","Neue Datenbank",QLineEdit::Normal,Database::getDatabaseName());

  GuiControler::getInstance()->stopEdit();
  GuiRepository::getInstance()->closeGui();
  if(MappingControler::getInstance()->initNewDatabase(db_name.toStdString())){
      SStundenplan::getInstance()->close();
      SStundenplan::getInstance();
      SKalender::getInstance()->close;
      SKalender::getInstance();
      GuiConfig::getInstance()->setDatabaseName(db_name);

  } else {
      GuiRepository::getInstance()->showInfo("Ungueltige Datenbank",QString("Konnte Datenbank %1 nicht oeffnen").arg(db_name));

  }
  GuiRepository::getInstance()->reloadGui();
}


void StundenPlanerMainWindow::slotDumpDatabase()
{
  QString fileName = QFileDialog::getSaveFileName();
  dumpDatabase(fileName);
}

void StundenPlanerMainWindow::dumpDatabase(QString fileName)
{
  QString databasename = GuiConfig::getInstance()->getDatabaseName();
  QStringList args = databasename.split(":");
  // change 0th argument is the drive now
  QString dbName=args.at(1);
  QString com;
  if(args.size()>2){
      com = QString("mysqldump -h%1 -u%2 -p%3 %4 > %5").arg(args.at(1),args.at(2),args.at(3),dbName,fileName);
  } else {
      com = QString("mysqldump -user=root %1 > %2").arg(dbName).arg(fileName);
  }
  qDebug() << com;
  QProcess *p = new QProcess(this);
  p->start(com);
}

void StundenPlanerMainWindow::slotReadDatabase()
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

void StundenPlanerMainWindow::slotDatabaseReadFinished(){
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


void StundenPlanerMainWindow::slotNewObjectIconView()
{
  AbstractMapper *mapper=GuiCreateAction::chooseMapper();
  if(mapper){
      PObjectIconView *iconView = new PObjectIconView(mapper);
      GuiRepository::getInstance()->addIconView(iconView, QString("Leer %1").arg(getNewIconViewNumber()),"Leer");
   }
}


void StundenPlanerMainWindow::slotCheckDatamodel()
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


void StundenPlanerMainWindow::slotShowKalender()
{
  GuiRepository::getInstance()->showFormForObject(SKalender::getInstance());
}


int StundenPlanerMainWindow::getNewIconViewNumber()
{
  return iv_nr++;
}



void StundenPlanerMainWindow::slotFileNewWindow()
{

StundenPlanerMainWindow *new_window= new StundenPlanerMainWindow();
new_window->show();


}

void StundenPlanerMainWindow::slotFileNew()
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

void StundenPlanerMainWindow::slotFileOpen()
{

XmlImportDialog *dialog = new XmlImportDialog(this);
dialog->exec();
}

void StundenPlanerMainWindow::slotFileOpenRecent(const QUrl& url)
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

void StundenPlanerMainWindow::slotFileSave()
{

GuiControler::getInstance()->stopEdit();
Transactions::getCurrentTransaction()->commit();

}

void StundenPlanerMainWindow::slotFileSaveAs()
{
XmlExportDialog *dialog = new XmlExportDialog(this);
dialog->show();

}

void StundenPlanerMainWindow::slotFileClose()
{

close();

}

void StundenPlanerMainWindow::slotFilePrint()
{
  qDebug()<< "Warning: StundenPlanerMainWindow::slotFilePrint() not implemented";

}

void StundenPlanerMainWindow::slotFileQuit()
{
dumpDatabase(QString("/home/mopp/schule/stundenplaner/stundenplaner-%1.sql").arg(QDate::currentDate().toString("yy-MM-dd")));

saveOptions();

}

void StundenPlanerMainWindow::slotEditCut()
{
}

void StundenPlanerMainWindow::slotEditCopy()
{

}

void StundenPlanerMainWindow::slotEditPaste()
{
}

void StundenPlanerMainWindow::slotViewToolBar()
{
  qDebug() << "Warning: StundenPlanerMainWindow::slotViewToolBar() not implemented";

}

void StundenPlanerMainWindow::slotViewStatusBar()
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


void StundenPlanerMainWindow::editIcons()
{
    QDialog *d=new IconChooserDialog();
    d->show();
    d->raise();
    d->activateWindow();

}

void StundenPlanerMainWindow::slotStatusMsg(const QString &text)
{
 qDebug() << "Warning: StundenPlanerMainWindow::slotStatusMsg() not implemented";

}


void StundenPlanerMainWindow::keyPressEvent( QKeyEvent *k )
{
  qDebug() << QString("StundenPlanerMainWindow: ") + k->text();
}



/*!
  \fn StundenPlanerMainWindow::getTree
*/
/*
doctree_stunden* StundenPlanerMainWindow::getTree()
{
  return view->getTree();
}
*/





