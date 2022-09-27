#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial_port = std::make_unique<SerialPortHead>();

    connect(ui->searchPortsPushBtn, &QPushButton::clicked, this, &MainWindow::searchPorts);
    connect(ui->connectPushBtn, &QPushButton::clicked, this, &MainWindow::connectPort);
    connect(ui->sendPushBtn, &QPushButton::clicked, this, &MainWindow::sendData);

    connect(serial_port.get(), &SerialPortHead::error, this, &MainWindow::errorWindow);
    connect(serial_port.get(), &SerialPortHead::data, this, &MainWindow::viewData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::errorWindow(const QString &error)
{
    QMessageBox::critical(this, "Error", error.toUtf8());
}

void MainWindow::viewData(const QString &data)
{
    ui->dataTextEdit->append(data);
}

void MainWindow::searchPorts()
{
    _availablePorts = QSerialPortInfo::availablePorts();
    ui->availablePortsComboBox->clear();
    for(int i = 0; i < _availablePorts.size(); i++)
        ui->availablePortsComboBox->addItem(_availablePorts[i].portName());
}

void MainWindow::connectPort()
{
    PortSettings sett;
    int index = ui->availablePortsComboBox->currentIndex();
    if (index == -1)
        return;
    QSerialPortInfo port = _availablePorts.at(index);
    sett.name = port.portName();
    sett.baudRate = (QSerialPort::BaudRate) ui->baudRateComboBox->currentText().toInt();
    sett.dataBits = (QSerialPort::DataBits) ui->dataBitsComboBox->currentText().toInt();
    sett.parity = QSerialPort::NoParity;
    sett.stopBits = QSerialPort::OneStop;
    sett.flowControl = QSerialPort::NoFlowControl;

    serial_port->setSettings(sett);
    serial_port->connectPort();
}

void MainWindow::sendData()
{
    QByteArray data = ui->writeLineEdit->text().toUtf8();
    serial_port->write(data);
}

