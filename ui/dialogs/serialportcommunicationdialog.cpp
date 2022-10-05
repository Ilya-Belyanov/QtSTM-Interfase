#include "serialportcommunicationdialog.hpp"
#include "../view/ui_serialportcommunicationdialog.h"

#include <QDebug>

SerialPortCommunicationDialog::SerialPortCommunicationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortCommunicationDialog)
{
    ui->setupUi(this);

    connect(ui->sendPushBtn, &QPushButton::clicked, this, &SerialPortCommunicationDialog::sendData);
}

SerialPortCommunicationDialog::~SerialPortCommunicationDialog()
{
    delete ui;
    if(_serial_port)
        disconnect(_serial_port.get(), SIGNAL(data(QString)), this, SLOT(viewData(QString)));
    qDebug() << "DELETE SerialPortCommunicationDialog";
}

void SerialPortCommunicationDialog::setSerialPort(std::shared_ptr<SerialPortHead> serial_port)
{
    _serial_port = serial_port;
    connect(_serial_port.get(), SIGNAL(data(QString)), this, SLOT(viewData(QString)));
}

void SerialPortCommunicationDialog::viewData(const QString &data)
{
    ui->recieveTextEdit->append(data);
}

void SerialPortCommunicationDialog::sendData()
{
    QByteArray data = ui->sendLineEdit->text().toUtf8();
    _serial_port->write(data);
}
