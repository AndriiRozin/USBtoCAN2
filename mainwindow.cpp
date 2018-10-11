#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "hmi.h"
#include "hmi/hmi_info.h"
#include "hmi/hmi_transmit.h"
#include "hmi/hmi_monitor.h"
#include "hmi/hmi_status.h"
#include "hmi/hmi_filter.h"

#include "config.h"

#include<QDebug>
#include <QStatusBar>
#include <QTableWidget>
#include <QSettings>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , device(NULL)
    , m_queue()
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);


    //init HMI-tables
    m_table_monitor= ui->tableWidget_Monitor;
    m_table_tx = ui->tableWidget_TX;
    m_table_info = ui->tableWidget_Info;
    m_table_filters = ui->tableWidget_Filters;
    m_statusBar = ui->statusBar;


    //test HMI
    Hmi_status statusMesage(m_statusBar);
    QStringList statusList={"My First statusBar is ready"};
    statusMesage.draw(statusList);

    Hmi_info infoMessage(m_table_info);
    infoMessage.hmi_init();
    QStringList infoList={"06.10.2018", "13:08", "Info", "The first comment"};
    infoMessage.draw(infoList);
    infoMessage.draw(infoList);

    Hmi_monitor monitorMessage(m_table_monitor);
    monitorMessage.hmi_init();
    QStringList monitorList={"1", "13.086", "TX", "2fd", "8","01 02 03 04 05 06 07 08","test ASCII"};
    monitorMessage.draw(monitorList);

    Hmi_transmit transmitMessage(m_table_tx);
    transmitMessage.hmi_init();
    QStringList txList={"1", "1ad", "0", "8", "01", "02","03","04","05","06","07","08","Test TX message"};
    transmitMessage.draw(txList);
    transmitMessage.draw(txList);

    Hmi_filter filtersMessage(m_table_filters);
    filtersMessage.hmi_init();
    QStringList filterList={"1aa", "1bb", "1cc", "1dd"};
    filtersMessage.draw(filterList);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (device) {
        delete device;
    }
//    if (logFile) {
//        delete logFile;
//    }
//    delete tmr;
}

void MainWindow::on_pushButton_clicked()
{
    Config dlg;
    dlg.exec();
    qDebug()<<"end config";

     QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;
     settings.beginGroup("InputDevice");
     int port=settings.value("Port").toInt();
     settings.endGroup();
     settings.beginGroup("SerialPort");
     QString portName=settings.value("portName").toString();
     settings.endGroup();



//     settings.beginGroup("CANbus");
//     int baudRateCAN=settings.value("baudRate").toInt();
//     settings.endGroup();
//             switch (baudRateCAN){
//         case 0:
//             ui->label_CANspeed->setText("1M");
//             break;
//         case 1:
//             ui->label_CANspeed->setText("500k");
//             break;
//         case 2:
//             ui->label_CANspeed->setText("250k");
//             break;

//     }

//     MainWindow::loadFilterFromFile();
// }
}

void MainWindow::on_actionPort_triggered()
{
    Config dlg;
    dlg.exec();
    qDebug()<<"end config";

     QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;
     settings.beginGroup("InputDevice");
     int port=settings.value("Port").toInt();
     settings.endGroup();
     settings.beginGroup("SerialPort");
     QString portName=settings.value("portName").toString();
     settings.endGroup();



//     settings.beginGroup("CANbus");
//     int baudRateCAN=settings.value("baudRate").toInt();
//     settings.endGroup();
//             switch (baudRateCAN){
//         case 0:
//             ui->label_CANspeed->setText("1M");
//             break;
//         case 1:
//             ui->label_CANspeed->setText("500k");
//             break;
//         case 2:
//             ui->label_CANspeed->setText("250k");
//             break;

}

void MainWindow::on_actionClear_Monitor_triggered()
{
    qDebug()<<"Clear Table Monitor";
   while (ui->tableWidget_Monitor->rowCount()>0)
   {
       ui->tableWidget_Monitor->removeRow(0);
   }
}

void MainWindow::on_actionCliar_Info_triggered()
{
     qDebug()<<"Clear Table Info";
     while (ui->tableWidget_Info->rowCount()>0)
     {
         ui->tableWidget_Info->removeRow(0);
     }
}



void MainWindow::on_actionOpenPort_triggered()
{
    QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ; //load data from file.ini
     settings.beginGroup("InputDevice");
     const int port=settings.value("Port").toInt();
     settings.endGroup();

     if (device) {
         device->stop();
         delete device;
         device = NULL;
     }


     if (port==1) {
        device = new Inp_File(ui->statusBar);
//        MainWindow::writeLog("inputPort:File");
     }
     else if (port==0) {
         device = new Inp_Serial(ui->statusBar);
//         MainWindow::writeLog("inputPort:Serial");
     }


     if (device) {
         const bool configResult = device->config();
         if (configResult)
         {
             const bool startResult = device->start();
             if (startResult == false) {
                 delete device;
                 device = NULL;
                 mMessageMonitor.bufferRX="";
 //                ui->checkBox_InputPort->setChecked(false);
  //               MainWindow::writeLog("InputPort:open:error");
             }
             else {
 //                ui->checkBox_InputPort->setChecked(true);
 //                MainWindow::writeLog("InputPort:open:ok");
             }
         }
         else {
             delete device;
             device = NULL;
         }
     }
     else {
         qDebug() << "Device pointer is incorrect";
     }
}

void MainWindow::on_actionClosePort_triggered()
{
    if (device) {
          device->stop();
          delete device;
          device = NULL;
  //        ui->checkBox_InputPort->setChecked(false);
  //        MainWindow::writeLog("InputPort:close:ok");
    }
}

void MainWindow::on_pushButton_ReadPort_clicked()
{
    qDebug()<<"on_pushButton_delegat_clicked";

     if(device){
          device->read_DATA(m_queue);
     }
     else {
         QMessageBox::information(this,tr("Warning"), tr("Input port not open!"));
     }

     bool processResult=false;
     while (!m_queue.empty()){
        QString newMessage=m_queue.dequeue();

        qDebug()<<"m_queue.dequeue:" <<newMessage;

             for(QVector<Process_message*>::iterator iterator=processListenerVector.begin(); iterator != processListenerVector.end(); ++iterator){
                 if((*iterator)->processMesage(newMessage)) {
                 processResult=true;
                 break;
                 }
             }
     }
}
