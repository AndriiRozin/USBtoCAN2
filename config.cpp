#include "config.h"
#include "ui_config.h"

#include <QFileDialog>
#include <QDebug>
#include <QSettings>
#include <QSerialPort>

Config::Config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);

    Config::createFilterTable();

     Config::loadInputDevice();
     Config::loadSerialConfigFromFile();
     Config::loadCANconfigFromFile();
     Config::loadFiltersStatus();
     Config::loadFiltersData();
     Config::loadFileFromFile();

}

Config::~Config()
{
    delete ui;
}


void Config::createFilterTable()
{
    ui->tableWidget_Filters->setColumnCount(6);
    ui->tableWidget_Filters->horizontalHeader()->resizeSection(0,60);
    ui->tableWidget_Filters->horizontalHeader()->resizeSection(1,60);
    ui->tableWidget_Filters->horizontalHeader()->resizeSection(2,60);
    ui->tableWidget_Filters->horizontalHeader()->resizeSection(3,60);
    ui->tableWidget_Filters->horizontalHeader()->resizeSection(4,60);

    ui->tableWidget_Filters->horizontalHeader()->setSectionResizeMode(5,QHeaderView::Stretch);

    QStringList tableFiltersHeader;
    tableFiltersHeader <<"Filter"<<"ID1H"<<"ID1L"<<"ID2H"<<"ID2L"<<"Result";

    ui->tableWidget_Filters->setHorizontalHeaderLabels(tableFiltersHeader);
    ui->tableWidget_Filters->horizontalHeader()->setStyleSheet("color: blue");
    ui->tableWidget_Filters->horizontalHeader()->setVisible(true);
    for (int i=0; i<=13; i++)
    {
        ui->tableWidget_Filters->item(i,0)->setTextColor(Qt::blue);
    }
}

void Config::loadInputDevice()
{
    QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;
    settings.beginGroup("InputDevice");
    m_config.inpDevice.Port=settings.value("Port").toInt();
    settings.endGroup();
    qDebug()<<"LoadFileFromFile(m_config.inpDevice)"<<m_config.inpDevice.Port;

    switch (m_config.inpDevice.Port) {
    case 0:
        ui->comboBox_inputDevices->setCurrentIndex(0);
        ui->groupBox_File->setEnabled(false);
        ui->groupBox_Serial->setEnabled(true);
        break;
    case 1:
        ui->comboBox_inputDevices->setCurrentIndex(1);
        ui->groupBox_File->setEnabled(true);
        ui->groupBox_Serial->setEnabled(false);
        break;
    }
}

void Config::loadFileFromFile()
{
    QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;
    settings.beginGroup("File");
    m_config.file.fileName = settings.value("inputFile").toString();
    settings.endGroup();
    qDebug()<<"LoadFileFtomFile()"<<m_config.file.fileName;
    ui->lineEdit_fileName->setText(m_config.file.fileName);
}

void Config::loadFiltersData()
{
    QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;
    for (int i=0; i<=13; i++ )
    {
        settings.beginGroup("Filter"+QString::number(i));
        m_config.filter[i].data1 = settings.value("data1").toString();
        m_config.filter[i].data2 = settings.value("data2").toString();
        m_config.filter[i].data3 = settings.value("data3").toString();
        m_config.filter[i].data4 = settings.value("data4").toString();
        settings.endGroup();

        ui->tableWidget_Filters->item(i,1)->setText(m_config.filter[i].data1);
        ui->tableWidget_Filters->item(i,2)->setText(m_config.filter[i].data2);
        ui->tableWidget_Filters->item(i,3)->setText(m_config.filter[i].data3);
        ui->tableWidget_Filters->item(i,4)->setText(m_config.filter[i].data4);

        qDebug()<<"read from File"<<"Filter"+QString::number(i)<<m_config.filter[i].data1<<m_config.filter[i].data2<<m_config.filter[i].data3<<m_config.filter[i].data4;


        if(m_config.filter[i].status)
        {
            ui->tableWidget_Filters->item(i,1)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(i,2)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(i,3)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(i,4)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(i,5)->setTextColor(Qt::black);

        }
        else
        {
            ui->tableWidget_Filters->item(i,1)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(i,2)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(i,3)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(i,4)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(i,5)->setTextColor(Qt::gray);
        }


    }
}

void Config::loadSerialConfigFromFile()
{
    QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;

    settings.beginGroup("SerialPort");
    m_config.serial.portName = settings.value("portName").toString();
    m_config.serial.baudRate = settings.value("baudRate").toInt();
    m_config.serial.dataBits = settings.value("dataBits").toInt();
    m_config.serial.parity = settings.value("parity").toInt();
    m_config.serial.stopBit = settings.value("stopBit").toInt();
    settings.endGroup();

    settings.beginGroup("FilterCAN");
    m_config.filterCAN.filterMode = settings.value("filterMode").toInt();
    m_config.filterCAN.filterScale = settings.value("filterScale").toInt();
    m_config.filterCAN.fifoBuffer = settings.value("fifoBuffer").toInt();
    settings.endGroup();

    ui->lineEdit_PortName->setText(m_config.serial.portName);

    switch (m_config.serial.baudRate)
    {
    case 115200:
        ui->comboBox_Baud->setCurrentIndex(0);
        break;
    case 9600:
        ui->comboBox_Baud->setCurrentIndex(1);
        break;
    default:
        break;
     }

    switch (m_config.serial.dataBits)
     {
     case 8:
        ui->comboBox_DataBit->setCurrentIndex(0);
        break;
     case 7:
        ui->comboBox_DataBit->setCurrentIndex(1);
        break;
     case 6:
        ui->comboBox_DataBit->setCurrentIndex(2);
        break;
     case 5:
        ui->comboBox_DataBit->setCurrentIndex(3);
        break;
     default:
        ui->comboBox_DataBit->setCurrentIndex(0);
        m_config.serial.dataBits=8;
        break;
     }

    switch (m_config.serial.parity)
     {
     case 0:
         ui->comboBox_Parity->setCurrentIndex(0);
         break;
     case 2:
         ui->comboBox_Parity->setCurrentIndex(1);
         break;
     case 3:
         ui->comboBox_Parity->setCurrentIndex(2);
         break;
     case 4:
         ui->comboBox_Parity->setCurrentIndex(3);
         break;
     case 5:
         ui->comboBox_Parity->setCurrentIndex(4);
         break;
     default:
         break;
     }

    switch (m_config.serial.stopBit)
     {
     case 1:
         ui->comboBox_StopBits->setCurrentIndex(0);
         break;
     case 2:
         ui->comboBox_StopBits->setCurrentIndex(1);
         break;
     case 3:
         ui->comboBox_StopBits->setCurrentIndex(2);
         break;
     default:
         break;
     }



    ui->comboBox_Filter_Mode->setCurrentIndex(m_config.filterCAN.filterMode);


    ui->comboBox_Filter_Scale->setCurrentIndex(m_config.filterCAN.filterScale);

    ui->comboBox_FifoBuffer->setCurrentIndex(m_config.filterCAN.fifoBuffer);




}

void Config::loadCANconfigFromFile()
{
    QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;

    settings.beginGroup("CANbus");
    m_config.canbus.baudrate = settings.value("baudRate").toInt();
    m_config.canbus.busCoupling=settings.value("busCoupling").toInt();
    m_config.canbus.protocol=settings.value("protocol").toInt();
    m_config.canbus.detectError=settings.value("detectError").toBool();
    m_config.canbus.txPassive=settings.value("txPassive").toBool();
    settings.endGroup();

   if(m_config.canbus.baudrate>=3) {
        qDebug()<< "Error CAN bautrate:" <<m_config.canbus.baudrate;
        m_config.canbus.baudrate=0;
    }
    ui->comboBox_CANspeed->setCurrentIndex(m_config.canbus.baudrate);

    if(m_config.canbus.busCoupling>=3) {
         qDebug()<< "Error CAN busCoupling:" <<m_config.canbus.busCoupling;
         m_config.canbus.busCoupling=0;
     }
     ui->comboBox_CANcoupling->setCurrentIndex(m_config.canbus.busCoupling);


    if(m_config.canbus.protocol>=3)
    {
        qDebug()<< "Error CAN protocol:" <<m_config.canbus.protocol;
        m_config.canbus.protocol=0;
    }
    ui->comboBox_CAN_protocol->setCurrentIndex(m_config.canbus.protocol);


    ui->checkBox_detectError->setChecked(m_config.canbus.detectError);
    ui->checkBox_txPassive->setChecked(m_config.canbus.txPassive);

}


void Config::loadFiltersStatus()
{
    QString group;
    QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;
    for (int i=0; i<=13; i++)
    {
        settings.beginGroup("Filter"+QString::number(i));
        m_config.filter[i].status=settings.value("status").toBool();
        settings.endGroup();

        if (m_config.filter[i].status)
        {
            ui->tableWidget_Filters->item(i,0)->setCheckState(Qt::Checked);
        }
        else
        {
            ui->tableWidget_Filters->item(i,0)->setCheckState(Qt::Unchecked);
        }
    }
}

void Config::on_lineEdit_PortName_editingFinished()
{
    m_config.serial.portName = ui->lineEdit_PortName->text();
    qDebug()<<"m_config.serial.portName:"<<m_config.serial.portName;
}

void Config::on_comboBox_Baud_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        m_config.serial.baudRate = QSerialPort::Baud115200;
        break;
    case 1:
        m_config.serial.baudRate = QSerialPort::Baud9600;
        break;
   default:
       break;
   }
    qDebug()<<"m_config.serial.baudRate:"<<m_config.serial.baudRate;
}

void Config::on_comboBox_Parity_currentIndexChanged(int index)
{
    switch (ui->comboBox_Parity->currentIndex())
    {
    case 0:
        m_config.serial.parity = QSerialPort::NoParity;
        break;
    case 1:
        m_config.serial.parity = QSerialPort::EvenParity;
        break;
    case 2:
        m_config.serial.parity = QSerialPort::OddParity;
        break;
    case 3:
        m_config.serial.parity = QSerialPort::SpaceParity;
        break;
    case 4:
        m_config.serial.parity = QSerialPort::MarkParity;
        break;
    default :
        break;
    }
    qDebug()<<"m_config.serial.parity:"<<m_config.serial.parity ;
}

void Config::on_comboBox_StopBits_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        m_config.serial.stopBit=QSerialPort::OneStop;
        break;
    case 1:
        m_config.serial.stopBit=QSerialPort::TwoStop;
        break;
    case 2:
        m_config.serial.stopBit=QSerialPort::OneAndHalfStop;
        break;
    default:
        break;
    }
   qDebug()<<"m_config.serial.stopBit:"<<m_config.serial.stopBit ;
}

void Config::on_comboBox_DataBit_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        m_config.serial.dataBits=QSerialPort::Data8;
        break;
    case 1:
        m_config.serial.dataBits=QSerialPort::Data7;
        break;
    case 2:
        m_config.serial.dataBits=QSerialPort::Data6;
        break;
    case 3:
        m_config.serial.dataBits=QSerialPort::Data5;
        break;
    default:
        break;
    }
    qDebug()<<"m_config.serial.dataBits:"<<m_config.serial.dataBits ;
}





void Config::on_comboBox_Filter_Mode_currentIndexChanged(int index)
{
    QString filterMode;
    m_config.filterCAN.filterMode =index;
    qDebug()<<"m_config.filterCAN.filterMode:"<<m_config.filterCAN.filterMode ;
}

void Config::on_comboBox_Filter_Scale_currentIndexChanged(int index)
{
    m_config.filterCAN.filterScale = index;

    qDebug()<<"m_config.filterCAN.filterScale ="<<m_config.filterCAN.filterScale ;
}

void Config::on_comboBox_FifoBuffer_currentIndexChanged(int index)
{
    m_config.filterCAN.fifoBuffer = index;
    qDebug()<<"m_config.filterCAN.fifoBuffer ="<<m_config.filterCAN.fifoBuffer;
}

void Config::on_tableWidget_Filters_itemChanged(QTableWidgetItem *item)
{
    int row=item->row();
    int column=item->column();
    bool checkState=item->checkState();
    QString columnData=item->text();

    switch (column) {
    case 0:
        m_config.filter[row].status = checkState;
        if(m_config.filter[row].status)
        {
            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::black);

        }
        else
        {
            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::gray);
        }
        break;
    case 1:
        m_config.filter[row].data1=Config::testInputData(columnData);
        ui->tableWidget_Filters->item(row,column)->setText(m_config.filter[row].data1);
        if(m_config.filter[row].status)
        {
            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::black);

        }
        else
        {
            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::gray);
        }
        break;
    case 2:
        m_config.filter[row].data2=Config::testInputData(columnData);
        ui->tableWidget_Filters->item(row,column)->setText(m_config.filter[row].data2);
        if(m_config.filter[row].status)
        {
            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::black);

        }
        else
        {
            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::gray);
        }

        break;
    case 3:
        m_config.filter[row].data3=Config::testInputData(columnData);
        ui->tableWidget_Filters->item(row,column)->setText(m_config.filter[row].data3);
        if(m_config.filter[row].status)
        {
            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::black);

        }
        else
        {
            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::gray);
        }

        break;
    case 4:
        m_config.filter[row].data4=Config::testInputData(columnData);
        ui->tableWidget_Filters->item(row,column)->setText(m_config.filter[row].data4);


        if(m_config.filter[row].status)
        {
            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::black);
            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::black);

        }
        else
        {
            ui->tableWidget_Filters->item(row,1)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,2)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,3)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,4)->setTextColor(Qt::gray);
            ui->tableWidget_Filters->item(row,5)->setTextColor(Qt::gray);
        }

        break;
    default:
        break;
    }
    qDebug()<<"write to File"<<"row:"<<row<<"column:"<<column<<"columnData:"<<columnData<<checkState;
}


void Config::on_pushButton_WriteToFile_clicked()
{
    QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;


    settings.beginGroup("InputDevice");
    settings.setValue("Port", m_config.inpDevice.Port);
    settings.endGroup();




    settings.beginGroup("SerialPort");
    settings.setValue("portName",m_config.serial.portName);
    settings.setValue("baudRate",m_config.serial.baudRate);
    settings.setValue("dataBits",m_config.serial.dataBits);
    settings.setValue("parity",m_config.serial.parity);
    settings.setValue("stopBit",m_config.serial.stopBit);
    settings.endGroup();

    settings.beginGroup("CANbus");
    settings.setValue("baudRate",m_config.canbus.baudrate);
    settings.setValue("busCoupling",m_config.canbus.busCoupling);
    settings.setValue("protocol",m_config.canbus.protocol);
    settings.setValue("detectError",m_config.canbus.detectError);
    settings.setValue("txPassive",m_config.canbus.txPassive);
    settings.endGroup();

    settings.beginGroup("FilterCAN");
    settings.setValue("filterMode",m_config.filterCAN.filterMode);
    settings.setValue("filterScale",m_config.filterCAN.filterScale);
    settings.setValue("fifoBuffer",m_config.filterCAN.fifoBuffer);
    settings.endGroup();

    for (int i=0; i<=13; i++)
    {
        settings.beginGroup("Filter"+QString::number(i));
        settings.setValue("status",m_config.filter[i].status);
        settings.setValue("data1",m_config.filter[i].data1);
        settings.setValue("data2",m_config.filter[i].data2);
        settings.setValue("data3",m_config.filter[i].data3);
        settings.setValue("data4",m_config.filter[i].data4);
        settings.endGroup();
        qDebug()<<"write data to File"<<m_config.filter[i].data1<<m_config.filter[i].data2<<m_config.filter[i].data3<<m_config.filter[i].data4;

    }
    settings.beginGroup("File");
    settings.setValue("inputFile",m_config.file.fileName);
    settings.endGroup();

    reject();
}

void Config::on_pushButton_cancel_clicked()
{
    reject();
}

QString Config::testInputData(QString hexData)
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

void Config::on_pushButton_OpenFile_clicked()
{
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Select current File"),
                "C://",
                "type files (*.ini); (*.txt)"
                );
    m_config.file.fileName = filename;
    ui->lineEdit_fileName->setText(m_config.file.fileName);
    qDebug()<<"File name:"<<m_config.file.fileName;
}

void Config::on_pushButton_SaveFile_clicked()
{
    QString filename=QFileDialog::getSaveFileName(
                this,
                tr("Create new File"),
                "C://",
                "type files (*.ini);(*.txt)"
                );
    m_config.file.fileName = filename;
    ui->lineEdit_fileName->setText(m_config.file.fileName);
    qDebug()<<"File name:"<<m_config.file.fileName;
}

void Config::on_comboBox_inputDevices_currentIndexChanged(int index)
{
    m_config.inpDevice.Port=index;
    switch (index) {
    case 0:

        ui->groupBox_File->setEnabled(false);
        ui->groupBox_Serial->setEnabled(true);
        break;
    case 1:
        ui->groupBox_File->setEnabled(true);
        ui->groupBox_Serial->setEnabled(false);
        break;
    }

    qDebug()<<"Input Devices"<<index;
}

void Config::on_comboBox_CANspeed_currentIndexChanged(int index)
{
    m_config.canbus.baudrate=index;
}

void Config::on_comboBox_CAN_protocol_currentIndexChanged(int index)
{
    m_config.canbus.protocol=index;
}

void Config::on_checkBox_detectError_released()
{
    m_config.canbus.detectError=ui->checkBox_detectError->checkState();
}


void Config::on_comboBox_CANcoupling_currentIndexChanged(int index)
{
    m_config.canbus.busCoupling=index;
}



void Config::on_checkBox_txPassive_released()
{
    m_config.canbus.txPassive=ui->checkBox_txPassive->checkState();
}





//void Config::on_comboBox_Baud_currentIndexChanged(const QString &arg1)
//{

//}

//void Config::on_comboBox_Baud_currentIndexChanged(int index)
//{

//}

//void Config::on_comboBox_Parity_currentIndexChanged(int index)
//{

//}

//void Config::on_comboBox_StopBits_currentIndexChanged(int index)
//{

//}
