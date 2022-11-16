#ifndef RECIEVEEVENTS_H
#define RECIEVEEVENTS_H


#include <QEvent>

static const QEvent::Type RecieveEventType = static_cast<QEvent::Type>(2000);

struct RecieveEvent : public QEvent {
    RecieveEvent():
        QEvent(RecieveEventType){}
};

#endif // RECIEVEEVENTS_H
