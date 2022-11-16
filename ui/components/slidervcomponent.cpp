#include "slidervcomponent.hpp"
#include "../view/ui_slidervcomponent.h"

#include <QVariant>

SliderVComponent::SliderVComponent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliderVComponent)
{
    ui->setupUi(this);
    connect(ui->requestSlider, SIGNAL(valueChanged(int)), this, SLOT(updateRequestValue(int)));
}

SliderVComponent::~SliderVComponent()
{
    delete ui;
}

void SliderVComponent::setModel(std::shared_ptr<VariableModel> value)
{
    if(_value)
        disconnectModel();
    _value = value;

    updateVisible();
    connectModel();
}

void SliderVComponent::updateVisible()
{
    ui->label->setText(_value->name());
    ui->realValueSlider->setValue(_value->realValue().toInt());
    ui->requestSlider->setValue(_value->value().toInt());
    ui->realValueSlider->setVisible(_value->type() & VariableKeys::NEED_REAL);
    ui->requestSlider->setVisible(_value->type() & VariableKeys::USE_REQUEST);
}

void SliderVComponent::connectModel()
{
    if(_value->type() & VariableKeys::NEED_REAL)
        connect(_value.get(), SIGNAL(realValueChanged(const QVariant&)), this, SLOT(updateRealValue(const QVariant&)));
    if(_value->type() & VariableKeys::USE_REQUEST)
        connect(_value.get(), SIGNAL(requestValueChanged(const QVariant&)), this, SLOT(updateRequestViewValue(const QVariant&)));
}

void SliderVComponent::disconnectModel()
{
    if(_value->type() & VariableKeys::NEED_REAL)
        disconnect(_value.get(), SIGNAL(realValueChanged(const QVariant&)), this, SLOT(updateRealValue(const QVariant&)));
    if(_value->type() & VariableKeys::USE_REQUEST)
        disconnect(_value.get(), SIGNAL(requestValueChanged(const QVariant&)), this, SLOT(updateRequestViewValue(const QVariant&)));
}

void SliderVComponent::updateRealValue(const QVariant &value)
{
    ui->realValueSlider->setValue(value.toInt());
}

void SliderVComponent::updateRequestViewValue(const QVariant& value)
{
    ui->realValueSlider->setValue(value.toInt());
}

void SliderVComponent::updateRequestValue(int value)
{
    if(_value)
        _value->setValue(value);
}
