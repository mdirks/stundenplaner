/***************************************************************************
                          utils.h  -  description
                             -------------------
    begin                : Sam Jul 5 2003
    copyright            : (C) 2003 by Marcus Dirks
    email                : marcus.dirks@t-online.de
 ***************************************************************************/
#include <sstream>
#include <qstring.h>
#include <qdatetime.h>
#include "orm/mapping/murl.h"

using namespace std;
                                                                       
 template< class T>
    inline std::string to_string( const T & Value)
{
    std::stringstream streamOut;
    streamOut << Value;
    return streamOut.str( );
}

template< >
   inline std::string to_string( const MUrl &url)
{
       std::stringstream streamOut;
       streamOut << url.toStdString();
       return streamOut.str( );
}

template< >
    inline std::string to_string( const QDate & Value)
{
    std::stringstream streamOut;
    streamOut << Value.toString().toStdString();
    return streamOut.str( );
}

template< >
    inline std::string to_string( const KUrl & Value)
{
    std::stringstream streamOut;
    streamOut << Value.url().toStdString();
    return streamOut.str( );
}

template< >
    inline std::string to_string( const QDateTime & Value)
{
    std::stringstream streamOut;
    streamOut << Value.toString().toStdString();
    return streamOut.str( );
}

template<class T>
inline QString to_qstring( const T &value) {
	std::string ss = to_string(value);
	return QString(ss.c_str());
}

//  specialization for string.
template< >
    inline std::string to_string( const std::string & Value)
{
    return Value;
}
