#include "remoteserialdriver.h"

RemoteSerialDriver::RemoteSerialDriver(QObject *parent) : QObject(parent){

    m_connected = false;
    m_milliseconds = 2000; // sane default setting.
    m_portList = QSerialPortInfo::availablePorts();
    qDebug() << "Available Ports:";
    for(int i=0; i<m_portList.count(); i++){
        qDebug() << "   " << m_portList[i].portName() << m_portList[i].systemLocation();
    }
    // pre-prepare the header.
    m_header.append(0x55);
    m_header.append(0x56);
    m_header.append(char(0x00));
    m_header.append(char(0x00));
    m_header.append(char(0x00));
}

RemoteSerialDriver::~RemoteSerialDriver(){
    this->closePort();
}

bool RemoteSerialDriver::setPortName(QString portName){
    if(portName.isEmpty()){
        return false;
    }
    for(int i=0; i<=m_portList.count(); i++){
        if(m_portList[i].systemLocation() == portName){
            m_portName = portName;
            return true;
        }
    }
    // The port wasn't found.
    qDebug() << "Port not found in list.";
    emit onMessage(QString("%1 wasn't in the list of available ports. Check getAvailablePorts().").arg(portName));
    return false;
}

void RemoteSerialDriver::setSecondsDelay(int seconds)
{
    m_milliseconds = seconds * 1000;
}

void RemoteSerialDriver::onRelay1()
{
    sendFrame(char(0x02), char(0x01), char(0xAE));
}

void RemoteSerialDriver::offRelay1()
{
    sendFrame(char(0x02), char(0x02), char(0xAF));
}

void RemoteSerialDriver::onRelay2()
{
    sendFrame(char(0x01), char(0x01), char(0xAD));
}

void RemoteSerialDriver::offRelay2()
{
    sendFrame(char(0x01), char(0x02), char(0xAE));
}

void RemoteSerialDriver::autoDelayRelay1()
{
    QTimer::singleShot(m_milliseconds, this, SLOT(offRelay1()));
}

void RemoteSerialDriver::autoDelayRelay2()
{
    QTimer::singleShot(m_milliseconds, this, SLOT(offRelay2()));
}

QList<QString> RemoteSerialDriver::getAvailablePorts()
{
    QList<QString> ports;
    m_portList = QSerialPortInfo::availablePorts();
    for(int i=0; i<m_portList.count(); i++){
        ports.append(m_portList[i].systemLocation());
    }
    return ports;
}

void RemoteSerialDriver::sendFrame(char chn, char cmd, char val)
{
    if(!m_port)
        openPort();

    QByteArray frame;
    // Assemble the frame.
    frame.append(m_header);
    frame.append(chn); // The channel
    frame.append(cmd); // The command
    frame.append(val); // The payload;
    // Send the frame!
    if(m_port->isOpen() && m_port->isWritable()){
        qint64 bytewrote = m_port->write(frame, frame.length());
        m_port->waitForBytesWritten(100);
        qDebug() << "Wrote:" << bytewrote << "of" << frame.length();
        emit onMessage(QString("Wrote: %1 bytes of %2 bytes").arg(bytewrote).arg(frame.length()));
    }else{
        qDebug() << "Connection is not open for writing." << m_port->errorString();
        emit onMessage(QString("Connection failed: %1").arg(m_port->errorString()));
    }
}

void RemoteSerialDriver::openPort()
{
    emit onMessage(QString("Connecting to %1...").arg(m_portName));
    if(m_port && m_port->isOpen()){
        m_port->disconnect();
    }
    m_port = new QSerialPort(m_portName, this);        // Open connection.
    m_port->setPortName(m_portName);
    QObject::connect(m_port, SIGNAL(readyRead()), this, SLOT(readData()));

    if(m_port->open(QIODevice::ReadWrite)){
        qDebug() << "Opened" << m_portName;
        emit onMessage(QString("%1 open.").arg(m_portName));
        m_port->setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);
        m_port->setFlowControl(QSerialPort::NoFlowControl);
        m_port->setDataBits(QSerialPort::Data8);
        m_port->setParity(QSerialPort::NoParity);
        m_port->setStopBits(QSerialPort::OneStop);
    }else{
       qDebug() << "Failed to open:" << m_port->errorString();
       emit onMessage(QString("Failed to open: %1").arg(m_port->errorString()));
    }
}

void RemoteSerialDriver::closePort()
{
    if(m_port->isOpen()){
        m_port->close();
    }
}

void RemoteSerialDriver::readData()
{
    QByteArray data = m_port->readAll();
    qDebug() << "Data arrived:" << data;
    emit dataReady(data);
}
