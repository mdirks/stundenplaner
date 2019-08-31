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

#include "pobjectcombobox.h"

#include <QDebug>
#include <QStringListModel>

FilterModel::FilterModel(RepositoryEntry *re)
        : QAbstractListModel ()
{
    rootFilter = new AbstractFilter();

    list<RepositoryProperty*> *list_prop = re->getAllProperties(true);
    v_filter=new vector<Filter*>(list_prop->size());

    list_prop->sort(NamedObjectPtrComp<RepositoryProperty>());
    unsigned int i=0;
    for(list<RepositoryProperty*>::iterator it = list_prop->begin(); it != list_prop->end(); it++){
        v_filter->at(i) = (*it)->getFilter();
        i++;
    }
}

int FilterModel::rowCount(const QModelIndex &parent) const
{
    return (int) v_filter->size();
}

QVariant FilterModel::data(const QModelIndex &index, int role) const
{
    /*

    */
    if (!index.isValid())
            return QVariant();

    if (index.row() >= v_filter->size())
            return QVariant();

    if (role == Qt::DisplayRole){
            Filter *f =  v_filter->at(index.row());
            return QVariant(f->getDisplayString().c_str());
            //return stringList.at(index.row());
    } else {
            return QVariant();
    }
}

Filter *FilterModel::filter(const QModelIndex &index) const
{
    if (!index.isValid())
            return nullptr;

    if (index.row() >= v_filter->size())
            return nullptr;

    Filter *f =  v_filter->at(index.row());
    return f;

}

Filter *FilterModel::getRootFilter() const
{
    return rootFilter;
}

Qt::ItemFlags FilterModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}


FilterEditorDelegate::FilterEditorDelegate(QObject *p)
 : QStyledItemDelegate(p)
{
    editorType=0;
}
QWidget *FilterEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const
{
    //const QAbstractItemModel *model = index.model();
    const FilterModel *fmodel=static_cast<const FilterModel*>(index.model());
    Filter *f = fmodel->filter(index);

    QWidget *editor=0;

    switch(f->type()){
        case 1: {const PObjectPropertyFilter *pofilter = dynamic_cast<const PObjectPropertyFilter*>(f);
                if(pofilter){
                    editor = new PObjectComboBox(pofilter->getPropertyType().c_str(), parent);
                } else {
                    editor = new QLineEdit("Unknown property", parent);
                }
                break;}
    default: { editor = new QLineEdit("MeinEditor", parent);
               break;}
    }
    return editor;
}

void FilterEditorDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{

    /*
    QString modelData = index.model()->data(index, Qt::EditRole).toString();

    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString value = lineEdit->text().append(modelData);
    lineEdit->setText(value);
    */
}

void FilterEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    const FilterModel *fmodel=static_cast<const FilterModel*>(index.model());
    Filter *f = fmodel->filter(index);
    switch(f->type()){
    case 1: {
        PObjectComboBox *pov = dynamic_cast<PObjectComboBox*>(editor);
        if(pov){
            PObject *o=pov->getCurrentObject();
            if(o){
                PObjectPropertyFilter *pof = dynamic_cast<PObjectPropertyFilter*>(f);
                if(pof){
                    pof->setValue(o);
                    fmodel->getRootFilter()->addAnd(f);
                }

            }
        }
        break;
    }
    default: break;
    }
    /*
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString value = lineEdit->text();
    model->setData(index, value, Qt::EditRole);
    */
}

void FilterEditorDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

FilterEditor::FilterEditor(RepositoryEntry *re, QWidget *parent)
    : QListView(parent)
{
    model=new FilterModel(re);
    setModel(model);
    setItemDelegate(new FilterEditorDelegate());
    show();


}

AbstractFilter* FilterEditor::getFilter()
{
    model->getRootFilter();

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

/*
void FilterEditor::addFilterFromChild(FilterEditorItem* fei)
{
	if(fei->getFilter()){
		rootFilter->addAnd(fei->getFilter());
		hasContents = true;
	}
}
*/

FilterEditor::~FilterEditor()
{
}

FilterEditorDialog::FilterEditorDialog(RepositoryEntry *re, QWidget *parent)
    : QDialog(parent)
{
	filterEditor = new FilterEditor(re,this);


    /*
    QStringList numbers;
    numbers << "One" << "Two" << "Three" << "Four" << "Five";

    QAbstractItemModel *model = new QStringListModel(numbers);
    */


    filterEditor->show();
    // ToDo: Does the editor show up, add it to layout ?
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
