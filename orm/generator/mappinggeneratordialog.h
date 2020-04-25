#ifndef MAPPINGGENERATORDIALOG_H
#define MAPPINGGENERATORDIALOG_H

#include <QDialog>
#include <QFile>
#include <QDir>
#include <QMenu>
#include <QAction>
#include "dommodel.h"

namespace Ui {
class MappingGeneratorDialog;
}

class MappingGeneratorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MappingGeneratorDialog(QWidget *parent = nullptr);
    ~MappingGeneratorDialog();



public slots:
    void chooseOut();
    void chooseDesc();
    void addClass();
    void addProperty();
    void addAsociation();


    void accept() override;
    void onCustomContextMenu(const QPoint &point);
    void newSelection(QModelIndex ind);

private:
    QString HtmlFromXml(const QString &xmlFileName);
    QString XmlFromHtml(const QString &strHtml);


private:
    Ui::MappingGeneratorDialog *ui;

    QString descFileName;
    QString outDirName;
    QMenu *contextMenu;

    bool selectOk;
    DomModel *domModel;
    QDomNode selectedNode;
    QDomDocument doc;
};

class MGDAddNodeAction : public QAction
{
    Q_OBJECT

public:
    MGDAddNodeAction(QModelIndex &index,QString &type);

private:
    QModelIndex &ind;
    QString type;
};

#endif // MAPPINGGENERATORDIALOG_H
