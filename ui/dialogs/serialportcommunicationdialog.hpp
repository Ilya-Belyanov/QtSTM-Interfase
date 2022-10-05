#ifndef SERIALPORTCOMMUNICATIONDIALOG_HPP
#define SERIALPORTCOMMUNICATIONDIALOG_HPP

#include <QDialog>

#include "serialporthandler.hpp"

namespace Ui {
class SerialPortCommunicationDialog;
}

class SerialPortCommunicationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialPortCommunicationDialog(QWidget *parent = nullptr);
    ~SerialPortCommunicationDialog();
    void setSerialPort(std::shared_ptr<SerialPortHead> serial_port);

public slots:
    void viewData(const QString &data);

private slots:
    void sendData();

private:
    Ui::SerialPortCommunicationDialog *ui;

    std::shared_ptr<SerialPortHead> _serial_port;
};

#endif // SERIALPORTCOMMUNICATIONDIALOG_HPP
