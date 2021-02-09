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
#include "splashscreenimpl.h"
#include <QMessageBox>

SplashScreenImpl::SplashScreenImpl(const QPixmap & pixmap, Qt::WindowFlags f)
 : QSplashScreen(pixmap,f)
{
}


SplashScreenImpl::~SplashScreenImpl()
{
}

bool SplashScreenImpl::versionChangeRequested(string className)
{
    int ans = QMessageBox::question(this,"Version change",
              QString("Really change version of %1 in database - stored data could be lost").arg(className.c_str()),
                                    QMessageBox::No, QMessageBox::Yes, QMessageBox::NoButton);

    if(ans==QMessageBox::Yes)
        return true;
    else return false;
}

bool SplashScreenImpl::confirm(string req)
{
    int ans = QMessageBox::question(this,"Version change",
              QString("Confirm: %1").arg(req.c_str()),
                                    QMessageBox::No, QMessageBox::Yes, QMessageBox::NoButton);

    if(ans==QMessageBox::Yes)
        return true;
    else return false;
}

void SplashScreenImpl::message(string mes)
{
    QMessageBox::question(this,"Version change",
                          QString("Message: %1").arg(mes.c_str()),
                                                QMessageBox::No, QMessageBox::Yes, QMessageBox::NoButton);
}
