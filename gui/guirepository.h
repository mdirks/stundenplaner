//
// C++ Interface: guirepository
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GUIREPOSITORY_H
#define GUIREPOSITORY_H

#include <qstring.h>
#include <qwidget.h>
//#include <kiconloader.h>
//#include <kmainwindow.h>

#include "orm/persistence/pobject.h"
#include "orm/mapping/abstractmapper.h"
#include "orm/repository/repositoryproperty.h"
#include "gui/base/propertyeditor.h"
#include "gui/forms/pobjecticonview.h"
#include "gui/mapviews/sitzplanmapview.h"
#include "datamodel/stundenplan.h"
#include "splashscreen.h"
#include "gui/base/guicontroler.h"
#include "guimode.h"
#include "guiservice.h"

//#include <kglobal.h>
//#include <KConfig>
//#include <KConfig>
//#include <KIconLoader>
//#include <KIconDialog>
//#include <ktrader.h>
//#include <klibloader.h>
//#include <KParts/Part>
//#include <kmessagebox.h>
//#include <KXmlGuiWindow>

#include <QStackedWidget>
#include <QMainWindow>

/** The main GUI Controller Singleton (Startup, global services, editing controll)
@author Marcus Dirks
*/
class GuiRepository :public GuiControler {

Q_OBJECT


public slots:
    virtual void showForm(QWidget *w)=0;
    virtual void showDialog(QWidget *form)=0;
    virtual void showFormForObject(PObject *o, bool top=true)=0;
    virtual void showFormForObject(PObject *o, list<RepositoryProperty*> *properties, bool top=true)=0;
    virtual void showFormForObject(PObject *o, QWidget *form, bool top=true)=0;
	virtual void showDialogForObject(PObject *o,list<RepositoryProperty*> *properties=0)=0;
    virtual void showCentralWidget(QWidget *w)=0;

public:
    virtual QWidget* getFormForObject(PObject *o,QWidget *parent=0, list<RepositoryProperty*> *properties=0)=0;


    virtual SitzplanMapView* getMapViewForSitzplan(sitzplan *sp)=0;
    virtual void setSelectedObject(PObject *o)=0;
    virtual QStackedWidget* getCentralWidget()=0;
    virtual void setCentralWidget(QStackedWidget *sw)=0;
    virtual void setActiveMode(GuiMode *mode)=0;
   virtual void showEditorForProperty(PObject *o,RepositoryProperty *rp)=0;
   virtual void addTool(QWidget *tool,
                         QString label,
                         QString short_label,
                         Qt::DockWidgetArea area = Qt::RightDockWidgetArea)=0;
   virtual void addIconView(PObjectIconView *iv, QString label, QString short_label)=0;
    virtual void addMode(GuiMode *mode)=0;
    virtual void addService(GuiService *serv)=0;

   virtual QMenu* getPopup(QString identifier) = 0;
   
   static GuiRepository* getInstance();
   static SplashScreen* showSplashScreen();
   static  void hideSplashScreen();

   virtual void initGui()=0;
   virtual list<AbstractMapper*>* getMapViews() = 0;
   
    


    virtual /*KXmlGuiWindow**/ QMainWindow* getMainFrame() = 0;


    virtual void setMainFrame(/*KXmlGuiWindow*/ QMainWindow *mf) = 0;

   virtual QWidget* getEditor(PObject *o, RepositoryProperty *rp, QWidget *parent=0)=0;


    virtual list<AbstractMapper*>* getPersistentClasses() = 0;
    virtual stundenplan* getActiveStundenplan()=0;

    virtual void reloadGui() = 0;
    virtual void showInfo(QString cap, QString mes) = 0;
    virtual void closeGui() = 0;
 
    //KParts::Part* getPdfPart(QWidget *parent);
    //KParts::Part* getPart(QWidget *parent, QString qs1, QString qs2);
    virtual void close() = 0;
    virtual QString getDisplayString(PObject *po)=0;
    virtual SitzplanMap*  getMapForSitzplan(sitzplan *sp)=0;

private:
    /** */
    static GuiRepository* instance;
    static SplashScreen *splash;
};

#endif
