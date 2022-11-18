#ifndef COMMANDSENDER_HPP
#define COMMANDSENDER_HPP

#include <memory>

#include <QObject>
#include <QHash>

#include "serialporthandler.hpp"

/**
 * @brief The CommandSender class - абстракция, для простой подачи команд на порт.
 * Формирует заголовки (headers) сообщений
 */
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
    void sendCommand(const QByteArray  &head, const QString &value);

    std::shared_ptr<SerialPortHead> _serial_port;

};

#endif // COMMANDSENDER_HPP
