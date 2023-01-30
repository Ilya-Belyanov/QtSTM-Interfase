#ifndef SENDERCONNECTOR_H
#define SENDERCONNECTOR_H

#include <QObject>
#include <QVariant>

#include "database.hpp"
#include "commandsender.hpp"

class Q_DECL_EXPORT SenderConnector : public QObject
{
    Q_OBJECT
public:
    explicit SenderConnector(const Database *db = nullptr,
                             CommandSender *sender  = nullptr,
                             QObject *parent = nullptr);

    void setDB(const Database *db){_db = db;};
    void setSender(CommandSender *sender){_sender = sender;};

    bool connectDbToSender();

private:
    const Database *_db;
    CommandSender *_sender;

private slots:
    void setServoADegree(const QVariant &degree);
    void setServoBDegree(const QVariant &degree);
    void setStepAPosition(const QVariant &degree);
    void setStepBPosition(const QVariant &degree);
    void setStepASpeed(const QVariant &speed);
    void setStepBSpeed(const QVariant &speed);

signals:

};

#endif // SENDERCONNECTOR_H
