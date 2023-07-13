#ifndef REMOTESERIALDRIVER_H
#define REMOTESERIALDRIVER_H

#include <QObject>
#include <QByteArray>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

#include <QDebug>

class RemoteSerialDriver : public QObject
{
    Q_OBJECT
public:
    explicit RemoteSerialDriver(QObject *parent = nullptr);
    ~RemoteSerialDriver();

    bool setPortName(QString portName);     // Eg. COM1
    void setSecondsDelay(int seconds);      // Eg. 3, will auto trigger offRelay if using autoDelayRelay
    // Turns relay on, then off after setSecondsDelay.
    void autoDelayRelay1();
    void autoDelayRelay2();
    QList<QString> getAvailablePorts();

private:
    void sendFrame(char chn, char cmd, char val);

    bool m_connected;
    QList<QSerialPortInfo> m_portList;
    QByteArray m_header;
    QSerialPort *m_port;
    QString m_portName;
    uint m_milliseconds;

public slots:
    void openPort();
    void closePort();
    // Turn relay1 on and off
    void onRelay1();
    void offRelay1();
    // Turn relay2 on and off.
    void onRelay2();
    void offRelay2();

private slots:
    void readData();

signals:
    void onConnect();
    void onDisconnect();
    void onMessage(QString msg);
    void dataReady(QString msg);
};

#endif // REMOTESERIALDRIVER_H
