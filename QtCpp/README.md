
# Qt C++ Version of the 12vDC 2 channel Serial Port RS232 relay Board


Add the RemoteSerialDriver header and unit file to your project.

Include the `QT += serialport` to your projects .PRO file to enable access to
Qt's serial port implementations.

Clear all project files, run QMake and then recompile your application.


Minimal implementation is as follows;

RemoteSerialDriver *m_serialDriver = new RemoteSerialDriver();
QObject::connect(m_remoteSerial, SIGNAL(onMessage(QString)), this, SLOT(processMessage(QString)));
m_remoteSerial->setPortName("/dev/cu.usbserial-0001");
### For a list of available ports you can run m_serialDriver->getAvailablePorts(); which returns a vector of strings.
m_remoteSerial->setSecondsDelay(3); # if you want to use the auto feature.
m_remoteSerial->openPort();

m_remoteSerial->onRelay1();

m_remoteSerial->offRelay1();

### Or you can use the auto feature;

m_serialDriver->autoDelayRelay1();

### Remember to clear your mallocs

m_serialDriver->closePort();
delete m_serialDriver;



