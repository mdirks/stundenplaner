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
#include "variant.h"
#include <QString>
#include <QDebug>

Variant::Variant(){}

Variant::~Variant(){}

Variant::Variant(const Variant& v){
	this->qv = v.qv;
}

 Variant::Variant(const QVariant& qv)
{
    this->qv = qv;
}

Variant::operator string()
{
	QString str = qv.toString();
	if(str != QString::null)
	{
           stdstr = (qv.toString()).toStdString();
	} else {
	   stdstr = "";
	 }
	
	//qDebug(QString("Variant conversion to %1").arg(stdstr));
	return stdstr;
}

Variant::operator double()
{
	return qv.toDouble();
}

Variant::operator QDate()
{
	return QDate::fromString(qv.toString());
}



Variant::operator QDateTime()
{
	return QDateTime::fromString(qv.toString());
}

Variant::operator KUrl()
{
    return KUrl(qv.toString());
}
/*!
    \fn Variant::isValid()
 */
bool Variant::isValid()
{
    return qv.isValid();
}

Variant& Variant::operator=(const Variant& v)
{
	this->qv = v.qv;
	return *this;
}

QDateTime Variant::asQDateTime()
{
	QString st = qv.toString();
	QDateTime datetime = QDateTime::fromString(st);
    qDebug() << QString("Variant: returning %1 vor %2").arg(datetime.toString()).arg(st);
	return datetime;
	//return qv.toDateTime();
}
string Variant::asstring()
{
	QString str = qv.toString();
	if(str != QString::null)
	{
        stdstr = (qv.toString()).toStdString();
	} else {
	   stdstr = "";
	 }
	
	//qDebug(QString("Variant conversion to %1").arg(stdstr));
	return stdstr;
}

double Variant::asdouble()
{
	return qv.toDouble();
}

int Variant::asint()
{
	return qv.toInt();
}

QDate Variant::asQDate()
{
	//return qv.toDate();
	QString st = qv.toString();
	QDate date = QDate::fromString(st);

    qDebug() << QString("Variant: returning %1 vor %2").arg(date.toString()).arg(st);
	return date;
	//QDate::fromString(qv.toString());
}

KUrl Variant::asKUrl()
{
    KUrl url(qv.toString());
	return url;
}

bool Variant::asbool()
{
	qv.toBool();
}
