#include "variablemodel.hpp"

VariableModel::VariableModel(const QString &name, QObject *parent)
    : QObject{parent},
      _request_value(0),
      _real_value(0),
      _name(name)
{}

void VariableModel::setValue(int value)
{
    if(value == _request_value)
        return;
    _request_value = value;
    emit requestValueChanged(value);
}

void VariableModel::setRealValue(int value)
{
    if(value == _real_value)
        return;
    _real_value = value;
    emit realValueChanged(value);
}
