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
    ui->label->setText(_value->name());
    ui->realValueSlider->setValue(_value->realValue().toInt());
    ui->requestSlider->setValue(_value->value().toInt());
    connectModel();
}

void SliderVComponent::connectModel()
{
    connect(_value.get(), SIGNAL(realValueChanged(const QVariant&)), this, SLOT(updateRealValue(const QVariant&)));
    connect(_value.get(), SIGNAL(requestValueChanged(const QVariant&)), this, SLOT(updateRequestViewValue(const QVariant&)));
}

void SliderVComponent::disconnectModel()
{
    disconnect(_value.get(), SIGNAL(realValueChanged(const QVariant&)), this, SLOT(updateRealValue(const QVariant&)));
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
    {
        _value->setValue(value);
        _value->setRealValue(value);
    }
}
