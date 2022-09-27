#include "serialporthandler.hpp"
#include <QByteArray>
#include <QDebug>

SerialPortHead::SerialPortHead(QObject *parent)
    : QObject{parent}
{
    connect(&_serial,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError))); // подключаем проверку ошибок порта
    QObject::connect(&_serial, &QSerialPort::readyRead,this, &SerialPortHead::readFromPort);//подключаем   чтение с порта по сигналу readyRead()
}

void SerialPortHead::setSettings(const PortSettings &settings)
{
    _settings_port = settings;
}

void SerialPortHead::disconnectPort()
{
    if(_serial.isOpen())
    {
        _serial.close();
        emit error(_settings_port.name.toLocal8Bit() + " >> Closed!\r");
    }
}

void SerialPortHead::connectPort()
{
    _serial.setPortName(_settings_port.name);
    if (!_serial.open(QIODevice::ReadWrite))
    {
        _serial.close();
        emit error(_serial.errorString().toLocal8Bit());
    }

    if (_serial.setBaudRate(_settings_port.baudRate)
            && _serial.setDataBits(_settings_port.dataBits)//DataBits
            && _serial.setParity(_settings_port.parity)
            && _serial.setStopBits(_settings_port.stopBits)
            && _serial.setFlowControl(_settings_port.flowControl))
    {
        if (_serial.isOpen())
        {
            emit error((_settings_port.name+ " >> Opened!\r").toLocal8Bit());
        }
    }
    else
    {
        _serial.close();
        emit error(_serial.errorString().toLocal8Bit());
    }
}

void SerialPortHead::write(const QByteArray &bytes)
{
    if(!_serial.isOpen())
        return;
    qDebug() << _serial.write(bytes.data());
}

void SerialPortHead::handleError(QSerialPort::SerialPortError error)
{
    if ( (_serial.isOpen()) && (error == QSerialPort::ResourceError)) {
        emit this->error(_serial.errorString().toLocal8Bit());
        disconnectPort();
    }
}

void SerialPortHead::readFromPort()
{
    QByteArray data;
    data.append(_serial.readAll());
    QString s_data = QString(data);
    emit this->data(s_data);
    qDebug() << s_data << data << QString::fromUtf8(data);
}
