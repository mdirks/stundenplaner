#ifndef MURL_H
#define MURL_H

#include <string>

using namespace::std;

class MUrl
{
public:
    MUrl(string fullpath);
    MUrl(const MUrl &other);
    ~MUrl();

    string toStdString() const;

private:
    string fpath;
};

#endif // MURL_H
