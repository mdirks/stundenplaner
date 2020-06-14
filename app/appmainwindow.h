#ifndef APPMAINWINDOW_H
#define APPMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AppMainWindow; }
QT_END_NAMESPACE

class AppMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppMainWindow(QWidget *parent = nullptr);
    ~AppMainWindow();

private:
    Ui::AppMainWindow *ui;
};
#endif // APPMAINWINDOW_H
