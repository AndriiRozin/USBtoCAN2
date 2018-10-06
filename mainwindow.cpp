#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "hmi.h"
#include "hmi/hmi_info.h"
#include "hmi/hmi_transmit.h"
#include "hmi/hmi_monitor.h"
#include "hmi/hmi_status.h"
#include "hmi/hmi_filter.h"
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
    infoMessage.hmi_init();
    infoMessage.draw("02:22");

    Hmi_monitor monitorMessage(ui->tableWidget_Monitor);
    monitorMessage.hmi_init();
    monitorMessage.draw("03:33");

    Hmi_transmit transmitMessage(ui->tableWidget_TX);
    transmitMessage.hmi_init();
    transmitMessage.draw("04:44");

    Hmi_filter filtersMessage(ui->tableWidget_Filters);
    filtersMessage.hmi_init();
    filtersMessage.draw("hellow");

}

MainWindow::~MainWindow()
{
    delete ui;
}
