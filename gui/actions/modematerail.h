#ifndef MODEMATERAIL_H
#define MODEMATERAIL_H
#include "gui/guimode.h"
#include "gui/forms/pdfviewer.h"
#include "datamodel/material.h"

#include <QTextEdit>
#include <QToolBar>
#include <QSplitter>

class ModeMaterial : public GuiMode
{
Q_OBJECT
public:
    ModeMaterial();

    void setupMode();
    void tearDownMode();
    static ModeMaterial* getInstance();

public slots:
    void createNew();
    void open();
    void save();

private:
    void setupLatex();

private:
    QTextEdit *editor;
    PdfViewer *viewer;
    static ModeMaterial* instance;
    QToolBar *toolBar;
    material *activeMaterial;
    QWidget *mainPanel;
};

#endif // MODEMATERAIL_H
