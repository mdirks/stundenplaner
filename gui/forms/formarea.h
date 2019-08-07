#ifndef FORMAREA_H
#define FORMAREA_H

#include <QWidget>

namespace Ui {
class FormArea;
}

class FormArea : public QWidget
{
    Q_OBJECT

public:
    explicit FormArea(QWidget *parent = 0);
    ~FormArea();

    void showForm(QWidget *w);

private:
    Ui::FormArea *ui;
};

#endif // FORMAREA_H
