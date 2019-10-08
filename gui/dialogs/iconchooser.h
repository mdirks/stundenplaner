#ifndef ICONCHOOSER_H
#define ICONCHOOSER_H

#include <QListWidget>
#include <QDialog>

class IconChooser : public QListWidget
{
   Q_OBJECT
public:
    IconChooser(QWidget *parent=nullptr);

public slots:
    void activateItem(QListWidgetItem *item);
};

class IconChooserItem : public QListWidgetItem
{
public:
    IconChooserItem(QIcon icon, QString text, QListWidget *parent);
};

class IconChooserDialog : public QDialog
{
public:
    IconChooserDialog(QWidget *parent=nullptr);

private:
    IconChooser *chooser;
};

#endif // ICONCHOOSER_H
