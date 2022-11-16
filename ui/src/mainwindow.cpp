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

    // Передаем обработчику базу
    _recieve_handler.setDB(&_db);

    // Действия
    connect(ui->actionConnection, &QAction::triggered, this, &MainWindow::openConnectionDialog);
    connect(ui->actionCommunication, &QAction::triggered, this, &MainWindow::openCommunicationDialog);

    // Сообщения с порта об ошибках и прочее
    connect(serial_port.get(), SIGNAL(error(QString)), this, SLOT(errorWindow(QString)));
    connect(serial_port.get(), SIGNAL(message(QString)), this, SLOT(errorWindow(QString)));
    connect(serial_port.get(), SIGNAL(isOpenChanged(bool)), this, SLOT(updateVisible()));

    // Подключаем обработчик сообщений
    connect(serial_port.get(), SIGNAL(data(const QString&)), &_recieve_handler, SLOT(handler(const QString&)));

    // Values -> Sender
    _sender.setSerialPort(serial_port);
    connect(_db._servo_a.get(), SIGNAL(requestValueChanged(const QVariant&)), this, SLOT(setServoADegree(const QVariant&)));
    connect(_db._servo_b.get(), SIGNAL(requestValueChanged(const QVariant&)), this, SLOT(setServoBDegree(const QVariant&)));
    connect(_db._step_driver_a.get(), SIGNAL(requestValueChanged(const QVariant&)), this, SLOT(setStepAPosition(const QVariant&)));
    connect(_db._step_driver_b.get(), SIGNAL(requestValueChanged(const QVariant&)), this, SLOT(setStepBPosition(const QVariant&)));

    // Ui -> Values
    ui->ServoAWidget->setModel(_db._servo_a);
    ui->servoBWidget->setModel(_db._servo_b);
    ui->stepAWidget->setModel(_db._step_driver_a);
    ui->stepBWidget->setModel(_db._step_driver_b);
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
    ui->stepAWidget->setEnabled(isOpen);
    ui->stepBWidget->setEnabled(isOpen);
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

void MainWindow::setServoADegree(const QVariant &degree)
{
    _sender.setServoADegree(degree.toInt());
}

void MainWindow::setServoBDegree(const QVariant &degree)
{
    _sender.setServoBDegree(degree.toInt());
}

void MainWindow::setStepAPosition(const QVariant &degree)
{
    _sender.setStepDriverAPos(degree.toInt());
}

void MainWindow::setStepBPosition(const QVariant &degree)
{
    _sender.setStepDriverBPos(degree.toInt());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    bool serialIsOpen = serial_port->isOpen();
    if(!serialIsOpen)
    {
        event->accept();
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Port is open, close and quit?",
                                  QMessageBox::Yes |QMessageBox::No);

    if(reply == QMessageBox::No )
    {
        event->ignore();
        return;
    }
    serial_port->disconnectPort();
    event->accept();
}

