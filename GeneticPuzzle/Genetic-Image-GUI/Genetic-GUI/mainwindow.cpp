#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../Image/GenerativeImg.h"

#include <QDir>
#include <iostream>

/*!
 * \brief MainWindow::MainWindow Constructor of MainWindow's class, it will show the GUI of the project and will show the image paths available
 * \param parent main widget in wich information is displayed
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir dir("../Genetic-GUI/images");
    foreach(QFileInfo var, dir.entryInfoList())                 // type of "for loop" in wich shows the files abilable in the specified path
    { ui->listWidget->addItem(var.absoluteFilePath()); }
}

/*!
 * \brief MainWindow::~MainWindow destructor of MainWindow's class
 */
MainWindow::~MainWindow() { delete ui;}

/*!
 * \brief MainWindow::on_listWidget_itemClicked method that reacts to the user when clicked. It delects the chosen path from the widgetList
 * \param item the item selected in the widgetList
 */
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QImage image(item->text());

    //GenerativeImg *newImage = new GenerativeImg(image,4);

    QPixmap pm = QPixmap::fromImage(image);
    ui->label->setPixmap(pm);
    ui->label->adjustSize();                                  // Modifies the label's size to the given image
    ui->label->setAlignment(Qt::AlignCenter);                 // Aligns label in the midle of the widget

}
