#ifndef SLIDERVCOMPONENT_HPP
#define SLIDERVCOMPONENT_HPP

#include <QWidget>

#include "models/variablemodel.hpp"

namespace Ui {
class SliderVComponent;
}

class SliderVComponent : public QWidget
{
    Q_OBJECT

public:
    explicit SliderVComponent(QWidget *parent = nullptr);
    ~SliderVComponent();
    void setModel(std::shared_ptr<VariableModel> value);

private:
    Ui::SliderVComponent *ui;
    std::shared_ptr<VariableModel> _value;

    void connectModel();
    void disconnectModel();

private slots:
    void updateRealValue(int value);
    void updateRequestValue(int value);
};

#endif // SLIDERVCOMPONENT_HPP
