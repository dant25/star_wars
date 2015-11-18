#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "iostream"
 #include <QWSServer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->glwidget->label = ui->label;
}

MainWindow::~MainWindow()
{
    delete ui;
}


