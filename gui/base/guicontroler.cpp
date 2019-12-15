//
// C++ Implementation: guicontroler
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "guicontroler.h"

#include <QDebug>

GuiControler* GuiControler::instance=0;

GuiControler* GuiControler::getInstance(){
   if(!instance){
     instance = new GuiControler();
   }
   return instance;
}

void GuiControler::setInstance(GuiControler *controler)
{
	instance=controler;
}


GuiControler::GuiControler()
{
	activeEditors=new list<PropertyEditor*>();
}


GuiControler::~GuiControler()
{
}


void GuiControler::addActiveEditor(PropertyEditor *editor)
{
     	
	activeEditors->push_back(editor);
}

void GuiControler::stopEdit()
{
    mymutex.lock();
    if(activeEditors){
        for(list<PropertyEditor*>::iterator it = activeEditors->begin(); it != activeEditors->end(); it++){
            if((*it)){
                (*it)->stopEdit();
            } else {
                qDebug() << QString("GuiControler::stopEdit : !!! Invalid editor in editor-list");
		}
	}
	activeEditors->clear();
   }
   mymutex.unlock();
}

