#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QSerialPortInfo>

#include "serialporthandler.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void errorWindow(const QString &error);
    void viewData(const QString &data);

private slots:
    void searchPorts();
    void connectPort();
    void sendData();

private:
    Ui::MainWindow *ui;
    QList<QSerialPortInfo> _availablePorts;

    std::unique_ptr<SerialPortHead> serial_port;
};
#endif // MAINWINDOW_HPP
