#ifndef DEVICESKEYS_H
#define DEVICESKEYS_H

#include <QHash>
#include <QByteArray>

namespace Devices {
    enum Devices{
        SERVO_A = 0, SERVO_B,
        STEP_DRIVER_A, STEP_DRIVER_B
    };

    extern QHash<int, QByteArray> headers;
}

#endif // DEVICESKEYS_H
