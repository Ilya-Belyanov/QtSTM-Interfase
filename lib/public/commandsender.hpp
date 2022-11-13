#ifndef COMMANDSENDER_HPP
#define COMMANDSENDER_HPP

#include <memory>

#include <QObject>
#include <QHash>

#include "serialporthandler.hpp"

class Q_DECL_EXPORT CommandSender : public QObject
{
    Q_OBJECT
public:
    explicit CommandSender(QObject *parent = nullptr);

    void setSerialPort(std::shared_ptr<SerialPortHead> serial_port);

public slots:
    void setServoADegree(int degree);
    void setServoBDegree(int degree);
    void setStepDriverAPos(int position);
    void setStepDriverBPos(int position);

signals:

private:
    enum Devices{
        SERVO_A = 0, SERVO_B,
        STEP_DRIVER_A, STEP_DRIVER_B
    };

    QHash<int, QString> headers{
        {CommandSender::SERVO_A, "SA"},
        {CommandSender::SERVO_B, "SB"},
        {CommandSender::STEP_DRIVER_A, "DA"},
        {CommandSender::STEP_DRIVER_B, "DB"}
    };

    void sendCommand(const QString &head, const QString &value);

    std::shared_ptr<SerialPortHead> _serial_port;

};

#endif // COMMANDSENDER_HPP
