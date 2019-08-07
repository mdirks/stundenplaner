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
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

/**
@author Marcus Dirks
*/
class SplashScreen{
public:
    SplashScreen();

    ~SplashScreen();
    virtual void show() = 0;
    virtual void hide() =0;

};

#endif
