#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Add_clicked()
{
    scene.add(ui->spinBox->value());
}

void MainWindow::on_Delete_clicked()
{
    scene.del(ui->spinBox->value());
}

void MainWindow::on_Search_clicked()
{
    scene.search(ui->spinBox->value());
}
