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

bool MUrl::isImage()
{
    if( fpath.find(".jpg") != string::npos) return true;
    if( fpath.find(".png") != string::npos) return true;
    if( fpath.find(".gif") != string::npos) return true;
    return false;
}
