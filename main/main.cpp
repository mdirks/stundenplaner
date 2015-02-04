/***************************************************************************
                          main.cpp  -  description
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


#include <kaboutdata.h>
#include <klocale.h>
#include <kapplication.h>
#include <kcmdlineargs.h>

//#include "stundeplaner.h"
#include "orm/mapping/mappingcontroler.h"
#include "gui/base/guiconfig.h"
#include "gui/guirepository.h"
#include "datamodel/datamodelrepository.h"

#include <iostream>

using namespace std;

static const char *description =
	I18N_NOOP("StundePlaner");
// INSERT A DESCRIPTION FOR YOUR APPLICATION HERE
	
/*
static KCmdLineOptions options[] =
{
  { "+Database", I18N_NOOP("database to open"), 0 },
  //{ 0, 0, 0 },
  //{ "d <datbasename>",I18N_NOOP("database to open"), 0 } // INSERT YOUR COMMANDLINE OPTIONS HERE
};
*/

/**
	\mainpage

	


	A meaningfull global documentation is still missing.

	
	\todo xml-Formulare
	


	\section Common-Tasks

	\subsection General 

		- Konfiguration
			
	
	\subsection Persistence

		- Create an instance of a persistent type
			<pre>
		className* newObject = (className*) CreateAction::getInstance()->create(className);
			</pre>	

		- Add a new persistent class
			- Declare / define the class
			- Allowed property types: 
				- plain: type getProperty(), setProperty(type )
				- reference (PObject): type* getProperty(), setProperty(type* )
				- association (PObject collection): list<<type*>> getProperty(), addToProperty(type* ), deleteFromProperty(type*)
			- Add an entry to the persistence.xml in the package
			- MappingGenerator will generate a mapping class

		- Add a new persistent property type
			- Make it writable to std::stringstream by declaring an appropriate template in utils.h
			- Define an appropriate RepositoryProperty

		- Get the class name of a given object
			- o->getPersistenceObject()->getClassName()


		

	\subsection GUI

		- Standard form: PObjectEditor2 (fixed in GuiRepositoryImpl::showFormForObject())

		- Show a form for a given object
			- call GuiRepository::showFormForObject(PObject *o)

		- Add a Formular to the system
			- Declare / define the corresponding widget
			- Modifie GuiRepositoryImp::showFormForObject() to handel your form

		- Edit a persisten (PObject) Property 
			- in addition to the object get the RepositoryProperty for the property to be edited
			- according to the property type use one of the Editors: StringEditor, TextPropertyEditor, DateEditor, PObjectIconView
			- all Gui/Transaction is handeled by those

		- Icons
			- handeled on class-basis 
			- 

	\subsection Repository

		- Get properties of a given object

			<pre>
		RepositoryEntry *re=Repository::getInstance()->getRepositoryEntry(mo);
		list<RepositoryProperty*> *properties = entry->getAllProperties(true);
		for(list<<RepositoryProperty*>>::iterator it=properties->begin(); it != properties->end(); it++){
			RepositoryProperty *prop = (*it);
...
		}
			</pre>

	\subsection Test
*/

int main(int argc, char *argv[])
{

        cout << "TEST";
    /*
	KAboutData aboutData( "stundeplaner", I18N_NOOP("StundePlaner"),
		"0.1", description, KAboutData::License_GPL,
		"(c) 2004, Marcus Dirks", 0, 0, "marcus.dirks@web.de");
	aboutData.addAuthor("Marcus Dirks",0, "marcus.dirks@web.de");
    */
    KCmdLineArgs::init( argc, argv,QByteArray("stundenplaner"),QByteArray(),ki18n("Stundenplaner"), QByteArray("2.0"));
    KCmdLineOptions options;
    options.add("+Database",  ki18n("database to open"));

	KCmdLineArgs::addCmdLineOptions( options ); // Add our own options.
 
    KApplication app;
    GuiRepository::showSplashScreen();

    QLocale::setDefault(QLocale::German);
    //setenv("LC_ALL","de_DE.UTF-8");
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
    MappingControler::setDatabaseName(args->arg(0));
    MappingControler::getInstance();

    GuiConfig::getInstance()->setDatabaseName(args->arg(0));

   
    DataModelRepository::getInstance();
    GuiRepository *rp=GuiRepository::getInstance();
    rp->initGui();

   
    /*
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
		
		if (args->count())
		{
        stundeplaner->openDocumentFile(args->arg(0));
		}
		else
		{
		  stundeplaner->openDocumentFile();
		}
		args->clear();
  }
  */
  GuiRepository::hideSplashScreen();
  
    app.exec();

	return 0;
}  
