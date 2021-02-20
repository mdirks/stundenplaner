//
// C++ Implementation: guirepositoryimpl
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//


#include "guirepositoryimpl.h"
//#include "form_stunde_rt_impl.h"
//#include "form_opo.h"
#include "gui/forms/pobjecteditor3.h"
#include "../datamodel/stunde.h"
#include "splashscreenimpl.h"
#include "orm/mapping/mappingcontroler.h"
#include "orm/mapping/abstractmapper.h"
#include "data/themaitemmapper.h"
#include "data/themamapmapper.h"
#include "data/daymapmapper.h"
#include "data/weekmapmapper.h"
#include "mapviews/daymapview.h"
#include "mapviews/weekmapview.h"
#include "data/pobjectgraphicsitemmapper.h"
#include "data/themamap.h"
#include "forms/pobjecteditor.h"
//#include "pobjectlistbox.h"
//#include "typelistview.h"
#include "datamodel/datamodelrepository.h"
#include "datamodel/opomapper.h"
#include "datamodel/stundemapper.h"
#include "datamodel/reihe.h"
#include "datamodel/schuljahrmapper.h"
#include "datamodel/teilleistung.h"
#include "gui/forms/pobjecticonview.h"
#include "gui/forms/pobjecteditor2.h"
#include "gui/forms/reiheplaner.h"
#include "orm/transactions/transactions.h"
#include "gui/base/propertyeditor.h"
#include "gui/forms/pobjecttable.h"
#include "gui/base/guiconfig.h"
#include "services/actions/createaction.h"
#include "datamodel/stundenplanmapper.h"
#include "gui/forms/pobjectdialog.h"
#include "gui/forms/dateeditor.h"
#include "gui/forms/pobjectlabel.h"
#include "gui/data/schultaggraphicsitemmapper.h"
#include "gui/forms/stringeditor.h"
#include "gui/forms/textpropertyeditor.h"
#include "gui/forms/seatmap.h"
#include "gui/actions/readcsvlistaction.h"
#include "gui/forms/formspopupfactory.h"
#include "gui/mapviews/mapviewspopupfactory.h"
#include "gui/actions/guipopupfactory.h"
#include "orm/repository/repositoryenabled.h"
#include "services/skalender.h"
#include "gui/forms/kalenderview.h"
#include "gui/actions/guiobjectfactoryimpl.h"
#include "gui/forms/pobjecttable.h"
#include "gui/actions/pobjecttablecontrolerimpl.h"
#include "gui/forms/lernkarteviewer.h"
#include "datamodel/lernkarte.h"
#include "gui/data/sitzplanmapmapper.h"
#include "gui/actions/kalenderviewcontroler.h"
#include "gui/actions/genericmapviewcontroler.h"
#include "gui/actions/sitzplanmapviewcontroler.h"
#include "gui/mapviews/sitzplanmapview.h"
#include "gui/data/platzgraphicsitemmapper.h"
#include "gui/data/guiobject.h"
#include "gui/data/guiobjectmapper.h"
#include "services/sstundenplan.h"
#include "gui/actions/modeplanung.h"
#include "gui/actions/modelesen.h"
//#include "gui/actions/modelesenmapper.h"
#include "gui/actions/modematerail.h"
#include "gui/actions/servicelatex.h"
#include "gui/actions/modelernen.h"
#include "gui/actions/servicexml.h"
#include "gui/actions/modenotes.h"
#include "gui/actions/servicepdf.h"
#include "gui/actions/modemaps.h"
#include "gui/data/themamapsatzmapper.h"

#include <QPixmap>
//#include <qscrollview.h>
#include <QMessageBox>
#include <QWidget>

//#include <KParts/ComponentFactory>
//#include <KXMLGUIFactory>
//#include <kglobal.h>
//#include <KConfig>
//#include <KIconLoader>
//#include <KIconDialog>
//#include <ktrader.h>
//#include <klibloader.h>
//#include <kmessagebox.h>
//#include <kservice.h>
//#include <kservicetypetrader.h>
//#include <KParts/Part>



GuiRepositoryImpl* GuiRepositoryImpl::impl_instance=0;
//static GuiRepositoryImpl::QMdiarea* formWorkspace=0;


GuiRepositoryImpl* GuiRepositoryImpl::getInstance()
{
	if(!impl_instance)
	{
		impl_instance=new GuiRepositoryImpl();
	}
	return impl_instance;
}


GuiRepositoryImpl::GuiRepositoryImpl()
 : GuiRepository(),std_icon_pixmap(16,16)
{
	formWorkspace=0;
	
	stundeplaner = 0;
	listMappers = 0;
	activeplan = 0;
    activeMode = 0;

	
	activeEditors = new list<PropertyEditor*>();
	activeIconViews = new list<PObjectIconView*>();
    modelist = new list<GuiMode*>();


	


	listMappers = new list<AbstractMapper*>();
	listMappers->push_back(ThemaItemmapper::getInstance());
	listMappers->push_back(ThemaMapmapper::getInstance());
    listMappers->push_back(ThemaMapSatzmapper::getInstance());
	listMappers->push_back(PObjectGraphicsItemmapper::getInstance());
	listMappers->push_back(PlatzGraphicsItemmapper::getInstance());
	listMappers->push_back(SchultagGraphicsItemmapper::getInstance());
	listMappers->push_back(DayMapmapper::getInstance());
        listMappers->push_back(WeekMapmapper::getInstance());
	listMappers->push_back(SitzplanMapmapper::getInstance());
	listMappers->push_back(GuiObjectmapper::getInstance());
    //listMappers->push_back(ModeLesenmapper::getInstance());
	

    // Listener does not work here since Gui not yet available
    //MappingControler::getInstance()->addMappingEventListener(this);
	for(list<AbstractMapper*>::iterator it = listMappers->begin();
		it!=listMappers->end(); ++it)
	{
		AbstractMapper *mapper = *it;
		
		MappingControler::getInstance()->registerPersistentClass(mapper);
		RepositoryEnabled *re = dynamic_cast<RepositoryEnabled*>(*it);
		if(re){
			Repository::getInstance()->addRepositoryEntry(re->getRepositoryEntry());
		}
	}
	
	listMapViews = new list<AbstractMapper*>();
	listMapViews->push_back(ThemaMapmapper::getInstance());
	listMapViews->push_back(DayMapmapper::getInstance());
	listMapViews->push_back(WeekMapmapper::getInstance());
	
}


GuiRepositoryImpl::~GuiRepositoryImpl()
{
}




/*!
    \fn GuiRepositoryImpl::showFormForObject(PObject *o)

     Given the object we get its class to create the appropriate widget. Appropriate widgets are hard coded.
	The generic case (PObject) is handeld by PObjectEditor2. The widget is then turned into a KMdiChildView

			stundeplaner->createWrapper(form, className, className);

	and added to the Mainframe.

			stundeplaner->addWindow(childView);
    
 */
QWidget* GuiRepositoryImpl::getFormForObject(PObject *o, QWidget *parent, list<RepositoryProperty*> *properties)
{
	if(stundeplaner==0)
	{
		qWarning("GuiRepositoryImp::getFormForObject: No FormWorkspace given");
		return 0;
	}
	if(o==0)
	{
		qWarning("GuiRepositoryImp::getFormForObject: Null objet given given");
		return 0;
	}


	
	string className;
	if(o->getPersistenceObject()){
		className = o->getPersistenceObject()->getClassName();
	} else {
		qWarning("GuiRepositoryImp::getFormForObject: Invalid objet given given");
		return 0;
	}
	/*
	if(className == "stunde")
	{
		stunde *st = (stunde*) o;
		form = new form_stunde_rt_impl();
		((form_stunde_rt_impl*)form)->setStunde(st);
	} else if(className == "opo"){
		opo *op = (opo*) o;
		form = new form_opo();
		((form_opo*)form)->setObject(op);
	} else 
	*/

	QWidget *form =0;

	if (className == "ThemaMap"){
		ThemaMapView *mapView = new ThemaMapView();
		ThemaMap *map = (ThemaMap*) o;//ThemaMapmapper::getInstance()->create();
		mapView->setMap(map);
		new GenericMapViewControler(mapView);

		form = mapView;
	} else if (className == "DayMap"){
		DayMapDisplay *view = new DayMapDisplay();
		DayMap *map = dynamic_cast<DayMap*>(o);
		view->setMap(map);
		
		form = view;
	
	}else if (className == "WeekMap"){
		WeekMapView *view = new WeekMapView();
		WeekMap *map = dynamic_cast<WeekMap*>(o);
		view->setMap(map);
		
		form = view;
        form->setToolTip("Wochenuebersicht");
	} else if (className == "reihe"){
		reihe *rh = dynamic_cast<reihe*>(o);
		ReihePlaner *rp = new ReihePlaner(rh);
		form = rp;
	} else if (className == "sitzplan"){
        sitzplan *sp = dynamic_cast<sitzplan*>(o);
        form=getMapViewForSitzplan(sp);

	} else  if (className == "SKalender"){
        SKalender *sk = dynamic_cast<SKalender*>(o);
		KalenderView *kw = new KalenderView(parent);
		new KalenderViewControler(kw);
		kw->setMap(sk->getCurrentWeek());
        form=kw;
        form->setToolTip(QString("Wochenuebersicht"));
	} else if (className == "lernkarte"){
		lernkarte *lk = dynamic_cast<lernkarte*>(o);
        LernkarteViewer *lkv = new LernkarteViewer(parent);
		lkv->setLernkarte(lk);
		form=lkv;
	} else if (className == "lernkartensatz"){
		lernkartensatz *ls = dynamic_cast<lernkartensatz*>(o);
        LernkartensatzViewer *lkv = new LernkartensatzViewer(ls,parent);
		//lkv->setLernkartensatz(ls);
		form=lkv;
	
	} else {
        PObjectEditor3 *editor = new PObjectEditor3(o,parent, properties);
		/*
		connect(editor->editRequestor,SIGNAL(editRequested(PObject*)),this,SLOT(showFormForObject(PObject*)));
		connect(editor->editRequestor,SIGNAL(dialogRequested(PObject*)),this,SLOT(showDialogForObject(PObject*)));
		*/
		form = editor;
        form->setToolTip(QString("%1: %2").arg(o->getClassName().c_str()).arg(o->getName().c_str()));
		Transactions::getCurrentTransaction() -> add(o);
	}
    form->setWindowIcon(GuiConfig::getInstance()->getIcon(className.c_str()));
	return form;
}






SitzplanMapView* GuiRepositoryImpl::getMapViewForSitzplan(sitzplan *sp)
{
    SitzplanMapView *spmv=0;
    if(sp){
        SitzplanMap *spm = getMapForSitzplan(sp);
        if(spm){
            spmv = new SitzplanMapView(spm);
            //spmv->setMap(spm);

            new SitzplanMapViewControler(spmv);
            //spmv->setToolTip(QString("Sitzplan %1").arg(sp->getKlasse()->getName().c_str()));
            if(sp->getKlasse()){
                spmv->setToolTip(sp->getKlasse()->getName().c_str());
            } else {
                spmv->setToolTip("Empty klasse");
            }

        }
    }
    return spmv;
}

void GuiRepositoryImpl::showForm(QWidget *w){
    if(activeMode){
        activeMode->showForm(w);
    }
}

void GuiRepositoryImpl::showFormForObject(PObject *o, bool top){
    QWidget *form = getFormForObject(o, getMainFrame());
    showFormForObject(o,form,top);
}

void GuiRepositoryImpl::showFormForObject(PObject *o, list<RepositoryProperty*> *properties, bool top){

	QWidget *form = getFormForObject(o, getMainFrame());
    showFormForObject(o,form,top);
}

void GuiRepositoryImpl::showFormForObject(PObject *o, QWidget *form, bool top){
    if(form !=0){
        string objectName = o-> getName();
		string className = o->getPersistenceObject()->getClassName();

        if(activeMode){
            activeMode->showForm(form);
        }
	} else { qDebug("GuiRepositoryImp: could not get a valid form");}
	
}



void GuiRepositoryImpl::showDialogForObject(PObject *o, list<RepositoryProperty*> *properties)
{
	
	EditorBase *dialog = new EditorBase(stundeplaner);
	QWidget *form=getFormForObject(o,dialog,properties);
	

	if(form){
        showDialog(form);
    } else {
		qWarning("GuiRepositoryImpl::showDialogForObject: Could not get form for object");
	}
}

void GuiRepositoryImpl::showDialog(QWidget *form)
{
    if(form){
        EditorBase *dialog = new EditorBase(stundeplaner);
        dialog->setMainWidget(form);
        dialog->exec();
    } else {
        qWarning("GuiRepositoryImpl::showDialog: Zero form");
    }
}

void GuiRepositoryImpl::showCentralWidget(QWidget *w)
{


}


void GuiRepositoryImpl::showEditorForProperty(PObject *o,RepositoryProperty *rp)
{

    //Transactions::getCurrentTransaction()->add(o); // hack because some editors do not commit properly

    if(rp){
        if(rp->isPObject()){
            showFormForObject(rp->asPObject(o));
        } else {
            QString title=rp->getName().c_str();
            EditorBase *dialog = new EditorBase(stundeplaner,title);
            QWidget *form=0;

            if(rp->isString()){
                StringEditor *se= new StringEditor(o,rp,dialog);
                connect(dialog,SIGNAL(finished(int)),se,SLOT(stopEdit()));
                form=se;
            } else if(rp->isText()){
                TextPropertyEditor *pe = new TextPropertyEditor(o,rp,dialog);
                connect(dialog,SIGNAL(finished(int)),pe,SLOT(stopEdit()));
                form=pe;
            } else if(rp->isNumeric()){
                form = new StringEditor(o,rp,dialog);
            } else if(rp){
                form = new QLabel(QString("%1 : unknown editor type").arg(rp->getName().c_str()),dialog);
            } else {
                form = new QLabel(QString("empty property"),dialog);
            }

            dialog->setMainWidget(form);
            dialog->exec();
        }
    }

}
/*!
    \fn GuiRepositoryImpl::setFormWorkspace(QMdiarea *w)
 */
void GuiRepositoryImpl::setFormWorkspace(QMdiArea *w)
{
    formWorkspace=w;
}





/*!
    \fn GuiRepositoryImpl::setGraphicsView(QGraphicsView *GraphicsView)
 */
void GuiRepositoryImpl::setGraphicsView(QGraphicsView *GraphicsView)
{
    this->GraphicsView  = GraphicsView;
}


/*!
    \fn GuiRepositoryImpl::initGui()
 */
void GuiRepositoryImpl::initGui()
{
    //stundeplaner = new StundePlanerApp();
    stundeplaner = new StundenPlanerMainWindow();

    //rightToolBar = new QToolBar(stundeplaner);
    //stundeplaner->addToolBar(Qt::RightToolBarArea,rightToolBar);
    modeToolBar = new QToolBar(stundeplaner);
    stundeplaner->addToolBar(Qt::LeftToolBarArea,modeToolBar);
    serviceToolBar = new QToolBar(stundeplaner);
    stundeplaner->addToolBar(Qt::LeftToolBarArea,serviceToolBar);


    setMainFrame(stundeplaner);
    setCentralWidget(stundeplaner->getCentralWidget());
    stundeplaner->show();
     
	SKalender::getInstance();


    (new ReadCsvlistAction())->reg();

	GuiControler::setInstance(this);
	GuiObjectFactory::setInstance(new GuiObjectFactoryImpl());
	FormsPopupFactory::setInstance(GuiPopupFactory::getInstance());
	MapviewsPopupFactory::setInstance(GuiPopupFactory::getInstance());
	PObjectTableControlerFactory::setInstance(new PObjectTableControlerFactoryImpl());

    //addMode(ModePlanung::getInstance());
    addMode(new ModeLesen());
    addMode(new ModeMaterial());
    addMode(new ModeLernen());
    addMode(new ModeNotes());
    addMode(new ModeMaps());
    addService(ServiceLatex::getInstance());
    addService(new ServiceXml());
    addService(ServicePdf::getInstance());
}

void GuiRepositoryImpl::setSelectedObject(PObject *o)
{
    if(activeMode){
        activeMode->activateObject(o);
    }
}

void GuiRepositoryImpl::setActiveMode(GuiMode *mode)
{
    if(activeMode != mode){
        if(activeMode) activeMode->deactivate();
        activeMode=mode;
        //mode->setupMode();
        mode->activate();
    }
}

void GuiRepositoryImpl::addMode(GuiMode *mode)
{
    modelist->push_back(mode);
    modeToolBar->addAction(mode);

}

void GuiRepositoryImpl::addService(GuiService *serv)
{
    //stundeplaner->addMode(mode);
    GuiServiceToolButton *tb = new GuiServiceToolButton(serv,serviceToolBar);
    tb->setIcon(serv->icon());
    serviceToolBar->addWidget(tb);

}



void GuiRepositoryImpl::addIconView(PObjectIconView *iv, QString label, QString short_label)
{
	activeIconViews->push_back(iv);
	addTool(iv,label,short_label);
	
}

void GuiRepositoryImpl::addTool(QWidget *tool,
                                QString label,
                                QString short_label,
                                Qt::DockWidgetArea area)
{
    stundeplaner->addDockWindow( tool, short_label,area);
}

void GuiRepositoryImpl::addTypeView(list<PObject*>* list, QString label, QString short_label){
    qDebug() << "Warning: GuiRepositoryImpl::addTypeView not implemented";
}

/*!
    \fn GuiRepositoryImpl::wrappWidget(QWidget *w)
 */
void GuiRepositoryImpl::wrappWidgetAndAdd(QWidget *pNewView)
{
   if(activeMode){
       activeMode->showForm( pNewView);
   }
}


/*!
    \fn GuiRepositoryImpl::getMapViews()
 */
list<AbstractMapper*>* GuiRepositoryImpl::getMapViews()
{
    return listMapViews;
}




/*
void GuiRepositoryImpl::addActiveEditor(PropertyEditor *editor)
{
     	
	activeEditors->push_back(editor);
}



void GuiRepositoryImpl::stopEdit()
{
    if(activeEditors){
	for(list<PropertyEditor*>::iterator it = activeEditors->begin(); it != activeEditors->end(); it++){
		if((*it)){
			(*it)->stopEdit();
		} else {
			qDebug(QString("GuiRepositoryImpl::stopEdit : !!! Invalid editor in editor-list"));
		}
	}
   }
}
*/

QStackedWidget* GuiRepositoryImpl::getCentralWidget()
{
    return centralWidget;
}

void GuiRepositoryImpl::setCentralWidget(QStackedWidget *cW)
{
    centralWidget = cW;
}


/*!
    \fn GuiRepositoryImpl::getMainFrame()
 */
QMainWindow* GuiRepositoryImpl::getMainFrame()
{
    return mainFrame;
}

void  GuiRepositoryImpl::setMainFrame(QMainWindow *mf)
{
     this->mainFrame = mf;
}

/*!
    \fn GuiRepositoryImpl::getPopup(QString identifier)
 */

QMenu* GuiRepositoryImpl::getPopup(QString identifier)
{
    QMenu *popup = new QMenu();

	return popup;
}


/*!
    \fn GuiRepositoryImpl::getPersistentClasses()
 */
list<AbstractMapper*>* GuiRepositoryImpl::getPersistentClasses()
{
    return getMapViews();
}


/*!
    \fn GuiRepositoryImpl::getActiveStundenplan()
 */
stundenplan* GuiRepositoryImpl::getActiveStundenplan()
{
    if(activeplan==0) {
	QString plan_id_str = GuiConfig::getInstance()->readEntry("GUI", "stundenplan_id");
	if(plan_id_str==""){
		 qDebug("No Stundenplan registered");
		//activeplan = (stundenplan*) CreateAction::getInstance()->create( "stundenplan");
		activeplan = (stundenplan*) PObjectDialog::choosePObject( stundenplanmapper::getInstance());
		QString str_id;
		str_id.setNum(activeplan->getID());
		GuiConfig::getInstance()->writeEntry("GUI","stundenplan_id",str_id);
	} else {
		qDebug("Loading active plan");
		int plan_id = plan_id_str.toInt();
		PObject *o = Database::getInstance()->loadObjectById(plan_id);
		if(activeplan = dynamic_cast<stundenplan*>(o)){
			qDebug("Loading successful");
		} else {
			qDebug("FAILED to load acitve plan");
		}
	}
   
	
    }
    return activeplan;
}


QWidget* GuiRepositoryImpl::getEditor(PObject *mo, RepositoryProperty *prop, QWidget *mainTab)
{
	QWidget *w = 0;
	if(prop->isString()){
		w= new StringEditor(mo,prop,mainTab);
	} else if(prop->isText()){
					
					w =  new TextPropertyEditor(mo,prop,mainTab);
					//w->setPaletteBackgroundColor(QColor(220,220,250));
			} else if(prop->isCollection()){
					if(prop->getName() == "Eintraege"){
						PObjectTable *table = new PObjectTable(prop,mo,mainTab);
						table->load();
						w=table;
					} else {
						PObjectIconView *iconView = new PObjectIconView(prop,mo,mainTab);
						iconView->load();
						//iconView -> load(prop->asCollection( mo ) );
						w = iconView;
					}
			} else if(prop->isDate()){
					w=new DateEditor(mo,prop,mainTab) ;
			} else if(prop->isPObject()){
					if(prop->getType() == "sitzplan"){
						sitzplan* sp = dynamic_cast<sitzplan*>(prop->asPObject(mo));
						if(sp){
							w = getFormForObject(sp,mainTab);
						}
					} else {
						w= new PObjectLabel(prop,mo,mainTab);
					}
			} else if(prop->isNumeric()){
					w= new StringEditor(mo,prop,mainTab);
			}	
			return w;
}

void GuiRepositoryImpl::reloadGui()
{
	for(list<PObjectIconView*>::iterator it = activeIconViews->begin(); it!=activeIconViews->end(); it++)
	{
		(*it)->clear();
		(*it)->load();
	}
    for(list<GuiMode*>::iterator it=modelist->begin(); it!=modelist->end(); it++)
    {
        (*it)->reload();

    }
}



/*!
    \fn GuiRepositoryImpl::showInfo(QString msg)
 */
void GuiRepositoryImpl::showInfo(QString cap, QString mesg)
{
    QMessageBox::warning(getMainFrame(),cap,mesg,QMessageBox::Ok,QMessageBox::Ignore );
}


/*!
    \fn GuiRepositoryImpl::closeGui()
 */
void GuiRepositoryImpl::closeGui()
{
    for(list<GuiMode*>::iterator it = modelist->begin(); it!=modelist->end(); it++)
    {
        (*it)->close();
    }
    SKalender::close();


}

bool GuiRepositoryImpl::versionChangeRequested(string className)
{
    int ans = QMessageBox::question(getMainFrame(),"Version change",
              QString("Really change version of %1 in database - stored data could be lost").arg(className.c_str()),
                                    QMessageBox::No, QMessageBox::Yes, QMessageBox::NoButton);

	if(ans==QMessageBox::Yes)
		return true;
	else return false;
}

/*!
    \fn GuiRepositoryImpl::getMapForSitzplan(sitzplan *sp)
 */
SitzplanMap*  GuiRepositoryImpl::getMapForSitzplan(sitzplan *sp)
{
    list<PObject*> *list_maps = SitzplanMapmapper::getInstance()->find_gen();
	SitzplanMap *result=0;
	list<PObject*>::iterator it = list_maps->begin();
	while(it != list_maps->end() && result ==0)
	{
		SitzplanMap *sm = dynamic_cast<SitzplanMap*>(*it);
		if(sm){
			if(sm->getSitzplan() == sp) result = sm;
		}
		it++;
	}
	if(!result){
		qDebug("WARNING --- GuiRepositoryImpl::getMapForSitzplan : could not find SitzplanMap for sitzplan, creating NEW");
		result = (SitzplanMap*) SitzplanMapmapper::getInstance()->create();
		result->setSitzplan(sp);
		result->loadSitzplan();
	}
	return result;
}


/*!
    \fn GuiRepositoryImpl::close()
 */
void GuiRepositoryImpl::close()
{
    /// @todo implement me
}





/*!
    \fn GuiRepositoryImpl::getDisplayString(PObject *)
 */
QString GuiRepositoryImpl::getDisplayString(PObject *po)
{
    QString dS("N t d");
    if(teilleistung *tl = dynamic_cast<teilleistung*>(po)){
    dS=QString("\\begin{center} {\\bf \n %1 -- %2\\\\ \n Ergebnis\\\"ubersicht}\\\\[.5cm] \n\n").arg(tl->getName().c_str()).arg(tl->getKlasse()->getName().c_str());
	int all=tl->getNoten()->size();
	int mis=tl->getAnzahl(-1);
	dS=dS.append(QString("Von %1 Sch\\\"ulern: %2 geschrieben, %3 gefehlt \\\\[.5cm] \n").arg(all).arg(all-mis).arg(mis));
	dS=dS.append("\\begin{description}\n");
	// noten
	int sum=0;
	int ges=0;
	dS=dS.append("\\item[Noten]~\\\\[.5cm]\n");
	dS=dS.append("\\begin{tabular}{|c|c|c|c|c|c|} \n \\hline \n");
	for(int i=1;i<=5;i++){
		dS=dS.append(QString("%1  & ").arg(i)); 
	}
	dS=dS.append("6 \\\\ \\hline \n");
	for(int i=1; i<=5; i++){
		int n=tl->getAnzahlNote(i);
		ges+=n;
		sum+=n*i;
		dS=dS.append(QString("%1 & ").arg(tl->getAnzahlNote(i)));
	}
	int n=tl->getAnzahlNote(6);
	ges+=n;
	sum+=n*6;
	dS=dS.append(" %1 \\\\ \n \\hline \n").arg(n);
	dS=dS.append("\\end{tabular}\n\n");
	dS=dS.append(QString("{\\bf Durchschnitt: %1}\n").arg(sum*1.0/ges));
	//punkte
	sum=0;
	ges=0;
	dS=dS.append("\\item[Punkte]~\\\\[.5cm]\n");
	dS=dS.append("\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|} \n \\hline \n");
	for(int i=15;i>0;i--){
		dS=dS.append(QString("%1  & ").arg(i)); 
	}
	dS=dS.append("0 \\\\ \\hline \n");
	for(int i=15; i>0; i--){
		int n=tl->getAnzahl(i);
		ges+=n;
		sum+=n*i;
		dS=dS.append(QString("%1 & ").arg(n));

	}
	n=tl->getAnzahlNote(0);
	ges+=n;
	sum+=n*0;
	dS=dS.append(QString(" %1 \\\\ \n \\hline \n").arg(n));
	dS=dS.append("\\end{tabular}\n\n");
	dS=dS.append(QString("{\\bf Durchschnitt: %1}\n").arg(sum*1.0/ges));
	

	dS=dS.append("\\end{description} \n \\end{center}\n");
    }
    return dS;
}


EditorBase::EditorBase(QWidget *parent,QString title) : QDialog(parent)
{
    setWindowTitle(title);
    mainWidget=new QLabel("",this);

    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);

    contentsLayout = new QVBoxLayout;
    contentsLayout->addWidget(mainWidget);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout= new QVBoxLayout;
    mainLayout->addLayout(contentsLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

}




void EditorBase::slotOk()
{
    GuiControler::getInstance()->stopEdit(); /*QDialog::slotOk();*/
}

void EditorBase::setMainWidget(QWidget *mw)
{
    contentsLayout->replaceWidget(mainWidget,mw);
    mainWidget=mw;
}
