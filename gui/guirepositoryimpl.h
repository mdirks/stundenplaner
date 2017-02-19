//
// C++ Interface: guirepositoryimpl
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GUIREPOSITORYIMPL_H
#define GUIREPOSITORYIMPL_H

#include <list>

#include <QMdiArea>
#include <QGraphicsScene>
#include <QWidget>
#include <QString>
#include <QStackedWidget>
#include <QToolBar>
#include <QVBoxLayout>

#include <QApplication>
//#include <kmdichildview.h>
//#include <kmdimainfrm.h>
#include <kmainwindow.h>

#include "guirepository.h"
#include "splashscreen.h"
#include "stundeplaner.h"
#include "orm/persistence/pobject.h"
#include "orm/mapping/abstractmapper.h"
#include "orm/mapping/mappingeventlistener.h"
#include "orm/repository/repositoryproperty.h"
#include "gui/forms/pobjecticonview.h"
#include "gui/base/guicontroler.h"
#include "datamodel/sitzplan.h"
#include "gui/data/sitzplanmap.h"
#include "guimode.h"
#include <QDialog>

#include <list>
#include <map>

using namespace std;

/**
@author Marcus Dirks
*/
class GuiRepositoryImpl : public GuiRepository, public MappingEventListener
{
public:
    ~GuiRepositoryImpl();
    static GuiRepositoryImpl* getInstance();
    
    void showForm(QWidget *w);
    void showDialog(QWidget *w);
    void showFormForObject(PObject *o, bool top=false);
    void showFormForObject(PObject *o, list<RepositoryProperty*> *properties, bool top=true);
    void showFormForObject(PObject *o, QWidget *form, bool top=true);
    void showDialogForObject(PObject *o, list<RepositoryProperty*> *properties=0);
    void showEditorForProperty(PObject *o,RepositoryProperty *rp);
    void showCentralWidget(QWidget *w);
    QWidget* getFormForObject(PObject *o,QWidget *parent=0, list<RepositoryProperty*> *properties=0);
    SitzplanMapView* getMapViewForSitzplan(sitzplan *sp);
    void setSelectedObject(PObject *o);
    void setFormWorkspace(QMdiArea *w);
    
    void setGraphicsView(QGraphicsView *GraphicsView);
    void initGui();
    void addTool(QWidget *tool, QString label, QString short_label,Qt::DockWidgetArea area=Qt::RightDockWidgetArea);
    void addIconView(PObjectIconView *iv, QString label, QString short_label);
    //KParts::Part *getPdfPart(QWidget *parent);
    //KParts::Part *getPart(QWidget *parent, QString qs1, QString qs2);

    void addMode(GuiMode *mode);
    void addService(GuiService *serv);
    void setActiveMode(GuiMode *mode);

    QStackedWidget* getCentralWidget();
    void setCentralWidget(QStackedWidget *sw);
  /*	
     QPixmap loadIcon(QString iconName, KIcon::Group group=KIcon::Desktop);
     QPixmap getIcon(PObject *o, KIcon::Group group=KIcon::Small);
     QPixmap getIcon(QString name, KIcon::Group group=KIcon::Small);
     QPixmap getIcon(RepositoryProperty *rp, KIcon::Group group=KIcon::Small);
     
     void selectIcon(QString name);
     void selectIcon(PObject *o);
     void selectIcon(RepositoryProperty *rp);
    */
    /*
     void addActiveEditor(PropertyEditor *editor);
     void stopEdit();
    */
    /*KXmlGuiWindow*/ QMainWindow* getMainFrame();
    void setMainFrame(/*KXmlGuiWindow*/ QMainWindow *mf);
    stundenplan* getActiveStundenplan();
    QWidget* getEditor(PObject *o, RepositoryProperty *rp, QWidget *parent=0);
     void reloadGui();
    void showInfo(QString cap, QString msg);
    void closeGui();

	bool versionChangeRequested(string className);
    void close();
    QString getDisplayString(PObject *);
    //QWidget* getFormForType(string className, QWidget *parent);
    SitzplanMap*  getMapForSitzplan(sitzplan *sp);

private:
     GuiRepositoryImpl();



     void addTypeView(list<PObject*>* list, QString label, QString short_label);
     void wrappWidgetAndAdd(QWidget *w);
    list<AbstractMapper*>* getMapViews();
    QMenu* getPopup(QString identifier);
    list<AbstractMapper*>* getPersistentClasses();

    
	list<PropertyEditor*> *activeEditors;
    list<GuiMode*> *modelist;

    
private:
     static GuiRepositoryImpl* impl_instance;
     QMdiArea* formWorkspace;
     QStackedWidget *centralWidget;

     const QPixmap std_icon_pixmap;
     QMainWindow /*KXmlGuiWindow*/ *mainFrame;
     stundenplan *activeplan;
     list<PObjectIconView*> *activeIconViews;
     GuiMode *activeMode;


protected:
    QGraphicsView* GraphicsView;
    //KApplication *app;
    StundePlanerApp *stundeplaner;
    list<AbstractMapper*> *listMappers, *listMapViews;
    map<QString, QString> mapIcons;

private:
    QToolBar *modeToolBar, *serviceToolBar;

};

class EditorBase : public QDialog
{
public:
    EditorBase(QWidget *parent);
    void setMainWidget(QWidget *mw);

protected slots:
    void slotOk();

private:
    QWidget *mainWidget;
    QVBoxLayout *contentsLayout;

};
#endif
