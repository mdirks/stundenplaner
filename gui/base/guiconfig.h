//
// C++ Interface: config
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GUICONFIG_H
#define GUICONFIG_H

#include "datamodel/schuljahr.h"
#include "datamodel/tutorium.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/persistence/pobject.h"

#include <QString>
#include <QPixmap>
#include <QWidget>



#include <map>

using namespace std;
/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class GuiConfig{
public:
    GuiConfig();
    ~GuiConfig();

   static GuiConfig* getInstance();

   QString readEntry(QString group, QString name);
   void writeEntry(QString group, QString name, QString entry);


   QPixmap loadIcon(QString iconName);

    QPixmap getIcon(RepositoryProperty *rp) ;
    QPixmap getIcon(PObject *o);
    QPixmap getIcon(QString className) ;

    void selectIcon(QString name); 
    void selectIcon(PObject *o);
    void selectIcon(RepositoryProperty *rp);
    QDate getCurrentTermEnd();
    QDate getCurrentTermStart();
    void setCurrentTermEnd(QDate date);
    void setCurrentTermStart(QDate date);
    QString getDatabaseName();
    void setDatabaseName(QString dbName);
    QStringList getDisplayProperties(QString guiObjectIdentifier);
    void setDisplayProperties(QString guiObjectIdentifier, QStringList properties);
    schuljahr* getActiveSchuljahr();
    void setActiveSchuljahr(schuljahr *sj);
    tutorium* getActiveTutorium();
    void setActiveTutorium(tutorium *tu);

   //QWidget* getEditor(PObject *o, RepositoryProperty *rp, QWidget *parent=0);

private:
	static GuiConfig *instance;
	map<QString, QString> mapIcons;
	QDate termEnd, termStart;
	schuljahr *activesj;
	tutorium *activetut;

};

#endif
