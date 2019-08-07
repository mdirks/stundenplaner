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
//#include "pobjectdrag.h"
#include "pobjectdata.h"

#include <cstring>

#include <QString>
#include <QDebug>
//#include <qcstring.h>

#include "orm/persistence/database.h"

using namespace std;

PObjectData::PObjectData(PObject *o, QWidget *source)
 : QMimeData()
{
	//this->o=o;
    if(o){
        className = o->getPersistenceObject()->getClassName().c_str();
        typedMimeType=QString("application/pobject/").append(className);
        id  = o->getID();
    } else {
        qDebug() << "WARNING: PObjectData : given object is Null";
    }
}


PObjectData::~PObjectData()
{
}



 
/*
QByteArray PObjectDrag::encodedData(const char* mimetype) const
{
	if(strcmp(mimetype,"application/pobject")==0){
		QString string_rep=QString(o->getPersistenceObject()->getClassName()).append(",%1").arg(o->getID());
		
		return string_rep.utf8();
		/*
		const char* str = string_rep.ascii();
		QByteArray ba;
		ba.assign(str,string_rep.length());
		return ba.copy();
		*//*
	} else {
		qDebug(QString("PObjectDrag::encodedData : cannot encode to %1").arg(mimetype));
	}
}
*/

QByteArray PObjectData::data(const QString &mimetype) const
{
    if(mimetype == QString("application/pobject")){
        QString string_rep=QString(className).append(",%1").arg(id);
        qDebug() << QString("PObjectDrag: Encode object as : ").append(string_rep);
        return string_rep.toUtf8();
	} else if (typedMimeType == QString(mimetype)){
        QString string_rep=QString(className).append(",%1").arg(id);
        qDebug() << QString("PObjectDrag: Encode object as : ").append(string_rep);
        return string_rep.toUtf8();

	} else {
        qDebug() << QString("PObjectDrag: Cannot ask  QIconDrag to encode for : ").append(mimetype);
		//return QIconDrag::encodedData(mimetype);
		//qDebug(QString("PObjectDrag::encodedData : cannot encode to %1").arg(mimetype));
	}
}


bool PObjectData::hasFormat(const QString &type)
{
    return type.compare("application/pobject") == 0;
	//return true;
}

PObject* PObjectData::decode(QByteArray ba)
{
    //QByteArray ba = data("application/pobject");
	QString str_rep(ba);
    qDebug() << str_rep;
	int id = str_rep.section(",",1,1).toInt();
	QString className = str_rep.section(",",0,0);
	
	
    PObject *res = Database::getInstance()->load(className.toStdString(), id);
	if(res==0){
        qWarning() << QString("PObjectDrag::decode : Failed to load from database : %1/%2").arg(className).arg(id);
	}
	return res;
}

QStringList  PObjectData::formats()
{
    return QStringList("application/pobject");
}
