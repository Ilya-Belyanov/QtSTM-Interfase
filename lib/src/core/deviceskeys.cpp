#include "deviceskeys.hpp"

namespace Devices {

    QHash<int, QByteArray> headers{
        {SERVO_A, "SA"},
        {SERVO_B, "SB"},
        {STEP_DRIVER_A, "DA"},
        {STEP_DRIVER_B, "DB"}
    };
}
