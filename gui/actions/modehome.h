#ifndef MODEHOME_H
#define MODEHOME_H

#include "guimode.h"

#include <QWidget>

namespace Ui {
class ModeHome;
}

class ModeHome : public GuiMode
{
    Q_OBJECT

public:
    ModeHome();
    ~ModeHome();

    void setupMode();
    void tearDownMode();
    void activateObject(PObject *o);
    void showForm(QWidget *w);
    QList<QAction*>* getModeActions();


private:
    Ui::ModeHome *ui;
    QWidget *displayWidget;
};

#endif // MODEHOME_H
