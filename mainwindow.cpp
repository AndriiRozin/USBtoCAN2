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
    QStringList statusList={"My First statusBar is ready"};
    statusMesage.draw(statusList);

    Hmi_info infoMessage(ui->tableWidget_Info);
    infoMessage.hmi_init();
    QStringList infoList={"06.10.2018", "13:08", "Info", "The first comment"};
    infoMessage.draw(infoList);
    infoMessage.draw(infoList);

    Hmi_monitor monitorMessage(ui->tableWidget_Monitor);
    monitorMessage.hmi_init();
    QStringList monitorList={"1", "13.086", "TX", "2fd", "8","01 02 03 04 05 06 07 08","test ASCII"};
    monitorMessage.draw(monitorList);

    Hmi_transmit transmitMessage(ui->tableWidget_TX);
    transmitMessage.hmi_init();
    QStringList txList={"1", "1ad", "0", "8", "01", "02","03","04","05","06","07","08","Test TX message"};
    transmitMessage.draw(txList);
    transmitMessage.draw(txList);

    Hmi_filter filtersMessage(ui->tableWidget_Filters);
    filtersMessage.hmi_init();
    QStringList filterList={"1aa", "1bb", "1cc", "1dd"};
    filtersMessage.draw(filterList);
}

MainWindow::~MainWindow()
{
    delete ui;
}
