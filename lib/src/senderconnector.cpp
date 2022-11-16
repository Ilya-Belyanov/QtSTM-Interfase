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
    connect(_db->_servo_a.get(), SIGNAL(requestValueChanged(const QVariant&)), this, SLOT(setServoADegree(const QVariant&)));
    connect(_db->_servo_b.get(), SIGNAL(requestValueChanged(const QVariant&)), this, SLOT(setServoBDegree(const QVariant&)));
    connect(_db->_step_driver_a.get(), SIGNAL(requestValueChanged(const QVariant&)), this, SLOT(setStepAPosition(const QVariant&)));
    connect(_db->_step_driver_b.get(), SIGNAL(requestValueChanged(const QVariant&)), this, SLOT(setStepBPosition(const QVariant&)));
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
