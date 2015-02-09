//
// C++ Implementation: pobjectlabel
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pobjectlabel.h"
#include "gui/base/guiconfig.h"

#include "pobjectdialog.h"
#include "pobjecticonview.h" //for pobjecticonviewdrag
#include "orm/mapping/mappingcontroler.h"

#include <qlayout.h>
#include <QDebug>
#include <QDropEvent>


PObjectLabel::PObjectLabel(RepositoryProperty *prop, PObject *o, QWidget *p, bool with_icon, bool with_buttons, bool with_text)
	: my_object(o), QWidget(p), AbstractPropertyEditor(o,prop), with_icon(with_icon), with_buttons(with_buttons), with_text(with_text)
{
	QHBoxLayout *layout = new QHBoxLayout(this);

	
	if(with_icon){
		label_pix = new QLabel(this);
        QPixmap pmap;
        if(prop){
            pmap = GuiConfig::getInstance()->getIcon( prop->getType().c_str() );
		} else if(o){
            pmap = GuiConfig::getInstance()->getIcon( o->getPersistenceObject()->getClassName().c_str());
		}
        pmap=pmap.scaledToHeight(20);
        label_pix->setPixmap(pmap);
		layout->addWidget(label_pix);
	}


	label= new QLabel(this);
    //label->setFont(QFont("Helvetica [Cronyx]", 13, QFont::Bold ));
	label->setEnabled(true);

	if(with_text){
		layout->addWidget(label,10,Qt::AlignHCenter);
	} else {
		label->hide();
	}
	
	

	
	if(with_buttons){
		editButton = new QPushButton(this);
		editButton->setText("E");
		chooseButton = new QPushButton(this);
		chooseButton -> setText("W");

		layout->addWidget(chooseButton);
		layout->addWidget(editButton);

		connect(chooseButton,SIGNAL(clicked()),this,SLOT(chooseObject()));
		connect(editButton,SIGNAL(clicked()),this,SLOT(editObject()));
	}

	/*
	if(with_icon){
		label->setIcon(GuiConfig::getInstance()->getIcon(AbstractPropertyEditor::property));
	}
	*/
	setLabelText();

	
	//connect(this,SIGNAL(dropped( QDropEvent *, const QValueList<QIconDragItem> & )), this, SLOT( handleDrop(QDropEvent *)));
	//if(o){ startEdit(prop,o);}
	//this->edit_o=o;
	setAcceptDrops(TRUE);
}

void PObjectLabel::chooseObject(){
	AbstractPropertyEditor::startEdit();
 	if(AbstractPropertyEditor::property){
		string className = AbstractPropertyEditor::property->getType();
		PObject *o = PObjectDialog::choosePObject(MappingControler::getInstance()->getMapperByName( className ) );
		setObject(o);
		/*
		if(o){
			AbstractPropertyEditor::property->set(o,AbstractPropertyEditor::parent);
			setLabelText();
		} else { qDebug("PObjectLabel::editObject(): Could not get Object from editor");}
		*/
	}
}


void PObjectLabel::editObject(){
	AbstractPropertyEditor::startEdit();
	PObject *o = getObject();
	if(o){
		editRequestor->requestDialog(o);
	} else {
        qDebug() << "PObjectLabel::editObject(): No object to edit";
	}
}

void PObjectLabel::setLabelText(){
    qDebug() << "Setting label";
	PObject *o=getObject();
	if(o){
        /*
        if(with_icon){
			label_pix->setPixmap(GuiConfig::getInstance()->getIcon(o));
		}
        */
        label->setText(o ->getName().c_str());
        qDebug() << QString("Setting label to %1").arg(o->getName().c_str());
	} else {
		label->setText("Leer");
	}
}

PObject* PObjectLabel::getObject(){
	PObject *result = 0;
	if(AbstractPropertyEditor::property){
        result =  AbstractPropertyEditor::property->asPObject( AbstractPropertyEditor::parentObject);
	} else if(my_object){
		return my_object;
	}
	return result;
}

PObjectLabel::~PObjectLabel()
{
}


void PObjectLabel::startEdit(RepositoryProperty *prop, PObject *o)
{
	
	setLabelText();
	if(with_icon){
        label->setPixmap(GuiConfig::getInstance()->getIcon(AbstractPropertyEditor::property));
	}

	AbstractPropertyEditor::startEdit();
}



void PObjectLabel::stopEdit()
{
	AbstractPropertyEditor::stopEdit();
	qDebug("PObjectLabel: parent saved");
}

void PObjectLabel::dropEvent(QDropEvent *e)
{
    qDebug() << "PObjectLabel::handleDrop";
    PObject *o = PObjectData::decode(e->mimeData()->data("application/pobject"));
    e->accept();
    if(o){
		AbstractPropertyEditor::startEdit();	
		setObject(o);
	} else {
		qDebug("PObjectLabel::handleDrop : decode of object failed");
	}	
		
	/*
	} else if(PObjectIconViewDrag::canDecode(e,clName)){
		//PObjectIconViewItem *item = PObjectIconViewDrag::decode(e,this);
		PObject *o = PObjectDrag::decode(e);
		addObject(o);
	} */
	
}

/*
QDragObject* PObjectLabel::dragObject()
{
	PObjectDrag *drag=0;

	
		PObject *o = getObject();
		if(o){
			drag = new PObjectDrag(o,this);
        } else {
			qDebug("PObjectView::dragObject() : drag failed, could not get selected objecct");
		}
	

	return drag;
}
*/

/*!
    \fn PObjectLabel::setObject(PObejct *o)
 */
void PObjectLabel::setObject(PObject *o)
{
    //if(o){
    qDebug() << QString("PObjectLabel::dragLeaveEvent: setObject to %1").arg((long) o);
    AbstractPropertyEditor::property->set(o,AbstractPropertyEditor::parentObject);
	setLabelText();
	emit objectChanged();
}

void PObjectLabel::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("application/pobject"))
    {
        e->acceptProposedAction();
    }
	
}

void PObjectLabel::dragLeaveEvent ( QDragLeaveEvent * )
{
	dragging = false;
	
	AbstractPropertyEditor::startEdit();
	setObject((PObject*)0);
	qDebug("PObjectLabel::dragLeaveEvent: setObject to 0");
}

void PObjectLabel::mouseMoveEvent ( QMouseEvent * e )
{
	if(!dragging){
		dragging = true;
        QDrag *d = new QDrag(this);
        QMimeData *md = new PObjectData(getObject(),this);
        d->setMimeData(md);

        d->exec();
        e->accept();
	}
}

void PObjectLabel::mouseReleaseEvent ( QMouseEvent * e )
{
	dragging = false;
}

void PObjectLabel::mouseDoubleClickEvent ( QMouseEvent * e )
{
	editObject();
}
