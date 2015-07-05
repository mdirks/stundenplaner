#include "formarea.h"
#include "ui_formarea.h"

FormArea::FormArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormArea)
{
    ui->setupUi(this);
}

FormArea::~FormArea()
{
    delete ui;
}

void FormArea::showForm(QWidget *w)
{
    ui->mdiArea->addSubWindow(w);
    w->show();
}
