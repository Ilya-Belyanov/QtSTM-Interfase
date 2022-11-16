#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QCloseEvent>

#include "serialporthandler.hpp"
#include "database.hpp"
#include "commandsender.hpp"
#include "mainrecievehandler.hpp"
#include "senderconnector.hpp"

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
    void messageWindow(const QString &msg);
    void updateVisible();

private slots:
    void openConnectionDialog();
    void openCommunicationDialog();

private:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    Database _db;
    CommandSender _sender;
    SenderConnector _sender_connector;
    MainRecieveHandler _recieve_handler;
    std::shared_ptr<SerialPortHead> serial_port;
};
#endif // MAINWINDOW_HPP
