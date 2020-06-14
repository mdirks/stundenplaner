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
#ifndef VARIANT_H
#define VARIANT_H

#include <string>
#include <map>

#include <QDateTime>
#include <QVariant>
#include <QUrl>
#include "../mapping/murl.h"

using namespace std;

/**
@author Marcus Dirks
*/
class Variant{
public:
     Variant();
     Variant(const Variant &v);
     Variant(const QVariant &qv);
     
     Variant& operator=(const Variant &v);
     
    ~Variant();
        
     operator string();
     operator double();
     operator QDate();
     operator QDateTime();
     operator QUrl();
     operator MUrl();

     QDateTime asQDateTime();
     QDate asQDate();
     QUrl asQUrl();
     MUrl asMUrl();
     QString asQString();
     string asstring();
     double asdouble();
     bool asbool();
     int asint();
     
     bool isValid();
     
private:
	QVariant qv;
    string stdstr;
    static map<wstring,string> map_replace;

};

#endif
