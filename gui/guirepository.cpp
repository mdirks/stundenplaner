//
// C++ Implementation: guirepository
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "guirepository.h"
#include "guirepositoryimpl.h"
#include "splashscreenimpl.h"


GuiRepository* GuiRepository::instance = 0;
SplashScreen* GuiRepository::splash = 0;

GuiRepository* GuiRepository::getInstance(){
   if(!instance){
     instance = GuiRepositoryImpl::getInstance();
   }
   return instance;
}

/*
void GuiRepository::showFormForObject(PObject *o)
{
	qWarning("showFormForObject not implemented");
}
*/

/*!
    \fn GuiRepositoryImpl::getSplashScreen()
 */
SplashScreen* GuiRepository::showSplashScreen()
{
     if(splash == 0){ 
        QPixmap pm("gui/splash.png");
	splash = new SplashScreenImpl( pm );
     }
     splash->show();
     return splash;
}

void GuiRepository::hideSplashScreen()
{
   if(splash!=0){
  	splash->hide();
 
	//delete splash;
	splash=0;
	
   }
}

