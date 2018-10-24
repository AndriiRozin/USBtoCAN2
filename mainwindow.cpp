#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

#include<QDebug>
#include <QStatusBar>
#include <QTableWidget>
#include <QSettings>
#include <QMessageBox>

#include <QFileDialog>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , device(NULL)
    , processListenerVector()
    , m_queue()
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    //init HMI-tables
    infoMessageView = new Hmi_info(ui->tableWidget_Info);
    infoMessageView->hmi_init();

    monitorMessageView = new Hmi_monitor(ui->tableWidget_Monitor);
    monitorMessageView->hmi_init();

    txMessageView =new Hmi_transmit(ui->tableWidget_TX);
    txMessageView->hmi_init();

    filterMessageView = new Hmi_filter(ui->tableWidget_Filters);
    filterMessageView->hmi_init();

    //init delegats for messageProccessor
     processListenerVector.reserve(4);
     processListenerVector.push_back(new Process_Tx(monitorMessageView));
     processListenerVector.push_back(new Process_rx(monitorMessageView));
     processListenerVector.push_back(new Process_Info(infoMessageView));
     processListenerVector.push_back(new Process_Error(infoMessageView));
     processListenerVector.push_back(new Process_filter(infoMessageView));

     //init Timer
     tmr=new QTimer(this);    //
     tmr->setInterval(200);  // 1ms
     connect(tmr,SIGNAL(timeout()),this,SLOT(updateTime()));
     tmr->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete infoMessageView;
    delete monitorMessageView;
    delete txMessageView;
    delete filterMessageView;

    if (device) {
        delete device;
    }

    delete tmr;
}


void MainWindow::updateTime()
{
    if(device){
          device->read_DATA(m_queue);

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
 //    else {
 //        QMessageBox::information(this,tr("Warning"), tr("Input port not open!"));
 //    }


}

//void MainWindow::on_pushButton_clicked()
//{
//    Config dlg;
//    dlg.exec();
//    qDebug()<<"end config";

//     QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;
//     settings.beginGroup("InputDevice");
//     int port=settings.value("Port").toInt();
//     settings.endGroup();
//     settings.beginGroup("SerialPort");
//     QString portName=settings.value("portName").toString();
//     settings.endGroup();



////     settings.beginGroup("CANbus");
////     int baudRateCAN=settings.value("baudRate").toInt();
////     settings.endGroup();
////             switch (baudRateCAN){
////         case 0:
////             ui->label_CANspeed->setText("1M");
////             break;
////         case 1:
////             ui->label_CANspeed->setText("500k");
////             break;
////         case 2:
////             ui->label_CANspeed->setText("250k");
////             break;

////     }

////     MainWindow::loadFilterFromFile();
//// }
//}

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

void MainWindow::on_tableWidget_TX_cellClicked(int row, int column)
{
    QString startCondition="<t";
     QString endCondition=">";

     if(column==0)
     {
         QString send_word;
         QString CAN_ID=ui->tableWidget_TX->item(row,1)->text();
         QString CAN_DO=ui->tableWidget_TX->item(row,3)->text();
         QString CAN_D1=ui->tableWidget_TX->item(row,4)->text();
         QString CAN_D2=ui->tableWidget_TX->item(row,5)->text();
         QString CAN_D3=ui->tableWidget_TX->item(row,6)->text();
         QString CAN_D4=ui->tableWidget_TX->item(row,7)->text();
         QString CAN_D5=ui->tableWidget_TX->item(row,8)->text();
         QString CAN_D6=ui->tableWidget_TX->item(row,9)->text();
         QString CAN_D7=ui->tableWidget_TX->item(row,10)->text();
         int DLC=0;
         QString RTR=ui->tableWidget_TX->item(row,2)->text();

         if(CAN_D7!="") DLC=8;
         else DLC=7;
         if(CAN_D6=="") DLC=6;
         if(CAN_D5=="") DLC=5;
         if(CAN_D4=="") DLC=4;
         if(CAN_D3=="") DLC=3;
         if(CAN_D2=="") DLC=2;
         if(CAN_D1=="") DLC=1;
         if(CAN_DO=="") DLC=0;

         if(RTR=="1") DLC=9;


         if(CAN_ID=="")
         {
             send_word="Error:No ID";
 //            ui->lineEdit_InputData_TX->setText(send_word);
             return;
         }
         else
         {
             send_word=startCondition+CAN_ID;
             send_word+=QString::number(DLC);

          qDebug()<<"DLC"<<DLC;

             switch (DLC) {
             case 9:
                 send_word+=endCondition;
                 break;
             case 0:
                 send_word+=endCondition;
                 break;
             case 1:
                 send_word+=CAN_DO;
                 send_word+=endCondition;
                 break;
             case 2:
                 send_word+=CAN_DO;
                 send_word+=CAN_D1;
                 send_word+=endCondition;
                 break;
             case 3:
                 send_word+=CAN_DO;
                 send_word+=CAN_D1;
                 send_word+=CAN_D2;
                 send_word+=endCondition;
                 break;
             case 4:
                 send_word+=CAN_DO;
                 send_word+=CAN_D1;
                 send_word+=CAN_D2;
                 send_word+=CAN_D3;
                 send_word+=endCondition;
                 break;
             case 5:
                 send_word+=CAN_DO;
                 send_word+=CAN_D1;
                 send_word+=CAN_D2;
                 send_word+=CAN_D3;
                 send_word+=CAN_D4;
                 send_word+=endCondition;
                 break;
             case 6:
                 send_word+=CAN_DO;
                 send_word+=CAN_D1;
                 send_word+=CAN_D2;
                 send_word+=CAN_D3;
                 send_word+=CAN_D4;
                 send_word+=CAN_D5;
                 send_word+=endCondition;
                 break;
             case 7:
                 send_word+=CAN_DO;
                 send_word+=CAN_D1;
                 send_word+=CAN_D2;
                 send_word+=CAN_D3;
                 send_word+=CAN_D4;
                 send_word+=CAN_D5;
                 send_word+=CAN_D6;
                 send_word+=endCondition;
                 break;
             case 8:
                 send_word+=CAN_DO;
                 send_word+=CAN_D1;
                 send_word+=CAN_D2;
                 send_word+=CAN_D3;
                 send_word+=CAN_D4;
                 send_word+=CAN_D5;
                 send_word+=CAN_D6;
                 send_word+=CAN_D7;
                 send_word+=endCondition;
                 break;
             default:
                 break;
             }

             if(device){
    //             ui->lineEdit_InputData_TX->setText(send_word);
                 device->write_DATA(send_word);
    //             MainWindow::writeLog(send_word);

             }
             else{
                 QMessageBox::information(this,tr("Warning"), tr("Input port not open!"));
             }
         }
     }
}

void MainWindow::on_tableWidget_TX_cellChanged(int row, int column)
{
    QString temp_word=NULL;

      switch (column){
       case 1:
      {
          temp_word=ui->tableWidget_TX->item(row,column)->text();
          MainWindow::editTX_ID(temp_word,row,column);
          break;
      }

       case 11:
      {
           qDebug()<<"row="<<row<<"column2="<<column;
           break;
      }

      case 2:
      {
           QString data=ui->tableWidget_TX->item(row,column)->text();
           MainWindow::editTX_RTR(data,row,column);
           break;
      }
      case 3:     //edit D0
      {
          QString data=ui->tableWidget_TX->item(row,column)->text();
          MainWindow::editTXdata(data,row,column);

          break;
      }
      case 4:     //edit D1
          {
          QString data=ui->tableWidget_TX->item(row,column)->text();
          MainWindow::editTXdata(data,row,column);
          break;
          }
      case 5:     //edit D2
          {
          QString data=ui->tableWidget_TX->item(row,column)->text();
          MainWindow::editTXdata(data,row,column);
          break;
          }
       case 6:     //edit D3
          {
          QString data=ui->tableWidget_TX->item(row,column)->text();
          MainWindow::editTXdata(data,row,column);
          break;
          }
      case 7:     //edit D4
         {
         QString data=ui->tableWidget_TX->item(row,column)->text();
         MainWindow::editTXdata(data,row,column);
         break;
         }
      case 8:     //edit D5
         {
         QString data=ui->tableWidget_TX->item(row,column)->text();
         MainWindow::editTXdata(data,row,column);
         break;
         }
      case 9:     //edit D6
         {
         QString data=ui->tableWidget_TX->item(row,column)->text();
         MainWindow::editTXdata(data,row,column);
         break;
         }
      case 10:     //edit D7
         {
         QString data=ui->tableWidget_TX->item(row,column)->text();
         MainWindow::editTXdata(data,row,column);
         break;
         }

      default:
          break;

       }


}

void MainWindow::editTX_ID(QString data,int row, int column)
{
    int len=data.length();
    QString data_out=NULL;
    QString temp_word=NULL;
    bool ok;

    switch(len)
    {
    case 1:
        temp_word=data.mid(0,1); //read 1 byte from data
        temp_word.toInt(&ok,16);
        if(ok==false) data_out="";
        else data_out="00"+temp_word;
        break;
    case 2:
        temp_word=data.mid(0,2); //read 2 byte from data
        temp_word.toInt(&ok,16);
        if(ok==false) data_out="";
        else data_out="0"+temp_word;
        break;
    case 3:
        temp_word=data.mid(0,3); //read 3 byte from data
        temp_word.toInt(&ok,16);
        if(ok==false) data_out="";
        else data_out=temp_word;
        break;
    case 4:
        temp_word=data.mid(0,1); //read 1 byte from data
        if (temp_word!="0") data_out="";
        else {
            temp_word=data.mid(1,3); //read 3 byte from data
            temp_word.toInt(&ok,16);
            if(ok==false) data_out="";
            else data_out=temp_word;
        }
    default:
        break;
    }


    data_out=data_out.toUpper();
    qDebug()<<"data"<<data<<"data_out"<<data_out;
    ui->tableWidget_TX->item(row,column)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_TX->item(row,column)->setText(data_out);
    return ;
 }

void MainWindow::editTX_RTR(QString data,int row, int column)
 {
     if(data=="" || data=="0") ui->tableWidget_TX->item(row,column)->setText("");
     else {
         ui->tableWidget_TX->item(row,column)->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget_TX->item(row,column)->setText("1");
     }
 }

void MainWindow::editTXdata(QString data,int row,int column)
{
    int len=data.length();
    QString temp_word=NULL;
    QString data_out=NULL;
    bool ok;

    switch(len)
    {
       case 1:
        temp_word=data.mid(0,1); //read 1 byte from data
        temp_word.toInt(&ok,16);
        if(ok==false) data_out="";
        else data_out="0"+temp_word;
        break;
    case 2:
        temp_word=data.mid(0,2); //read 1 byte from data
        temp_word.toInt(&ok,16);
        if(ok==false) data_out="";
        else data_out=temp_word;
        break;
    default:
        break;
    }

    data_out=data_out.toUpper();
    ui->tableWidget_TX->item(row,column)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_TX->item(row,column)->setText(data_out);
    return ;
}

void MainWindow::on_tableWidget_Filters_cellChanged(int row, int column)
{
    bool checkState=ui->tableWidget_Filters->item(row,column)->checkState();
    QString columnData=ui->tableWidget_Filters->item(row,column)->text();

    switch (column) {
    case 0:
        filterCAN.filter[row].status = checkState;
        if(filterCAN.filter[row].status)
        {
          //  qDebug()<<Qt::black;
       //     ui->tableWidget_Filters->item(row,1)->setText("hello");        //->setTextColor(Qt::black);
      //      ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::black);
      //      ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::black);
      //      ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::black);
      //      ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::black);

        }
        else
        {
     //       ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::gray);
     //       ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::gray);
     //       ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::gray);
     //       ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::gray);
     //       ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::gray);
        }
        break;
    case 1:
//        filterCAN.filter[row].data1=MainWindow::testInputData(columnData);
//        ui->tableWidget_Filters->item(row,column)->setText(filterCAN.filter[row].data1);
//        if(filterCAN.filter[row].status)
//        {
//            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::black);

//        }
//        else
//        {
//            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::gray);
//        }
        break;
    case 2:
//        filterCAN.filter[row].data2=MainWindow::testInputData(columnData);
//        ui->tableWidget_Filters->item(row,column)->setText(filterCAN.filter[row].data2);
//        if(filterCAN.filter[row].status)
//        {
//            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::black);

//        }
//        else
//        {
//            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::gray);
//        }

       break;
    case 3:
//        filterCAN.filter[row].data3=MainWindow::testInputData(columnData);
//        ui->tableWidget_Filters->item(row,column)->setText(filterCAN.filter[row].data3);
//        if(filterCAN.filter[row].status)
//        {
//            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::black);

//        }
//        else
//        {
//            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::gray);
//        }

        break;
    case 4:
//        filterCAN.filter[row].data4=MainWindow::testInputData(columnData);
//        ui->tableWidget_Filters->item(row,column)->setText(filterCAN.filter[row].data4);


//        if(filterCAN.filter[row].status)
//        {
//            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::black);
//            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::black);

//        }
//        else
//        {
//            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::gray);
//            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::gray);
//        }

        break;
    default:
        break;
    }
    qDebug()<<"on_tableWidget_Filters_cellChanged"<<"row:"<<row<<"column:"<<column<<"columnData:"<<columnData<<checkState;

}

QString MainWindow::testInputData(QString hexData)
{
    bool ok;
    QString dataOut;
    int intData;

    if (hexData=="")
    {
        dataOut=hexData;
    }
    else
    {
        intData = hexData.toInt(&ok,16);
        if(ok==false || intData>=1024)
        {
            dataOut="0";
        }
        else
        {
            dataOut=QString("%1").arg(intData,0,16).toUpper();
        }
    }
    return dataOut;
}

//void MainWindow::on_actionDown_Monitor_triggered()
//{

//}

void MainWindow::on_actionDown_Monitor_toggled(bool arg1)
{
    QStringList monitorConfig;

    monitorConfig<<"true"<<"test";


    if(arg1){
        monitorConfig[0]="Down_true";
    }
    else{
        monitorConfig[0]="Down_false";
    }



    monitorMessageView->hmi_key(monitorConfig);

    qDebug()<<"on_actionDown_Monitor_triggered"<<monitorConfig[0]<<arg1;
}
