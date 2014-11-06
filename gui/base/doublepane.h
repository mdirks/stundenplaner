#ifndef DOUBLEPANE_H
#define DOUBLEPANE_H

#include <QWidget>
#include <QComboBox>
#include <QSplitter>
#include <QStackedWidget>

class MyPane;


class DoublePane : public QSplitter
{
    Q_OBJECT
public:
    DoublePane(QWidget *parent = 0, Qt::Orientation=Qt::Vertical);
    void showFormAtTop(QWidget *w);
    void showFormAtBottom(QWidget *);

signals:
    
public slots:

private:
    MyPane *mdiAreaTop, *mdiAreaBottom;
    
};


class MyPane : public QWidget
{
Q_OBJECT

public:
    MyPane(QWidget *w);

    void addSubWindow(QWidget *w);

public slots:
    void changeIndex(int i);

private:
    bool top;
    QStackedWidget *stackedWidget;
    QComboBox *box;
};

#endif
