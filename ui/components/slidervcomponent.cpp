#include "slidervcomponent.hpp"
#include "../view/ui_slidervcomponent.h"

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
    connectModel();
}

void SliderVComponent::connectModel()
{
    connect(_value.get(), SIGNAL(realValueChanged(int)), this, SLOT(updateRealValue(int)));
}

void SliderVComponent::disconnectModel()
{
    disconnect(_value.get(), SIGNAL(realValueChanged(int)), this, SLOT(updateRealValue(int)));
}

void SliderVComponent::updateRealValue(int value)
{
    ui->realValueSlider->setValue(value);
}

void SliderVComponent::updateRequestValue(int value)
{
    if(_value)
        _value->setValue(value);
}
