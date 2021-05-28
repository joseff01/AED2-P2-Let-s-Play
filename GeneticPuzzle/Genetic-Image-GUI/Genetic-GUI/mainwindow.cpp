#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../Image/GenerativeImg.h"

#include <QDir>
#include <iostream>

//For testing out frankenImg function, can be removed later
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

QString imagePath;
int num = 0;

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
 * \brief MainWindow::on_listWidget_itemClicked method that reacts to the user when clicked. It detects the chosen path from the widgetList
 * \param item the item selected in the widgetList
 */
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QImage image (item->text());
    imagePath = item->text();
    QPixmap pm = QPixmap::fromImage(image);
    ui->label->setPixmap(pm);
    ui->label->adjustSize();                  // Modifies the label's size to the given image
    ui->label->setAlignment(Qt::AlignCenter); // Aligns label in the midle of the widget
}

/*!
 * \brief MainWindow::on_horizontalSlider_sliderMoved method that allows the user to go trough different generations
 * \param position its the position in wihc the slider is placed
 */
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    if(position>num){

        bool ok;
        QString temp = ui->lineEdit->text();                               //Gets the user's number input
        int chunks = temp.toInt(&ok);

        if(!ok){ std::cout << "please enter a number" << std::endl; }      //Checks if an int was introduced

        if(imagePath.back()!= 'g'){                                        //Checks if an image was introduced
            std::cout << "please enter a image" << std::endl;
        }
        else{                                                              //Shows new generated Image
            num++;
            QImage image(imagePath);
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
    }
}
