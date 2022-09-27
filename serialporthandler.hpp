#ifndef SERIALPORTHANDLER_HPP
#define SERIALPORTHANDLER_HPP

#include <QObject>
#include <QSerialPort>

struct PortSettings {//Структура с настройками порта
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
};

class SerialPortHead : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortHead(QObject *parent = nullptr);

    void setSettings(const PortSettings &settings);

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

signals:
    void error(const QString &err);//Сигнал ошибок порта
    void data(const QString &data); //Сигнал вывода полученных данных
};

#endif // SERIALPORTHANDLER_HPP
