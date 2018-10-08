#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QTimer>
#include <QQueue>


//#include "inp_serial.h"
//#include "messageprocessor.h"
//#include "hmi.h"
//#include "inp_file.h"
//#include "logfile.h"


#include <QStatusBar>
#include <QTableWidget>

#include "hmi.h"
//#include "hmi/hmi_status.h"

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

//    Hmi * hmi_message;

    QTableWidget * m_table_monitor;
    QTableWidget * m_table_tx;
    QTableWidget * m_table_info;
    QTableWidget * m_table_filters;
//    QStatusBar * m_statusBar;


private slots:
    void on_pushButton_clicked();

    void on_actionPort_triggered();

    void on_actionClear_Monitor_triggered();

    void on_actionCliar_Info_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
