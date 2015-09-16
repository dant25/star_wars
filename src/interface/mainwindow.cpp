#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "iostream"
 #include <QWSServer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    controler = new Controler();

    //setCursor(Qt::BlankCursor);
    //QApplication::setOverrideCursor(Qt::BlankCursor);

    QCursor c = cursor();
    c.setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
/*    c.setShape(Qt::BlankCursor);
    setCursor(c);*/


}

MainWindow::~MainWindow()
{
    delete ui;
}


