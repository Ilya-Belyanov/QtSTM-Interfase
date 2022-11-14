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
    ui->label->setText(_value->name());
    ui->realValueSlider->setValue(_value->realValue());
    ui->requestSlider->setValue(_value->value());
    connectModel();
}

void SliderVComponent::connectModel()
{
    connect(_value.get(), SIGNAL(realValueChanged(int)), ui->realValueSlider, SLOT(setValue(int)));
    connect(_value.get(), SIGNAL(requestValueChanged(int)), ui->requestSlider, SLOT(setValue(int)));
}

void SliderVComponent::disconnectModel()
{
    disconnect(_value.get(), SIGNAL(realValueChanged(int)), ui->realValueSlider, SLOT(setValue(int)));
    disconnect(_value.get(), SIGNAL(requestValueChanged(int)), ui->requestSlider, SLOT(setValue(int)));
}

void SliderVComponent::updateRealValue(int value)
{
    ui->realValueSlider->setValue(value);
}

void SliderVComponent::updateRequestValue(int value)
{
    if(_value)
    {
        _value->setValue(value);
        _value->setRealValue(value);
    }
}
