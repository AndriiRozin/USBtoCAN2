#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QTableWidget>

#include "hmi.h"
#include "hmi/hmi_status.h"

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
//    QStatusBar * m_statusBar;


private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
