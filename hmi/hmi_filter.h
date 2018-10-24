#ifndef HMI_FILTER_H
#define HMI_FILTER_H
#include "hmi.h"
#include <QtWidgets/QTableWidget>
#include <QHeaderView>

class Hmi_filter: public Hmi
{
public:
    virtual bool hmi_init() override;
    virtual bool draw(QStringList str_list) override;
    virtual bool hmi_key(QStringList strlist) override;

    Hmi_filter(QTableWidget * m_table_filter);
    virtual ~Hmi_filter() override;

private:
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


    void loadFilterFromFile();
    void paintData();

    QTableWidget * m_table_filter;


};

#endif // HMI_FILTER_H
