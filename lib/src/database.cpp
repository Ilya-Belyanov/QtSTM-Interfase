#include "database.hpp"

Database::Database(QObject *parent)
    : QObject{parent}
{
    _servo_a = std::make_shared<VariableModel>("SERVO A");
    _servo_b = std::make_shared<VariableModel>("SERVO B");
    _step_driver_a = std::make_shared<VariableModel>("STEP DRIVER A", VariableKeys::NEED_REAL | VariableKeys::USE_REQUEST);
    _step_driver_b = std::make_shared<VariableModel>("STEP DRIVER B", VariableKeys::NEED_REAL | VariableKeys::USE_REQUEST);
}
