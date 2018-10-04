#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "hmi.h"
#include "hmi/hmi_info.h"
#include "hmi/hmi_transmit.h"
#include "hmi/hmi_monitor.h"
#include "hmi/hmi_status.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //test HMI
       Hmi_status statusMesage;
       statusMesage.draw("01:11");
       Hmi_info infoMessage;
       infoMessage.draw("02:22");
       Hmi_monitor monitorMessage;
       monitorMessage.draw("03:33");
       Hmi_transmit transmitMessage;
       transmitMessage.draw("04:44");

}

MainWindow::~MainWindow()
{
    delete ui;
}
