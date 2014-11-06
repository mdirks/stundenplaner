//
// C++ Interface: mapperview
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MAPPERVIEW_H
#define MAPPERVIEW_H

#include "orm/mapping/abstractmapper.h"

#include <QListWidget>
#include <KDialog>

#include "orm/mapping/abstractmapper.h"

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class MapperView : public QListWidget
{
public:
    MapperView(QWidget *parent=0, QStringList classList=QStringList());
    ~MapperView();

    AbstractMapper* getSelectedMapper();

};


class MapperViewItem : public QListWidgetItem
{
public:
	MapperViewItem(AbstractMapper *mapper, MapperView *parent);
	AbstractMapper* getMapper();
	
private:
	AbstractMapper *mapper;
};

#endif


class MapperDialog : public KDialog
{
public:
	MapperDialog(QWidget *parent=0L, QStringList classList=QStringList());
	AbstractMapper* getSelectedMapper();

	static AbstractMapper* chooseMapper(QStringList classList=QStringList());

private:
	MapperView *mapperView;
};
