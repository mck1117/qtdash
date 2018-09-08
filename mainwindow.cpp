#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	// This hides the window boredr/title bar/etc
	this->setWindowFlags(Qt::CustomizeWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}
