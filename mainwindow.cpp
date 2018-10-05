#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "hmi.h"
#include "hmi/hmi_info.h"
#include "hmi/hmi_transmit.h"
#include "hmi/hmi_monitor.h"
#include "hmi/hmi_status.h"
#include <QStatusBar>
#include <QTableWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) ,
    ui(new Ui::MainWindow)


{
     ui->setupUi(this);


    //test HMI
    Hmi_status statusMesage(ui->statusBar);
    statusMesage.draw("Test statusBar");
    Hmi_info infoMessage(ui->tableWidget_Info);
    infoMessage.draw("02:22");
    Hmi_monitor monitorMessage(ui->tableWidget_Monitor);
    monitorMessage.draw("03:33");
    Hmi_transmit transmitMessage(ui->tableWidget_TX);
    transmitMessage.draw("04:44");
}

MainWindow::~MainWindow()
{
    delete ui;
}
