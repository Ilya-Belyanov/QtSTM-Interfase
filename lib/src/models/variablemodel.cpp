#include "variablemodel.hpp"

VariableModel::VariableModel(const QString &name, const unsigned char &type, QObject *parent)
    : QObject{parent},
      _request_value(0),
      _real_value(0),
      _name(name),
      _type(type)
{}

void VariableModel::setValue(const QVariant &value)
{
    if(value == _request_value)
        return;
    _request_value = value;
    emit requestValueChanged(value);
}

void VariableModel::setRealValue(const QVariant &value)
{
    if(value == _real_value)
        return;
    _real_value = value;
    emit realValueChanged(value);
}
