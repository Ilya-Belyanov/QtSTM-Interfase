#include "mainrecievehandler.hpp"
#include "recieveevents.hpp"

#include <QDebug>

MainRecieveHandler::MainRecieveHandler(QObject *parent) : QObject(parent)
{

}

void MainRecieveHandler::handler(const QString &data)
{
    qDebug() << "Handler" << data;
}

bool MainRecieveHandler::event(QEvent *event)
{
    if(event->type() == RecieveEventType) {
        qDebug() << "Recieve";
        return true;
    }
    return QObject::event(event);
}
