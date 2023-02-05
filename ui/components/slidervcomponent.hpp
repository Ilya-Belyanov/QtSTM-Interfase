#ifndef SLIDERVCOMPONENT_HPP
#define SLIDERVCOMPONENT_HPP

#include <QWidget>

#include "models/variablemodel.hpp"

namespace Ui {
class SliderVComponent;
}

/**
 * @brief The SliderVComponent class компонент вертикального слайдера
 * для управления переменной типа int.
 * Поэтому модель должна хранить переменную типа int!
 */
class SliderVComponent : public QWidget
{
    Q_OBJECT

public:
    explicit SliderVComponent(QWidget *parent = nullptr);
    ~SliderVComponent();
    void setModel(std::shared_ptr<VariableModel> value);
    void setRangeValue(int min, int max, int step = 1);

private:
    Ui::SliderVComponent *ui;
    std::shared_ptr<VariableModel> _value;

    void updateVisible();
    void connectModel();
    void disconnectModel();

private slots:
    void updateRealValue(const QVariant& value);
    void updateRequestViewValue(const QVariant& value);

    void updateRequestValue(int value);
};

#endif // SLIDERVCOMPONENT_HPP
