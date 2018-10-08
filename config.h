#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(QWidget *parent = nullptr);
    ~Config();

private slots:

    void on_pushButton_OpenFile_clicked();
    void on_pushButton_SaveFile_clicked();
    void on_comboBox_CANcoupling_currentIndexChanged(int index);
    void on_checkBox_txPassive_released();
    void on_checkBox_detectError_released();
    void on_comboBox_CAN_protocol_currentIndexChanged(int index);
    void on_comboBox_CANspeed_currentIndexChanged(int index);
    void on_comboBox_inputDevices_currentIndexChanged(int index);



    void on_pushButton_WriteToFile_clicked();

    void on_pushButton_cancel_clicked();

    void on_tableWidget_Filters_itemChanged(QTableWidgetItem *item);

    void on_comboBox_FifoBuffer_currentIndexChanged(int index);

    void on_comboBox_Filter_Scale_currentIndexChanged(int index);

    void on_comboBox_Filter_Mode_currentIndexChanged(int index);

    void on_comboBox_DataBit_currentIndexChanged(int index);

    void on_lineEdit_PortName_editingFinished();

   // void on_comboBox_Baud_currentIndexChanged(const QString &arg1);

    void on_comboBox_Baud_currentIndexChanged(int index);

    void on_comboBox_Parity_currentIndexChanged(int index);

    void on_comboBox_StopBits_currentIndexChanged(int index);

private:
    struct SInpDevice
     {
         int Port;

     };
     struct SFile
     {
         QString fileName;
     };
     struct SSerialPort
     {
         QString portName;
         int baudRate;
         int dataBits;
         int parity;
         int stopBit;
     };

     struct SCAN
     {
         int baudrate;
         int busCoupling;
         int protocol;
         bool detectError;
         bool txPassive;
     } ;

     struct SFilterCAN
     {
         int filterMode;
         int filterScale;
         int fifoBuffer;
     };

     struct SFilter
     {
         bool status;
         QString data1;
         QString data2;
         QString data3;
         QString data4;
     };

     struct SConfig
     {
         SInpDevice  inpDevice;
         SFile       file;
         SSerialPort serial;
         SFilterCAN  filterCAN;
         SFilter     filter[14];
         SCAN        canbus;
     } m_config;





    Ui::Config *ui;

    void loadInputDevice();
    void loadSerialConfigFromFile();
    void loadCANconfigFromFile();
    void loadFiltersStatus();
    void createFilterTable();
    void loadFiltersData();
    void loadFileFromFile();
    QString testInputData(QString hexData);
};

#endif // CONFIG_H
