#ifndef SERIALPORTDIALOG_HPP
#define SERIALPORTDIALOG_HPP

#include <QDialog>
#include <QSerialPortInfo>

#include "serialporthandler.hpp"

namespace Ui {
class SerialPortDialog;
}

/**
 * @brief The SerialPortDialog class предназначен для установления и отмены подключения
 * сериал порта по настраиваемым параметрам
 */
class SerialPortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialPortDialog(QWidget *parent = nullptr);
    ~SerialPortDialog();

    void setSerialPort(std::shared_ptr<SerialPortHead> serial_port);

private slots:
    void searchPorts();
    void connectPort();
    void disconnectPort();
    void updateVisible();

private:
    Ui::SerialPortDialog *ui;

    QList<QSerialPortInfo> _available_ports;
    std::shared_ptr<SerialPortHead> _serial_port;

    void connectSignalPort();
    void disconnectSignalPort();
};

#endif // SERIALPORTDIALOG_HPP
