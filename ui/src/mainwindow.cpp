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

    // Values -> Sender
    _sender.setSerialPort(serial_port);
    connect(_db._servo_a.get(), SIGNAL(requestValueChanged(int)), &_sender, SLOT(setServoADegree(int)));

    // Ui -> Values
    ui->ServoAWidget->setModel(_db._servo_a);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::errorWindow(const QString &error)
{
    QMessageBox::critical(this, "Error", error.toUtf8());
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

