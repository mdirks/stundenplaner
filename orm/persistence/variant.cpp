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

map<wstring,string> create_map() {
  map<wstring, string> m;
  m[wstring(L"Okt")] = "Oct";
  m[wstring(L"Dez")] = "Dec";
  m[wstring(L"Mär")] = "Mar";
  m[wstring(L"Mai")] = "May";
  return m;
}


map<wstring,string> Variant::map_replace=create_map();

Variant::Variant(){

}

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

Variant::operator QUrl()
{
    return QUrl(qv.toString());
}

Variant::operator MUrl(){
    return MUrl(qv.toString().toStdString());
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
    for(map<wstring,string>::iterator it = map_replace.begin(); it!=map_replace.end(); it++){
        //qDebug() << QString("Replacing %1 with %2").arg(it->first.c_str()).arg(it->second.c_str());
        st.replace(QString::fromStdWString(it->first), it->second.c_str());
        //qDebug() << QString("Gave: %1").arg(st);
    }
    QDateTime datetime = QDateTime::fromString(st);
    //qDebug() << QString("Variant: returning %1 vor %2").arg(datetime.toString()).arg(st);
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
    if(!date.isValid()){
        for(map<wstring,string>::iterator it = map_replace.begin(); it!=map_replace.end(); it++){
            //qDebug() << QString("Replacing %1 with %2").arg(it->first.c_str()).arg(it->second.c_str());
            QString ist=QString::fromStdWString(it->first);
            QString soll = it->second.c_str();
            st.replace(ist, soll);
            //qDebug() << QString("Gave: %1").arg(st);
        }
        date=QDate::fromString(st);
    }

    //QDate date=qv.toDate();
    //qDebug() << QString("Variant: returning %1 vor %2").arg(date.toString()).arg(st);
	return date;
	//QDate::fromString(qv.toString());
}

QUrl Variant::asQUrl()
{
    QUrl url(qv.toString());
	return url;
}

MUrl Variant::asMUrl()
{
    MUrl url(qv.toString().toStdString());
    return url;
}

bool Variant::asbool()
{
	qv.toBool();
}
