#include "murl.h"

MUrl::MUrl(string fullpath)
    : fpath(fullpath)
{

}

MUrl::MUrl(const MUrl &other)
{
     fpath=other.toStdString();
}

MUrl::~MUrl()
{

}


string MUrl::toStdString() const
{
    return fpath;
}
