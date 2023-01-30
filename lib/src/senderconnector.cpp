#include "senderconnector.hpp"

SenderConnector::SenderConnector(const Database *db,
                                 CommandSender *sender,
                                 QObject *parent)
    : QObject(parent),
      _db(db),
      _sender(sender)
{

}

bool SenderConnector::connectDbToSender()
{
    if(!_db || !_sender)
        return false;
    connect(_db->_servo_a.get(), SIGNAL(requestValueChanged(QVariant)), this, SLOT(setServoADegree(QVariant)));
    connect(_db->_servo_b.get(), SIGNAL(requestValueChanged(QVariant)), this, SLOT(setServoBDegree(QVariant)));
    connect(_db->_step_driver_a.get(), SIGNAL(requestValueChanged(QVariant)), this, SLOT(setStepAPosition(QVariant)));
    connect(_db->_step_driver_b.get(), SIGNAL(requestValueChanged(QVariant)), this, SLOT(setStepBPosition(QVariant)));
    connect(_db->_step_driver_speed_a.get(), SIGNAL(requestValueChanged(QVariant)), this, SLOT(setStepASpeed(QVariant)));
    connect(_db->_step_driver_speed_b.get(), SIGNAL(requestValueChanged(QVariant)), this, SLOT(setStepBSpeed(QVariant)));
    return true;
}

void SenderConnector::setServoADegree(const QVariant &degree)
{
    _sender->setServoADegree(degree.toInt());
}

void SenderConnector::setServoBDegree(const QVariant &degree)
{
    _sender->setServoBDegree(degree.toInt());
}

void SenderConnector::setStepAPosition(const QVariant &degree)
{
    _sender->setStepDriverAPos(degree.toInt());
}

void SenderConnector::setStepBPosition(const QVariant &degree)
{
    _sender->setStepDriverBPos(degree.toInt());
}

void SenderConnector::setStepASpeed(const QVariant &speed)
{
    _sender->setStepDriverASpeed(speed.toInt());
}

void SenderConnector::setStepBSpeed(const QVariant &speed)
{
    _sender->setStepDriverBSpeed(speed.toInt());
}
