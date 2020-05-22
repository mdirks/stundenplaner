#ifndef DOCSTOREDIALOG_H
#define DOCSTOREDIALOG_H

#include <QDialog>

namespace Ui {
class DocStoreDialog;
}

class DocStoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DocStoreDialog(QWidget *parent = nullptr);
    ~DocStoreDialog();

public slots:
    void chooseLocation();

private:
    Ui::DocStoreDialog *ui;
    QString locationDirName;
};

#endif // DOCSTOREDIALOG_H
