//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef POBJECTDRAG_H
#define POBJECTDRAG_H

#include <QDrag>
#include <QMimeData>
//#include <qdragobject.h>
#include <QWidget>
#include <QString>

#include "orm/persistence/pobject.h"

/**
@author Marcus Dirks
*/
class PObjectData : public  QMimeData
{
public:
    PObjectData(PObject *o, QWidget *source);
    ~PObjectData();

     QStringList formats();
     QByteArray data(const QString &mimetype) const;
     
     bool hasFormat(const QString &mimetype);
     static PObject* decode(QByteArray ba);

protected:
     //PObject *o;
     //const char *mime_types[];
	int id;
	QString typedMimeType,className;
};

#endif
