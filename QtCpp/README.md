
# Qt C++ Version of the 12vDC 2 channel Serial Port RS232 relay Board


Add the RemoteSerialDriver header and unit file to your project.

Include the `QT += serialport` to your projects .PRO file to enable access to
Qt's serial port implementations.

Clear all project files, run QMake and then recompile your application.

## Available methods
```
bool setPortName(QString)
void setSecondsDelay()
void getAvailablePorts()

void autoDelayRelay1()
void autoDelayRelay1()
```

`setPortName` returns a bool as it will only return true if the portName requested
was in the list of port names it can find.

## Available Qt Slots
```
void openPort()
void closePort()

void onRelay1()
void offRelay1()

void onRelay2()
void offRelay()
```

## Available Signals
```
void onMessage(QString)
void dataRead(QByteArray)
```

Minimal implementation is as follows;
```
RemoteSerialDriver *m_serialDriver = new RemoteSerialDriver();
QObject::connect(m_remoteSerial, SIGNAL(onMessage(QString)), this, SLOT(processMessage(QString)));
m_remoteSerial->setPortName("/dev/cu.usbserial-0001");
```
The signature for the `processMessage` method to receive any communication in
your app is as follows;

```
void processMessage(QString message);
```

### For a list of available ports you can run m_serialDriver->getAvailablePorts(); which returns a vector of strings.
```
m_remoteSerial->setSecondsDelay(3); # if you want to use the auto feature.
m_remoteSerial->openPort();

m_remoteSerial->onRelay1();

m_remoteSerial->offRelay1();
```
### Or you can use the auto feature;
```
m_serialDriver->autoDelayRelay1();
```

### Remember to release your mallocs
```
m_serialDriver->closePort();
delete m_serialDriver;
```

Example output when looping the Available Ports method.
```
Available Ports:
    "cu.wlan-debug" "/dev/cu.wlan-debug"
    "tty.wlan-debug" "/dev/tty.wlan-debug"
    "cu.UEBOOM" "/dev/cu.UEBOOM"
    "tty.UEBOOM" "/dev/tty.UEBOOM"
    "cu.Bluetooth-Incoming-Port" "/dev/cu.Bluetooth-Incoming-Port"
    "tty.Bluetooth-Incoming-Port" "/dev/tty.Bluetooth-Incoming-Port"
    "cu.usbserial-0001" "/dev/cu.usbserial-0001"
    "tty.usbserial-0001" "/dev/tty.usbserial-0001"
    "cu.SLAB_USBtoUART" "/dev/cu.SLAB_USBtoUART"
    "tty.SLAB_USBtoUART" "/dev/tty.SLAB_USBtoUART"
Opened "/dev/cu.usbserial-0001"
```
