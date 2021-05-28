#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../Image/GenerativeImg.h"

#include <QDir>
#include <iostream>

//For testing out frankenImg function, can be removed later
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

/*!
 * \brief MainWindow::MainWindow Constructor of MainWindow's class, it will show the GUI of the project and will show the image paths available
 * \param parent main widget in wich information is displayed
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir dir("../Genetic-GUI/images");
    foreach (QFileInfo var, dir.entryInfoList()) // type of "for loop" in wich shows the files abilable in the specified path
    {
        ui->listWidget->addItem(var.absoluteFilePath());
    }
}

/*!
 * \brief MainWindow::~MainWindow destructor of MainWindow's class
 */
MainWindow::~MainWindow() { delete ui; }

/*!
 * \brief MainWindow::on_listWidget_itemClicked method that reacts to the user when clicked. It delects the chosen path from the widgetList
 * \param item the item selected in the widgetList
 */
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QImage image(item->text());

    int chunks = 256;

    GenerativeImg newImage(image, chunks);

    List<int> l;

    srand(time(NULL));
    for (int i = 0; i < chunks; i++)
    {
        l.push_back(rand() % chunks);
    }

    QPixmap pm = QPixmap::fromImage(newImage.getFrankenImg(l));
    ui->label->setPixmap(pm);
    ui->label->adjustSize();                  // Modifies the label's size to the given image
    ui->label->setAlignment(Qt::AlignCenter); // Aligns label in the midle of the widget
}
