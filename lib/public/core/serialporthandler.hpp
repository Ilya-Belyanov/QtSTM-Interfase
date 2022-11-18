#ifndef SERIALPORTHANDLER_HPP
#define SERIALPORTHANDLER_HPP

#include <chrono>

#include <QObject>
#include <QSerialPort>

#include "mainrecievehandler.hpp"

struct PortSettings {//Структура с настройками порта
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
};

/**
 * @brief The SerialPortHead class - удобный класс для управления Сериал портом.
 * Фасад.
 */
class Q_DECL_EXPORT SerialPortHead : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortHead(QObject *parent = nullptr);

    void setSettings(const PortSettings &settings);
    bool isOpen(){return _serial.isOpen();};
    void setRecieveHandler(MainRecieveHandler *reciever);

public slots:
    void disconnectPort(); // Слот отключения порта
    void connectPort(); // Слот подключения порта
    void write(const QByteArray &bytes);

private slots:
    void handleError(QSerialPort::SerialPortError error);//Слот обработки ощибок
    void readFromPort(); //Слот чтения из порта по ReadyRead

private:
    QSerialPort  _serial;
    PortSettings _settings_port;
    MainRecieveHandler *_reciever;

    std::chrono::steady_clock::time_point begin;

Q_SIGNALS:
     void isOpenChanged(bool isOpen);
     void message(const QString &msg);//Сигнал ошибок порта
     void error(const QString &err);//Сигнал ошибок порта
     void data(const QByteArray &data); //Сигнал вывода полученных данных
};

#endif // SERIALPORTHANDLER_HPP
