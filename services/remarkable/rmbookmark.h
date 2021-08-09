#ifndef RMBOOKMARK_H
#define RMBOOKMARK_H

#include <QString>

class RmBookmark
{
public:
    RmBookmark();
    RmBookmark(QString pn,QString de);

    void setPageNumber(QString pn);
    void setPageNumber(int pn);
    QString getPageNumber();

    void setName(QString desc);

    void setDescription(QString de);
    QString getDescription();

private:
    QString pagen, descr;
};

#endif // RMBOOKMARK_H
