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
    connect(ui->disconnectPushBtn, &QPushButton::clicked, this, &SerialPortDialog::disconnectPort);

    searchPorts();
}

SerialPortDialog::~SerialPortDialog()
{
    delete ui;
}

void SerialPortDialog::setSerialPort(std::shared_ptr<SerialPortHead> serial_port)
{
    if(_serial_port)
        disconnectSignalPort();
    _serial_port = serial_port;
    connectSignalPort();
    updateVisible();
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

void SerialPortDialog::disconnectPort()
{
    _serial_port->disconnectPort();
}

void SerialPortDialog::connectSignalPort()
{
    connect(_serial_port.get(), SIGNAL(isOpenChanged(bool)), this, SLOT(updateVisible()));
}

void SerialPortDialog::disconnectSignalPort()
{
    disconnect(_serial_port.get(), SIGNAL(isOpenChanged(bool)), this, SLOT(updateVisible()));
}

void SerialPortDialog::updateVisible()
{
    bool isOpen = _serial_port->isOpen();
    ui->searchPushBtn->setEnabled(!isOpen);
    ui->availablePortsComboBox->setEnabled(!isOpen);
    ui->baudRatesComboBox->setEnabled(!isOpen);
    ui->dataBitsComboBox->setEnabled(!isOpen);
    ui->parityComboBox->setEnabled(!isOpen);
    ui->stopBitsComboBox->setEnabled(!isOpen);
    ui->flowControlComboBox->setEnabled(!isOpen);
    ui->connectPushBtn->setEnabled(!isOpen);
    ui->disconnectPushBtn->setEnabled(isOpen);
}
