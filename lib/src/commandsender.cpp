#include "commandsender.hpp"

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
    sendCommand(headers[SERVO_A], QString::number(degree));
}

void CommandSender::setServoBDegree(int degree)
{
    sendCommand(headers[SERVO_B], QString::number(degree));
}

void CommandSender::setStepDriverAPos(int position)
{
    sendCommand(headers[STEP_DRIVER_A], QString::number(position));
}

void CommandSender::setStepDriverBPos(int position)
{
    sendCommand(headers[STEP_DRIVER_B], QString::number(position));
}

void CommandSender::sendCommand(const QString &head, const QString &value)
{
    _serial_port->write(head.toUtf8() + value.toUtf8());
}
