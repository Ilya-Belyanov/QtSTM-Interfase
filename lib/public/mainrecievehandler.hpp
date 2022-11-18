#ifndef MAINRECIEVEHANDLER_H
#define MAINRECIEVEHANDLER_H

#include <QObject>
#include <QEvent>

#include "database.hpp"

/**
 * @brief The MainRecieveHandler class - должне обрабатывать сообщения,
 * приходящие из COM порта
 */
class Q_DECL_EXPORT MainRecieveHandler : public QObject
{
    Q_OBJECT
public:
    explicit MainRecieveHandler(QObject *parent = nullptr);

    void setDB(Database *db){_db = db;};

public slots:
    void handler(const QByteArray &data);

private:

    // Возможно будем использовать в будущем
    bool event(QEvent *event);

private:
    // Указатель на внешнюю БД
    Database *_db;

signals:

};

#endif // MAINRECIEVEHANDLER_H
