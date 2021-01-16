#ifndef TEXTPROPERTYVIEWER2_H
#define TEXTPROPERTYVIEWER2_H

#include "textpropertyviewer.h"

#include "qlabel.h"
#include "qdir.h"
#include "qimage.h"
#include "qprocess.h"
#include "qlabel.h"
#include <QDialog>
#include "textpropertyeditor.h"
#include "pdfviewer.h"

#include <QScrollArea>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QColor>
#include <QSplitter>

#include <QClipboard>
#include "klfbackend/klfbackend.h"
#include "klfbackend/klfpreviewbuilderthread.h"

class TextPropertyViewer2 : public QWidget
{
Q_OBJECT

public:
    TextPropertyViewer2(QWidget *pw=nullptr);
    TextPropertyViewer2(PObject *parent, RepositoryProperty *prop, QWidget *pw=nullptr, double w=18.0, double h=28.0);
    TextPropertyViewer2(PObject *parent, QString displayString, QWidget *pw=nullptr);
    ~TextPropertyViewer2();

    void setParentObject(PObject *o);
    void setProperty(RepositoryProperty *p);

    QString getCompileStringVorn();
    void compileVorn(bool reload);
    void setHidden(bool h);
    void setFitToView(bool f);
    void setScrollBarPolicy(Qt::ScrollBarPolicy policy);

    void setFooter(QString f);
    void setHeader(QString f);
    void setBackgroundColor(QColor c);
    void setZoomFactor(double f);
    void setResizePolicy(bool res);

    QSize sizeHint();

public slots:
    //void editVorn();
    //void readVorn();
    void stopEdit();
    //void compileFinished(int code, QProcess::ExitStatus exitStatus);
    //void compileError( QProcess::ProcessError error);

    void print();
    void updatePreview();
    void showPreview(const QByteArray& pdfData, bool latexerror);

signals:
    void applyRequested();

protected:
    void keyPressEvent ( QKeyEvent * e );
    void resizeEvent ( QResizeEvent *e);
    void contextMenuEvent(QContextMenuEvent *e);

private:
    //QString getFileName();
    //QString getTexFileName();
    //void setDisplayPixmapToLabel(QPixmap dpm);
    void doCommonSetup();



public:
    static QString StandardHeader, StandardFooter;


private:
    PObject *parent;
    RepositoryProperty *prop;
    QDir tmpDir;
    TextPropertyEditor *editor;
    QScrollArea *scroll;
    PdfViewer *label;
    QString displayString;
    bool editing;
    bool hidden;
    bool fit;
    QProcess *p;
    QString header,footer;
    QPixmap displayPm;
    QSplitter *splitter;

       QSize displaySize;
       QColor bgColor;
     double width,height;

     KLFPreviewBuilderThread *mPreviewBuilderThread;
     KLFBackend::klfInput input;
     KLFBackend::klfSettings settings;
     KLFBackend::klfOutput output;
     QClipboard *clipboard;
     QPixmap pixmap;

     QString name;

};

#endif // TEXTPROPERTYVIEWER2_H
