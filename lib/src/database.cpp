#include "database.hpp"

Database::Database(QObject *parent)
    : QObject{parent}
{
    _servo_a = std::make_shared<VariableModel>();
    _servo_b = std::make_shared<VariableModel>();
    _step_driver_a = std::make_shared<VariableModel>();
    _step_driver_b = std::make_shared<VariableModel>();
}
