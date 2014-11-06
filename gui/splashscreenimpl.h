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
#ifndef SPLASHSCREENIMPL_H
#define SPLASHSCREENIMPL_H

#include <qsplashscreen.h>
#include <qpixmap.h>
#include "splashscreen.h"

/**
@author Marcus Dirks
*/
class SplashScreenImpl : public QSplashScreen, public SplashScreen
{
public:
    SplashScreenImpl(const QPixmap & pixmap = QPixmap ( ), Qt::WindowFlags f = 0);

    ~SplashScreenImpl();
    void show(){QSplashScreen::show();}
    void hide(){QSplashScreen::hide();}

};

#endif
