#include "serialportcommunicationdialog.hpp"
#include "../view/ui_serialportcommunicationdialog.h"

#include <QDebug>
#include <QMessageBox>

SerialPortCommunicationDialog::SerialPortCommunicationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortCommunicationDialog)
{
    ui->setupUi(this);

    connect(ui->sendPushBtn, &QPushButton::clicked, this, &SerialPortCommunicationDialog::sendData);
    connect(ui->clearRecievesButton, &QToolButton::clicked, ui->recieveTextEdit, &QTextEdit::clear);
    connect(ui->clearRequestsButton, &QToolButton::clicked, ui->requestsTextEdit, &QTextEdit::clear);
}

SerialPortCommunicationDialog::~SerialPortCommunicationDialog()
{
    delete ui;
    if(_serial_port)
        disconnectPort();
    qDebug() << "DELETE SerialPortCommunicationDialog";
}

void SerialPortCommunicationDialog::setSerialPort(std::shared_ptr<SerialPortHead> serial_port)
{
    if(_serial_port)
        disconnectPort();
    _serial_port = serial_port;
    connectPort();
}

void SerialPortCommunicationDialog::viewData(const QByteArray &data)
{
    ui->recieveTextEdit->append(QString(data));
}

void SerialPortCommunicationDialog::sendData()
{
    if(!_serial_port->isOpen())
    {
        QMessageBox::critical(this, "Error", "Port doesn't open!");
        return;
    }
    QByteArray data = ui->sendLineEdit->text().toUtf8();
    ui->requestsTextEdit->append(data);
    _serial_port->write(data);
}

void SerialPortCommunicationDialog::connectPort()
{
    connect(_serial_port.get(), SIGNAL(data(QByteArray)), this, SLOT(viewData(QByteArray)));
}

void SerialPortCommunicationDialog::disconnectPort()
{
    disconnect(_serial_port.get(), SIGNAL(data(QByteArray)), this, SLOT(viewData(QByteArray)));
}
