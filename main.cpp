#include "widget.h"
#include <QApplication>

#include <QPushButton>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    QStringList listPath;
//    QDir dir = QDir(a.applicationDirPath() + "/./");
//    QDir dir1 = QDir(a.applicationDirPath() + ".");
//    QDir dir2 = QDir(a.applicationDirPath() + "/.");
//    QDir dir3 = QDir(a.applicationDirPath() + "/");
//    listPath << dir.absolutePath() << a.libraryPaths()<< dir1.absolutePath()<< dir2.absolutePath()<< dir3.absolutePath();
//    a.setLibraryPaths(listPath);


    Widget w;
    w.show();
    return a.exec();
}

