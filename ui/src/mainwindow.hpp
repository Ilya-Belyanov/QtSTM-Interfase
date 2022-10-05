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

private slots:
    void openConnectionDialog();
    void openCommunicationDialog();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<SerialPortHead> serial_port;
};
#endif // MAINWINDOW_HPP