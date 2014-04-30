#include "mainwindow.h"
#include "dialogbase.h"
#include "popup.h"

#include <QApplication>
#include <QUrl>
#include <QWebView>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setQuitOnLastWindowClosed(false);

    MainWindow w;
    w.show();

    return a.exec();
}
