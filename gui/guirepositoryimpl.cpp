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
#include "stundeplaner.h"
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
#include "gui/actions/modelesenmapper.h"
#include "gui/actions/modematerail.h"
#include "gui/actions/servicelatex.h"
#include "gui/actions/modelernen.h"
#include "gui/actions/servicexml.h"
#include "gui/actions/modenotes.h"
#include "gui/actions/servicepdf.h"

#include <QPixmap>
//#include <qscrollview.h>
#include <QMessageBox>
#include <QWidget>

#include <KParts/ComponentFactory>
#include <KXMLGUIFactory>
#include <kglobal.h>
#include <kconfig.h>
#include <kiconloader.h>
#include <kicondialog.h>
#include <ktrader.h>
#include <klibloader.h>
#include <kmessagebox.h>
//#include <kservice.h>
//#include <kservicetypetrader.h>




GuiRepositoryImpl* GuiRepositoryImpl::impl_instance=0;
//static GuiRepositoryImpl::QWorkspace* formWorkspace=0;


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
	listMappers->push_back(PObjectGraphicsItemmapper::getInstance());
	listMappers->push_back(PlatzGraphicsItemmapper::getInstance());
	listMappers->push_back(SchultagGraphicsItemmapper::getInstance());
	listMappers->push_back(DayMapmapper::getInstance());
        listMappers->push_back(WeekMapmapper::getInstance());
	listMappers->push_back(SitzplanMapmapper::getInstance());
	listMappers->push_back(GuiObjectmapper::getInstance());
    listMappers->push_back(ModeLesenmapper::getInstance());
	
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
		/*	
		if(! form->icon()){
			qDebug("GuiRepositoryImpl::showFromForObject(): Found form  without icon: Resetting empty one");
			form->setIcon(std_icon_pixmap);
		}
		*/
		
		//wrappWidgetAndAdd(form);
		string objectName = o-> getName();
		string className = o->getPersistenceObject()->getClassName();
		
        /*
        KMdiChildView *childView =0;
		qDebug(QString("Creating wrapper for %1, %2").arg(className).arg(objectName));
        childView = stundeplaner->createWrapper(form, objectName, objectName);
		childView->setIcon(GuiConfig::getInstance()->getIcon(className));
		if( ! childView->icon()){
		 qDebug("Warning child view has no icon !!");
		}
		if(childView != 0){
			qDebug("Adding childView ...");
			stundeplaner->addWindow(childView);
			qDebug("..done");
		} else {
			qWarning("Failed to create child window");
		}
        */
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
	
    KDialog *dialog = new KDialog(stundeplaner);
	QWidget *form=0;

    //Transactions::getCurrentTransaction()->add(o); // hack because some editors do not commit properly

    if(rp){
	if(rp->isString()){
        StringEditor *se= new StringEditor(o,rp,dialog);
        connect(dialog,SIGNAL(okClicked()),se,SLOT(stopEdit()));
        form=se;
	} else if(rp->isText()){
        TextPropertyEditor *pe = new TextPropertyEditor(o,rp,dialog);
        connect(dialog,SIGNAL(okClicked()),pe,SLOT(stopEdit()));
        form=pe;
	} else if(rp->isNumeric()){
		form = new StringEditor(o,rp,dialog);
	} else if(rp->isPObject()){
		form = getFormForObject(rp->asPObject(o), dialog);
	} else if(rp){
        form = new QLabel(QString("%1 : unknown editor type").arg(rp->getName().c_str()),dialog);
	} else {
		form = new QLabel(QString("empty property"),dialog);
	}
    }

	dialog->setMainWidget(form);
	dialog->exec();	
}
/*!
    \fn GuiRepositoryImpl::setFormWorkspace(QWorkspace *w)
 */
void GuiRepositoryImpl::setFormWorkspace(QWorkspace *w)
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
    stundeplaner = new StundePlanerApp();

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

	if(GuiConfig::getInstance()->getActiveSchuljahr() == 0){
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


    /*
	if(MappingControler::getInstance()->isOpen()){
		AbstractMapper *mapper = MappingControler::getInstance()->getMapperByName("klasse");
		if(mapper){
			PObjectIconView *iconView = new PObjectIconView(mapper);
            iconView->load();
            addTool(iconView,
                    QString::fromStdString(mapper->getClassName()),
                    QString::fromStdString(mapper->getClassName()));
			//iconView->load(); //laizy load on show
			activeIconViews->push_back(iconView);
		}
		mapper = MappingControler::getInstance()->getMapperByName("ThemaMap");
		if(mapper){
			PObjectIconView *iconView = new PObjectIconView(mapper);
			
            addTool(iconView,
                    QString::fromStdString(mapper->getClassName()),
                    QString::fromStdString(mapper->getClassName()),
                    Qt::LeftDockWidgetArea);
			//iconView->load(); //laizy load on show
			activeIconViews->push_back(iconView);
		}

        //showFormForObject(SKalender::getInstance()->getDay(QDate::currentDate()));
        //showFormForObject(GuiObject::getInstance()->getDashBoard());
        //showFormForObject(SKalender::getInstance(),true);
		
	} 
    */



	GuiControler::setInstance(this);
	GuiObjectFactory::setInstance(new GuiObjectFactoryImpl());
	FormsPopupFactory::setInstance(GuiPopupFactory::getInstance());
	MapviewsPopupFactory::setInstance(GuiPopupFactory::getInstance());
	PObjectTableControlerFactory::setInstance(new PObjectTableControlerFactoryImpl());

    addMode(ModePlanung::getInstance());
    addMode(ModeLesen::getInstance());
    addMode(ModeMaterial::getInstance());
    addMode(new ModeLernen());
    addMode(new ModeNotes());
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
        if(activeMode) activeMode->tearDownMode();
        activeMode=mode;
        mode->setupMode();
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


KParts::Part* GuiRepositoryImpl::getPdfPart(QWidget* parent)
{	
	return getPart(parent, "application/pdf", "'KParts/ReadOnlyPart' in ServiceTypes");
}

KParts::Part* GuiRepositoryImpl::getPart(QWidget* parent, QString mimetype, QString qs2)
{
    KParts::Part* part=0;

    part = KParts::ComponentFactory::createPartInstanceFromQuery<KParts::ReadOnlyPart>(
                mimetype, QString(), parent);
    /*
    if ( part ) {
        part->openUrl( url );
        part->widget()->show(); // also insert the widget into a layout, or simply use a KVBox as parentWidget
    }
    */
    QString message("Found %1");
    if(part){
        message=message.arg("part");
    } else {
        message=message.arg("nothing");
    }
    /*
    KTrader::OfferList offers = KTrader::self()->query(qs1,qs2);
	KLibLoader* loader = KLibLoader::self();

	QString message("Found ");	

	for (uint i = 0; i < offers.count(); ++i)
	{
		KLibFactory* factory = loader->factory(offers[i]->library());
		if (factory != 0 )//&& factory->inherits("KParts::Factory"))
		{
			 p = static_cast<KParts::ReadOnlyPart* >( factory->create(getMainFrame(), offers[i]->name(), "KParts::ReadOnlyPart"));
 	            
            if (p != 0 ) //&& p->inherits("MyPart"))
			{
				message = message.append(offers[i]->name()).append(", ");
				break;
            }
			
		}else {
	 	        KMessageBox::error(getMainFrame(),"Could not find a suitable HTML component");
	        }
	}
    */

	KMessageBox::error(getMainFrame(),message);
	


	/*
	KService::List services ;
	KServiceTypeTrader* trader = KServiceTypeTrader::self();
	
	QString constraint = "'text/plain' in MimeTypes and "
			"('KOfficePart' in ServiceTypes or "
			" 'oasis' ~ [X-KDE-ExtraNativeMimeTypes])";
	services = trader->query("KParts/ReadWritePart", constraint);
	
	foreach (KService::Ptr service, services) {
	kDebug() << "read write part" << service->name();
	}
	*/
    return part;
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
    //KMdiChildView *childView = stundeplaner->createWrapper(tool, label, short_label);
    stundeplaner->addDockWindow( tool, short_label,area);
}

void GuiRepositoryImpl::addTypeView(list<PObject*>* list, QString label, QString short_label){
    qDebug() << "Warning: GuiRepositoryImpl::addTypeView not implemented";
    /*
    PObjectListBox *listBox = new PObjectListBox();
	listBox->addObjects(list);
	addTool(listBox,label,short_label);
    */
}

/*!
    \fn GuiRepositoryImpl::wrappWidget(QWidget *w)
 */
void GuiRepositoryImpl::wrappWidgetAndAdd(QWidget *pNewView)
{
    /*
    KMdiChildView* pMDICover = new KMdiChildView( pNewView->caption());
          QBoxLayout* pLayout = new QHBoxLayout( pMDICover, 0, -1, "layout");
          pNewView->reparent( pMDICover, QPoint(0,0));
          pLayout->addWidget( pNewView);
          pMDICover->setName( pNewView->name());
   	QString shortName = pNewView->caption();
   	int length = shortName.length();
  	 shortName = shortName.right(length - (shortName.findRev('/') +1));
   	pMDICover->setTabCaption( shortName);
   	pMDICover->setCaption(pNewView->caption());

   	int flags = KMdi::StandardAdd;
    */

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

QPixmap GuiRepositoryImpl::loadIcon(QString iconName, KIcon::Group group)
{
	KIconLoader *loader = KGlobal::iconLoader();
	return loader->loadIcon(iconName, group);
}


QPixmap GuiRepositoryImpl::getIcon(QString name, KIcon::Group group)
{
	KIconLoader *loader = KGlobal::iconLoader();
	map<QString,QString>::iterator it = mapIcons.find(name);
	if(it != mapIcons.end()){
		QString iconName = it->second;
		return loader->loadIcon(iconName, group);
		qDebug(QString("Map: Found icon %1 for %2").arg(iconName).arg(name));
	} else {
		//KConfig *config = KGlobal::config();
		//config->setGroup("Gui");
		//QString iconName = config->readEntry(name.append("_icon"),"unknown");
		QString iconName = GuiConfig::getInstance()->readEntry("Gui",name.append("_icon"));
		mapIcons[name]=iconName;
		qDebug(QString("Config: Found icon %1 for %2").arg(iconName).arg(name));
		
		return loader->loadIcon(iconName,group);
	}
}

QPixmap GuiRepositoryImpl::getIcon(PObject *o, KIcon::Group group)
{
    KIconLoader *loader = KGlobal::iconLoader();
    if(o && o->getPersistenceObject()){
	QString className(o->getPersistenceObject()->getClassName());
	return getIcon(className,group);
    } else {
        qDebug("Warning: getPersistenceObject failed for object");
    	return loader->loadIcon("kfind",group);
    }
    
   
}

QPixmap GuiRepositoryImpl::getIcon(RepositoryProperty *rp, KIcon::Group group)
{
	if(rp->isCollection()){
		return getIcon("Collection", group);
	} else if (rp->isString()){
		return getIcon("String", group);
	} else if (rp->isText()){
		return getIcon("Text", group);
	} else {
		return getIcon("Unknown", group);
	}
}


void GuiRepositoryImpl::selectIcon(PObject *o)
{
	QString className(o->getPersistenceObject()->getClassName());
	selectIcon(className);
}

void GuiRepositoryImpl::selectIcon(QString name)
{
	QString iconName = KIconDialog::getIcon();
	mapIcons[name] = iconName;
	
	KConfig *config = KGlobal::config();
	config->setGroup("Gui");
	config->writeEntry(name.append("_icon"), iconName);
}


void GuiRepositoryImpl::selectIcon(RepositoryProperty *rp)
{
	QString type;
	if(rp->isCollection()){
		type = "Collection";
	} else if (rp->isString()){
		type = "String";
	} else if (rp->isText()){
		type = "Text";
	} else {
		type = "Unknown";
	}
	
	selectIcon(type);
}


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
/*KXmlGuiWindow**/ QMainWindow* GuiRepositoryImpl::getMainFrame()
{
    return mainFrame;
}

void  GuiRepositoryImpl::setMainFrame(QMainWindow /*KXmlGuiWindow*/ *mf)
{
     this->mainFrame = mf;
}

/*!
    \fn GuiRepositoryImpl::getPopup(QString identifier)
 */

QMenu* GuiRepositoryImpl::getPopup(QString identifier)
{
    QMenu *popup = new QMenu();
    /*
    QWidget *w =0;
    if(getMainFrame()){
        QWidget *w = getMainFrame()->guiFactory()->container(identifier, getMainFrame());
        if(w){
            popup= static_cast<QMenu*>(w);
        }
    }

    if(!popup){
        qDebug() << "Failed to get widget from xml";
	}
    */
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
    SKalender::close();

    for(list<GuiMode*>::iterator it = modelist->begin(); it!=modelist->end(); it++)
    {
        (*it)->close();
    }
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
