
#include <QApplication>
#include <QMessageBox>
#include "mappinggenerator.h"
#include "mappinggeneratordialog.h"
/**

*/
 int main(int argc, char** argv){
    QApplication a(argc,argv);

    MappingGeneratorDialog *d = new MappingGeneratorDialog();
    d->exec();
    a.exec();
}
