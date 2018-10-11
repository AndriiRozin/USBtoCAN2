#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QTimer>
#include <QQueue>

#include "hmi.h"

#include <QStatusBar>
#include <QTableWidget>

#include "inp_devices.h"
#include "inp_devices/inp_file.h"
#include "inp_devices/inp_serial.h"

#include "process_message.h"



class Hmi;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    Inp_Devices* device;
    Process_message* message;

    QTableWidget * m_table_monitor;
    QTableWidget * m_table_tx;
    QTableWidget * m_table_info;
    QTableWidget * m_table_filters;
    QStatusBar * m_statusBar;


private slots:
    void on_pushButton_clicked();

    void on_actionPort_triggered();

    void on_actionClear_Monitor_triggered();

    void on_actionCliar_Info_triggered();

    void on_actionOpenPort_triggered();

    void on_actionClosePort_triggered();

    void on_pushButton_ReadPort_clicked();

private:
    struct SRow{
         QString description;
         QString idHex;
         QString rtr;
         QString d0;
         QString d1;
         QString d2;
         QString d3;
         QString d4;
         QString d5;
         QString d6;
         QString d7;
     };

     struct STableTX{
         SRow tx_row[5];
     } mTableTx;

     struct bufferMonitor{
         QString bufferRX;
         QString bufferInfo;
         QString bufferErr;
     } mMessageMonitor;

     struct SFilter{
         QString data1;
         QString data2;
         QString data3;
         QString data4;
         QString configMessage;
         bool status;
     } mFilter;

     struct SCANfilter{
         SFilter filter[14];
         int mode;
         int scale;
         int fifo;
         int baudRate;

     } filterCAN;


    Ui::MainWindow *ui;

       QVector<Process_message*> processListenerVector;
       QQueue<QString> m_queue;
};

#endif // MAINWINDOW_H
