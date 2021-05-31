#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <QMainWindow>
#include <QListWidgetItem>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include "json.hpp"
#include "List.h"
#include "tinyxml2.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE
using json = nlohmann::json;
using namespace tinyxml2;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_clicked();

private:
    int sockfd;
    char buffer[511];

    Ui::MainWindow *ui;
    void clientSetup();
    void serverError(const char *msg);
    void sendMsg(json message);
    std::string receiveMsg();
    List<int> getGenerationList(int generation);
};
#endif // MAINWINDOW_H
