#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include "pdfview/pdfview.h"
#include <QSize>

class PdfViewer : public PdfView
{
public:
    PdfViewer(QWidget *parent=0);

    void loadNewFile(QString fileName);
    void loadNewData(const QByteArray &fileContents, QString name);
    void setResizePolicy(bool res);

protected:
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dropEvent(QDropEvent *e);
    virtual void dragMoveEvent(QDragMoveEvent* e);



private:
    void doInitialSetup();

private:
    QSize psize;
    bool resize;
};

#endif // PDFVIEWER_H
