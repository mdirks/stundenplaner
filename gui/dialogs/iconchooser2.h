#ifndef ICONCHOOSER2_H
#define ICONCHOOSER2_H

#include <QWidget>
#include <QListWidget>
#include <QDialog>

namespace Ui {
class IconChooser2;
}

class IconChooser2 : public QWidget
{
    Q_OBJECT

public:
    explicit IconChooser2(QWidget *parent = nullptr);
    ~IconChooser2();

public slots:
    void slotSelectIcon(QListWidgetItem *item);

private:
    Ui::IconChooser2 *ui;
};


class IconChooserItem2 : public QListWidgetItem
{
public:
    IconChooserItem2(QIcon icon, QString text, QListWidget *parent);
    void selectIcon(QString iconName);
};


class IconChooserDialog2 : public QDialog
{
public:
    IconChooserDialog2(QWidget *parent=nullptr);

private:
    IconChooser2 *chooser;
};


#endif // ICONCHOOSER2_H
