#include "commandsender.hpp"
#include "deviceskeys.hpp"

#include <QDebug>

CommandSender::CommandSender(QObject *parent)
    : QObject{parent}
{

}

void CommandSender::setSerialPort(std::shared_ptr<SerialPortHead> serial_port)
{
    _serial_port = serial_port;
}

void CommandSender::setServoADegree(int degree)
{
    sendCommand(Devices::headers[Devices::SERVO_A], QString::number(degree));
}

void CommandSender::setServoBDegree(int degree)
{
    sendCommand(Devices::headers[Devices::SERVO_B], QString::number(degree));
}

void CommandSender::setStepDriverAPos(int position)
{
    sendCommand(Devices::headers[Devices::STEP_DRIVER_A], QString::number(position));
}

void CommandSender::setStepDriverBPos(int position)
{
    sendCommand(Devices::headers[Devices::STEP_DRIVER_B], QString::number(position));
}

void CommandSender::sendCommand(const QByteArray &head, const QString &value)
{
    qDebug() << head << value;
    _serial_port->write(head + value.toUtf8());
}
