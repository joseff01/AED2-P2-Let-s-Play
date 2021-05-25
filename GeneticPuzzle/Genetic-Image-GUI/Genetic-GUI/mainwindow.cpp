#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir dir("../Genetic-GUI/images");
    foreach(QFileInfo var, dir.entryInfoList())
    {
        ui->listWidget->addItem(var.absoluteFilePath());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    std::cout << item->text().toStdString() << std::endl;
    QImage imagen(item->text());
    QPixmap pm = QPixmap::fromImage(imagen);
    ui->label->setPixmap(pm);
    ui->label->adjustSize();
    ui->label->setAlignment(Qt::AlignCenter);
    //ui->label->adjustSize();

}
