#ifndef MODEMATERAIL_H
#define MODEMATERAIL_H
#include "gui/guimode.h"
#include "gui/forms/pdfviewer.h"
#include "gui/forms/pobjecticonview.h"
#include "datamodel/material.h"
#include "ui_modematerial.h"

#include <QTextEdit>
#include <QToolBar>
#include <QSplitter>

namespace Ui {
class ModeMaterial;
}
class ModeMaterial : public GuiMode
{
Q_OBJECT
public:
    ModeMaterial();

    void setupMode();
    void tearDownMode();

public slots:
    void createNew();
    void save();
    void changeMaterial();
    //void changeSatz();

private:
    void setupLatex();
    void setupTxt();
    void setupPdf();
    void setupJap();

    void genericSetup();
    void open(material *m);


private:
    //QTextEdit *editor;
    //PdfViewer *viewer;
    static ModeMaterial* instance;
    QToolBar *toolBar;
    material *activeMaterial;
    QWidget *displayWidget;
    PObjectListProvider *prov;
    //PObjectIconView *viewMaterialien;

private:
    Ui::ModeMaterial *ui;
};

#endif // MODEMATERAIL_H
