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
#include "propertyitem.h"
#include "gui/base/guiconfig.h"


PropertyItem::PropertyItem(QListWidgetItem *parent, RepositoryProperty *rp, PObject *mo)
 : QListWidgetItem()
{
	this->rp = rp;
	this->mo = mo;
    // todo : setPixmap(0, GuiConfig::getInstance()->getIcon(rp));
}


PropertyItem::~PropertyItem()
{
}


QString PropertyItem::text ( int column ) const
{
    return QString(rp->getName().c_str()).append(": ").append(rp->asString( mo ).c_str());
}


RepositoryProperty* PropertyItem::getRepositoryProperty()
{
	return rp;
}

/*!
    \fn PropertyItem::getParent()
 */
PObject* PropertyItem::getParent()
{
    return mo;
}
