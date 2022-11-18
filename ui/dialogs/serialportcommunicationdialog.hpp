#ifndef SERIALPORTCOMMUNICATIONDIALOG_HPP
#define SERIALPORTCOMMUNICATIONDIALOG_HPP

#include <QDialog>

#include "serialporthandler.hpp"

namespace Ui {
class SerialPortCommunicationDialog;
}

/**
 * @brief The SerialPortCommunicationDialog class предоставляет
 * простой интерфейс для подачи текстовых сообщение через порт.
 * Возможен просмотр отправленных команд (reauests) через это окно и полученных
 * ответов (recieve)
 */
class SerialPortCommunicationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialPortCommunicationDialog(QWidget *parent = nullptr);
    ~SerialPortCommunicationDialog();
    void setSerialPort(std::shared_ptr<SerialPortHead> serial_port);

public slots:
    void viewData(const QByteArray  &data);

private slots:
    void sendData();

private:
    Ui::SerialPortCommunicationDialog *ui;

    std::shared_ptr<SerialPortHead> _serial_port;

    void connectPort();
    void disconnectPort();
};

#endif // SERIALPORTCOMMUNICATIONDIALOG_HPP
