//
// C++ Interface: guicontroler
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GUICONTROLER_H
#define GUICONTROLER_H

#include "propertyeditor.h"
#include <list>

#include <qobject.h>

using namespace std;
/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class GuiControler : public QObject {
public:
    static GuiControler* getInstance();
    static void setInstance(GuiControler *controler);
    

    void addActiveEditor(PropertyEditor *editor);
    void stopEdit();

public slots:
	virtual void showFormForObject(PObject*){qDebug("GuiControler::showFormForObject : Warning : do nothing implementation ");};
	virtual void showDialogForObject(PObject*){qDebug("GuiControler::showFormForObject : Warning : do nothing implementation ");};

protected:
     GuiControler();
    ~GuiControler();

private:
    
    static GuiControler* instance;
    list<PropertyEditor*> *activeEditors;

};

#endif
