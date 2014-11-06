//
// C++ Interface: pobjectlabel
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef POBJECTLABEL_H
#define POBJECTLABEL_H

#include "abstractpropertyeditor.h"
#include "orm/persistence/pobject.h"
#include "gui/base/editrequestor.h"

#include <QLabel>
#include <QPushButton>
#include <QDrag>
//#include <qdragobject.h>



/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class PObjectLabel : public QWidget,  public AbstractPropertyEditor
{
Q_OBJECT


public:
     //PObjectLabel();
     PObjectLabel(RepositoryProperty *prop, PObject *o=0, QWidget *p=0, bool with_icon=true, bool with_buttons=true, bool with_text=true);
    ~PObjectLabel();

     void startEdit(RepositoryProperty *prop, PObject *o);
    void stopEdit();
    void setObject(PObject *o);
    //QDrag* dragObject();

protected:
	void dragEnterEvent(QDragEnterEvent *e);
	void dragLeaveEvent ( QDragLeaveEvent * );
	void dropEvent(QDropEvent *e);
	void mouseMoveEvent ( QMouseEvent * e );
	void mouseReleaseEvent ( QMouseEvent * e );
	void mouseDoubleClickEvent ( QMouseEvent * e );

signals:
	void objectChanged();

public slots:
	void chooseObject();
	void editObject();
	//void handleDrop(QDropEvent *e);

private:
	PObject* getObject();
	void setLabelText();



private:
	QLabel *label, *label_pix;
	QPushButton *editButton, *chooseButton;
	//PObject *edit_o;
	bool with_icon, with_buttons, with_text, dragging;
	PObject *my_object;

};

#endif
