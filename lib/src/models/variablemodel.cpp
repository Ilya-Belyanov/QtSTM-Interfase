#include "variablemodel.hpp"

VariableModel::VariableModel(QObject *parent)
    : QObject{parent}
{

}

void VariableModel::setValue(int value)
{
    _request_value = value;
    emit requestValueChanged(value);
}

void VariableModel::setRealValue(int value)
{
    _real_value = value;
    emit realValueChanged(value);
}
