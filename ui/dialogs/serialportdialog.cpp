#include "serialportdialog.hpp"
#include "../view/ui_serialportdialog.h"

SerialPortDialog::SerialPortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortDialog),
    _serial_port(nullptr)
{
    ui->setupUi(this);

    connect(ui->searchPushBtn, &QPushButton::clicked, this, &SerialPortDialog::searchPorts);
    connect(ui->connectPushBtn, &QPushButton::clicked, this, &SerialPortDialog::connectPort);

    searchPorts();
}

SerialPortDialog::~SerialPortDialog()
{
    delete ui;
}

void SerialPortDialog::setSerialPort(std::shared_ptr<SerialPortHead> serial_port)
{
    _serial_port = serial_port;
}

void SerialPortDialog::searchPorts()
{
    _available_ports = QSerialPortInfo::availablePorts();
    ui->availablePortsComboBox->clear();
    foreach(auto port, _available_ports)
        ui->availablePortsComboBox->addItem(port.portName());
}

void SerialPortDialog::connectPort()
{
    PortSettings sett;
    int index = ui->availablePortsComboBox->currentIndex();
    if (index == -1)
        return;
    QSerialPortInfo port = _available_ports.at(index);
    sett.name = port.portName();
    sett.baudRate = (QSerialPort::BaudRate) ui->baudRatesComboBox->currentText().toInt();
    sett.dataBits = (QSerialPort::DataBits) ui->dataBitsComboBox->currentText().toInt();
    sett.parity = QSerialPort::NoParity;
    sett.stopBits = QSerialPort::OneStop;
    sett.flowControl = QSerialPort::NoFlowControl;

    _serial_port->setSettings(sett);
    _serial_port->connectPort();
}
