#include "doublepane.h"

#include <QVBoxLayout>
#include <QToolBar>

DoublePane::DoublePane(QWidget *parent, Qt::Orientation ori) :
    QSplitter(parent)
{
    setOrientation(ori);

    mdiAreaTop = new MyPane(this);
    addWidget(mdiAreaTop);
    mdiAreaBottom = new MyPane(this);
    addWidget(mdiAreaBottom);
}

void DoublePane::showFormAtTop(QWidget *form)
{
    mdiAreaTop->addSubWindow(form);
}

void DoublePane::showFormAtBottom(QWidget *form)
{
    mdiAreaBottom->addSubWindow(form);
}


MyPane::MyPane(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    setContentsMargins(0,0,0,0);
    QToolBar *tb = new QToolBar(this);
    tb->setStyleSheet("QToolBar {color: grey}");
    box=new QComboBox();
    //box->setStyleSheet("QComboBox {border: 0px; color: grey}");
    box->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    box->setContentsMargins(0,0,0,0);
    tb->addWidget(box);


    stackedWidget = new QStackedWidget(this);
    stackedWidget->setContentsMargins(0,0,0,0);
    l->setContentsMargins(0,0,0,0);
    l->setSpacing(0);

    l->addWidget(tb);
    l->addWidget(stackedWidget);


    tb->show();
    stackedWidget->show();

    connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(changeIndex(int)));
}

void MyPane::addSubWindow(QWidget *w){
    stackedWidget->addWidget(w);
    stackedWidget->setCurrentWidget(w);
    box->addItem(w->windowIcon(),w->toolTip());
}

void MyPane::changeIndex(int i)
{
    stackedWidget->setCurrentIndex(i);
}
