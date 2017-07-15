#include "client.h"
#include <QTcpSocket>
#include <QTextStream>

static inline QByteArray IntToArray(qint32 source);

Client::Client(QObject *parent) : QObject(parent)
{
    connect(&client,SIGNAL(connected()),
            this,SLOT(startTransfer()));
    connect(&client,SIGNAL(readyRead()),
            this,SLOT(startRead()));

}

void Client::start(QString address, quint16 port)
{
    QHostAddress addr(address);
    client.connectToHost(addr,port);

}

void Client::getText(const QString &in)
{
    textTemp = in.toUtf8();
    startTransfer();
}

QString Client::callMeFromQml()
{
    return receivedData;
}

void Client::startTransfer()
{
    client.write(IntToArray(textTemp.size()));
    client.write(textTemp);
}

void Client::startRead()
{
    while(client.bytesAvailable())
    {
        receivedData = client.readAll();
    }
    receivedData.replace(0,4,"");
}


QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
