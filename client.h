#include <QtCore>
#include <QtNetwork>
#include <QTcpSocket>


class QTcpSocket;
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void start(QString address, quint16 port);

public slots:
    void getText(const QString& in);
    QString callMeFromQml();
    void startTransfer();
    void startRead();

private:
    QTcpSocket client;
    QByteArray textTemp;
    QByteArray receivedData;

};
