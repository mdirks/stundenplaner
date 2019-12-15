#ifndef DOCSTORE_H
#define DOCSTORE_H


class DocStore
{
public:
    DocStore();

    DocStore *createStore();
    void addRemote();

    void addDocument();
    void removeDocument();

    void getDocument();
    void dropDocument();
    void moveDocument();

};

#endif // DOCSTORE_H
