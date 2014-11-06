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
#ifndef NOTIZ_H
#define NOTIZ_H

#include <string>

using namespace std;

#include "orm/transactions/transactionobject.h"

/**
@author Marcus Dirks
*/
class notiz : public TransactionObject {
public:
    notiz();

    ~notiz();
    string getTitle();
    void setTitle(string text);
    string getBody();
    void setBody(string text);
    
private:
	string title, body;

};

#endif
