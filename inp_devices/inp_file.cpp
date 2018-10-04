#include "inp_file.h"
#include <QString>
#include <QDebug>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QQueue>

Inp_File::Inp_File(QStatusBar * statusLable)
    : m_statusLable(statusLable)
{
    QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ; //load data from file.ini
    settings.beginGroup("File");
    const QString inpFileName=settings.value("inputFile").toString();
    settings.endGroup();

    qDebug()<<"inputFile:"<<inpFileName;
    mFile.setFileName(inpFileName);
}

Inp_File::~Inp_File()
{
    if (mFile.isOpen()) {
        mFile.close();
    }
}




bool Inp_File::config()
{
    if(QFile::exists(mFile.fileName()))
    {
        qDebug()<<"Inp_File: config:ok"<<mFile.fileName();
        return true;
    }
    else
    {
        qDebug()<<"Inp_File: config:err";
        return false;
    }
}


bool Inp_File::start()
{
    if(!mFile.isOpen()){
        if (mFile.open(QIODevice::ReadWrite | QIODevice::Text)){
            qDebug()<<"Inp_File: start:ok"<<mFile.fileName();
            m_statusLable->showMessage("Input File: open");
            return true;
        }
    }

    else {
        m_statusLable->showMessage("Input File: opening error");
        qDebug()<<"Inp_File: start:";
        return false;
    }
}

bool Inp_File::stop()
{
    if (mFile.isOpen()) {
        mFile.close();
        m_statusLable->showMessage("Input File: close");
        qDebug()<<"Inp_File: stop:ok";

        return true;
    }
    else {
        qDebug()<<"Inp_File: stop:err";
        return false;
    }

}

bool Inp_File::read_DATA(QQueue<QString> & queueData)
{
    if(mFile.isOpen()){
        if(!mFile.atEnd()){
            mFileData.readData += mFile.readLine();
            qDebug()<<"Inp_File:read: "<<mFileData.readData;
            mFileData.readData.remove('\r');
            mFileData.readData.remove('\n');
            Inp_File::parsingMessage(queueData);
            return true;
        }
        else{
            qDebug()<<"Inp_File:read:end";
            return false;
        }
    }
    else{
        qDebug()<<"Inp_File:read:err";
        return false;
    }
}

void Inp_File::parsingMessage(QQueue<QString> & queueData)
{
    /*get message,
     *add message to buffer
     *extract all ready message
     *transmit message to function for analyse
     * startCondition="<"
     * endCondition=">"
    */

     const QChar startCondition='<';
     const QChar endCondition='>';
     int startConditionPosition;
     int endConditionPosition;

     do
     {
         startConditionPosition = mFileData.readData.indexOf(startCondition,0);
         switch (startConditionPosition){
         case -1:                           //"startCondition" not present in message
             mFileData.readData="";
             break;
         case 0:                            //"startCondition" in 0-position
             break;
         default:                           //"startCondition" is present in message
             mFileData.readData.remove(0,startConditionPosition);
             break;
         }

         endConditionPosition= mFileData.readData.indexOf(endCondition,1);     //extract messsage
         if(endConditionPosition !=-1){
            QString newMessage= mFileData.readData.left(endConditionPosition+1);
            mFileData.readData.remove(0,endConditionPosition+1);
            if(newMessage!=""){
                qDebug()<<"inp_file:enqueue:"<<newMessage;
                queueData.enqueue(newMessage);
            }
         }
     }
     while (endConditionPosition !=-1);

}

QString Inp_File::write_DATA(QString data)
{
    if(mFile.isOpen()){
        QTextStream out(&mFile);
        out<<data;
        qDebug()<<"Inp_File:write: "<<data;
        return "ok";
    }
    else{
        qDebug()<<"Inp_File: write:err";
        return "err";
    }
}



