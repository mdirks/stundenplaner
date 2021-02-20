//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "textpropertyeditor.h"
#include "gui/guirepository.h"
#include "gui/base/guicontroler.h"
#include "orm/transactions/transactions.h"
#include <QTextStream>

TextPropertyEditor::TextPropertyEditor(QWidget *parent)
 : QTextEdit(parent) , property(0)
{
    editing=false;

    connect(this,SIGNAL(textChanged()),this,SLOT(startEdit()));
    setLineWrapMode(QTextEdit::NoWrap);

    lEdit=new QLabel("editing",this);
    lEdit->hide();
}

TextPropertyEditor::TextPropertyEditor(PObject *o, RepositoryProperty *prop, QWidget *p)
 : QTextEdit(p), property(prop), parent(o)
{
    editing=false;

    setLineWrapMode(QTextEdit::NoWrap);
    setText(property->asString( parent ).c_str());
    connect(this,SIGNAL(textChanged()),this,SLOT(startEdit()));

    lEdit=new QLabel("editing",this);
    lEdit->hide();

}


TextPropertyEditor::TextPropertyEditor(PObject *o, QString displayString, QWidget *p)
 : QTextEdit(p), property(0), parent(o)
{
    editing=false;
    setLineWrapMode(QTextEdit::NoWrap);
    setText(displayString);
    connect(this,SIGNAL(textChanged()),this,SLOT(startEdit()));

    lEdit=new QLabel("editing",this);
    lEdit->hide();

}



TextPropertyEditor::~TextPropertyEditor()
{
}




/*!
    \fn TextPropertyEditor::startEdit(RepositoryProperty *prop, PObject *o)
 */
void TextPropertyEditor::startEdit(RepositoryProperty *prop, PObject *parent)
{
    this->property = prop;
    this->parent = parent;
    setLineWrapMode(QTextEdit::NoWrap);
    setText(property->asString( parent ).c_str());
}

void TextPropertyEditor::startEdit()
{
    if(!editing){
        GuiControler::getInstance()->addActiveEditor(this);
        setEditing(true);
        //editing = true;
        if(property && parent){
            Transactions::getCurrentTransaction()->add(property->getTrueParent(parent));
        }
	}
}

QString TextPropertyEditor::getText()
{
    setTextToParent();
    return toPlainText().toUtf8();
}

void TextPropertyEditor::setEditing(bool edit)
{
    if(edit){
        lEdit->show();
    } else {
        lEdit->hide();
    }
    editing=edit;
}

void TextPropertyEditor::stopEdit()
{
    if(property && parent){
        setTextToParent();
	}
    setEditing(false);
    //editing = false;
	
	//clear();
}

void TextPropertyEditor::setTextToParent()
{
    QString text = toPlainText();
    property->fromString(text.toStdString(),parent);
    /*
    QString text = toPlainText();
    QTextStream str(&text);
    property->fromString(str.readAll().toStdString(), parent);
    parent->save();
    */
}


/*!
    \fn TextPropertyEditor::focusOutEvent(QFocusEvent *e)
 */
void TextPropertyEditor::focusOutEvent(QFocusEvent *e)
{
	//qDebug("TextPropertyEditor: focusOutEvent");
       //stopEdit();
}

void TextPropertyEditor::setProperty(RepositoryProperty *rp)
{
    this->property = rp;
}

void TextPropertyEditor::setParentObject(PObject *po)
{
    //consider a previous Parent having been edited
    stopEdit();

    this->parent=po;
    if(property && po){
        setText(property->asString( parent ).c_str());
    } else {
        clear();
    }
}
