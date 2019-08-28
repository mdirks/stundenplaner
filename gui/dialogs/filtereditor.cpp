/***************************************************************************
 *   Copyright (C) 2008 by Marcus Dirks   *
 *   m-dirks@web.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "filtereditor.h"
#include "orm/mapping/mappingcontroler.h"
#include "orm/mapping/abstractmapper.h"
#include "gui/forms/pobjectdialog.h"
#include "services/filter/pobjectpropertyfilter.h"
#include "services/utils/namedobjectptrcomp.h"

#include <QDebug>

FilterModel::FilterModel(RepositoryEntry *re)
{
    list_filter=new list<Filter*>();
    list<RepositoryProperty*> *list_prop = re->getAllProperties(true);
    list_prop->sort(NamedObjectPtrComp<RepositoryProperty>());
    for(list<RepositoryProperty*>::iterator it = list_prop->begin(); it != list_prop->end(); it++){
        list_filter->push_back((*it)->getFilter());
    }
}

int FilterModel::rowCount(const QModelIndex &parent) const
{
    return list_filter->size();
}

QVariant FilterModel::data(const QModelIndex &index, int role) const
{
    list<Filter*>::iterator it=list_filter->begin();
    for(int i=0; i<index.row(); i++)
        it++;
    return QVariant("unknown");
}

FilterEditorItem::FilterEditorItem(RepositoryProperty *rp, QListWidget *lw)
    : QListWidgetItem(rp->getName().c_str(),lw)
{
	this->rp = rp;
	filter = 0;
    setFlags(flags() | Qt::ItemIsEditable);
}

void FilterEditorItem::activate()
{
	if(rp->isPObject()){
		AbstractMapper *mapper = MappingControler::getInstance()->getMapperByName(rp->getType());
		if(mapper){
			PObject *o = PObjectDialog::choosePObject(mapper);
			if(o){
				filter = new PObjectPropertyFilter(rp,o);
			}
		}
	} else if(rp->isString()){
		//filter = new StringPropertyFilter(rp);
	} 
	if(filter){
        setText(filter->getValueString().c_str());
	}
}

PropertyFilter* FilterEditorItem::getFilter()
{
	return filter;
}

FilterEditorDelegate::FilterEditorDelegate(QObject *p)
 : QStyledItemDelegate(p)
{

}
QWidget *FilterEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit("Mein Editor", parent);
    return editor;
}

void FilterEditorDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString modelData = index.model()->data(index, Qt::EditRole).toString();

    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString value = lineEdit->text().append(modelData);
    lineEdit->setText(value);
}

void FilterEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString value = lineEdit->text();
    model->setData(index, value, Qt::EditRole);
}

void FilterEditorDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

FilterEditor::FilterEditor(RepositoryEntry *re, QWidget *parent)
    : QListWidget(parent)
{
	this->re = re;
    //root = new QListWidgetItem("Filter",this);
    //rootFilter = 0;
	hasContents=false;

	list<RepositoryProperty*> *list_prop = re->getAllProperties(true);
	list_prop->sort(NamedObjectPtrComp<RepositoryProperty>());
	for(list<RepositoryProperty*>::iterator it = list_prop->begin(); it != list_prop->end(); it++){
        new FilterEditorItem(*it,this);
	}
    //addColumn("Property");
    //addColumn("Filterwert");

    setItemDelegate(new FilterEditorDelegate());
}

AbstractFilter* FilterEditor::getFilter()
{
    qDebug() << "WARNING: FilterEditor::getFilter() not implemented";

    /*
    rootFilter = new AbstractFilter();
    QListWidgetItem *child = root->firstChild();
	FilterEditorItem *fei = dynamic_cast<FilterEditorItem*>(child);
	while(fei){
		addFilterFromChild(fei);
		fei = dynamic_cast<FilterEditorItem*>(fei->nextSibling());
	}
    */
}

void FilterEditor::addFilterFromChild(FilterEditorItem* fei)
{
	if(fei->getFilter()){
		rootFilter->addAnd(fei->getFilter());
		hasContents = true;
	}
}

FilterEditor::~FilterEditor()
{
}

FilterEditorDialog::FilterEditorDialog(RepositoryEntry *re, QWidget *parent)
    : QDialog(parent)
{
	filterEditor = new FilterEditor(re,this);
    // ToDO: Does the editor show up, add it to layout ?
    //setMainWidget(filterEditor);
}

AbstractFilter* FilterEditorDialog::getFilter()
{
	return filterEditor->getFilter();
}


/*!
    \fn FilterEditorDialog::createFilter(RepositoryEntry *re)
 */
AbstractFilter* FilterEditorDialog::createFilter(RepositoryEntry *re)
{
     FilterEditorDialog *instance = new FilterEditorDialog(re);
     instance->exec();
     return instance->getFilter();
}
