#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../Image/GenerativeImg.h"

#include <QDir>



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
    clientSetup();
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

/**
 * @brief MainWindow::clientSetup Funciton in charge of seting up the client side of the connection with the server.
 * Socket: 5000. Ip: localhost
 */
void MainWindow::clientSetup(){
    int portno = 5000;
    int option = 1;
    struct sockaddr_in serv_addr;
    char const *localHost = "localhost";
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEPORT,&option,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    if (sockfd < 0)
      serverError("ERROR opening socket");
    server = gethostbyname(localHost);
    if (server == NULL){
      fprintf(stderr,"ERROR, no such host");
      exit(0);
    }
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    std::cout << "Connecting to mserver..." << std::endl;
    if (::connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        serverError("ERROR connecting");
    }
}

/**
 * @brief MainWindow::serverError If an error ocurrs at some point while connecting with the server, sending a messsage, or receiving one,
 * this function will kill the program
 * @param msg error message displayed
 */
void MainWindow::serverError(const char *msg)
{
    perror(msg);
    exit(1);
}

/**
 * @brief MainWindow::sendMsg Sends a json object to the server.
 * @param jsonMsg json to send to the server
 */
void MainWindow::sendMsg(json jsonMsg)
{
    std::string stringMsg = jsonMsg.dump();
    memset(buffer,0,511);
    strncpy(buffer, stringMsg.c_str(),511);
    int n = write(sockfd,buffer,strlen(buffer));
    if (n < 0){serverError("ERROR writing to socket");}
}
/**
 * @brief MainWindow::receiveMsg Receives a message from the server. Clienmt waits until the message arrives
 * @return stringBuffer String of message sent by the server
 */
std::string MainWindow::receiveMsg()
{
    memset(buffer, 0, 511);
    int n = read(sockfd,buffer,511);
    if (n < 0) serverError("ERROR reading from socket");
    std::string stringBuffer(buffer);
    return stringBuffer;
}

List<int> MainWindow::getGenerationList(int generation)
{
    std::string XMLStr = "../GenerationXML/XMLGeneration";
    std::string generationCounterStr = std::to_string(generation);
    XMLStr.append(generationCounterStr);
    XMLStr.append(".xml");
    XMLDocument XMLDoc;
    XMLDoc.LoadFile(XMLStr.c_str());
    XMLNode *pRoot = XMLDoc.FirstChild();
    int mostFitness = 0;
    int mostFintessPos;
    int counter = 0;
    List<List<int>> listOfIndividuals;
    XMLElement *pList = pRoot->FirstChildElement("Individual0");
    for(pList; pList != NULL; pList = pList->NextSiblingElement()){
        XMLElement *pListElement = pList->FirstChildElement();
        int fitness;
        pListElement->QueryIntText(&fitness);
        if (fitness >= mostFitness){
            mostFitness = fitness;
            mostFintessPos = counter;
        }
        List<int> listGenes;
        pListElement = pListElement->NextSiblingElement();
        for (pListElement; pListElement != NULL; pListElement = pListElement->NextSiblingElement()){
            int gene;
            pListElement->QueryIntText(&gene);
            listGenes.push_back(gene);
        }
        listOfIndividuals.push_back(listGenes);
        counter++;
    }
    return listOfIndividuals[mostFintessPos];
}
