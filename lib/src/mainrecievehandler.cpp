#include "mainrecievehandler.hpp"
#include "recieveevents.hpp"

#include "deviceskeys.hpp"

#include <QDebug>

MainRecieveHandler::MainRecieveHandler(QObject *parent) :
    QObject(parent),
    _db(nullptr)
{

}

void MainRecieveHandler::handler(const QByteArray &data)
{
    qDebug() << "Handler " << QString(data);
    QByteArray code = data.mid(0, 2);
    if(code == Devices::headers[Devices::STEP_DRIVER_A])
    {
        QByteArray number = data.mid(2, -1);
        qDebug() << "NUMBER " << number.toInt();
        _db->_step_driver_a->setRealValue(number.toInt());
    }
    else if(code == Devices::headers[Devices::STEP_DRIVER_B])
    {
        QByteArray number = data.mid(2, -1);
        _db->_step_driver_b->setRealValue(number.toInt());
    }
}

bool MainRecieveHandler::event(QEvent *event)
{
    if(event->type() == RecieveEventType) {
        qDebug() << "Recieve";
        return true;
    }
    return QObject::event(event);
}
