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
#include "actionitem.h"

int ActionItem::Rtti = 1001;

ActionItem::ActionItem(QListWidgetItem *parent)
 : QListWidgetItem()
{
}


ActionItem::~ActionItem(){}

int ActionItem::rtti() const
{
	return ActionItem::Rtti;
}


