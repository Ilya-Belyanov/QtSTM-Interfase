#include "mainwindow.hpp"
#include "../view/ui_mainwindow.h"

#include <QMessageBox>

#include "serialportdialog.hpp"
#include "serialportcommunicationdialog.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial_port = std::make_shared<SerialPortHead>();

    connect(ui->actionConnection, &QAction::triggered, this, &MainWindow::openConnectionDialog);
    connect(ui->actionCommunication, &QAction::triggered, this, &MainWindow::openCommunicationDialog);
    connect(serial_port.get(), SIGNAL(error(QString)), this, SLOT(errorWindow(QString)));
    connect(serial_port.get(), SIGNAL(message(QString)), this, SLOT(errorWindow(QString)));
    connect(serial_port.get(), SIGNAL(isOpenChanged(bool)), this, SLOT(updateVisible()));

    // Values -> Sender
    _sender.setSerialPort(serial_port);
    connect(_db._servo_a.get(), SIGNAL(requestValueChanged(int)), &_sender, SLOT(setServoADegree(int)));
    connect(_db._servo_b.get(), SIGNAL(requestValueChanged(int)), &_sender, SLOT(setServoBDegree(int)));

    // Ui -> Values
    ui->ServoAWidget->setModel(_db._servo_a);
    ui->servoBWidget->setModel(_db._servo_b);
    updateVisible();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::errorWindow(const QString &error)
{
    QMessageBox::critical(this, "Error", error.toUtf8());
}

void MainWindow::messageWindow(const QString &msg)
{
    QMessageBox::information(this, "Message", msg.toUtf8());
}

void MainWindow::updateVisible()
{
    bool isOpen = serial_port->isOpen();
    ui->ServoAWidget->setEnabled(isOpen);
    ui->servoBWidget->setEnabled(isOpen);
}

void MainWindow::openConnectionDialog()
{
    SerialPortDialog *dialog = new SerialPortDialog(this);
    dialog->setSerialPort(serial_port);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
}

void MainWindow::openCommunicationDialog()
{
    SerialPortCommunicationDialog *dialog = new SerialPortCommunicationDialog(this);
    dialog->setSerialPort(serial_port);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
}

