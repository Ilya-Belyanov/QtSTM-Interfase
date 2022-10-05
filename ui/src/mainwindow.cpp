#include "mainwindow.hpp"
#include "../view/ui_mainwindow.h"
#include "serialportdialog.hpp"
#include "serialportcommunicationdialog.hpp"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial_port = std::make_shared<SerialPortHead>();

    connect(ui->actionConnection, &QAction::triggered, this, &MainWindow::openConnectionDialog);
    connect(ui->actionCommunication, &QAction::triggered, this, &MainWindow::openCommunicationDialog);
    connect(serial_port.get(), SIGNAL(error(QString)), this, SLOT(errorWindow(QString)));
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

