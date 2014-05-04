#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cwebview.h"
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QUrl url("http://www.chinadaily.com.cn/china/2012qq_index.html");
//    Popup::showCentralPop(NULL, url);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QUrl url("http://www.chinadaily.com.cn/china/2012qq_index.html");
    Popup::showCornerPop(NULL, url);

}
